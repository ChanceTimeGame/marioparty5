#ifndef DATANUM_W02_H
#define DATANUM_W02_H

#include "datadir_enum.h"

/* Named as they are identified; the numbers are the disc's. Entries 1-26 are
 * the board's scenery models, created in MB2_Create in an order that is not
 * their file order -- what each one is has not been established, so they keep
 * their file numbers. */
enum {
    W02_BIN_masuData = DATANUM(DATA_w02, 0),
    W02_HSF_obj01,
    W02_HSF_obj02,
    W02_HSF_obj03,
    W02_HSF_obj04,
    W02_HSF_obj05,
    W02_HSF_obj06,
    W02_HSF_obj07,
    W02_HSF_obj08,
    W02_HSF_obj09,
    W02_HSF_obj10,
    W02_HSF_obj11,
    W02_HSF_obj12,
    W02_HSF_obj13,
    W02_HSF_obj14,
    W02_HSF_obj15,
    W02_HSF_obj16,
    W02_HSF_obj17,
    W02_HSF_obj18,
    W02_HSF_obj19,
    W02_HSF_obj20,
    W02_HSF_obj21,
    W02_HSF_obj22,
    W02_HSF_obj23,
    W02_HSF_obj24,
    W02_HSF_obj25,
    W02_HSF_obj26,
    W02_HSF_scrollCol,
    W02_HSF_capsuleCol,
    W02_ANM_board,
    W02_ANM_splashEff,
};

#endif
