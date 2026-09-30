#ifndef M532_PARAM_H
#define M532_PARAM_H

inline int RoundTimeInit() { return 300; }
inline int ReactTimeInit() { return 60; }
static int s_roundTime = RoundTimeInit(); /* 300 */
static int s_reactTime = ReactTimeInit(); /* 60 */

#endif
