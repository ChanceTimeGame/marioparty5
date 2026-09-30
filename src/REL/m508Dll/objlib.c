/*
 * objlib.c -- m508Dll's shared object library, written once and #included by
 * BOTH of the overlay's translation units.  m508.o carries it at fn_1_5D20..
 * fn_1_A114 and object.o carries a second copy of the same code; the bodies
 * below are m526dll/math.c plus m540dll/object.c (function for function, in
 * file order), with m508's names.
 *
 * An #included .c file is compiled before the including file's own code -- so
 * CodeWarrior can inline it into that code with plain -inline auto -- yet its
 * .text is emitted as a separate section AFTER the including file's, which is
 * where the reference puts this library.  See games/mp5/src/REL/m540dll/NOTES.md.
 *
 * M508_CAMTBL is the three-entry camera state table.  It is a per-unit object
 * (lbl_1_data_0 in m508.o, lbl_1_data_B0 in object.o), so the including unit
 * names it.
 */

#include "REL/m526Dll/math.c"

#ifndef M508_CAMTBL
#define M508_CAMTBL lbl_1_data_0
#endif
extern void (*M508_CAMTBL[3])(void *);

/* --- prototypes (reference order) --- */
static M508_OBJ *fn_1_7848(s32 prio, s32 stackSize, s32 funcMax, M508_OBJFUNC *funcTbl);
static void fn_1_797C(M508_OBJ *obj);
static void fn_1_79BC(void);
static void fn_1_7A24(M508_OBJ *obj);
static M508_OBJ *fn_1_7A3C(s32 prio, s32 stackSize, u32 mdlNum, s32 motMax, const u32 *motTbl, s32 funcMax, M508_OBJFUNC *funcTbl);
static void fn_1_7CC0(M508_OBJ *obj);
static void fn_1_7D60(M508_OBJ *obj, float x, float y, float z);
static void fn_1_7DB4(M508_OBJ *obj, float *x, float *y, float *z);
static void fn_1_7DF4(M508_OBJ *obj, float x, float y, float z);
static void fn_1_7E48(M508_OBJ *obj, float *x, float *y, float *z);
static void fn_1_7E88(M508_OBJ *obj, float x, float y, float z);
static void fn_1_7EDC(M508_OBJ *obj, float *x, float *y, float *z);
static void fn_1_7F1C(M508_OBJ *obj, float tpLvl);
static float fn_1_7F58(M508_OBJ *obj);
static void fn_1_7F60(M508_OBJ *obj);
static void fn_1_7F9C(M508_OBJ *obj);
static s32 fn_1_7FD8(M508_OBJ *obj);
static void fn_1_7FE0(M508_OBJ *obj, s32 time);
static void fn_1_803C(M508_OBJ *obj, s32 loopF);
static void fn_1_80B4(M508_OBJ *obj);
static s32 fn_1_80EC(M508_OBJ *obj);
static void fn_1_813C(M508_OBJ *obj, s32 motIdx, float start, float end, u32 attr);
static s32 fn_1_81B8(M508_OBJ *obj);
static void fn_1_81C0(M508_OBJ *obj, float speed);
static void fn_1_81FC(M508_OBJ *obj);
static void fn_1_822C(M508_OBJ *obj);
static void fn_1_825C(M508_OBJ *obj);
static void fn_1_828C(void);
static void fn_1_8290(M508_OBJ *obj, char *objName, M508_OBJ *hookObj);
static void fn_1_82D8(M508_OBJ *obj);
static M508_OBJ *fn_1_8308(s32 prio, s32 stackSize, s32 playerNo, s32 motMax, const u32 *motTbl, s32 funcMax, M508_OBJFUNC *funcTbl, s16 model);
static void fn_1_85F8(M508_OBJ *obj);
static void fn_1_8698(M508_OBJ *obj, char *hookName);
static M508_CAMERA *fn_1_86F0(s16 cameraBit);
static void fn_1_88E0(M508_CAMERA *camera);
static void fn_1_8918(void);
static void fn_1_897C(M508_CAMERA *camera);
static void fn_1_8BF4(M508_CAMERA *camera);
static void fn_1_8C64(M508_CAMERA *camera);
static void fn_1_8C70(M508_CAMERA *camera);
static void fn_1_8D24(M508_CAMERA *camera);
static void fn_1_8D30(M508_CAMERA *camera);
static BOOL fn_1_8DF8(M508_CAMERA *camera);
static void fn_1_8E28(M508_CAMERA *camera, const HuVecF *center, const HuVecF *rot, const float *zoom, int speed);
static void fn_1_926C(M508_CAMERA *camera);
static void fn_1_9578(M508_CAMERA *camera, float vpX, float vpY, float vpW, float vpH, float vpNearZ, float vpFarZ);
static void fn_1_95D8(M508_CAMERA *camera, float fov, float near, float far, float aspect);
static void fn_1_9628(M508_CAMERA *camera, float scissorX, float scissorY, float scissorW, float scissorH);
static void fn_1_96BC(M508_CAMERA *camera);
static void fn_1_9B38(M508_CAMERA *camera);
static void fn_1_9B3C(int time, int waitF);
static void fn_1_9B98(int time, int waitF);
static void fn_1_9BF4(int time);
static void fn_1_9C80(int time);
static float fn_1_9D0C(float start, float end, float t);
static M508_WIN *fn_1_9E10(int w, int h);
static void fn_1_9EB8(M508_WIN *win);
static void fn_1_9EF8(void);
static void fn_1_9F0C(M508_WIN *win, float posX, float posY);
static void fn_1_9F54(M508_WIN *win, float *posX, float *posY);
static void fn_1_9F68(M508_WIN *win, u32 mess);
static void fn_1_9FA0(M508_WIN *win);
static void fn_1_9FD8(M508_WIN *win);
static void fn_1_A010(M508_WIN *win, int mesCol);
static void fn_1_A04C(M508_WIN *win, s16 mesSpeed);
static void fn_1_A084(M508_WIN *win);
static void fn_1_A0B4(M508_WIN *win);
static void fn_1_A0E4(M508_WIN *win);
static void fn_1_A114(M508_WIN *win, float scaleX, float scaleY);

/* --- bodies: m540dll/object.c, verbatim apart from the names --- */
static M508_OBJ *fn_1_7848(s32 prio, s32 stackSize, s32 funcMax, M508_OBJFUNC *funcTbl)
{
    M508_OBJ *obj;
    s32 i;

    obj = HuMemDirectMallocNum(HEAP_HEAP, M508_OBJ_SIZE, HU_MEMNUM_OVL);
    obj->unk004 = 0;
    obj->unk008 = 0;
    obj->unk014 = funcMax;
    obj->unk00C = 0;
    obj->unk010 = HuMemDirectMallocNum(HEAP_HEAP, funcMax * sizeof(M508_OBJFUNC), HU_MEMNUM_OVL);
    for (i = 0; i < funcMax; i++) {
        obj->unk010[i] = fn_1_7A24;
    }
    obj->unk000 = HuPrcChildCreate(fn_1_79BC, prio, stackSize, 0, HuPrcCurrentGet());
    obj->unk000->property = obj;
    if (funcTbl != NULL) {
        for (i = 0; i < funcMax; i++) {
            if (funcTbl[i] != NULL) {
                obj->unk010[i] = funcTbl[i];
            }
        }
    }
    return obj;
}
static void fn_1_797C(M508_OBJ *obj)
{
    HuMemDirectFree(obj->unk010);
    HuPrcKill(obj->unk000);
    HuMemDirectFree(obj);
}
static void fn_1_79BC(void)
{
    M508_OBJ *obj;

    obj = HuPrcCurrentGet()->property;
    while (obj->unk004 < obj->unk014) {
        obj->unk010[obj->unk004](obj);
        obj->unk008 = obj->unk004;
    }
    HuPrcEnd();
}
static void fn_1_7A24(M508_OBJ *obj)
{
    while (1) {
        HuPrcSleep(0);
    }
}
static M508_OBJ *fn_1_7A3C(s32 prio, s32 stackSize, u32 mdlNum, s32 motMax, const u32 *motTbl, s32 funcMax, M508_OBJFUNC *funcTbl)
{
    M508_OBJ *obj;
    s32 i;

    obj = HuMemDirectMallocNum(HEAP_HEAP, M508_MDLOBJ_SIZE, HU_MEMNUM_OVL);
    obj->unk004 = 0;
    obj->unk008 = 0;
    obj->unk014 = funcMax;
    obj->unk158 = 1;
    obj->unk160.x = 0.0f;
    obj->unk160.y = 0.0f;
    obj->unk160.z = 0.0f;
    obj->unk16C.x = 0.0f;
    obj->unk16C.y = 0.0f;
    obj->unk16C.z = 0.0f;
    obj->unk178.x = 1.0f;
    obj->unk178.y = 1.0f;
    obj->unk178.z = 1.0f;
    obj->unk184 = -1;
    obj->unk00C = 0;
    obj->unk18C = motMax;
    obj->unk190 = HuMemDirectMallocNum(HEAP_HEAP, motMax * 2, HU_MEMNUM_OVL);
    for (i = 0; i < motMax; i++) {
        obj->unk190[i] = -1;
    }
    obj->unk010 = HuMemDirectMallocNum(HEAP_HEAP, funcMax * sizeof(M508_OBJFUNC), HU_MEMNUM_OVL);
    for (i = 0; i < funcMax; i++) {
        obj->unk010[i] = fn_1_7A24;
    }
    obj->unk000 = HuPrcChildCreate(fn_1_79BC, prio, stackSize, 0, HuPrcCurrentGet());
    obj->unk000->property = obj;
    if (mdlNum != -1) {
        obj->unk184 = Hu3DModelCreate(HuDataSelHeapReadNum(mdlNum, HU_MEMNUM_OVL, HEAP_MODEL));
    }
    for (i = 0; i < motMax; i++) {
        if (motTbl[i] != -1) {
            obj->unk190[i] = Hu3DJointMotion(obj->unk184, HuDataSelHeapReadNum(motTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        }
    }
    if (funcTbl != NULL) {
        for (i = 0; i < funcMax; i++) {
            if (funcTbl[i] != NULL) {
                obj->unk010[i] = funcTbl[i];
            }
        }
    }
    return obj;
}
static void fn_1_7CC0(M508_OBJ *obj)
{
    s32 i;

    for (i = 0; i < obj->unk18C; i++) {
        if (obj->unk190[i] != -1) {
            Hu3DMotionKill(obj->unk190[i]);
        }
    }
    HuMemDirectFree(obj->unk190);
    if (obj->unk184 != -1) {
        Hu3DModelKill(obj->unk184);
    }
    HuMemDirectFree(obj->unk010);
    HuPrcKill(obj->unk000);
    HuMemDirectFree(obj);
}
static void fn_1_7D60(M508_OBJ *obj, float x, float y, float z)
{
    M508_OBJPOSSET(obj, x, y, z);
}
static void fn_1_7DB4(M508_OBJ *obj, float *x, float *y, float *z)
{
    M508_OBJPOSGET(obj, x, y, z);
}
static void fn_1_7DF4(M508_OBJ *obj, float x, float y, float z)
{
    M508_OBJROTSET(obj, x, y, z);
}
static void fn_1_7E48(M508_OBJ *obj, float *x, float *y, float *z)
{
    if (x != NULL) {
        *x = obj->unk16C.x;
    }
    if (y != NULL) {
        *y = obj->unk16C.y;
    }
    if (z != NULL) {
        *z = obj->unk16C.z;
    }
}
static void fn_1_7E88(M508_OBJ *obj, float x, float y, float z)
{
    Hu3DModelScaleSet(obj->unk184, obj->unk178.x = x, obj->unk178.y = y, obj->unk178.z = z);
}
static void fn_1_7EDC(M508_OBJ *obj, float *x, float *y, float *z)
{
    if (x != NULL) {
        *x = obj->unk178.x;
    }
    if (y != NULL) {
        *y = obj->unk178.y;
    }
    if (z != NULL) {
        *z = obj->unk178.z;
    }
}
static void fn_1_7F1C(M508_OBJ *obj, float tpLvl)
{
    Hu3DModelTPLvlSet(obj->unk184, obj->unk1B0 = tpLvl);
}
static float fn_1_7F58(M508_OBJ *obj)
{
    return obj->unk1B0;
}
static void fn_1_7F60(M508_OBJ *obj)
{
    obj->unk158 = 1;
    Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
}
static void fn_1_7F9C(M508_OBJ *obj)
{
    obj->unk158 = 0;
    Hu3DModelAttrSet(obj->unk184, HU3D_ATTR_DISPOFF);
}
static s32 fn_1_7FD8(M508_OBJ *obj)
{
    return obj->unk158;
}
static void fn_1_7FE0(M508_OBJ *obj, s32 time)
{
    Hu3DMotionTimeSet(obj->unk184, time);
}
static void fn_1_803C(M508_OBJ *obj, s32 loopF)
{
    HU3DMODELID model;

    model = obj->unk184;
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    if (loopF) {
        Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    } else {
        Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
    }
}
static void fn_1_80B4(M508_OBJ *obj)
{
    Hu3DModelAttrSet(obj->unk184, HU3D_MOTATTR_PAUSE);
}
static s32 fn_1_80EC(M508_OBJ *obj)
{
    return (Hu3DMotionEndCheck(obj->unk184) == 0) ? 1 : 0;
}
static void fn_1_813C(M508_OBJ *obj, s32 motIdx, float start, float end, u32 attr)
{
    obj->unk188 = motIdx;
    if (motIdx == -1) {
        Hu3DMotionSet(obj->unk184, -1);
    } else {
        Hu3DMotionShiftSet(obj->unk184, obj->unk190[motIdx], start, end, attr);
    }
}
static s32 fn_1_81B8(M508_OBJ *obj)
{
    return obj->unk188;
}
static void fn_1_81C0(M508_OBJ *obj, float speed)
{
    Hu3DMotionSpeedSet(obj->unk184, obj->unk1B4 = speed);
}
static void fn_1_81FC(M508_OBJ *obj)
{
    Hu3DModelShadowSet(obj->unk184);
}
static void fn_1_822C(M508_OBJ *obj)
{
    Hu3DModelShadowReset(obj->unk184);
}
static void fn_1_825C(M508_OBJ *obj)
{
    Hu3DModelShadowMapSet(obj->unk184);
}
static void fn_1_828C(void)
{
}
static void fn_1_8290(M508_OBJ *obj, char *objName, M508_OBJ *hookObj)
{
    Hu3DModelHookSet(obj->unk184, objName, hookObj->unk184);
}
static void fn_1_82D8(M508_OBJ *obj)
{
    Hu3DModelHookReset(obj->unk184);
}
static M508_OBJ *fn_1_8308(s32 prio, s32 stackSize, s32 playerNo, s32 motMax, const u32 *motTbl, s32 funcMax, M508_OBJFUNC *funcTbl, s16 model)
{
    M508_OBJ *obj;
    s32 i;
    s32 idx;

    obj = HuMemDirectMallocNum(HEAP_HEAP, M508_CHROBJ_SIZE, HU_MEMNUM_OVL);
    obj->unk004 = 0;
    obj->unk008 = 0;
    obj->unk014 = funcMax;
    obj->unk158 = 1;
    obj->unk160.x = 0.0f;
    obj->unk160.y = 0.0f;
    obj->unk160.z = 0.0f;
    obj->unk16C.x = 0.0f;
    obj->unk16C.y = 0.0f;
    obj->unk16C.z = 0.0f;
    obj->unk178.x = 1.0f;
    obj->unk178.y = 1.0f;
    obj->unk178.z = 1.0f;
    obj->unk184 = -1;
    obj->unk1B8 = GwPlayerConf[playerNo].type ? 1 : 0;
    obj->unk1BC = GwPlayerConf[playerNo].charNo;
    obj->unk1C0 = GwPlayerConf[playerNo].padNo;
    obj->unk1C4 = GwPlayerConf[playerNo].dif;
    obj->unk1C8 = playerNo;
    obj->unk00C = 0;
    obj->unk18C = motMax;
    obj->unk190 = HuMemDirectMallocNum(HEAP_HEAP, motMax * 2, HU_MEMNUM_OVL);
    for (i = 0; i < motMax; i++) {
        obj->unk190[i] = -1;
    }
    obj->unk010 = HuMemDirectMallocNum(HEAP_HEAP, funcMax * sizeof(M508_OBJFUNC), HU_MEMNUM_OVL);
    for (i = 0; i < funcMax; i++) {
        obj->unk010[i] = fn_1_7A24;
    }
    obj->unk000 = HuPrcChildCreate(fn_1_79BC, prio, stackSize, 0, HuPrcCurrentGet());
    obj->unk000->property = obj;
    obj->unk184 = CharModelCreate(obj->unk1BC, model);
    for (i = 0; i < motMax; i++) {
        idx = i + obj->unk1BC * 13;
        if (motTbl[idx] != -1) {
            obj->unk190[i] = CharMotionCreate(obj->unk1BC, motTbl[i]);
        }
    }
    CharMotionDataClose(obj->unk1BC);
    for (i = 0; i < funcMax; i++) {
        if (funcTbl[i] != NULL) {
            obj->unk010[i] = funcTbl[i];
        }
    }
    return obj;
}
static void fn_1_85F8(M508_OBJ *obj)
{
    s32 i;

    for (i = 0; i < obj->unk18C; i++) {
        if (obj->unk190[i] != -1) {
            Hu3DMotionKill(obj->unk190[i]);
        }
    }
    HuMemDirectFree(obj->unk190);
    if (obj->unk184 != -1) {
        Hu3DModelKill(obj->unk184);
    }
    HuMemDirectFree(obj->unk010);
    HuPrcKill(obj->unk000);
    HuMemDirectFree(obj);
}
static void fn_1_8698(M508_OBJ *obj, char *hookName)
{
    if(obj->unk1BC = 0) {
        CharModelHookDustCreate(obj->unk1BC, hookName);
    } else {
        Hu3DModelHookReset(obj->unk184);
    }
}
static M508_CAMERA *fn_1_86F0(s16 cameraBit)
{
    M508_CAMERAVIEW *view;
    M508_CAMERA *camera;
    int i;
    camera = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M508_CAMERA), HU_MEMNUM_OVL);
    camera->unk008 = cameraBit;
    for(i=0; i<3; i++) {
        view = &camera->unk010[i];
        view->unk018.x = 0;
        view->unk018.y = 0;
        view->unk018.z = 0;
        view->unk024.x = 0;
        view->unk024.y = 0;
        view->unk024.z = 0;
        view->unk030 = 0;
    }
    camera->unk00C = HuPrcChildCreate(fn_1_8918, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    camera->unk00C->property = camera;
    camera->unk0AC = 0;
    Hu3DCameraCreate(cameraBit);
    fn_1_95D8(camera, 30, 10, 8000, 1.2f);
    fn_1_9578(camera, 0, 0, 640, 480, 0, 1);
    fn_1_9628(camera, 0, 0, 640, 480);
    camera->unk000 = 2;
    return camera;
}
static void fn_1_88E0(M508_CAMERA *camera)
{
    HuPrcKill(camera->unk00C);
    HuMemDirectFree(camera);
}
static void fn_1_8918(void)
{
    M508_CAMERA *camera = HuPrcCurrentGet()->property;
    while(camera->unk000 != 3) {
        M508_CAMTBL[camera->unk000](camera);
    }
    HuPrcEnd();
}
static void fn_1_897C(M508_CAMERA *camera)
{
    M508_CAMERAVIEW *view;
    int i;
    for(i=0; i<3; i++) {
        view = &camera->unk010[i];
        view->unk000.x = view->unk018.x+(view->unk030*(HuSin(view->unk024.y)*HuCos(view->unk024.x)));
        view->unk000.y = view->unk018.y+(view->unk030*(-HuSin(view->unk024.x)));
        view->unk000.z = view->unk018.z+(view->unk030*(HuCos(view->unk024.y)*HuCos(view->unk024.x)));
        view->unk00C.x = HuSin(view->unk024.y)*HuSin(view->unk024.x);
        view->unk00C.y = HuCos(view->unk024.x);
        view->unk00C.z = HuCos(view->unk024.y)*HuSin(view->unk024.x);
    }
}
static void fn_1_8BF4(M508_CAMERA *camera)
{
    M508_CAMERAVIEW *view;
    if(camera->unk000 != 2) {
        view = &camera->unk010[0];
        Hu3DCameraPosSet(camera->unk008,
            view->unk000.x, view->unk000.y, view->unk000.z,
            view->unk00C.x, view->unk00C.y, view->unk00C.z,
            view->unk018.x, view->unk018.y, view->unk018.z);
    }
}
static void fn_1_8C64(M508_CAMERA *camera)
{
    camera->unk000 = 2;
}
static void fn_1_8C70(M508_CAMERA *camera)
{
    while(1) {
        CAMERA_SLEEP_MODECHG(1);
    }
}
static void fn_1_8D24(M508_CAMERA *camera)
{
    camera->unk000 = 0;
}
static void fn_1_8D30(M508_CAMERA *camera)
{
    while(1) {
        fn_1_96BC(camera);
        fn_1_9B38(camera);
        CAMERA_SLEEP_MODECHG(1);
    }
}
static BOOL fn_1_8DF8(M508_CAMERA *camera)
{
    return (camera->unk000) ? TRUE : FALSE;
}
static void fn_1_8E28(M508_CAMERA *camera, const HuVecF *center, const HuVecF *rot, const float *zoom, int speed)
{
    M508_CAMERAVIEW *view = &camera->unk010[0];
    M508_CAMERAVIEW *view2 = &camera->unk010[1];
    M508_CAMERAVIEW *view3 = &camera->unk010[2];
    *view2 = *view;
    *view3 = *view;
    if(center != NULL) {
        view3->unk018 = *center;
    }
    if(rot != NULL) {
        view3->unk024 = *rot;
    }
    if(zoom != NULL) {
        view3->unk030 = *zoom;
    }
    fn_1_897C(camera);
    camera->unk004 = speed;
    if(speed > 0) {
        camera->unk000 = 1;
    } else {
        *view = *view3;
        camera->unk000 = 0;
    }
}
static void fn_1_926C(M508_CAMERA *camera)
{
    M508_CAMERAVIEW *view = &camera->unk010[0];
    M508_CAMERAVIEW *view2 = &camera->unk010[1];
    M508_CAMERAVIEW *view3 = &camera->unk010[2];
    float step = 1.0f/camera->unk004;
    float t = 0;
    while(1) {
        float s = HuSin(t*90);
        s = s*s;
        view->unk018.x = view2->unk018.x+(s*(view3->unk018.x-view2->unk018.x));
        view->unk018.y = view2->unk018.y+(s*(view3->unk018.y-view2->unk018.y));
        view->unk018.z = view2->unk018.z+(s*(view3->unk018.z-view2->unk018.z));
        view->unk000.x = view2->unk000.x+(s*(view3->unk000.x-view2->unk000.x));
        view->unk000.y = view2->unk000.y+(s*(view3->unk000.y-view2->unk000.y));
        view->unk000.z = view2->unk000.z+(s*(view3->unk000.z-view2->unk000.z));
        view->unk00C.x = view2->unk00C.x+(s*(view3->unk00C.x-view2->unk00C.x));
        view->unk00C.y = view2->unk00C.y+(s*(view3->unk00C.y-view2->unk00C.y));
        view->unk00C.z = view2->unk00C.z+(s*(view3->unk00C.z-view2->unk00C.z));
        fn_1_96BC(camera);
        fn_1_9B38(camera);
        t += step;
        if(t >= 1.0f) {
            break;
        }
        CAMERA_SLEEP_MODECHG(1);
    }
    *view = *view3;
    camera->unk000 = 0;
}
static void fn_1_9578(M508_CAMERA *camera, float vpX, float vpY, float vpW, float vpH, float vpNearZ, float vpFarZ)
{
    Hu3DCameraViewportSet(camera->unk008, vpX, vpY, vpW, vpH, vpNearZ, vpFarZ);
}
static void fn_1_95D8(M508_CAMERA *camera, float fov, float near, float far, float aspect)
{
    Hu3DCameraPerspectiveSet(camera->unk008, fov, near, far, aspect);
}
static void fn_1_9628(M508_CAMERA *camera, float scissorX, float scissorY, float scissorW, float scissorH)
{
    Hu3DCameraScissorSet(camera->unk008, scissorX, scissorY, scissorW, scissorH);
}
static void fn_1_96BC(M508_CAMERA *camera)
{
    M508_CAMERAVIEW *view;
    if(camera->unk0AC && (HuPadBtn[0] & PAD_BUTTON_Y)) {
        view = &camera->unk010[0];
        view->unk018.x += 0.1f*HuPadSubStkX[0];
        view->unk018.z -= 0.02f*HuPadSubStkY[0];
        view->unk024.y -= 0.1f*HuPadStkX[0];
        view->unk024.x += 0.1f*HuPadStkY[0];
        view->unk030 += 0.1f*HuPadTrigL[0];
        view->unk030 -= 0.1f*HuPadTrigR[0];
        fn_1_897C(camera);
    }
}
static void fn_1_9B38(M508_CAMERA *camera)
{
}
static void fn_1_9B3C(int time, int waitF)
{
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, time);
    while(waitF && WipeCheckEnd()) {
        HuPrcVSleep();
    }
}
static void fn_1_9B98(int time, int waitF)
{
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, time);
    while(waitF && WipeCheckEnd()) {
        HuPrcVSleep();
    }
}
static void fn_1_9BF4(int time)
{
    GAMEMESID mesId = GameMesMgStartCreate();
    int i;
    if(time == -1) {
        while(GameMesStatGet(mesId)) {
            HuPrcVSleep();
        }
    } else {
        for(i=0; i<time; i++) {
            HuPrcVSleep();
        }
    }
}
static void fn_1_9C80(int time)
{
    GAMEMESID mesId = GameMesMgFinishCreate();
    int i;
    if(time == -1) {
        while(GameMesStatGet(mesId)) {
            HuPrcVSleep();
        }
    } else {
        for(i=0; i<time; i++) {
            HuPrcVSleep();
        }
    }
}
static float fn_1_9D0C(float start, float end, float t)
{
    float angleDiff;
    float result;
    angleDiff = fmod(end-start, 360);
    if(angleDiff < 0) {
        angleDiff += 360;
    }
    if(angleDiff > 180) {
        angleDiff -= 360;
    }
    result = fmod(start+(angleDiff*t), 360);
    if(result < 0) {
        result += 360;
    }
    return result;
}
static M508_WIN *fn_1_9E10(int w, int h)
{
    M508_WIN *win = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M508_WIN), HU_MEMNUM_OVL);
    win->unk010 = HuPrcChildCreate(fn_1_9EF8, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    win->unk010->property = win;
    win->unk000 = HuWinExCreateFrame(0, 0, w, h, -1, 1);
    return win;
}
static void fn_1_9EB8(M508_WIN *win)
{
    HuWinKill(win->unk000);
    HuPrcKill(win->unk010);
    HuMemDirectFree(win);
}
static void fn_1_9EF8(void)
{
    while(1) {
        HuPrcVSleep();
    }
}
static void fn_1_9F0C(M508_WIN *win, float posX, float posY)
{
    HuWinPosSet(win->unk000, win->unk004 = posX, win->unk008 = posY);
}
static void fn_1_9F54(M508_WIN *win, float *posX, float *posY)
{
    *posX = win->unk004;
    *posY = win->unk008;
}
static void fn_1_9F68(M508_WIN *win, u32 mess)
{
    HuWinMesSet(win->unk000, mess);
}
static void fn_1_9FA0(M508_WIN *win)
{
    HuWinDispOn(win->unk000);
    win->unk00C = 1;
}
static void fn_1_9FD8(M508_WIN *win)
{
    HuWinDispOff(win->unk000);
    win->unk00C = 0;
}
static void fn_1_A010(M508_WIN *win, int mesCol)
{
    HuWinMesColSet(win->unk000, mesCol);
}
static void fn_1_A04C(M508_WIN *win, s16 mesSpeed)
{
    HuWinMesSpeedSet(win->unk000, mesSpeed);
}
static void fn_1_A084(M508_WIN *win)
{
    HuWinMesWait(win->unk000);
}
static void fn_1_A0B4(M508_WIN *win)
{
    HuWinExOpen(win->unk000);
}
static void fn_1_A0E4(M508_WIN *win)
{
    HuWinExClose(win->unk000);
}
static void fn_1_A114(M508_WIN *win, float scaleX, float scaleY)
{
    HuWinScaleSet(win->unk000, scaleX, scaleY);
}
