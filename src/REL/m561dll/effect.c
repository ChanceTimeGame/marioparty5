/*
 * m561dll/effect.c -- the overlay's private copy of the game's dust effect.
 *
 * This is not new code so much as a second copy of one: the DOL already
 * carries the same particle system in src/game/charman.c (EffectParticleInit,
 * EffectParticleCreate, EffectCreate, EffectParticleHook), and m561dll ships
 * its own stripped version of it -- no effect types, no parManId dispatch, one
 * hard-wired EFFECTPARAM. Where a function here has a counterpart in
 * charman.c it is named for it, and the two should be read side by side.
 *
 * EFFECTPARAM is charman.c's, not a header's -- it is a file-local type there,
 * so the original necessarily has a second declaration of it here. The 0x38
 * layout is confirmed by the .data blob at 0x2F0, which is exactly one of them
 * (colorBegin a0a0a0ff, colorEnd 000000ff, vel {0,2,1}, velDecay
 * {0.95,0.99,0.95}, scaleVel 1.5, alphaBase -4), and by the 0x20D0 work buffer,
 * which is 150 * 0x38 for the 150-particle system created below.
 *
 * Seven functions, 891 instructions. See ../m524dll/m524.c for how to verify.
 */

#include "game/object.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/sprite.h"

#include "datadir_enum.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"

#include "REL/m561dll/m561.h"

/* --- forward declarations, asm address order --- */

void fn_1_8AE8(void);
void fn_1_8B38(void);
void fn_1_8BCC(s16 cameraBit, HuVecF *pos);
s16 fn_1_8F5C(s16 cameraBit, float posX, float posY, float posZ, float scale, M561_EFFECTPARAM *param);
void fn_1_9200(void);
void fn_1_9464(void);
void fn_1_9688(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

/* --- .data --- */

/*
 * .data:0x2F0 -- the one and only effect this overlay emits, and the reason
 * the whole file exists. Grey smoke that fades to black over a -4-per-frame
 * alpha ramp and grows 1.5 units a frame. fn_1_8BCC rewrites
 * vel and colorBegin.a in place before each burst, so it is deliberately not
 * const.
 */
M561_EFFECTPARAM lbl_1_data_5A0 = {
    0,
    { 0xA0, 0xA0, 0xA0, 0xFF },
    { 0x00, 0x00, 0x00, 0xFF },
    { 0.0f, 2.0f, 1.0f },
    { 0.95f, 0.99f, 0.95f },
    0.0f,
    0,
    1.5f,
    -4.0f,
    0.0f
};

/* --- .bss --- */

M561_EFFECTPARAM *lbl_1_bss_300;          /* 150 of them, shared by every camera */
HU3DMODELID lbl_1_bss_2E0[HU3D_CAM_MAX];  /* one system per camera */

/* ===== decoded functions, asm address order ===== */

/* fn_1_668C -- charman.c's EffectInit. */
void fn_1_8AE8(void)
{
    int i;
    for(i=0; i<HU3D_CAM_MAX; i++) {
        lbl_1_bss_2E0[i] = HU3D_MODELID_NONE;
    }
    lbl_1_bss_300 = NULL;
}

/*
 * fn_1_66DC -- the teardown. Nothing in the overlay calls it; it is in the
 * shipped object, so it is here. fn_1_8AE8 is inlined into its tail,
 * which is why the reset loop appears twice in the disassembly.
 */
void fn_1_8B38(void)
{
    if(lbl_1_bss_300) {
        HuMemDirectFree(lbl_1_bss_300);
        lbl_1_bss_300 = NULL;
    }
    fn_1_8AE8();
}

/*
 * fn_1_6770 -- one puff of smoke, as two counter-phased rings of eight.
 * The inner ring throws particles 3.5 units out at 45 degree steps starting
 * from straight back, the outer one 1.5 units out at the same steps offset by
 * 22.5, so the two interleave. Both are half-transparent, which is what the
 * colorBegin.a poke either side of the loops is for.
 *
 * `ratio` is the original's own local and is never anything but 2.0f, but it
 * multiplies the y position as well as the velocities, so it is not a scale in
 * any useful sense -- it is written as the object has it.
 */
void fn_1_8BCC(s16 cameraBit, HuVecF *pos)
{
    float ratio = 2.0f;
    s16 i;

    lbl_1_data_5A0.colorBegin.a = 128;
    for(i=0; i<8; i++) {
        lbl_1_data_5A0.vel.x = ratio*(3.5*sin((M_PI*(270.0f+(45.0f*i)))/180.0));
        lbl_1_data_5A0.vel.y = 1.0f;
        lbl_1_data_5A0.vel.z = ratio*(3.5*cos((M_PI*(270.0f+(45.0f*i)))/180.0));
        fn_1_8F5C(cameraBit, pos->x, pos->y*ratio, pos->z, 50.0f, &lbl_1_data_5A0);
    }
    for(i=0; i<8; i++) {
        lbl_1_data_5A0.vel.x = ratio*(1.5*sin((M_PI*(270.0+(22.5+(45.0f*i))))/180.0));
        lbl_1_data_5A0.vel.y = 1.0f;
        lbl_1_data_5A0.vel.z = ratio*(1.5*cos((M_PI*(270.0+(22.5+(45.0f*i))))/180.0));
        fn_1_8F5C(cameraBit, pos->x, pos->y*ratio, pos->z, 30.0f, &lbl_1_data_5A0);
    }
    lbl_1_data_5A0.colorBegin.a = 255;
}

/*
 * fn_1_6B00 -- charman.c's EffectCreate, minus the effect type. Finds a free
 * particle slot in each named camera's system, starting from where the last
 * one was taken and wrapping once, and fills it in.
 */
s16 fn_1_8F5C(s16 cameraBit, float posX, float posY, float posZ, float scale, M561_EFFECTPARAM *param)
{
    s16 cameraNo, bit;
    s16 id;

    fn_1_9200();
    id = -1;
    for(cameraNo=0, bit=HU3D_CAM0; cameraNo<HU3D_CAM_MAX; cameraNo++, bit <<= 1) {
        HU3DPARTICLEDATA *particleDataP;
        HU3DPARTICLE *particleP;
        s16 nextId;
        HU3DMODEL *modelP;
        M561_EFFECTPARAM *effParam;
        HU3DMODELID modelId;
        if(!(bit & cameraBit)) {
            continue;
        }
        if(-1.0f == Hu3DCamera[cameraNo].fov) {
            continue;
        }
        modelId = lbl_1_bss_2E0[cameraNo];
        if(modelId == HU3D_MODELID_NONE) {
            return -1;
        }
        modelP = &Hu3DData[modelId];
        particleP = modelP->hookData;
        effParam = particleP->work;
        for(particleDataP=&particleP->data[particleP->emitCnt], nextId=particleP->emitCnt; nextId<particleP->maxCnt; nextId++, particleDataP++) {
            if(!particleDataP->scale) {
                break;
            }
        }
        if(nextId >= particleP->maxCnt) {
            for(particleDataP=&particleP->data[0], nextId=0; nextId<particleP->maxCnt; nextId++, particleDataP++) {
                if(!particleDataP->scale) {
                    break;
                }
            }
        }
        if(nextId != particleP->maxCnt) {
            effParam[nextId] = *param;
            particleDataP->cameraBit = cameraBit;
            particleDataP->pos.x = posX;
            particleDataP->pos.y = posY;
            particleDataP->pos.z = posZ;
            particleDataP->vel = param->vel;
            particleDataP->color = param->colorBegin;
            particleDataP->scaleBase = scale;
            particleDataP->scale = scale;
            particleDataP->time = 0;
            particleDataP->parManId = HU3D_PARMANID_NONE;
            particleP->emitCnt = nextId;
            id = nextId;
        }
    }
    return id;
}

/*
 * fn_1_6DA4 -- charman.c's EffectParticleCreate. Called before every burst, so
 * a camera created after the overlay started still gets a system; the anim is
 * read from whichever system already has one, and only off the disc if none
 * does.
 */
void fn_1_9200(void)
{
    ANIMDATA *anim = NULL;
    s16 cameraNo;
    HU3DPARTICLE *particleP;

    for(cameraNo=0; cameraNo<HU3D_CAM_MAX; cameraNo++) {
        if(-1.0f == Hu3DCamera[cameraNo].fov) {
            continue;
        }
        if(lbl_1_bss_2E0[cameraNo] != HU3D_MODELID_NONE) {
            particleP = Hu3DData[lbl_1_bss_2E0[cameraNo]].hookData;
            if(particleP->anim) {
                anim = particleP->anim;
                continue;
            }
        } else {
            if(!anim) {
                void *data = HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL);
                anim = HuSprAnimRead(data);
            }
            lbl_1_bss_2E0[cameraNo] = Hu3DParticleCreate(anim, 150);
            Hu3DModelLayerSet(lbl_1_bss_2E0[cameraNo], 5);
            Hu3DParticleHookSet(lbl_1_bss_2E0[cameraNo], fn_1_9688);
            Hu3DModelCameraSet(lbl_1_bss_2E0[cameraNo], (1 << cameraNo));
            if(!lbl_1_bss_300) {
                lbl_1_bss_300 = HuMemDirectMallocNum(HEAP_HEAP, 150*sizeof(M561_EFFECTPARAM), HU_MEMNUM_OVL);
            }
            Hu3DParticleBlendModeSet(lbl_1_bss_2E0[cameraNo], HU3D_PARTICLE_BLEND_NORMAL);
            {
                HU3DPARTICLEDATA *particleDataP;
                s16 j;
                particleP = Hu3DData[lbl_1_bss_2E0[cameraNo]].hookData;
                particleP->emitCnt = 0;
                particleP->work = lbl_1_bss_300;
                particleP->count = 1;
                for(particleDataP = particleP->data, j=0; j<particleP->maxCnt; j++, particleDataP++) {
                    particleDataP->scale = 0;
                }
            }
        }
    }
}

/*
 * fn_1_7008 -- charman.c's EffectParticleInit, called once from ObjectSetup.
 * Same body as the above with the reuse branch replaced by a plain skip.
 */
void fn_1_9464(void)
{
    ANIMDATA *anim = NULL;
    s16 cameraNo;
    HU3DPARTICLE *particleP;

    for(cameraNo=0; cameraNo<HU3D_CAM_MAX; cameraNo++) {
        if(-1.0f == Hu3DCamera[cameraNo].fov) {
            continue;
        }
        if(lbl_1_bss_2E0[cameraNo] != HU3D_MODELID_NONE) {
            continue;
        }
        if(!anim) {
            void *data = HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL);
            anim = HuSprAnimRead(data);
        }
        lbl_1_bss_2E0[cameraNo] = Hu3DParticleCreate(anim, 150);
        Hu3DModelLayerSet(lbl_1_bss_2E0[cameraNo], 5);
        Hu3DParticleHookSet(lbl_1_bss_2E0[cameraNo], fn_1_9688);
        Hu3DModelCameraSet(lbl_1_bss_2E0[cameraNo], (1 << cameraNo));
        if(!lbl_1_bss_300) {
            lbl_1_bss_300 = HuMemDirectMallocNum(HEAP_HEAP, 150*sizeof(M561_EFFECTPARAM), HU_MEMNUM_OVL);
        }
        Hu3DParticleBlendModeSet(lbl_1_bss_2E0[cameraNo], HU3D_PARTICLE_BLEND_NORMAL);
        {
            HU3DPARTICLEDATA *particleDataP;
            s16 j;
            particleP = Hu3DData[lbl_1_bss_2E0[cameraNo]].hookData;
            particleP->emitCnt = 0;
            particleP->work = lbl_1_bss_300;
            particleP->count = 1;
            for(particleDataP = particleP->data, j=0; j<particleP->maxCnt; j++, particleDataP++) {
                particleDataP->scale = 0;
            }
        }
    }
}

/*
 * fn_1_722C -- charman.c's EffectParticleHook, run once a frame per camera.
 * Same integrator: decay the velocity, add it to the position, add gravity,
 * walk each colour channel toward colorEnd by colorWeight, ramp the alpha by
 * alphaBase and retire the particle when it runs out, then grow the scale.
 * The parManId branch charman.c has is absent -- this overlay only ever emits
 * plain particles.
 */
void fn_1_9688(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    M561_EFFECTPARAM *param = particleP->work;
    HU3DPARTICLEDATA *particleDataP;
    s16 color;
    s16 i;

    if(particleP->count == 0) {
        for(particleDataP=&particleP->data[0], i=0; i<particleP->maxCnt; i++, particleDataP++) {
            particleDataP->scale = 0;
        }
    }
    for(particleDataP=&particleP->data[0], i=0; i<particleP->maxCnt; i++, particleDataP++) {
        if(!particleDataP->scale) {
            continue;
        }
        particleDataP->vel.x *= param[i].velDecay.x;
        particleDataP->vel.y *= param[i].velDecay.y;
        particleDataP->vel.z *= param[i].velDecay.z;
        VECAdd(&particleDataP->vel, &particleDataP->pos, &particleDataP->pos);
        particleDataP->vel.y += param[i].gravity;
        color = particleDataP->color.r+(param[i].colorWeight*(param[i].colorEnd.r-param[i].colorBegin.r));
        if(color < 0) {
            color = 0;
        } else if(color > 255) {
            color = 255;
        }
        particleDataP->color.r = color;
        color = particleDataP->color.g+(param[i].colorWeight*(param[i].colorEnd.g-param[i].colorBegin.g));
        if(color < 0) {
            color = 0;
        } else if(color > 255) {
            color = 255;
        }
        particleDataP->color.g = color;
        color = particleDataP->color.b+(param[i].colorWeight*(param[i].colorEnd.b-param[i].colorBegin.b));
        if(color < 0) {
            color = 0;
        } else if(color > 255) {
            color = 255;
        }
        particleDataP->color.b = color;
        color = particleDataP->color.a+param[i].alphaBase;
        if(color < 1) {
            particleDataP->scale = 0;
        }
        particleDataP->color.a = color;
        if(particleDataP->scale) {
            if(param[i].attr & 0x1) {
                particleDataP->scale = particleDataP->scaleBase*(((particleDataP->time+i) & 0x1) ? 1.0 : 0.5);
            } else {
                particleDataP->scale = particleDataP->scaleBase;
            }
            particleDataP->scaleBase += param[i].scaleVel;
            if(particleDataP->scaleBase <= 0.01f) {
                particleDataP->scale = 0;
            }
        }
        particleDataP->time++;
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt*sizeof(HU3DPARTICLEDATA));
}
