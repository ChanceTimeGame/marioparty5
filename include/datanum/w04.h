#ifndef DATANUM_W04_H
#define DATANUM_W04_H

#include "datadir_enum.h"

/*
 * Entries are named only after their consumers have been decoded; the rest
 * keep their index. 0x05 and 0x34 are not referenced by world04.c at all
 * and are left out.
 */
enum {
    W04_BIN_masuData   = DATANUM(DATA_w04, 0x00),
    W04_HSF_map        = DATANUM(DATA_w04, 0x01),
    W04_HSF_obj02      = DATANUM(DATA_w04, 0x02),
    W04_HSF_akari      = DATANUM(DATA_w04, 0x03),
    W04_HSF_hasigo     = DATANUM(DATA_w04, 0x04),
    W04_HSF_sKai       = DATANUM(DATA_w04, 0x06),
    W04_HSF_rBok       = DATANUM(DATA_w04, 0x07),
    W04_HSF_sangoO     = DATANUM(DATA_w04, 0x08),
    W04_HSF_kai0       = DATANUM(DATA_w04, 0x09),
    W04_HSF_kai1       = DATANUM(DATA_w04, 0x0A),
    W04_HSF_kai2       = DATANUM(DATA_w04, 0x0B),
    W04_HSF_kaisooEv0  = DATANUM(DATA_w04, 0x0C),
    W04_HSF_kaisooEv1  = DATANUM(DATA_w04, 0x0D),
    W04_HSF_kaisooEv2  = DATANUM(DATA_w04, 0x0E),
    W04_HSF_blowEv     = DATANUM(DATA_w04, 0x0F),
    W04_HSF_kihonEv    = DATANUM(DATA_w04, 0x10),
    W04_HSF_coinLink   = DATANUM(DATA_w04, 0x11),
    W04_HSF_obj12      = DATANUM(DATA_w04, 0x12),
    W04_HSF_obj13      = DATANUM(DATA_w04, 0x13),
    W04_HSF_obj14      = DATANUM(DATA_w04, 0x14),
    W04_HSF_puku0      = DATANUM(DATA_w04, 0x15),
    W04_HSF_puku1      = DATANUM(DATA_w04, 0x16),
    W04_HSF_irukaEv    = DATANUM(DATA_w04, 0x17),
    W04_HSF_yazi       = DATANUM(DATA_w04, 0x18),
    W04_HSF_ueYazi     = DATANUM(DATA_w04, 0x19),
    W04_HSF_sakana0    = DATANUM(DATA_w04, 0x1A),
    W04_HSF_sakana1    = DATANUM(DATA_w04, 0x1B),
    W04_HSF_sakana2    = DATANUM(DATA_w04, 0x1C),
    W04_HSF_sakana3    = DATANUM(DATA_w04, 0x1D),
    W04_HSF_sango1     = DATANUM(DATA_w04, 0x1E),
    W04_HSF_sango2     = DATANUM(DATA_w04, 0x1F),
    W04_HSF_sango3     = DATANUM(DATA_w04, 0x20),
    W04_HSF_sango4     = DATANUM(DATA_w04, 0x21),
    W04_HSF_sango5     = DATANUM(DATA_w04, 0x22),
    W04_HSF_hitode1    = DATANUM(DATA_w04, 0x23),
    W04_HSF_hitode2    = DATANUM(DATA_w04, 0x24),
    W04_HSF_kaisoo     = DATANUM(DATA_w04, 0x25),
    W04_HSF_kihonChr   = DATANUM(DATA_w04, 0x26),
    W04_HSF_mapViewOff = DATANUM(DATA_w04, 0x27),
    W04_HSF_puku2      = DATANUM(DATA_w04, 0x28),
    W04_ANM_puku2_0    = DATANUM(DATA_w04, 0x29),
    W04_ANM_puku2_1    = DATANUM(DATA_w04, 0x2A),
    W04_HSF_kihonSipp  = DATANUM(DATA_w04, 0x2B),
    W04_ANM_kihonSipp0 = DATANUM(DATA_w04, 0x2C),
    W04_ANM_kihonSipp1 = DATANUM(DATA_w04, 0x2D),
    W04_ANM_kihonSipp2 = DATANUM(DATA_w04, 0x2E),
    W04_HSF_iruka      = DATANUM(DATA_w04, 0x2F),
    W04_ANM_iruka      = DATANUM(DATA_w04, 0x30),
    W04_HSF_scrollCol  = DATANUM(DATA_w04, 0x31),
    W04_HSF_capsuleCol = DATANUM(DATA_w04, 0x32),
    W04_ANM_bubbleEff  = DATANUM(DATA_w04, 0x33),
    W04_SPR_sakana     = DATANUM(DATA_w04, 0x35)
};

#endif
