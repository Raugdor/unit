
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Valentin V. Bartenev
 * Copyright (C) NGINX, Inc.
 */

#include <nxt_main.h>
#include <nxt_conf.h>
#if 0
#include <math.h>
#include <float.h>
#endif


#define NXT_CONF_MAX_SHORT_STRING  14
#define NXT_CONF_MAX_STRING        NXT_INT32_T_MAX


typedef enum {
    NXT_CONF_VALUE_NULL = 0,
    NXT_CONF_VALUE_BOOLEAN,
    NXT_CONF_VALUE_INTEGER,
    NXT_CONF_VALUE_NUMBER,
    NXT_CONF_VALUE_SHORT_STRING,
    NXT_CONF_VALUE_STRING,
    NXT_CONF_VALUE_ARRAY,
    NXT_CONF_VALUE_OBJECT,
} nxt_conf_value_type_t;


typedef enum {
    NXT_CONF_OP_PASS = 0,
    NXT_CONF_OP_CREATE,
    NXT_CONF_OP_REPLACE,
    NXT_CONF_OP_DELETE,
} nxt_conf_op_action_t;


typedef struct nxt_conf_array_s   nxt_conf_array_t;
typedef struct nxt_conf_object_s  nxt_conf_object_t;


struct nxt_aligned(8) nxt_conf_value_s {
    union nxt_packed {
        uint8_t               boolean;  /* 1 bit. */
        int64_t               integer;
        double                number;
        u_char                str[1 + NXT_CONF_MAX_SHORT_STRING];

        struct nxt_packed {
            u_char            *start;
            uint32_t          length;
        } string;

        nxt_conf_array_t      *array;
        nxt_conf_object_t     *object;
    } u;

    uint8_t                   type;  /* 3 bits. */
};


struct nxt_conf_array_s {
    nxt_uint_t                count;
    nxt_conf_value_t          elements[];
};


typedef struct {
    nxt_conf_value_t          name;
    nxt_conf_value_t          value;
} nxt_conf_object_member_t;


struct nxt_conf_object_s {
    nxt_uint_t                count;
    nxt_conf_object_member_t  members[];
};


struct nxt_conf_op_s {
    uint32_t                  index;
    uint32_t                  action;  /* nxt_conf_op_action_t */
    void                      *ctx;
    nxt_conf_op_t             *next;
};


static u_char *nxt_conf_json_skip_space(u_char *start, u_char *end);
static u_char *nxt_conf_json_parse_value(nxt_mp_t *mp, nxt_conf_value_t *value,
    u_char *start, u_char *end);
static u_char *nxt_conf_json_parse_object(nxt_mp_t *mp, nxt_conf_value_t *value,
    u_char *start, u_char *end);
static nxt_int_t nxt_conf_object_hash_add(nxt_mp_t *mp,
    nxt_lvlhsh_t *lvlhsh, nxt_conf_object_member_t *member);
static nxt_int_t nxt_conf_object_hash_test(nxt_lvlhsh_query_t *lhq,
    void *data);
static void *nxt_conf_object_hash_alloc(void *data, size_t size);
static void nxt_conf_object_hash_free(void *data, void *p);
static u_char *nxt_conf_json_parse_array(nxt_mp_t *mp, nxt_conf_value_t *value,
    u_char *start, u_char *end);
static u_char *nxt_conf_json_parse_string(nxt_mp_t *mp, nxt_conf_value_t *value,
    u_char *start, u_char *end);
static u_char *nxt_conf_json_parse_number(nxt_mp_t *mp, nxt_conf_value_t *value,
    u_char *start, u_char *end);

static nxt_int_t nxt_conf_copy_value(nxt_mp_t *mp, nxt_conf_op_t *op,
    nxt_conf_value_t *dst, nxt_conf_value_t *src);
static nxt_int_t nxt_conf_copy_object(nxt_mp_t *mp, nxt_conf_op_t *op,
    nxt_conf_value_t *dst, nxt_conf_value_t *src);

static size_t nxt_conf_json_integer_length(nxt_conf_value_t *value);
static u_char *nxt_conf_json_print_integer(u_char *p, nxt_conf_value_t *value);
static size_t nxt_conf_json_string_length(nxt_conf_value_t *value);
static u_char *nxt_conf_json_print_string(u_char *p, nxt_conf_value_t *value);
static size_t nxt_conf_json_array_length(nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);
static u_char *nxt_conf_json_print_array(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);
static size_t nxt_conf_json_object_length(nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);
static u_char *nxt_conf_json_print_object(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty);

static size_t nxt_conf_json_escape_length(u_char *p, size_t size);
static u_char *nxt_conf_json_escape(u_char *dst, u_char *src, size_t size);


#define nxt_conf_json_newline(p)                                              \
    ((p)[0] = '\r', (p)[1] = '\n', (p) + 2)


nxt_inline u_char *
nxt_conf_json_indentation(u_char *p, uint32_t level)
{
    while (level) {
        *p++ = '\t';
        level--;
    }

    return p;
}


void
nxt_conf_get_string(nxt_conf_value_t *value, nxt_str_t *str)
{
    if (value->type == NXT_CONF_VALUE_SHORT_STRING) {
        str->length = value->u.str[0];
        str->start = &value->u.str[1];

    } else {
        str->length = value->u.string.length;
        str->start = value->u.string.start;
    }
}


nxt_uint_t
nxt_conf_object_members_count(nxt_conf_value_t *value)
{
    return value->u.object->count;
}


nxt_conf_value_t *
nxt_conf_create_object(nxt_mp_t *mp, nxt_uint_t count)
{
    size_t            size;
    nxt_conf_value_t  *value;

    size = sizeof(nxt_conf_value_t)
           + sizeof(nxt_conf_object_t)
           + count * sizeof(nxt_conf_object_member_t);

    value = nxt_mp_get(mp, size);
    if (nxt_slow_path(value == NULL)) {
        return NULL;
    }

    value->u.object = nxt_pointer_to(value, sizeof(nxt_conf_value_t));
    value->u.object->count = count;

    value->type = NXT_CONF_VALUE_OBJECT;

    return value;
}


nxt_int_t
nxt_conf_set_object_member(nxt_conf_value_t *object, nxt_str_t *name,
    nxt_conf_value_t *value, uint32_t index)
{
    nxt_conf_value_t          *name_value;
    nxt_conf_object_member_t  *member;

    member = &object->u.object->members[index];
    name_value = &member->name;

    if (name->length > NXT_CONF_MAX_SHORT_STRING) {
        name_value->type = NXT_CONF_VALUE_STRING;
        name_value->u.string.length = name->length;
        name_value->u.string.start = name->start;

    } else {
        name_value->type = NXT_CONF_VALUE_SHORT_STRING;
        name_value->u.str[0] = name->length;

        nxt_memcpy(&name_value->u.str[1], name->start, name->length);
    }

    member->value = *value;

    return NXT_OK;
}


nxt_uint_t
nxt_conf_type(nxt_conf_value_t *value)
{
    switch (value->type) {

    case NXT_CONF_VALUE_NULL:
        return NXT_CONF_NULL;

    case NXT_CONF_VALUE_BOOLEAN:
        return NXT_CONF_BOOLEAN;

    case NXT_CONF_VALUE_INTEGER:
        return NXT_CONF_INTEGER;

    case NXT_CONF_VALUE_NUMBER:
        return NXT_CONF_NUMBER;

    case NXT_CONF_VALUE_SHORT_STRING:
    case NXT_CONF_VALUE_STRING:
        return NXT_CONF_STRING;

    case NXT_CONF_VALUE_ARRAY:
        return NXT_CONF_ARRAY;

    case NXT_CONF_VALUE_OBJECT:
        return NXT_CONF_OBJECT;
    }

    nxt_unreachable();

    return 0;
}


typedef struct {
    u_char      *start;
    u_char      *end;
    nxt_bool_t  last;
} nxt_conf_path_parse_t;


static void nxt_conf_path_next_token(nxt_conf_path_parse_t *parse,
    nxt_str_t *token);


nxt_conf_value_t *
nxt_conf_get_path(nxt_conf_value_t *value, nxt_str_t *path)
{
    nxt_str_t              token;
    nxt_conf_path_parse_t  parse;

    parse.start = path->start;
    parse.end = path->start + path->length;
    parse.last = 0;

    do {
        nxt_conf_path_next_token(&parse, &token);

        if (token.length == 0) {

            if (parse.last) {
                break;
            }

            return NULL;
        }

        value = nxt_conf_get_object_member(value, &token, NULL);

        if (value == NULL) {
            return NULL;
        }

    } while (parse.last == 0);

    return value;
}


static void
nxt_conf_path_next_token(nxt_conf_path_parse_t *parse, nxt_str_t *token)
{
    u_char  *p, *end;

    end = parse->end;
    p = parse->start + 1;

    token->start = p;

    while (p < end && *p != '/') {
        p++;
    }

    parse->start = p;
    parse->last = (p >= end);

    token->length = p - token->start;
}


nxt_conf_value_t *
nxt_conf_get_object_member(nxt_conf_value_t *value, nxt_str_t *name,
    uint32_t *index)
{
    nxt_str_t                 str;
    nxt_uint_t                n;
    nxt_conf_object_t         *object;
    nxt_conf_object_member_t  *member;

    if (value->type != NXT_CONF_VALUE_OBJECT) {
        return NULL;
    }

    object = value->u.object;

    for (n = 0; n < object->count; n++) {
        member = &object->members[n];

        nxt_conf_get_string(&member->name, &str);

        if (nxt_strstr_eq(&str, name)) {

            if (index != NULL) {
                *index = n;
            }

            return &member->value;
        }
    }

    return NULL;
}


nxt_int_t
nxt_conf_map_object(nxt_conf_value_t *value, nxt_conf_map_t *map, nxt_uint_t n,
    void *data)
{
    nxt_uint_t        i;
    nxt_conf_value_t  *v;

    union {
        uint8_t     ui8;
        int32_t     i32;
        int64_t     i64;
        nxt_int_t   i;
        ssize_t     size;
        off_t       off;
        nxt_msec_t  msec;
        double      dbl;
        nxt_str_t   str;
        void        *v;
    } *ptr;

    for (i = 0; i < n; i++) {

        v = nxt_conf_get_object_member(value, &map[i].name, NULL);

        if (v == NULL || v->type == NXT_CONF_VALUE_NULL) {
            continue;
        }

        ptr = nxt_pointer_to(data, map[i].offset);

        switch (map[i].type) {

        case NXT_CONF_MAP_INT8:

            if (v->type == NXT_CONF_VALUE_BOOLEAN) {
                ptr->ui8 = v->u.boolean;
            }

            break;

        case NXT_CONF_MAP_INT32:
        case NXT_CONF_MAP_INT64:
        case NXT_CONF_MAP_INT:
        case NXT_CONF_MAP_SIZE:
        case NXT_CONF_MAP_OFF:
        case NXT_CONF_MAP_MSEC:

            if (v->type != NXT_CONF_VALUE_INTEGER) {
                break;
            }

            switch (map[i].type) {

            case NXT_CONF_MAP_INT32:
                ptr->i32 = v->u.integer;
                break;

            case NXT_CONF_MAP_INT64:
                ptr->i64 = v->u.integer;
                break;

            case NXT_CONF_MAP_INT:
                ptr->i = v->u.integer;
                break;

            case NXT_CONF_MAP_SIZE:
                ptr->size = v->u.integer;
                break;

            case NXT_CONF_MAP_OFF:
                ptr->off = v->u.integer;
                break;

            case NXT_CONF_MAP_MSEC:
                ptr->msec = v->u.integer;
                break;

            default:
                nxt_unreachable();
            }

            break;

        case NXT_CONF_MAP_DOUBLE:

            if (v->type == NXT_CONF_VALUE_NUMBER) {
                ptr->dbl = v->u.number;

            } else if (v->type == NXT_CONF_VALUE_INTEGER) {
                ptr->dbl = v->u.integer;

            }

            break;

        case NXT_CONF_MAP_STR:

            if (v->type == NXT_CONF_VALUE_SHORT_STRING
                || v->type == NXT_CONF_VALUE_STRING)
            {
                nxt_conf_get_string(v, &ptr->str);
            }

            break;


        case NXT_CONF_MAP_PTR:

            ptr->v = v;

            break;
        }
    }

    return NXT_OK;
}


nxt_conf_value_t *
nxt_conf_next_object_member(nxt_conf_value_t *value, nxt_str_t *name,
    uint32_t *next)
{
    uint32_t                  n;
    nxt_conf_object_t         *object;
    nxt_conf_object_member_t  *member;

    if (value->type != NXT_CONF_VALUE_OBJECT) {
        return NULL;
    }

    n = *next;
    object = value->u.object;

    if (n >= object->count) {
        return NULL;
    }

    member = &object->members[n];
    *next = n + 1;

    nxt_conf_get_string(&member->name, name);

    return &member->value;
}


nxt_int_t
nxt_conf_op_compile(nxt_mp_t *mp, nxt_conf_op_t **ops, nxt_conf_value_t *root,
    nxt_str_t *path, nxt_conf_value_t *value)
{
    nxt_str_t                 token;
    nxt_conf_op_t             *op, **parent;
    nxt_conf_path_parse_t     parse;
    nxt_conf_object_member_t  *member;

    parse.start = path->start;
    parse.end = path->start + path->length;
    parse.last = 0;

    parent = ops;

    for ( ;; ) {
        op = nxt_mp_zget(mp, sizeof(nxt_conf_op_t));
        if (nxt_slow_path(op == NULL)) {
            return NXT_ERROR;
        }

        *parent = op;
        parent = (nxt_conf_op_t **) &op->ctx;

        nxt_conf_path_next_token(&parse, &token);

        root = nxt_conf_get_object_member(root, &token, &op->index);

        if (parse.last) {
            break;
        }

        if (root == NULL) {
            return NXT_DECLINED;
        }

        op->action = NXT_CONF_OP_PASS;
    }

    if (value == NULL) {

        if (root == NULL) {
            return NXT_DECLINED;
        }

        op->action = NXT_CONF_OP_DELETE;

        return NXT_OK;
    }

    if (root == NULL) {

        member = nxt_mp_zget(mp, sizeof(nxt_conf_object_member_t));
        if (nxt_slow_path(member == NULL)) {
            return NXT_ERROR;
        }

        if (token.length > NXT_CONF_MAX_SHORT_STRING) {
            member->name.u.string.length = token.length;
            member->name.u.string.start = token.start;

            member->name.type = NXT_CONF_VALUE_STRING;

        } else {
            member->name.u.str[0] = token.length;
            nxt_memcpy(&member->name.u.str[1], token.start, token.length);

            member->name.type = NXT_CONF_VALUE_SHORT_STRING;
        }

        member->value = *value;

        op->action = NXT_CONF_OP_CREATE;
        op->ctx = member;

    } else {
        op->action = NXT_CONF_OP_REPLACE;
        op->ctx = value;
    }

    return NXT_OK;
}


nxt_conf_value_t *
nxt_conf_clone(nxt_mp_t *mp, nxt_conf_op_t *op, nxt_conf_value_t *value)
{
    nxt_int_t         rc;
    nxt_conf_value_t  *copy;

    copy = nxt_mp_get(mp, sizeof(nxt_conf_value_t));
    if (nxt_slow_path(copy == NULL)) {
        return NULL;
    }

    rc = nxt_conf_copy_value(mp, op, copy, value);

    if (nxt_slow_path(rc != NXT_OK)) {
        return NULL;
    }

    return copy;
}


static nxt_int_t
nxt_conf_copy_value(nxt_mp_t *mp, nxt_conf_op_t *op, nxt_conf_value_t *dst,
    nxt_conf_value_t *src)
{
    size_t      size;
    nxt_int_t   rc;
    nxt_uint_t  n;

    if (op != NULL && src->type != NXT_CONF_VALUE_OBJECT) {
        return NXT_ERROR;
    }

    dst->type = src->type;

    switch (src->type) {

    case NXT_CONF_VALUE_STRING:

        dst->u.string.start = nxt_mp_nget(mp, src->u.string.length);
        if (nxt_slow_path(dst->u.string.start == NULL)) {
            return NXT_ERROR;
        }

        nxt_memcpy(dst->u.string.start, src->u.string.start,
                   src->u.string.length);

        dst->u.string.length = src->u.string.length;

        break;

    case NXT_CONF_VALUE_ARRAY:

        size = sizeof(nxt_conf_array_t)
               + src->u.array->count * sizeof(nxt_conf_value_t);

        dst->u.array = nxt_mp_get(mp, size);
        if (nxt_slow_path(dst->u.array == NULL)) {
            return NXT_ERROR;
        }

        dst->u.array->count = src->u.array->count;

        for (n = 0; n < src->u.array->count; n++) {
            rc = nxt_conf_copy_value(mp, NULL, &dst->u.array->elements[n],
                                               &src->u.array->elements[n]);

            if (nxt_slow_path(rc != NXT_OK)) {
                return NXT_ERROR;
            }
        }

        break;

    case NXT_CONF_VALUE_OBJECT:
        return nxt_conf_copy_object(mp, op, dst, src);

    default:
        dst->u = src->u;
    }

    return NXT_OK;
}


static nxt_int_t
nxt_conf_copy_object(nxt_mp_t *mp, nxt_conf_op_t *op, nxt_conf_value_t *dst,
    nxt_conf_value_t *src)
{
    size_t                    size;
    nxt_int_t                 rc;
    nxt_uint_t                s, d, count, index;
    nxt_conf_op_t             *pass_op;
    nxt_conf_value_t          *value;
    nxt_conf_object_member_t  *member;

    count = src->u.object->count;

    if (op != NULL) {
        if (op->action == NXT_CONF_OP_CREATE) {
            count++;

        } else if (op->action == NXT_CONF_OP_DELETE) {
            count--;
        }
    }

    size = sizeof(nxt_conf_object_t)
           + count * sizeof(nxt_conf_object_member_t);

    dst->u.object = nxt_mp_get(mp, size);
    if (nxt_slow_path(dst->u.object == NULL)) {
        return NXT_ERROR;
    }

    dst->u.object->count = count;

    s = 0;
    d = 0;

    pass_op = NULL;

    /*
     * This initialization is needed only to
     * suppress a warning on GCC 4.8 and older.
     */
    index = 0;

    do {
        if (pass_op == NULL) {
            index = (op == NULL || op->action == NXT_CONF_OP_CREATE)
                    ? src->u.object->count
                    : op->index;
        }

        while (s != index) {
            rc = nxt_conf_copy_value(mp, NULL,
                                     &dst->u.object->members[d].name,
                                     &src->u.object->members[s].name);

            if (nxt_slow_path(rc != NXT_OK)) {
                return NXT_ERROR;
            }

            rc = nxt_conf_copy_value(mp, pass_op,
                                     &dst->u.object->members[d].value,
                                     &src->u.object->members[s].value);

            if (nxt_slow_path(rc != NXT_OK)) {
                return NXT_ERROR;
            }

            s++;
            d++;
        }

        if (pass_op != NULL) {
            pass_op = NULL;
            continue;
        }

        if (op != NULL) {
            switch (op->action) {
            case NXT_CONF_OP_PASS:
                pass_op = op->ctx;
                index++;
                break;

            case NXT_CONF_OP_CREATE:
                member = op->ctx;

                rc = nxt_conf_copy_value(mp, NULL,
                                         &dst->u.object->members[d].name,
                                         &member->name);

                if (nxt_slow_path(rc != NXT_OK)) {
                    return NXT_ERROR;
                }

                dst->u.object->members[d].value = member->value;

                d++;
                break;

            case NXT_CONF_OP_REPLACE:
                rc = nxt_conf_copy_value(mp, NULL,
                                         &dst->u.object->members[d].name,
                                         &src->u.object->members[s].name);

                if (nxt_slow_path(rc != NXT_OK)) {
                    return NXT_ERROR;
                }

                value = op->ctx;

                dst->u.object->members[d].value = *value;

                s++;
                d++;
                break;

            case NXT_CONF_OP_DELETE:
                s++;
                break;
            }

            op = op->next;
        }

    } while (d != count);

    dst->type = src->type;

    return NXT_OK;
}


nxt_conf_value_t *
nxt_conf_json_parse(nxt_mp_t *mp, u_char *start, u_char *end)
{
    u_char            *p;
    nxt_conf_value_t  *value;

    value = nxt_mp_get(mp, sizeof(nxt_conf_value_t));
    if (nxt_slow_path(value == NULL)) {
        return NULL;
    }

    p = nxt_conf_json_skip_space(start, end);

    if (nxt_slow_path(p == end)) {
        return NULL;
    }

    p = nxt_conf_json_parse_value(mp, value, p, end);

    if (nxt_slow_path(p == NULL)) {
        return NULL;
    }

    p = nxt_conf_json_skip_space(p, end);

    if (nxt_slow_path(p != end)) {
        return NULL;
    }

    return value;
}


static u_char *
nxt_conf_json_skip_space(u_char *start, u_char *end)
{
    u_char  *p;

    for (p = start; nxt_fast_path(p != end); p++) {

        switch (*p) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            continue;
        }

        break;
    }

    return p;
}


static u_char *
nxt_conf_json_parse_value(nxt_mp_t *mp, nxt_conf_value_t *value, u_char *start,
    u_char *end)
{
    u_char  ch;

    ch = *start;

    switch (ch) {
    case '{':
        return nxt_conf_json_parse_object(mp, value, start, end);

    case '[':
        return nxt_conf_json_parse_array(mp, value, start, end);

    case '"':
        return nxt_conf_json_parse_string(mp, value, start, end);

    case 't':
        if (nxt_fast_path(end - start >= 4
                          && nxt_memcmp(start, "true", 4) == 0))
        {
            value->u.boolean = 1;
            value->type = NXT_CONF_VALUE_BOOLEAN;

            return start + 4;
        }

        return NULL;

    case 'f':
        if (nxt_fast_path(end - start >= 5
                          && nxt_memcmp(start, "false", 5) == 0))
        {
            value->u.boolean = 0;
            value->type = NXT_CONF_VALUE_BOOLEAN;

            return start + 5;
        }

        return NULL;

    case 'n':
        if (nxt_fast_path(end - start >= 4
                          && nxt_memcmp(start, "null", 4) == 0))
        {
            value->type = NXT_CONF_VALUE_NULL;
            return start + 4;
        }

        return NULL;
    }

    if (nxt_fast_path(ch == '-' || (ch - '0') <= 9)) {
        return nxt_conf_json_parse_number(mp, value, start, end);
    }

    return NULL;
}


static const nxt_lvlhsh_proto_t  nxt_conf_object_hash_proto
    nxt_aligned(64) =
{
    NXT_LVLHSH_DEFAULT,
    nxt_conf_object_hash_test,
    nxt_conf_object_hash_alloc,
    nxt_conf_object_hash_free,
};


static u_char *
nxt_conf_json_parse_object(nxt_mp_t *mp, nxt_conf_value_t *value, u_char *start,
    u_char *end)
{
    u_char                    *p;
    nxt_mp_t                  *mp_temp;
    nxt_int_t                 rc;
    nxt_uint_t                count;
    nxt_lvlhsh_t              hash;
    nxt_lvlhsh_each_t         lhe;
    nxt_conf_object_t         *object;
    nxt_conf_object_member_t  *member, *element;

    mp_temp = nxt_mp_create(1024, 128, 256, 32);
    if (nxt_slow_path(mp_temp == NULL)) {
        return NULL;
    }

    nxt_lvlhsh_init(&hash);

    count = 0;
    p = start;

    for ( ;; ) {
        p = nxt_conf_json_skip_space(p + 1, end);

        if (nxt_slow_path(p == end)) {
            goto error;
        }

        if (*p != '"') {
            if (nxt_fast_path(*p == '}')) {
                break;
            }

            goto error;
        }

        count++;

        member = nxt_mp_get(mp_temp, sizeof(nxt_conf_object_member_t));
        if (nxt_slow_path(member == NULL)) {
            goto error;
        }

        p = nxt_conf_json_parse_string(mp, &member->name, p, end);

        if (nxt_slow_path(p == NULL)) {
            goto error;
        }

        rc = nxt_conf_object_hash_add(mp_temp, &hash, member);

        if (nxt_slow_path(rc != NXT_OK)) {
            goto error;
        }

        p = nxt_conf_json_skip_space(p, end);

        if (nxt_slow_path(p == end || *p != ':')) {
            goto error;
        }

        p = nxt_conf_json_skip_space(p + 1, end);

        if (nxt_slow_path(p == end)) {
            goto error;
        }

        p = nxt_conf_json_parse_value(mp, &member->value, p, end);

        if (nxt_slow_path(p == NULL)) {
            goto error;
        }

        p = nxt_conf_json_skip_space(p, end);

        if (nxt_slow_path(p == end)) {
            goto error;
        }

        if (*p != ',') {
            if (nxt_fast_path(*p == '}')) {
                break;
            }

            goto error;
        }
    }

    object = nxt_mp_get(mp, sizeof(nxt_conf_object_t)
                            + count * sizeof(nxt_conf_object_member_t));
    if (nxt_slow_path(object == NULL)) {
        goto error;
    }

    value->u.object = object;
    value->type = NXT_CONF_VALUE_OBJECT;

    object->count = count;
    member = object->members;

    nxt_memzero(&lhe, sizeof(nxt_lvlhsh_each_t));
    lhe.proto = &nxt_conf_object_hash_proto;

    for ( ;; ) {
        element = nxt_lvlhsh_each(&hash, &lhe);

        if (element == NULL) {
            break;
        }

        *member++ = *element;
    }

    nxt_mp_destroy(mp_temp);

    return p + 1;

error:

    nxt_mp_destroy(mp_temp);
    return NULL;
}


static nxt_int_t
nxt_conf_object_hash_add(nxt_mp_t *mp, nxt_lvlhsh_t *lvlhsh,
    nxt_conf_object_member_t *member)
{
    nxt_lvlhsh_query_t  lhq;

    nxt_conf_get_string(&member->name, &lhq.key);

    lhq.key_hash = nxt_djb_hash(lhq.key.start, lhq.key.length);
    lhq.replace = 0;
    lhq.value = member;
    lhq.proto = &nxt_conf_object_hash_proto;
    lhq.pool = mp;

    return nxt_lvlhsh_insert(lvlhsh, &lhq);
}


static nxt_int_t
nxt_conf_object_hash_test(nxt_lvlhsh_query_t *lhq, void *data)
{
    nxt_str_t                 str;
    nxt_conf_object_member_t  *member;

    member = data;

    nxt_conf_get_string(&member->name, &str);

    if (nxt_strstr_eq(&lhq->key, &str)) {
        return NXT_OK;
    }

    return NXT_DECLINED;
}


static void *
nxt_conf_object_hash_alloc(void *data, size_t size)
{
    return nxt_mp_align(data, size, size);
}


static void
nxt_conf_object_hash_free(void *data, void *p)
{
    nxt_mp_free(data, p);
}


static u_char *
nxt_conf_json_parse_array(nxt_mp_t *mp, nxt_conf_value_t *value, u_char *start,
    u_char *end)
{
    u_char            *p;
    nxt_mp_t          *mp_temp;
    nxt_uint_t        count;
    nxt_list_t        *list;
    nxt_conf_array_t  *array;
    nxt_conf_value_t  *element;

    mp_temp = nxt_mp_create(1024, 128, 256, 32);
    if (nxt_slow_path(mp_temp == NULL)) {
        return NULL;
    }

    list = nxt_list_create(mp_temp, 8, sizeof(nxt_conf_value_t));
    if (nxt_slow_path(list == NULL)) {
        goto error;
    }

    count = 0;
    p = start;

    for ( ;; ) {
        p = nxt_conf_json_skip_space(p + 1, end);

        if (nxt_slow_path(p == end)) {
            goto error;
        }

        if (*p == ']') {
            break;
        }

        count++;

        element = nxt_list_add(list);
        if (nxt_slow_path(element == NULL)) {
            goto error;
        }

        p = nxt_conf_json_parse_value(mp, element, p, end);

        if (nxt_slow_path(p == NULL)) {
            goto error;
        }

        p = nxt_conf_json_skip_space(p, end);

        if (nxt_slow_path(p == end)) {
            goto error;
        }

        if (*p != ',') {
            if (nxt_fast_path(*p == ']')) {
                break;
            }

            goto error;
        }
    }

    array = nxt_mp_get(mp, sizeof(nxt_conf_array_t)
                           + count * sizeof(nxt_conf_value_t));
    if (nxt_slow_path(array == NULL)) {
        goto error;
    }

    value->u.array = array;
    value->type = NXT_CONF_VALUE_ARRAY;

    array->count = count;
    element = array->elements;

    nxt_list_each(value, list) {
        *element++ = *value;
    } nxt_list_loop;

    nxt_mp_destroy(mp_temp);

    return p + 1;

error:

    nxt_mp_destroy(mp_temp);
    return NULL;
}


static u_char *
nxt_conf_json_parse_string(nxt_mp_t *mp, nxt_conf_value_t *value, u_char *start,
    u_char *end)
{
    u_char      *p, ch, *last, *s;
    size_t      size, surplus;
    uint32_t    utf, utf_high;
    nxt_uint_t  i;
    enum {
        sw_usual = 0,
        sw_escape,
        sw_encoded1,
        sw_encoded2,
        sw_encoded3,
        sw_encoded4,
    } state;

    start++;

    state = 0;
    surplus = 0;

    for (p = start; nxt_fast_path(p != end); p++) {
        ch = *p;

        switch (state) {

        case sw_usual:

            if (ch == '"') {
                break;
            }

            if (ch == '\\') {
                state = sw_escape;
                continue;
            }

            if (nxt_fast_path(ch >= ' ')) {
                continue;
            }

            return NULL;

        case sw_escape:

            switch (ch) {
            case '"':
            case '\\':
            case '/':
            case 'n':
            case 'r':
            case 't':
            case 'b':
            case 'f':
                surplus++;
                state = sw_usual;
                continue;

            case 'u':
                /*
                 * Basic unicode 6 bytes "\uXXXX" in JSON
                 * and up to 3 bytes in UTF-8.
                 *
                 * Surrogate pair: 12 bytes "\uXXXX\uXXXX" in JSON
                 * and 3 or 4 bytes in UTF-8.
                 */
                surplus += 3;
                state = sw_encoded1;
                continue;
            }

            return NULL;

        case sw_encoded1:
        case sw_encoded2:
        case sw_encoded3:
        case sw_encoded4:

            if (nxt_fast_path((ch >= '0' && ch <= '9')
                              || (ch >= 'A' && ch <= 'F')))
            {
                state = (state == sw_encoded4) ? sw_usual : state + 1;
                continue;
            }

            return NULL;
        }

        break;
    }

    if (nxt_slow_path(p == end)) {
        return NULL;
    }

    /* Points to the ending quote mark. */
    last = p;

    size = last - start - surplus;

    if (size > NXT_CONF_MAX_SHORT_STRING) {

        if (nxt_slow_path(size > NXT_CONF_MAX_STRING)) {
            return NULL;
        }

        value->type = NXT_CONF_VALUE_STRING;

        value->u.string.start = nxt_mp_nget(mp, size);
        if (nxt_slow_path(value->u.string.start == NULL)) {
            return NULL;
        }

        value->u.string.length = size;

        s = value->u.string.start;

    } else {
        value->type = NXT_CONF_VALUE_SHORT_STRING;
        value->u.str[0] = size;

        s = &value->u.str[1];
    }

    if (surplus == 0) {
        nxt_memcpy(s, start, size);
        return last + 1;
    }

    p = start;

    do {
        ch = *p++;

        if (ch != '\\') {
            *s++ = ch;
            continue;
        }

        ch = *p++;

        switch (ch) {
        case '"':
        case '\\':
        case '/':
            *s++ = ch;
            continue;

        case 'n':
            *s++ = '\n';
            continue;

        case 'r':
            *s++ = '\r';
            continue;

        case 't':
            *s++ = '\t';
            continue;

        case 'b':
            *s++ = '\b';
            continue;

        case 'f':
            *s++ = '\f';
            continue;
        }

        utf = 0;
        utf_high = 0;

        for ( ;; ) {
            for (i = 0; i < 4; i++) {
                utf = (utf << 4) + (p[i] - (p[i] >= 'A' ? 'A' : '0'));
            }

            p += 4;

            if (utf < 0xd800 || utf > 0xdbff || utf_high) {
                break;
            }

            utf_high = utf;
            utf = 0;

            if (p[0] != '\\' || p[1] != 'u') {
                break;
            }

            p += 2;
        }

        if (utf_high != 0) {
            if (nxt_slow_path(utf_high < 0xd800
                              || utf_high > 0xdbff
                              || utf < 0xdc00
                              || utf > 0xdfff))
            {
                /* Invalid surrogate pair. */
                return NULL;
            }

            utf = ((utf_high - 0xd800) << 10) + (utf - 0xdc00);
        }

        s = nxt_utf8_encode(s, utf);

    } while (p != last);

    if (size > NXT_CONF_MAX_SHORT_STRING) {
        value->u.string.length = s - value->u.string.start;

    } else {
        value->u.str[0] = s - &value->u.str[1];
    }

    return last + 1;
}


static u_char *
nxt_conf_json_parse_number(nxt_mp_t *mp, nxt_conf_value_t *value, u_char *start,
    u_char *end)
{
    u_char     *p, ch;
    uint64_t   integer;
    nxt_int_t  sign;
#if 0
    uint64_t   frac, power
    nxt_int_t  e, negative;
#endif

    static const uint64_t cutoff = NXT_INT64_T_MAX / 10;
    static const uint64_t cutlim = NXT_INT64_T_MAX % 10;

    ch = *start;

    if (ch == '-') {
        sign = -1;
        start++;

    } else {
        sign = 1;
    }

    integer = 0;

    for (p = start; nxt_fast_path(p != end); p++) {
        ch = *p;

        /* Values below '0' become >= 208. */
        ch = ch - '0';

        if (ch > 9) {
            break;
        }

        if (nxt_slow_path(integer >= cutoff
                          && (integer > cutoff || ch > cutlim)))
        {
             return NULL;
        }

        integer = integer * 10 + ch;
    }

    if (nxt_slow_path(p == start || (p - start > 1 && *start == '0'))) {
        return NULL;
    }

    if (ch != '.') {
        value->type = NXT_CONF_VALUE_INTEGER;
        value->u.integer = sign * integer;
        return p;
    }

#if 0
    start = p + 1;

    frac = 0;
    power = 1;

    for (p = start; nxt_fast_path(p != end); p++) {
        ch = *p;

        /* Values below '0' become >= 208. */
        ch = ch - '0';

        if (ch > 9) {
            break;
        }

        if (nxt_slow_path((frac >= cutoff && (frac > cutoff || ch > cutlim))
                          || power > cutoff))
        {
            return NULL;
        }

        frac = frac * 10 + ch;
        power *= 10;
    }

    if (nxt_slow_path(p == start)) {
        return NULL;
    }

    value->type = NXT_CONF_VALUE_NUMBER;
    value->u.number = integer + (double) frac / power;

    value->u.number = copysign(value->u.number, sign);

    if (ch == 'e' || ch == 'E') {
        start = p + 1;

        ch = *start;

        if (ch == '-' || ch == '+') {
            start++;
        }

        negative = (ch == '-') ? 1 : 0;
        e = 0;

        for (p = start; nxt_fast_path(p != end); p++) {
            ch = *p;

            /* Values below '0' become >= 208. */
            ch = ch - '0';

            if (ch > 9) {
                break;
            }

            e = e * 10 + ch;

            if (nxt_slow_path(e > DBL_MAX_10_EXP)) {
                return NULL;
            }
        }

        if (nxt_slow_path(p == start)) {
            return NULL;
        }

        if (negative) {
            value->u.number /= exp10(e);

        } else {
            value->u.number *= exp10(e);
        }
    }

    if (nxt_fast_path(isfinite(value->u.number))) {
        return p;
    }
#endif

    return NULL;
}


size_t
nxt_conf_json_length(nxt_conf_value_t *value, nxt_conf_json_pretty_t *pretty)
{
    switch (value->type) {

    case NXT_CONF_VALUE_NULL:
        return sizeof("null") - 1;

    case NXT_CONF_VALUE_BOOLEAN:
        return value->u.boolean ? sizeof("true") - 1 : sizeof("false") - 1;

    case NXT_CONF_VALUE_INTEGER:
        return nxt_conf_json_integer_length(value);

    case NXT_CONF_VALUE_NUMBER:
        /* TODO */
        return 0;

    case NXT_CONF_VALUE_SHORT_STRING:
    case NXT_CONF_VALUE_STRING:
        return nxt_conf_json_string_length(value);

    case NXT_CONF_VALUE_ARRAY:
        return nxt_conf_json_array_length(value, pretty);

    case NXT_CONF_VALUE_OBJECT:
        return nxt_conf_json_object_length(value, pretty);
    }

    nxt_unreachable();

    return 0;
}


u_char *
nxt_conf_json_print(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty)
{
    switch (value->type) {

    case NXT_CONF_VALUE_NULL:
        return nxt_cpymem(p, "null", 4);

    case NXT_CONF_VALUE_BOOLEAN:
        return value->u.boolean ? nxt_cpymem(p, "true", 4)
                                : nxt_cpymem(p, "false", 5);

    case NXT_CONF_VALUE_INTEGER:
        return nxt_conf_json_print_integer(p, value);

    case NXT_CONF_VALUE_NUMBER:
        /* TODO */
        return p;

    case NXT_CONF_VALUE_SHORT_STRING:
    case NXT_CONF_VALUE_STRING:
        return nxt_conf_json_print_string(p, value);

    case NXT_CONF_VALUE_ARRAY:
        return nxt_conf_json_print_array(p, value, pretty);

    case NXT_CONF_VALUE_OBJECT:
        return nxt_conf_json_print_object(p, value, pretty);
    }

    nxt_unreachable();

    return p;
}


static size_t
nxt_conf_json_integer_length(nxt_conf_value_t *value)
{
    int64_t  num;

    num = llabs(value->u.integer);

    if (num <= 9999) {
        return sizeof("-9999") - 1;
    }

    if (num <= 99999999999) {
        return sizeof("-99999999999") - 1;
    }

    return NXT_INT64_T_LEN;
}


static u_char *
nxt_conf_json_print_integer(u_char *p, nxt_conf_value_t *value)
{
    return nxt_sprintf(p, p + NXT_INT64_T_LEN, "%L", value->u.integer);
}


static size_t
nxt_conf_json_string_length(nxt_conf_value_t *value)
{
    nxt_str_t  str;

    nxt_conf_get_string(value, &str);

    return 2 + nxt_conf_json_escape_length(str.start, str.length);
}


static u_char *
nxt_conf_json_print_string(u_char *p, nxt_conf_value_t *value)
{
    nxt_str_t  str;

    nxt_conf_get_string(value, &str);

    *p++ = '"';

    p = nxt_conf_json_escape(p, str.start, str.length);

    *p++ = '"';

    return p;
}


static size_t
nxt_conf_json_array_length(nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty)
{
    size_t            len;
    nxt_uint_t        n;
    nxt_conf_array_t  *array;

    array = value->u.array;

    /* [] */
    len = 2;

    if (pretty != NULL) {
        pretty->level++;
    }

    value = array->elements;

    for (n = 0; n < array->count; n++) {
        len += nxt_conf_json_length(&value[n], pretty);

        if (pretty != NULL) {
            /* Indentation and new line. */
            len += pretty->level + 2;
        }
    }

    if (pretty != NULL) {
        pretty->level--;

        if (n != 0) {
            /* Indentation and new line. */
            len += pretty->level + 2;
        }
    }

    /* Reserve space for "n" commas. */
    return len + n;
}


static u_char *
nxt_conf_json_print_array(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty)
{
    nxt_uint_t        n;
    nxt_conf_array_t  *array;

    array = value->u.array;

    *p++ = '[';

    if (array->count != 0) {
        value = array->elements;

        if (pretty != NULL) {
            p = nxt_conf_json_newline(p);

            pretty->level++;
            p = nxt_conf_json_indentation(p, pretty->level);
        }

        p = nxt_conf_json_print(p, &value[0], pretty);

        for (n = 1; n < array->count; n++) {
            *p++ = ',';

            if (pretty != NULL) {
                p = nxt_conf_json_newline(p);
                p = nxt_conf_json_indentation(p, pretty->level);

                pretty->more_space = 0;
            }

            p = nxt_conf_json_print(p, &value[n], pretty);
        }

        if (pretty != NULL) {
            p = nxt_conf_json_newline(p);

            pretty->level--;
            p = nxt_conf_json_indentation(p, pretty->level);

            pretty->more_space = 1;
        }
    }

    *p++ = ']';

    return p;
}


static size_t
nxt_conf_json_object_length(nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty)
{
    size_t                    len;
    nxt_uint_t                n;
    nxt_conf_object_t         *object;
    nxt_conf_object_member_t  *member;

    object = value->u.object;

    /* {} */
    len = 2;

    if (pretty != NULL) {
        pretty->level++;
    }

    member = object->members;

    for (n = 0; n < object->count; n++) {
        len += nxt_conf_json_string_length(&member[n].name) + 1
               + nxt_conf_json_length(&member[n].value, pretty) + 1;

        if (pretty != NULL) {
            /*
             * Indentation, space after ":", new line, and possible
             * additional empty line between non-empty objects.
             */
            len += pretty->level + 1 + 2 + 2;
        }
    }

    if (pretty != NULL) {
        pretty->level--;

        /* Indentation and new line. */
        len += pretty->level + 2;
    }

    return len;
}


static u_char *
nxt_conf_json_print_object(u_char *p, nxt_conf_value_t *value,
    nxt_conf_json_pretty_t *pretty)
{
    nxt_uint_t                n;
    nxt_conf_object_t         *object;
    nxt_conf_object_member_t  *member;

    object = value->u.object;

    *p++ = '{';

    if (object->count != 0) {

        if (pretty != NULL) {
            p = nxt_conf_json_newline(p);
            pretty->level++;
        }

        member = object->members;

        n = 0;

        for ( ;; ) {
            if (pretty != NULL) {
                p = nxt_conf_json_indentation(p, pretty->level);
            }

            p = nxt_conf_json_print_string(p, &member[n].name);

            *p++ = ':';

            if (pretty != NULL) {
                *p++ = ' ';
            }

            p = nxt_conf_json_print(p, &member[n].value, pretty);

            n++;

            if (n == object->count) {
                break;
            }

            *p++ = ',';

            if (pretty != NULL) {
                p = nxt_conf_json_newline(p);

                if (pretty->more_space) {
                    pretty->more_space = 0;
                    p = nxt_conf_json_newline(p);
                }
            }
        }

        if (pretty != NULL) {
            p = nxt_conf_json_newline(p);

            pretty->level--;
            p = nxt_conf_json_indentation(p, pretty->level);

            pretty->more_space = 1;
        }
    }

    *p++ = '}';

    return p;
}


static size_t
nxt_conf_json_escape_length(u_char *p, size_t size)
{
    u_char  ch;
    size_t  len;

    len = size;

    while (size) {
        ch = *p++;

        if (ch == '\\' || ch == '"') {
            len++;

        } else if (ch <= 0x1f) {

            switch (ch) {
            case '\n':
            case '\r':
            case '\t':
            case '\b':
            case '\f':
                len++;
                break;

            default:
                len += sizeof("\\u001F") - 2;
            }
        }

        size--;
    }

    return len;
}


static u_char *
nxt_conf_json_escape(u_char *dst, u_char *src, size_t size)
{
    u_char  ch;

    while (size) {
        ch = *src++;

        if (ch > 0x1f) {

            if (ch == '\\' || ch == '"') {
                *dst++ = '\\';
            }

            *dst++ = ch;

        } else {
            *dst++ = '\\';

            switch (ch) {
            case '\n':
                *dst++ = 'n';
                break;

            case '\r':
                *dst++ = 'r';
                break;

            case '\t':
                *dst++ = 't';
                break;

            case '\b':
                *dst++ = 'b';
                break;

            case '\f':
                *dst++ = 'f';
                break;

            default:
                *dst++ = 'u'; *dst++ = '0'; *dst++ = '0';
                *dst++ = '0' + (ch >> 4);

                ch &= 0xf;

                *dst++ = (ch < 10) ? ('0' + ch) : ('A' + ch - 10);
            }
        }

        size--;
    }

    return dst;
}
