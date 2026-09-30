/*
 * m504dll input.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/input.s.
 */

#include "REL/m504dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* forward declarations: nodes point at later nodes */
extern M504_PATH1 lbl_1_data_528;
extern M504_PATH1 lbl_1_data_538;
extern M504_PATH2 lbl_1_data_548;
extern M504_PATH1 lbl_1_data_564;
extern M504_PATH1 lbl_1_data_574;
extern M504_PATH1 lbl_1_data_584;
extern M504_PATH1 lbl_1_data_594;
extern M504_PATH1 lbl_1_data_5A4;
extern M504_PATH1 lbl_1_data_5B4;
extern M504_PATH1 lbl_1_data_5C4;
extern M504_PATH1 lbl_1_data_5D4;
extern M504_PATH1 lbl_1_data_5E4;
extern M504_PATH1 lbl_1_data_5F4;
extern M504_PATH1 lbl_1_data_604;
extern M504_PATH1 lbl_1_data_614;
extern M504_PATH1 lbl_1_data_624;
extern M504_PATH1 lbl_1_data_634;
extern M504_PATH1 lbl_1_data_644;
extern M504_PATH2 lbl_1_data_654;
extern M504_PATH1 lbl_1_data_670;
extern M504_PATH3 lbl_1_data_680;
extern M504_PATH1 lbl_1_data_6A8;
extern M504_PATH1 lbl_1_data_6B8;
extern M504_PATH1 lbl_1_data_6C8;
extern M504_PATH3 lbl_1_data_6D8;
extern M504_PATH1 lbl_1_data_700;
extern M504_PATH1 lbl_1_data_710;
extern M504_PATH1 lbl_1_data_720;
extern M504_PATH1 lbl_1_data_730;
extern M504_PATH1 lbl_1_data_740;
extern M504_PATH1 lbl_1_data_750;
extern M504_PATH1 lbl_1_data_760;
extern M504_PATH1 lbl_1_data_770;
extern M504_PATH1 lbl_1_data_780;
extern M504_PATH1 lbl_1_data_790;
extern M504_PATH1 lbl_1_data_7A0;
extern M504_PATH2 lbl_1_data_7B0;
extern M504_PATH1 lbl_1_data_7CC;
extern M504_PATH1 lbl_1_data_7DC;
extern M504_PATH1 lbl_1_data_7EC;
extern M504_PATH1 lbl_1_data_7FC;
extern M504_PATH1 lbl_1_data_80C;
extern M504_PATH2 lbl_1_data_81C;
extern M504_PATH1 lbl_1_data_838;
extern M504_PATH1 lbl_1_data_848;
extern M504_PATH1 lbl_1_data_858;
extern M504_PATH3 lbl_1_data_868;
extern M504_PATH1 lbl_1_data_890;
extern M504_PATH1 lbl_1_data_8A0;
extern M504_PATH1 lbl_1_data_8B0;
extern M504_PATH1 lbl_1_data_8C0;
extern M504_PATH1 lbl_1_data_8D0;
extern M504_PATH1 lbl_1_data_8E0;
extern M504_PATH1 lbl_1_data_8F0;
extern M504_PATH2 lbl_1_data_900;
extern M504_PATH1 lbl_1_data_91C;
extern M504_PATH1 lbl_1_data_92C;
extern M504_PATH1 lbl_1_data_93C;
extern M504_PATH1 lbl_1_data_94C;
extern M504_PATH1 lbl_1_data_95C;
extern M504_PATH1 lbl_1_data_96C;
extern M504_PATH1 lbl_1_data_97C;
extern M504_PATH1 lbl_1_data_98C;
extern M504_PATH1 lbl_1_data_99C;
extern M504_PATH1 lbl_1_data_9AC;
extern M504_PATH1 lbl_1_data_9BC;
extern M504_PATH1 lbl_1_data_9CC;
extern M504_PATH1 lbl_1_data_9DC;
extern M504_PATH1 lbl_1_data_9EC;
extern M504_PATH1 lbl_1_data_9FC;
extern M504_PATH1 lbl_1_data_A0C;
extern M504_PATH1 lbl_1_data_A1C;
extern M504_PATH2 lbl_1_data_A2C;
extern M504_PATH1 lbl_1_data_A48;
extern M504_PATH1 lbl_1_data_A58;
extern M504_PATH1 lbl_1_data_A68;
extern M504_PATH1 lbl_1_data_A78;
extern M504_PATH1 lbl_1_data_A88;
extern M504_PATH3 lbl_1_data_A98;
extern M504_PATH1 lbl_1_data_AC0;
extern M504_PATH1 lbl_1_data_AD0;
extern M504_PATH1 lbl_1_data_AE0;
extern M504_PATH1 lbl_1_data_AF0;
extern M504_PATH1 lbl_1_data_B00;
extern M504_PATH1 lbl_1_data_B10;
extern M504_PATH1 lbl_1_data_B20;
extern M504_PATH1 lbl_1_data_B30;
extern M504_PATH1 lbl_1_data_B40;
extern M504_PATH3 lbl_1_data_B50;
extern M504_PATH1 lbl_1_data_B78;
extern M504_PATH1 lbl_1_data_B88;
extern M504_PATH1 lbl_1_data_B98;
extern M504_PATH2 lbl_1_data_BA8;
extern M504_PATH1 lbl_1_data_BC4;
extern M504_PATH1 lbl_1_data_BD4;
extern M504_PATH1 lbl_1_data_BE4;
extern M504_PATH1 lbl_1_data_BF4;
extern M504_PATH1 lbl_1_data_C04;
extern M504_PATH1 lbl_1_data_C14;
extern M504_PATH1 lbl_1_data_C24;
extern M504_PATH1 lbl_1_data_C34;
extern M504_PATH1 lbl_1_data_C44;
extern M504_PATH1 lbl_1_data_C54;
extern M504_PATH1 lbl_1_data_C64;
extern M504_PATH2 lbl_1_data_C74;
extern M504_PATH1 lbl_1_data_C90;
extern M504_PATH1 lbl_1_data_CA0;
extern M504_PATH1 lbl_1_data_CB0;
extern M504_PATH1 lbl_1_data_CC0;
extern M504_PATH1 lbl_1_data_CD0;
extern M504_PATH1 lbl_1_data_CE0;
extern M504_PATH1 lbl_1_data_CF0;
extern M504_PATH1 lbl_1_data_D00;
extern M504_PATH1 lbl_1_data_D10;
extern M504_PATH1 lbl_1_data_D20;
extern M504_PATH1 lbl_1_data_D30;
extern M504_PATH1 lbl_1_data_D40;
extern M504_PATH1 lbl_1_data_D50;
extern M504_PATH1 lbl_1_data_D60;
extern M504_PATH1 lbl_1_data_D70;
extern M504_PATH1 lbl_1_data_D80;
extern M504_PATH1 lbl_1_data_D90;
extern M504_PATH1 lbl_1_data_DA0;
extern M504_PATH1 lbl_1_data_DB0;
extern M504_PATH1 lbl_1_data_DC0;
extern M504_PATH1 lbl_1_data_DD0;
extern M504_PATH1 lbl_1_data_DE0;
extern M504_PATH1 lbl_1_data_DF0;
extern M504_PATH2 lbl_1_data_E00;
extern M504_PATH1 lbl_1_data_E1C;
extern M504_PATH1 lbl_1_data_E2C;
extern M504_PATH1 lbl_1_data_E3C;
extern M504_PATH3 lbl_1_data_E4C;
extern M504_PATH1 lbl_1_data_E74;
extern M504_PATH1 lbl_1_data_E84;
extern M504_PATH1 lbl_1_data_E94;
extern M504_PATH1 lbl_1_data_EA4;
extern M504_PATH1 lbl_1_data_EB4;
extern M504_PATH1 lbl_1_data_EC4;
extern M504_PATH1 lbl_1_data_ED4;
extern M504_PATH1 lbl_1_data_EE4;
extern M504_PATH1 lbl_1_data_EF4;
extern M504_PATH1 lbl_1_data_F04;
extern M504_PATH1 lbl_1_data_F14;
extern M504_PATH1 lbl_1_data_F24;
extern M504_PATH1 lbl_1_data_F34;
extern M504_PATH1 lbl_1_data_F44;
extern M504_PATH1 lbl_1_data_F54;
extern M504_PATH1 lbl_1_data_F64;
extern M504_PATH1 lbl_1_data_F74;
extern M504_PATH1 lbl_1_data_F84;
extern M504_PATH1 lbl_1_data_F94;
extern M504_PATH1 lbl_1_data_FA4;
extern M504_PATH1 lbl_1_data_FB4;
extern M504_PATH1 lbl_1_data_FC4;
extern M504_PATH1 lbl_1_data_FD4;
extern M504_PATH1 lbl_1_data_FE4;
extern M504_PATH1 lbl_1_data_FF4;
extern M504_PATH1 lbl_1_data_1004;
extern M504_PATH1 lbl_1_data_1014;
extern M504_PATH1 lbl_1_data_1024;
extern M504_PATH2 lbl_1_data_1034;
extern M504_PATH3 lbl_1_data_1050;
extern M504_PATH1 lbl_1_data_1078;
extern M504_PATH1 lbl_1_data_1088;
extern M504_PATH1 lbl_1_data_1098;
extern M504_PATH1 lbl_1_data_10A8;
extern M504_PATH1 lbl_1_data_10B8;
extern M504_PATH1 lbl_1_data_10C8;
extern M504_PATH1 lbl_1_data_10D8;
extern M504_PATH1 lbl_1_data_10E8;
extern M504_PATH1 lbl_1_data_10F8;
extern M504_PATH1 lbl_1_data_1108;
extern M504_PATH1 lbl_1_data_1118;
extern M504_PATH1 lbl_1_data_1128;
extern M504_PATH1 lbl_1_data_1138;
extern M504_PATH4 lbl_1_data_1148;
extern M504_PATH1 lbl_1_data_117C;
extern M504_PATH1 lbl_1_data_118C;
extern M504_PATH1 lbl_1_data_119C;
extern M504_PATH1 lbl_1_data_11AC;
extern M504_PATH1 lbl_1_data_11BC;
extern M504_PATH1 lbl_1_data_11CC;
extern M504_PATH1 lbl_1_data_11DC;
extern M504_PATH1 lbl_1_data_11EC;
extern M504_PATH1 lbl_1_data_11FC;
extern M504_PATH1 lbl_1_data_120C;
extern M504_PATH1 lbl_1_data_121C;
extern M504_PATH1 lbl_1_data_122C;
extern M504_PATH1 lbl_1_data_123C;
extern M504_PATH1 lbl_1_data_124C;
extern M504_PATH1 lbl_1_data_125C;
extern M504_PATH4 lbl_1_data_126C;
extern M504_PATH1 lbl_1_data_12A0;
extern M504_PATH1 lbl_1_data_12B0;
extern M504_PATH1 lbl_1_data_12C0;
extern M504_PATH1 lbl_1_data_12D0;
extern M504_PATH1 lbl_1_data_12E0;
extern M504_PATH1 lbl_1_data_12F0;
extern M504_PATH1 lbl_1_data_1300;
extern M504_PATH5 lbl_1_data_1310;
extern M504_PATH1 lbl_1_data_1350;
extern M504_PATH1 lbl_1_data_1360;
extern M504_PATH1 lbl_1_data_1370;
extern M504_PATH1 lbl_1_data_1380;
extern M504_PATH1 lbl_1_data_1390;
extern M504_PATH1 lbl_1_data_13A0;
extern M504_PATH1 lbl_1_data_13B0;
extern M504_PATH1 lbl_1_data_13C0;
extern M504_PATH1 lbl_1_data_13D0;
extern M504_PATH1 lbl_1_data_13E0;
extern M504_PATH1 lbl_1_data_13F0;
extern M504_PATH3 lbl_1_data_1400;
extern M504_PATH1 lbl_1_data_1428;
extern M504_PATH1 lbl_1_data_1438;
extern M504_PATH1 lbl_1_data_1448;
extern M504_PATH1 lbl_1_data_1458;
extern M504_PATH1 lbl_1_data_1468;
extern M504_PATH1 lbl_1_data_1478;
extern M504_PATH1 lbl_1_data_1488;
extern M504_PATH1 lbl_1_data_1498;
extern M504_PATH1 lbl_1_data_14A8;
extern M504_PATH1 lbl_1_data_14B8;
extern M504_PATH1 lbl_1_data_14C8;
extern M504_PATH1 lbl_1_data_14D8;
extern M504_PATH1 lbl_1_data_14E8;
extern M504_PATH3 lbl_1_data_14F8;
extern M504_PATH1 lbl_1_data_1520;
extern M504_PATH1 lbl_1_data_1530;
extern M504_PATH1 lbl_1_data_1540;
extern M504_PATH1 lbl_1_data_1550;
extern M504_PATH1 lbl_1_data_1560;
extern M504_PATH1 lbl_1_data_1570;
extern M504_PATH1 lbl_1_data_1580;
extern M504_PATH1 lbl_1_data_1590;
extern M504_PATH1 lbl_1_data_15A0;
extern M504_PATH1 lbl_1_data_15B0;
extern M504_PATH1 lbl_1_data_15C0;
extern M504_PATH1 lbl_1_data_15D0;
extern M504_PATH1 lbl_1_data_15E0;
extern M504_PATH1 lbl_1_data_15F0;
extern M504_PATH1 lbl_1_data_1600;
extern M504_PATH1 lbl_1_data_1610;
extern M504_PATH1 lbl_1_data_1620;
extern M504_PATH1 lbl_1_data_1630;
extern M504_PATH1 lbl_1_data_1640;
extern M504_PATH2 lbl_1_data_1650;
extern M504_PATH1 lbl_1_data_166C;
extern M504_PATH2 lbl_1_data_167C;
extern M504_PATH1 lbl_1_data_1698;
extern M504_PATH1 lbl_1_data_16A8;
extern M504_PATH1 lbl_1_data_16B8;
extern M504_PATH1 lbl_1_data_16C8;
extern M504_PATH1 lbl_1_data_16D8;
extern M504_PATH1 lbl_1_data_16E8;
extern M504_PATH1 lbl_1_data_16F8;
extern M504_PATH1 lbl_1_data_1708;
extern M504_PATH1 lbl_1_data_1718;
extern M504_PATH1 lbl_1_data_1728;
extern M504_PATH1 lbl_1_data_1738;
extern M504_PATH1 lbl_1_data_1748;
extern M504_PATH1 lbl_1_data_1758;
extern M504_PATH1 lbl_1_data_1768;
extern M504_PATH1 lbl_1_data_1778;
extern M504_PATH2 lbl_1_data_1788;
extern M504_PATH1 lbl_1_data_17A4;
extern M504_PATH1 lbl_1_data_17B4;
extern M504_PATH1 lbl_1_data_17C4;
extern M504_PATH1 lbl_1_data_17D4;
extern M504_PATH1 lbl_1_data_17E4;
extern M504_PATH1 lbl_1_data_17F4;
extern M504_PATH1 lbl_1_data_1804;
extern M504_PATH1 lbl_1_data_1814;
extern M504_PATH1 lbl_1_data_1824;
extern M504_PATH1 lbl_1_data_1834;
extern M504_PATH1 lbl_1_data_1844;
extern M504_PATH1 lbl_1_data_1854;
extern M504_PATH1 lbl_1_data_1864;
extern M504_PATH1 lbl_1_data_1874;
extern M504_PATH1 lbl_1_data_1884;
extern M504_PATH1 lbl_1_data_1894;
extern M504_PATH1 lbl_1_data_18A4;
extern M504_PATH1 lbl_1_data_18B4;
extern M504_PATH1 lbl_1_data_18C4;
extern M504_PATH1 lbl_1_data_18D4;
extern M504_PATH1 lbl_1_data_18E4;
extern M504_PATH1 lbl_1_data_18F4;
extern M504_PATH1 lbl_1_data_1904;
extern M504_PATH1 lbl_1_data_1914;
extern M504_PATH1 lbl_1_data_1924;
extern M504_PATH1 lbl_1_data_1934;
extern M504_PATH1 lbl_1_data_1944;
extern M504_PATH1 lbl_1_data_1954;
extern M504_PATH1 lbl_1_data_1964;
extern M504_PATH1 lbl_1_data_1974;
extern M504_PATH1 lbl_1_data_1984;
extern M504_PATH2 lbl_1_data_1994;
extern M504_PATH1 lbl_1_data_19B0;
extern M504_PATH1 lbl_1_data_19C0;
extern M504_PATH1 lbl_1_data_19D0;
extern M504_PATH1 lbl_1_data_19E0;
extern M504_PATH1 lbl_1_data_19F0;
extern M504_PATH1 lbl_1_data_1A00;
extern M504_PATH1 lbl_1_data_1A10;
extern M504_PATH6 lbl_1_data_1A20;
extern M504_PATH1 lbl_1_data_1A6C;
extern M504_PATH1 lbl_1_data_1A7C;
extern M504_PATH1 lbl_1_data_1A8C;
extern M504_PATH1 lbl_1_data_1A9C;
extern M504_PATH1 lbl_1_data_1AAC;
extern M504_PATH1 lbl_1_data_1ABC;
extern M504_PATH1 lbl_1_data_1ACC;
extern M504_PATH1 lbl_1_data_1ADC;
extern M504_PATH1 lbl_1_data_1AEC;
extern M504_PATH1 lbl_1_data_1AFC;
extern M504_PATH1 lbl_1_data_1B0C;
extern M504_PATH1 lbl_1_data_1B1C;
extern M504_PATH1 lbl_1_data_1B2C;
extern M504_PATH1 lbl_1_data_1B3C;
extern M504_PATH1 lbl_1_data_1B4C;
extern M504_PATH3 lbl_1_data_1B5C;
extern M504_PATH1 lbl_1_data_1B84;
extern M504_PATH1 lbl_1_data_1B94;
extern M504_PATH1 lbl_1_data_1BA4;
extern M504_PATH1 lbl_1_data_1BB4;
extern M504_PATH1 lbl_1_data_1BC4;
extern M504_PATH1 lbl_1_data_1BD4;
extern M504_PATH1 lbl_1_data_1BE4;
extern M504_PATH3 lbl_1_data_1BF4;
extern M504_PATH1 lbl_1_data_1C1C;
extern M504_PATH1 lbl_1_data_1C2C;
extern M504_PATH1 lbl_1_data_1C3C;
extern M504_PATH1 lbl_1_data_1C4C;
extern M504_PATH1 lbl_1_data_1C5C;
extern M504_PATH1 lbl_1_data_1C6C;
extern M504_PATH1 lbl_1_data_1C7C;
extern M504_PATH1 lbl_1_data_1C8C;
extern M504_PATH1 lbl_1_data_1C9C;
extern M504_PATH1 lbl_1_data_1CAC;
extern M504_PATH1 lbl_1_data_1CBC;
extern M504_PATH1 lbl_1_data_1CCC;
extern M504_PATH1 lbl_1_data_1CDC;
extern M504_PATH1 lbl_1_data_1CEC;
extern M504_PATH1 lbl_1_data_1CFC;
extern M504_PATH4 lbl_1_data_1D0C;
extern M504_PATH1 lbl_1_data_1D40;
extern M504_PATH2 lbl_1_data_1D50;
extern M504_PATH1 lbl_1_data_1D6C;
extern M504_PATH1 lbl_1_data_1D7C;
extern M504_PATH1 lbl_1_data_1D8C;
extern M504_PATH2 lbl_1_data_1D9C;
extern M504_PATH1 lbl_1_data_1DB8;
extern M504_PATH1 lbl_1_data_1DC8;
extern M504_PATH1 lbl_1_data_1DD8;
extern M504_PATH1 lbl_1_data_1DE8;
extern M504_PATH1 lbl_1_data_1DF8;
extern M504_PATH1 lbl_1_data_1E08;
extern M504_PATH1 lbl_1_data_1E18;
extern M504_PATH1 lbl_1_data_1E28;
extern M504_PATH1 lbl_1_data_1E38;
extern M504_PATH1 lbl_1_data_1E48;
extern M504_PATH1 lbl_1_data_1E58;
extern M504_PATH1 lbl_1_data_1E68;
extern M504_PATH1 lbl_1_data_1E78;
extern M504_PATH1 lbl_1_data_1E88;
extern M504_PATH1 lbl_1_data_1E98;
extern M504_PATH1 lbl_1_data_1EA8;
extern M504_PATH1 lbl_1_data_1EB8;
extern M504_PATH3 lbl_1_data_1EC8;
extern M504_PATH1 lbl_1_data_1EF0;
extern M504_PATH1 lbl_1_data_1F00;
extern M504_PATH1 lbl_1_data_1F10;
extern M504_PATH1 lbl_1_data_1F20;
extern M504_PATH1 lbl_1_data_1F30;
extern M504_PATH1 lbl_1_data_1F40;
extern M504_PATH1 lbl_1_data_1F50;
extern M504_PATH1 lbl_1_data_1F60;
extern M504_PATH1 lbl_1_data_1F70;
extern M504_PATH1 lbl_1_data_1F80;
extern M504_PATH1 lbl_1_data_1F90;
extern M504_PATH1 lbl_1_data_1FA0;
extern M504_PATH1 lbl_1_data_1FB0;
extern M504_PATH2 lbl_1_data_1FC0;
extern M504_PATH1 lbl_1_data_1FDC;
extern M504_PATH1 lbl_1_data_1FEC;
extern M504_PATH1 lbl_1_data_1FFC;
extern M504_PATH1 lbl_1_data_200C;
extern M504_PATH1 lbl_1_data_201C;
extern M504_PATH1 lbl_1_data_202C;
extern M504_PATH1 lbl_1_data_203C;
extern M504_PATH1 lbl_1_data_204C;
extern M504_PATH1 lbl_1_data_205C;
extern M504_PATH2 lbl_1_data_206C;
extern M504_PATH1 lbl_1_data_2088;
extern M504_PATH1 lbl_1_data_2098;
extern M504_PATH1 lbl_1_data_20A8;
extern M504_PATH1 lbl_1_data_20B8;
extern M504_PATH1 lbl_1_data_20C8;
extern M504_PATH1 lbl_1_data_20D8;
extern M504_PATH1 lbl_1_data_20E8;
extern M504_PATH5 lbl_1_data_20F8;
extern M504_PATH1 lbl_1_data_2138;
extern M504_PATH1 lbl_1_data_2148;
extern M504_PATH1 lbl_1_data_2158;
extern M504_PATH1 lbl_1_data_2168;
extern M504_PATH1 lbl_1_data_2178;
extern M504_PATH2 lbl_1_data_2188;
extern M504_PATH1 lbl_1_data_21A4;
extern M504_PATH5 lbl_1_data_21B4;
extern M504_PATH1 lbl_1_data_21F4;
extern M504_PATH3 lbl_1_data_2204;
extern M504_PATH1 lbl_1_data_222C;
extern M504_PATH1 lbl_1_data_223C;
extern M504_PATH1 lbl_1_data_224C;
extern M504_PATH1 lbl_1_data_225C;
extern M504_PATH1 lbl_1_data_226C;
extern M504_PATH1 lbl_1_data_227C;
extern M504_PATH1 lbl_1_data_228C;
extern M504_PATH1 lbl_1_data_229C;
extern M504_PATH1 lbl_1_data_22AC;
extern M504_PATH1 lbl_1_data_22BC;
extern M504_PATH1 lbl_1_data_22CC;
extern M504_PATH1 lbl_1_data_22DC;
extern M504_PATH1 lbl_1_data_22EC;
extern M504_PATH1 lbl_1_data_22FC;
extern M504_PATH1 lbl_1_data_230C;
extern M504_PATH3 lbl_1_data_231C;
extern M504_PATH1 lbl_1_data_2344;
extern M504_PATH1 lbl_1_data_2354;
extern M504_PATH1 lbl_1_data_2364;
extern M504_PATH3 lbl_1_data_2374;
extern M504_PATH1 lbl_1_data_239C;
extern M504_PATH3 lbl_1_data_23AC;
extern M504_PATH1 lbl_1_data_23D4;
extern M504_PATH1 lbl_1_data_23E4;
extern M504_PATH1 lbl_1_data_23F4;
extern M504_PATH1 lbl_1_data_2404;
extern M504_PATH1 lbl_1_data_2414;
extern M504_PATH1 lbl_1_data_2424;
extern M504_PATH1 lbl_1_data_2434;
extern M504_PATH1 lbl_1_data_2444;
extern M504_PATH1 lbl_1_data_2454;
extern M504_PATH1 lbl_1_data_2464;
extern M504_PATH1 lbl_1_data_2474;
extern M504_PATH1 lbl_1_data_2484;
extern M504_PATH1 lbl_1_data_2494;
extern M504_PATH1 lbl_1_data_24A4;
extern M504_PATH1 lbl_1_data_24B4;
extern M504_PATH1 lbl_1_data_24C4;
extern M504_PATH1 lbl_1_data_24D4;
extern M504_PATH1 lbl_1_data_24E4;
extern M504_PATH1 lbl_1_data_24F4;
extern M504_PATH1 lbl_1_data_2504;
extern M504_PATH1 lbl_1_data_2514;
extern M504_PATH1 lbl_1_data_2524;
extern M504_PATH1 lbl_1_data_2534;
extern M504_PATH1 lbl_1_data_2544;
extern M504_PATH1 lbl_1_data_2554;
extern M504_PATH1 lbl_1_data_2564;
extern M504_PATH1 lbl_1_data_2574;
extern M504_PATH2 lbl_1_data_2584;
extern M504_PATH1 lbl_1_data_25A0;
extern M504_PATH1 lbl_1_data_25B0;
extern M504_PATH1 lbl_1_data_25C0;
extern M504_PATH3 lbl_1_data_25D0;
extern M504_PATH1 lbl_1_data_25F8;
extern M504_PATH2 lbl_1_data_2608;
extern M504_PATH1 lbl_1_data_2624;
extern M504_PATH2 lbl_1_data_2634;
extern M504_PATH1 lbl_1_data_2650;
extern M504_PATH1 lbl_1_data_2660;
extern M504_PATH1 lbl_1_data_2670;
extern M504_PATH4 lbl_1_data_2680;
extern M504_PATH1 lbl_1_data_26B4;
extern M504_PATH1 lbl_1_data_26C4;
extern M504_PATH1 lbl_1_data_26D4;
extern M504_PATH1 lbl_1_data_26E4;
extern M504_PATH1 lbl_1_data_26F4;
extern M504_PATH4 lbl_1_data_2704;
extern M504_PATH1 lbl_1_data_2738;
extern M504_PATH1 lbl_1_data_2748;
extern M504_PATH1 lbl_1_data_2758;
extern M504_PATH1 lbl_1_data_2768;
extern M504_PATH1 lbl_1_data_2778;
extern M504_PATH1 lbl_1_data_2788;
extern M504_PATH1 lbl_1_data_2798;
extern M504_PATH1 lbl_1_data_27A8;
extern M504_PATH1 lbl_1_data_27B8;
extern M504_PATH2 lbl_1_data_27C8;
extern M504_PATH1 lbl_1_data_27E4;
extern M504_PATH1 lbl_1_data_27F4;
extern M504_PATH1 lbl_1_data_2804;
extern M504_PATH1 lbl_1_data_2814;
extern M504_PATH1 lbl_1_data_2824;
extern M504_PATH1 lbl_1_data_2834;
extern M504_PATH1 lbl_1_data_2844;
extern M504_PATH1 lbl_1_data_2854;
extern M504_PATH1 lbl_1_data_2864;
extern M504_PATH2 lbl_1_data_2874;
extern M504_PATH1 lbl_1_data_2890;
extern M504_PATH1 lbl_1_data_28A0;
extern M504_PATH1 lbl_1_data_28B0;
extern M504_PATH1 lbl_1_data_28C0;
extern M504_PATH1 lbl_1_data_28D0;
extern M504_PATH1 lbl_1_data_28E0;
extern M504_PATH1 lbl_1_data_28F0;
extern M504_PATH2 lbl_1_data_2900;
extern M504_PATH1 lbl_1_data_291C;
extern M504_PATH1 lbl_1_data_292C;
extern M504_PATH1 lbl_1_data_293C;
extern M504_PATH1 lbl_1_data_294C;
extern M504_PATH1 lbl_1_data_295C;
extern M504_PATH1 lbl_1_data_296C;
extern M504_PATH1 lbl_1_data_297C;
extern M504_PATH1 lbl_1_data_298C;
extern M504_PATH1 lbl_1_data_299C;
extern M504_PATH1 lbl_1_data_29AC;
extern M504_PATH1 lbl_1_data_29BC;
extern M504_PATH1 lbl_1_data_29CC;
extern M504_PATH1 lbl_1_data_29DC;
extern M504_PATH1 lbl_1_data_29EC;
extern M504_PATH1 lbl_1_data_29FC;
extern M504_PATH3 lbl_1_data_2A0C;
extern M504_PATH1 lbl_1_data_2A34;
extern M504_PATH1 lbl_1_data_2A44;
extern M504_PATH1 lbl_1_data_2A54;
extern M504_PATH1 lbl_1_data_2A64;
extern M504_PATH1 lbl_1_data_2A74;
extern M504_PATH1 lbl_1_data_2A84;
extern M504_PATH1 lbl_1_data_2A94;
extern M504_PATH1 lbl_1_data_2AA4;
extern M504_PATH1 lbl_1_data_2AB4;
extern M504_PATH1 lbl_1_data_2AC4;
extern M504_PATH1 lbl_1_data_2AD4;
extern M504_PATH3 lbl_1_data_2AE4;
extern M504_PATH1 lbl_1_data_2B0C;
extern M504_PATH1 lbl_1_data_2B1C;
extern M504_PATH1 lbl_1_data_2B2C;
extern M504_PATH1 lbl_1_data_2B3C;
extern M504_PATH1 lbl_1_data_2B4C;
extern M504_PATH1 lbl_1_data_2B5C;
extern M504_PATH1 lbl_1_data_2B6C;
extern M504_PATH2 lbl_1_data_2B7C;
extern M504_PATH1 lbl_1_data_2B98;
extern M504_PATH1 lbl_1_data_2BA8;
extern M504_PATH1 lbl_1_data_2BB8;
extern M504_PATH1 lbl_1_data_2BC8;
extern M504_PATH1 lbl_1_data_2BD8;
extern M504_PATH1 lbl_1_data_2BE8;
extern M504_PATH1 lbl_1_data_2BF8;
extern M504_PATH5 lbl_1_data_2C08;
extern M504_PATH1 lbl_1_data_2C48;
extern M504_PATH1 lbl_1_data_2C58;
extern M504_PATH1 lbl_1_data_2C68;
extern M504_PATH1 lbl_1_data_2C78;
extern M504_PATH1 lbl_1_data_2C88;
extern M504_PATH1 lbl_1_data_2C98;
extern M504_PATH1 lbl_1_data_2CA8;
extern M504_PATH1 lbl_1_data_2CB8;
extern M504_PATH1 lbl_1_data_2CC8;
extern M504_PATH1 lbl_1_data_2CD8;
extern M504_PATH1 lbl_1_data_2CE8;
extern M504_PATH1 lbl_1_data_2CF8;
extern M504_PATH1 lbl_1_data_2D08;
extern M504_PATH1 lbl_1_data_2D18;
extern M504_PATH1 lbl_1_data_2D28;
extern M504_PATH2 lbl_1_data_2D38;
extern M504_PATH1 lbl_1_data_2D54;
extern M504_PATH1 lbl_1_data_2D64;
extern M504_PATH1 lbl_1_data_2D74;
extern M504_PATH1 lbl_1_data_2D84;
extern M504_PATH1 lbl_1_data_2D94;
extern M504_PATH1 lbl_1_data_2DA4;
extern M504_PATH1 lbl_1_data_2DB4;
extern M504_PATH1 lbl_1_data_2DC4;
extern M504_PATH1 lbl_1_data_2DD4;
extern M504_PATH1 lbl_1_data_2DE4;
extern M504_PATH1 lbl_1_data_2DF4;
extern M504_NODE1 lbl_1_data_2E04;
extern M504_NODE6 lbl_1_data_2E14;
extern M504_NODE12 lbl_1_data_2E38;
extern M504_NODE12 lbl_1_data_2E74;
extern M504_NODE6 lbl_1_data_2EB0;
extern M504_NODE1 lbl_1_data_2ED4;
extern M504_NODE3 lbl_1_data_2EE4;
extern M504_NODE1 lbl_1_data_2EFC;
extern M504_NODE2 lbl_1_data_2F0C;
extern M504_NODE1 lbl_1_data_2F20;
extern M504_NODE1 lbl_1_data_2F30;
extern M504_NODE1 lbl_1_data_2F40;
extern M504_NODE1 lbl_1_data_2F50;
extern M504_NODE1 lbl_1_data_2F60;
extern M504_NODE3 lbl_1_data_2F70;
extern M504_NODE1 lbl_1_data_2F88;
extern M504_NODE1 lbl_1_data_2F98;
extern M504_NODE1 lbl_1_data_2FA8;
extern M504_NODE1 lbl_1_data_2FB8;
extern M504_NODE1 lbl_1_data_2FC8;
extern M504_NODE1 lbl_1_data_2FD8;
extern M504_NODE1 lbl_1_data_2FE8;
extern M504_NODE1 lbl_1_data_2FF8;
extern M504_NODE3 lbl_1_data_3008;
extern M504_NODE1 lbl_1_data_3020;
extern M504_NODE2 lbl_1_data_3030;
extern M504_NODE1 lbl_1_data_3044;
extern M504_NODE1 lbl_1_data_3054;
extern M504_NODE1 lbl_1_data_3064;
extern M504_NODE1 lbl_1_data_3074;
extern M504_NODE1 lbl_1_data_3084;
extern M504_NODE1 lbl_1_data_3094;
extern M504_NODE1 lbl_1_data_30A4;
extern M504_NODE1 lbl_1_data_30B4;
extern M504_NODE1 lbl_1_data_30C4;
extern M504_NODE1 lbl_1_data_30D4;
extern M504_NODE1 lbl_1_data_30E4;
extern M504_NODE1 lbl_1_data_30F4;
extern M504_NODE1 lbl_1_data_3104;
extern M504_NODE1 lbl_1_data_3114;
extern M504_NODE1 lbl_1_data_3124;
extern M504_NODE1 lbl_1_data_3134;
extern M504_NODE1 lbl_1_data_3144;
extern M504_NODE1 lbl_1_data_3154;
extern M504_NODE1 lbl_1_data_3164;
extern M504_NODE1 lbl_1_data_3174;
extern M504_NODE1 lbl_1_data_3184;
extern M504_NODE1 lbl_1_data_3194;
extern M504_NODE1 lbl_1_data_31A4;
extern M504_NODE1 lbl_1_data_31B4;
extern M504_NODE1 lbl_1_data_31C4;
extern M504_NODE1 lbl_1_data_31D4;
extern M504_NODE1 lbl_1_data_31E4;
extern M504_NODE1 lbl_1_data_31F4;
extern M504_NODE1 lbl_1_data_3204;
extern M504_NODE1 lbl_1_data_3214;
extern M504_NODE1 lbl_1_data_3224;
extern M504_NODE1 lbl_1_data_3234;
extern M504_NODE1 lbl_1_data_3244;
extern M504_NODE1 lbl_1_data_3254;
extern M504_NODE1 lbl_1_data_3264;
extern M504_NODE1 lbl_1_data_3274;
extern M504_NODE1 lbl_1_data_3284;
extern M504_NODE1 lbl_1_data_3294;
extern M504_NODE1 lbl_1_data_32A4;
extern M504_NODE1 lbl_1_data_32B4;
extern M504_NODE1 lbl_1_data_32C4;
extern M504_NODE1 lbl_1_data_32D4;
extern M504_NODE1 lbl_1_data_32E4;
extern M504_NODE1 lbl_1_data_32F4;
extern M504_NODE1 lbl_1_data_3304;
extern M504_NODE1 lbl_1_data_3314;
extern M504_NODE1 lbl_1_data_3324;
extern M504_NODE1 lbl_1_data_3334;
extern M504_NODE1 lbl_1_data_3344;
extern M504_NODE1 lbl_1_data_3354;
extern M504_NODE1 lbl_1_data_3364;
extern M504_NODE1 lbl_1_data_3374;
extern M504_NODE1 lbl_1_data_3384;
extern M504_NODE1 lbl_1_data_3394;
extern M504_NODE1 lbl_1_data_33A4;
extern M504_NODE1 lbl_1_data_33B4;
extern M504_NODE1 lbl_1_data_33C4;
extern M504_NODE1 lbl_1_data_33D4;
extern M504_NODE1 lbl_1_data_33E4;
extern M504_NODE1 lbl_1_data_33F4;
extern M504_NODE1 lbl_1_data_3404;
extern M504_NODE1 lbl_1_data_3414;
extern M504_NODE1 lbl_1_data_3424;
extern M504_NODE1 lbl_1_data_3434;
extern M504_NODE1 lbl_1_data_3444;
extern M504_NODE1 lbl_1_data_3454;
extern M504_NODE1 lbl_1_data_3464;
extern M504_NODE1 lbl_1_data_3474;
extern M504_NODE1 lbl_1_data_3484;
extern M504_NODE1 lbl_1_data_3494;
extern M504_NODE1 lbl_1_data_34A4;
extern M504_NODE1 lbl_1_data_34B4;
extern M504_NODE1 lbl_1_data_34C4;
extern M504_NODE1 lbl_1_data_34D4;
extern M504_NODE1 lbl_1_data_34E4;
extern M504_NODE1 lbl_1_data_34F4;
extern M504_NODE1 lbl_1_data_3504;
extern M504_NODE1 lbl_1_data_3514;
extern M504_NODE1 lbl_1_data_3524;
extern M504_NODE1 lbl_1_data_3534;
extern M504_NODE1 lbl_1_data_3544;
extern M504_NODE1 lbl_1_data_3554;
extern M504_NODE1 lbl_1_data_3564;
extern M504_NODE1 lbl_1_data_3574;
extern M504_NODE1 lbl_1_data_3584;
extern M504_NODE1 lbl_1_data_3594;
extern M504_NODE1 lbl_1_data_35A4;
extern M504_NODE1 lbl_1_data_35B4;
extern M504_NODE1 lbl_1_data_35C4;
extern M504_NODE1 lbl_1_data_35D4;
extern M504_NODE1 lbl_1_data_35E4;
extern M504_NODE1 lbl_1_data_35F4;
extern M504_NODE1 lbl_1_data_3604;
extern M504_NODE1 lbl_1_data_3614;
extern M504_NODE1 lbl_1_data_3624;
extern M504_NODE1 lbl_1_data_3634;
extern M504_NODE1 lbl_1_data_3644;
extern M504_NODE1 lbl_1_data_3654;
extern M504_NODE1 lbl_1_data_3664;
extern M504_NODE1 lbl_1_data_3674;
extern M504_NODE1 lbl_1_data_3684;
extern M504_NODE1 lbl_1_data_3694;
extern M504_NODE1 lbl_1_data_36A4;
extern M504_NODE1 lbl_1_data_36B4;
extern M504_NODE1 lbl_1_data_36C4;
extern M504_NODE1 lbl_1_data_36D4;
extern M504_NODE1 lbl_1_data_36E4;
extern M504_NODE1 lbl_1_data_36F4;
extern M504_NODE1 lbl_1_data_3704;
extern M504_NODE1 lbl_1_data_3714;
extern M504_NODE1 lbl_1_data_3724;
extern M504_NODE1 lbl_1_data_3734;
extern M504_NODE1 lbl_1_data_3744;
extern M504_NODE1 lbl_1_data_3754;
extern M504_NODE1 lbl_1_data_3764;
extern M504_NODE1 lbl_1_data_3774;
extern M504_NODE1 lbl_1_data_3784;
extern M504_NODE1 lbl_1_data_3794;
extern M504_NODE1 lbl_1_data_37A4;
extern M504_NODE1 lbl_1_data_37B4;
extern M504_NODE1 lbl_1_data_37C4;
extern M504_NODE1 lbl_1_data_37D4;
extern M504_NODE1 lbl_1_data_37E4;
extern M504_NODE1 lbl_1_data_37F4;
extern M504_NODE1 lbl_1_data_3804;
extern M504_NODE1 lbl_1_data_3814;
extern M504_NODE1 lbl_1_data_3824;
extern M504_NODE1 lbl_1_data_3834;
extern M504_NODE1 lbl_1_data_3844;
extern M504_NODE1 lbl_1_data_3854;
extern M504_NODE1 lbl_1_data_3864;
extern M504_NODE1 lbl_1_data_3874;
extern M504_NODE1 lbl_1_data_3884;
extern M504_NODE1 lbl_1_data_3894;
extern M504_NODE1 lbl_1_data_38A4;
extern M504_NODE1 lbl_1_data_38B4;
extern M504_NODE1 lbl_1_data_38C4;
extern M504_NODE1 lbl_1_data_38D4;
extern M504_NODE1 lbl_1_data_38E4;
extern M504_NODE1 lbl_1_data_38F4;
extern M504_NODE1 lbl_1_data_3904;
extern M504_NODE1 lbl_1_data_3914;
extern M504_NODE1 lbl_1_data_3924;
extern M504_NODE1 lbl_1_data_3934;
extern M504_NODE1 lbl_1_data_3944;
extern M504_NODE1 lbl_1_data_3954;
extern M504_NODE1 lbl_1_data_3964;
extern M504_NODE1 lbl_1_data_3974;
extern M504_NODE1 lbl_1_data_3984;
extern M504_NODE1 lbl_1_data_3994;
extern M504_NODE1 lbl_1_data_39A4;
extern M504_NODE1 lbl_1_data_39B4;
extern M504_NODE1 lbl_1_data_39C4;
extern M504_NODE1 lbl_1_data_39D4;
extern M504_NODE1 lbl_1_data_39E4;
extern M504_NODE1 lbl_1_data_39F4;
extern M504_NODE1 lbl_1_data_3A04;
extern M504_NODE1 lbl_1_data_3A14;
extern M504_NODE1 lbl_1_data_3A24;
extern M504_NODE1 lbl_1_data_3A34;
extern M504_NODE1 lbl_1_data_3A44;
extern M504_NODE1 lbl_1_data_3A54;
extern M504_NODE1 lbl_1_data_3A64;
extern M504_NODE1 lbl_1_data_3A74;
extern M504_NODE1 lbl_1_data_3A84;
extern M504_NODE1 lbl_1_data_3A94;
extern M504_NODE1 lbl_1_data_3AA4;
extern M504_NODE1 lbl_1_data_3AB4;
extern M504_NODE1 lbl_1_data_3AC4;
extern M504_NODE1 lbl_1_data_3AD4;
extern M504_NODE1 lbl_1_data_3AE4;
extern M504_NODE1 lbl_1_data_3AF4;
extern M504_NODE1 lbl_1_data_3B04;
extern M504_NODE1 lbl_1_data_3B14;
extern M504_NODE2 lbl_1_data_3B24;
extern M504_NODE1 lbl_1_data_3B38;
extern M504_NODE1 lbl_1_data_3B48;
extern M504_NODE1 lbl_1_data_3B58;
extern M504_NODE2 lbl_1_data_3B68;
extern M504_NODE1 lbl_1_data_3B7C;
extern M504_NODE1 lbl_1_data_3B8C;
extern M504_NODE1 lbl_1_data_3B9C;
extern M504_NODE1 lbl_1_data_3BAC;
extern M504_NODE2 lbl_1_data_3BBC;
extern M504_NODE1 lbl_1_data_3BD0;
extern M504_NODE1 lbl_1_data_3BE0;
extern M504_NODE1 lbl_1_data_3BF0;
extern M504_NODE1 lbl_1_data_3C00;
extern M504_NODE1 lbl_1_data_3C10;
extern M504_NODE1 lbl_1_data_3C20;
extern M504_NODE1 lbl_1_data_3C30;
extern M504_NODE1 lbl_1_data_3C40;
extern M504_NODE2 lbl_1_data_3C50;
extern M504_NODE1 lbl_1_data_3C64;
extern M504_NODE1 lbl_1_data_3C74;
extern M504_NODE1 lbl_1_data_3C84;
extern M504_NODE2 lbl_1_data_3C94;
extern M504_NODE1 lbl_1_data_3CA8;
extern M504_NODE1 lbl_1_data_3CB8;
extern M504_NODE1 lbl_1_data_3CC8;
extern M504_NODE1 lbl_1_data_3CD8;
extern M504_NODE1 lbl_1_data_3CE8;
extern M504_NODE1 lbl_1_data_3CF8;
extern M504_NODE2 lbl_1_data_3D08;
extern M504_NODE1 lbl_1_data_3D1C;
extern M504_NODE1 lbl_1_data_3D2C;
extern M504_NODE1 lbl_1_data_3D3C;
extern M504_NODE1 lbl_1_data_3D4C;
extern M504_NODE1 lbl_1_data_3D5C;
extern M504_NODE1 lbl_1_data_3D6C;
extern M504_NODE2 lbl_1_data_3D7C;
extern M504_NODE1 lbl_1_data_3D90;
extern M504_NODE1 lbl_1_data_3DA0;
extern M504_NODE1 lbl_1_data_3DB0;
extern M504_NODE1 lbl_1_data_3DC0;
extern M504_NODE1 lbl_1_data_3DD0;
extern M504_NODE1 lbl_1_data_3DE0;
extern M504_NODE1 lbl_1_data_3DF0;
extern M504_NODE1 lbl_1_data_3E00;
extern M504_NODE1 lbl_1_data_3E10;
extern M504_NODE1 lbl_1_data_3E20;
extern M504_NODE1 lbl_1_data_3E30;
extern M504_NODE1 lbl_1_data_3E40;
extern M504_NODE1 lbl_1_data_3E50;
extern M504_NODE2 lbl_1_data_3E60;
extern M504_NODE1 lbl_1_data_3E74;
extern M504_NODE1 lbl_1_data_3E84;
extern M504_NODE1 lbl_1_data_3E94;
extern M504_NODE2 lbl_1_data_3EA4;
extern M504_NODE1 lbl_1_data_3EB8;
extern M504_NODE1 lbl_1_data_3EC8;
extern M504_NODE1 lbl_1_data_3ED8;
extern M504_NODE1 lbl_1_data_3EE8;
extern M504_NODE1 lbl_1_data_3EF8;
extern M504_NODE1 lbl_1_data_3F08;
extern M504_NODE1 lbl_1_data_3F18;
extern M504_NODE1 lbl_1_data_3F28;
extern M504_NODE1 lbl_1_data_3F38;
extern M504_NODE1 lbl_1_data_3F48;
extern M504_NODE1 lbl_1_data_3F58;
extern M504_NODE1 lbl_1_data_3F68;
extern M504_NODE2 lbl_1_data_3F78;
extern M504_NODE1 lbl_1_data_3F8C;
extern M504_NODE1 lbl_1_data_3F9C;
extern M504_NODE1 lbl_1_data_3FAC;
extern M504_NODE1 lbl_1_data_3FBC;
extern M504_NODE2 lbl_1_data_3FCC;
extern M504_NODE1 lbl_1_data_3FE0;
extern M504_NODE1 lbl_1_data_3FF0;
extern M504_NODE1 lbl_1_data_4000;
extern M504_NODE1 lbl_1_data_4010;
extern M504_NODE1 lbl_1_data_4020;
extern M504_NODE1 lbl_1_data_4030;
extern M504_NODE1 lbl_1_data_4040;
extern M504_NODE1 lbl_1_data_4050;
extern M504_NODE2 lbl_1_data_4060;
extern M504_NODE1 lbl_1_data_4074;
extern M504_NODE1 lbl_1_data_4084;
extern M504_NODE1 lbl_1_data_4094;
extern M504_NODE1 lbl_1_data_40A4;
extern M504_NODE1 lbl_1_data_40B4;
extern M504_NODE1 lbl_1_data_40C4;
extern M504_NODE1 lbl_1_data_40D4;
extern M504_NODE1 lbl_1_data_40E4;
extern M504_NODE1 lbl_1_data_40F4;
extern M504_NODE1 lbl_1_data_4104;
extern M504_NODE1 lbl_1_data_4114;
extern M504_NODE1 lbl_1_data_4124;

/* --- .data --- */
/* 0x528 */ M504_PATH1 lbl_1_data_528 = { 0, 0, { { 0.0f, 0.0f, 0.0f } } };
/* 0x538 */ M504_PATH1 lbl_1_data_538 = { -1, 0, { { 0.0f, 0.0f, 0.0f } } };
/* 0x548 */ M504_PATH2 lbl_1_data_548 = { 2, 0, { { -2e+01f, 0.0f, 4.8e+02f }, { -3.6e+02f, 0.0f, 5.6e+02f } } };
/* 0x564 */ M504_PATH1 lbl_1_data_564 = { 1, 0, { { -3.6e+02f, 0.0f, 8.6e+02f } } };
/* 0x574 */ M504_PATH1 lbl_1_data_574 = { 1, 0, { { 3.6e+02f, 0.0f, 1.04e+03f } } };
/* 0x584 */ M504_PATH1 lbl_1_data_584 = { 1, 0, { { 3.6e+02f, 0.0f, 1.36e+03f } } };
/* 0x594 */ M504_PATH1 lbl_1_data_594 = { 1, 0, { { 1.4e+02f, 0.0f, 1.71e+03f } } };
/* 0x5A4 */ M504_PATH1 lbl_1_data_5A4 = { 1, 0, { { -1.8e+02f, 0.0f, 1.71e+03f } } };
/* 0x5B4 */ M504_PATH1 lbl_1_data_5B4 = { 1, 0, { { -3.6e+02f, 0.0f, 1.4e+03f } } };
/* 0x5C4 */ M504_PATH1 lbl_1_data_5C4 = { 1, 0, { { -266.0f, 0.0f, 1.83e+03f } } };
/* 0x5D4 */ M504_PATH1 lbl_1_data_5D4 = { 1, 0, { { -1.3e+02f, 0.0f, 2153.0f } } };
/* 0x5E4 */ M504_PATH1 lbl_1_data_5E4 = { 1, 0, { { -3.6e+02f, 0.0f, 2.2e+03f } } };
/* 0x5F4 */ M504_PATH1 lbl_1_data_5F4 = { 1, 0, { { 0.0f, 0.0f, 2225.0f } } };
/* 0x604 */ M504_PATH1 lbl_1_data_604 = { 1, 0, { { 3.6e+02f, 0.0f, 2.6e+03f } } };
/* 0x614 */ M504_PATH1 lbl_1_data_614 = { 1, 0, { { 3.6e+02f, 0.0f, 2.9e+03f } } };
/* 0x624 */ M504_PATH1 lbl_1_data_624 = { 1, 0, { { 1e+02f, 0.0f, 3.2e+03f } } };
/* 0x634 */ M504_PATH1 lbl_1_data_634 = { 1, 0, { { 8e+01f, 0.0f, 3.5e+03f } } };
/* 0x644 */ M504_PATH1 lbl_1_data_644 = { 1, 0, { { -1.6e+02f, 0.0f, 3.5e+03f } } };
/* 0x654 */ M504_PATH2 lbl_1_data_654 = { 2, 0, { { -2e+01f, 0.0f, 4.8e+02f }, { -1.5e+02f, 0.0f, 5.8e+02f } } };
/* 0x670 */ M504_PATH1 lbl_1_data_670 = { 1, 0, { { -3.6e+02f, 0.0f, 5.1e+02f } } };
/* 0x680 */ M504_PATH3 lbl_1_data_680 = { 3, 0, { { -71.0f, 0.0f, 5.1e+02f }, { -6e+01f, 0.0f, 7.6e+02f }, { 3.6e+02f, 0.0f, 9e+02f } } };
/* 0x6A8 */ M504_PATH1 lbl_1_data_6A8 = { 1, 0, { { 3.6e+02f, 0.0f, 1.36e+03f } } };
/* 0x6B8 */ M504_PATH1 lbl_1_data_6B8 = { 1, 0, { { 6e+01f, 0.0f, 1.71e+03f } } };
/* 0x6C8 */ M504_PATH1 lbl_1_data_6C8 = { 1, 0, { { 3.6e+02f, 0.0f, 1.71e+03f } } };
/* 0x6D8 */ M504_PATH3 lbl_1_data_6D8 = { 3, 0, { { 3.6e+02f, 0.0f, 2.2e+03f }, { -1.8e+02f, 0.0f, 2.2e+03f }, { -3.5e+02f, 0.0f, 1.4e+03f } } };
/* 0x700 */ M504_PATH1 lbl_1_data_700 = { 1, 0, { { -266.0f, 0.0f, 1.83e+03f } } };
/* 0x710 */ M504_PATH1 lbl_1_data_710 = { 1, 0, { { -3.5e+02f, 0.0f, 2.4e+03f } } };
/* 0x720 */ M504_PATH1 lbl_1_data_720 = { 1, 0, { { 55.0f, 0.0f, 2.3e+03f } } };
/* 0x730 */ M504_PATH1 lbl_1_data_730 = { 1, 0, { { 3.6e+02f, 0.0f, 2.58e+03f } } };
/* 0x740 */ M504_PATH1 lbl_1_data_740 = { 1, 0, { { 3.6e+02f, 0.0f, 2.9e+03f } } };
/* 0x750 */ M504_PATH1 lbl_1_data_750 = { 1, 0, { { 2.4e+02f, 0.0f, 3e+03f } } };
/* 0x760 */ M504_PATH1 lbl_1_data_760 = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x770 */ M504_PATH1 lbl_1_data_770 = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x780 */ M504_PATH1 lbl_1_data_780 = { 1, 0, { { -3e+02f, 0.0f, 3.05e+03f } } };
/* 0x790 */ M504_PATH1 lbl_1_data_790 = { 1, 0, { { 0.0f, 0.0f, 3.5e+03f } } };
/* 0x7A0 */ M504_PATH1 lbl_1_data_7A0 = { 1, 0, { { 2.5e+02f, 0.0f, 3.5e+03f } } };
/* 0x7B0 */ M504_PATH2 lbl_1_data_7B0 = { 2, 0, { { -2e+01f, 0.0f, 4.8e+02f }, { -255.0f, 0.0f, 6.7e+02f } } };
/* 0x7CC */ M504_PATH1 lbl_1_data_7CC = { 1, 0, { { 0.0f, 0.0f, 6.7e+02f } } };
/* 0x7DC */ M504_PATH1 lbl_1_data_7DC = { 1, 0, { { 3.6e+02f, 0.0f, 8e+02f } } };
/* 0x7EC */ M504_PATH1 lbl_1_data_7EC = { 1, 0, { { 3.6e+02f, 0.0f, 1.36e+03f } } };
/* 0x7FC */ M504_PATH1 lbl_1_data_7FC = { 1, 0, { { 256.0f, 0.0f, 1.36e+03f } } };
/* 0x80C */ M504_PATH1 lbl_1_data_80C = { 1, 0, { { 65.0f, 0.0f, 1.36e+03f } } };
/* 0x81C */ M504_PATH2 lbl_1_data_81C = { 2, 0, { { 65.0f, 0.0f, 1.5e+03f }, { -2.1e+02f, 0.0f, 1.49e+03f } } };
/* 0x838 */ M504_PATH1 lbl_1_data_838 = { 1, 0, { { -266.0f, 0.0f, 1.83e+03f } } };
/* 0x848 */ M504_PATH1 lbl_1_data_848 = { 1, 0, { { -1.2e+02f, 0.0f, 2.15e+03f } } };
/* 0x858 */ M504_PATH1 lbl_1_data_858 = { 1, 0, { { -3.6e+02f, 0.0f, 2.15e+03f } } };
/* 0x868 */ M504_PATH3 lbl_1_data_868 = { 3, 0, { { 1.1e+02f, 0.0f, 2.19e+03f }, { 2.1e+02f, 0.0f, 2.44e+03f }, { 2.2e+02f, 0.0f, 2.35e+03f } } };
/* 0x890 */ M504_PATH1 lbl_1_data_890 = { 1, 0, { { 3.6e+02f, 0.0f, 2.9e+03f } } };
/* 0x8A0 */ M504_PATH1 lbl_1_data_8A0 = { 1, 0, { { 3e+02f, 0.0f, 3.3e+03f } } };
/* 0x8B0 */ M504_PATH1 lbl_1_data_8B0 = { 1, 0, { { 45.0f, 0.0f, 3.3e+03f } } };
/* 0x8C0 */ M504_PATH1 lbl_1_data_8C0 = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x8D0 */ M504_PATH1 lbl_1_data_8D0 = { 1, 0, { { 3e+02f, 0.0f, 3.05e+03f } } };
/* 0x8E0 */ M504_PATH1 lbl_1_data_8E0 = { 1, 0, { { 0.0f, 0.0f, 3.8e+03f } } };
/* 0x8F0 */ M504_PATH1 lbl_1_data_8F0 = { 1, 0, { { -1.8e+02f, 0.0f, 3.7e+03f } } };
/* 0x900 */ M504_PATH2 lbl_1_data_900 = { 2, 0, { { 3.5e+02f, 0.0f, 7.2e+02f }, { -2.8e+02f, 0.0f, 7e+02f } } };
/* 0x91C */ M504_PATH1 lbl_1_data_91C = { 1, 0, { { 0.0f, 0.0f, 9.4e+02f } } };
/* 0x92C */ M504_PATH1 lbl_1_data_92C = { 1, 0, { { 3.6e+02f, 0.0f, 1.02e+03f } } };
/* 0x93C */ M504_PATH1 lbl_1_data_93C = { 1, 0, { { 3.6e+02f, 0.0f, 1.32e+03f } } };
/* 0x94C */ M504_PATH1 lbl_1_data_94C = { 1, 0, { { 155.0f, 0.0f, 1.7e+03f } } };
/* 0x95C */ M504_PATH1 lbl_1_data_95C = { 1, 0, { { -7e+01f, 0.0f, 1.61e+03f } } };
/* 0x96C */ M504_PATH1 lbl_1_data_96C = { 1, 0, { { -2e+02f, 0.0f, 1.49e+03f } } };
/* 0x97C */ M504_PATH1 lbl_1_data_97C = { 1, 0, { { -3.1e+02f, 0.0f, 1829.0f } } };
/* 0x98C */ M504_PATH1 lbl_1_data_98C = { 1, 0, { { -3.6e+02f, 0.0f, 2.45e+03f } } };
/* 0x99C */ M504_PATH1 lbl_1_data_99C = { 1, 0, { { 0.0f, 0.0f, 2.55e+03f } } };
/* 0x9AC */ M504_PATH1 lbl_1_data_9AC = { 1, 0, { { 2.1e+02f, 0.0f, 2.34e+03f } } };
/* 0x9BC */ M504_PATH1 lbl_1_data_9BC = { 1, 0, { { 2.7e+02f, 0.0f, 2.67e+03f } } };
/* 0x9CC */ M504_PATH1 lbl_1_data_9CC = { 1, 0, { { 3e+02f, 0.0f, 3.33e+03f } } };
/* 0x9DC */ M504_PATH1 lbl_1_data_9DC = { 1, 0, { { 7e+01f, 0.0f, 3.3e+03f } } };
/* 0x9EC */ M504_PATH1 lbl_1_data_9EC = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x9FC */ M504_PATH1 lbl_1_data_9FC = { 1, 0, { { -3e+02f, 0.0f, 3.25e+03f } } };
/* 0xA0C */ M504_PATH1 lbl_1_data_A0C = { 1, 0, { { 0.0f, 0.0f, 3.7e+03f } } };
/* 0xA1C */ M504_PATH1 lbl_1_data_A1C = { 1, 0, { { -205.0f, 0.0f, 3.7e+03f } } };
/* 0xA2C */ M504_PATH2 lbl_1_data_A2C = { 2, 0, { { 3.5e+02f, 0.0f, 7.2e+02f }, { -215.0f, 0.0f, 9.5e+02f } } };
/* 0xA48 */ M504_PATH1 lbl_1_data_A48 = { 1, 0, { { 9e+01f, 0.0f, 9.5e+02f } } };
/* 0xA58 */ M504_PATH1 lbl_1_data_A58 = { 1, 0, { { 3.6e+02f, 0.0f, 9.5e+02f } } };
/* 0xA68 */ M504_PATH1 lbl_1_data_A68 = { 1, 0, { { 3.6e+02f, 0.0f, 1.3e+03f } } };
/* 0xA78 */ M504_PATH1 lbl_1_data_A78 = { 1, 0, { { 3.6e+02f, 0.0f, 1.75e+03f } } };
/* 0xA88 */ M504_PATH1 lbl_1_data_A88 = { 1, 0, { { 3.6e+02f, 0.0f, 1.9e+03f } } };
/* 0xA98 */ M504_PATH3 lbl_1_data_A98 = { 3, 0, { { 3.6e+02f, 0.0f, 2.23e+03f }, { -1.1e+02f, 0.0f, 2.23e+03f }, { -1.8e+02f, 0.0f, 1.52e+03f } } };
/* 0xAC0 */ M504_PATH1 lbl_1_data_AC0 = { 1, 0, { { -1.8e+02f, 0.0f, 1.9e+03f } } };
/* 0xAD0 */ M504_PATH1 lbl_1_data_AD0 = { 1, 0, { { 0.0f, 0.0f, 2.35e+03f } } };
/* 0xAE0 */ M504_PATH1 lbl_1_data_AE0 = { 1, 0, { { 0.0f, 0.0f, 2.35e+03f } } };
/* 0xAF0 */ M504_PATH1 lbl_1_data_AF0 = { 1, 0, { { -3.6e+02f, 0.0f, 2.35e+03f } } };
/* 0xB00 */ M504_PATH1 lbl_1_data_B00 = { 1, 0, { { 0.0f, 0.0f, 2.45e+03f } } };
/* 0xB10 */ M504_PATH1 lbl_1_data_B10 = { 1, 0, { { 3.6e+02f, 0.0f, 2.76e+03f } } };
/* 0xB20 */ M504_PATH1 lbl_1_data_B20 = { 1, 0, { { 3.6e+02f, 0.0f, 3.15e+03f } } };
/* 0xB30 */ M504_PATH1 lbl_1_data_B30 = { 1, 0, { { 4e+01f, 0.0f, 3.5e+03f } } };
/* 0xB40 */ M504_PATH1 lbl_1_data_B40 = { 1, 0, { { -2e+02f, 0.0f, 3.5e+03f } } };
/* 0xB50 */ M504_PATH3 lbl_1_data_B50 = { 3, 0, { { 155.0f, 0.0f, 3.6e+02f }, { -1e+02f, 0.0f, 3.6e+02f }, { -2.6e+02f, 0.0f, 5.5e+02f } } };
/* 0xB78 */ M504_PATH1 lbl_1_data_B78 = { 1, 0, { { 1.6e+02f, 0.0f, 8.4e+02f } } };
/* 0xB88 */ M504_PATH1 lbl_1_data_B88 = { 1, 0, { { 3.6e+02f, 0.0f, 1.23e+03f } } };
/* 0xB98 */ M504_PATH1 lbl_1_data_B98 = { 1, 0, { { 3.6e+02f, 0.0f, 1.43e+03f } } };
/* 0xBA8 */ M504_PATH2 lbl_1_data_BA8 = { 2, 0, { { 0.0f, 0.0f, 1.6e+03f }, { -1.3e+02f, 0.0f, 1.85e+03f } } };
/* 0xBC4 */ M504_PATH1 lbl_1_data_BC4 = { 1, 0, { { -115.0f, 0.0f, 2.35e+03f } } };
/* 0xBD4 */ M504_PATH1 lbl_1_data_BD4 = { 1, 0, { { -3e+01f, 0.0f, 2.56e+03f } } };
/* 0xBE4 */ M504_PATH1 lbl_1_data_BE4 = { 1, 0, { { 222.0f, 0.0f, 2378.0f } } };
/* 0xBF4 */ M504_PATH1 lbl_1_data_BF4 = { 1, 0, { { 222.0f, 0.0f, 2378.0f } } };
/* 0xC04 */ M504_PATH1 lbl_1_data_C04 = { 1, 0, { { 3.2e+02f, 0.0f, 2.79e+03f } } };
/* 0xC14 */ M504_PATH1 lbl_1_data_C14 = { 1, 0, { { 3.2e+02f, 0.0f, 3.32e+03f } } };
/* 0xC24 */ M504_PATH1 lbl_1_data_C24 = { 1, 0, { { 0.0f, 0.0f, 3.32e+03f } } };
/* 0xC34 */ M504_PATH1 lbl_1_data_C34 = { 1, 0, { { 0.0f, 0.0f, 3.05e+03f } } };
/* 0xC44 */ M504_PATH1 lbl_1_data_C44 = { 1, 0, { { -3.1e+02f, 0.0f, 3.23e+03f } } };
/* 0xC54 */ M504_PATH1 lbl_1_data_C54 = { 1, 0, { { -1e+01f, 0.0f, 3.75e+03f } } };
/* 0xC64 */ M504_PATH1 lbl_1_data_C64 = { 1, 0, { { 2e+02f, 0.0f, 3.75e+03f } } };
/* 0xC74 */ M504_PATH2 lbl_1_data_C74 = { 2, 0, { { 5e+01f, 0.0f, 356.0f }, { -3e+02f, 0.0f, 356.0f } } };
/* 0xC90 */ M504_PATH1 lbl_1_data_C90 = { 1, 0, { { -1.6e+02f, 0.0f, 6.2e+02f } } };
/* 0xCA0 */ M504_PATH1 lbl_1_data_CA0 = { 1, 0, { { -1e+02f, 0.0f, 1.01e+03f } } };
/* 0xCB0 */ M504_PATH1 lbl_1_data_CB0 = { 1, 0, { { 1.6e+02f, 0.0f, 1.01e+03f } } };
/* 0xCC0 */ M504_PATH1 lbl_1_data_CC0 = { 1, 0, { { 3.6e+02f, 0.0f, 1.01e+03f } } };
/* 0xCD0 */ M504_PATH1 lbl_1_data_CD0 = { 1, 0, { { 3.6e+02f, 0.0f, 1.3e+03f } } };
/* 0xCE0 */ M504_PATH1 lbl_1_data_CE0 = { 1, 0, { { 1.4e+02f, 0.0f, 1.68e+03f } } };
/* 0xCF0 */ M504_PATH1 lbl_1_data_CF0 = { 1, 0, { { -9e+01f, 0.0f, 1.63e+03f } } };
/* 0xD00 */ M504_PATH1 lbl_1_data_D00 = { 1, 0, { { -2.4e+02f, 0.0f, 1.49e+03f } } };
/* 0xD10 */ M504_PATH1 lbl_1_data_D10 = { 1, 0, { { -2.4e+02f, 0.0f, 1.86e+03f } } };
/* 0xD20 */ M504_PATH1 lbl_1_data_D20 = { 1, 0, { { -3.1e+02f, 0.0f, 2.04e+03f } } };
/* 0xD30 */ M504_PATH1 lbl_1_data_D30 = { 1, 0, { { -2e+02f, 0.0f, 2.25e+03f } } };
/* 0xD40 */ M504_PATH1 lbl_1_data_D40 = { 1, 0, { { -1.1e+02f, 0.0f, 2.55e+03f } } };
/* 0xD50 */ M504_PATH1 lbl_1_data_D50 = { 1, 0, { { 9e+01f, 0.0f, 2.37e+03f } } };
/* 0xD60 */ M504_PATH1 lbl_1_data_D60 = { 1, 0, { { 1.4e+02f, 0.0f, 2.19e+03f } } };
/* 0xD70 */ M504_PATH1 lbl_1_data_D70 = { 1, 0, { { 2.6e+02f, 0.0f, 2.52e+03f } } };
/* 0xD80 */ M504_PATH1 lbl_1_data_D80 = { 1, 0, { { 3.6e+02f, 0.0f, 2.69e+03f } } };
/* 0xD90 */ M504_PATH1 lbl_1_data_D90 = { 1, 0, { { 3.6e+02f, 0.0f, 3.03e+03f } } };
/* 0xDA0 */ M504_PATH1 lbl_1_data_DA0 = { 1, 0, { { 3.6e+02f, 0.0f, 3.4e+03f } } };
/* 0xDB0 */ M504_PATH1 lbl_1_data_DB0 = { 1, 0, { { 0.0f, 0.0f, 3.4e+03f } } };
/* 0xDC0 */ M504_PATH1 lbl_1_data_DC0 = { 1, 0, { { 0.0f, 0.0f, 3.05e+03f } } };
/* 0xDD0 */ M504_PATH1 lbl_1_data_DD0 = { 1, 0, { { -3.3e+02f, 0.0f, 3.05e+03f } } };
/* 0xDE0 */ M504_PATH1 lbl_1_data_DE0 = { 1, 0, { { -2e+01f, 0.0f, 3.51e+03f } } };
/* 0xDF0 */ M504_PATH1 lbl_1_data_DF0 = { 1, 0, { { 2.8e+02f, 0.0f, 3.51e+03f } } };
/* 0xE00 */ M504_PATH2 lbl_1_data_E00 = { 2, 0, { { -2e+01f, 0.0f, 3.2e+02f }, { -3.6e+02f, 0.0f, 7.1e+02f } } };
/* 0xE1C */ M504_PATH1 lbl_1_data_E1C = { 1, 0, { { -3.6e+02f, 0.0f, 1.25e+03f } } };
/* 0xE2C */ M504_PATH1 lbl_1_data_E2C = { 1, 0, { { -3.6e+02f, 0.0f, 1.25e+03f } } };
/* 0xE3C */ M504_PATH1 lbl_1_data_E3C = { 1, 0, { { -3.6e+02f, 0.0f, 1.4e+03f } } };
/* 0xE4C */ M504_PATH3 lbl_1_data_E4C = { 3, 0, { { -3.6e+02f, 0.0f, 1.55e+03f }, { 1e+02f, 0.0f, 1.55e+03f }, { 1e+02f, 0.0f, 9.5e+02f } } };
/* 0xE74 */ M504_PATH1 lbl_1_data_E74 = { 1, 0, { { 1e+02f, 0.0f, 1.25e+03f } } };
/* 0xE84 */ M504_PATH1 lbl_1_data_E84 = { 1, 0, { { 1e+02f, 0.0f, 1.42e+03f } } };
/* 0xE94 */ M504_PATH1 lbl_1_data_E94 = { 1, 0, { { 1e+02f, 0.0f, 1.67e+03f } } };
/* 0xEA4 */ M504_PATH1 lbl_1_data_EA4 = { 1, 0, { { 1e+02f, 0.0f, 1.67e+03f } } };
/* 0xEB4 */ M504_PATH1 lbl_1_data_EB4 = { 1, 0, { { -1.5e+02f, 0.0f, 1.67e+03f } } };
/* 0xEC4 */ M504_PATH1 lbl_1_data_EC4 = { 1, 0, { { -3.6e+02f, 0.0f, 1.55e+03f } } };
/* 0xED4 */ M504_PATH1 lbl_1_data_ED4 = { 1, 0, { { -1.9e+02f, 0.0f, 1.9e+03f } } };
/* 0xEE4 */ M504_PATH1 lbl_1_data_EE4 = { 1, 0, { { -4e+01f, 0.0f, 2.02e+03f } } };
/* 0xEF4 */ M504_PATH1 lbl_1_data_EF4 = { 1, 0, { { -4.0f, 0.0f, 2.36e+03f } } };
/* 0xF04 */ M504_PATH1 lbl_1_data_F04 = { 1, 0, { { -4e+01f, 0.0f, 2.56e+03f } } };
/* 0xF14 */ M504_PATH1 lbl_1_data_F14 = { 1, 0, { { 1.4e+02f, 0.0f, 2.56e+03f } } };
/* 0xF24 */ M504_PATH1 lbl_1_data_F24 = { 1, 0, { { 2.1e+02f, 0.0f, 2.34e+03f } } };
/* 0xF34 */ M504_PATH1 lbl_1_data_F34 = { 1, 0, { { 2.9e+02f, 0.0f, 2.71e+03f } } };
/* 0xF44 */ M504_PATH1 lbl_1_data_F44 = { 1, 0, { { 295.0f, 0.0f, 3.2e+03f } } };
/* 0xF54 */ M504_PATH1 lbl_1_data_F54 = { 1, 0, { { 0.0f, 0.0f, 3.2e+03f } } };
/* 0xF64 */ M504_PATH1 lbl_1_data_F64 = { 1, 0, { { 0.0f, 0.0f, 3.03e+03f } } };
/* 0xF74 */ M504_PATH1 lbl_1_data_F74 = { 1, 0, { { -3.3e+02f, 0.0f, 3.3e+03f } } };
/* 0xF84 */ M504_PATH1 lbl_1_data_F84 = { 1, 0, { { 0.0f, 0.0f, 3.67e+03f } } };
/* 0xF94 */ M504_PATH1 lbl_1_data_F94 = { 1, 0, { { -3e+02f, 0.0f, 3.4e+03f } } };
/* 0xFA4 */ M504_PATH1 lbl_1_data_FA4 = { 1, 0, { { 5e+01f, 0.0f, 3.6e+02f } } };
/* 0xFB4 */ M504_PATH1 lbl_1_data_FB4 = { 1, 0, { { -2.2e+02f, 0.0f, 3.6e+02f } } };
/* 0xFC4 */ M504_PATH1 lbl_1_data_FC4 = { 1, 0, { { -2.2e+02f, 0.0f, 3.6e+02f } } };
/* 0xFD4 */ M504_PATH1 lbl_1_data_FD4 = { 1, 0, { { -2.2e+02f, 0.0f, 6.1e+02f } } };
/* 0xFE4 */ M504_PATH1 lbl_1_data_FE4 = { 1, 0, { { -6e+01f, 0.0f, 1.01e+03f } } };
/* 0xFF4 */ M504_PATH1 lbl_1_data_FF4 = { 1, 0, { { 3e+02f, 0.0f, 1.01e+03f } } };
/* 0x1004 */ M504_PATH1 lbl_1_data_1004 = { 1, 0, { { 3e+02f, 0.0f, 1.01e+03f } } };
/* 0x1014 */ M504_PATH1 lbl_1_data_1014 = { 1, 0, { { 3e+02f, 0.0f, 1.28e+03f } } };
/* 0x1024 */ M504_PATH1 lbl_1_data_1024 = { 1, 0, { { 1.6e+02f, 0.0f, 1.64e+03f } } };
/* 0x1034 */ M504_PATH2 lbl_1_data_1034 = { 2, 0, { { 3.6e+02f, 0.0f, 1.64e+03f }, { 3.6e+02f, 0.0f, 1.82e+03f } } };
/* 0x1050 */ M504_PATH3 lbl_1_data_1050 = { 3, 0, { { 3.6e+02f, 0.0f, 2.22e+03f }, { -2.5e+02f, 0.0f, 2.22e+03f }, { -2.5e+02f, 0.0f, 1.59e+03f } } };
/* 0x1078 */ M504_PATH1 lbl_1_data_1078 = { 1, 0, { { -2.5e+02f, 0.0f, 1.86e+03f } } };
/* 0x1088 */ M504_PATH1 lbl_1_data_1088 = { 1, 0, { { -5e+01f, 0.0f, 2.08e+03f } } };
/* 0x1098 */ M504_PATH1 lbl_1_data_1098 = { 1, 0, { { -5e+01f, 0.0f, 2.32e+03f } } };
/* 0x10A8 */ M504_PATH1 lbl_1_data_10A8 = { 1, 0, { { -3.6e+02f, 0.0f, 2.32e+03f } } };
/* 0x10B8 */ M504_PATH1 lbl_1_data_10B8 = { 1, 0, { { -1.3e+02f, 0.0f, 2.5e+03f } } };
/* 0x10C8 */ M504_PATH1 lbl_1_data_10C8 = { 1, 0, { { 3.6e+02f, 0.0f, 2.67e+03f } } };
/* 0x10D8 */ M504_PATH1 lbl_1_data_10D8 = { 1, 0, { { 3.6e+02f, 0.0f, 3.2e+03f } } };
/* 0x10E8 */ M504_PATH1 lbl_1_data_10E8 = { 1, 0, { { 3.6e+02f, 0.0f, 3.3e+03f } } };
/* 0x10F8 */ M504_PATH1 lbl_1_data_10F8 = { 1, 0, { { -5e+01f, 0.0f, 3.3e+03f } } };
/* 0x1108 */ M504_PATH1 lbl_1_data_1108 = { 1, 0, { { -5e+01f, 0.0f, 3.3e+03f } } };
/* 0x1118 */ M504_PATH1 lbl_1_data_1118 = { 1, 0, { { -5e+01f, 0.0f, 3.54e+03f } } };
/* 0x1128 */ M504_PATH1 lbl_1_data_1128 = { 1, 0, { { 1.3e+02f, 0.0f, 3.7e+03f } } };
/* 0x1138 */ M504_PATH1 lbl_1_data_1138 = { 1, 0, { { 1.3e+02f, 0.0f, 3.3e+03f } } };
/* 0x1148 */ M504_PATH4 lbl_1_data_1148 = { 4, 0, { { 3.6e+02f, 0.0f, 3e+02f }, { 3.6e+02f, 0.0f, 7e+02f }, { -3.6e+02f, 0.0f, 7e+02f }, { -3.6e+02f, 0.0f, 3.3e+02f } } };
/* 0x117C */ M504_PATH1 lbl_1_data_117C = { 1, 0, { { -3.6e+02f, 0.0f, 6.5e+02f } } };
/* 0x118C */ M504_PATH1 lbl_1_data_118C = { 1, 0, { { -1.8e+02f, 0.0f, 1.01e+03f } } };
/* 0x119C */ M504_PATH1 lbl_1_data_119C = { 1, 0, { { 9e+01f, 0.0f, 1.01e+03f } } };
/* 0x11AC */ M504_PATH1 lbl_1_data_11AC = { 1, 0, { { 2.2e+02f, 0.0f, 1.01e+03f } } };
/* 0x11BC */ M504_PATH1 lbl_1_data_11BC = { 1, 0, { { 2.2e+02f, 0.0f, 1.3e+03f } } };
/* 0x11CC */ M504_PATH1 lbl_1_data_11CC = { 1, 0, { { 1.5e+02f, 0.0f, 1.7e+03f } } };
/* 0x11DC */ M504_PATH1 lbl_1_data_11DC = { 1, 0, { { -1.1e+02f, 0.0f, 1.7e+03f } } };
/* 0x11EC */ M504_PATH1 lbl_1_data_11EC = { 1, 0, { { -2.7e+02f, 0.0f, 1.49e+03f } } };
/* 0x11FC */ M504_PATH1 lbl_1_data_11FC = { 1, 0, { { -2.7e+02f, 0.0f, 1.78e+03f } } };
/* 0x120C */ M504_PATH1 lbl_1_data_120C = { 1, 0, { { -2.7e+02f, 0.0f, 2e+03f } } };
/* 0x121C */ M504_PATH1 lbl_1_data_121C = { 1, 0, { { -2.7e+02f, 0.0f, 2.36e+03f } } };
/* 0x122C */ M504_PATH1 lbl_1_data_122C = { 1, 0, { { -55.0f, 0.0f, 2.56e+03f } } };
/* 0x123C */ M504_PATH1 lbl_1_data_123C = { 1, 0, { { 1.2e+02f, 0.0f, 2.22e+03f } } };
/* 0x124C */ M504_PATH1 lbl_1_data_124C = { 1, 0, { { 1.2e+02f, 0.0f, 2.22e+03f } } };
/* 0x125C */ M504_PATH1 lbl_1_data_125C = { 1, 0, { { 3.6e+02f, 0.0f, 2.22e+03f } } };
/* 0x126C */ M504_PATH4 lbl_1_data_126C = { 4, 0, { { 3.6e+02f, 0.0f, 1.64e+03f }, { -1.5e+02f, 0.0f, 1.64e+03f }, { -1.5e+02f, 0.0f, 2.47e+03f }, { 3.6e+02f, 0.0f, 2.47e+03f } } };
/* 0x12A0 */ M504_PATH1 lbl_1_data_12A0 = { 1, 0, { { 3.6e+02f, 0.0f, 2.9e+03f } } };
/* 0x12B0 */ M504_PATH1 lbl_1_data_12B0 = { 1, 0, { { 3.6e+02f, 0.0f, 3.3e+03f } } };
/* 0x12C0 */ M504_PATH1 lbl_1_data_12C0 = { 1, 0, { { -1e+02f, 0.0f, 3.3e+03f } } };
/* 0x12D0 */ M504_PATH1 lbl_1_data_12D0 = { 1, 0, { { 0.0f, 0.0f, 3.25e+03f } } };
/* 0x12E0 */ M504_PATH1 lbl_1_data_12E0 = { 1, 0, { { 0.0f, 0.0f, 3.62e+03f } } };
/* 0x12F0 */ M504_PATH1 lbl_1_data_12F0 = { 1, 0, { { 1.1e+02f, 0.0f, 3.62e+03f } } };
/* 0x1300 */ M504_PATH1 lbl_1_data_1300 = { 1, 0, { { -1.9e+02f, 0.0f, 3.62e+03f } } };
/* 0x1310 */ M504_PATH5 lbl_1_data_1310 = { 5, 0, { { 3.6e+02f, 0.0f, 3.3e+02f }, { 3.6e+02f, 0.0f, 7.7e+02f }, { 1.6e+02f, 0.0f, 8.4e+02f }, { -6e+01f, 0.0f, 8.1e+02f }, { -2e+02f, 0.0f, 5.5e+02f } } };
/* 0x1350 */ M504_PATH1 lbl_1_data_1350 = { 1, 0, { { 0.0f, 0.0f, 8.4e+02f } } };
/* 0x1360 */ M504_PATH1 lbl_1_data_1360 = { 1, 0, { { 2.6e+02f, 0.0f, 8.5e+02f } } };
/* 0x1370 */ M504_PATH1 lbl_1_data_1370 = { 1, 0, { { 2.6e+02f, 0.0f, 1.1e+03f } } };
/* 0x1380 */ M504_PATH1 lbl_1_data_1380 = { 1, 0, { { 1.6e+02f, 0.0f, 1.68e+03f } } };
/* 0x1390 */ M504_PATH1 lbl_1_data_1390 = { 1, 0, { { -1.2e+02f, 0.0f, 1.68e+03f } } };
/* 0x13A0 */ M504_PATH1 lbl_1_data_13A0 = { 1, 0, { { -2.6e+02f, 0.0f, 1.49e+03f } } };
/* 0x13B0 */ M504_PATH1 lbl_1_data_13B0 = { 1, 0, { { -2.6e+02f, 0.0f, 1.8e+03f } } };
/* 0x13C0 */ M504_PATH1 lbl_1_data_13C0 = { 1, 0, { { -2.6e+02f, 0.0f, 2.48e+03f } } };
/* 0x13D0 */ M504_PATH1 lbl_1_data_13D0 = { 1, 0, { { -2.8e+02f, 0.0f, 2.92e+03f } } };
/* 0x13E0 */ M504_PATH1 lbl_1_data_13E0 = { 1, 0, { { -2.8e+02f, 0.0f, 2.92e+03f } } };
/* 0x13F0 */ M504_PATH1 lbl_1_data_13F0 = { 1, 0, { { -1.3e+02f, 0.0f, 3.15e+03f } } };
/* 0x1400 */ M504_PATH3 lbl_1_data_1400 = { 3, 0, { { 2.3e+02f, 0.0f, 3.15e+03f }, { 2.3e+02f, 0.0f, 2.56e+03f }, { 5e+01f, 0.0f, 2.2e+03f } } };
/* 0x1428 */ M504_PATH1 lbl_1_data_1428 = { 1, 0, { { 5e+01f, 0.0f, 2.54e+03f } } };
/* 0x1438 */ M504_PATH1 lbl_1_data_1438 = { 1, 0, { { 3.6e+02f, 0.0f, 2.6e+03f } } };
/* 0x1448 */ M504_PATH1 lbl_1_data_1448 = { 1, 0, { { 3.6e+02f, 0.0f, 3.07e+03f } } };
/* 0x1458 */ M504_PATH1 lbl_1_data_1458 = { 1, 0, { { -6e+01f, 0.0f, 3.07e+03f } } };
/* 0x1468 */ M504_PATH1 lbl_1_data_1468 = { 1, 0, { { 1.8e+02f, 0.0f, 3.15e+03f } } };
/* 0x1478 */ M504_PATH1 lbl_1_data_1478 = { 1, 0, { { 3.6e+02f, 0.0f, 3.3e+03f } } };
/* 0x1488 */ M504_PATH1 lbl_1_data_1488 = { 1, 0, { { 0.0f, 0.0f, 3.3e+03f } } };
/* 0x1498 */ M504_PATH1 lbl_1_data_1498 = { 1, 0, { { 0.0f, 0.0f, 3.05e+03f } } };
/* 0x14A8 */ M504_PATH1 lbl_1_data_14A8 = { 1, 0, { { -2.9e+02f, 0.0f, 3.22e+03f } } };
/* 0x14B8 */ M504_PATH1 lbl_1_data_14B8 = { 1, 0, { { 0.0f, 0.0f, 3.4e+03f } } };
/* 0x14C8 */ M504_PATH1 lbl_1_data_14C8 = { 1, 0, { { 3.5e+02f, 0.0f, 3.5e+03f } } };
/* 0x14D8 */ M504_PATH1 lbl_1_data_14D8 = { 1, 0, { { 2.2e+02f, 0.0f, 2.5e+02f } } };
/* 0x14E8 */ M504_PATH1 lbl_1_data_14E8 = { 1, 0, { { 3.6e+02f, 0.0f, 5e+02f } } };
/* 0x14F8 */ M504_PATH3 lbl_1_data_14F8 = { 3, 0, { { 3.6e+02f, 0.0f, 7e+02f }, { -1.6e+02f, 0.0f, 7e+02f }, { -1.6e+02f, 0.0f, 3e+02f } } };
/* 0x1520 */ M504_PATH1 lbl_1_data_1520 = { 1, 0, { { -1.6e+02f, 0.0f, 6.5e+02f } } };
/* 0x1530 */ M504_PATH1 lbl_1_data_1530 = { 1, 0, { { -1.6e+02f, 0.0f, 9e+02f } } };
/* 0x1540 */ M504_PATH1 lbl_1_data_1540 = { 1, 0, { { 1.5e+02f, 0.0f, 9e+02f } } };
/* 0x1550 */ M504_PATH1 lbl_1_data_1550 = { 1, 0, { { 3e+02f, 0.0f, 9e+02f } } };
/* 0x1560 */ M504_PATH1 lbl_1_data_1560 = { 1, 0, { { 3e+02f, 0.0f, 1.3e+03f } } };
/* 0x1570 */ M504_PATH1 lbl_1_data_1570 = { 1, 0, { { 7e+01f, 0.0f, 1.37e+03f } } };
/* 0x1580 */ M504_PATH1 lbl_1_data_1580 = { 1, 0, { { 1.4e+02f, 0.0f, 1.58e+03f } } };
/* 0x1590 */ M504_PATH1 lbl_1_data_1590 = { 1, 0, { { 1.4e+02f, 0.0f, 1.69e+03f } } };
/* 0x15A0 */ M504_PATH1 lbl_1_data_15A0 = { 1, 0, { { -9e+01f, 0.0f, 1.69e+03f } } };
/* 0x15B0 */ M504_PATH1 lbl_1_data_15B0 = { 1, 0, { { -1.8e+02f, 0.0f, 1.49e+03f } } };
/* 0x15C0 */ M504_PATH1 lbl_1_data_15C0 = { 1, 0, { { -1.8e+02f, 0.0f, 1.82e+03f } } };
/* 0x15D0 */ M504_PATH1 lbl_1_data_15D0 = { 1, 0, { { -2.9e+02f, 0.0f, 2.16e+03f } } };
/* 0x15E0 */ M504_PATH1 lbl_1_data_15E0 = { 1, 0, { { -1.1e+02f, 0.0f, 2.3e+03f } } };
/* 0x15F0 */ M504_PATH1 lbl_1_data_15F0 = { 1, 0, { { 3.6e+02f, 0.0f, 2.78e+03f } } };
/* 0x1600 */ M504_PATH1 lbl_1_data_1600 = { 1, 0, { { 3.6e+02f, 0.0f, 3.03e+03f } } };
/* 0x1610 */ M504_PATH1 lbl_1_data_1610 = { 1, 0, { { 3.6e+02f, 0.0f, 3.03e+03f } } };
/* 0x1620 */ M504_PATH1 lbl_1_data_1620 = { 1, 0, { { 0.0f, 0.0f, 3.03e+03f } } };
/* 0x1630 */ M504_PATH1 lbl_1_data_1630 = { 1, 0, { { 0.0f, 0.0f, 3.03e+03f } } };
/* 0x1640 */ M504_PATH1 lbl_1_data_1640 = { 1, 0, { { 3.6e+02f, 0.0f, 3.03e+03f } } };
/* 0x1650 */ M504_PATH2 lbl_1_data_1650 = { 2, 0, { { 3.6e+02f, 0.0f, 3.43e+03f }, { 0.0f, 0.0f, 3.43e+03f } } };
/* 0x166C */ M504_PATH1 lbl_1_data_166C = { 1, 0, { { -3.3e+02f, 0.0f, 3.43e+03f } } };
/* 0x167C */ M504_PATH2 lbl_1_data_167C = { 2, 0, { { 8e+01f, 0.0f, 3.5e+02f }, { -1.3e+02f, 0.0f, 3.5e+02f } } };
/* 0x1698 */ M504_PATH1 lbl_1_data_1698 = { 1, 0, { { -3.6e+02f, 0.0f, 3.5e+02f } } };
/* 0x16A8 */ M504_PATH1 lbl_1_data_16A8 = { 1, 0, { { 7e+01f, 0.0f, 7.3e+02f } } };
/* 0x16B8 */ M504_PATH1 lbl_1_data_16B8 = { 1, 0, { { 7e+01f, 0.0f, 1.1e+03f } } };
/* 0x16C8 */ M504_PATH1 lbl_1_data_16C8 = { 1, 0, { { 7e+01f, 0.0f, 1.23e+03f } } };
/* 0x16D8 */ M504_PATH1 lbl_1_data_16D8 = { 1, 0, { { 3e+02f, 0.0f, 1.38e+03f } } };
/* 0x16E8 */ M504_PATH1 lbl_1_data_16E8 = { 1, 0, { { 2.1e+02f, 0.0f, 1.71e+03f } } };
/* 0x16F8 */ M504_PATH1 lbl_1_data_16F8 = { 1, 0, { { -6e+01f, 0.0f, 1.71e+03f } } };
/* 0x1708 */ M504_PATH1 lbl_1_data_1708 = { 1, 0, { { -2e+02f, 0.0f, 1.49e+03f } } };
/* 0x1718 */ M504_PATH1 lbl_1_data_1718 = { 1, 0, { { -2e+02f, 0.0f, 1.88e+03f } } };
/* 0x1728 */ M504_PATH1 lbl_1_data_1728 = { 1, 0, { { -3.1e+02f, 0.0f, 1.88e+03f } } };
/* 0x1738 */ M504_PATH1 lbl_1_data_1738 = { 1, 0, { { -3.1e+02f, 0.0f, 2.13e+03f } } };
/* 0x1748 */ M504_PATH1 lbl_1_data_1748 = { 1, 0, { { -1.5e+02f, 0.0f, 2.43e+03f } } };
/* 0x1758 */ M504_PATH1 lbl_1_data_1758 = { 1, 0, { { 9e+01f, 0.0f, 2.43e+03f } } };
/* 0x1768 */ M504_PATH1 lbl_1_data_1768 = { 1, 0, { { 2.2e+02f, 0.0f, 2.4e+03f } } };
/* 0x1778 */ M504_PATH1 lbl_1_data_1778 = { 1, 0, { { 2.2e+02f, 0.0f, 2.2e+03f } } };
/* 0x1788 */ M504_PATH2 lbl_1_data_1788 = { 2, 0, { { 3.6e+02f, 0.0f, 2.2e+03f }, { 3.6e+02f, 0.0f, 2.77e+03f } } };
/* 0x17A4 */ M504_PATH1 lbl_1_data_17A4 = { 1, 0, { { 3.6e+02f, 0.0f, 3.07e+03f } } };
/* 0x17B4 */ M504_PATH1 lbl_1_data_17B4 = { 1, 0, { { 3.6e+02f, 0.0f, 3.07e+03f } } };
/* 0x17C4 */ M504_PATH1 lbl_1_data_17C4 = { 1, 0, { { 0.0f, 0.0f, 3.07e+03f } } };
/* 0x17D4 */ M504_PATH1 lbl_1_data_17D4 = { 1, 0, { { 0.0f, 0.0f, 3.07e+03f } } };
/* 0x17E4 */ M504_PATH1 lbl_1_data_17E4 = { 1, 0, { { -3.6e+02f, 0.0f, 3.24e+03f } } };
/* 0x17F4 */ M504_PATH1 lbl_1_data_17F4 = { 1, 0, { { 0.0f, 0.0f, 3.47e+03f } } };
/* 0x1804 */ M504_PATH1 lbl_1_data_1804 = { 1, 0, { { -2.9e+02f, 0.0f, 3.47e+03f } } };
/* 0x1814 */ M504_PATH1 lbl_1_data_1814 = { 1, 0, { { 3e+01f, 0.0f, 3.6e+02f } } };
/* 0x1824 */ M504_PATH1 lbl_1_data_1824 = { 1, 0, { { -2.2e+02f, 0.0f, 3.6e+02f } } };
/* 0x1834 */ M504_PATH1 lbl_1_data_1834 = { 1, 0, { { -2.2e+02f, 0.0f, 3.6e+02f } } };
/* 0x1844 */ M504_PATH1 lbl_1_data_1844 = { 1, 0, { { -2.2e+02f, 0.0f, 6.5e+02f } } };
/* 0x1854 */ M504_PATH1 lbl_1_data_1854 = { 1, 0, { { -2.2e+02f, 0.0f, 6.5e+02f } } };
/* 0x1864 */ M504_PATH1 lbl_1_data_1864 = { 1, 0, { { 1.2e+02f, 0.0f, 8.3e+02f } } };
/* 0x1874 */ M504_PATH1 lbl_1_data_1874 = { 1, 0, { { 3.6e+02f, 0.0f, 9.3e+02f } } };
/* 0x1884 */ M504_PATH1 lbl_1_data_1884 = { 1, 0, { { 3.6e+02f, 0.0f, 1.27e+03f } } };
/* 0x1894 */ M504_PATH1 lbl_1_data_1894 = { 1, 0, { { 7e+01f, 0.0f, 1.27e+03f } } };
/* 0x18A4 */ M504_PATH1 lbl_1_data_18A4 = { 1, 0, { { 3.2e+02f, 0.0f, 1.48e+03f } } };
/* 0x18B4 */ M504_PATH1 lbl_1_data_18B4 = { 1, 0, { { 1.5e+02f, 0.0f, 1.71e+03f } } };
/* 0x18C4 */ M504_PATH1 lbl_1_data_18C4 = { 1, 0, { { -9e+01f, 0.0f, 1.71e+03f } } };
/* 0x18D4 */ M504_PATH1 lbl_1_data_18D4 = { 1, 0, { { -3.1e+02f, 0.0f, 1.56e+03f } } };
/* 0x18E4 */ M504_PATH1 lbl_1_data_18E4 = { 1, 0, { { -2.3e+02f, 0.0f, 1.92e+03f } } };
/* 0x18F4 */ M504_PATH1 lbl_1_data_18F4 = { 1, 0, { { -4e+01f, 0.0f, 2.01e+03f } } };
/* 0x1904 */ M504_PATH1 lbl_1_data_1904 = { 1, 0, { { -2.3e+02f, 0.0f, 2.15e+03f } } };
/* 0x1914 */ M504_PATH1 lbl_1_data_1914 = { 1, 0, { { -3.6e+02f, 0.0f, 2.32e+03f } } };
/* 0x1924 */ M504_PATH1 lbl_1_data_1924 = { 1, 0, { { -1.4e+02f, 0.0f, 2.5e+03f } } };
/* 0x1934 */ M504_PATH1 lbl_1_data_1934 = { 1, 0, { { 2.2e+02f, 0.0f, 2.37e+03f } } };
/* 0x1944 */ M504_PATH1 lbl_1_data_1944 = { 1, 0, { { 2.2e+02f, 0.0f, 2.62e+03f } } };
/* 0x1954 */ M504_PATH1 lbl_1_data_1954 = { 1, 0, { { 3.6e+02f, 0.0f, 2.84e+03f } } };
/* 0x1964 */ M504_PATH1 lbl_1_data_1964 = { 1, 0, { { 3.6e+02f, 0.0f, 3.14e+03f } } };
/* 0x1974 */ M504_PATH1 lbl_1_data_1974 = { 1, 0, { { 7e+01f, 0.0f, 3.5e+03f } } };
/* 0x1984 */ M504_PATH1 lbl_1_data_1984 = { 1, 0, { { -1.9e+02f, 0.0f, 3.5e+03f } } };
/* 0x1994 */ M504_PATH2 lbl_1_data_1994 = { 2, 0, { { 2e+01f, 0.0f, 3.6e+02f }, { -3.6e+02f, 0.0f, 5.5e+02f } } };
/* 0x19B0 */ M504_PATH1 lbl_1_data_19B0 = { 1, 0, { { -2.2e+02f, 0.0f, 9.2e+02f } } };
/* 0x19C0 */ M504_PATH1 lbl_1_data_19C0 = { 1, 0, { { 3.6e+02f, 0.0f, 1.02e+03f } } };
/* 0x19D0 */ M504_PATH1 lbl_1_data_19D0 = { 1, 0, { { 1.6e+02f, 0.0f, 1.23e+03f } } };
/* 0x19E0 */ M504_PATH1 lbl_1_data_19E0 = { 1, 0, { { 1.6e+02f, 0.0f, 1.64e+03f } } };
/* 0x19F0 */ M504_PATH1 lbl_1_data_19F0 = { 1, 0, { { -7e+01f, 0.0f, 1.64e+03f } } };
/* 0x1A00 */ M504_PATH1 lbl_1_data_1A00 = { 1, 0, { { -3.5e+02f, 0.0f, 1.6e+03f } } };
/* 0x1A10 */ M504_PATH1 lbl_1_data_1A10 = { 1, 0, { { -3.5e+02f, 0.0f, 1.36e+03f } } };
/* 0x1A20 */ M504_PATH6 lbl_1_data_1A20 = { 6, 0, { { -3.5e+02f, 0.0f, 1.36e+03f }, { -3.5e+02f, 0.0f, 9.8e+02f }, { 9e+01f, 0.0f, 9.8e+02f }, { 9e+01f, 0.0f, 1.63e+03f }, { -7e+01f, 0.0f, 1.63e+03f }, { -7e+01f, 0.0f, 2.11e+03f } } };
/* 0x1A6C */ M504_PATH1 lbl_1_data_1A6C = { 1, 0, { { -7e+01f, 0.0f, 2.4e+03f } } };
/* 0x1A7C */ M504_PATH1 lbl_1_data_1A7C = { 1, 0, { { -3.6e+02f, 0.0f, 2.4e+03f } } };
/* 0x1A8C */ M504_PATH1 lbl_1_data_1A8C = { 1, 0, { { -8e+01f, 0.0f, 2.53e+03f } } };
/* 0x1A9C */ M504_PATH1 lbl_1_data_1A9C = { 1, 0, { { 215.0f, 0.0f, 2.36e+03f } } };
/* 0x1AAC */ M504_PATH1 lbl_1_data_1AAC = { 1, 0, { { 215.0f, 0.0f, 2.6e+03f } } };
/* 0x1ABC */ M504_PATH1 lbl_1_data_1ABC = { 1, 0, { { 3.6e+02f, 0.0f, 2.76e+03f } } };
/* 0x1ACC */ M504_PATH1 lbl_1_data_1ACC = { 1, 0, { { 3.6e+02f, 0.0f, 3.06e+03f } } };
/* 0x1ADC */ M504_PATH1 lbl_1_data_1ADC = { 1, 0, { { 3.6e+02f, 0.0f, 3.3e+03f } } };
/* 0x1AEC */ M504_PATH1 lbl_1_data_1AEC = { 1, 0, { { 0.0f, 0.0f, 3.3e+03f } } };
/* 0x1AFC */ M504_PATH1 lbl_1_data_1AFC = { 1, 0, { { 0.0f, 0.0f, 3.7e+03f } } };
/* 0x1B0C */ M504_PATH1 lbl_1_data_1B0C = { 1, 0, { { 0.0f, 0.0f, 3.9e+03f } } };
/* 0x1B1C */ M504_PATH1 lbl_1_data_1B1C = { 1, 0, { { 0.0f, 0.0f, 3.3e+03f } } };
/* 0x1B2C */ M504_PATH1 lbl_1_data_1B2C = { 1, 0, { { 0.0f, 0.0f, 3.04e+03f } } };
/* 0x1B3C */ M504_PATH1 lbl_1_data_1B3C = { 1, 0, { { 0.0f, 0.0f, 3.5e+03f } } };
/* 0x1B4C */ M504_PATH1 lbl_1_data_1B4C = { 1, 0, { { 3e+02f, 0.0f, 3.3e+03f } } };
/* 0x1B5C */ M504_PATH3 lbl_1_data_1B5C = { 3, 0, { { 3.6e+02f, 0.0f, 3.6e+02f }, { 3.6e+02f, 0.0f, 6.8e+02f }, { -3e+02f, 0.0f, 6.8e+02f } } };
/* 0x1B84 */ M504_PATH1 lbl_1_data_1B84 = { 1, 0, { { -1e+02f, 0.0f, 9.7e+02f } } };
/* 0x1B94 */ M504_PATH1 lbl_1_data_1B94 = { 1, 0, { { -1e+02f, 0.0f, 9.7e+02f } } };
/* 0x1BA4 */ M504_PATH1 lbl_1_data_1BA4 = { 1, 0, { { 2e+02f, 0.0f, 9.7e+02f } } };
/* 0x1BB4 */ M504_PATH1 lbl_1_data_1BB4 = { 1, 0, { { 3e+02f, 0.0f, 9.7e+02f } } };
/* 0x1BC4 */ M504_PATH1 lbl_1_data_1BC4 = { 1, 0, { { 3e+02f, 0.0f, 1.22e+03f } } };
/* 0x1BD4 */ M504_PATH1 lbl_1_data_1BD4 = { 1, 0, { { 3e+02f, 0.0f, 1.62e+03f } } };
/* 0x1BE4 */ M504_PATH1 lbl_1_data_1BE4 = { 1, 0, { { 3e+02f, 0.0f, 1.93e+03f } } };
/* 0x1BF4 */ M504_PATH3 lbl_1_data_1BF4 = { 3, 0, { { 3e+02f, 0.0f, 2.23e+03f }, { -1.8e+02f, 0.0f, 2.23e+03f }, { -1.8e+02f, 0.0f, 1.62e+03f } } };
/* 0x1C1C */ M504_PATH1 lbl_1_data_1C1C = { 1, 0, { { -1.8e+02f, 0.0f, 1.88e+03f } } };
/* 0x1C2C */ M504_PATH1 lbl_1_data_1C2C = { 1, 0, { { -4e+01f, 0.0f, 2.11e+03f } } };
/* 0x1C3C */ M504_PATH1 lbl_1_data_1C3C = { 1, 0, { { -4e+01f, 0.0f, 2.34e+03f } } };
/* 0x1C4C */ M504_PATH1 lbl_1_data_1C4C = { 1, 0, { { -2.3e+02f, 0.0f, 2.42e+03f } } };
/* 0x1C5C */ M504_PATH1 lbl_1_data_1C5C = { 1, 0, { { 3e+01f, 0.0f, 2.52e+03f } } };
/* 0x1C6C */ M504_PATH1 lbl_1_data_1C6C = { 1, 0, { { 3e+01f, 0.0f, 2.29e+03f } } };
/* 0x1C7C */ M504_PATH1 lbl_1_data_1C7C = { 1, 0, { { 2.4e+02f, 0.0f, 2.5e+03f } } };
/* 0x1C8C */ M504_PATH1 lbl_1_data_1C8C = { 1, 0, { { 3.5e+02f, 0.0f, 2.71e+03f } } };
/* 0x1C9C */ M504_PATH1 lbl_1_data_1C9C = { 1, 0, { { 3.5e+02f, 0.0f, 3.12e+03f } } };
/* 0x1CAC */ M504_PATH1 lbl_1_data_1CAC = { 1, 0, { { 3.5e+02f, 0.0f, 3.12e+03f } } };
/* 0x1CBC */ M504_PATH1 lbl_1_data_1CBC = { 1, 0, { { 0.0f, 0.0f, 3.05e+03f } } };
/* 0x1CCC */ M504_PATH1 lbl_1_data_1CCC = { 1, 0, { { 0.0f, 0.0f, 3.05e+03f } } };
/* 0x1CDC */ M504_PATH1 lbl_1_data_1CDC = { 1, 0, { { -2e+02f, 0.0f, 3.36e+03f } } };
/* 0x1CEC */ M504_PATH1 lbl_1_data_1CEC = { 1, 0, { { 0.0f, 0.0f, 3.67e+03f } } };
/* 0x1CFC */ M504_PATH1 lbl_1_data_1CFC = { 1, 0, { { 2.6e+02f, 0.0f, 3.4e+03f } } };
/* 0x1D0C */ M504_PATH4 lbl_1_data_1D0C = { 4, 0, { { 3.6e+02f, 0.0f, 3.6e+02f }, { 3.6e+02f, 0.0f, 6.8e+02f }, { -2.4e+02f, 0.0f, 6.8e+02f }, { -2.4e+02f, 0.0f, 4.4e+02f } } };
/* 0x1D40 */ M504_PATH1 lbl_1_data_1D40 = { 1, 0, { { -2.4e+02f, 0.0f, 8.7e+02f } } };
/* 0x1D50 */ M504_PATH2 lbl_1_data_1D50 = { 2, 0, { { 2e+02f, 0.0f, 8.7e+02f }, { 2e+02f, 0.0f, 1.06e+03f } } };
/* 0x1D6C */ M504_PATH1 lbl_1_data_1D6C = { 1, 0, { { 2e+02f, 0.0f, 1.46e+03f } } };
/* 0x1D7C */ M504_PATH1 lbl_1_data_1D7C = { 1, 0, { { -2.4e+02f, 0.0f, 1.72e+03f } } };
/* 0x1D8C */ M504_PATH1 lbl_1_data_1D8C = { 1, 0, { { -2.4e+02f, 0.0f, 1.88e+03f } } };
/* 0x1D9C */ M504_PATH2 lbl_1_data_1D9C = { 2, 0, { { -2.4e+02f, 0.0f, 1.65e+03f }, { 1.5e+02f, 0.0f, 1.65e+03f } } };
/* 0x1DB8 */ M504_PATH1 lbl_1_data_1DB8 = { 1, 0, { { -1.9e+02f, 0.0f, 1.65e+03f } } };
/* 0x1DC8 */ M504_PATH1 lbl_1_data_1DC8 = { 1, 0, { { -1.9e+02f, 0.0f, 1.5e+03f } } };
/* 0x1DD8 */ M504_PATH1 lbl_1_data_1DD8 = { 1, 0, { { -1.9e+02f, 0.0f, 1.9e+03f } } };
/* 0x1DE8 */ M504_PATH1 lbl_1_data_1DE8 = { 1, 0, { { -2.7e+02f, 0.0f, 2.22e+03f } } };
/* 0x1DF8 */ M504_PATH1 lbl_1_data_1DF8 = { 1, 0, { { -7e+01f, 0.0f, 2.48e+03f } } };
/* 0x1E08 */ M504_PATH1 lbl_1_data_1E08 = { 1, 0, { { -5e+01f, 0.0f, 2.55e+03f } } };
/* 0x1E18 */ M504_PATH1 lbl_1_data_1E18 = { 1, 0, { { 2.2e+02f, 0.0f, 2.35e+03f } } };
/* 0x1E28 */ M504_PATH1 lbl_1_data_1E28 = { 1, 0, { { 2.2e+02f, 0.0f, 2.35e+03f } } };
/* 0x1E38 */ M504_PATH1 lbl_1_data_1E38 = { 1, 0, { { 3.6e+02f, 0.0f, 2.7e+03f } } };
/* 0x1E48 */ M504_PATH1 lbl_1_data_1E48 = { 1, 0, { { 3.6e+02f, 0.0f, 2.7e+03f } } };
/* 0x1E58 */ M504_PATH1 lbl_1_data_1E58 = { 1, 0, { { 3.6e+02f, 0.0f, 3.07e+03f } } };
/* 0x1E68 */ M504_PATH1 lbl_1_data_1E68 = { 1, 0, { { 3.6e+02f, 0.0f, 3.3e+03f } } };
/* 0x1E78 */ M504_PATH1 lbl_1_data_1E78 = { 1, 0, { { 5e+01f, 0.0f, 3.3e+03f } } };
/* 0x1E88 */ M504_PATH1 lbl_1_data_1E88 = { 1, 0, { { 5e+01f, 0.0f, 3.3e+03f } } };
/* 0x1E98 */ M504_PATH1 lbl_1_data_1E98 = { 1, 0, { { 5e+01f, 0.0f, 3.04e+03f } } };
/* 0x1EA8 */ M504_PATH1 lbl_1_data_1EA8 = { 1, 0, { { 5e+01f, 0.0f, 3.7e+03f } } };
/* 0x1EB8 */ M504_PATH1 lbl_1_data_1EB8 = { 1, 0, { { 2.5e+02f, 0.0f, 3.2e+03f } } };
/* 0x1EC8 */ M504_PATH3 lbl_1_data_1EC8 = { 3, 0, { { 3.6e+02f, 0.0f, 3.6e+02f }, { 3.6e+02f, 0.0f, 6.8e+02f }, { -2.7e+02f, 0.0f, 8.9e+02f } } };
/* 0x1EF0 */ M504_PATH1 lbl_1_data_1EF0 = { 1, 0, { { 1e+01f, 0.0f, 8.7e+02f } } };
/* 0x1F00 */ M504_PATH1 lbl_1_data_1F00 = { 1, 0, { { 2.9e+02f, 0.0f, 9.1e+02f } } };
/* 0x1F10 */ M504_PATH1 lbl_1_data_1F10 = { 1, 0, { { 2.9e+02f, 0.0f, 1.21e+03f } } };
/* 0x1F20 */ M504_PATH1 lbl_1_data_1F20 = { 1, 0, { { 1.6e+02f, 0.0f, 1.71e+03f } } };
/* 0x1F30 */ M504_PATH1 lbl_1_data_1F30 = { 1, 0, { { -8e+01f, 0.0f, 1.71e+03f } } };
/* 0x1F40 */ M504_PATH1 lbl_1_data_1F40 = { 1, 0, { { -3.5e+02f, 0.0f, 1.44e+03f } } };
/* 0x1F50 */ M504_PATH1 lbl_1_data_1F50 = { 1, 0, { { -3.5e+02f, 0.0f, 1.44e+03f } } };
/* 0x1F60 */ M504_PATH1 lbl_1_data_1F60 = { 1, 0, { { -3e+02f, 0.0f, 1.83e+03f } } };
/* 0x1F70 */ M504_PATH1 lbl_1_data_1F70 = { 1, 0, { { -3e+02f, 0.0f, 2.06e+03f } } };
/* 0x1F80 */ M504_PATH1 lbl_1_data_1F80 = { 1, 0, { { -4e+01f, 0.0f, 2.06e+03f } } };
/* 0x1F90 */ M504_PATH1 lbl_1_data_1F90 = { 1, 0, { { -4e+01f, 0.0f, 2.35e+03f } } };
/* 0x1FA0 */ M504_PATH1 lbl_1_data_1FA0 = { 1, 0, { { -4e+01f, 0.0f, 2.55e+03f } } };
/* 0x1FB0 */ M504_PATH1 lbl_1_data_1FB0 = { 1, 0, { { -3.3e+02f, 0.0f, 2.55e+03f } } };
/* 0x1FC0 */ M504_PATH2 lbl_1_data_1FC0 = { 2, 0, { { -3.3e+02f, 0.0f, 2.25e+03f }, { 3.6e+02f, 0.0f, 2.25e+03f } } };
/* 0x1FDC */ M504_PATH1 lbl_1_data_1FDC = { 1, 0, { { 3.6e+02f, 0.0f, 2.25e+03f } } };
/* 0x1FEC */ M504_PATH1 lbl_1_data_1FEC = { 1, 0, { { 3.6e+02f, 0.0f, 2.76e+03f } } };
/* 0x1FFC */ M504_PATH1 lbl_1_data_1FFC = { 1, 0, { { 3.6e+02f, 0.0f, 3.02e+03f } } };
/* 0x200C */ M504_PATH1 lbl_1_data_200C = { 1, 0, { { 3.6e+02f, 0.0f, 3.22e+03f } } };
/* 0x201C */ M504_PATH1 lbl_1_data_201C = { 1, 0, { { 1e+02f, 0.0f, 3.22e+03f } } };
/* 0x202C */ M504_PATH1 lbl_1_data_202C = { 1, 0, { { -1.8e+02f, 0.0f, 3.22e+03f } } };
/* 0x203C */ M504_PATH1 lbl_1_data_203C = { 1, 0, { { -1.8e+02f, 0.0f, 3.48e+03f } } };
/* 0x204C */ M504_PATH1 lbl_1_data_204C = { 1, 0, { { 1.1e+02f, 0.0f, 3.65e+03f } } };
/* 0x205C */ M504_PATH1 lbl_1_data_205C = { 1, 0, { { 2.6e+02f, 0.0f, 3.34e+03f } } };
/* 0x206C */ M504_PATH2 lbl_1_data_206C = { 2, 0, { { -2e+01f, 0.0f, 4.8e+02f }, { -3.6e+02f, 0.0f, 4.8e+02f } } };
/* 0x2088 */ M504_PATH1 lbl_1_data_2088 = { 1, 0, { { -15.0f, 0.0f, 9.2e+02f } } };
/* 0x2098 */ M504_PATH1 lbl_1_data_2098 = { 1, 0, { { -1.3e+02f, 0.0f, 1.01e+03f } } };
/* 0x20A8 */ M504_PATH1 lbl_1_data_20A8 = { 1, 0, { { 1e+02f, 0.0f, 8.2e+02f } } };
/* 0x20B8 */ M504_PATH1 lbl_1_data_20B8 = { 1, 0, { { -1.3e+02f, 0.0f, 1.01e+03f } } };
/* 0x20C8 */ M504_PATH1 lbl_1_data_20C8 = { 1, 0, { { -1e+02f, 0.0f, 8.2e+02f } } };
/* 0x20D8 */ M504_PATH1 lbl_1_data_20D8 = { 1, 0, { { 3.6e+02f, 0.0f, 8.3e+02f } } };
/* 0x20E8 */ M504_PATH1 lbl_1_data_20E8 = { 1, 0, { { 3.6e+02f, 0.0f, 5.5e+02f } } };
/* 0x20F8 */ M504_PATH5 lbl_1_data_20F8 = { 5, 0, { { 3.6e+02f, 0.0f, 2.9e+02f }, { -1e+02f, 0.0f, 2.9e+02f }, { -1e+02f, 0.0f, 1.01e+03f }, { 8e+01f, 0.0f, 1.01e+03f }, { 8e+01f, 0.0f, 1.25e+03f } } };
/* 0x2138 */ M504_PATH1 lbl_1_data_2138 = { 1, 0, { { 3.6e+02f, 0.0f, 1.25e+03f } } };
/* 0x2148 */ M504_PATH1 lbl_1_data_2148 = { 1, 0, { { 2.3e+02f, 0.0f, 1625.0f } } };
/* 0x2158 */ M504_PATH1 lbl_1_data_2158 = { 1, 0, { { -5e+01f, 0.0f, 1625.0f } } };
/* 0x2168 */ M504_PATH1 lbl_1_data_2168 = { 1, 0, { { 2.3e+02f, 0.0f, 1625.0f } } };
/* 0x2178 */ M504_PATH1 lbl_1_data_2178 = { 1, 0, { { 3.6e+02f, 0.0f, 1625.0f } } };
/* 0x2188 */ M504_PATH2 lbl_1_data_2188 = { 2, 0, { { -6e+01f, 0.0f, 1625.0f }, { -3.2e+02f, 0.0f, 1615.0f } } };
/* 0x21A4 */ M504_PATH1 lbl_1_data_21A4 = { 1, 0, { { -3.5e+02f, 0.0f, 1.34e+03f } } };
/* 0x21B4 */ M504_PATH5 lbl_1_data_21B4 = { 5, 0, { { -3.5e+02f, 0.0f, 1e+03f }, { 65.0f, 0.0f, 1e+03f }, { 65.0f, 0.0f, 1.71e+03f }, { -8e+01f, 0.0f, 1.71e+03f }, { -8e+01f, 0.0f, 1.49e+03f } } };
/* 0x21F4 */ M504_PATH1 lbl_1_data_21F4 = { 1, 0, { { 1.5e+02f, 0.0f, 1.49e+03f } } };
/* 0x2204 */ M504_PATH3 lbl_1_data_2204 = { 3, 0, { { 1.5e+02f, 0.0f, 1.71e+03f }, { -55.0f, 0.0f, 1.71e+03f }, { -135.0f, 0.0f, 2.32e+03f } } };
/* 0x222C */ M504_PATH1 lbl_1_data_222C = { 1, 0, { { -3.6e+02f, 0.0f, 2.32e+03f } } };
/* 0x223C */ M504_PATH1 lbl_1_data_223C = { 1, 0, { { 2.2e+02f, 0.0f, 2.19e+03f } } };
/* 0x224C */ M504_PATH1 lbl_1_data_224C = { 1, 0, { { 2.2e+02f, 0.0f, 2.61e+03f } } };
/* 0x225C */ M504_PATH1 lbl_1_data_225C = { 1, 0, { { 2.2e+02f, 0.0f, 2.19e+03f } } };
/* 0x226C */ M504_PATH1 lbl_1_data_226C = { 1, 0, { { 2.2e+02f, 0.0f, 2.34e+03f } } };
/* 0x227C */ M504_PATH1 lbl_1_data_227C = { 1, 0, { { 5e+01f, 0.0f, 2.56e+03f } } };
/* 0x228C */ M504_PATH1 lbl_1_data_228C = { 1, 0, { { 3.6e+02f, 0.0f, 2.56e+03f } } };
/* 0x229C */ M504_PATH1 lbl_1_data_229C = { 1, 0, { { 3.6e+02f, 0.0f, 2.56e+03f } } };
/* 0x22AC */ M504_PATH1 lbl_1_data_22AC = { 1, 0, { { 3.6e+02f, 0.0f, 3.1e+03f } } };
/* 0x22BC */ M504_PATH1 lbl_1_data_22BC = { 1, 0, { { 262.0f, 0.0f, 3.23e+03f } } };
/* 0x22CC */ M504_PATH1 lbl_1_data_22CC = { 1, 0, { { 0.0f, 0.0f, 3.23e+03f } } };
/* 0x22DC */ M504_PATH1 lbl_1_data_22DC = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x22EC */ M504_PATH1 lbl_1_data_22EC = { 1, 0, { { -2.6e+02f, 0.0f, 3.05e+03f } } };
/* 0x22FC */ M504_PATH1 lbl_1_data_22FC = { 1, 0, { { 0.0f, 0.0f, 3.5e+03f } } };
/* 0x230C */ M504_PATH1 lbl_1_data_230C = { 1, 0, { { 3.2e+02f, 0.0f, 3.42e+03f } } };
/* 0x231C */ M504_PATH3 lbl_1_data_231C = { 3, 0, { { 3e+02f, 0.0f, 7.2e+02f }, { -3.6e+02f, 0.0f, 7.2e+02f }, { -3.6e+02f, 0.0f, 1.5e+02f } } };
/* 0x2344 */ M504_PATH1 lbl_1_data_2344 = { 1, 0, { { -3.6e+02f, 0.0f, 4.3e+02f } } };
/* 0x2354 */ M504_PATH1 lbl_1_data_2354 = { 1, 0, { { -3.5e+02f, 0.0f, 1.26e+03f } } };
/* 0x2364 */ M504_PATH1 lbl_1_data_2364 = { 1, 0, { { -3.5e+02f, 0.0f, 1.3e+03f } } };
/* 0x2374 */ M504_PATH3 lbl_1_data_2374 = { 3, 0, { { -3.5e+02f, 0.0f, 1.54e+03f }, { 1e+02f, 0.0f, 1.54e+03f }, { 1e+02f, 0.0f, 9.5e+02f } } };
/* 0x239C */ M504_PATH1 lbl_1_data_239C = { 1, 0, { { 1e+02f, 0.0f, 1.18e+03f } } };
/* 0x23AC */ M504_PATH3 lbl_1_data_23AC = { 3, 0, { { -3.5e+02f, 0.0f, 1.54e+03f }, { 1e+02f, 0.0f, 1.54e+03f }, { 1e+02f, 0.0f, 9.5e+02f } } };
/* 0x23D4 */ M504_PATH1 lbl_1_data_23D4 = { 1, 0, { { 3e+02f, 0.0f, 1.01e+03f } } };
/* 0x23E4 */ M504_PATH1 lbl_1_data_23E4 = { 1, 0, { { 1e+02f, 0.0f, 1.4e+03f } } };
/* 0x23F4 */ M504_PATH1 lbl_1_data_23F4 = { 1, 0, { { 3.6e+02f, 0.0f, 1.4e+03f } } };
/* 0x2404 */ M504_PATH1 lbl_1_data_2404 = { 1, 0, { { 3.6e+02f, 0.0f, 1.56e+03f } } };
/* 0x2414 */ M504_PATH1 lbl_1_data_2414 = { 1, 0, { { 0.0f, 0.0f, 1.56e+03f } } };
/* 0x2424 */ M504_PATH1 lbl_1_data_2424 = { 1, 0, { { 0.0f, 0.0f, 1.69e+03f } } };
/* 0x2434 */ M504_PATH1 lbl_1_data_2434 = { 1, 0, { { -1.9e+02f, 0.0f, 1.49e+03f } } };
/* 0x2444 */ M504_PATH1 lbl_1_data_2444 = { 1, 0, { { 0.0f, 0.0f, 1.69e+03f } } };
/* 0x2454 */ M504_PATH1 lbl_1_data_2454 = { 1, 0, { { 1.7e+02f, 0.0f, 1.69e+03f } } };
/* 0x2464 */ M504_PATH1 lbl_1_data_2464 = { 1, 0, { { -2e+02f, 0.0f, 1.49e+03f } } };
/* 0x2474 */ M504_PATH1 lbl_1_data_2474 = { 1, 0, { { -3.6e+02f, 0.0f, 1.49e+03f } } };
/* 0x2484 */ M504_PATH1 lbl_1_data_2484 = { 1, 0, { { -3e+02f, 0.0f, 1.9e+03f } } };
/* 0x2494 */ M504_PATH1 lbl_1_data_2494 = { 1, 0, { { -45.0f, 0.0f, 1.9e+03f } } };
/* 0x24A4 */ M504_PATH1 lbl_1_data_24A4 = { 1, 0, { { -45.0f, 0.0f, 2.1e+03f } } };
/* 0x24B4 */ M504_PATH1 lbl_1_data_24B4 = { 1, 0, { { -2.4e+02f, 0.0f, 2.33e+03f } } };
/* 0x24C4 */ M504_PATH1 lbl_1_data_24C4 = { 1, 0, { { -3.6e+02f, 0.0f, 2.35e+03f } } };
/* 0x24D4 */ M504_PATH1 lbl_1_data_24D4 = { 1, 0, { { -4e+01f, 0.0f, 2.55e+03f } } };
/* 0x24E4 */ M504_PATH1 lbl_1_data_24E4 = { 1, 0, { { 1.8e+02f, 0.0f, 2.34e+03f } } };
/* 0x24F4 */ M504_PATH1 lbl_1_data_24F4 = { 1, 0, { { 2e+02f, 0.0f, 2.63e+03f } } };
/* 0x2504 */ M504_PATH1 lbl_1_data_2504 = { 1, 0, { { 3e+02f, 0.0f, 3.1e+03f } } };
/* 0x2514 */ M504_PATH1 lbl_1_data_2514 = { 1, 0, { { 0.0f, 0.0f, 3.1e+03f } } };
/* 0x2524 */ M504_PATH1 lbl_1_data_2524 = { 1, 0, { { 3e+02f, 0.0f, 3.1e+03f } } };
/* 0x2534 */ M504_PATH1 lbl_1_data_2534 = { 1, 0, { { 188.0f, 0.0f, 3.27e+03f } } };
/* 0x2544 */ M504_PATH1 lbl_1_data_2544 = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x2554 */ M504_PATH1 lbl_1_data_2554 = { 1, 0, { { 2.6e+02f, 0.0f, 3.05e+03f } } };
/* 0x2564 */ M504_PATH1 lbl_1_data_2564 = { 1, 0, { { 0.0f, 0.0f, 3.5e+03f } } };
/* 0x2574 */ M504_PATH1 lbl_1_data_2574 = { 1, 0, { { -3.2e+02f, 0.0f, 3.42e+03f } } };
/* 0x2584 */ M504_PATH2 lbl_1_data_2584 = { 2, 0, { { -1e+02f, 0.0f, 3.3e+02f }, { -2.9e+02f, 0.0f, 105.0f } } };
/* 0x25A0 */ M504_PATH1 lbl_1_data_25A0 = { 1, 0, { { -2.9e+02f, 0.0f, 4.4e+02f } } };
/* 0x25B0 */ M504_PATH1 lbl_1_data_25B0 = { 1, 0, { { -3.5e+02f, 0.0f, 1.3e+03f } } };
/* 0x25C0 */ M504_PATH1 lbl_1_data_25C0 = { 1, 0, { { -3.5e+02f, 0.0f, 1.46e+03f } } };
/* 0x25D0 */ M504_PATH3 lbl_1_data_25D0 = { 3, 0, { { -3.5e+02f, 0.0f, 1.55e+03f }, { 3.5e+02f, 0.0f, 1.55e+03f }, { 3.5e+02f, 0.0f, 9.5e+02f } } };
/* 0x25F8 */ M504_PATH1 lbl_1_data_25F8 = { 1, 0, { { 3.5e+02f, 0.0f, 7.1e+02f } } };
/* 0x2608 */ M504_PATH2 lbl_1_data_2608 = { 2, 0, { { 7e+01f, 0.0f, 7.1e+02f }, { 7e+01f, 0.0f, 1.37e+03f } } };
/* 0x2624 */ M504_PATH1 lbl_1_data_2624 = { 1, 0, { { 3.6e+02f, 0.0f, 1.37e+03f } } };
/* 0x2634 */ M504_PATH2 lbl_1_data_2634 = { 2, 0, { { 7e+01f, 0.0f, 7.1e+02f }, { 7e+01f, 0.0f, 1.37e+03f } } };
/* 0x2650 */ M504_PATH1 lbl_1_data_2650 = { 1, 0, { { 1.8e+02f, 0.0f, 1.36e+03f } } };
/* 0x2660 */ M504_PATH1 lbl_1_data_2660 = { 1, 0, { { 3.2e+02f, 0.0f, 1.9e+03f } } };
/* 0x2670 */ M504_PATH1 lbl_1_data_2670 = { 1, 0, { { 3.2e+02f, 0.0f, 2.03e+03f } } };
/* 0x2680 */ M504_PATH4 lbl_1_data_2680 = { 4, 0, { { 3.2e+02f, 0.0f, 2.24e+03f }, { -1.2e+02f, 0.0f, 2.24e+03f }, { -1.2e+02f, 0.0f, 1.6e+03f }, { -3.6e+02f, 0.0f, 1.6e+03f } } };
/* 0x26B4 */ M504_PATH1 lbl_1_data_26B4 = { 1, 0, { { -2e+02f, 0.0f, 1.82e+03f } } };
/* 0x26C4 */ M504_PATH1 lbl_1_data_26C4 = { 1, 0, { { -55.0f, 0.0f, 2.06e+03f } } };
/* 0x26D4 */ M504_PATH1 lbl_1_data_26D4 = { 1, 0, { { -55.0f, 0.0f, 2.32e+03f } } };
/* 0x26E4 */ M504_PATH1 lbl_1_data_26E4 = { 1, 0, { { -2.6e+02f, 0.0f, 2.68e+03f } } };
/* 0x26F4 */ M504_PATH1 lbl_1_data_26F4 = { 1, 0, { { -3e+02f, 0.0f, 3.06e+03f } } };
/* 0x2704 */ M504_PATH4 lbl_1_data_2704 = { 4, 0, { { -2e+02f, 0.0f, 3.15e+03f }, { 2e+02f, 0.0f, 3.15e+03f }, { 2e+02f, 0.0f, 2.52e+03f }, { 9e+01f, 0.0f, 2.2e+03f } } };
/* 0x2738 */ M504_PATH1 lbl_1_data_2738 = { 1, 0, { { 3.5e+02f, 0.0f, 2.7e+03f } } };
/* 0x2748 */ M504_PATH1 lbl_1_data_2748 = { 1, 0, { { 3.5e+02f, 0.0f, 2.7e+03f } } };
/* 0x2758 */ M504_PATH1 lbl_1_data_2758 = { 1, 0, { { 1.6e+02f, 0.0f, 3.05e+03f } } };
/* 0x2768 */ M504_PATH1 lbl_1_data_2768 = { 1, 0, { { 3.5e+02f, 0.0f, 3.3e+03f } } };
/* 0x2778 */ M504_PATH1 lbl_1_data_2778 = { 1, 0, { { 0.0f, 0.0f, 3.3e+03f } } };
/* 0x2788 */ M504_PATH1 lbl_1_data_2788 = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x2798 */ M504_PATH1 lbl_1_data_2798 = { 1, 0, { { 2.6e+02f, 0.0f, 3.05e+03f } } };
/* 0x27A8 */ M504_PATH1 lbl_1_data_27A8 = { 1, 0, { { 0.0f, 0.0f, 3.8e+03f } } };
/* 0x27B8 */ M504_PATH1 lbl_1_data_27B8 = { 1, 0, { { -2e+02f, 0.0f, 3.7e+03f } } };
/* 0x27C8 */ M504_PATH2 lbl_1_data_27C8 = { 2, 0, { { 3e+01f, 0.0f, 3.6e+02f }, { -3.6e+02f, 0.0f, 1e+02f } } };
/* 0x27E4 */ M504_PATH1 lbl_1_data_27E4 = { 1, 0, { { -3.6e+02f, 0.0f, 4.4e+02f } } };
/* 0x27F4 */ M504_PATH1 lbl_1_data_27F4 = { 1, 0, { { -1.2e+02f, 0.0f, 9.8e+02f } } };
/* 0x2804 */ M504_PATH1 lbl_1_data_2804 = { 1, 0, { { 1.7e+02f, 0.0f, 9.8e+02f } } };
/* 0x2814 */ M504_PATH1 lbl_1_data_2814 = { 1, 0, { { 3.6e+02f, 0.0f, 9.8e+02f } } };
/* 0x2824 */ M504_PATH1 lbl_1_data_2824 = { 1, 0, { { 3.6e+02f, 0.0f, 1.28e+03f } } };
/* 0x2834 */ M504_PATH1 lbl_1_data_2834 = { 1, 0, { { 1.4e+02f, 0.0f, 1.71e+03f } } };
/* 0x2844 */ M504_PATH1 lbl_1_data_2844 = { 1, 0, { { -25.0f, 0.0f, 1.49e+03f } } };
/* 0x2854 */ M504_PATH1 lbl_1_data_2854 = { 1, 0, { { 1.4e+02f, 0.0f, 1.71e+03f } } };
/* 0x2864 */ M504_PATH1 lbl_1_data_2864 = { 1, 0, { { 135.0f, 0.0f, 1.46e+03f } } };
/* 0x2874 */ M504_PATH2 lbl_1_data_2874 = { 2, 0, { { -25.0f, 0.0f, 1.49e+03f }, { -2e+02f, 0.0f, 1.49e+03f } } };
/* 0x2890 */ M504_PATH1 lbl_1_data_2890 = { 1, 0, { { -2.2e+02f, 0.0f, 1.85e+03f } } };
/* 0x28A0 */ M504_PATH1 lbl_1_data_28A0 = { 1, 0, { { -3e+02f, 0.0f, 1.95e+03f } } };
/* 0x28B0 */ M504_PATH1 lbl_1_data_28B0 = { 1, 0, { { -5e+01f, 0.0f, 2.17e+03f } } };
/* 0x28C0 */ M504_PATH1 lbl_1_data_28C0 = { 1, 0, { { -5e+01f, 0.0f, 2.17e+03f } } };
/* 0x28D0 */ M504_PATH1 lbl_1_data_28D0 = { 1, 0, { { -2.8e+02f, 0.0f, 2.37e+03f } } };
/* 0x28E0 */ M504_PATH1 lbl_1_data_28E0 = { 1, 0, { { -5e+01f, 0.0f, 2.17e+03f } } };
/* 0x28F0 */ M504_PATH1 lbl_1_data_28F0 = { 1, 0, { { -1.9e+02f, 0.0f, 2.17e+03f } } };
/* 0x2900 */ M504_PATH2 lbl_1_data_2900 = { 2, 0, { { -2.8e+02f, 0.0f, 2.37e+03f }, { -5e+01f, 0.0f, 2.56e+03f } } };
/* 0x291C */ M504_PATH1 lbl_1_data_291C = { 1, 0, { { 2e+02f, 0.0f, 2.56e+03f } } };
/* 0x292C */ M504_PATH1 lbl_1_data_292C = { 1, 0, { { 2.2e+02f, 0.0f, 2.35e+03f } } };
/* 0x293C */ M504_PATH1 lbl_1_data_293C = { 1, 0, { { 2.2e+02f, 0.0f, 2.7e+03f } } };
/* 0x294C */ M504_PATH1 lbl_1_data_294C = { 1, 0, { { 2.7e+02f, 0.0f, 3.25e+03f } } };
/* 0x295C */ M504_PATH1 lbl_1_data_295C = { 1, 0, { { -3e+01f, 0.0f, 3.2e+03f } } };
/* 0x296C */ M504_PATH1 lbl_1_data_296C = { 1, 0, { { -2.4e+02f, 0.0f, 3.16e+03f } } };
/* 0x297C */ M504_PATH1 lbl_1_data_297C = { 1, 0, { { -2.4e+02f, 0.0f, 3.44e+03f } } };
/* 0x298C */ M504_PATH1 lbl_1_data_298C = { 1, 0, { { 118.0f, 0.0f, 3437.0f } } };
/* 0x299C */ M504_PATH1 lbl_1_data_299C = { 1, 0, { { 0.0f, 0.0f, 3.75e+03f } } };
/* 0x29AC */ M504_PATH1 lbl_1_data_29AC = { 1, 0, { { -5e+01f, 0.0f, 3.05e+03f } } };
/* 0x29BC */ M504_PATH1 lbl_1_data_29BC = { 1, 0, { { 2.6e+02f, 0.0f, 3.05e+03f } } };
/* 0x29CC */ M504_PATH1 lbl_1_data_29CC = { 1, 0, { { 0.0f, 0.0f, 3.5e+03f } } };
/* 0x29DC */ M504_PATH1 lbl_1_data_29DC = { 1, 0, { { -2e+02f, 0.0f, 3.5e+03f } } };
/* 0x29EC */ M504_PATH1 lbl_1_data_29EC = { 1, 0, { { 2.2e+02f, 0.0f, 2.5e+02f } } };
/* 0x29FC */ M504_PATH1 lbl_1_data_29FC = { 1, 0, { { 345.0f, 0.0f, 5.4e+02f } } };
/* 0x2A0C */ M504_PATH3 lbl_1_data_2A0C = { 3, 0, { { 345.0f, 0.0f, 7.1e+02f }, { -1.6e+02f, 0.0f, 7.1e+02f }, { -1.6e+02f, 0.0f, 3e+02f } } };
/* 0x2A34 */ M504_PATH1 lbl_1_data_2A34 = { 1, 0, { { -1.6e+02f, 0.0f, 5.5e+02f } } };
/* 0x2A44 */ M504_PATH1 lbl_1_data_2A44 = { 1, 0, { { -1.3e+02f, 0.0f, 9.5e+02f } } };
/* 0x2A54 */ M504_PATH1 lbl_1_data_2A54 = { 1, 0, { { 1.6e+02f, 0.0f, 9.5e+02f } } };
/* 0x2A64 */ M504_PATH1 lbl_1_data_2A64 = { 1, 0, { { 2.5e+02f, 0.0f, 9.5e+02f } } };
/* 0x2A74 */ M504_PATH1 lbl_1_data_2A74 = { 1, 0, { { 2.5e+02f, 0.0f, 1.25e+03f } } };
/* 0x2A84 */ M504_PATH1 lbl_1_data_2A84 = { 1, 0, { { 7e+01f, 0.0f, 1.39e+03f } } };
/* 0x2A94 */ M504_PATH1 lbl_1_data_2A94 = { 1, 0, { { 2.8e+02f, 0.0f, 1.58e+03f } } };
/* 0x2AA4 */ M504_PATH1 lbl_1_data_2AA4 = { 1, 0, { { 7e+01f, 0.0f, 1.39e+03f } } };
/* 0x2AB4 */ M504_PATH1 lbl_1_data_2AB4 = { 1, 0, { { 2.2e+02f, 0.0f, 1.39e+03f } } };
/* 0x2AC4 */ M504_PATH1 lbl_1_data_2AC4 = { 1, 0, { { 3.4e+02f, 0.0f, 1.66e+03f } } };
/* 0x2AD4 */ M504_PATH1 lbl_1_data_2AD4 = { 1, 0, { { 3.4e+02f, 0.0f, 1.9e+03f } } };
/* 0x2AE4 */ M504_PATH3 lbl_1_data_2AE4 = { 3, 0, { { 3.4e+02f, 0.0f, 2.2e+03f }, { -2.5e+02f, 0.0f, 2.2e+03f }, { -2.5e+02f, 0.0f, 1.58e+03f } } };
/* 0x2B0C */ M504_PATH1 lbl_1_data_2B0C = { 1, 0, { { -2.5e+02f, 0.0f, 1.84e+03f } } };
/* 0x2B1C */ M504_PATH1 lbl_1_data_2B1C = { 1, 0, { { -4e+01f, 0.0f, 2.09e+03f } } };
/* 0x2B2C */ M504_PATH1 lbl_1_data_2B2C = { 1, 0, { { -1.5e+02f, 0.0f, 2.3e+03f } } };
/* 0x2B3C */ M504_PATH1 lbl_1_data_2B3C = { 1, 0, { { -3.6e+02f, 0.0f, 2.3e+03f } } };
/* 0x2B4C */ M504_PATH1 lbl_1_data_2B4C = { 1, 0, { { -8e+01f, 0.0f, 2.45e+03f } } };
/* 0x2B5C */ M504_PATH1 lbl_1_data_2B5C = { 1, 0, { { -3.6e+02f, 0.0f, 2.3e+03f } } };
/* 0x2B6C */ M504_PATH1 lbl_1_data_2B6C = { 1, 0, { { -2.4e+02f, 0.0f, 2.3e+03f } } };
/* 0x2B7C */ M504_PATH2 lbl_1_data_2B7C = { 2, 0, { { 6e+01f, 0.0f, 2355.0f }, { 2e+02f, 0.0f, 2355.0f } } };
/* 0x2B98 */ M504_PATH1 lbl_1_data_2B98 = { 1, 0, { { 325.0f, 0.0f, 2.2e+03f } } };
/* 0x2BA8 */ M504_PATH1 lbl_1_data_2BA8 = { 1, 0, { { 3.6e+02f, 0.0f, 3.25e+03f } } };
/* 0x2BB8 */ M504_PATH1 lbl_1_data_2BB8 = { 1, 0, { { 0.0f, 0.0f, 3.25e+03f } } };
/* 0x2BC8 */ M504_PATH1 lbl_1_data_2BC8 = { 1, 0, { { 0.0f, 0.0f, 3.25e+03f } } };
/* 0x2BD8 */ M504_PATH1 lbl_1_data_2BD8 = { 1, 0, { { 0.0f, 0.0f, 3.69e+03f } } };
/* 0x2BE8 */ M504_PATH1 lbl_1_data_2BE8 = { 1, 0, { { 1.7e+02f, 0.0f, 3.62e+03f } } };
/* 0x2BF8 */ M504_PATH1 lbl_1_data_2BF8 = { 1, 0, { { -2e+01f, 0.0f, 3.82e+03f } } };
/* 0x2C08 */ M504_PATH5 lbl_1_data_2C08 = { 5, 0, { { 3.5e+02f, 0.0f, 3e+02f }, { 3.5e+02f, 0.0f, 6.4e+02f }, { 1.3e+02f, 0.0f, 8.2e+02f }, { -1.4e+02f, 0.0f, 7.4e+02f }, { -3e+02f, 0.0f, 385.0f } } };
/* 0x2C48 */ M504_PATH1 lbl_1_data_2C48 = { 1, 0, { { -7e+01f, 0.0f, 575.0f } } };
/* 0x2C58 */ M504_PATH1 lbl_1_data_2C58 = { 1, 0, { { -7e+01f, 0.0f, 1.01e+03f } } };
/* 0x2C68 */ M504_PATH1 lbl_1_data_2C68 = { 1, 0, { { 2e+02f, 0.0f, 1.01e+03f } } };
/* 0x2C78 */ M504_PATH1 lbl_1_data_2C78 = { 1, 0, { { 3.2e+02f, 0.0f, 1.01e+03f } } };
/* 0x2C88 */ M504_PATH1 lbl_1_data_2C88 = { 1, 0, { { 3.2e+02f, 0.0f, 1.27e+03f } } };
/* 0x2C98 */ M504_PATH1 lbl_1_data_2C98 = { 1, 0, { { 1.5e+02f, 0.0f, 1.71e+03f } } };
/* 0x2CA8 */ M504_PATH1 lbl_1_data_2CA8 = { 1, 0, { { -8e+01f, 0.0f, 1.53e+03f } } };
/* 0x2CB8 */ M504_PATH1 lbl_1_data_2CB8 = { 1, 0, { { 1.5e+02f, 0.0f, 1.71e+03f } } };
/* 0x2CC8 */ M504_PATH1 lbl_1_data_2CC8 = { 1, 0, { { 285.0f, 0.0f, 1.64e+03f } } };
/* 0x2CD8 */ M504_PATH1 lbl_1_data_2CD8 = { 1, 0, { { -2e+02f, 0.0f, 1.49e+03f } } };
/* 0x2CE8 */ M504_PATH1 lbl_1_data_2CE8 = { 1, 0, { { -2e+02f, 0.0f, 1.79e+03f } } };
/* 0x2CF8 */ M504_PATH1 lbl_1_data_2CF8 = { 1, 0, { { -3e+02f, 0.0f, 2.09e+03f } } };
/* 0x2D08 */ M504_PATH1 lbl_1_data_2D08 = { 1, 0, { { -1e+02f, 0.0f, 2.37e+03f } } };
/* 0x2D18 */ M504_PATH1 lbl_1_data_2D18 = { 1, 0, { { -5e+01f, 0.0f, 2.56e+03f } } };
/* 0x2D28 */ M504_PATH1 lbl_1_data_2D28 = { 1, 0, { { -3.2e+02f, 0.0f, 2.56e+03f } } };
/* 0x2D38 */ M504_PATH2 lbl_1_data_2D38 = { 2, 0, { { -3.2e+02f, 0.0f, 2.3e+03f }, { 2.2e+02f, 0.0f, 2.3e+03f } } };
/* 0x2D54 */ M504_PATH1 lbl_1_data_2D54 = { 1, 0, { { 3.5e+02f, 0.0f, 2.12e+03f } } };
/* 0x2D64 */ M504_PATH1 lbl_1_data_2D64 = { 1, 0, { { 3.6e+02f, 0.0f, 3e+03f } } };
/* 0x2D74 */ M504_PATH1 lbl_1_data_2D74 = { 1, 0, { { 1e+02f, 0.0f, 3.2e+03f } } };
/* 0x2D84 */ M504_PATH1 lbl_1_data_2D84 = { 1, 0, { { -1e+01f, 0.0f, 3.23e+03f } } };
/* 0x2D94 */ M504_PATH1 lbl_1_data_2D94 = { 1, 0, { { 1.9e+02f, 0.0f, 3.33e+03f } } };
/* 0x2DA4 */ M504_PATH1 lbl_1_data_2DA4 = { 1, 0, { { 2e+01f, 0.0f, 3.74e+03f } } };
/* 0x2DB4 */ M504_PATH1 lbl_1_data_2DB4 = { 1, 0, { { 135.0f, 0.0f, 3.62e+03f } } };
/* 0x2DC4 */ M504_PATH1 lbl_1_data_2DC4 = { 1, 0, { { 3e+02f, 0.0f, 3.02e+03f } } };
/* 0x2DD4 */ M504_PATH1 lbl_1_data_2DD4 = { 1, 0, { { 3e+02f, 0.0f, 3.35e+03f } } };
/* 0x2DE4 */ M504_PATH1 lbl_1_data_2DE4 = { 1, 0, { { 0.0f, 0.0f, 3.8e+03f } } };
/* 0x2DF4 */ M504_PATH1 lbl_1_data_2DF4 = { 1, 0, { { -178.0f, 0.0f, 3712.0f } } };
/* 0x2E04 */ M504_NODE1 lbl_1_data_2E04 = { (M504_PATH *)&lbl_1_data_528, NULL, 1, 0, { (M504_NODE *)&lbl_1_data_4040 } };
/* 0x2E14 */ M504_NODE6 lbl_1_data_2E14 = { (M504_PATH *)&lbl_1_data_528, NULL, 6, 0, { (M504_NODE *)&lbl_1_data_2ED4, (M504_NODE *)&lbl_1_data_2F60, (M504_NODE *)&lbl_1_data_2FF8, (M504_NODE *)&lbl_1_data_3094, (M504_NODE *)&lbl_1_data_3124, (M504_NODE *)&lbl_1_data_31A4 } };
/* 0x2E38 */ M504_NODE12 lbl_1_data_2E38 = { (M504_PATH *)&lbl_1_data_528, NULL, 12, 0, { (M504_NODE *)&lbl_1_data_3224, (M504_NODE *)&lbl_1_data_32E4, (M504_NODE *)&lbl_1_data_33A4, (M504_NODE *)&lbl_1_data_3464, (M504_NODE *)&lbl_1_data_3524, (M504_NODE *)&lbl_1_data_35E4, (M504_NODE *)&lbl_1_data_36A4, (M504_NODE *)&lbl_1_data_3764, (M504_NODE *)&lbl_1_data_3824, (M504_NODE *)&lbl_1_data_38E4, (M504_NODE *)&lbl_1_data_39A4, (M504_NODE *)&lbl_1_data_3A64 } };
/* 0x2E74 */ M504_NODE12 lbl_1_data_2E74 = { (M504_PATH *)&lbl_1_data_528, NULL, 12, 0, { (M504_NODE *)&lbl_1_data_3224, (M504_NODE *)&lbl_1_data_32E4, (M504_NODE *)&lbl_1_data_33A4, (M504_NODE *)&lbl_1_data_3464, (M504_NODE *)&lbl_1_data_3524, (M504_NODE *)&lbl_1_data_35E4, (M504_NODE *)&lbl_1_data_36A4, (M504_NODE *)&lbl_1_data_3764, (M504_NODE *)&lbl_1_data_3824, (M504_NODE *)&lbl_1_data_38E4, (M504_NODE *)&lbl_1_data_39A4, (M504_NODE *)&lbl_1_data_3A64 } };
/* 0x2EB0 */ M504_NODE6 lbl_1_data_2EB0 = { (M504_PATH *)&lbl_1_data_528, NULL, 6, 0, { (M504_NODE *)&lbl_1_data_3B24, (M504_NODE *)&lbl_1_data_3C40, (M504_NODE *)&lbl_1_data_3D5C, (M504_NODE *)&lbl_1_data_3E40, (M504_NODE *)&lbl_1_data_3F48, (M504_NODE *)&lbl_1_data_4040 } };
/* 0x2ED4 */ M504_NODE1 lbl_1_data_2ED4 = { (M504_PATH *)&lbl_1_data_548, (M504_PATH *)&lbl_1_data_564, 1, 0, { (M504_NODE *)&lbl_1_data_2EE4 } };
/* 0x2EE4 */ M504_NODE3 lbl_1_data_2EE4 = { (M504_PATH *)&lbl_1_data_574, (M504_PATH *)&lbl_1_data_584, 3, 0, { (M504_NODE *)&lbl_1_data_2EFC, (M504_NODE *)&lbl_1_data_2F88, (M504_NODE *)&lbl_1_data_3020 } };
/* 0x2EFC */ M504_NODE1 lbl_1_data_2EFC = { (M504_PATH *)&lbl_1_data_594, (M504_PATH *)&lbl_1_data_5A4, 1, 0, { (M504_NODE *)&lbl_1_data_2F0C } };
/* 0x2F0C */ M504_NODE2 lbl_1_data_2F0C = { (M504_PATH *)&lbl_1_data_5B4, (M504_PATH *)&lbl_1_data_5C4, 2, 0, { (M504_NODE *)&lbl_1_data_2F20, (M504_NODE *)&lbl_1_data_3044 } };
/* 0x2F20 */ M504_NODE1 lbl_1_data_2F20 = { (M504_PATH *)&lbl_1_data_5D4, (M504_PATH *)&lbl_1_data_5E4, 1, 0, { (M504_NODE *)&lbl_1_data_2F30 } };
/* 0x2F30 */ M504_NODE1 lbl_1_data_2F30 = { (M504_PATH *)&lbl_1_data_5F4, (M504_PATH *)&lbl_1_data_604, 1, 0, { (M504_NODE *)&lbl_1_data_2F40 } };
/* 0x2F40 */ M504_NODE1 lbl_1_data_2F40 = { (M504_PATH *)&lbl_1_data_614, (M504_PATH *)&lbl_1_data_624, 1, 0, { (M504_NODE *)&lbl_1_data_2F50 } };
/* 0x2F50 */ M504_NODE1 lbl_1_data_2F50 = { (M504_PATH *)&lbl_1_data_634, (M504_PATH *)&lbl_1_data_644, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x2F60 */ M504_NODE1 lbl_1_data_2F60 = { (M504_PATH *)&lbl_1_data_654, (M504_PATH *)&lbl_1_data_670, 1, 0, { (M504_NODE *)&lbl_1_data_2F70 } };
/* 0x2F70 */ M504_NODE3 lbl_1_data_2F70 = { (M504_PATH *)&lbl_1_data_680, (M504_PATH *)&lbl_1_data_6A8, 3, 0, { (M504_NODE *)&lbl_1_data_2F88, (M504_NODE *)&lbl_1_data_2EFC, (M504_NODE *)&lbl_1_data_3020 } };
/* 0x2F88 */ M504_NODE1 lbl_1_data_2F88 = { (M504_PATH *)&lbl_1_data_6B8, (M504_PATH *)&lbl_1_data_6C8, 1, 0, { (M504_NODE *)&lbl_1_data_2F98 } };
/* 0x2F98 */ M504_NODE1 lbl_1_data_2F98 = { (M504_PATH *)&lbl_1_data_6D8, (M504_PATH *)&lbl_1_data_700, 1, 0, { (M504_NODE *)&lbl_1_data_2FA8 } };
/* 0x2FA8 */ M504_NODE1 lbl_1_data_2FA8 = { (M504_PATH *)&lbl_1_data_710, (M504_PATH *)&lbl_1_data_720, 1, 0, { (M504_NODE *)&lbl_1_data_2FB8 } };
/* 0x2FB8 */ M504_NODE1 lbl_1_data_2FB8 = { (M504_PATH *)&lbl_1_data_730, (M504_PATH *)&lbl_1_data_740, 1, 0, { (M504_NODE *)&lbl_1_data_2FC8 } };
/* 0x2FC8 */ M504_NODE1 lbl_1_data_2FC8 = { (M504_PATH *)&lbl_1_data_750, (M504_PATH *)&lbl_1_data_760, 1, 0, { (M504_NODE *)&lbl_1_data_2FD8 } };
/* 0x2FD8 */ M504_NODE1 lbl_1_data_2FD8 = { (M504_PATH *)&lbl_1_data_770, (M504_PATH *)&lbl_1_data_780, 1, 0, { (M504_NODE *)&lbl_1_data_2FE8 } };
/* 0x2FE8 */ M504_NODE1 lbl_1_data_2FE8 = { (M504_PATH *)&lbl_1_data_790, (M504_PATH *)&lbl_1_data_7A0, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x2FF8 */ M504_NODE1 lbl_1_data_2FF8 = { (M504_PATH *)&lbl_1_data_7B0, (M504_PATH *)&lbl_1_data_7CC, 1, 0, { (M504_NODE *)&lbl_1_data_3008 } };
/* 0x3008 */ M504_NODE3 lbl_1_data_3008 = { (M504_PATH *)&lbl_1_data_7DC, (M504_PATH *)&lbl_1_data_7EC, 3, 0, { (M504_NODE *)&lbl_1_data_3020, (M504_NODE *)&lbl_1_data_2EFC, (M504_NODE *)&lbl_1_data_2F88 } };
/* 0x3020 */ M504_NODE1 lbl_1_data_3020 = { (M504_PATH *)&lbl_1_data_7FC, (M504_PATH *)&lbl_1_data_80C, 1, 0, { (M504_NODE *)&lbl_1_data_3030 } };
/* 0x3030 */ M504_NODE2 lbl_1_data_3030 = { (M504_PATH *)&lbl_1_data_81C, (M504_PATH *)&lbl_1_data_838, 2, 0, { (M504_NODE *)&lbl_1_data_3044, (M504_NODE *)&lbl_1_data_2F20 } };
/* 0x3044 */ M504_NODE1 lbl_1_data_3044 = { (M504_PATH *)&lbl_1_data_848, (M504_PATH *)&lbl_1_data_858, 1, 0, { (M504_NODE *)&lbl_1_data_3054 } };
/* 0x3054 */ M504_NODE1 lbl_1_data_3054 = { (M504_PATH *)&lbl_1_data_868, (M504_PATH *)&lbl_1_data_890, 1, 0, { (M504_NODE *)&lbl_1_data_3064 } };
/* 0x3064 */ M504_NODE1 lbl_1_data_3064 = { (M504_PATH *)&lbl_1_data_8A0, (M504_PATH *)&lbl_1_data_8B0, 1, 0, { (M504_NODE *)&lbl_1_data_3074 } };
/* 0x3074 */ M504_NODE1 lbl_1_data_3074 = { (M504_PATH *)&lbl_1_data_8C0, (M504_PATH *)&lbl_1_data_8D0, 1, 0, { (M504_NODE *)&lbl_1_data_3084 } };
/* 0x3084 */ M504_NODE1 lbl_1_data_3084 = { (M504_PATH *)&lbl_1_data_8E0, (M504_PATH *)&lbl_1_data_8F0, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3094 */ M504_NODE1 lbl_1_data_3094 = { (M504_PATH *)&lbl_1_data_900, (M504_PATH *)&lbl_1_data_91C, 1, 0, { (M504_NODE *)&lbl_1_data_30A4 } };
/* 0x30A4 */ M504_NODE1 lbl_1_data_30A4 = { (M504_PATH *)&lbl_1_data_92C, (M504_PATH *)&lbl_1_data_93C, 1, 0, { (M504_NODE *)&lbl_1_data_30B4 } };
/* 0x30B4 */ M504_NODE1 lbl_1_data_30B4 = { (M504_PATH *)&lbl_1_data_94C, (M504_PATH *)&lbl_1_data_95C, 1, 0, { (M504_NODE *)&lbl_1_data_30C4 } };
/* 0x30C4 */ M504_NODE1 lbl_1_data_30C4 = { (M504_PATH *)&lbl_1_data_96C, (M504_PATH *)&lbl_1_data_97C, 1, 0, { (M504_NODE *)&lbl_1_data_30D4 } };
/* 0x30D4 */ M504_NODE1 lbl_1_data_30D4 = { (M504_PATH *)&lbl_1_data_98C, (M504_PATH *)&lbl_1_data_99C, 1, 0, { (M504_NODE *)&lbl_1_data_30E4 } };
/* 0x30E4 */ M504_NODE1 lbl_1_data_30E4 = { (M504_PATH *)&lbl_1_data_9AC, (M504_PATH *)&lbl_1_data_9BC, 1, 0, { (M504_NODE *)&lbl_1_data_30F4 } };
/* 0x30F4 */ M504_NODE1 lbl_1_data_30F4 = { (M504_PATH *)&lbl_1_data_9CC, (M504_PATH *)&lbl_1_data_9DC, 1, 0, { (M504_NODE *)&lbl_1_data_3104 } };
/* 0x3104 */ M504_NODE1 lbl_1_data_3104 = { (M504_PATH *)&lbl_1_data_9EC, (M504_PATH *)&lbl_1_data_9FC, 1, 0, { (M504_NODE *)&lbl_1_data_3114 } };
/* 0x3114 */ M504_NODE1 lbl_1_data_3114 = { (M504_PATH *)&lbl_1_data_A0C, (M504_PATH *)&lbl_1_data_A1C, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3124 */ M504_NODE1 lbl_1_data_3124 = { (M504_PATH *)&lbl_1_data_A2C, (M504_PATH *)&lbl_1_data_A48, 1, 0, { (M504_NODE *)&lbl_1_data_3134 } };
/* 0x3134 */ M504_NODE1 lbl_1_data_3134 = { (M504_PATH *)&lbl_1_data_A58, (M504_PATH *)&lbl_1_data_A68, 1, 0, { (M504_NODE *)&lbl_1_data_3144 } };
/* 0x3144 */ M504_NODE1 lbl_1_data_3144 = { (M504_PATH *)&lbl_1_data_A78, (M504_PATH *)&lbl_1_data_A88, 1, 0, { (M504_NODE *)&lbl_1_data_3154 } };
/* 0x3154 */ M504_NODE1 lbl_1_data_3154 = { (M504_PATH *)&lbl_1_data_A98, (M504_PATH *)&lbl_1_data_AC0, 1, 0, { (M504_NODE *)&lbl_1_data_3164 } };
/* 0x3164 */ M504_NODE1 lbl_1_data_3164 = { (M504_PATH *)&lbl_1_data_AD0, (M504_PATH *)&lbl_1_data_AE0, 1, 0, { (M504_NODE *)&lbl_1_data_3174 } };
/* 0x3174 */ M504_NODE1 lbl_1_data_3174 = { (M504_PATH *)&lbl_1_data_AF0, (M504_PATH *)&lbl_1_data_B00, 1, 0, { (M504_NODE *)&lbl_1_data_3184 } };
/* 0x3184 */ M504_NODE1 lbl_1_data_3184 = { (M504_PATH *)&lbl_1_data_B10, (M504_PATH *)&lbl_1_data_B20, 1, 0, { (M504_NODE *)&lbl_1_data_3194 } };
/* 0x3194 */ M504_NODE1 lbl_1_data_3194 = { (M504_PATH *)&lbl_1_data_B30, (M504_PATH *)&lbl_1_data_B40, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x31A4 */ M504_NODE1 lbl_1_data_31A4 = { (M504_PATH *)&lbl_1_data_B50, (M504_PATH *)&lbl_1_data_B78, 1, 0, { (M504_NODE *)&lbl_1_data_31B4 } };
/* 0x31B4 */ M504_NODE1 lbl_1_data_31B4 = { (M504_PATH *)&lbl_1_data_B88, (M504_PATH *)&lbl_1_data_B98, 1, 0, { (M504_NODE *)&lbl_1_data_31C4 } };
/* 0x31C4 */ M504_NODE1 lbl_1_data_31C4 = { (M504_PATH *)&lbl_1_data_BA8, (M504_PATH *)&lbl_1_data_BC4, 1, 0, { (M504_NODE *)&lbl_1_data_31D4 } };
/* 0x31D4 */ M504_NODE1 lbl_1_data_31D4 = { (M504_PATH *)&lbl_1_data_BD4, (M504_PATH *)&lbl_1_data_BE4, 1, 0, { (M504_NODE *)&lbl_1_data_31E4 } };
/* 0x31E4 */ M504_NODE1 lbl_1_data_31E4 = { (M504_PATH *)&lbl_1_data_BF4, (M504_PATH *)&lbl_1_data_C04, 1, 0, { (M504_NODE *)&lbl_1_data_31F4 } };
/* 0x31F4 */ M504_NODE1 lbl_1_data_31F4 = { (M504_PATH *)&lbl_1_data_C14, (M504_PATH *)&lbl_1_data_C24, 1, 0, { (M504_NODE *)&lbl_1_data_3204 } };
/* 0x3204 */ M504_NODE1 lbl_1_data_3204 = { (M504_PATH *)&lbl_1_data_C34, (M504_PATH *)&lbl_1_data_C44, 1, 0, { (M504_NODE *)&lbl_1_data_3214 } };
/* 0x3214 */ M504_NODE1 lbl_1_data_3214 = { (M504_PATH *)&lbl_1_data_C54, (M504_PATH *)&lbl_1_data_C64, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3224 */ M504_NODE1 lbl_1_data_3224 = { (M504_PATH *)&lbl_1_data_C74, (M504_PATH *)&lbl_1_data_C90, 1, 0, { (M504_NODE *)&lbl_1_data_3234 } };
/* 0x3234 */ M504_NODE1 lbl_1_data_3234 = { (M504_PATH *)&lbl_1_data_CA0, (M504_PATH *)&lbl_1_data_CB0, 1, 0, { (M504_NODE *)&lbl_1_data_3244 } };
/* 0x3244 */ M504_NODE1 lbl_1_data_3244 = { (M504_PATH *)&lbl_1_data_CC0, (M504_PATH *)&lbl_1_data_CD0, 1, 0, { (M504_NODE *)&lbl_1_data_3254 } };
/* 0x3254 */ M504_NODE1 lbl_1_data_3254 = { (M504_PATH *)&lbl_1_data_CE0, (M504_PATH *)&lbl_1_data_CF0, 1, 0, { (M504_NODE *)&lbl_1_data_3264 } };
/* 0x3264 */ M504_NODE1 lbl_1_data_3264 = { (M504_PATH *)&lbl_1_data_D00, (M504_PATH *)&lbl_1_data_D10, 1, 0, { (M504_NODE *)&lbl_1_data_3274 } };
/* 0x3274 */ M504_NODE1 lbl_1_data_3274 = { (M504_PATH *)&lbl_1_data_D20, (M504_PATH *)&lbl_1_data_D30, 1, 0, { (M504_NODE *)&lbl_1_data_3284 } };
/* 0x3284 */ M504_NODE1 lbl_1_data_3284 = { (M504_PATH *)&lbl_1_data_D40, (M504_PATH *)&lbl_1_data_D50, 1, 0, { (M504_NODE *)&lbl_1_data_3294 } };
/* 0x3294 */ M504_NODE1 lbl_1_data_3294 = { (M504_PATH *)&lbl_1_data_D60, (M504_PATH *)&lbl_1_data_D70, 1, 0, { (M504_NODE *)&lbl_1_data_32A4 } };
/* 0x32A4 */ M504_NODE1 lbl_1_data_32A4 = { (M504_PATH *)&lbl_1_data_D80, (M504_PATH *)&lbl_1_data_D90, 1, 0, { (M504_NODE *)&lbl_1_data_32B4 } };
/* 0x32B4 */ M504_NODE1 lbl_1_data_32B4 = { (M504_PATH *)&lbl_1_data_DA0, (M504_PATH *)&lbl_1_data_DB0, 1, 0, { (M504_NODE *)&lbl_1_data_32C4 } };
/* 0x32C4 */ M504_NODE1 lbl_1_data_32C4 = { (M504_PATH *)&lbl_1_data_DC0, (M504_PATH *)&lbl_1_data_DD0, 1, 0, { (M504_NODE *)&lbl_1_data_32D4 } };
/* 0x32D4 */ M504_NODE1 lbl_1_data_32D4 = { (M504_PATH *)&lbl_1_data_DE0, (M504_PATH *)&lbl_1_data_DF0, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x32E4 */ M504_NODE1 lbl_1_data_32E4 = { (M504_PATH *)&lbl_1_data_E00, (M504_PATH *)&lbl_1_data_E1C, 1, 0, { (M504_NODE *)&lbl_1_data_32F4 } };
/* 0x32F4 */ M504_NODE1 lbl_1_data_32F4 = { (M504_PATH *)&lbl_1_data_E2C, (M504_PATH *)&lbl_1_data_E3C, 1, 0, { (M504_NODE *)&lbl_1_data_3304 } };
/* 0x3304 */ M504_NODE1 lbl_1_data_3304 = { (M504_PATH *)&lbl_1_data_E4C, (M504_PATH *)&lbl_1_data_E74, 1, 0, { (M504_NODE *)&lbl_1_data_3314 } };
/* 0x3314 */ M504_NODE1 lbl_1_data_3314 = { (M504_PATH *)&lbl_1_data_E84, (M504_PATH *)&lbl_1_data_E94, 1, 0, { (M504_NODE *)&lbl_1_data_3324 } };
/* 0x3324 */ M504_NODE1 lbl_1_data_3324 = { (M504_PATH *)&lbl_1_data_EA4, (M504_PATH *)&lbl_1_data_EB4, 1, 0, { (M504_NODE *)&lbl_1_data_3334 } };
/* 0x3334 */ M504_NODE1 lbl_1_data_3334 = { (M504_PATH *)&lbl_1_data_EC4, (M504_PATH *)&lbl_1_data_ED4, 1, 0, { (M504_NODE *)&lbl_1_data_3344 } };
/* 0x3344 */ M504_NODE1 lbl_1_data_3344 = { (M504_PATH *)&lbl_1_data_EE4, (M504_PATH *)&lbl_1_data_EF4, 1, 0, { (M504_NODE *)&lbl_1_data_3354 } };
/* 0x3354 */ M504_NODE1 lbl_1_data_3354 = { (M504_PATH *)&lbl_1_data_F04, (M504_PATH *)&lbl_1_data_F14, 1, 0, { (M504_NODE *)&lbl_1_data_3364 } };
/* 0x3364 */ M504_NODE1 lbl_1_data_3364 = { (M504_PATH *)&lbl_1_data_F24, (M504_PATH *)&lbl_1_data_F34, 1, 0, { (M504_NODE *)&lbl_1_data_3374 } };
/* 0x3374 */ M504_NODE1 lbl_1_data_3374 = { (M504_PATH *)&lbl_1_data_F44, (M504_PATH *)&lbl_1_data_F54, 1, 0, { (M504_NODE *)&lbl_1_data_3384 } };
/* 0x3384 */ M504_NODE1 lbl_1_data_3384 = { (M504_PATH *)&lbl_1_data_F64, (M504_PATH *)&lbl_1_data_F74, 1, 0, { (M504_NODE *)&lbl_1_data_3394 } };
/* 0x3394 */ M504_NODE1 lbl_1_data_3394 = { (M504_PATH *)&lbl_1_data_F84, (M504_PATH *)&lbl_1_data_F94, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x33A4 */ M504_NODE1 lbl_1_data_33A4 = { (M504_PATH *)&lbl_1_data_FA4, (M504_PATH *)&lbl_1_data_FB4, 1, 0, { (M504_NODE *)&lbl_1_data_33B4 } };
/* 0x33B4 */ M504_NODE1 lbl_1_data_33B4 = { (M504_PATH *)&lbl_1_data_FC4, (M504_PATH *)&lbl_1_data_FD4, 1, 0, { (M504_NODE *)&lbl_1_data_33C4 } };
/* 0x33C4 */ M504_NODE1 lbl_1_data_33C4 = { (M504_PATH *)&lbl_1_data_FE4, (M504_PATH *)&lbl_1_data_FF4, 1, 0, { (M504_NODE *)&lbl_1_data_33D4 } };
/* 0x33D4 */ M504_NODE1 lbl_1_data_33D4 = { (M504_PATH *)&lbl_1_data_1004, (M504_PATH *)&lbl_1_data_1014, 1, 0, { (M504_NODE *)&lbl_1_data_33E4 } };
/* 0x33E4 */ M504_NODE1 lbl_1_data_33E4 = { (M504_PATH *)&lbl_1_data_1024, (M504_PATH *)&lbl_1_data_1034, 1, 0, { (M504_NODE *)&lbl_1_data_33F4 } };
/* 0x33F4 */ M504_NODE1 lbl_1_data_33F4 = { (M504_PATH *)&lbl_1_data_1050, (M504_PATH *)&lbl_1_data_1078, 1, 0, { (M504_NODE *)&lbl_1_data_3404 } };
/* 0x3404 */ M504_NODE1 lbl_1_data_3404 = { (M504_PATH *)&lbl_1_data_1088, (M504_PATH *)&lbl_1_data_1098, 1, 0, { (M504_NODE *)&lbl_1_data_3414 } };
/* 0x3414 */ M504_NODE1 lbl_1_data_3414 = { (M504_PATH *)&lbl_1_data_10A8, (M504_PATH *)&lbl_1_data_10B8, 1, 0, { (M504_NODE *)&lbl_1_data_3424 } };
/* 0x3424 */ M504_NODE1 lbl_1_data_3424 = { (M504_PATH *)&lbl_1_data_10C8, (M504_PATH *)&lbl_1_data_10D8, 1, 0, { (M504_NODE *)&lbl_1_data_3434 } };
/* 0x3434 */ M504_NODE1 lbl_1_data_3434 = { (M504_PATH *)&lbl_1_data_10E8, (M504_PATH *)&lbl_1_data_10F8, 1, 0, { (M504_NODE *)&lbl_1_data_3444 } };
/* 0x3444 */ M504_NODE1 lbl_1_data_3444 = { (M504_PATH *)&lbl_1_data_1108, (M504_PATH *)&lbl_1_data_1118, 1, 0, { (M504_NODE *)&lbl_1_data_3454 } };
/* 0x3454 */ M504_NODE1 lbl_1_data_3454 = { (M504_PATH *)&lbl_1_data_1128, (M504_PATH *)&lbl_1_data_1138, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3464 */ M504_NODE1 lbl_1_data_3464 = { (M504_PATH *)&lbl_1_data_1148, (M504_PATH *)&lbl_1_data_117C, 1, 0, { (M504_NODE *)&lbl_1_data_3474 } };
/* 0x3474 */ M504_NODE1 lbl_1_data_3474 = { (M504_PATH *)&lbl_1_data_118C, (M504_PATH *)&lbl_1_data_119C, 1, 0, { (M504_NODE *)&lbl_1_data_3484 } };
/* 0x3484 */ M504_NODE1 lbl_1_data_3484 = { (M504_PATH *)&lbl_1_data_11AC, (M504_PATH *)&lbl_1_data_11BC, 1, 0, { (M504_NODE *)&lbl_1_data_3494 } };
/* 0x3494 */ M504_NODE1 lbl_1_data_3494 = { (M504_PATH *)&lbl_1_data_11CC, (M504_PATH *)&lbl_1_data_11DC, 1, 0, { (M504_NODE *)&lbl_1_data_34A4 } };
/* 0x34A4 */ M504_NODE1 lbl_1_data_34A4 = { (M504_PATH *)&lbl_1_data_11EC, (M504_PATH *)&lbl_1_data_11FC, 1, 0, { (M504_NODE *)&lbl_1_data_34B4 } };
/* 0x34B4 */ M504_NODE1 lbl_1_data_34B4 = { (M504_PATH *)&lbl_1_data_120C, (M504_PATH *)&lbl_1_data_121C, 1, 0, { (M504_NODE *)&lbl_1_data_34C4 } };
/* 0x34C4 */ M504_NODE1 lbl_1_data_34C4 = { (M504_PATH *)&lbl_1_data_122C, (M504_PATH *)&lbl_1_data_123C, 1, 0, { (M504_NODE *)&lbl_1_data_34D4 } };
/* 0x34D4 */ M504_NODE1 lbl_1_data_34D4 = { (M504_PATH *)&lbl_1_data_124C, (M504_PATH *)&lbl_1_data_125C, 1, 0, { (M504_NODE *)&lbl_1_data_34E4 } };
/* 0x34E4 */ M504_NODE1 lbl_1_data_34E4 = { (M504_PATH *)&lbl_1_data_126C, (M504_PATH *)&lbl_1_data_12A0, 1, 0, { (M504_NODE *)&lbl_1_data_34F4 } };
/* 0x34F4 */ M504_NODE1 lbl_1_data_34F4 = { (M504_PATH *)&lbl_1_data_12B0, (M504_PATH *)&lbl_1_data_12C0, 1, 0, { (M504_NODE *)&lbl_1_data_3504 } };
/* 0x3504 */ M504_NODE1 lbl_1_data_3504 = { (M504_PATH *)&lbl_1_data_12D0, (M504_PATH *)&lbl_1_data_12E0, 1, 0, { (M504_NODE *)&lbl_1_data_3514 } };
/* 0x3514 */ M504_NODE1 lbl_1_data_3514 = { (M504_PATH *)&lbl_1_data_12F0, (M504_PATH *)&lbl_1_data_1300, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3524 */ M504_NODE1 lbl_1_data_3524 = { (M504_PATH *)&lbl_1_data_1310, (M504_PATH *)&lbl_1_data_1350, 1, 0, { (M504_NODE *)&lbl_1_data_3534 } };
/* 0x3534 */ M504_NODE1 lbl_1_data_3534 = { (M504_PATH *)&lbl_1_data_1360, (M504_PATH *)&lbl_1_data_1370, 1, 0, { (M504_NODE *)&lbl_1_data_3544 } };
/* 0x3544 */ M504_NODE1 lbl_1_data_3544 = { (M504_PATH *)&lbl_1_data_1380, (M504_PATH *)&lbl_1_data_1390, 1, 0, { (M504_NODE *)&lbl_1_data_3554 } };
/* 0x3554 */ M504_NODE1 lbl_1_data_3554 = { (M504_PATH *)&lbl_1_data_13A0, (M504_PATH *)&lbl_1_data_13B0, 1, 0, { (M504_NODE *)&lbl_1_data_3564 } };
/* 0x3564 */ M504_NODE1 lbl_1_data_3564 = { (M504_PATH *)&lbl_1_data_13C0, (M504_PATH *)&lbl_1_data_13D0, 1, 0, { (M504_NODE *)&lbl_1_data_3574 } };
/* 0x3574 */ M504_NODE1 lbl_1_data_3574 = { (M504_PATH *)&lbl_1_data_13E0, (M504_PATH *)&lbl_1_data_13F0, 1, 0, { (M504_NODE *)&lbl_1_data_3584 } };
/* 0x3584 */ M504_NODE1 lbl_1_data_3584 = { (M504_PATH *)&lbl_1_data_1400, (M504_PATH *)&lbl_1_data_1428, 1, 0, { (M504_NODE *)&lbl_1_data_3594 } };
/* 0x3594 */ M504_NODE1 lbl_1_data_3594 = { (M504_PATH *)&lbl_1_data_1438, (M504_PATH *)&lbl_1_data_1448, 1, 0, { (M504_NODE *)&lbl_1_data_35A4 } };
/* 0x35A4 */ M504_NODE1 lbl_1_data_35A4 = { (M504_PATH *)&lbl_1_data_1458, (M504_PATH *)&lbl_1_data_1468, 1, 0, { (M504_NODE *)&lbl_1_data_35B4 } };
/* 0x35B4 */ M504_NODE1 lbl_1_data_35B4 = { (M504_PATH *)&lbl_1_data_1478, (M504_PATH *)&lbl_1_data_1488, 1, 0, { (M504_NODE *)&lbl_1_data_35C4 } };
/* 0x35C4 */ M504_NODE1 lbl_1_data_35C4 = { (M504_PATH *)&lbl_1_data_1498, (M504_PATH *)&lbl_1_data_14A8, 1, 0, { (M504_NODE *)&lbl_1_data_35D4 } };
/* 0x35D4 */ M504_NODE1 lbl_1_data_35D4 = { (M504_PATH *)&lbl_1_data_14B8, (M504_PATH *)&lbl_1_data_14C8, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x35E4 */ M504_NODE1 lbl_1_data_35E4 = { (M504_PATH *)&lbl_1_data_14D8, (M504_PATH *)&lbl_1_data_14E8, 1, 0, { (M504_NODE *)&lbl_1_data_35F4 } };
/* 0x35F4 */ M504_NODE1 lbl_1_data_35F4 = { (M504_PATH *)&lbl_1_data_14F8, (M504_PATH *)&lbl_1_data_1520, 1, 0, { (M504_NODE *)&lbl_1_data_3604 } };
/* 0x3604 */ M504_NODE1 lbl_1_data_3604 = { (M504_PATH *)&lbl_1_data_1530, (M504_PATH *)&lbl_1_data_1540, 1, 0, { (M504_NODE *)&lbl_1_data_3614 } };
/* 0x3614 */ M504_NODE1 lbl_1_data_3614 = { (M504_PATH *)&lbl_1_data_1550, (M504_PATH *)&lbl_1_data_1560, 1, 0, { (M504_NODE *)&lbl_1_data_3624 } };
/* 0x3624 */ M504_NODE1 lbl_1_data_3624 = { (M504_PATH *)&lbl_1_data_1570, (M504_PATH *)&lbl_1_data_1580, 1, 0, { (M504_NODE *)&lbl_1_data_3634 } };
/* 0x3634 */ M504_NODE1 lbl_1_data_3634 = { (M504_PATH *)&lbl_1_data_1590, (M504_PATH *)&lbl_1_data_15A0, 1, 0, { (M504_NODE *)&lbl_1_data_3644 } };
/* 0x3644 */ M504_NODE1 lbl_1_data_3644 = { (M504_PATH *)&lbl_1_data_15B0, (M504_PATH *)&lbl_1_data_15C0, 1, 0, { (M504_NODE *)&lbl_1_data_3654 } };
/* 0x3654 */ M504_NODE1 lbl_1_data_3654 = { (M504_PATH *)&lbl_1_data_15D0, (M504_PATH *)&lbl_1_data_15E0, 1, 0, { (M504_NODE *)&lbl_1_data_3664 } };
/* 0x3664 */ M504_NODE1 lbl_1_data_3664 = { (M504_PATH *)&lbl_1_data_15F0, (M504_PATH *)&lbl_1_data_1600, 1, 0, { (M504_NODE *)&lbl_1_data_3674 } };
/* 0x3674 */ M504_NODE1 lbl_1_data_3674 = { (M504_PATH *)&lbl_1_data_1610, (M504_PATH *)&lbl_1_data_1620, 1, 0, { (M504_NODE *)&lbl_1_data_3684 } };
/* 0x3684 */ M504_NODE1 lbl_1_data_3684 = { (M504_PATH *)&lbl_1_data_1630, (M504_PATH *)&lbl_1_data_1640, 1, 0, { (M504_NODE *)&lbl_1_data_3694 } };
/* 0x3694 */ M504_NODE1 lbl_1_data_3694 = { (M504_PATH *)&lbl_1_data_1650, (M504_PATH *)&lbl_1_data_166C, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x36A4 */ M504_NODE1 lbl_1_data_36A4 = { (M504_PATH *)&lbl_1_data_167C, (M504_PATH *)&lbl_1_data_1698, 1, 0, { (M504_NODE *)&lbl_1_data_36B4 } };
/* 0x36B4 */ M504_NODE1 lbl_1_data_36B4 = { (M504_PATH *)&lbl_1_data_16A8, (M504_PATH *)&lbl_1_data_16B8, 1, 0, { (M504_NODE *)&lbl_1_data_36C4 } };
/* 0x36C4 */ M504_NODE1 lbl_1_data_36C4 = { (M504_PATH *)&lbl_1_data_16C8, (M504_PATH *)&lbl_1_data_16D8, 1, 0, { (M504_NODE *)&lbl_1_data_36D4 } };
/* 0x36D4 */ M504_NODE1 lbl_1_data_36D4 = { (M504_PATH *)&lbl_1_data_16E8, (M504_PATH *)&lbl_1_data_16F8, 1, 0, { (M504_NODE *)&lbl_1_data_36E4 } };
/* 0x36E4 */ M504_NODE1 lbl_1_data_36E4 = { (M504_PATH *)&lbl_1_data_1708, (M504_PATH *)&lbl_1_data_1718, 1, 0, { (M504_NODE *)&lbl_1_data_36F4 } };
/* 0x36F4 */ M504_NODE1 lbl_1_data_36F4 = { (M504_PATH *)&lbl_1_data_1728, (M504_PATH *)&lbl_1_data_1738, 1, 0, { (M504_NODE *)&lbl_1_data_3704 } };
/* 0x3704 */ M504_NODE1 lbl_1_data_3704 = { (M504_PATH *)&lbl_1_data_1748, (M504_PATH *)&lbl_1_data_1758, 1, 0, { (M504_NODE *)&lbl_1_data_3714 } };
/* 0x3714 */ M504_NODE1 lbl_1_data_3714 = { (M504_PATH *)&lbl_1_data_1768, (M504_PATH *)&lbl_1_data_1778, 1, 0, { (M504_NODE *)&lbl_1_data_3724 } };
/* 0x3724 */ M504_NODE1 lbl_1_data_3724 = { (M504_PATH *)&lbl_1_data_1788, (M504_PATH *)&lbl_1_data_17A4, 1, 0, { (M504_NODE *)&lbl_1_data_3734 } };
/* 0x3734 */ M504_NODE1 lbl_1_data_3734 = { (M504_PATH *)&lbl_1_data_17B4, (M504_PATH *)&lbl_1_data_17C4, 1, 0, { (M504_NODE *)&lbl_1_data_3744 } };
/* 0x3744 */ M504_NODE1 lbl_1_data_3744 = { (M504_PATH *)&lbl_1_data_17D4, (M504_PATH *)&lbl_1_data_17E4, 1, 0, { (M504_NODE *)&lbl_1_data_3754 } };
/* 0x3754 */ M504_NODE1 lbl_1_data_3754 = { (M504_PATH *)&lbl_1_data_17F4, (M504_PATH *)&lbl_1_data_1804, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3764 */ M504_NODE1 lbl_1_data_3764 = { (M504_PATH *)&lbl_1_data_1814, (M504_PATH *)&lbl_1_data_1824, 1, 0, { (M504_NODE *)&lbl_1_data_3774 } };
/* 0x3774 */ M504_NODE1 lbl_1_data_3774 = { (M504_PATH *)&lbl_1_data_1834, (M504_PATH *)&lbl_1_data_1844, 1, 0, { (M504_NODE *)&lbl_1_data_3784 } };
/* 0x3784 */ M504_NODE1 lbl_1_data_3784 = { (M504_PATH *)&lbl_1_data_1854, (M504_PATH *)&lbl_1_data_1864, 1, 0, { (M504_NODE *)&lbl_1_data_3794 } };
/* 0x3794 */ M504_NODE1 lbl_1_data_3794 = { (M504_PATH *)&lbl_1_data_1874, (M504_PATH *)&lbl_1_data_1884, 1, 0, { (M504_NODE *)&lbl_1_data_37A4 } };
/* 0x37A4 */ M504_NODE1 lbl_1_data_37A4 = { (M504_PATH *)&lbl_1_data_1894, (M504_PATH *)&lbl_1_data_18A4, 1, 0, { (M504_NODE *)&lbl_1_data_37B4 } };
/* 0x37B4 */ M504_NODE1 lbl_1_data_37B4 = { (M504_PATH *)&lbl_1_data_18B4, (M504_PATH *)&lbl_1_data_18C4, 1, 0, { (M504_NODE *)&lbl_1_data_37C4 } };
/* 0x37C4 */ M504_NODE1 lbl_1_data_37C4 = { (M504_PATH *)&lbl_1_data_18D4, (M504_PATH *)&lbl_1_data_18E4, 1, 0, { (M504_NODE *)&lbl_1_data_37D4 } };
/* 0x37D4 */ M504_NODE1 lbl_1_data_37D4 = { (M504_PATH *)&lbl_1_data_18F4, (M504_PATH *)&lbl_1_data_1904, 1, 0, { (M504_NODE *)&lbl_1_data_37E4 } };
/* 0x37E4 */ M504_NODE1 lbl_1_data_37E4 = { (M504_PATH *)&lbl_1_data_1914, (M504_PATH *)&lbl_1_data_1924, 1, 0, { (M504_NODE *)&lbl_1_data_37F4 } };
/* 0x37F4 */ M504_NODE1 lbl_1_data_37F4 = { (M504_PATH *)&lbl_1_data_1934, (M504_PATH *)&lbl_1_data_1944, 1, 0, { (M504_NODE *)&lbl_1_data_3804 } };
/* 0x3804 */ M504_NODE1 lbl_1_data_3804 = { (M504_PATH *)&lbl_1_data_1954, (M504_PATH *)&lbl_1_data_1964, 1, 0, { (M504_NODE *)&lbl_1_data_3814 } };
/* 0x3814 */ M504_NODE1 lbl_1_data_3814 = { (M504_PATH *)&lbl_1_data_1974, (M504_PATH *)&lbl_1_data_1984, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3824 */ M504_NODE1 lbl_1_data_3824 = { (M504_PATH *)&lbl_1_data_1994, (M504_PATH *)&lbl_1_data_19B0, 1, 0, { (M504_NODE *)&lbl_1_data_3834 } };
/* 0x3834 */ M504_NODE1 lbl_1_data_3834 = { (M504_PATH *)&lbl_1_data_19C0, (M504_PATH *)&lbl_1_data_19D0, 1, 0, { (M504_NODE *)&lbl_1_data_3844 } };
/* 0x3844 */ M504_NODE1 lbl_1_data_3844 = { (M504_PATH *)&lbl_1_data_19E0, (M504_PATH *)&lbl_1_data_19F0, 1, 0, { (M504_NODE *)&lbl_1_data_3854 } };
/* 0x3854 */ M504_NODE1 lbl_1_data_3854 = { (M504_PATH *)&lbl_1_data_1A00, (M504_PATH *)&lbl_1_data_1A10, 1, 0, { (M504_NODE *)&lbl_1_data_3864 } };
/* 0x3864 */ M504_NODE1 lbl_1_data_3864 = { (M504_PATH *)&lbl_1_data_1A20, (M504_PATH *)&lbl_1_data_1A6C, 1, 0, { (M504_NODE *)&lbl_1_data_3874 } };
/* 0x3874 */ M504_NODE1 lbl_1_data_3874 = { (M504_PATH *)&lbl_1_data_1A7C, (M504_PATH *)&lbl_1_data_1A8C, 1, 0, { (M504_NODE *)&lbl_1_data_3884 } };
/* 0x3884 */ M504_NODE1 lbl_1_data_3884 = { (M504_PATH *)&lbl_1_data_1A9C, (M504_PATH *)&lbl_1_data_1AAC, 1, 0, { (M504_NODE *)&lbl_1_data_3894 } };
/* 0x3894 */ M504_NODE1 lbl_1_data_3894 = { (M504_PATH *)&lbl_1_data_1ABC, (M504_PATH *)&lbl_1_data_1ACC, 1, 0, { (M504_NODE *)&lbl_1_data_38A4 } };
/* 0x38A4 */ M504_NODE1 lbl_1_data_38A4 = { (M504_PATH *)&lbl_1_data_1ADC, (M504_PATH *)&lbl_1_data_1AEC, 1, 0, { (M504_NODE *)&lbl_1_data_38B4 } };
/* 0x38B4 */ M504_NODE1 lbl_1_data_38B4 = { (M504_PATH *)&lbl_1_data_1AFC, (M504_PATH *)&lbl_1_data_1B0C, 1, 0, { (M504_NODE *)&lbl_1_data_38C4 } };
/* 0x38C4 */ M504_NODE1 lbl_1_data_38C4 = { (M504_PATH *)&lbl_1_data_1B1C, (M504_PATH *)&lbl_1_data_1B2C, 1, 0, { (M504_NODE *)&lbl_1_data_38D4 } };
/* 0x38D4 */ M504_NODE1 lbl_1_data_38D4 = { (M504_PATH *)&lbl_1_data_1B3C, (M504_PATH *)&lbl_1_data_1B4C, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x38E4 */ M504_NODE1 lbl_1_data_38E4 = { (M504_PATH *)&lbl_1_data_1B5C, (M504_PATH *)&lbl_1_data_1B84, 1, 0, { (M504_NODE *)&lbl_1_data_38F4 } };
/* 0x38F4 */ M504_NODE1 lbl_1_data_38F4 = { (M504_PATH *)&lbl_1_data_1B94, (M504_PATH *)&lbl_1_data_1BA4, 1, 0, { (M504_NODE *)&lbl_1_data_3904 } };
/* 0x3904 */ M504_NODE1 lbl_1_data_3904 = { (M504_PATH *)&lbl_1_data_1BB4, (M504_PATH *)&lbl_1_data_1BC4, 1, 0, { (M504_NODE *)&lbl_1_data_3914 } };
/* 0x3914 */ M504_NODE1 lbl_1_data_3914 = { (M504_PATH *)&lbl_1_data_1BD4, (M504_PATH *)&lbl_1_data_1BE4, 1, 0, { (M504_NODE *)&lbl_1_data_3924 } };
/* 0x3924 */ M504_NODE1 lbl_1_data_3924 = { (M504_PATH *)&lbl_1_data_1BF4, (M504_PATH *)&lbl_1_data_1C1C, 1, 0, { (M504_NODE *)&lbl_1_data_3934 } };
/* 0x3934 */ M504_NODE1 lbl_1_data_3934 = { (M504_PATH *)&lbl_1_data_1C2C, (M504_PATH *)&lbl_1_data_1C3C, 1, 0, { (M504_NODE *)&lbl_1_data_3944 } };
/* 0x3944 */ M504_NODE1 lbl_1_data_3944 = { (M504_PATH *)&lbl_1_data_1C4C, (M504_PATH *)&lbl_1_data_1C5C, 1, 0, { (M504_NODE *)&lbl_1_data_3954 } };
/* 0x3954 */ M504_NODE1 lbl_1_data_3954 = { (M504_PATH *)&lbl_1_data_1C6C, (M504_PATH *)&lbl_1_data_1C7C, 1, 0, { (M504_NODE *)&lbl_1_data_3964 } };
/* 0x3964 */ M504_NODE1 lbl_1_data_3964 = { (M504_PATH *)&lbl_1_data_1C8C, (M504_PATH *)&lbl_1_data_1C9C, 1, 0, { (M504_NODE *)&lbl_1_data_3974 } };
/* 0x3974 */ M504_NODE1 lbl_1_data_3974 = { (M504_PATH *)&lbl_1_data_1CAC, (M504_PATH *)&lbl_1_data_1CBC, 1, 0, { (M504_NODE *)&lbl_1_data_3984 } };
/* 0x3984 */ M504_NODE1 lbl_1_data_3984 = { (M504_PATH *)&lbl_1_data_1CCC, (M504_PATH *)&lbl_1_data_1CDC, 1, 0, { (M504_NODE *)&lbl_1_data_3994 } };
/* 0x3994 */ M504_NODE1 lbl_1_data_3994 = { (M504_PATH *)&lbl_1_data_1CEC, (M504_PATH *)&lbl_1_data_1CFC, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x39A4 */ M504_NODE1 lbl_1_data_39A4 = { (M504_PATH *)&lbl_1_data_1D0C, (M504_PATH *)&lbl_1_data_1D40, 1, 0, { (M504_NODE *)&lbl_1_data_39B4 } };
/* 0x39B4 */ M504_NODE1 lbl_1_data_39B4 = { (M504_PATH *)&lbl_1_data_1D50, (M504_PATH *)&lbl_1_data_1D6C, 1, 0, { (M504_NODE *)&lbl_1_data_39C4 } };
/* 0x39C4 */ M504_NODE1 lbl_1_data_39C4 = { (M504_PATH *)&lbl_1_data_1D7C, (M504_PATH *)&lbl_1_data_1D8C, 1, 0, { (M504_NODE *)&lbl_1_data_39D4 } };
/* 0x39D4 */ M504_NODE1 lbl_1_data_39D4 = { (M504_PATH *)&lbl_1_data_1D9C, (M504_PATH *)&lbl_1_data_1DB8, 1, 0, { (M504_NODE *)&lbl_1_data_39E4 } };
/* 0x39E4 */ M504_NODE1 lbl_1_data_39E4 = { (M504_PATH *)&lbl_1_data_1DC8, (M504_PATH *)&lbl_1_data_1DD8, 1, 0, { (M504_NODE *)&lbl_1_data_39F4 } };
/* 0x39F4 */ M504_NODE1 lbl_1_data_39F4 = { (M504_PATH *)&lbl_1_data_1DE8, (M504_PATH *)&lbl_1_data_1DF8, 1, 0, { (M504_NODE *)&lbl_1_data_3A04 } };
/* 0x3A04 */ M504_NODE1 lbl_1_data_3A04 = { (M504_PATH *)&lbl_1_data_1E08, (M504_PATH *)&lbl_1_data_1E18, 1, 0, { (M504_NODE *)&lbl_1_data_3A14 } };
/* 0x3A14 */ M504_NODE1 lbl_1_data_3A14 = { (M504_PATH *)&lbl_1_data_1E28, (M504_PATH *)&lbl_1_data_1E38, 1, 0, { (M504_NODE *)&lbl_1_data_3A24 } };
/* 0x3A24 */ M504_NODE1 lbl_1_data_3A24 = { (M504_PATH *)&lbl_1_data_1E48, (M504_PATH *)&lbl_1_data_1E58, 1, 0, { (M504_NODE *)&lbl_1_data_3A34 } };
/* 0x3A34 */ M504_NODE1 lbl_1_data_3A34 = { (M504_PATH *)&lbl_1_data_1E68, (M504_PATH *)&lbl_1_data_1E78, 1, 0, { (M504_NODE *)&lbl_1_data_3A44 } };
/* 0x3A44 */ M504_NODE1 lbl_1_data_3A44 = { (M504_PATH *)&lbl_1_data_1E88, (M504_PATH *)&lbl_1_data_1E98, 1, 0, { (M504_NODE *)&lbl_1_data_3A54 } };
/* 0x3A54 */ M504_NODE1 lbl_1_data_3A54 = { (M504_PATH *)&lbl_1_data_1EA8, (M504_PATH *)&lbl_1_data_1EB8, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3A64 */ M504_NODE1 lbl_1_data_3A64 = { (M504_PATH *)&lbl_1_data_1EC8, (M504_PATH *)&lbl_1_data_1EF0, 1, 0, { (M504_NODE *)&lbl_1_data_3A74 } };
/* 0x3A74 */ M504_NODE1 lbl_1_data_3A74 = { (M504_PATH *)&lbl_1_data_1F00, (M504_PATH *)&lbl_1_data_1F10, 1, 0, { (M504_NODE *)&lbl_1_data_3A84 } };
/* 0x3A84 */ M504_NODE1 lbl_1_data_3A84 = { (M504_PATH *)&lbl_1_data_1F20, (M504_PATH *)&lbl_1_data_1F30, 1, 0, { (M504_NODE *)&lbl_1_data_3A94 } };
/* 0x3A94 */ M504_NODE1 lbl_1_data_3A94 = { (M504_PATH *)&lbl_1_data_1F40, (M504_PATH *)&lbl_1_data_1F50, 1, 0, { (M504_NODE *)&lbl_1_data_3AA4 } };
/* 0x3AA4 */ M504_NODE1 lbl_1_data_3AA4 = { (M504_PATH *)&lbl_1_data_1F60, (M504_PATH *)&lbl_1_data_1F70, 1, 0, { (M504_NODE *)&lbl_1_data_3AB4 } };
/* 0x3AB4 */ M504_NODE1 lbl_1_data_3AB4 = { (M504_PATH *)&lbl_1_data_1F80, (M504_PATH *)&lbl_1_data_1F90, 1, 0, { (M504_NODE *)&lbl_1_data_3AC4 } };
/* 0x3AC4 */ M504_NODE1 lbl_1_data_3AC4 = { (M504_PATH *)&lbl_1_data_1FA0, (M504_PATH *)&lbl_1_data_1FB0, 1, 0, { (M504_NODE *)&lbl_1_data_3AD4 } };
/* 0x3AD4 */ M504_NODE1 lbl_1_data_3AD4 = { (M504_PATH *)&lbl_1_data_1FC0, (M504_PATH *)&lbl_1_data_1FDC, 1, 0, { (M504_NODE *)&lbl_1_data_3AE4 } };
/* 0x3AE4 */ M504_NODE1 lbl_1_data_3AE4 = { (M504_PATH *)&lbl_1_data_1FEC, (M504_PATH *)&lbl_1_data_1FFC, 1, 0, { (M504_NODE *)&lbl_1_data_3AF4 } };
/* 0x3AF4 */ M504_NODE1 lbl_1_data_3AF4 = { (M504_PATH *)&lbl_1_data_200C, (M504_PATH *)&lbl_1_data_201C, 1, 0, { (M504_NODE *)&lbl_1_data_3B04 } };
/* 0x3B04 */ M504_NODE1 lbl_1_data_3B04 = { (M504_PATH *)&lbl_1_data_202C, (M504_PATH *)&lbl_1_data_203C, 1, 0, { (M504_NODE *)&lbl_1_data_3B14 } };
/* 0x3B14 */ M504_NODE1 lbl_1_data_3B14 = { (M504_PATH *)&lbl_1_data_204C, (M504_PATH *)&lbl_1_data_205C, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3B24 */ M504_NODE2 lbl_1_data_3B24 = { (M504_PATH *)&lbl_1_data_206C, (M504_PATH *)&lbl_1_data_2088, 2, 0, { (M504_NODE *)&lbl_1_data_3B38, (M504_NODE *)&lbl_1_data_3B48 } };
/* 0x3B38 */ M504_NODE1 lbl_1_data_3B38 = { (M504_PATH *)&lbl_1_data_2098, (M504_PATH *)&lbl_1_data_20A8, 1, 0, { (M504_NODE *)&lbl_1_data_3B58 } };
/* 0x3B48 */ M504_NODE1 lbl_1_data_3B48 = { (M504_PATH *)&lbl_1_data_20B8, (M504_PATH *)&lbl_1_data_20C8, 1, 0, { (M504_NODE *)&lbl_1_data_3B58 } };
/* 0x3B58 */ M504_NODE1 lbl_1_data_3B58 = { (M504_PATH *)&lbl_1_data_20D8, (M504_PATH *)&lbl_1_data_20E8, 1, 0, { (M504_NODE *)&lbl_1_data_3B68 } };
/* 0x3B68 */ M504_NODE2 lbl_1_data_3B68 = { (M504_PATH *)&lbl_1_data_20F8, (M504_PATH *)&lbl_1_data_2138, 2, 0, { (M504_NODE *)&lbl_1_data_3B7C, (M504_NODE *)&lbl_1_data_3B8C } };
/* 0x3B7C */ M504_NODE1 lbl_1_data_3B7C = { (M504_PATH *)&lbl_1_data_2148, (M504_PATH *)&lbl_1_data_2158, 1, 0, { (M504_NODE *)&lbl_1_data_3B9C } };
/* 0x3B8C */ M504_NODE1 lbl_1_data_3B8C = { (M504_PATH *)&lbl_1_data_2168, (M504_PATH *)&lbl_1_data_2178, 1, 0, { (M504_NODE *)&lbl_1_data_3B9C } };
/* 0x3B9C */ M504_NODE1 lbl_1_data_3B9C = { (M504_PATH *)&lbl_1_data_2188, (M504_PATH *)&lbl_1_data_21A4, 1, 0, { (M504_NODE *)&lbl_1_data_3BAC } };
/* 0x3BAC */ M504_NODE1 lbl_1_data_3BAC = { (M504_PATH *)&lbl_1_data_21B4, (M504_PATH *)&lbl_1_data_21F4, 1, 0, { (M504_NODE *)&lbl_1_data_3BBC } };
/* 0x3BBC */ M504_NODE2 lbl_1_data_3BBC = { (M504_PATH *)&lbl_1_data_2204, (M504_PATH *)&lbl_1_data_222C, 2, 0, { (M504_NODE *)&lbl_1_data_3BD0, (M504_NODE *)&lbl_1_data_3BE0 } };
/* 0x3BD0 */ M504_NODE1 lbl_1_data_3BD0 = { (M504_PATH *)&lbl_1_data_223C, (M504_PATH *)&lbl_1_data_224C, 1, 0, { (M504_NODE *)&lbl_1_data_3BF0 } };
/* 0x3BE0 */ M504_NODE1 lbl_1_data_3BE0 = { (M504_PATH *)&lbl_1_data_225C, (M504_PATH *)&lbl_1_data_226C, 1, 0, { (M504_NODE *)&lbl_1_data_3BF0 } };
/* 0x3BF0 */ M504_NODE1 lbl_1_data_3BF0 = { (M504_PATH *)&lbl_1_data_227C, (M504_PATH *)&lbl_1_data_228C, 1, 0, { (M504_NODE *)&lbl_1_data_3C00 } };
/* 0x3C00 */ M504_NODE1 lbl_1_data_3C00 = { (M504_PATH *)&lbl_1_data_229C, (M504_PATH *)&lbl_1_data_22AC, 1, 0, { (M504_NODE *)&lbl_1_data_3C10 } };
/* 0x3C10 */ M504_NODE1 lbl_1_data_3C10 = { (M504_PATH *)&lbl_1_data_22BC, (M504_PATH *)&lbl_1_data_22CC, 1, 0, { (M504_NODE *)&lbl_1_data_3C20 } };
/* 0x3C20 */ M504_NODE1 lbl_1_data_3C20 = { (M504_PATH *)&lbl_1_data_22DC, (M504_PATH *)&lbl_1_data_22EC, 1, 0, { (M504_NODE *)&lbl_1_data_3C30 } };
/* 0x3C30 */ M504_NODE1 lbl_1_data_3C30 = { (M504_PATH *)&lbl_1_data_22FC, (M504_PATH *)&lbl_1_data_230C, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3C40 */ M504_NODE1 lbl_1_data_3C40 = { (M504_PATH *)&lbl_1_data_231C, (M504_PATH *)&lbl_1_data_2344, 1, 0, { (M504_NODE *)&lbl_1_data_3C50 } };
/* 0x3C50 */ M504_NODE2 lbl_1_data_3C50 = { (M504_PATH *)&lbl_1_data_2354, (M504_PATH *)&lbl_1_data_2364, 2, 0, { (M504_NODE *)&lbl_1_data_3C64, (M504_NODE *)&lbl_1_data_3C74 } };
/* 0x3C64 */ M504_NODE1 lbl_1_data_3C64 = { (M504_PATH *)&lbl_1_data_2374, (M504_PATH *)&lbl_1_data_239C, 1, 0, { (M504_NODE *)&lbl_1_data_3C84 } };
/* 0x3C74 */ M504_NODE1 lbl_1_data_3C74 = { (M504_PATH *)&lbl_1_data_23AC, (M504_PATH *)&lbl_1_data_23D4, 1, 0, { (M504_NODE *)&lbl_1_data_3C84 } };
/* 0x3C84 */ M504_NODE1 lbl_1_data_3C84 = { (M504_PATH *)&lbl_1_data_23E4, (M504_PATH *)&lbl_1_data_23F4, 1, 0, { (M504_NODE *)&lbl_1_data_3C94 } };
/* 0x3C94 */ M504_NODE2 lbl_1_data_3C94 = { (M504_PATH *)&lbl_1_data_2404, (M504_PATH *)&lbl_1_data_2414, 2, 0, { (M504_NODE *)&lbl_1_data_3CA8, (M504_NODE *)&lbl_1_data_3CB8 } };
/* 0x3CA8 */ M504_NODE1 lbl_1_data_3CA8 = { (M504_PATH *)&lbl_1_data_2424, (M504_PATH *)&lbl_1_data_2434, 1, 0, { (M504_NODE *)&lbl_1_data_3CC8 } };
/* 0x3CB8 */ M504_NODE1 lbl_1_data_3CB8 = { (M504_PATH *)&lbl_1_data_2444, (M504_PATH *)&lbl_1_data_2454, 1, 0, { (M504_NODE *)&lbl_1_data_3CC8 } };
/* 0x3CC8 */ M504_NODE1 lbl_1_data_3CC8 = { (M504_PATH *)&lbl_1_data_2464, (M504_PATH *)&lbl_1_data_2474, 1, 0, { (M504_NODE *)&lbl_1_data_3CD8 } };
/* 0x3CD8 */ M504_NODE1 lbl_1_data_3CD8 = { (M504_PATH *)&lbl_1_data_2484, (M504_PATH *)&lbl_1_data_2494, 1, 0, { (M504_NODE *)&lbl_1_data_3CE8 } };
/* 0x3CE8 */ M504_NODE1 lbl_1_data_3CE8 = { (M504_PATH *)&lbl_1_data_24A4, (M504_PATH *)&lbl_1_data_24B4, 1, 0, { (M504_NODE *)&lbl_1_data_3CF8 } };
/* 0x3CF8 */ M504_NODE1 lbl_1_data_3CF8 = { (M504_PATH *)&lbl_1_data_24C4, (M504_PATH *)&lbl_1_data_24D4, 1, 0, { (M504_NODE *)&lbl_1_data_3D08 } };
/* 0x3D08 */ M504_NODE2 lbl_1_data_3D08 = { (M504_PATH *)&lbl_1_data_24E4, (M504_PATH *)&lbl_1_data_24F4, 2, 0, { (M504_NODE *)&lbl_1_data_3D1C, (M504_NODE *)&lbl_1_data_3D2C } };
/* 0x3D1C */ M504_NODE1 lbl_1_data_3D1C = { (M504_PATH *)&lbl_1_data_2504, (M504_PATH *)&lbl_1_data_2514, 1, 0, { (M504_NODE *)&lbl_1_data_3D3C } };
/* 0x3D2C */ M504_NODE1 lbl_1_data_3D2C = { (M504_PATH *)&lbl_1_data_2524, (M504_PATH *)&lbl_1_data_2534, 1, 0, { (M504_NODE *)&lbl_1_data_3D3C } };
/* 0x3D3C */ M504_NODE1 lbl_1_data_3D3C = { (M504_PATH *)&lbl_1_data_2544, (M504_PATH *)&lbl_1_data_2554, 1, 0, { (M504_NODE *)&lbl_1_data_3D4C } };
/* 0x3D4C */ M504_NODE1 lbl_1_data_3D4C = { (M504_PATH *)&lbl_1_data_2564, (M504_PATH *)&lbl_1_data_2574, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3D5C */ M504_NODE1 lbl_1_data_3D5C = { (M504_PATH *)&lbl_1_data_2584, (M504_PATH *)&lbl_1_data_25A0, 1, 0, { (M504_NODE *)&lbl_1_data_3D6C } };
/* 0x3D6C */ M504_NODE1 lbl_1_data_3D6C = { (M504_PATH *)&lbl_1_data_25B0, (M504_PATH *)&lbl_1_data_25C0, 1, 0, { (M504_NODE *)&lbl_1_data_3D7C } };
/* 0x3D7C */ M504_NODE2 lbl_1_data_3D7C = { (M504_PATH *)&lbl_1_data_25D0, (M504_PATH *)&lbl_1_data_25F8, 2, 0, { (M504_NODE *)&lbl_1_data_3D90, (M504_NODE *)&lbl_1_data_3DA0 } };
/* 0x3D90 */ M504_NODE1 lbl_1_data_3D90 = { (M504_PATH *)&lbl_1_data_2608, (M504_PATH *)&lbl_1_data_2624, 1, 0, { (M504_NODE *)&lbl_1_data_3DB0 } };
/* 0x3DA0 */ M504_NODE1 lbl_1_data_3DA0 = { (M504_PATH *)&lbl_1_data_2634, (M504_PATH *)&lbl_1_data_2650, 1, 0, { (M504_NODE *)&lbl_1_data_3DB0 } };
/* 0x3DB0 */ M504_NODE1 lbl_1_data_3DB0 = { (M504_PATH *)&lbl_1_data_2660, (M504_PATH *)&lbl_1_data_2670, 1, 0, { (M504_NODE *)&lbl_1_data_3DC0 } };
/* 0x3DC0 */ M504_NODE1 lbl_1_data_3DC0 = { (M504_PATH *)&lbl_1_data_2680, (M504_PATH *)&lbl_1_data_26B4, 1, 0, { (M504_NODE *)&lbl_1_data_3DD0 } };
/* 0x3DD0 */ M504_NODE1 lbl_1_data_3DD0 = { (M504_PATH *)&lbl_1_data_26C4, (M504_PATH *)&lbl_1_data_26D4, 1, 0, { (M504_NODE *)&lbl_1_data_3DE0 } };
/* 0x3DE0 */ M504_NODE1 lbl_1_data_3DE0 = { (M504_PATH *)&lbl_1_data_26E4, (M504_PATH *)&lbl_1_data_26F4, 1, 0, { (M504_NODE *)&lbl_1_data_3DF0 } };
/* 0x3DF0 */ M504_NODE1 lbl_1_data_3DF0 = { (M504_PATH *)&lbl_1_data_2704, (M504_PATH *)&lbl_1_data_2738, 1, 0, { (M504_NODE *)&lbl_1_data_3E00 } };
/* 0x3E00 */ M504_NODE1 lbl_1_data_3E00 = { (M504_PATH *)&lbl_1_data_2748, (M504_PATH *)&lbl_1_data_2758, 1, 0, { (M504_NODE *)&lbl_1_data_3E10 } };
/* 0x3E10 */ M504_NODE1 lbl_1_data_3E10 = { (M504_PATH *)&lbl_1_data_2768, (M504_PATH *)&lbl_1_data_2778, 1, 0, { (M504_NODE *)&lbl_1_data_3E20 } };
/* 0x3E20 */ M504_NODE1 lbl_1_data_3E20 = { (M504_PATH *)&lbl_1_data_2788, (M504_PATH *)&lbl_1_data_2798, 1, 0, { (M504_NODE *)&lbl_1_data_3E30 } };
/* 0x3E30 */ M504_NODE1 lbl_1_data_3E30 = { (M504_PATH *)&lbl_1_data_27A8, (M504_PATH *)&lbl_1_data_27B8, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3E40 */ M504_NODE1 lbl_1_data_3E40 = { (M504_PATH *)&lbl_1_data_27C8, (M504_PATH *)&lbl_1_data_27E4, 1, 0, { (M504_NODE *)&lbl_1_data_3E50 } };
/* 0x3E50 */ M504_NODE1 lbl_1_data_3E50 = { (M504_PATH *)&lbl_1_data_27F4, (M504_PATH *)&lbl_1_data_2804, 1, 0, { (M504_NODE *)&lbl_1_data_3E60 } };
/* 0x3E60 */ M504_NODE2 lbl_1_data_3E60 = { (M504_PATH *)&lbl_1_data_2814, (M504_PATH *)&lbl_1_data_2824, 2, 0, { (M504_NODE *)&lbl_1_data_3E74, (M504_NODE *)&lbl_1_data_3E84 } };
/* 0x3E74 */ M504_NODE1 lbl_1_data_3E74 = { (M504_PATH *)&lbl_1_data_2834, (M504_PATH *)&lbl_1_data_2844, 1, 0, { (M504_NODE *)&lbl_1_data_3E94 } };
/* 0x3E84 */ M504_NODE1 lbl_1_data_3E84 = { (M504_PATH *)&lbl_1_data_2854, (M504_PATH *)&lbl_1_data_2864, 1, 0, { (M504_NODE *)&lbl_1_data_3E94 } };
/* 0x3E94 */ M504_NODE1 lbl_1_data_3E94 = { (M504_PATH *)&lbl_1_data_2874, (M504_PATH *)&lbl_1_data_2890, 1, 0, { (M504_NODE *)&lbl_1_data_3EA4 } };
/* 0x3EA4 */ M504_NODE2 lbl_1_data_3EA4 = { (M504_PATH *)&lbl_1_data_28A0, (M504_PATH *)&lbl_1_data_28B0, 2, 0, { (M504_NODE *)&lbl_1_data_3EB8, (M504_NODE *)&lbl_1_data_3EC8 } };
/* 0x3EB8 */ M504_NODE1 lbl_1_data_3EB8 = { (M504_PATH *)&lbl_1_data_28C0, (M504_PATH *)&lbl_1_data_28D0, 1, 0, { (M504_NODE *)&lbl_1_data_3ED8 } };
/* 0x3EC8 */ M504_NODE1 lbl_1_data_3EC8 = { (M504_PATH *)&lbl_1_data_28E0, (M504_PATH *)&lbl_1_data_28F0, 1, 0, { (M504_NODE *)&lbl_1_data_3ED8 } };
/* 0x3ED8 */ M504_NODE1 lbl_1_data_3ED8 = { (M504_PATH *)&lbl_1_data_2900, (M504_PATH *)&lbl_1_data_291C, 1, 0, { (M504_NODE *)&lbl_1_data_3EE8 } };
/* 0x3EE8 */ M504_NODE1 lbl_1_data_3EE8 = { (M504_PATH *)&lbl_1_data_292C, (M504_PATH *)&lbl_1_data_293C, 1, 0, { (M504_NODE *)&lbl_1_data_3EF8 } };
/* 0x3EF8 */ M504_NODE1 lbl_1_data_3EF8 = { (M504_PATH *)&lbl_1_data_294C, (M504_PATH *)&lbl_1_data_295C, 1, 0, { (M504_NODE *)&lbl_1_data_3F08 } };
/* 0x3F08 */ M504_NODE1 lbl_1_data_3F08 = { (M504_PATH *)&lbl_1_data_296C, (M504_PATH *)&lbl_1_data_297C, 1, 0, { (M504_NODE *)&lbl_1_data_3F18 } };
/* 0x3F18 */ M504_NODE1 lbl_1_data_3F18 = { (M504_PATH *)&lbl_1_data_298C, (M504_PATH *)&lbl_1_data_299C, 1, 0, { (M504_NODE *)&lbl_1_data_3F28 } };
/* 0x3F28 */ M504_NODE1 lbl_1_data_3F28 = { (M504_PATH *)&lbl_1_data_29AC, (M504_PATH *)&lbl_1_data_29BC, 1, 0, { (M504_NODE *)&lbl_1_data_3F38 } };
/* 0x3F38 */ M504_NODE1 lbl_1_data_3F38 = { (M504_PATH *)&lbl_1_data_29CC, (M504_PATH *)&lbl_1_data_29DC, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x3F48 */ M504_NODE1 lbl_1_data_3F48 = { (M504_PATH *)&lbl_1_data_29EC, (M504_PATH *)&lbl_1_data_29FC, 1, 0, { (M504_NODE *)&lbl_1_data_3F58 } };
/* 0x3F58 */ M504_NODE1 lbl_1_data_3F58 = { (M504_PATH *)&lbl_1_data_2A0C, (M504_PATH *)&lbl_1_data_2A34, 1, 0, { (M504_NODE *)&lbl_1_data_3F68 } };
/* 0x3F68 */ M504_NODE1 lbl_1_data_3F68 = { (M504_PATH *)&lbl_1_data_2A44, (M504_PATH *)&lbl_1_data_2A54, 1, 0, { (M504_NODE *)&lbl_1_data_3F78 } };
/* 0x3F78 */ M504_NODE2 lbl_1_data_3F78 = { (M504_PATH *)&lbl_1_data_2A64, (M504_PATH *)&lbl_1_data_2A74, 2, 0, { (M504_NODE *)&lbl_1_data_3F8C, (M504_NODE *)&lbl_1_data_3F9C } };
/* 0x3F8C */ M504_NODE1 lbl_1_data_3F8C = { (M504_PATH *)&lbl_1_data_2A84, (M504_PATH *)&lbl_1_data_2A94, 1, 0, { (M504_NODE *)&lbl_1_data_3FAC } };
/* 0x3F9C */ M504_NODE1 lbl_1_data_3F9C = { (M504_PATH *)&lbl_1_data_2AA4, (M504_PATH *)&lbl_1_data_2AB4, 1, 0, { (M504_NODE *)&lbl_1_data_3FAC } };
/* 0x3FAC */ M504_NODE1 lbl_1_data_3FAC = { (M504_PATH *)&lbl_1_data_2AC4, (M504_PATH *)&lbl_1_data_2AD4, 1, 0, { (M504_NODE *)&lbl_1_data_3FBC } };
/* 0x3FBC */ M504_NODE1 lbl_1_data_3FBC = { (M504_PATH *)&lbl_1_data_2AE4, (M504_PATH *)&lbl_1_data_2B0C, 1, 0, { (M504_NODE *)&lbl_1_data_3FCC } };
/* 0x3FCC */ M504_NODE2 lbl_1_data_3FCC = { (M504_PATH *)&lbl_1_data_2B1C, (M504_PATH *)&lbl_1_data_2B2C, 1, 0, { (M504_NODE *)&lbl_1_data_3FE0, (M504_NODE *)&lbl_1_data_3FF0 } }; /* retail: num 1 but 2 children */
/* 0x3FE0 */ M504_NODE1 lbl_1_data_3FE0 = { (M504_PATH *)&lbl_1_data_2B3C, (M504_PATH *)&lbl_1_data_2B4C, 1, 0, { (M504_NODE *)&lbl_1_data_4000 } };
/* 0x3FF0 */ M504_NODE1 lbl_1_data_3FF0 = { (M504_PATH *)&lbl_1_data_2B5C, (M504_PATH *)&lbl_1_data_2B6C, 1, 0, { (M504_NODE *)&lbl_1_data_4000 } };
/* 0x4000 */ M504_NODE1 lbl_1_data_4000 = { (M504_PATH *)&lbl_1_data_2B7C, (M504_PATH *)&lbl_1_data_2B98, 1, 0, { (M504_NODE *)&lbl_1_data_4010 } };
/* 0x4010 */ M504_NODE1 lbl_1_data_4010 = { (M504_PATH *)&lbl_1_data_2BA8, (M504_PATH *)&lbl_1_data_2BB8, 1, 0, { (M504_NODE *)&lbl_1_data_4020 } };
/* 0x4020 */ M504_NODE1 lbl_1_data_4020 = { (M504_PATH *)&lbl_1_data_2BC8, (M504_PATH *)&lbl_1_data_2BD8, 1, 0, { (M504_NODE *)&lbl_1_data_4030 } };
/* 0x4030 */ M504_NODE1 lbl_1_data_4030 = { (M504_PATH *)&lbl_1_data_2BE8, (M504_PATH *)&lbl_1_data_2BF8, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x4040 */ M504_NODE1 lbl_1_data_4040 = { (M504_PATH *)&lbl_1_data_2C08, (M504_PATH *)&lbl_1_data_2C48, 1, 0, { (M504_NODE *)&lbl_1_data_4050 } };
/* 0x4050 */ M504_NODE1 lbl_1_data_4050 = { (M504_PATH *)&lbl_1_data_2C58, (M504_PATH *)&lbl_1_data_2C68, 1, 0, { (M504_NODE *)&lbl_1_data_4060 } };
/* 0x4060 */ M504_NODE2 lbl_1_data_4060 = { (M504_PATH *)&lbl_1_data_2C78, (M504_PATH *)&lbl_1_data_2C88, 2, 0, { (M504_NODE *)&lbl_1_data_4074, (M504_NODE *)&lbl_1_data_4084 } };
/* 0x4074 */ M504_NODE1 lbl_1_data_4074 = { (M504_PATH *)&lbl_1_data_2C98, (M504_PATH *)&lbl_1_data_2CA8, 1, 0, { (M504_NODE *)&lbl_1_data_4094 } };
/* 0x4084 */ M504_NODE1 lbl_1_data_4084 = { (M504_PATH *)&lbl_1_data_2CB8, (M504_PATH *)&lbl_1_data_2CC8, 1, 0, { (M504_NODE *)&lbl_1_data_4094 } };
/* 0x4094 */ M504_NODE1 lbl_1_data_4094 = { (M504_PATH *)&lbl_1_data_2CD8, (M504_PATH *)&lbl_1_data_2CE8, 1, 0, { (M504_NODE *)&lbl_1_data_40A4 } };
/* 0x40A4 */ M504_NODE1 lbl_1_data_40A4 = { (M504_PATH *)&lbl_1_data_2CF8, (M504_PATH *)&lbl_1_data_2D08, 1, 0, { (M504_NODE *)&lbl_1_data_40B4 } };
/* 0x40B4 */ M504_NODE1 lbl_1_data_40B4 = { (M504_PATH *)&lbl_1_data_2D18, (M504_PATH *)&lbl_1_data_2D28, 1, 0, { (M504_NODE *)&lbl_1_data_40C4 } };
/* 0x40C4 */ M504_NODE1 lbl_1_data_40C4 = { (M504_PATH *)&lbl_1_data_2D38, (M504_PATH *)&lbl_1_data_2D54, 1, 0, { (M504_NODE *)&lbl_1_data_40D4 } };
/* 0x40D4 */ M504_NODE1 lbl_1_data_40D4 = { (M504_PATH *)&lbl_1_data_2D64, (M504_PATH *)&lbl_1_data_2D74, 1, 0, { (M504_NODE *)&lbl_1_data_40E4 } };
/* 0x40E4 */ M504_NODE1 lbl_1_data_40E4 = { (M504_PATH *)&lbl_1_data_2D84, (M504_PATH *)&lbl_1_data_2D94, 1, 0, { (M504_NODE *)&lbl_1_data_40F4 } };
/* 0x40F4 */ M504_NODE1 lbl_1_data_40F4 = { (M504_PATH *)&lbl_1_data_2DA4, (M504_PATH *)&lbl_1_data_2DB4, 1, 0, { (M504_NODE *)&lbl_1_data_4104 } };
/* 0x4104 */ M504_NODE1 lbl_1_data_4104 = { (M504_PATH *)&lbl_1_data_2DC4, (M504_PATH *)&lbl_1_data_2DD4, 1, 0, { (M504_NODE *)&lbl_1_data_4114 } };
/* 0x4114 */ M504_NODE1 lbl_1_data_4114 = { (M504_PATH *)&lbl_1_data_2DE4, (M504_PATH *)&lbl_1_data_2DF4, 1, 0, { (M504_NODE *)&lbl_1_data_4124 } };
/* 0x4124 */ M504_NODE1 lbl_1_data_4124 = { (M504_PATH *)&lbl_1_data_538, NULL, 1, 0, { NULL } };
/* 0x4134 */ M504_NODE *lbl_1_data_4134[] = {
    (M504_NODE *)&lbl_1_bss_7810,
    (M504_NODE *)&lbl_1_data_2ED4,
    (M504_NODE *)&lbl_1_data_2EE4,
    (M504_NODE *)&lbl_1_data_2EFC,
    (M504_NODE *)&lbl_1_data_2F0C,
    (M504_NODE *)&lbl_1_data_2F20,
    (M504_NODE *)&lbl_1_data_2F30,
    (M504_NODE *)&lbl_1_data_2F40,
    (M504_NODE *)&lbl_1_data_2F50,
    (M504_NODE *)&lbl_1_data_2F60,
    (M504_NODE *)&lbl_1_data_2F70,
    (M504_NODE *)&lbl_1_data_2F88,
    (M504_NODE *)&lbl_1_data_2F98,
    (M504_NODE *)&lbl_1_data_2FA8,
    (M504_NODE *)&lbl_1_data_2FB8,
    (M504_NODE *)&lbl_1_data_2FC8,
    (M504_NODE *)&lbl_1_data_2FD8,
    (M504_NODE *)&lbl_1_data_2FE8,
    (M504_NODE *)&lbl_1_data_2FF8,
    (M504_NODE *)&lbl_1_data_3008,
    (M504_NODE *)&lbl_1_data_3020,
    (M504_NODE *)&lbl_1_data_3030,
    (M504_NODE *)&lbl_1_data_3044,
    (M504_NODE *)&lbl_1_data_3054,
    (M504_NODE *)&lbl_1_data_3064,
    (M504_NODE *)&lbl_1_data_3074,
    (M504_NODE *)&lbl_1_data_3084,
    (M504_NODE *)&lbl_1_data_3094,
    (M504_NODE *)&lbl_1_data_30A4,
    (M504_NODE *)&lbl_1_data_30B4,
    (M504_NODE *)&lbl_1_data_30C4,
    (M504_NODE *)&lbl_1_data_30D4,
    (M504_NODE *)&lbl_1_data_30E4,
    (M504_NODE *)&lbl_1_data_30F4,
    (M504_NODE *)&lbl_1_data_3104,
    (M504_NODE *)&lbl_1_data_3114,
    (M504_NODE *)&lbl_1_data_3124,
    (M504_NODE *)&lbl_1_data_3134,
    (M504_NODE *)&lbl_1_data_3144,
    (M504_NODE *)&lbl_1_data_3154,
    (M504_NODE *)&lbl_1_data_3164,
    (M504_NODE *)&lbl_1_data_3174,
    (M504_NODE *)&lbl_1_data_3184,
    (M504_NODE *)&lbl_1_data_3194,
    (M504_NODE *)&lbl_1_data_31A4,
    (M504_NODE *)&lbl_1_data_31B4,
    (M504_NODE *)&lbl_1_data_31C4,
    (M504_NODE *)&lbl_1_data_31D4,
    (M504_NODE *)&lbl_1_data_31E4,
    (M504_NODE *)&lbl_1_data_31F4,
    (M504_NODE *)&lbl_1_data_3204,
    (M504_NODE *)&lbl_1_data_3214,
    (M504_NODE *)&lbl_1_data_3224,
    (M504_NODE *)&lbl_1_data_3234,
    (M504_NODE *)&lbl_1_data_3244,
    (M504_NODE *)&lbl_1_data_3254,
    (M504_NODE *)&lbl_1_data_3264,
    (M504_NODE *)&lbl_1_data_3274,
    (M504_NODE *)&lbl_1_data_3284,
    (M504_NODE *)&lbl_1_data_3294,
    (M504_NODE *)&lbl_1_data_32A4,
    (M504_NODE *)&lbl_1_data_32B4,
    (M504_NODE *)&lbl_1_data_32C4,
    (M504_NODE *)&lbl_1_data_32D4,
    (M504_NODE *)&lbl_1_data_32E4,
    (M504_NODE *)&lbl_1_data_32F4,
    (M504_NODE *)&lbl_1_data_3304,
    (M504_NODE *)&lbl_1_data_3314,
    (M504_NODE *)&lbl_1_data_3324,
    (M504_NODE *)&lbl_1_data_3334,
    (M504_NODE *)&lbl_1_data_3344,
    (M504_NODE *)&lbl_1_data_3354,
    (M504_NODE *)&lbl_1_data_3364,
    (M504_NODE *)&lbl_1_data_3374,
    (M504_NODE *)&lbl_1_data_3384,
    (M504_NODE *)&lbl_1_data_3394,
    (M504_NODE *)&lbl_1_data_33A4,
    (M504_NODE *)&lbl_1_data_33B4,
    (M504_NODE *)&lbl_1_data_33C4,
    (M504_NODE *)&lbl_1_data_33D4,
    (M504_NODE *)&lbl_1_data_33E4,
    (M504_NODE *)&lbl_1_data_33F4,
    (M504_NODE *)&lbl_1_data_3404,
    (M504_NODE *)&lbl_1_data_3414,
    (M504_NODE *)&lbl_1_data_3424,
    (M504_NODE *)&lbl_1_data_3434,
    (M504_NODE *)&lbl_1_data_3444,
    (M504_NODE *)&lbl_1_data_3454,
    (M504_NODE *)&lbl_1_data_3464,
    (M504_NODE *)&lbl_1_data_3474,
    (M504_NODE *)&lbl_1_data_3484,
    (M504_NODE *)&lbl_1_data_3494,
    (M504_NODE *)&lbl_1_data_34A4,
    (M504_NODE *)&lbl_1_data_34B4,
    (M504_NODE *)&lbl_1_data_34C4,
    (M504_NODE *)&lbl_1_data_34D4,
    (M504_NODE *)&lbl_1_data_34E4,
    (M504_NODE *)&lbl_1_data_34F4,
    (M504_NODE *)&lbl_1_data_3504,
    (M504_NODE *)&lbl_1_data_3514,
    (M504_NODE *)&lbl_1_data_3524,
    (M504_NODE *)&lbl_1_data_3534,
    (M504_NODE *)&lbl_1_data_3544,
    (M504_NODE *)&lbl_1_data_3554,
    (M504_NODE *)&lbl_1_data_3564,
    (M504_NODE *)&lbl_1_data_3574,
    (M504_NODE *)&lbl_1_data_3584,
    (M504_NODE *)&lbl_1_data_3594,
    (M504_NODE *)&lbl_1_data_35A4,
    (M504_NODE *)&lbl_1_data_35B4,
    (M504_NODE *)&lbl_1_data_35C4,
    (M504_NODE *)&lbl_1_data_35D4,
    (M504_NODE *)&lbl_1_data_35E4,
    (M504_NODE *)&lbl_1_data_35F4,
    (M504_NODE *)&lbl_1_data_3604,
    (M504_NODE *)&lbl_1_data_3614,
    (M504_NODE *)&lbl_1_data_3624,
    (M504_NODE *)&lbl_1_data_3634,
    (M504_NODE *)&lbl_1_data_3644,
    (M504_NODE *)&lbl_1_data_3654,
    (M504_NODE *)&lbl_1_data_3664,
    (M504_NODE *)&lbl_1_data_3674,
    (M504_NODE *)&lbl_1_data_3684,
    (M504_NODE *)&lbl_1_data_3694,
    (M504_NODE *)&lbl_1_data_36A4,
    (M504_NODE *)&lbl_1_data_36B4,
    (M504_NODE *)&lbl_1_data_36C4,
    (M504_NODE *)&lbl_1_data_36D4,
    (M504_NODE *)&lbl_1_data_36E4,
    (M504_NODE *)&lbl_1_data_36F4,
    (M504_NODE *)&lbl_1_data_3704,
    (M504_NODE *)&lbl_1_data_3714,
    (M504_NODE *)&lbl_1_data_3724,
    (M504_NODE *)&lbl_1_data_3734,
    (M504_NODE *)&lbl_1_data_3744,
    (M504_NODE *)&lbl_1_data_3754,
    (M504_NODE *)&lbl_1_data_3764,
    (M504_NODE *)&lbl_1_data_3774,
    (M504_NODE *)&lbl_1_data_3784,
    (M504_NODE *)&lbl_1_data_3794,
    (M504_NODE *)&lbl_1_data_37A4,
    (M504_NODE *)&lbl_1_data_37B4,
    (M504_NODE *)&lbl_1_data_37C4,
    (M504_NODE *)&lbl_1_data_37D4,
    (M504_NODE *)&lbl_1_data_37E4,
    (M504_NODE *)&lbl_1_data_37F4,
    (M504_NODE *)&lbl_1_data_3804,
    (M504_NODE *)&lbl_1_data_3814,
    (M504_NODE *)&lbl_1_data_3824,
    (M504_NODE *)&lbl_1_data_3834,
    (M504_NODE *)&lbl_1_data_3844,
    (M504_NODE *)&lbl_1_data_3854,
    (M504_NODE *)&lbl_1_data_3864,
    (M504_NODE *)&lbl_1_data_3874,
    (M504_NODE *)&lbl_1_data_3884,
    (M504_NODE *)&lbl_1_data_3894,
    (M504_NODE *)&lbl_1_data_38A4,
    (M504_NODE *)&lbl_1_data_38B4,
    (M504_NODE *)&lbl_1_data_38C4,
    (M504_NODE *)&lbl_1_data_38D4,
    (M504_NODE *)&lbl_1_data_38E4,
    (M504_NODE *)&lbl_1_data_38F4,
    (M504_NODE *)&lbl_1_data_3904,
    (M504_NODE *)&lbl_1_data_3914,
    (M504_NODE *)&lbl_1_data_3924,
    (M504_NODE *)&lbl_1_data_3934,
    (M504_NODE *)&lbl_1_data_3944,
    (M504_NODE *)&lbl_1_data_3954,
    (M504_NODE *)&lbl_1_data_3964,
    (M504_NODE *)&lbl_1_data_3974,
    (M504_NODE *)&lbl_1_data_3984,
    (M504_NODE *)&lbl_1_data_3994,
    (M504_NODE *)&lbl_1_data_39A4,
    (M504_NODE *)&lbl_1_data_39B4,
    (M504_NODE *)&lbl_1_data_39C4,
    (M504_NODE *)&lbl_1_data_39D4,
    (M504_NODE *)&lbl_1_data_39E4,
    (M504_NODE *)&lbl_1_data_39F4,
    (M504_NODE *)&lbl_1_data_3A04,
    (M504_NODE *)&lbl_1_data_3A14,
    (M504_NODE *)&lbl_1_data_3A24,
    (M504_NODE *)&lbl_1_data_3A34,
    (M504_NODE *)&lbl_1_data_3A44,
    (M504_NODE *)&lbl_1_data_3A54,
    (M504_NODE *)&lbl_1_data_3A64,
    (M504_NODE *)&lbl_1_data_3A74,
    (M504_NODE *)&lbl_1_data_3A84,
    (M504_NODE *)&lbl_1_data_3A94,
    (M504_NODE *)&lbl_1_data_3AA4,
    (M504_NODE *)&lbl_1_data_3AB4,
    (M504_NODE *)&lbl_1_data_3AC4,
    (M504_NODE *)&lbl_1_data_3AD4,
    (M504_NODE *)&lbl_1_data_3AE4,
    (M504_NODE *)&lbl_1_data_3AF4,
    (M504_NODE *)&lbl_1_data_3B04,
    (M504_NODE *)&lbl_1_data_3B14,
    (M504_NODE *)&lbl_1_data_3B24,
    (M504_NODE *)&lbl_1_data_3B38,
    (M504_NODE *)&lbl_1_data_3B58,
    (M504_NODE *)&lbl_1_data_3B68,
    (M504_NODE *)&lbl_1_data_3B7C,
    (M504_NODE *)&lbl_1_data_3B9C,
    (M504_NODE *)&lbl_1_data_3BAC,
    (M504_NODE *)&lbl_1_data_3BBC,
    (M504_NODE *)&lbl_1_data_3BD0,
    (M504_NODE *)&lbl_1_data_3BF0,
    (M504_NODE *)&lbl_1_data_3C00,
    (M504_NODE *)&lbl_1_data_3C10,
    (M504_NODE *)&lbl_1_data_3C20,
    (M504_NODE *)&lbl_1_data_3C30,
    (M504_NODE *)&lbl_1_data_3B48,
    (M504_NODE *)&lbl_1_data_3B8C,
    (M504_NODE *)&lbl_1_data_3BE0,
    (M504_NODE *)&lbl_1_data_3C40,
    (M504_NODE *)&lbl_1_data_3C50,
    (M504_NODE *)&lbl_1_data_3C64,
    (M504_NODE *)&lbl_1_data_3C84,
    (M504_NODE *)&lbl_1_data_3C94,
    (M504_NODE *)&lbl_1_data_3CA8,
    (M504_NODE *)&lbl_1_data_3CC8,
    (M504_NODE *)&lbl_1_data_3CD8,
    (M504_NODE *)&lbl_1_data_3CE8,
    (M504_NODE *)&lbl_1_data_3CF8,
    (M504_NODE *)&lbl_1_data_3D08,
    (M504_NODE *)&lbl_1_data_3D1C,
    (M504_NODE *)&lbl_1_data_3D3C,
    (M504_NODE *)&lbl_1_data_3D4C,
    (M504_NODE *)&lbl_1_data_3C74,
    (M504_NODE *)&lbl_1_data_3CB8,
    (M504_NODE *)&lbl_1_data_3D2C,
    (M504_NODE *)&lbl_1_data_3D5C,
    (M504_NODE *)&lbl_1_data_3D6C,
    (M504_NODE *)&lbl_1_data_3D7C,
    (M504_NODE *)&lbl_1_data_3D90,
    (M504_NODE *)&lbl_1_data_3DB0,
    (M504_NODE *)&lbl_1_data_3DC0,
    (M504_NODE *)&lbl_1_data_3DD0,
    (M504_NODE *)&lbl_1_data_3DE0,
    (M504_NODE *)&lbl_1_data_3DF0,
    (M504_NODE *)&lbl_1_data_3E00,
    (M504_NODE *)&lbl_1_data_3E10,
    (M504_NODE *)&lbl_1_data_3E20,
    (M504_NODE *)&lbl_1_data_3E30,
    (M504_NODE *)&lbl_1_data_3DA0,
    (M504_NODE *)&lbl_1_data_3E40,
    (M504_NODE *)&lbl_1_data_3E50,
    (M504_NODE *)&lbl_1_data_3E60,
    (M504_NODE *)&lbl_1_data_3E74,
    (M504_NODE *)&lbl_1_data_3E94,
    (M504_NODE *)&lbl_1_data_3EA4,
    (M504_NODE *)&lbl_1_data_3EB8,
    (M504_NODE *)&lbl_1_data_3ED8,
    (M504_NODE *)&lbl_1_data_3EE8,
    (M504_NODE *)&lbl_1_data_3EF8,
    (M504_NODE *)&lbl_1_data_3F08,
    (M504_NODE *)&lbl_1_data_3F18,
    (M504_NODE *)&lbl_1_data_3F28,
    (M504_NODE *)&lbl_1_data_3F38,
    (M504_NODE *)&lbl_1_data_3E84,
    (M504_NODE *)&lbl_1_data_3EC8,
    (M504_NODE *)&lbl_1_data_3F48,
    (M504_NODE *)&lbl_1_data_3F58,
    (M504_NODE *)&lbl_1_data_3F68,
    (M504_NODE *)&lbl_1_data_3F78,
    (M504_NODE *)&lbl_1_data_3F8C,
    (M504_NODE *)&lbl_1_data_3FAC,
    (M504_NODE *)&lbl_1_data_3FBC,
    (M504_NODE *)&lbl_1_data_3FCC,
    (M504_NODE *)&lbl_1_data_3FE0,
    (M504_NODE *)&lbl_1_data_4000,
    (M504_NODE *)&lbl_1_data_4010,
    (M504_NODE *)&lbl_1_data_4020,
    (M504_NODE *)&lbl_1_data_4030,
    (M504_NODE *)&lbl_1_data_3F9C,
    (M504_NODE *)&lbl_1_data_3FF0,
    (M504_NODE *)&lbl_1_data_4040,
    (M504_NODE *)&lbl_1_data_4050,
    (M504_NODE *)&lbl_1_data_4060,
    (M504_NODE *)&lbl_1_data_4074,
    (M504_NODE *)&lbl_1_data_4094,
    (M504_NODE *)&lbl_1_data_40A4,
    (M504_NODE *)&lbl_1_data_40B4,
    (M504_NODE *)&lbl_1_data_40C4,
    (M504_NODE *)&lbl_1_data_40D4,
    (M504_NODE *)&lbl_1_data_40E4,
    (M504_NODE *)&lbl_1_data_40F4,
    (M504_NODE *)&lbl_1_data_4104,
    (M504_NODE *)&lbl_1_data_4114,
    (M504_NODE *)&lbl_1_data_4084,
    (M504_NODE *)&lbl_1_data_4124
};

/* --- functions (reference order) --- */
/* 28 insns */
void fn_1_B828(M504_INPUT *input, s32 playerNo, M504_PLAYER *player)
{
    memset(input, 0, sizeof(M504_INPUT));
    input->unk000 = player;
    input->unk028 = GwPlayerConf[playerNo].padNo;
    fn_1_BAC4(&input->unk004, input);
}

/* 16 insns */
void fn_1_B898(M504_INPUT *input)
{
    fn_1_BC54(&input->unk004);
    memset(input, 0, sizeof(M504_INPUT));
}

/* 123 insns */
void fn_1_B8D8(M504_INPUT *input)
{
    if (input->unk004.unk010 != 0) {
        fn_1_BC84(&input->unk004);
    }
    else {
        input->unk02C = HuPadBtn[input->unk028];
        input->unk030 = HuPadBtnDown[input->unk028];
        input->unk036 = HuPadBtnRep[input->unk028];
        input->unk034 = HuPadStkX[input->unk028];
        input->unk034 = (((input->unk034 >= 0) ? input->unk034 : -input->unk034) < 10) ? 0 : input->unk034;
        input->unk035 = HuPadStkY[input->unk028];
        input->unk035 = (((input->unk035 >= 0) ? input->unk035 : -input->unk035) < 10) ? 0 : input->unk035;
        input->unk038 = HuPadSubStkX[input->unk028];
        input->unk039 = HuPadSubStkY[input->unk028];
        input->unk03A = HuPadTrigL[input->unk028];
        input->unk03B = HuPadTrigR[input->unk028];
        input->unk03C = HuPadDStk[input->unk028];
        input->unk03D = HuPadDStkRep[input->unk028];
    }
}

/* 100 insns */
void fn_1_BAC4(M504_COM *com, M504_INPUT *input)
{
    s32 i;
    s32 no = input->unk000->unk000->unk004;

    memset(com, 0, sizeof(M504_COM));
    com->unk000 = input;
    com->unk010 = GwPlayerConf[no].type;
    com->unk014 = (GwPlayerConf[no].dif == 3) ? 0 : (GwPlayerConf[no].dif == 2) ? 1 : (GwPlayerConf[no].dif == 1) ? 2 : 3;
    com->unk008 = (com->unk014 == 0) ? (M504_NODE *)&lbl_1_data_2E14
        : (com->unk014 == 1) ? (M504_NODE *)&lbl_1_data_2E38
        : (com->unk014 == 2) ? (M504_NODE *)&lbl_1_data_2E74
        : (M504_NODE *)&lbl_1_data_2EB0;
    for (i = 0; lbl_1_data_4134[i] != NULL; i++) {
        lbl_1_data_4134[i]->unk0A = 0;
    }
}
