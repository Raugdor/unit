
/*
 * 15 128-bytes blocks, 511 pointers.
 * 9267 bytes on 32-bit platforms, 11307 bytes on 64-bit platforms.
 */

#define NXT_UNICODE_MAX_LOWCASE  0x0FF3A

#define NXT_UNICODE_BLOCK_SIZE   128


static const uint32_t  nxt_unicode_block_000[128]  nxt_aligned(64) = {
    0x00000, 0x00001, 0x00002, 0x00003, 0x00004, 0x00005, 0x00006, 0x00007,
    0x00008, 0x00009, 0x0000A, 0x0000B, 0x0000C, 0x0000D, 0x0000E, 0x0000F,
    0x00010, 0x00011, 0x00012, 0x00013, 0x00014, 0x00015, 0x00016, 0x00017,
    0x00018, 0x00019, 0x0001A, 0x0001B, 0x0001C, 0x0001D, 0x0001E, 0x0001F,
    0x00020, 0x00021, 0x00022, 0x00023, 0x00024, 0x00025, 0x00026, 0x00027,
    0x00028, 0x00029, 0x0002A, 0x0002B, 0x0002C, 0x0002D, 0x0002E, 0x0002F,
    0x00030, 0x00031, 0x00032, 0x00033, 0x00034, 0x00035, 0x00036, 0x00037,
    0x00038, 0x00039, 0x0003A, 0x0003B, 0x0003C, 0x0003D, 0x0003E, 0x0003F,
    0x00040, 0x00061, 0x00062, 0x00063, 0x00064, 0x00065, 0x00066, 0x00067,
    0x00068, 0x00069, 0x0006A, 0x0006B, 0x0006C, 0x0006D, 0x0006E, 0x0006F,
    0x00070, 0x00071, 0x00072, 0x00073, 0x00074, 0x00075, 0x00076, 0x00077,
    0x00078, 0x00079, 0x0007A, 0x0005B, 0x0005C, 0x0005D, 0x0005E, 0x0005F,
    0x00060, 0x00061, 0x00062, 0x00063, 0x00064, 0x00065, 0x00066, 0x00067,
    0x00068, 0x00069, 0x0006A, 0x0006B, 0x0006C, 0x0006D, 0x0006E, 0x0006F,
    0x00070, 0x00071, 0x00072, 0x00073, 0x00074, 0x00075, 0x00076, 0x00077,
    0x00078, 0x00079, 0x0007A, 0x0007B, 0x0007C, 0x0007D, 0x0007E, 0x0007F,
};


static const uint32_t  nxt_unicode_block_001[128]  nxt_aligned(64) = {
    0x00080, 0x00081, 0x00082, 0x00083, 0x00084, 0x00085, 0x00086, 0x00087,
    0x00088, 0x00089, 0x0008A, 0x0008B, 0x0008C, 0x0008D, 0x0008E, 0x0008F,
    0x00090, 0x00091, 0x00092, 0x00093, 0x00094, 0x00095, 0x00096, 0x00097,
    0x00098, 0x00099, 0x0009A, 0x0009B, 0x0009C, 0x0009D, 0x0009E, 0x0009F,
    0x000A0, 0x000A1, 0x000A2, 0x000A3, 0x000A4, 0x000A5, 0x000A6, 0x000A7,
    0x000A8, 0x000A9, 0x000AA, 0x000AB, 0x000AC, 0x000AD, 0x000AE, 0x000AF,
    0x000B0, 0x000B1, 0x000B2, 0x000B3, 0x000B4, 0x000B5, 0x000B6, 0x000B7,
    0x000B8, 0x000B9, 0x000BA, 0x000BB, 0x000BC, 0x000BD, 0x000BE, 0x000BF,
    0x000E0, 0x000E1, 0x000E2, 0x000E3, 0x000E4, 0x000E5, 0x000E6, 0x000E7,
    0x000E8, 0x000E9, 0x000EA, 0x000EB, 0x000EC, 0x000ED, 0x000EE, 0x000EF,
    0x000F0, 0x000F1, 0x000F2, 0x000F3, 0x000F4, 0x000F5, 0x000F6, 0x000D7,
    0x000F8, 0x000F9, 0x000FA, 0x000FB, 0x000FC, 0x000FD, 0x000FE, 0x000DF,
    0x000E0, 0x000E1, 0x000E2, 0x000E3, 0x000E4, 0x000E5, 0x000E6, 0x000E7,
    0x000E8, 0x000E9, 0x000EA, 0x000EB, 0x000EC, 0x000ED, 0x000EE, 0x000EF,
    0x000F0, 0x000F1, 0x000F2, 0x000F3, 0x000F4, 0x000F5, 0x000F6, 0x000F7,
    0x000F8, 0x000F9, 0x000FA, 0x000FB, 0x000FC, 0x000FD, 0x000FE, 0x000FF,
};


static const uint32_t  nxt_unicode_block_002[128]  nxt_aligned(64) = {
    0x00101, 0x00101, 0x00103, 0x00103, 0x00105, 0x00105, 0x00107, 0x00107,
    0x00109, 0x00109, 0x0010B, 0x0010B, 0x0010D, 0x0010D, 0x0010F, 0x0010F,
    0x00111, 0x00111, 0x00113, 0x00113, 0x00115, 0x00115, 0x00117, 0x00117,
    0x00119, 0x00119, 0x0011B, 0x0011B, 0x0011D, 0x0011D, 0x0011F, 0x0011F,
    0x00121, 0x00121, 0x00123, 0x00123, 0x00125, 0x00125, 0x00127, 0x00127,
    0x00129, 0x00129, 0x0012B, 0x0012B, 0x0012D, 0x0012D, 0x0012F, 0x0012F,
    0x00130, 0x00131, 0x00133, 0x00133, 0x00135, 0x00135, 0x00137, 0x00137,
    0x00138, 0x0013A, 0x0013A, 0x0013C, 0x0013C, 0x0013E, 0x0013E, 0x00140,
    0x00140, 0x00142, 0x00142, 0x00144, 0x00144, 0x00146, 0x00146, 0x00148,
    0x00148, 0x00149, 0x0014B, 0x0014B, 0x0014D, 0x0014D, 0x0014F, 0x0014F,
    0x00151, 0x00151, 0x00153, 0x00153, 0x00155, 0x00155, 0x00157, 0x00157,
    0x00159, 0x00159, 0x0015B, 0x0015B, 0x0015D, 0x0015D, 0x0015F, 0x0015F,
    0x00161, 0x00161, 0x00163, 0x00163, 0x00165, 0x00165, 0x00167, 0x00167,
    0x00169, 0x00169, 0x0016B, 0x0016B, 0x0016D, 0x0016D, 0x0016F, 0x0016F,
    0x00171, 0x00171, 0x00173, 0x00173, 0x00175, 0x00175, 0x00177, 0x00177,
    0x000FF, 0x0017A, 0x0017A, 0x0017C, 0x0017C, 0x0017E, 0x0017E, 0x0017F,
};


static const uint32_t  nxt_unicode_block_003[128]  nxt_aligned(64) = {
    0x00180, 0x00253, 0x00183, 0x00183, 0x00185, 0x00185, 0x00254, 0x00188,
    0x00188, 0x00256, 0x00257, 0x0018C, 0x0018C, 0x0018D, 0x001DD, 0x00259,
    0x0025B, 0x00192, 0x00192, 0x00260, 0x00263, 0x00195, 0x00269, 0x00268,
    0x00199, 0x00199, 0x0019A, 0x0019B, 0x0026F, 0x00272, 0x0019E, 0x00275,
    0x001A1, 0x001A1, 0x001A3, 0x001A3, 0x001A5, 0x001A5, 0x001A6, 0x001A8,
    0x001A8, 0x00283, 0x001AA, 0x001AB, 0x001AD, 0x001AD, 0x00288, 0x001B0,
    0x001B0, 0x0028A, 0x0028B, 0x001B4, 0x001B4, 0x001B6, 0x001B6, 0x00292,
    0x001B9, 0x001B9, 0x001BA, 0x001BB, 0x001BD, 0x001BD, 0x001BE, 0x001BF,
    0x001C0, 0x001C1, 0x001C2, 0x001C3, 0x001C6, 0x001C6, 0x001C6, 0x001C9,
    0x001C9, 0x001C9, 0x001CC, 0x001CC, 0x001CC, 0x001CE, 0x001CE, 0x001D0,
    0x001D0, 0x001D2, 0x001D2, 0x001D4, 0x001D4, 0x001D6, 0x001D6, 0x001D8,
    0x001D8, 0x001DA, 0x001DA, 0x001DC, 0x001DC, 0x001DD, 0x001DF, 0x001DF,
    0x001E1, 0x001E1, 0x001E3, 0x001E3, 0x001E5, 0x001E5, 0x001E7, 0x001E7,
    0x001E9, 0x001E9, 0x001EB, 0x001EB, 0x001ED, 0x001ED, 0x001EF, 0x001EF,
    0x001F0, 0x001F3, 0x001F3, 0x001F3, 0x001F5, 0x001F5, 0x001F6, 0x001F7,
    0x001F9, 0x001F9, 0x001FB, 0x001FB, 0x001FD, 0x001FD, 0x001FF, 0x001FF,
};


static const uint32_t  nxt_unicode_block_004[128]  nxt_aligned(64) = {
    0x00201, 0x00201, 0x00203, 0x00203, 0x00205, 0x00205, 0x00207, 0x00207,
    0x00209, 0x00209, 0x0020B, 0x0020B, 0x0020D, 0x0020D, 0x0020F, 0x0020F,
    0x00211, 0x00211, 0x00213, 0x00213, 0x00215, 0x00215, 0x00217, 0x00217,
    0x00219, 0x00219, 0x0021B, 0x0021B, 0x0021C, 0x0021D, 0x0021F, 0x0021F,
    0x00220, 0x00221, 0x00222, 0x00223, 0x00224, 0x00225, 0x00227, 0x00227,
    0x00229, 0x00229, 0x0022B, 0x0022B, 0x0022D, 0x0022D, 0x0022F, 0x0022F,
    0x00231, 0x00231, 0x00233, 0x00233, 0x00234, 0x00235, 0x00236, 0x00237,
    0x00238, 0x00239, 0x0023A, 0x0023B, 0x0023C, 0x0023D, 0x0023E, 0x0023F,
    0x00240, 0x00241, 0x00242, 0x00243, 0x00244, 0x00245, 0x00246, 0x00247,
    0x00248, 0x00249, 0x0024A, 0x0024B, 0x0024C, 0x0024D, 0x0024E, 0x0024F,
    0x00250, 0x00251, 0x00252, 0x00253, 0x00254, 0x00255, 0x00256, 0x00257,
    0x00258, 0x00259, 0x0025A, 0x0025B, 0x0025C, 0x0025D, 0x0025E, 0x0025F,
    0x00260, 0x00261, 0x00262, 0x00263, 0x00264, 0x00265, 0x00266, 0x00267,
    0x00268, 0x00269, 0x0026A, 0x0026B, 0x0026C, 0x0026D, 0x0026E, 0x0026F,
    0x00270, 0x00271, 0x00272, 0x00273, 0x00274, 0x00275, 0x00276, 0x00277,
    0x00278, 0x00279, 0x0027A, 0x0027B, 0x0027C, 0x0027D, 0x0027E, 0x0027F,
};


static const uint32_t  nxt_unicode_block_007[128]  nxt_aligned(64) = {
    0x00380, 0x00381, 0x00382, 0x00383, 0x00384, 0x00385, 0x003AC, 0x00387,
    0x003AD, 0x003AE, 0x003AF, 0x0038B, 0x003CC, 0x0038D, 0x003CD, 0x003CE,
    0x00390, 0x003B1, 0x003B2, 0x003B3, 0x003B4, 0x003B5, 0x003B6, 0x003B7,
    0x003B8, 0x003B9, 0x003BA, 0x003BB, 0x003BC, 0x003BD, 0x003BE, 0x003BF,
    0x003C0, 0x003C1, 0x003A2, 0x003C3, 0x003C4, 0x003C5, 0x003C6, 0x003C7,
    0x003C8, 0x003C9, 0x003CA, 0x003CB, 0x003AC, 0x003AD, 0x003AE, 0x003AF,
    0x003B0, 0x003B1, 0x003B2, 0x003B3, 0x003B4, 0x003B5, 0x003B6, 0x003B7,
    0x003B8, 0x003B9, 0x003BA, 0x003BB, 0x003BC, 0x003BD, 0x003BE, 0x003BF,
    0x003C0, 0x003C1, 0x003C2, 0x003C3, 0x003C4, 0x003C5, 0x003C6, 0x003C7,
    0x003C8, 0x003C9, 0x003CA, 0x003CB, 0x003CC, 0x003CD, 0x003CE, 0x003CF,
    0x003D0, 0x003D1, 0x003D2, 0x003D3, 0x003D4, 0x003D5, 0x003D6, 0x003D7,
    0x003D8, 0x003D9, 0x003DA, 0x003DB, 0x003DC, 0x003DD, 0x003DE, 0x003DF,
    0x003E0, 0x003E1, 0x003E3, 0x003E3, 0x003E5, 0x003E5, 0x003E7, 0x003E7,
    0x003E9, 0x003E9, 0x003EB, 0x003EB, 0x003ED, 0x003ED, 0x003EF, 0x003EF,
    0x003F0, 0x003F1, 0x003F2, 0x003F3, 0x003F4, 0x003F5, 0x003F6, 0x003F7,
    0x003F8, 0x003F9, 0x003FA, 0x003FB, 0x003FC, 0x003FD, 0x003FE, 0x003FF,
};


static const uint32_t  nxt_unicode_block_008[128]  nxt_aligned(64) = {
    0x00450, 0x00451, 0x00452, 0x00453, 0x00454, 0x00455, 0x00456, 0x00457,
    0x00458, 0x00459, 0x0045A, 0x0045B, 0x0045C, 0x0045D, 0x0045E, 0x0045F,
    0x00430, 0x00431, 0x00432, 0x00433, 0x00434, 0x00435, 0x00436, 0x00437,
    0x00438, 0x00439, 0x0043A, 0x0043B, 0x0043C, 0x0043D, 0x0043E, 0x0043F,
    0x00440, 0x00441, 0x00442, 0x00443, 0x00444, 0x00445, 0x00446, 0x00447,
    0x00448, 0x00449, 0x0044A, 0x0044B, 0x0044C, 0x0044D, 0x0044E, 0x0044F,
    0x00430, 0x00431, 0x00432, 0x00433, 0x00434, 0x00435, 0x00436, 0x00437,
    0x00438, 0x00439, 0x0043A, 0x0043B, 0x0043C, 0x0043D, 0x0043E, 0x0043F,
    0x00440, 0x00441, 0x00442, 0x00443, 0x00444, 0x00445, 0x00446, 0x00447,
    0x00448, 0x00449, 0x0044A, 0x0044B, 0x0044C, 0x0044D, 0x0044E, 0x0044F,
    0x00450, 0x00451, 0x00452, 0x00453, 0x00454, 0x00455, 0x00456, 0x00457,
    0x00458, 0x00459, 0x0045A, 0x0045B, 0x0045C, 0x0045D, 0x0045E, 0x0045F,
    0x00461, 0x00461, 0x00463, 0x00463, 0x00465, 0x00465, 0x00467, 0x00467,
    0x00469, 0x00469, 0x0046B, 0x0046B, 0x0046D, 0x0046D, 0x0046F, 0x0046F,
    0x00471, 0x00471, 0x00473, 0x00473, 0x00475, 0x00475, 0x00477, 0x00477,
    0x00479, 0x00479, 0x0047B, 0x0047B, 0x0047D, 0x0047D, 0x0047F, 0x0047F,
};


static const uint32_t  nxt_unicode_block_009[128]  nxt_aligned(64) = {
    0x00481, 0x00481, 0x00482, 0x00483, 0x00484, 0x00485, 0x00486, 0x00487,
    0x00488, 0x00489, 0x0048A, 0x0048B, 0x0048C, 0x0048D, 0x0048E, 0x0048F,
    0x00491, 0x00491, 0x00493, 0x00493, 0x00495, 0x00495, 0x00497, 0x00497,
    0x00499, 0x00499, 0x0049B, 0x0049B, 0x0049D, 0x0049D, 0x0049F, 0x0049F,
    0x004A1, 0x004A1, 0x004A3, 0x004A3, 0x004A5, 0x004A5, 0x004A7, 0x004A7,
    0x004A9, 0x004A9, 0x004AB, 0x004AB, 0x004AD, 0x004AD, 0x004AF, 0x004AF,
    0x004B1, 0x004B1, 0x004B3, 0x004B3, 0x004B5, 0x004B5, 0x004B7, 0x004B7,
    0x004B9, 0x004B9, 0x004BB, 0x004BB, 0x004BD, 0x004BD, 0x004BF, 0x004BF,
    0x004C0, 0x004C2, 0x004C2, 0x004C4, 0x004C4, 0x004C5, 0x004C6, 0x004C8,
    0x004C8, 0x004C9, 0x004CA, 0x004CC, 0x004CC, 0x004CD, 0x004CE, 0x004CF,
    0x004D1, 0x004D1, 0x004D3, 0x004D3, 0x004D4, 0x004D5, 0x004D7, 0x004D7,
    0x004D8, 0x004D9, 0x004DA, 0x004DB, 0x004DD, 0x004DD, 0x004DF, 0x004DF,
    0x004E0, 0x004E1, 0x004E3, 0x004E3, 0x004E5, 0x004E5, 0x004E7, 0x004E7,
    0x004E8, 0x004E9, 0x004EA, 0x004EB, 0x004ED, 0x004ED, 0x004EF, 0x004EF,
    0x004F1, 0x004F1, 0x004F3, 0x004F3, 0x004F5, 0x004F5, 0x004F6, 0x004F7,
    0x004F9, 0x004F9, 0x004FA, 0x004FB, 0x004FC, 0x004FD, 0x004FE, 0x004FF,
};


static const uint32_t  nxt_unicode_block_00a[128]  nxt_aligned(64) = {
    0x00500, 0x00501, 0x00502, 0x00503, 0x00504, 0x00505, 0x00506, 0x00507,
    0x00508, 0x00509, 0x0050A, 0x0050B, 0x0050C, 0x0050D, 0x0050E, 0x0050F,
    0x00510, 0x00511, 0x00512, 0x00513, 0x00514, 0x00515, 0x00516, 0x00517,
    0x00518, 0x00519, 0x0051A, 0x0051B, 0x0051C, 0x0051D, 0x0051E, 0x0051F,
    0x00520, 0x00521, 0x00522, 0x00523, 0x00524, 0x00525, 0x00526, 0x00527,
    0x00528, 0x00529, 0x0052A, 0x0052B, 0x0052C, 0x0052D, 0x0052E, 0x0052F,
    0x00530, 0x00561, 0x00562, 0x00563, 0x00564, 0x00565, 0x00566, 0x00567,
    0x00568, 0x00569, 0x0056A, 0x0056B, 0x0056C, 0x0056D, 0x0056E, 0x0056F,
    0x00570, 0x00571, 0x00572, 0x00573, 0x00574, 0x00575, 0x00576, 0x00577,
    0x00578, 0x00579, 0x0057A, 0x0057B, 0x0057C, 0x0057D, 0x0057E, 0x0057F,
    0x00580, 0x00581, 0x00582, 0x00583, 0x00584, 0x00585, 0x00586, 0x00557,
    0x00558, 0x00559, 0x0055A, 0x0055B, 0x0055C, 0x0055D, 0x0055E, 0x0055F,
    0x00560, 0x00561, 0x00562, 0x00563, 0x00564, 0x00565, 0x00566, 0x00567,
    0x00568, 0x00569, 0x0056A, 0x0056B, 0x0056C, 0x0056D, 0x0056E, 0x0056F,
    0x00570, 0x00571, 0x00572, 0x00573, 0x00574, 0x00575, 0x00576, 0x00577,
    0x00578, 0x00579, 0x0057A, 0x0057B, 0x0057C, 0x0057D, 0x0057E, 0x0057F,
};


static const uint32_t  nxt_unicode_block_03c[128]  nxt_aligned(64) = {
    0x01E01, 0x01E01, 0x01E03, 0x01E03, 0x01E05, 0x01E05, 0x01E07, 0x01E07,
    0x01E09, 0x01E09, 0x01E0B, 0x01E0B, 0x01E0D, 0x01E0D, 0x01E0F, 0x01E0F,
    0x01E11, 0x01E11, 0x01E13, 0x01E13, 0x01E15, 0x01E15, 0x01E17, 0x01E17,
    0x01E19, 0x01E19, 0x01E1B, 0x01E1B, 0x01E1D, 0x01E1D, 0x01E1F, 0x01E1F,
    0x01E21, 0x01E21, 0x01E23, 0x01E23, 0x01E25, 0x01E25, 0x01E27, 0x01E27,
    0x01E29, 0x01E29, 0x01E2B, 0x01E2B, 0x01E2D, 0x01E2D, 0x01E2F, 0x01E2F,
    0x01E31, 0x01E31, 0x01E33, 0x01E33, 0x01E35, 0x01E35, 0x01E37, 0x01E37,
    0x01E39, 0x01E39, 0x01E3B, 0x01E3B, 0x01E3D, 0x01E3D, 0x01E3F, 0x01E3F,
    0x01E41, 0x01E41, 0x01E43, 0x01E43, 0x01E45, 0x01E45, 0x01E47, 0x01E47,
    0x01E49, 0x01E49, 0x01E4B, 0x01E4B, 0x01E4D, 0x01E4D, 0x01E4F, 0x01E4F,
    0x01E51, 0x01E51, 0x01E53, 0x01E53, 0x01E55, 0x01E55, 0x01E57, 0x01E57,
    0x01E59, 0x01E59, 0x01E5B, 0x01E5B, 0x01E5D, 0x01E5D, 0x01E5F, 0x01E5F,
    0x01E61, 0x01E61, 0x01E63, 0x01E63, 0x01E65, 0x01E65, 0x01E67, 0x01E67,
    0x01E69, 0x01E69, 0x01E6B, 0x01E6B, 0x01E6D, 0x01E6D, 0x01E6F, 0x01E6F,
    0x01E71, 0x01E71, 0x01E73, 0x01E73, 0x01E75, 0x01E75, 0x01E77, 0x01E77,
    0x01E79, 0x01E79, 0x01E7B, 0x01E7B, 0x01E7D, 0x01E7D, 0x01E7F, 0x01E7F,
};


static const uint32_t  nxt_unicode_block_03d[128]  nxt_aligned(64) = {
    0x01E81, 0x01E81, 0x01E83, 0x01E83, 0x01E85, 0x01E85, 0x01E87, 0x01E87,
    0x01E89, 0x01E89, 0x01E8B, 0x01E8B, 0x01E8D, 0x01E8D, 0x01E8F, 0x01E8F,
    0x01E91, 0x01E91, 0x01E93, 0x01E93, 0x01E95, 0x01E95, 0x01E96, 0x01E97,
    0x01E98, 0x01E99, 0x01E9A, 0x01E9B, 0x01E9C, 0x01E9D, 0x01E9E, 0x01E9F,
    0x01EA1, 0x01EA1, 0x01EA3, 0x01EA3, 0x01EA5, 0x01EA5, 0x01EA7, 0x01EA7,
    0x01EA9, 0x01EA9, 0x01EAB, 0x01EAB, 0x01EAD, 0x01EAD, 0x01EAF, 0x01EAF,
    0x01EB1, 0x01EB1, 0x01EB3, 0x01EB3, 0x01EB5, 0x01EB5, 0x01EB7, 0x01EB7,
    0x01EB9, 0x01EB9, 0x01EBB, 0x01EBB, 0x01EBD, 0x01EBD, 0x01EBF, 0x01EBF,
    0x01EC1, 0x01EC1, 0x01EC3, 0x01EC3, 0x01EC5, 0x01EC5, 0x01EC7, 0x01EC7,
    0x01EC9, 0x01EC9, 0x01ECB, 0x01ECB, 0x01ECD, 0x01ECD, 0x01ECF, 0x01ECF,
    0x01ED1, 0x01ED1, 0x01ED3, 0x01ED3, 0x01ED5, 0x01ED5, 0x01ED7, 0x01ED7,
    0x01ED9, 0x01ED9, 0x01EDB, 0x01EDB, 0x01EDD, 0x01EDD, 0x01EDF, 0x01EDF,
    0x01EE1, 0x01EE1, 0x01EE3, 0x01EE3, 0x01EE5, 0x01EE5, 0x01EE7, 0x01EE7,
    0x01EE9, 0x01EE9, 0x01EEB, 0x01EEB, 0x01EED, 0x01EED, 0x01EEF, 0x01EEF,
    0x01EF1, 0x01EF1, 0x01EF3, 0x01EF3, 0x01EF5, 0x01EF5, 0x01EF7, 0x01EF7,
    0x01EF9, 0x01EF9, 0x01EFA, 0x01EFB, 0x01EFC, 0x01EFD, 0x01EFE, 0x01EFF,
};


static const uint32_t  nxt_unicode_block_03e[128]  nxt_aligned(64) = {
    0x01F00, 0x01F01, 0x01F02, 0x01F03, 0x01F04, 0x01F05, 0x01F06, 0x01F07,
    0x01F00, 0x01F01, 0x01F02, 0x01F03, 0x01F04, 0x01F05, 0x01F06, 0x01F07,
    0x01F10, 0x01F11, 0x01F12, 0x01F13, 0x01F14, 0x01F15, 0x01F16, 0x01F17,
    0x01F10, 0x01F11, 0x01F12, 0x01F13, 0x01F14, 0x01F15, 0x01F1E, 0x01F1F,
    0x01F20, 0x01F21, 0x01F22, 0x01F23, 0x01F24, 0x01F25, 0x01F26, 0x01F27,
    0x01F20, 0x01F21, 0x01F22, 0x01F23, 0x01F24, 0x01F25, 0x01F26, 0x01F27,
    0x01F30, 0x01F31, 0x01F32, 0x01F33, 0x01F34, 0x01F35, 0x01F36, 0x01F37,
    0x01F30, 0x01F31, 0x01F32, 0x01F33, 0x01F34, 0x01F35, 0x01F36, 0x01F37,
    0x01F40, 0x01F41, 0x01F42, 0x01F43, 0x01F44, 0x01F45, 0x01F46, 0x01F47,
    0x01F40, 0x01F41, 0x01F42, 0x01F43, 0x01F44, 0x01F45, 0x01F4E, 0x01F4F,
    0x01F50, 0x01F51, 0x01F52, 0x01F53, 0x01F54, 0x01F55, 0x01F56, 0x01F57,
    0x01F58, 0x01F51, 0x01F5A, 0x01F53, 0x01F5C, 0x01F55, 0x01F5E, 0x01F57,
    0x01F60, 0x01F61, 0x01F62, 0x01F63, 0x01F64, 0x01F65, 0x01F66, 0x01F67,
    0x01F60, 0x01F61, 0x01F62, 0x01F63, 0x01F64, 0x01F65, 0x01F66, 0x01F67,
    0x01F70, 0x01F71, 0x01F72, 0x01F73, 0x01F74, 0x01F75, 0x01F76, 0x01F77,
    0x01F78, 0x01F79, 0x01F7A, 0x01F7B, 0x01F7C, 0x01F7D, 0x01F7E, 0x01F7F,
};


static const uint32_t  nxt_unicode_block_03f[128]  nxt_aligned(64) = {
    0x01F80, 0x01F81, 0x01F82, 0x01F83, 0x01F84, 0x01F85, 0x01F86, 0x01F87,
    0x01F80, 0x01F81, 0x01F82, 0x01F83, 0x01F84, 0x01F85, 0x01F86, 0x01F87,
    0x01F90, 0x01F91, 0x01F92, 0x01F93, 0x01F94, 0x01F95, 0x01F96, 0x01F97,
    0x01F90, 0x01F91, 0x01F92, 0x01F93, 0x01F94, 0x01F95, 0x01F96, 0x01F97,
    0x01FA0, 0x01FA1, 0x01FA2, 0x01FA3, 0x01FA4, 0x01FA5, 0x01FA6, 0x01FA7,
    0x01FA0, 0x01FA1, 0x01FA2, 0x01FA3, 0x01FA4, 0x01FA5, 0x01FA6, 0x01FA7,
    0x01FB0, 0x01FB1, 0x01FB2, 0x01FB3, 0x01FB4, 0x01FB5, 0x01FB6, 0x01FB7,
    0x01FB0, 0x01FB1, 0x01F70, 0x01F71, 0x01FB3, 0x01FBD, 0x003B9, 0x01FBF,
    0x01FC0, 0x01FC1, 0x01FC2, 0x01FC3, 0x01FC4, 0x01FC5, 0x01FC6, 0x01FC7,
    0x01F72, 0x01F73, 0x01F74, 0x01F75, 0x01FC3, 0x01FCD, 0x01FCE, 0x01FCF,
    0x01FD0, 0x01FD1, 0x01FD2, 0x01FD3, 0x01FD4, 0x01FD5, 0x01FD6, 0x01FD7,
    0x01FD0, 0x01FD1, 0x01F76, 0x01F77, 0x01FDC, 0x01FDD, 0x01FDE, 0x01FDF,
    0x01FE0, 0x01FE1, 0x01FE2, 0x01FE3, 0x01FE4, 0x01FE5, 0x01FE6, 0x01FE7,
    0x01FE0, 0x01FE1, 0x01F7A, 0x01F7B, 0x01FE5, 0x01FED, 0x01FEE, 0x01FEF,
    0x01FF0, 0x01FF1, 0x01FF2, 0x01FF3, 0x01FF4, 0x01FF5, 0x01FF6, 0x01FF7,
    0x01F78, 0x01F79, 0x01F7C, 0x01F7D, 0x01FF3, 0x01FFD, 0x01FFE, 0x01FFF,
};


static const uint32_t  nxt_unicode_block_042[128]  nxt_aligned(64) = {
    0x02100, 0x02101, 0x02102, 0x02103, 0x02104, 0x02105, 0x02106, 0x02107,
    0x02108, 0x02109, 0x0210A, 0x0210B, 0x0210C, 0x0210D, 0x0210E, 0x0210F,
    0x02110, 0x02111, 0x02112, 0x02113, 0x02114, 0x02115, 0x02116, 0x02117,
    0x02118, 0x02119, 0x0211A, 0x0211B, 0x0211C, 0x0211D, 0x0211E, 0x0211F,
    0x02120, 0x02121, 0x02122, 0x02123, 0x02124, 0x02125, 0x02126, 0x02127,
    0x02128, 0x02129, 0x0212A, 0x0212B, 0x0212C, 0x0212D, 0x0212E, 0x0212F,
    0x02130, 0x02131, 0x02132, 0x02133, 0x02134, 0x02135, 0x02136, 0x02137,
    0x02138, 0x02139, 0x0213A, 0x0213B, 0x0213C, 0x0213D, 0x0213E, 0x0213F,
    0x02140, 0x02141, 0x02142, 0x02143, 0x02144, 0x02145, 0x02146, 0x02147,
    0x02148, 0x02149, 0x0214A, 0x0214B, 0x0214C, 0x0214D, 0x0214E, 0x0214F,
    0x02150, 0x02151, 0x02152, 0x02153, 0x02154, 0x02155, 0x02156, 0x02157,
    0x02158, 0x02159, 0x0215A, 0x0215B, 0x0215C, 0x0215D, 0x0215E, 0x0215F,
    0x02170, 0x02171, 0x02172, 0x02173, 0x02174, 0x02175, 0x02176, 0x02177,
    0x02178, 0x02179, 0x0217A, 0x0217B, 0x0217C, 0x0217D, 0x0217E, 0x0217F,
    0x02170, 0x02171, 0x02172, 0x02173, 0x02174, 0x02175, 0x02176, 0x02177,
    0x02178, 0x02179, 0x0217A, 0x0217B, 0x0217C, 0x0217D, 0x0217E, 0x0217F,
};


static const uint32_t  nxt_unicode_block_1fe[59]  nxt_aligned(64) = {
    0x0FF00, 0x0FF01, 0x0FF02, 0x0FF03, 0x0FF04, 0x0FF05, 0x0FF06, 0x0FF07,
    0x0FF08, 0x0FF09, 0x0FF0A, 0x0FF0B, 0x0FF0C, 0x0FF0D, 0x0FF0E, 0x0FF0F,
    0x0FF10, 0x0FF11, 0x0FF12, 0x0FF13, 0x0FF14, 0x0FF15, 0x0FF16, 0x0FF17,
    0x0FF18, 0x0FF19, 0x0FF1A, 0x0FF1B, 0x0FF1C, 0x0FF1D, 0x0FF1E, 0x0FF1F,
    0x0FF20, 0x0FF41, 0x0FF42, 0x0FF43, 0x0FF44, 0x0FF45, 0x0FF46, 0x0FF47,
    0x0FF48, 0x0FF49, 0x0FF4A, 0x0FF4B, 0x0FF4C, 0x0FF4D, 0x0FF4E, 0x0FF4F,
    0x0FF50, 0x0FF51, 0x0FF52, 0x0FF53, 0x0FF54, 0x0FF55, 0x0FF56, 0x0FF57,
    0x0FF58, 0x0FF59, 0x0FF5A,
};


static const uint32_t  *nxt_unicode_blocks[]  nxt_aligned(64) = {
    nxt_unicode_block_000,
    nxt_unicode_block_001,
    nxt_unicode_block_002,
    nxt_unicode_block_003,
    nxt_unicode_block_004,
    NULL,
    NULL,
    nxt_unicode_block_007,
    nxt_unicode_block_008,
    nxt_unicode_block_009,
    nxt_unicode_block_00a,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    nxt_unicode_block_03c,
    nxt_unicode_block_03d,
    nxt_unicode_block_03e,
    nxt_unicode_block_03f,
    NULL,
    NULL,
    nxt_unicode_block_042,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    nxt_unicode_block_1fe,
};
