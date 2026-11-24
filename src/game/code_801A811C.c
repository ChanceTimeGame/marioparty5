// Branch stubs at the end of the DOL's .text: each is a single `b` to a DOL symbol.
// Some targets are data symbols (declared here as functions so the asm can branch to them),
// so the table is written as asm, one function per stub.

#include "dolphin/types.h"

extern void ARAlloc();
extern void ARFree();
extern void ARGetDMAStatus();
extern void ARGetSize();
extern void ARInit();
extern void ARRegisterDMACallback();
extern void ARSetSize();
extern void ARStartDMA();
extern void AnimDebug();
extern void C_QUATAdd();
extern void C_QUATMtx();
extern void C_QUATRotAxisRad();
extern void C_QUATSlerp();
extern void C_VECReflect();
extern void CamMotionEx();
extern void CamMotionEx2();
extern void CamMotionExPath();
extern void CamMotionExPathGet();
extern void CharClose();
extern void CharDataClose();
extern void CharEffectCoinGlowCreate();
extern void CharEffectCryCreate();
extern void CharEffectDustCreate();
extern void CharEffectHitCreate();
extern void CharEffectLayerSet();
extern void CharEffectShoeHitCreate();
extern void CharEffectSmokeCreate();
extern void CharFXPlay();
extern void CharFXPlayPan();
extern void CharFXPlayPos();
extern void CharFXPlayVol();
extern void CharFXPlayVolPan();
extern void CharFXStop();
extern void CharInit();
extern void CharLoseVoicePlay();
extern void CharModelAttrReset();
extern void CharModelAttrSet();
extern void CharModelCreate();
extern void CharModelCryCreate();
extern void CharModelDataClose();
extern void CharModelEyeBmpGet();
extern void CharModelFileNumGet();
extern void CharModelFxFlagSet();
extern void CharModelHeightGet();
extern void CharModelHitCreate();
extern void CharModelHookDustCreate();
extern void CharModelKill();
extern void CharModelLandDustCreate();
extern void CharModelMotListCreate();
extern void CharModelShoeHitCreate();
extern void CharModelStepFxSet();
extern void CharModelTimingHookNoGet();
extern void CharModelVoicePanAutoSet();
extern void CharModelVoicePanSet();
extern void CharModelVoiceVolSet();
extern void CharMotionAMemPGet();
extern void CharMotionCreate();
extern void CharMotionDataClose();
extern void CharMotionEndCheck();
extern void CharMotionExtraTimeGet();
extern void CharMotionFileNumGet();
extern void CharMotionInit();
extern void CharMotionInitAsync();
extern void CharMotionKill();
extern void CharMotionMaxTimeGet();
extern void CharMotionNoSet();
extern void CharMotionSet();
extern void CharMotionShiftIDGet();
extern void CharMotionShiftSet();
extern void CharMotionShiftTimeGet();
extern void CharMotionSpeedSet();
extern void CharMotionStartEndSet();
extern void CharMotionTimeGet();
extern void CharMotionTimeSet();
extern void CharMotionTotalTimeGet();
extern void CharMotionUpdateSet();
extern void CharMotionVoiceOnSet();
extern void CharNpcDustSet();
extern void CharNpcDustVoiceOffSet();
extern void CharWinLoseVoicePlay();
extern void ClusterAdjustObject();
extern void GWBoardMaxCoinGet();
extern void GWBoardMaxCoinSet();
extern void GWBoardMaxStarGet();
extern void GWBoardMaxStarSet();
extern void GWCharColorGet();
extern void GWCharPlayNumGet();
extern void GWCharPlayNumInc();
extern void GWCharPlayNumSet();
extern void GWMgCustomGet();
extern void GWMgCustomReset();
extern void GWMgCustomSet();
extern void GWMgRecordGet();
extern void GWMgRecordSet();
extern void GWMgUnlockGet();
extern void GWPlayNumAdd();
extern void GWPlayNumGet();
extern void GWPlayNumSet();
extern void GWPlayerCoinAdd();
extern void GWPlayerCoinGet();
extern void GWPlayerCoinSet();
extern void GWPlayerStarAdd();
extern void GWPlayerStarGet();
extern void GWPlayerStarSet();
extern void GWSaveCompleteSet();
extern void GWSdCommonInit();
extern void GWTotalStarAdd();
extern void GWTotalStarGet();
extern void GWTotalStarSet();
extern void GXGetProjectionv();
extern void GXGetViewportv();
extern void GXPixModeSync();
extern void GXProject();
extern void GXSetIndTexMtx();
extern void GXSetIndTexOrder();
extern void GXSetTevIndTile();
extern void GXSetTevIndWarp();
extern void GXSetTexCoordScaleManually();
extern void GXSetVtxDescv();
extern void GXWaitDrawDone();
extern void GameMesCreate();
extern void GameMesDispSet();
extern void GameMesInit();
extern void GameMesKill();
extern void GameMesKillCheck();
extern void GameMesPosSet();
extern void GameMesSprKill();
extern void GameMesStatGet();
extern void GameMesStrWinCreate();
extern void Hu3D2Dto3D();
extern void Hu3D3Dto2D();
extern void Hu3DAnimAllKill();
extern void Hu3DAnimAttrReset();
extern void Hu3DAnimAttrSet();
extern void Hu3DAnimBankSet();
extern void Hu3DAnimCreate();
extern void Hu3DAnimExec();
extern void Hu3DAnimInit();
extern void Hu3DAnimKill();
extern void Hu3DAnimLink();
extern void Hu3DAnimSet();
extern void Hu3DAnimSpeedSet();
extern void Hu3DAnmNoSet();
extern void Hu3DBGColorSet();
extern void Hu3DCameraAllKill();
extern void Hu3DCameraCreate();
extern void Hu3DCameraKill();
extern void Hu3DCameraMotionOff();
extern void Hu3DCameraMotionOn();
extern void Hu3DCameraMotionStart();
extern void Hu3DCameraPerspectiveGet();
extern void Hu3DCameraPerspectiveSet();
extern void Hu3DCameraPosGet();
extern void Hu3DCameraPosSet();
extern void Hu3DCameraPosSetV();
extern void Hu3DCameraScissorSet();
extern void Hu3DCameraSet();
extern void Hu3DCameraViewportSet();
extern void Hu3DFbCopyExec();
extern void Hu3DFbCopyLayerSet();
extern void Hu3DFogClear();
extern void Hu3DFogSet();
extern void Hu3DGLightColorSet();
extern void Hu3DGLightCreate();
extern void Hu3DGLightCreateV();
extern void Hu3DGLightInfinitytSet();
extern void Hu3DGLightKill();
extern void Hu3DGLightParamGet();
extern void Hu3DGLightPointSet();
extern void Hu3DGLightPosAimSet();
extern void Hu3DGLightPosAimSetV();
extern void Hu3DGLightPosAngleSet();
extern void Hu3DGLightPosSet();
extern void Hu3DGLightPosSetV();
extern void Hu3DGLightSpotSet();
extern void Hu3DGLightStaticSet();
extern void Hu3DHookFuncCreate();
extern void Hu3DJointMotion();
extern void Hu3DLLightColorSet();
extern void Hu3DLLightCreate();
extern void Hu3DLLightCreateV();
extern void Hu3DLLightInfinitytSet();
extern void Hu3DLLightKill();
extern void Hu3DLLightParamGet();
extern void Hu3DLLightPointSet();
extern void Hu3DLLightPosAimSet();
extern void Hu3DLLightPosAimSetV();
extern void Hu3DLLightPosAngleSet();
extern void Hu3DLLightPosSet();
extern void Hu3DLLightPosSetV();
extern void Hu3DLLightSpotSet();
extern void Hu3DLLightStaticSet();
extern void Hu3DLayerHookReset();
extern void Hu3DLayerHookSet();
extern void Hu3DLighInit();
extern void Hu3DLightAllKill();
extern void Hu3DLightSet();
extern void Hu3DMatLightSet();
extern void Hu3DMipMapSet();
extern void Hu3DModelAllKill();
extern void Hu3DModelAmbSet();
extern void Hu3DModelAttrGet();
extern void Hu3DModelAttrReset();
extern void Hu3DModelAttrSet();
extern void Hu3DModelCameraCreate();
extern void Hu3DModelCameraInfoSet();
extern void Hu3DModelCameraSet();
extern void Hu3DModelClusterAttrReset();
extern void Hu3DModelClusterAttrSet();
extern void Hu3DModelCreate();
extern void Hu3DModelHiliteMapSet();
extern void Hu3DModelHiliteTypeSet();
extern void Hu3DModelHookObjReset();
extern void Hu3DModelHookReset();
extern void Hu3DModelHookSet();
extern void Hu3DModelKill();
extern void Hu3DModelLayerSet();
extern void Hu3DModelLightIdGet();
extern void Hu3DModelLightInfoSet();
extern void Hu3DModelLink();
extern void Hu3DModelMatHookSet();
extern void Hu3DModelMotionAttrGet();
extern void Hu3DModelObjDraw();
extern void Hu3DModelObjDrawInit();
extern void Hu3DModelObjMtxGet();
extern void Hu3DModelObjPosGet();
extern void Hu3DModelObjPtrDraw();
extern void Hu3DModelObjPtrGet();
extern void Hu3DModelPosSet();
extern void Hu3DModelPosSetV();
extern void Hu3DModelProjectionReset();
extern void Hu3DModelProjectionSet();
extern void Hu3DModelReflectTypeSet();
extern void Hu3DModelRotSet();
extern void Hu3DModelRotSetV();
extern void Hu3DModelScaleSet();
extern void Hu3DModelScaleSetV();
extern void Hu3DModelShadowDispOff();
extern void Hu3DModelShadowDispOn();
extern void Hu3DModelShadowMapObjReset();
extern void Hu3DModelShadowMapObjSet();
extern void Hu3DModelShadowMapSet();
extern void Hu3DModelShadowReset();
extern void Hu3DModelShadowSet();
extern void Hu3DModelTPLvlSet();
extern void Hu3DMotionAllKill();
extern void Hu3DMotionAttrReset();
extern void Hu3DMotionAttrSet();
extern void Hu3DMotionCalc();
extern void Hu3DMotionClusterMaxTimeGet();
extern void Hu3DMotionClusterNoSet();
extern void Hu3DMotionClusterReset();
extern void Hu3DMotionClusterSet();
extern void Hu3DMotionClusterSpeedSet();
extern void Hu3DMotionClusterTimeSet();
extern void Hu3DMotionCreate();
extern void Hu3DMotionEndCheck();
extern void Hu3DMotionExec();
extern void Hu3DMotionForceSet();
extern void Hu3DMotionIDGet();
extern void Hu3DMotionInit();
extern void Hu3DMotionKill();
extern void Hu3DMotionMaxTimeGet();
extern void Hu3DMotionModelCreate();
extern void Hu3DMotionMotionMaxTimeGet();
extern void Hu3DMotionNext();
extern void Hu3DMotionNoMotReset();
extern void Hu3DMotionNoMotSet();
extern void Hu3DMotionOverlayEndCheck();
extern void Hu3DMotionOverlayMaxTimeGet();
extern void Hu3DMotionOverlayReset();
extern void Hu3DMotionOverlaySet();
extern void Hu3DMotionOverlaySpeedSet();
extern void Hu3DMotionOverlayTimeGet();
extern void Hu3DMotionOverlayTimeSet();
extern void Hu3DMotionSet();
extern void Hu3DMotionShapeIDGet();
extern void Hu3DMotionShapeMaxTimeGet();
extern void Hu3DMotionShapeReset();
extern void Hu3DMotionShapeSet();
extern void Hu3DMotionShapeSpeedSet();
extern void Hu3DMotionShapeStartEndSet();
extern void Hu3DMotionShapeTimeSet();
extern void Hu3DMotionShiftIDGet();
extern void Hu3DMotionShiftMaxTimeGet();
extern void Hu3DMotionShiftSet();
extern void Hu3DMotionShiftSpeedSet();
extern void Hu3DMotionShiftStartEndSet();
extern void Hu3DMotionShiftTimeGet();
extern void Hu3DMotionShiftTimeSet();
extern void Hu3DMotionSpeedSet();
extern void Hu3DMotionStartEndSet();
extern void Hu3DMotionTimeGet();
extern void Hu3DMotionTimeSet();
extern void Hu3DMtxRotGet();
extern void Hu3DMtxScaleGet();
extern void Hu3DMtxTransGet();
extern void Hu3DNoSyncSet();
extern void Hu3DParManAllKill();
extern void Hu3DParManAttrReset();
extern void Hu3DParManAttrSet();
extern void Hu3DParManColorSet();
extern void Hu3DParManCreate();
extern void Hu3DParManInit();
extern void Hu3DParManKill();
extern void Hu3DParManLayerSet();
extern void Hu3DParManLink();
extern void Hu3DParManModelIDGet();
extern void Hu3DParManPosSet();
extern void Hu3DParManPtrGet();
extern void Hu3DParManRotSet();
extern void Hu3DParManTimeLimitSet();
extern void Hu3DParManVacumeSet();
extern void Hu3DParManVecSet();
extern void Hu3DParticleAnimModeSet();
extern void Hu3DParticleAttrReset();
extern void Hu3DParticleAttrSet();
extern void Hu3DParticleBlendModeSet();
extern void Hu3DParticleCntSet();
extern void Hu3DParticleColSet();
extern void Hu3DParticleCreate();
extern void Hu3DParticleHookSet();
extern void Hu3DParticleScaleSet();
extern void Hu3DParticleTPLvlSet();
extern void Hu3DParticleZRotSet();
extern void Hu3DProjectionCreate();
extern void Hu3DProjectionKill();
extern void Hu3DProjectionPosSet();
extern void Hu3DProjectionTPLvlSet();
extern void Hu3DReflectMapSet();
extern void Hu3DReflectModelSet();
extern void Hu3DReflectNoSet();
extern void Hu3DShadowColSet();
extern void Hu3DShadowCreate();
extern void Hu3DShadowMultiColSet();
extern void Hu3DShadowMultiCreate();
extern void Hu3DShadowMultiPosSet();
extern void Hu3DShadowMultiSizeSet();
extern void Hu3DShadowMultiTPLvlSet();
extern void Hu3DShadowPosSet();
extern void Hu3DShadowSizeSet();
extern void Hu3DShadowTPLvlSet();
extern void Hu3DSubMotionExec();
extern void Hu3DSubMotionReset();
extern void Hu3DSubMotionSet();
extern void Hu3DSubMotionTimeSet();
extern void Hu3DTexScrollAllKill();
extern void Hu3DTexScrollCreate();
extern void Hu3DTexScrollKill();
extern void Hu3DTexScrollPauseDisableSet();
extern void Hu3DTexScrollPosMoveSet();
extern void Hu3DTexScrollPosSet();
extern void Hu3DTexScrollRotMoveSet();
extern void Hu3DTexScrollRotSet();
extern void Hu3DWaterCameraSet();
extern void Hu3DWaterCreate();
extern void Hu3DWaterGlowSet();
extern void Hu3DWaterHiliteSet();
extern void Hu3DWaterHiliteTPLvlSet();
extern void Hu3DWaterIndTexMtxSet();
extern void Hu3DWaterPadYSet();
extern void Hu3DWaterTexPosSet();
extern void Hu3DWaterTexScaleSet();
extern void Hu3DWaterWaveCreate();
extern void Hu3DZClear();
extern void Hu3DZClearLayerSet();
extern void HuARDMACheck();
extern void HuARDirCheck();
extern void HuARDirFree();
extern void HuARFree();
extern void HuARMalloc();
extern void HuAR_ARAMtoMRAM();
extern void HuAR_ARAMtoMRAMFileRead();
extern void HuAR_ARAMtoMRAMNum();
extern void HuAR_DVDtoARAM();
extern void HuAR_MRAMtoARAM();
extern void HuAR_MRAMtoARAM2();
extern void HuAudAUXSet();
extern void HuAudAllStop();
extern void HuAudBGMPlay();
extern void HuAudDllSndGrpSet();
extern void HuAudFXEmiterPlay();
extern void HuAudFXEmiterUpDate();
extern void HuAudFXFadeOut();
extern void HuAudFXListnerKill();
extern void HuAudFXListnerSet();
extern void HuAudFXListnerSetEX();
extern void HuAudFXListnerUpdate();
extern void HuAudFXPanning();
extern void HuAudFXPitchSet();
extern void HuAudFXPlay();
extern void HuAudFXPlayPan();
extern void HuAudFXPlayVol();
extern void HuAudFXPlayVolPan();
extern void HuAudFXStatusGet();
extern void HuAudFXStop();
extern void HuAudFXVolSet();
extern void HuAudFadeOut();
extern void HuAudInit();
extern void HuAudJinglePlay();
extern void HuAudSStreamAllFadeOut();
extern void HuAudSStreamAllStop();
extern void HuAudSStreamChanPlay();
extern void HuAudSStreamFadeOut();
extern void HuAudSStreamPause();
extern void HuAudSStreamPauseFadeOut();
extern void HuAudSStreamPlay();
extern void HuAudSStreamStatGet();
extern void HuAudSStreamStop();
extern void HuAudSStreamVolSet();
extern void HuAudSeqFadeOut();
extern void HuAudSeqMidiCtrlGet();
extern void HuAudSeqPlay();
extern void HuAudSeqStop();
extern void HuAudSndCommonGrpSet();
extern void HuAudSndGrpSet();
extern void HuAudSndGrpSetSet();
extern void HuAudStreamFadeOut();
extern void HuAudStreamPauseOff();
extern void HuAudStreamPauseOn();
extern void HuAudStreamPlay();
extern void HuAudStreamVolSet();
extern void HuCardCheck();
extern void HuCardClose();
extern void HuCardCreate();
extern void HuCardDelete();
extern void HuCardFormat();
extern void HuCardFreeSpaceGet();
extern void HuCardMount();
extern void HuCardOpen();
extern void HuCardRead();
extern void HuCardSectorSizeGet();
extern void HuCardSlotCheck();
extern void HuCardWrite();
extern void HuDataClose();
extern void HuDataCloseMulti();
extern void HuDataDirCancel();
extern void HuDataDirCancelAsync();
extern void HuDataDirClose();
extern void HuDataDirCloseAsync();
extern void HuDataDirCloseNum();
extern void HuDataDirRead();
extern void HuDataDirReadAsync();
extern void HuDataDirReadNumAsync();
extern void HuDataGetAsyncStat();
extern void HuDataGetSize();
extern void HuDataInit();
extern void HuDataRead();
extern void HuDataReadMulti();
extern void HuDataReadNum();
extern void HuDataReadNumHeapShortForce();
extern void HuDataSelHeapRead();
extern void HuDataSelHeapReadNum();
extern void HuPadInit();
extern void HuPadRead();
extern void HuPadRumbleAllStop();
extern void HuPadRumbleGet();
extern void HuPadRumbleSet();
extern void HuPadRumbleStop();
extern void HuPadStatGet();
extern void HuPrcCall();
extern void HuPrcChildCreate();
extern void HuPrcChildKill();
extern void HuPrcChildLink();
extern void HuPrcChildUnlink();
extern void HuPrcCreate();
extern void HuPrcCurrentGet();
extern void HuPrcDestructorSet();
extern void HuPrcDestructorSet2();
extern void HuPrcEnd();
extern void HuPrcInit();
extern void HuPrcKill();
extern void HuPrcMemAlloc();
extern void HuPrcMemFree();
extern void HuPrcResetStat();
extern void HuPrcSetStat();
extern void HuPrcSleep();
extern void HuPrcVSleep();
extern void HuPrcWakeup();
extern void HuSetVecF();
extern void HuSprAnimKill();
extern void HuSprAnimLock();
extern void HuSprAnimMake();
extern void HuSprAnimNoSet();
extern void HuSprAnimNoSetPause();
extern void HuSprAnimRead();
extern void HuSprAttrGet();
extern void HuSprAttrReset();
extern void HuSprAttrSet();
extern void HuSprBGSet();
extern void HuSprBankSet();
extern void HuSprBegin();
extern void HuSprCall();
extern void HuSprColorSet();
extern void HuSprCreate();
extern void HuSprDrawNoSet();
extern void HuSprExecLayerCameraSet();
extern void HuSprExecLayerSet();
extern void HuSprFinish();
extern void HuSprFuncCreate();
extern void HuSprGrpCenterSet();
extern void HuSprGrpCreate();
extern void HuSprGrpDrawNoSet();
extern void HuSprGrpKill();
extern void HuSprGrpMemberKill();
extern void HuSprGrpMemberSet();
extern void HuSprGrpPosSet();
extern void HuSprGrpScaleSet();
extern void HuSprGrpScissorSet();
extern void HuSprGrpTPLvlSet();
extern void HuSprGrpZRotSet();
extern void HuSprKill();
extern void HuSprPosSet();
extern void HuSprPriSet();
extern void HuSprScaleSet();
extern void HuSprScissorSet();
extern void HuSprSpeedSet();
extern void HuSprSprBGSet();
extern void HuSprTPLvlSet();
extern void HuSprZRotSet();
extern void HuSubVecF();
extern void HuSysVWaitSet();
extern void HuTHP3DCreate();
extern void HuTHP3DCreateVol();
extern void HuTHPClose();
extern void HuTHPEndCheck();
extern void HuTHPFrameGet();
extern void HuTHPMatHook();
extern void HuTHPProcCheck();
extern void HuTHPRestart();
extern void HuTHPSetVolume();
extern void HuTHPSprCreate();
extern void HuTHPSprCreateVol();
extern void HuTHPStartCheck();
extern void HuTHPStop();
extern void HuTHPTotalFrameGet();
extern void HuWinAllKill();
extern void HuWinAnimSet();
extern void HuWinAttrReset();
extern void HuWinAttrSet();
extern void HuWinBGColSet();
extern void HuWinBGTPLvlSet();
extern void HuWinCenterPosSet();
extern void HuWinChoiceDisable();
extern void HuWinChoiceGet();
extern void HuWinChoiceNowGet();
extern void HuWinChoiceNumGet();
extern void HuWinChoiceSet();
extern void HuWinComKeyReset();
extern void HuWinComKeySet();
extern void HuWinComKeyWait();
extern void HuWinCreate();
extern void HuWinDisablePlayerReset();
extern void HuWinDisablePlayerSet();
extern void HuWinDispOff();
extern void HuWinDispOn();
extern void HuWinDrawNoSet();
extern void HuWinExClose();
extern void HuWinExCreate();
extern void HuWinExCreateFrame();
extern void HuWinExKill();
extern void HuWinExOpen();
extern void HuWinExSpeakerSet();
extern void HuWinHomeClear();
extern void HuWinInit();
extern void HuWinInsertMesSet();
extern void HuWinInsertMesSizeGet();
extern void HuWinKeyWaitEntry();
extern void HuWinKeyWaitNumGet();
extern void HuWinKill();
extern void HuWinMesColSet();
extern void HuWinMesMaxDirGet();
extern void HuWinMesMaxNumGet();
extern void HuWinMesMaxSizeBetGet();
extern void HuWinMesMaxSizeGet();
extern void HuWinMesPalSet();
extern void HuWinMesPtrGet();
extern void HuWinMesRead();
extern void HuWinMesSet();
extern void HuWinMesSizeCancelCRSet();
extern void HuWinMesSpeedSet();
extern void HuWinMesWait();
extern void HuWinPosSet();
extern void HuWinPriSet();
extern void HuWinPushKeySet();
extern void HuWinScaleSet();
extern void HuWinScissorSet();
extern void HuWinSprIDGet();
extern void HuWinSprKill();
extern void HuWinSprPosSet();
extern void HuWinSprPriSet();
extern void HuWinSprSet();
extern void HuWinStatGet();
extern void HuWinZRotSet();
extern void HuWindowInit();
extern void MB2Dto3D();
extern void MB3Dto2D();
extern void MB3MiracleGetExec();
extern void MBAngleAdd();
extern void MBAngleLerp();
extern void MBAngleLerpCos();
extern void MBAngleLerpSin();
extern void MBAngleMoveTo();
extern void MBAngleWrap();
extern void MBAngleWrapV();
extern void MBAudClose();
extern void MBAudFXClose();
extern void MBAudFXCreate();
extern void MBAudFXEmiterCreate();
extern void MBAudFXEmiterPosSet();
extern void MBAudFXEmiterSet();
extern void MBAudFXEmiterUpdate();
extern void MBAudFXKill();
extern void MBAudFXPlay();
extern void MBAudFXPosPanGet();
extern void MBAudFXPosPlay();
extern void MBAudFXRefSet();
extern void MBAudFXSet();
extern void MBAudFXStop();
extern void MBAudFXVolSet();
extern void MBAudInit();
extern void MBAudStub1();
extern void MBAudStub2();
extern void MBBankCoinGet();
extern void MBBankCoinReset();
extern void MBBezierCalc();
extern void MBBezierCalcSlope();
extern void MBBezierCalcSlopeV();
extern void MBBezierCalcV();
extern void MBBezierCalcVList();
extern void MBBranchExec();
extern void MBBranchExecDebug();
extern void MBBranchFlagGet();
extern void MBBranchFlagInit();
extern void MBBranchFlagReset();
extern void MBBranchFlagSet();
extern void MBBranchInit();
extern void MBCameraBitSet();
extern void MBCameraCreate();
extern void MBCameraCullCheck();
extern void MBCameraDirGet();
extern void MBCameraFocusAdd();
extern void MBCameraFocusMasuAdd();
extern void MBCameraFocusMasuSet();
extern void MBCameraFocusPlayerAdd();
extern void MBCameraFocusPlayerAddAll();
extern void MBCameraFocusPlayerSet();
extern void MBCameraFocusSet();
extern void MBCameraFovSet();
extern void MBCameraGet();
extern void MBCameraLookAtGet();
extern void MBCameraLookAtGetInv();
extern void MBCameraMasuViewSet();
extern void MBCameraMaxTimeSet();
extern void MBCameraModelKeySet();
extern void MBCameraModelViewSet();
extern void MBCameraMotionCheck();
extern void MBCameraMotionEnd();
extern void MBCameraMotionWait();
extern void MBCameraNearFarGet();
extern void MBCameraNearFarSet();
extern void MBCameraOffsetGet();
extern void MBCameraOffsetSet();
extern void MBCameraOffsetSetV();
extern void MBCameraPlayerViewSet();
extern void MBCameraPointFocusSet();
extern void MBCameraPop();
extern void MBCameraPosDirGet();
extern void MBCameraPosGet();
extern void MBCameraPosHookSet();
extern void MBCameraPosSet();
extern void MBCameraPosSetV();
extern void MBCameraPosTargetGet();
extern void MBCameraPosTargetSet();
extern void MBCameraPosTargetSetV();
extern void MBCameraPosViewSet();
extern void MBCameraPush();
extern void MBCameraQuakeReset();
extern void MBCameraQuakeSet();
extern void MBCameraRotGet();
extern void MBCameraRotSet();
extern void MBCameraRotSetV();
extern void MBCameraScissorSet();
extern void MBCameraSkipSet();
extern void MBCameraSpeedSet();
extern void MBCameraViewGet();
extern void MBCameraViewNoGet();
extern void MBCameraViewNoSet();
extern void MBCameraZoomGet();
extern void MBCameraZoomSet();
extern void MBCapMachineClose();
extern void MBCapMachineCreateAll();
extern void MBCapMachineExec();
extern void MBCapMachineInit();
extern void MBCapMachineObjCreate();
extern void MBCapMachineTutorialExec();
extern void MBCapsuleAddStory();
extern void MBCapsuleBowserAdd();
extern void MBCapsuleCodeGet();
extern void MBCapsuleColCheck();
extern void MBCapsuleColCreate();
extern void MBCapsuleColorNoGet();
extern void MBCapsuleCostGet();
extern void MBCapsuleDonkeyAdd();
extern void MBCapsuleDonkeyAddRandom();
extern void MBCapsuleEffHookCall();
extern void MBCapsuleEffHookSet();
extern void MBCapsuleEffHookStoryCall();
extern void MBCapsuleExec();
extern void MBCapsuleKupaGetExec();
extern void MBCapsuleListGet();
extern void MBCapsuleMasuPatNoGet();
extern void MBCapsuleMasuSet();
extern void MBCapsuleMdlGet();
extern void MBCapsuleMesGet();
extern void MBCapsuleNextGet();
extern void MBCapsuleNoGet();
extern void MBCapsuleNoUseCheck();
extern void MBCapsuleObjAlphaSet();
extern void MBCapsuleObjAttrReset();
extern void MBCapsuleObjAttrSet();
extern void MBCapsuleObjCreate();
extern void MBCapsuleObjDispSet();
extern void MBCapsuleObjInit();
extern void MBCapsuleObjKill();
extern void MBCapsuleObjLayerGet();
extern void MBCapsuleObjLayerSet();
extern void MBCapsuleObjMtxGet();
extern void MBCapsuleObjMtxSet();
extern void MBCapsuleObjPosGet();
extern void MBCapsuleObjPosSet();
extern void MBCapsuleObjPosSetV();
extern void MBCapsuleObjRotGet();
extern void MBCapsuleObjRotSet();
extern void MBCapsuleObjRotSetV();
extern void MBCapsuleObjScaleGet();
extern void MBCapsuleObjScaleSet();
extern void MBCapsuleObjScaleSetV();
extern void MBCapsuleOpeningAdd();
extern void MBCapsulePosAutoSelCheck();
extern void MBCapsulePosSelCheck();
extern void MBCapsulePosSelResultGet();
extern void MBCapsulePosSelStart();
extern void MBCapsulePosSetExec();
extern void MBCapsuleSelExec();
extern void MBCapsuleSelModelUpdate();
extern void MBCapsuleSelStoryExec();
extern void MBCapsuleStub();
extern void MBCapsuleStub0();
extern void MBCapsuleThrowAutoCheck();
extern void MBCapsuleThrowAutoExec();
extern void MBCapsuleThrowCheck();
extern void MBCapsuleThrowStart();
extern void MBCapsuleUseExec();
extern void MBCapsuleWinCreate();
extern void MBCircuitCarInit();
extern void MBCircuitCarMoveExec();
extern void MBCircuitExec();
extern void MBCircuitGoalCheck();
extern void MBCircuitKettouExec();
extern void MBCircuitKettouMgEndExec();
extern void MBCircuitKettouSaiExec();
extern void MBCircuitKupaExec();
extern void MBCircuitKupaMgEndExec();
extern void MBCircuitMgEndExec();
extern void MBCircuitReset();
extern void MBCoinAddAllDispExec();
extern void MBCoinAddAllExec();
extern void MBCoinAddAllProcExec();
extern void MBCoinAddDispExec();
extern void MBCoinAddExec();
extern void MBCoinAddProcExec();
extern void MBCoinClose();
extern void MBCoinDispCreate();
extern void MBCoinDispCreateSe();
extern void MBCoinDispKill();
extern void MBCoinDispKillCheck();
extern void MBCoinEffAttrReset();
extern void MBCoinEffAttrSet();
extern void MBCoinEffCheck();
extern void MBCoinEffCreate();
extern void MBCoinEffGet();
extern void MBCoinEffKill();
extern void MBCoinHitExec();
extern void MBCoinInit();
extern void MBCoinParManCreate();
extern void MBCoinParManKill();
extern void MBCoinPosGet();
extern void MBCoinPosSet();
extern void MBCoinPosSetV();
extern void MBCoinRotGet();
extern void MBCoinRotSet();
extern void MBCoinRotSetV();
extern void MBCoinScaleGet();
extern void MBCoinScaleSet();
extern void MBCoinScaleSetV();
extern void MBComCapsuleSelGet();
extern void MBComChoiceSetDown();
extern void MBComChoiceSetLeft();
extern void MBComChoiceSetRight();
extern void MBComChoiceSetUp();
extern void MBComMasuPathNoGet();
extern void MBDataAsyncWait();
extern void MBDataClose();
extern void MBDataDirReadAsync();
extern void MBDonkeyExec();
extern void MBDonkeyMgEndExec();
extern void MBDonkeyOpeningExec();
extern void MBEffAttrReset();
extern void MBEffAttrSet();
extern void MBEffConfettiCreate();
extern void MBEffConfettiKill();
extern void MBEffConfettiReset();
extern void MBEffCreate();
extern void MBEffDataCreate();
extern void MBEffFadeCameraSet();
extern void MBEffFadeCheck();
extern void MBEffFadeCreate();
extern void MBEffFadeDoneCheck();
extern void MBEffFadeOutSet();
extern void MBEffHookSet();
extern void MBEffKill();
extern void MBEffUnkTotalGet();
extern void MBEventMgCheck();
extern void MBGameEndExec();
extern void MBGateBattanExec();
extern void MBGateBattanKill();
extern void MBGateBattanSearch();
extern void MBGateClose();
extern void MBGateCreate();
extern void MBGateDossunKill();
extern void MBGateDossunSearch();
extern void MBGateInit();
extern void MBGateMasuExec();
extern void MBGuideCreate();
extern void MBGuideCreateDirect();
extern void MBGuideCreateFlag();
extern void MBGuideCreateIn();
extern void MBGuideEnd();
extern void MBGuideInit();
extern void MBGuideKill();
extern void MBGuideMdlPosGet();
extern void MBGuideMdlPosSet();
extern void MBGuideMdlPosSetV();
extern void MBGuideNoGet();
extern void MBGuideScreenPosGet();
extern void MBGuideScreenPosSet();
extern void MBGuideSpeakerNoGet();
extern void MBHermiteCalc();
extern void MBHermiteCalcSlope();
extern void MBHermiteCalcV();
extern void MBKettouCoinLoseGet();
extern void MBKettouCoinLoseGet2();
extern void MBKettouExec();
extern void MBKettouMgEndExec();
extern void MBKettouOppCoinLoseGet();
extern void MBKettouOppCoinLoseGet2();
extern void MBKillCheck();
extern void MBKillerEventCheck();
extern void MBKillerEventCheckAll();
extern void MBKillerEventExec();
extern void MBKillerExec();
extern void MBKillerMultiExec();
extern void MBKupaExec();
extern void MBKupaMgEndExec();
extern void MBLast5Exec();
extern void MBLightHookSet();
extern void MBLightReset();
extern void MBLightSet();
extern void MBMapViewCameraSet();
extern void MBMapViewExec();
extern void MBMapViewHookSet();
extern void MBMasuBomheiSet();
extern void MBMasuCameraSet();
extern void MBMasuCapsuleClear();
extern void MBMasuCapsuleFind();
extern void MBMasuCapsuleGet();
extern void MBMasuCapsuleSet();
extern void MBMasuCarNextGet();
extern void MBMasuCarPrevGet();
extern void MBMasuCarTargetGet();
extern void MBMasuColorSet();
extern void MBMasuCornerPosGet();
extern void MBMasuCornerRotPosGet();
extern void MBMasuCreate();
extern void MBMasuDataRead();
extern void MBMasuDispGet();
extern void MBMasuDispMaskGet();
extern void MBMasuDispMaskReset();
extern void MBMasuDispMaskSet();
extern void MBMasuDispSet();
extern void MBMasuDonkeyGet();
extern void MBMasuDonkeyNumGet();
extern void MBMasuDonkeySet();
extern void MBMasuEffClear();
extern void MBMasuEffSet();
extern void MBMasuEventFlagGet();
extern void MBMasuFlagFind();
extern void MBMasuFlagFindLink();
extern void MBMasuFlagGet();
extern void MBMasuFlagMatchFind();
extern void MBMasuFlagMatchFindLink();
extern void MBMasuFlagPosGet();
extern void MBMasuGet();
extern void MBMasuHatenaHookSet();
extern void MBMasuIdStarCheck();
extern void MBMasuKill();
extern void MBMasuMtxGet();
extern void MBMasuMtxSet();
extern void MBMasuNumGet();
extern void MBMasuPathCheck();
extern void MBMasuPathCheckHookSet();
extern void MBMasuPathFlagLenGet();
extern void MBMasuPathFlagMatchLenGet();
extern void MBMasuPathLenGet();
extern void MBMasuPathMasuGet();
extern void MBMasuPathMasuWrapGet();
extern void MBMasuPathNoLoopCheck();
extern void MBMasuPathTypeLenGet();
extern void MBMasuPathTypeWrapLenGet();
extern void MBMasuPathWrapLenGet();
extern void MBMasuPlayerLightSet();
extern void MBMasuPosGet();
extern void MBMasuRotGet();
extern void MBMasuSaiHiddenSet();
extern void MBMasuStarExec();
extern void MBMasuStarGet();
extern void MBMasuStub();
extern void MBMasuTargetGet();
extern void MBMasuTypeChange();
extern void MBMasuTypeLinkGet();
extern void MBMasuTypeSet();
extern void MBMasuWalkEndEventExec();
extern void MBMasuWalkEndExec();
extern void MBMasuWalkExec();
extern void MBMasuWalkPostExec();
extern void MBMasuWalkPostHookSet();
extern void MBMasuWalkPreExec();
extern void MBMasuWalkPreHookSet();
extern void MBMgCallDataClose();
extern void MBMgCallDispSet();
extern void MBMgCallDonkeyExec();
extern void MBMgCallExec();
extern void MBMgCallInit();
extern void MBMgCallKettouExec();
extern void MBMgCallKupaExec();
extern void MBMgCallTutorialExec();
extern void MBMgCallVsExec();
extern void MBModelAlphaSet();
extern void MBModelAmbSet();
extern void MBModelAmbSetAll();
extern void MBModelAttrReset();
extern void MBModelAttrSet();
extern void MBModelCameraSet();
extern void MBModelCameraSetAll();
extern void MBModelClose();
extern void MBModelCreate();
extern void MBModelCreateChar();
extern void MBModelCreateParam();
extern void MBModelDispGet();
extern void MBModelDispOffAll();
extern void MBModelDispOffCamera();
extern void MBModelDispSet();
extern void MBModelHookObjReset();
extern void MBModelHookReset();
extern void MBModelHookSet();
extern void MBModelIdGet();
extern void MBModelInit();
extern void MBModelKill();
extern void MBModelLayerGet();
extern void MBModelLayerSet();
extern void MBModelLayerSetAll();
extern void MBModelManDummy();
extern void MBModelMtxGet();
extern void MBModelMtxSet();
extern void MBModelOffsetGet();
extern void MBModelOffsetSet();
extern void MBModelOffsetSetV();
extern void MBModelPosGet();
extern void MBModelPosSet();
extern void MBModelPosSetV();
extern void MBModelRotGet();
extern void MBModelRotSet();
extern void MBModelRotSetV();
extern void MBModelRotYGet();
extern void MBModelRotYSet();
extern void MBModelScaleGet();
extern void MBModelScaleSet();
extern void MBModelScaleSetV();
extern void MBModelSePlay();
extern void MBModelStub();
extern void MBModelStubVal2Set();
extern void MBModelStubValSet();
extern void MBModelUnkFlagSet();
extern void MBModelUnkSpeedSet();
extern void MBModelZWriteOffSet();
extern void MBMotionCreate();
extern void MBMotionEndCheck();
extern void MBMotionKill();
extern void MBMotionLoopSet();
extern void MBMotionMaxTimeGet();
extern void MBMotionNoSet();
extern void MBMotionShapeEndCheck();
extern void MBMotionShapeMaxTimeGet();
extern void MBMotionShapeSet();
extern void MBMotionShapeSpeedGet();
extern void MBMotionShapeSpeedSet();
extern void MBMotionShapeStartEndSet();
extern void MBMotionShapeTimeGet();
extern void MBMotionShiftIDGet();
extern void MBMotionShiftSet();
extern void MBMotionSpeedGet();
extern void MBMotionSpeedSet();
extern void MBMotionStartEndSet();
extern void MBMotionTimeGet();
extern void MBMotionTimeSet();
extern void MBMotionVoiceOnSet();
extern void MBMtxLookAtCalc();
extern void MBMusCheck();
extern void MBMusEndCheck();
extern void MBMusFadeOut();
extern void MBMusFadeOutDefault();
extern void MBMusJingleStatGet();
extern void MBMusMainPlay();
extern void MBMusParamSet();
extern void MBMusPauseFadeOut();
extern void MBMusPlay();
extern void MBMusPlayJingle();
extern void MBMusStatGet();
extern void MBMusStopCheck();
extern void MBMusStub();
extern void MBObjectSetup();
extern void MBOpeningExec();
extern void MBOpeningProcExec();
extern void MBOpeningViewFocusGet();
extern void MBOpeningViewRotGet();
extern void MBOpeningViewSet();
extern void MBOpeningViewZoomGet();
extern void MBOvlGoto();
extern void MBPadBtnDownGetAll();
extern void MBPadDStkRepGetAll();
extern void MBPadStkXGet();
extern void MBPadStkYGet();
extern void MBPartySaveInit();
extern void MBPauseDisableGet();
extern void MBPauseDisableSet();
extern void MBPauseDispCopyCreate();
extern void MBPauseDispCopyKill();
extern void MBPauseFlagCheck();
extern void MBPauseFlagReset();
extern void MBPauseFlagSet();
extern void MBPauseHookPop();
extern void MBPauseHookPush();
extern void MBPauseOptionExec();
extern void MBPauseProcCheck();
extern void MBPauseProcCreate();
extern void MBPauseSet();
extern void MBPauseStartCheck();
extern void MBPauseWatchProcCreate();
extern void MBPauseWatchProcGet();
extern void MBPauseWatchProcStop();
extern void MBPlayerAliveCheck();
extern void MBPlayerAliveGet();
extern void MBPlayerAlivePlayerGet();
extern void MBPlayerAllComCheck();
extern void MBPlayerAmbSet();
extern void MBPlayerBestPathGet();
extern void MBPlayerBlackoutGet();
extern void MBPlayerBlackoutSet();
extern void MBPlayerCameraSet();
extern void MBPlayerCapsuleAdd();
extern void MBPlayerCapsuleFind();
extern void MBPlayerCapsuleGet();
extern void MBPlayerCapsuleMaxGet();
extern void MBPlayerCapsuleNumGet();
extern void MBPlayerCapsuleRemove();
extern void MBPlayerCapsuleUseGet();
extern void MBPlayerCapsuleUseSet();
extern void MBPlayerClose();
extern void MBPlayerCoinAdd();
extern void MBPlayerCoinGet();
extern void MBPlayerCoinSet();
extern void MBPlayerColorGet();
extern void MBPlayerDeadCheck();
extern void MBPlayerDeadComGet();
extern void MBPlayerDeadGet();
extern void MBPlayerDispSet();
extern void MBPlayerEyeMatDarkSet();
extern void MBPlayerGrpCapsuleGet();
extern void MBPlayerGrpCapsuleNumGet();
extern void MBPlayerGrpCoinGet();
extern void MBPlayerGrpCoinSet();
extern void MBPlayerGrpFind();
extern void MBPlayerGrpFindOther();
extern void MBPlayerGrpFindPlayer();
extern void MBPlayerGrpRankGet();
extern void MBPlayerGrpStarGet();
extern void MBPlayerGrpStarSet();
extern void MBPlayerInit();
extern void MBPlayerKettouCheck();
extern void MBPlayerKettouStoryCheck();
extern void MBPlayerLayerSet();
extern void MBPlayerMasuCornerGet();
extern void MBPlayerMasuCornerSet();
extern void MBPlayerMasuWalk();
extern void MBPlayerMasuWalkPos();
extern void MBPlayerMasuWalkSpeed();
extern void MBPlayerMasuWalkTo();
extern void MBPlayerMaxCoinGet();
extern void MBPlayerModelAttrReset();
extern void MBPlayerModelAttrSet();
extern void MBPlayerModelGet();
extern void MBPlayerMotIdleSet();
extern void MBPlayerMotionCreate();
extern void MBPlayerMotionEndCheck();
extern void MBPlayerMotionEndCheckAll();
extern void MBPlayerMotionEndWait();
extern void MBPlayerMotionKill();
extern void MBPlayerMotionMaxTimeGet();
extern void MBPlayerMotionNoGet();
extern void MBPlayerMotionNoSet();
extern void MBPlayerMotionNoShiftSet();
extern void MBPlayerMotionSpeedSet();
extern void MBPlayerMotionStartEndSet();
extern void MBPlayerMotionTimeGet();
extern void MBPlayerMotionTimeSet();
extern void MBPlayerMotionVoiceOnSet();
extern void MBPlayerMoveCheck();
extern void MBPlayerMtxSet();
extern void MBPlayerNameGet();
extern void MBPlayerNameMesGet();
extern void MBPlayerPosFix();
extern void MBPlayerPosFixCheck();
extern void MBPlayerPosFixCurr();
extern void MBPlayerPosFixEvent();
extern void MBPlayerPosFixFlagSet();
extern void MBPlayerPosFixOrderSet();
extern void MBPlayerPosFixPlayer();
extern void MBPlayerPosFixSet();
extern void MBPlayerPosFixWarp();
extern void MBPlayerPosGet();
extern void MBPlayerPosReset();
extern void MBPlayerPosRestoreAll();
extern void MBPlayerPosSet();
extern void MBPlayerPosSetV();
extern void MBPlayerPostTurnHookSet();
extern void MBPlayerPreTurnHookSet();
extern void MBPlayerRankGet();
extern void MBPlayerRotGet();
extern void MBPlayerRotSet();
extern void MBPlayerRotSetV();
extern void MBPlayerRotYGet();
extern void MBPlayerRotYSet();
extern void MBPlayerRotateCheck();
extern void MBPlayerRotateCheckAll();
extern void MBPlayerRotateStart();
extern void MBPlayerSaiMotExec();
extern void MBPlayerSaiTypeGet();
extern void MBPlayerSaveInit();
extern void MBPlayerScaleGet();
extern void MBPlayerScaleSet();
extern void MBPlayerScaleSetV();
extern void MBPlayerStarAdd();
extern void MBPlayerStarGet();
extern void MBPlayerStarSet();
extern void MBPlayerStoryAliveReset();
extern void MBPlayerStoryComCheck();
extern void MBPlayerStoryLoseCheck();
extern void MBPlayerStoryLoseExec();
extern void MBPlayerStoryPlayerCheck();
extern void MBPlayerStoryPlayerGet();
extern void MBPlayerStubValSet();
extern void MBPlayerUnkSpeedSet();
extern void MBPlayerVoicePanPlay();
extern void MBPlayerVoicePlay();
extern void MBPlayerWalkExec();
extern void MBPlayerWalkMain();
extern void MBPlayerWalkSpeedGet();
extern void MBPlayerWinLoseVoicePlay();
extern void MBPlayerWorkGet();
extern void MBPointDepthScale();
extern void MBPostTurnHookSet();
extern void MBPreTurnHookSet();
extern void MBRouletteCheck();
extern void MBRouletteComValueSet();
extern void MBRouletteCreate();
extern void MBRouletteKaneCreate();
extern void MBRouletteMaxSpeedSet();
extern void MBRouletteResultGet();
extern void MBRouletteWait();
extern void MBSaiChanceCharExec();
extern void MBSaiChanceTradeExec();
extern void MBSaiClose();
extern void MBSaiExec();
extern void MBSaiHiddenExec();
extern void MBSaiHitHookSet();
extern void MBSaiInit();
extern void MBSaiKill();
extern void MBSaiKillCheck();
extern void MBSaiKillCheckAll();
extern void MBSaiMotHookSet();
extern void MBSaiNumKill();
extern void MBSaiNumObjCreate();
extern void MBSaiNumShrinkSet();
extern void MBSaiNumStopCheck();
extern void MBSaiPadBtnHookSet();
extern void MBSaiPlayerExec();
extern void MBSaiResultGet();
extern void MBSaiStub();
extern void MBSaiTutorialExec();
extern void MBScrollClose();
extern void MBScrollInit();
extern void MBSpriteCreate();
extern void MBSpriteNumSet();
extern void MBStarClose();
extern void MBStarCreate();
extern void MBStarDispSet();
extern void MBStarDispSetAll();
extern void MBStarFlagGet();
extern void MBStarFlagInit();
extern void MBStarFlagReset();
extern void MBStarFlagSet();
extern void MBStarGetExec();
extern void MBStarGetProcExec();
extern void MBStarInit();
extern void MBStarMapViewExec();
extern void MBStarMapViewProcExec();
extern void MBStarMasuDispSet();
extern void MBStarNextNoGet();
extern void MBStarNextNoSet();
extern void MBStarNoInit();
extern void MBStarNoRandGet();
extern void MBStarNoReset();
extern void MBStarNoSet();
extern void MBStarNumGet();
extern void MBStarNumSet();
extern void MBStarObjDispSet();
extern void MBStarScrollCreate();
extern void MBStarScrollDoneCheck();
extern void MBStarScrollKill();
extern void MBStarScrollStart();
extern void MBStarTutorialExec();
extern void MBStatusCapsuleDispSet();
extern void MBStatusCapsuleFocusSet();
extern void MBStatusClose();
extern void MBStatusColorGet();
extern void MBStatusColorSet();
extern void MBStatusDispBackup();
extern void MBStatusDispFocusSet();
extern void MBStatusDispForceSet();
extern void MBStatusDispForceSetAll();
extern void MBStatusDispGet();
extern void MBStatusDispRestore();
extern void MBStatusDispSet();
extern void MBStatusDispSetAll();
extern void MBStatusInit();
extern void MBStatusKaoNoSet();
extern void MBStatusLayoutSet();
extern void MBStatusMoveCheck();
extern void MBStatusMoveSet();
extern void MBStatusMoveTo();
extern void MBStatusNoGet();
extern void MBStatusNoMoveSet();
extern void MBStatusNoPosGet();
extern void MBStatusPosGet();
extern void MBStatusPosOffGet();
extern void MBStatusPosOnGet();
extern void MBStatusRainbowSet();
extern void MBStatusReinit();
extern void MBStoryEndProcExec();
extern void MBStoryOpeningExec();
extern void MBStorySaveInit();
extern void MBTauntInit();
extern void MBTauntKill();
extern void MBTelopCheck();
extern void MBTelopComNumCreate();
extern void MBTelopCreate();
extern void MBTelopLast5Create();
extern void MBTelopPlayerCreate();
extern void MBTopWinAttrReset();
extern void MBTopWinAttrSet();
extern void MBTopWinChoiceDisable();
extern void MBTopWinChoiceNowGet();
extern void MBTopWinChoiceNowGet2();
extern void MBTopWinDispSet();
extern void MBTopWinDoneCheck();
extern void MBTopWinIDGet();
extern void MBTopWinInsertMesSet();
extern void MBTopWinKill();
extern void MBTopWinMesColSet();
extern void MBTopWinMesMaxSizeGet();
extern void MBTopWinMesSpeedSet();
extern void MBTopWinPause();
extern void MBTopWinPlayerDisable();
extern void MBTopWinPosGet();
extern void MBTopWinPosSet();
extern void MBTopWinPriSet();
extern void MBTopWinScaleGet();
extern void MBTopWinScaleSet();
extern void MBTopWinSizeSet();
extern void MBTopWinWait();
extern void MBTurnExecParty();
extern void MBTurnExecStory();
extern void MBTutorialExec();
extern void MBTutorialExitFlagGet();
extern void MBTutorialSprDispOff();
extern void MBTutorialSprDispOn();
extern void MBTutorialWatchProcCreate();
extern void MBVecDistXZ();
extern void MBVecDistXZCheck();
extern void MBVecMagCheck();
extern void MBVsMgEndExec();
extern void MBVsMgExec();
extern void MBWalkNumCreate();
extern void MBWalkNumCreateColor();
extern void MBWalkNumDispSet();
extern void MBWalkNumKill();
extern void MBWinAttrReset();
extern void MBWinAttrSet();
extern void MBWinCenterGet();
extern void MBWinChoiceDisable();
extern void MBWinChoiceGet();
extern void MBWinChoiceNowGet();
extern void MBWinChoiceNowGet2();
extern void MBWinClose();
extern void MBWinCreate();
extern void MBWinCreateChoice();
extern void MBWinCreateHelp();
extern void MBWinDispSet();
extern void MBWinDoneCheck();
extern void MBWinGet();
extern void MBWinIDGet();
extern void MBWinInit();
extern void MBWinInsertMesSet();
extern void MBWinKill();
extern void MBWinKillAll();
extern void MBWinLastChoiceGet();
extern void MBWinMesColSet();
extern void MBWinMesMaxSizeGet();
extern void MBWinMesSpeedSet();
extern void MBWinPause();
extern void MBWinPauseHook();
extern void MBWinPlayerDisable();
extern void MBWinPosGet();
extern void MBWinPosSet();
extern void MBWinPriSet();
extern void MBWinScaleGet();
extern void MBWinScaleSet();
extern void MBWinSizeSet();
extern void MBWinWait();
extern void MapPos();
extern void MapWall();
extern void MgActorColAttrGet();
extern void MgActorColAttrParamGet();
extern void MgActorColAttrParamSet();
extern void MgActorColAttrReset();
extern void MgActorColAttrSet();
extern void MgActorColCylReset();
extern void MgActorColCylSet();
extern void MgActorColMapInit();
extern void MgActorColMapMaskGet();
extern void MgActorColMapMaskSet();
extern void MgActorColMapPolyGet();
extern void MgActorColMaskGet();
extern void MgActorColMaskSet();
extern void MgActorCreate();
extern void MgActorExec();
extern void MgActorKill();
extern void MgActorObjectSetup();
extern void MgActorPauseOff();
extern void MgActorPauseOn();
extern void MgActorPosGet();
extern void MgActorPosSet();
extern void MgActorPosUpdate();
extern void MgActorVecChase();
extern void MgDecaScoreCalc();
extern void MgNoGet();
extern void MgPlayerAttrCheck();
extern void MgPlayerAttrReset();
extern void MgPlayerAttrSet();
extern void MgPlayerComStkOff();
extern void MgPlayerComStkOn();
extern void MgPlayerCreate();
extern void MgPlayerCreateJumpAlt();
extern void MgPlayerModeAttrCheck();
extern void MgPlayerModeAttrReset();
extern void MgPlayerModeAttrSet();
extern void MgPlayerModeFuncSet();
extern void MgPlayerModeLandSet();
extern void MgPlayerModeSet();
extern void MgPlayerPadSet();
extern void MgPlayerPauseOff();
extern void MgPlayerPauseOn();
extern void MgPlayerStunSet();
extern void MgPlayerVecChase();
extern void MgPlayerVibAttrCheck();
extern void MgPlayerVibAttrSet();
extern void MgPlayerVibrateCreate();
extern void MgPlayerVibrateKill();
extern void MgScoreColorSet();
extern void MgScoreCreate();
extern void MgScoreDigitScaleSet();
extern void MgScoreDigitWidthGet();
extern void MgScoreDigitWidthSet();
extern void MgScoreDispOff();
extern void MgScoreDispOn();
extern void MgScoreInit();
extern void MgScoreKill();
extern void MgScoreMaxDigitGet();
extern void MgScoreMaxDigitSet();
extern void MgScoreModeDefaultSet();
extern void MgScoreModeGet();
extern void MgScorePosGet();
extern void MgScorePosSet();
extern void MgScorePriSet();
extern void MgScoreScaleGet();
extern void MgScoreScaleSet();
extern void MgScoreTPLvlGet();
extern void MgScoreTPLvlSet();
extern void MgScoreValueGet();
extern void MgScoreValueSet();
extern void MgScoreWinColorSet();
extern void MgScoreWinCreate();
extern void MgScoreWinDispSet();
extern void MgScoreWinInit();
extern void MgScoreWinPosSet();
extern void MgScoreWinTPLvlSet();
extern void MgScoreZRotGet();
extern void MgScoreZRotSet();
extern void MgSeqCreate();
extern void MgSeqCreatePrio();
extern void MgSeqDrawSet();
extern void MgSeqFrameNoGet();
extern void MgSeqGameMesIdGet();
extern void MgSeqKill();
extern void MgSeqMaxTimeSet();
extern void MgSeqModeChangeOff();
extern void MgSeqModeChangeOn();
extern void MgSeqModeDelaySet();
extern void MgSeqModeGet();
extern void MgSeqModeHookAdd();
extern void MgSeqModeHookReset();
extern void MgSeqModeNext();
extern void MgSeqModeSet();
extern void MgSeqRecordSet();
extern void MgSeqStatBitReset();
extern void MgSeqStatBitSet();
extern void MgSeqStatGet();
extern void MgSeqTimerValueGet();
extern void MgSeqWinnerSet();
extern void MgSubModeGet();
extern void MgTimerCreate();
extern void MgTimerDigitColorSet();
extern void MgTimerDoneCheck();
extern void MgTimerKill();
extern void MgTimerModeGet();
extern void MgTimerModeOffSet();
extern void MgTimerModeOnSet();
extern void MgTimerParamSet();
extern void MgTimerPosGet();
extern void MgTimerPosSet();
extern void MgTimerRecordDispOff();
extern void MgTimerRecordDispOn();
extern void MgTimerRecordSet();
extern void MgTimerValueGet();
extern void MgTimerWinColorSet();
extern void OSCheckActiveThreads();
extern void OSDumpStopwatch();
extern void OSGetProgressiveMode();
extern void OSGetThreadPriority();
extern void OSInitSemaphore();
extern void OSIsThreadTerminated();
extern void OSSetProgressiveMode();
extern void OSSignalSemaphore();
extern void OSTicksToCalendarTime();
extern void OSWaitSemaphore();
extern void PSMTXInvXpose();
extern void PSMTXMultVecSR();
extern void PSMTXQuat();
extern void PSMTXRotAxisRad();
extern void PSMTXRotRad();
extern void PSMTXScaleApply();
extern void PSMTXTransApply();
extern void PSMTXTranspose();
extern void PSQUATAdd();
extern void PSQUATInverse();
extern void PSQUATMultiply();
extern void PSQUATNormalize();
extern void PSVECDistance();
extern void PSVECDotProduct();
extern void PSVECMag();
extern void PSVECScale();
extern void PSVECSquareDistance();
extern void PSVECSubtract();
extern void PlayerFXPlay();
extern void PlayerFXPlayPos();
extern void PlayerFXStop();
extern void SLBoardLoad();
extern void SLBoardLoadStory();
extern void SLBoardSave();
extern void SLBoardSaveStory();
extern void SLBoxBackupLoad();
extern void SLBoxBackupSlotLoad();
extern void SLBoxDataOffsetGet();
extern void SLCheckSumBoxSet();
extern void SLCheckSumBoxSlotCheck();
extern void SLCheckSumCheck();
extern void SLCheckSumGet();
extern void SLCheckSumSlotGet();
extern void SLCommonLoad();
extern void SLCommonLoadCopy();
extern void SLCommonSaveCopy();
extern void SLCommonSet();
extern void SLCurBoxNoGet();
extern void SLCurBoxNoSet();
extern void SLCurSlotNoGet();
extern void SLCurSlotNoSet();
extern void SLFileClose();
extern void SLFileCreate();
extern void SLFileOpen();
extern void SLFileRead();
extern void SLFileWrite();
extern void SLLoad();
extern void SLSave();
extern void SLSaveBoardEndExec();
extern void SLSaveBoardTurnExec();
extern void SLSaveDataMake();
extern void SLSaveDataSlotMake();
extern void SLSaveEmptyMark();
extern void SLSaveFlagGet();
extern void SLSaveFlagSet();
extern void SLSaveModeExec();
extern void SLSaveSdExec();
extern void SLSaveStaffExec();
extern void SLSaveStoryExec();
extern void SLSdLoad();
extern void SLSdSave();
extern void SLSerialNoCheck();
extern void SLSerialNoGet();
extern void SLWinIdSet();
extern void SetDefLight();
extern void THPSimpleGetFrameRate();
extern void VIGetDTVStatus();
extern void WipeCheckEnd();
extern void WipeColorSet();
extern void WipeCreate();
extern void WipeTypeGet();
extern void _CheckFlag();
extern void _ClearFlag();
extern void _SetFlag();
extern void __construct_array();
extern void __destroy_arr();
extern void atan2();
extern void atan2f();
extern void cos();
extern void espAttrReset();
extern void espAttrSet();
extern void espBankSet();
extern void espColorSet();
extern void espDispOff();
extern void espDispOn();
extern void espDrawNoSet();
extern void espEntry();
extern void espGrpIDGet();
extern void espInit();
extern void espKill();
extern void espPosSet();
extern void espPriSet();
extern void espScaleSet();
extern void espSpeedSet();
extern void espTPLvlSet();
extern void espZRotSet();
extern void fmod();
extern void fn_8006C2E0();
extern void fn_8008D448();
extern void fn_8008D450();
extern void fn_8008D458();
extern void fn_8008D460();
extern void fn_801A7E90();
extern void fn_801A7F78();
extern void frandf();
extern void frandmod();
extern void msmMusPlay();
extern void msmMusSetMasterVolume();
extern void msmSeGetIndexPtr();
extern void msmSeSetListener();
extern void msmSeUpdataListener();
extern void msmSysGetOutputMode();
extern void msmSysSetGroupLoadMode();
extern void mtxRotCat();
extern void omAddObjEx();
extern void omCameraViewCheck();
extern void omCameraViewInit();
extern void omCameraViewMove();
extern void omCameraViewMoveMulti();
extern void omCameraViewMoveSimple();
extern void omCameraViewMoveSimpleMulti();
extern void omCameraViewSet();
extern void omCameraViewSetMulti();
extern void omCurrentOvlGet();
extern void omDBGSystemKeyCheckSetup();
extern void omDelObjEx();
extern void omGameSysInit();
extern void omGetGroupMemberListEx();
extern void omInitObjMan();
extern void omMakeGroupEx();
extern void omOutView();
extern void omOutViewMulti();
extern void omOvlHisChg();
extern void omOvlHisGet();
extern void omOvlReturnEx();
extern void omPauseChk();
extern void omResetStatBit();
extern void omSetStatBit();
extern void omVibrate();
extern void print8();
extern void printWin();
extern void rand8();
extern void AddX(); /* data */
extern void AddZ(); /* data */
extern void CRotM(); /* data */
extern void CZoomM(); /* data */
extern void Center(); /* data */
extern void CenterM(); /* data */
extern void CharObject(); /* data */
extern void GXNtsc240Int(); /* data */
extern void GXNtsc480Int(); /* data */
extern void GXNtsc480Prog(); /* data */
extern void GameMesOvlPrev(); /* data */
extern void GwCommonBackup(); /* data */
extern void GwPlayer(); /* data */
extern void GwSdBackupNo(); /* data */
extern void GwSystem(); /* data */
extern void HitFace(); /* data */
extern void HitFaceCount(); /* data */
extern void HitFaceVec(); /* data */
extern void MapObject(); /* data */
extern void UnMountCnt(); /* data */
extern void _restfpr_22(); /* data */
extern void _restfpr_24(); /* data */
extern void _restfpr_27(); /* data */
extern void _restfpr_28(); /* data */
extern void _restgpr_14(); /* data */
extern void _restgpr_15(); /* data */
extern void _restgpr_16(); /* data */
extern void _savefpr_22(); /* data */
extern void _savefpr_24(); /* data */
extern void _savefpr_27(); /* data */
extern void _savefpr_28(); /* data */
extern void _savegpr_14(); /* data */
extern void _savegpr_15(); /* data */
extern void _savegpr_16(); /* data */
extern void charEyeBmpNameTbl(); /* data */
extern void curSlotNo(); /* data */
extern void lbl_80288138(); /* data */
extern void lbl_8028813C(); /* data */
extern void lbl_80288140(); /* data */
extern void lbl_80288888(); /* data */
extern void lbl_80288A28(); /* data */
extern void lbl_80288A2C(); /* data */
extern void lbl_80288A30(); /* data */
extern void m562CtrlNo(); /* data */
extern void mgBoard2Force(); /* data */
extern void mgDataTbl(); /* data */
extern void mgExitStartF(); /* data */
extern void mgInstExitF(); /* data */
extern void mgMatchGameType(); /* data */
extern void mgModeWork(); /* data */
extern void mgPauseExitF(); /* data */
extern void mgSubMode(); /* data */
extern void nChar(); /* data */
extern void nMap(); /* data */
extern void omovlevtno(); /* data */
extern void omovlstat(); /* data */
extern void saveExecF(); /* data */
extern void sdHealthLoss(); /* data */
extern void sdWorkFloat(); /* data */
extern void sdWorkInt(); /* data */

// Nothing calls the stubs; retail keeps them (and what only they reach) all the same.
#pragma force_active on

asm void fn_801A811C(void) {
    nofralloc
    b OSDumpStopwatch
}

asm void fn_801A8120(void) {
    nofralloc
    b PSVECDotProduct
}

asm void fn_801A8124(void) {
    nofralloc
    b PSVECDistance
}

asm void fn_801A8128(void) {
    nofralloc
    b PSVECSquareDistance
}

asm void fn_801A812C(void) {
    nofralloc
    b VIGetDTVStatus
}

asm void fn_801A8130(void) {
    nofralloc
    b OSGetProgressiveMode
}

asm void fn_801A8134(void) {
    nofralloc
    b OSSetProgressiveMode
}

asm void fn_801A8138(void) {
    nofralloc
    b PSVECSubtract
}

asm void fn_801A813C(void) {
    nofralloc
    b PSMTXTranspose
}

asm void fn_801A8140(void) {
    nofralloc
    b C_VECReflect
}

asm void fn_801A8144(void) {
    nofralloc
    b PSMTXInvXpose
}

asm void fn_801A8148(void) {
    nofralloc
    b PSMTXRotRad
}

asm void fn_801A814C(void) {
    nofralloc
    b PSMTXRotAxisRad
}

asm void fn_801A8150(void) {
    nofralloc
    b PSVECMag
}

asm void fn_801A8154(void) {
    nofralloc
    b PSVECScale
}

asm void fn_801A8158(void) {
    nofralloc
    b PSMTXMultVecSR
}

asm void fn_801A815C(void) {
    nofralloc
    b C_QUATRotAxisRad
}

asm void fn_801A8160(void) {
    nofralloc
    b C_QUATMtx
}

asm void fn_801A8164(void) {
    nofralloc
    b C_QUATAdd
}

asm void fn_801A8168(void) {
    nofralloc
    b C_QUATSlerp
}

asm void fn_801A816C(void) {
    nofralloc
    b PSQUATAdd
}

asm void fn_801A8170(void) {
    nofralloc
    b PSMTXQuat
}

asm void fn_801A8174(void) {
    nofralloc
    b PSQUATMultiply
}

asm void fn_801A8178(void) {
    nofralloc
    b PSQUATInverse
}

asm void fn_801A817C(void) {
    nofralloc
    b PSQUATNormalize
}

asm void fn_801A8180(void) {
    nofralloc
    b OSTicksToCalendarTime
}

asm void fn_801A8184(void) {
    nofralloc
    b PSMTXTransApply
}

asm void fn_801A8188(void) {
    nofralloc
    b PSMTXScaleApply
}

asm void fn_801A818C(void) {
    nofralloc
    b OSCheckActiveThreads
}

asm void fn_801A8190(void) {
    nofralloc
    b OSGetThreadPriority
}

asm void fn_801A8194(void) {
    nofralloc
    b OSInitSemaphore
}

asm void fn_801A8198(void) {
    nofralloc
    b OSIsThreadTerminated
}

asm void fn_801A819C(void) {
    nofralloc
    b OSSignalSemaphore
}

asm void fn_801A81A0(void) {
    nofralloc
    b OSWaitSemaphore
}

asm void fn_801A81A4(void) {
    nofralloc
    b GXWaitDrawDone
}

asm void fn_801A81A8(void) {
    nofralloc
    b GXProject
}

asm void fn_801A81AC(void) {
    nofralloc
    b GXGetProjectionv
}

asm void fn_801A81B0(void) {
    nofralloc
    b GXGetViewportv
}

asm void fn_801A81B4(void) {
    nofralloc
    b GXPixModeSync
}

asm void fn_801A81B8(void) {
    nofralloc
    b GXSetIndTexOrder
}

asm void fn_801A81BC(void) {
    nofralloc
    b GXSetIndTexMtx
}

asm void fn_801A81C0(void) {
    nofralloc
    b GXSetTevIndWarp
}

asm void fn_801A81C4(void) {
    nofralloc
    b GXSetTexCoordScaleManually
}

asm void fn_801A81C8(void) {
    nofralloc
    b GXSetTevIndTile
}

asm void fn_801A81CC(void) {
    nofralloc
    b GXNtsc480Prog
}

asm void fn_801A81D0(void) {
    nofralloc
    b GXNtsc480Int
}

asm void fn_801A81D4(void) {
    nofralloc
    b GXNtsc240Int
}

asm void fn_801A81D8(void) {
    nofralloc
    b GXSetVtxDescv
}

asm void fn_801A81DC(void) {
    nofralloc
    b omSetStatBit
}

asm void fn_801A81E0(void) {
    nofralloc
    b GameMesKillCheck
}

asm void fn_801A81E4(void) {
    nofralloc
    b WipeCheckEnd
}

asm void fn_801A81E8(void) {
    nofralloc
    b WipeTypeGet
}

asm void fn_801A81EC(void) {
    nofralloc
    b omMakeGroupEx
}

asm void fn_801A81F0(void) {
    nofralloc
    b omGetGroupMemberListEx
}

asm void fn_801A81F4(void) {
    nofralloc
    b GameMesDispSet
}

asm void fn_801A81F8(void) {
    nofralloc
    b GameMesKill
}

asm void fn_801A81FC(void) {
    nofralloc
    b ClusterAdjustObject
}

asm void fn_801A8200(void) {
    nofralloc
    b printWin
}

asm void fn_801A8204(void) {
    nofralloc
    b print8
}

asm void fn_801A8208(void) {
    nofralloc
    b HuSysVWaitSet
}

asm void fn_801A820C(void) {
    nofralloc
    b GameMesInit
}

asm void fn_801A8210(void) {
    nofralloc
    b GameMesCreate
}

asm void fn_801A8214(void) {
    nofralloc
    b omDelObjEx
}

asm void fn_801A8218(void) {
    nofralloc
    b GameMesPosSet
}

asm void fn_801A821C(void) {
    nofralloc
    b atan2
}

asm void fn_801A8220(void) {
    nofralloc
    b atan2f
}

asm void fn_801A8224(void) {
    nofralloc
    b cos
}

asm void fn_801A8228(void) {
    nofralloc
    b GameMesStatGet
}

asm void fn_801A822C(void) {
    nofralloc
    b Center
}

asm void fn_801A8230(void) {
    nofralloc
    b CRotM
}

asm void fn_801A8234(void) {
    nofralloc
    b CenterM
}

asm void fn_801A8238(void) {
    nofralloc
    b CZoomM
}

asm void fn_801A823C(void) {
    nofralloc
    b omOutViewMulti
}

asm void fn_801A8240(void) {
    nofralloc
    b omOutView
}

asm void fn_801A8244(void) {
    nofralloc
    b omAddObjEx
}

asm void fn_801A8248(void) {
    nofralloc
    b omInitObjMan
}

asm void fn_801A824C(void) {
    nofralloc
    b rand8
}

asm void fn_801A8250(void) {
    nofralloc
    b frandmod
}

asm void fn_801A8254(void) {
    nofralloc
    b SetDefLight
}

asm void fn_801A8258(void) {
    nofralloc
    b HuSetVecF
}

asm void fn_801A825C(void) {
    nofralloc
    b HuSubVecF
}

asm void fn_801A8260(void) {
    nofralloc
    b frandf
}

asm void fn_801A8264(void) {
    nofralloc
    b GameMesSprKill
}

asm void fn_801A8268(void) {
    nofralloc
    b mtxRotCat
}

asm void fn_801A826C(void) {
    nofralloc
    b MgScoreWinInit
}

asm void fn_801A8270(void) {
    nofralloc
    b MgScoreWinCreate
}

asm void fn_801A8274(void) {
    nofralloc
    b MgScoreWinColorSet
}

asm void fn_801A8278(void) {
    nofralloc
    b MgScoreWinTPLvlSet
}

asm void fn_801A827C(void) {
    nofralloc
    b MgScoreWinPosSet
}

asm void fn_801A8280(void) {
    nofralloc
    b MgScoreWinDispSet
}

asm void fn_801A8284(void) {
    nofralloc
    b GameMesStrWinCreate
}

asm void fn_801A8288(void) {
    nofralloc
    b Hu3DLayerHookSet
}

asm void fn_801A828C(void) {
    nofralloc
    b Hu3DLayerHookReset
}

asm void fn_801A8290(void) {
    nofralloc
    b Hu3DNoSyncSet
}

asm void fn_801A8294(void) {
    nofralloc
    b Hu3DModelCreate
}

asm void fn_801A8298(void) {
    nofralloc
    b Hu3DModelLink
}

asm void fn_801A829C(void) {
    nofralloc
    b Hu3DHookFuncCreate
}

asm void fn_801A82A0(void) {
    nofralloc
    b Hu3DModelPosSet
}

asm void fn_801A82A4(void) {
    nofralloc
    b Hu3DModelPosSetV
}

asm void fn_801A82A8(void) {
    nofralloc
    b Hu3DModelRotSet
}

asm void fn_801A82AC(void) {
    nofralloc
    b Hu3DModelRotSetV
}

asm void fn_801A82B0(void) {
    nofralloc
    b Hu3DModelScaleSet
}

asm void fn_801A82B4(void) {
    nofralloc
    b Hu3DModelScaleSetV
}

asm void fn_801A82B8(void) {
    nofralloc
    b Hu3DModelKill
}

asm void fn_801A82BC(void) {
    nofralloc
    b Hu3DModelAllKill
}

asm void fn_801A82C0(void) {
    nofralloc
    b Hu3DModelAttrSet
}

asm void fn_801A82C4(void) {
    nofralloc
    b Hu3DModelAttrReset
}

asm void fn_801A82C8(void) {
    nofralloc
    b Hu3DModelAttrGet
}

asm void fn_801A82CC(void) {
    nofralloc
    b Hu3DModelMotionAttrGet
}

asm void fn_801A82D0(void) {
    nofralloc
    b Hu3DBGColorSet
}

asm void fn_801A82D4(void) {
    nofralloc
    b Hu3DModelCameraSet
}

asm void fn_801A82D8(void) {
    nofralloc
    b Hu3DModelLayerSet
}

asm void fn_801A82DC(void) {
    nofralloc
    b Hu3DModelTPLvlSet
}

asm void fn_801A82E0(void) {
    nofralloc
    b Hu3DModelHookSet
}

asm void fn_801A82E4(void) {
    nofralloc
    b Hu3DModelHookReset
}

asm void fn_801A82E8(void) {
    nofralloc
    b Hu3DModelHookObjReset
}

asm void fn_801A82EC(void) {
    nofralloc
    b Hu3DModelAmbSet
}

asm void fn_801A82F0(void) {
    nofralloc
    b Hu3DModelShadowDispOn
}

asm void fn_801A82F4(void) {
    nofralloc
    b Hu3DModelShadowDispOff
}

asm void fn_801A82F8(void) {
    nofralloc
    b Hu3DModelProjectionSet
}

asm void fn_801A82FC(void) {
    nofralloc
    b Hu3DModelProjectionReset
}

asm void fn_801A8300(void) {
    nofralloc
    b Hu3DModelObjPosGet
}

asm void fn_801A8304(void) {
    nofralloc
    b Hu3DModelObjMtxGet
}

asm void fn_801A8308(void) {
    nofralloc
    b Hu3DModelHiliteTypeSet
}

asm void fn_801A830C(void) {
    nofralloc
    b Hu3DModelReflectTypeSet
}

asm void fn_801A8310(void) {
    nofralloc
    b Hu3DModelHiliteMapSet
}

asm void fn_801A8314(void) {
    nofralloc
    b Hu3DReflectModelSet
}

asm void fn_801A8318(void) {
    nofralloc
    b Hu3DModelMatHookSet
}

asm void fn_801A831C(void) {
    nofralloc
    b HuPadInit
}

asm void fn_801A8320(void) {
    nofralloc
    b HuPadRead
}

asm void fn_801A8324(void) {
    nofralloc
    b HuPadRumbleSet
}

asm void fn_801A8328(void) {
    nofralloc
    b HuPadRumbleStop
}

asm void fn_801A832C(void) {
    nofralloc
    b HuPadRumbleAllStop
}

asm void fn_801A8330(void) {
    nofralloc
    b HuPadStatGet
}

asm void fn_801A8334(void) {
    nofralloc
    b HuPadRumbleGet
}

asm void fn_801A8338(void) {
    nofralloc
    b Hu3DCameraCreate
}

asm void fn_801A833C(void) {
    nofralloc
    b Hu3DCameraPerspectiveSet
}

asm void fn_801A8340(void) {
    nofralloc
    b Hu3DCameraViewportSet
}

asm void fn_801A8344(void) {
    nofralloc
    b Hu3DCameraScissorSet
}

asm void fn_801A8348(void) {
    nofralloc
    b Hu3DCameraPosSet
}

asm void fn_801A834C(void) {
    nofralloc
    b Hu3DCameraKill
}

asm void fn_801A8350(void) {
    nofralloc
    b Hu3DCameraPosGet
}

asm void fn_801A8354(void) {
    nofralloc
    b Hu3DCameraPosSetV
}

asm void fn_801A8358(void) {
    nofralloc
    b Hu3DCameraAllKill
}

asm void fn_801A835C(void) {
    nofralloc
    b Hu3DCameraSet
}

asm void fn_801A8360(void) {
    nofralloc
    b Hu3DCameraMotionOn
}

asm void fn_801A8364(void) {
    nofralloc
    b Hu3DCameraMotionStart
}

asm void fn_801A8368(void) {
    nofralloc
    b Hu3DCameraMotionOff
}

asm void fn_801A836C(void) {
    nofralloc
    b Hu3DModelCameraCreate
}

asm void fn_801A8370(void) {
    nofralloc
    b Hu3DModelCameraInfoSet
}

asm void fn_801A8374(void) {
    nofralloc
    b Hu3DCameraPerspectiveGet
}

asm void fn_801A8378(void) {
    nofralloc
    b Hu3DLighInit
}

asm void fn_801A837C(void) {
    nofralloc
    b Hu3DGLightCreate
}

asm void fn_801A8380(void) {
    nofralloc
    b Hu3DGLightCreateV
}

asm void fn_801A8384(void) {
    nofralloc
    b Hu3DGLightKill
}

asm void fn_801A8388(void) {
    nofralloc
    b Hu3DLightAllKill
}

asm void fn_801A838C(void) {
    nofralloc
    b Hu3DLightSet
}

asm void fn_801A8390(void) {
    nofralloc
    b Hu3DGLightSpotSet
}

asm void fn_801A8394(void) {
    nofralloc
    b Hu3DGLightInfinitytSet
}

asm void fn_801A8398(void) {
    nofralloc
    b Hu3DGLightPointSet
}

asm void fn_801A839C(void) {
    nofralloc
    b Hu3DGLightColorSet
}

asm void fn_801A83A0(void) {
    nofralloc
    b Hu3DGLightPosSetV
}

asm void fn_801A83A4(void) {
    nofralloc
    b Hu3DGLightPosSet
}

asm void fn_801A83A8(void) {
    nofralloc
    b Hu3DGLightPosAimSetV
}

asm void fn_801A83AC(void) {
    nofralloc
    b Hu3DGLightPosAimSet
}

asm void fn_801A83B0(void) {
    nofralloc
    b Hu3DGLightStaticSet
}

asm void fn_801A83B4(void) {
    nofralloc
    b Hu3DLLightParamGet
}

asm void fn_801A83B8(void) {
    nofralloc
    b Hu3DGLightParamGet
}

asm void fn_801A83BC(void) {
    nofralloc
    b Hu3DGLightPosAngleSet
}

asm void fn_801A83C0(void) {
    nofralloc
    b Hu3DModelLightInfoSet
}

asm void fn_801A83C4(void) {
    nofralloc
    b Hu3DModelLightIdGet
}

asm void fn_801A83C8(void) {
    nofralloc
    b Hu3DReflectMapSet
}

asm void fn_801A83CC(void) {
    nofralloc
    b Hu3DReflectNoSet
}

asm void fn_801A83D0(void) {
    nofralloc
    b Hu3DFogSet
}

asm void fn_801A83D4(void) {
    nofralloc
    b Hu3DFogClear
}

asm void fn_801A83D8(void) {
    nofralloc
    b Hu3DModelObjPtrGet
}

asm void fn_801A83DC(void) {
    nofralloc
    b Hu3DModelShadowSet
}

asm void fn_801A83E0(void) {
    nofralloc
    b Hu3DModelShadowReset
}

asm void fn_801A83E4(void) {
    nofralloc
    b Hu3DShadowCreate
}

asm void fn_801A83E8(void) {
    nofralloc
    b Hu3DShadowPosSet
}

asm void fn_801A83EC(void) {
    nofralloc
    b Hu3DShadowTPLvlSet
}

asm void fn_801A83F0(void) {
    nofralloc
    b Hu3DShadowColSet
}

asm void fn_801A83F4(void) {
    nofralloc
    b Hu3DShadowMultiCreate
}

asm void fn_801A83F8(void) {
    nofralloc
    b Hu3DShadowMultiPosSet
}

asm void fn_801A83FC(void) {
    nofralloc
    b Hu3DShadowMultiSizeSet
}

asm void fn_801A8400(void) {
    nofralloc
    b Hu3DShadowMultiColSet
}

asm void fn_801A8404(void) {
    nofralloc
    b Hu3DShadowMultiTPLvlSet
}

asm void fn_801A8408(void) {
    nofralloc
    b Hu3DModelShadowMapSet
}

asm void fn_801A840C(void) {
    nofralloc
    b Hu3DModelShadowMapObjSet
}

asm void fn_801A8410(void) {
    nofralloc
    b Hu3DModelShadowMapObjReset
}

asm void fn_801A8414(void) {
    nofralloc
    b Hu3DShadowSizeSet
}

asm void fn_801A8418(void) {
    nofralloc
    b Hu3DMipMapSet
}

asm void fn_801A841C(void) {
    nofralloc
    b Hu3DModelClusterAttrSet
}

asm void fn_801A8420(void) {
    nofralloc
    b Hu3DModelClusterAttrReset
}

asm void fn_801A8424(void) {
    nofralloc
    b Hu3DLLightCreate
}

asm void fn_801A8428(void) {
    nofralloc
    b Hu3DLLightCreateV
}

asm void fn_801A842C(void) {
    nofralloc
    b Hu3DLLightSpotSet
}

asm void fn_801A8430(void) {
    nofralloc
    b Hu3DLLightInfinitytSet
}

asm void fn_801A8434(void) {
    nofralloc
    b Hu3DLLightPointSet
}

asm void fn_801A8438(void) {
    nofralloc
    b Hu3DLLightKill
}

asm void fn_801A843C(void) {
    nofralloc
    b Hu3DLLightColorSet
}

asm void fn_801A8440(void) {
    nofralloc
    b Hu3DLLightPosSetV
}

asm void fn_801A8444(void) {
    nofralloc
    b Hu3DLLightPosSet
}

asm void fn_801A8448(void) {
    nofralloc
    b Hu3DLLightPosAimSetV
}

asm void fn_801A844C(void) {
    nofralloc
    b Hu3DLLightPosAimSet
}

asm void fn_801A8450(void) {
    nofralloc
    b Hu3DLLightStaticSet
}

asm void fn_801A8454(void) {
    nofralloc
    b Hu3DLLightPosAngleSet
}

asm void fn_801A8458(void) {
    nofralloc
    b Hu3DAnimInit
}

asm void fn_801A845C(void) {
    nofralloc
    b Hu3DAnimCreate
}

asm void fn_801A8460(void) {
    nofralloc
    b Hu3DAnimLink
}

asm void fn_801A8464(void) {
    nofralloc
    b Hu3DAnimKill
}

asm void fn_801A8468(void) {
    nofralloc
    b Hu3DAnimAllKill
}

asm void fn_801A846C(void) {
    nofralloc
    b Hu3DAnimSet
}

asm void fn_801A8470(void) {
    nofralloc
    b Hu3DAnimExec
}

asm void fn_801A8474(void) {
    nofralloc
    b Hu3DAnimAttrSet
}

asm void fn_801A8478(void) {
    nofralloc
    b Hu3DAnimAttrReset
}

asm void fn_801A847C(void) {
    nofralloc
    b Hu3DAnimSpeedSet
}

asm void fn_801A8480(void) {
    nofralloc
    b Hu3DAnimBankSet
}

asm void fn_801A8484(void) {
    nofralloc
    b Hu3DAnmNoSet
}

asm void fn_801A8488(void) {
    nofralloc
    b Hu3DTexScrollCreate
}

asm void fn_801A848C(void) {
    nofralloc
    b Hu3DTexScrollPosSet
}

asm void fn_801A8490(void) {
    nofralloc
    b Hu3DTexScrollPosMoveSet
}

asm void fn_801A8494(void) {
    nofralloc
    b Hu3DTexScrollRotSet
}

asm void fn_801A8498(void) {
    nofralloc
    b Hu3DTexScrollRotMoveSet
}

asm void fn_801A849C(void) {
    nofralloc
    b Hu3DTexScrollKill
}

asm void fn_801A84A0(void) {
    nofralloc
    b Hu3DTexScrollAllKill
}

asm void fn_801A84A4(void) {
    nofralloc
    b Hu3DTexScrollPauseDisableSet
}

asm void fn_801A84A8(void) {
    nofralloc
    b Hu3DParticleCreate
}

asm void fn_801A84AC(void) {
    nofralloc
    b Hu3DParticleScaleSet
}

asm void fn_801A84B0(void) {
    nofralloc
    b Hu3DParticleZRotSet
}

asm void fn_801A84B4(void) {
    nofralloc
    b Hu3DParticleColSet
}

asm void fn_801A84B8(void) {
    nofralloc
    b Hu3DParticleTPLvlSet
}

asm void fn_801A84BC(void) {
    nofralloc
    b Hu3DParticleBlendModeSet
}

asm void fn_801A84C0(void) {
    nofralloc
    b Hu3DParticleHookSet
}

asm void fn_801A84C4(void) {
    nofralloc
    b Hu3DParticleCntSet
}

asm void fn_801A84C8(void) {
    nofralloc
    b Hu3DParticleAttrSet
}

asm void fn_801A84CC(void) {
    nofralloc
    b Hu3DParticleAttrReset
}

asm void fn_801A84D0(void) {
    nofralloc
    b Hu3DParticleAnimModeSet
}

asm void fn_801A84D4(void) {
    nofralloc
    b Hu3DParManInit
}

asm void fn_801A84D8(void) {
    nofralloc
    b Hu3DParManCreate
}

asm void fn_801A84DC(void) {
    nofralloc
    b Hu3DParManKill
}

asm void fn_801A84E0(void) {
    nofralloc
    b Hu3DParManAllKill
}

asm void fn_801A84E4(void) {
    nofralloc
    b Hu3DParManPtrGet
}

asm void fn_801A84E8(void) {
    nofralloc
    b Hu3DParManAttrSet
}

asm void fn_801A84EC(void) {
    nofralloc
    b Hu3DParManAttrReset
}

asm void fn_801A84F0(void) {
    nofralloc
    b Hu3DParManPosSet
}

asm void fn_801A84F4(void) {
    nofralloc
    b Hu3DParManVecSet
}

asm void fn_801A84F8(void) {
    nofralloc
    b Hu3DParManRotSet
}

asm void fn_801A84FC(void) {
    nofralloc
    b Hu3DParManModelIDGet
}

asm void fn_801A8500(void) {
    nofralloc
    b Hu3DParManLink
}

asm void fn_801A8504(void) {
    nofralloc
    b Hu3DParManTimeLimitSet
}

asm void fn_801A8508(void) {
    nofralloc
    b Hu3DParManColorSet
}

asm void fn_801A850C(void) {
    nofralloc
    b Hu3DParManLayerSet
}

asm void fn_801A8510(void) {
    nofralloc
    b Hu3DWaterCreate
}

asm void fn_801A8514(void) {
    nofralloc
    b Hu3DWaterTexPosSet
}

asm void fn_801A8518(void) {
    nofralloc
    b Hu3DWaterTexScaleSet
}

asm void fn_801A851C(void) {
    nofralloc
    b Hu3DWaterPadYSet
}

asm void fn_801A8520(void) {
    nofralloc
    b Hu3DWaterGlowSet
}

asm void fn_801A8524(void) {
    nofralloc
    b Hu3DWaterIndTexMtxSet
}

asm void fn_801A8528(void) {
    nofralloc
    b Hu3DWaterHiliteSet
}

asm void fn_801A852C(void) {
    nofralloc
    b Hu3DWaterHiliteTPLvlSet
}

asm void fn_801A8530(void) {
    nofralloc
    b Hu3DWaterCameraSet
}

asm void fn_801A8534(void) {
    nofralloc
    b Hu3DWaterWaveCreate
}

asm void fn_801A8538(void) {
    nofralloc
    b Hu3DMotionCreate
}

asm void fn_801A853C(void) {
    nofralloc
    b Hu3DMotionInit
}

asm void fn_801A8540(void) {
    nofralloc
    b Hu3DMotionModelCreate
}

asm void fn_801A8544(void) {
    nofralloc
    b Hu3DMotionKill
}

asm void fn_801A8548(void) {
    nofralloc
    b Hu3DMotionAllKill
}

asm void fn_801A854C(void) {
    nofralloc
    b Hu3DMotionSet
}

asm void fn_801A8550(void) {
    nofralloc
    b Hu3DMotionExec
}

asm void fn_801A8554(void) {
    nofralloc
    b Hu3DSubMotionExec
}

asm void fn_801A8558(void) {
    nofralloc
    b Hu3DMotionNext
}

asm void fn_801A855C(void) {
    nofralloc
    b Hu3DMotionTimeSet
}

asm void fn_801A8560(void) {
    nofralloc
    b Hu3DMotionTimeGet
}

asm void fn_801A8564(void) {
    nofralloc
    b Hu3DMotionMaxTimeGet
}

asm void fn_801A8568(void) {
    nofralloc
    b Hu3DMotionStartEndSet
}

asm void fn_801A856C(void) {
    nofralloc
    b Hu3DMotionMotionMaxTimeGet
}

asm void fn_801A8570(void) {
    nofralloc
    b Hu3DMotionEndCheck
}

asm void fn_801A8574(void) {
    nofralloc
    b Hu3DMotionShiftSet
}

asm void fn_801A8578(void) {
    nofralloc
    b Hu3DMotionIDGet
}

asm void fn_801A857C(void) {
    nofralloc
    b Hu3DMotionShiftIDGet
}

asm void fn_801A8580(void) {
    nofralloc
    b Hu3DMotionShiftTimeGet
}

asm void fn_801A8584(void) {
    nofralloc
    b Hu3DMotionShiftMaxTimeGet
}

asm void fn_801A8588(void) {
    nofralloc
    b Hu3DMotionShiftStartEndSet
}

asm void fn_801A858C(void) {
    nofralloc
    b Hu3DMotionShiftSpeedSet
}

asm void fn_801A8590(void) {
    nofralloc
    b Hu3DMotionSpeedSet
}

asm void fn_801A8594(void) {
    nofralloc
    b Hu3DMotionShapeSpeedSet
}

asm void fn_801A8598(void) {
    nofralloc
    b Hu3DMotionShapeTimeSet
}

asm void fn_801A859C(void) {
    nofralloc
    b Hu3DMotionNoMotSet
}

asm void fn_801A85A0(void) {
    nofralloc
    b Hu3DMotionNoMotReset
}

asm void fn_801A85A4(void) {
    nofralloc
    b Hu3DMotionForceSet
}

asm void fn_801A85A8(void) {
    nofralloc
    b Hu3DMotionShapeSet
}

asm void fn_801A85AC(void) {
    nofralloc
    b Hu3DMotionShapeIDGet
}

asm void fn_801A85B0(void) {
    nofralloc
    b Hu3DMotionShapeMaxTimeGet
}

asm void fn_801A85B4(void) {
    nofralloc
    b Hu3DMotionClusterSet
}

asm void fn_801A85B8(void) {
    nofralloc
    b Hu3DMotionClusterNoSet
}

asm void fn_801A85BC(void) {
    nofralloc
    b Hu3DMotionShapeReset
}

asm void fn_801A85C0(void) {
    nofralloc
    b Hu3DMotionClusterReset
}

asm void fn_801A85C4(void) {
    nofralloc
    b Hu3DJointMotion
}

asm void fn_801A85C8(void) {
    nofralloc
    b Hu3DMotionOverlaySet
}

asm void fn_801A85CC(void) {
    nofralloc
    b Hu3DMotionOverlayReset
}

asm void fn_801A85D0(void) {
    nofralloc
    b Hu3DMotionOverlayTimeGet
}

asm void fn_801A85D4(void) {
    nofralloc
    b Hu3DMotionOverlayTimeSet
}

asm void fn_801A85D8(void) {
    nofralloc
    b Hu3DMotionOverlaySpeedSet
}

asm void fn_801A85DC(void) {
    nofralloc
    b Hu3DMotionOverlayMaxTimeGet
}

asm void fn_801A85E0(void) {
    nofralloc
    b Hu3DMotionOverlayEndCheck
}

asm void fn_801A85E4(void) {
    nofralloc
    b Hu3DModelObjDrawInit
}

asm void fn_801A85E8(void) {
    nofralloc
    b Hu3DModelObjDraw
}

asm void fn_801A85EC(void) {
    nofralloc
    b Hu3DModelObjPtrDraw
}

asm void fn_801A85F0(void) {
    nofralloc
    b Hu3DMotionCalc
}

asm void fn_801A85F4(void) {
    nofralloc
    b Hu3DMotionShapeStartEndSet
}

asm void fn_801A85F8(void) {
    nofralloc
    b Hu3DSubMotionSet
}

asm void fn_801A85FC(void) {
    nofralloc
    b Hu3DSubMotionReset
}

asm void fn_801A8600(void) {
    nofralloc
    b Hu3DSubMotionTimeSet
}

asm void fn_801A8604(void) {
    nofralloc
    b Hu3DMotionShiftTimeSet
}

asm void fn_801A8608(void) {
    nofralloc
    b Hu3DMotionClusterSpeedSet
}

asm void fn_801A860C(void) {
    nofralloc
    b Hu3DMotionClusterTimeSet
}

asm void fn_801A8610(void) {
    nofralloc
    b Hu3DMotionClusterMaxTimeGet
}

asm void fn_801A8614(void) {
    nofralloc
    b Hu3DMotionAttrSet
}

asm void fn_801A8618(void) {
    nofralloc
    b Hu3DMotionAttrReset
}

asm void fn_801A861C(void) {
    nofralloc
    b Hu3DMatLightSet
}

asm void fn_801A8620(void) {
    nofralloc
    b Hu3DFbCopyLayerSet
}

asm void fn_801A8624(void) {
    nofralloc
    b Hu3DFbCopyExec
}

asm void fn_801A8628(void) {
    nofralloc
    b Hu3DZClear
}

asm void fn_801A862C(void) {
    nofralloc
    b Hu3DZClearLayerSet
}

asm void fn_801A8630(void) {
    nofralloc
    b CamMotionEx
}

asm void fn_801A8634(void) {
    nofralloc
    b CamMotionEx2
}

asm void fn_801A8638(void) {
    nofralloc
    b CamMotionExPathGet
}

asm void fn_801A863C(void) {
    nofralloc
    b CamMotionExPath
}

asm void fn_801A8640(void) {
    nofralloc
    b Hu3D2Dto3D
}

asm void fn_801A8644(void) {
    nofralloc
    b Hu3D3Dto2D
}

asm void fn_801A8648(void) {
    nofralloc
    b Hu3DMtxRotGet
}

asm void fn_801A864C(void) {
    nofralloc
    b Hu3DMtxTransGet
}

asm void fn_801A8650(void) {
    nofralloc
    b Hu3DMtxScaleGet
}

asm void fn_801A8654(void) {
    nofralloc
    b Hu3DProjectionCreate
}

asm void fn_801A8658(void) {
    nofralloc
    b Hu3DProjectionPosSet
}

asm void fn_801A865C(void) {
    nofralloc
    b Hu3DProjectionTPLvlSet
}

asm void fn_801A8660(void) {
    nofralloc
    b Hu3DProjectionKill
}

asm void fn_801A8664(void) {
    nofralloc
    b HuAudInit
}

asm void fn_801A8668(void) {
    nofralloc
    b HuAudStreamPlay
}

asm void fn_801A866C(void) {
    nofralloc
    b HuAudAllStop
}

asm void fn_801A8670(void) {
    nofralloc
    b HuAudFadeOut
}

asm void fn_801A8674(void) {
    nofralloc
    b HuAudStreamPauseOn
}

asm void fn_801A8678(void) {
    nofralloc
    b HuAudStreamPauseOff
}

asm void fn_801A867C(void) {
    nofralloc
    b HuAudStreamFadeOut
}

asm void fn_801A8680(void) {
    nofralloc
    b HuAudStreamVolSet
}

asm void fn_801A8684(void) {
    nofralloc
    b HuAudFXPlay
}

asm void fn_801A8688(void) {
    nofralloc
    b HuAudFXPlayVol
}

asm void fn_801A868C(void) {
    nofralloc
    b HuAudFXPlayVolPan
}

asm void fn_801A8690(void) {
    nofralloc
    b HuAudFXPlayPan
}

asm void fn_801A8694(void) {
    nofralloc
    b HuAudFXStop
}

asm void fn_801A8698(void) {
    nofralloc
    b HuAudFXFadeOut
}

asm void fn_801A869C(void) {
    nofralloc
    b HuAudFXPanning
}

asm void fn_801A86A0(void) {
    nofralloc
    b HuAudSeqPlay
}

asm void fn_801A86A4(void) {
    nofralloc
    b HuAudSeqStop
}

asm void fn_801A86A8(void) {
    nofralloc
    b HuAudSeqFadeOut
}

asm void fn_801A86AC(void) {
    nofralloc
    b HuAudSeqMidiCtrlGet
}

asm void fn_801A86B0(void) {
    nofralloc
    b HuAudFXListnerSet
}

asm void fn_801A86B4(void) {
    nofralloc
    b HuAudFXListnerUpdate
}

asm void fn_801A86B8(void) {
    nofralloc
    b HuAudFXEmiterPlay
}

asm void fn_801A86BC(void) {
    nofralloc
    b HuAudFXEmiterUpDate
}

asm void fn_801A86C0(void) {
    nofralloc
    b HuAudFXListnerKill
}

asm void fn_801A86C4(void) {
    nofralloc
    b HuAudFXStatusGet
}

asm void fn_801A86C8(void) {
    nofralloc
    b HuAudFXPitchSet
}

asm void fn_801A86CC(void) {
    nofralloc
    b HuAudFXVolSet
}

asm void fn_801A86D0(void) {
    nofralloc
    b HuAudDllSndGrpSet
}

asm void fn_801A86D4(void) {
    nofralloc
    b HuAudSndGrpSetSet
}

asm void fn_801A86D8(void) {
    nofralloc
    b HuAudSndGrpSet
}

asm void fn_801A86DC(void) {
    nofralloc
    b HuAudSndCommonGrpSet
}

asm void fn_801A86E0(void) {
    nofralloc
    b HuAudSStreamPlay
}

asm void fn_801A86E4(void) {
    nofralloc
    b HuAudSStreamStop
}

asm void fn_801A86E8(void) {
    nofralloc
    b HuAudSStreamFadeOut
}

asm void fn_801A86EC(void) {
    nofralloc
    b HuAudSStreamAllFadeOut
}

asm void fn_801A86F0(void) {
    nofralloc
    b HuAudSStreamAllStop
}

asm void fn_801A86F4(void) {
    nofralloc
    b HuAudSStreamStatGet
}

asm void fn_801A86F8(void) {
    nofralloc
    b HuAudSStreamPause
}

asm void fn_801A86FC(void) {
    nofralloc
    b HuAudSStreamPauseFadeOut
}

asm void fn_801A8700(void) {
    nofralloc
    b HuAudSStreamVolSet
}

asm void fn_801A8704(void) {
    nofralloc
    b PlayerFXPlay
}

asm void fn_801A8708(void) {
    nofralloc
    b CharFXPlay
}

asm void fn_801A870C(void) {
    nofralloc
    b CharFXPlayVol
}

asm void fn_801A8710(void) {
    nofralloc
    b CharFXPlayPan
}

asm void fn_801A8714(void) {
    nofralloc
    b CharFXPlayVolPan
}

asm void fn_801A8718(void) {
    nofralloc
    b PlayerFXPlayPos
}

asm void fn_801A871C(void) {
    nofralloc
    b CharFXPlayPos
}

asm void fn_801A8720(void) {
    nofralloc
    b PlayerFXStop
}

asm void fn_801A8724(void) {
    nofralloc
    b CharFXStop
}

asm void fn_801A8728(void) {
    nofralloc
    b HuAudAUXSet
}

asm void fn_801A872C(void) {
    nofralloc
    b HuAudSStreamChanPlay
}

asm void fn_801A8730(void) {
    nofralloc
    b HuAudBGMPlay
}

asm void fn_801A8734(void) {
    nofralloc
    b HuAudJinglePlay
}

asm void fn_801A8738(void) {
    nofralloc
    b msmMusPlay
}

asm void fn_801A873C(void) {
    nofralloc
    b espInit
}

asm void fn_801A8740(void) {
    nofralloc
    b espEntry
}

asm void fn_801A8744(void) {
    nofralloc
    b espKill
}

asm void fn_801A8748(void) {
    nofralloc
    b espGrpIDGet
}

asm void fn_801A874C(void) {
    nofralloc
    b espDispOn
}

asm void fn_801A8750(void) {
    nofralloc
    b espDispOff
}

asm void fn_801A8754(void) {
    nofralloc
    b espAttrSet
}

asm void fn_801A8758(void) {
    nofralloc
    b espAttrReset
}

asm void fn_801A875C(void) {
    nofralloc
    b espPosSet
}

asm void fn_801A8760(void) {
    nofralloc
    b espScaleSet
}

asm void fn_801A8764(void) {
    nofralloc
    b espZRotSet
}

asm void fn_801A8768(void) {
    nofralloc
    b espTPLvlSet
}

asm void fn_801A876C(void) {
    nofralloc
    b espColorSet
}

asm void fn_801A8770(void) {
    nofralloc
    b espSpeedSet
}

asm void fn_801A8774(void) {
    nofralloc
    b espBankSet
}

asm void fn_801A8778(void) {
    nofralloc
    b espDrawNoSet
}

asm void fn_801A877C(void) {
    nofralloc
    b espPriSet
}

asm void fn_801A8780(void) {
    nofralloc
    b HuPrcInit
}

asm void fn_801A8784(void) {
    nofralloc
    b HuPrcCall
}

asm void fn_801A8788(void) {
    nofralloc
    b HuPrcCreate
}

asm void fn_801A878C(void) {
    nofralloc
    b HuPrcKill
}

asm void fn_801A8790(void) {
    nofralloc
    b HuPrcEnd
}

asm void fn_801A8794(void) {
    nofralloc
    b HuPrcWakeup
}

asm void fn_801A8798(void) {
    nofralloc
    b HuPrcSleep
}

asm void fn_801A879C(void) {
    nofralloc
    b HuPrcVSleep
}

asm void fn_801A87A0(void) {
    nofralloc
    b HuPrcCurrentGet
}

asm void fn_801A87A4(void) {
    nofralloc
    b HuPrcDestructorSet
}

asm void fn_801A87A8(void) {
    nofralloc
    b HuPrcDestructorSet2
}

asm void fn_801A87AC(void) {
    nofralloc
    b HuPrcChildCreate
}

asm void fn_801A87B0(void) {
    nofralloc
    b HuPrcChildLink
}

asm void fn_801A87B4(void) {
    nofralloc
    b HuPrcChildUnlink
}

asm void fn_801A87B8(void) {
    nofralloc
    b HuPrcChildKill
}

asm void fn_801A87BC(void) {
    nofralloc
    b HuPrcMemAlloc
}

asm void fn_801A87C0(void) {
    nofralloc
    b HuPrcMemFree
}

asm void fn_801A87C4(void) {
    nofralloc
    b Hu3DParManVacumeSet
}

asm void fn_801A87C8(void) {
    nofralloc
    b HuDataInit
}

asm void fn_801A87CC(void) {
    nofralloc
    b HuDataDirRead
}

asm void fn_801A87D0(void) {
    nofralloc
    b HuDataRead
}

asm void fn_801A87D4(void) {
    nofralloc
    b HuDataReadNum
}

asm void fn_801A87D8(void) {
    nofralloc
    b HuDataReadMulti
}

asm void fn_801A87DC(void) {
    nofralloc
    b HuDataDirReadAsync
}

asm void fn_801A87E0(void) {
    nofralloc
    b HuDataDirReadNumAsync
}

asm void fn_801A87E4(void) {
    nofralloc
    b HuDataSelHeapRead
}

asm void fn_801A87E8(void) {
    nofralloc
    b HuDataSelHeapReadNum
}

asm void fn_801A87EC(void) {
    nofralloc
    b HuDataGetSize
}

asm void fn_801A87F0(void) {
    nofralloc
    b HuDataDirClose
}

asm void fn_801A87F4(void) {
    nofralloc
    b HuDataDirCloseNum
}

asm void fn_801A87F8(void) {
    nofralloc
    b HuDataClose
}

asm void fn_801A87FC(void) {
    nofralloc
    b HuDataCloseMulti
}

asm void fn_801A8800(void) {
    nofralloc
    b HuDataReadNumHeapShortForce
}

asm void fn_801A8804(void) {
    nofralloc
    b HuDataDirCancel
}

asm void fn_801A8808(void) {
    nofralloc
    b ARRegisterDMACallback
}

asm void fn_801A880C(void) {
    nofralloc
    b ARGetDMAStatus
}

asm void fn_801A8810(void) {
    nofralloc
    b ARStartDMA
}

asm void fn_801A8814(void) {
    nofralloc
    b ARInit
}

asm void fn_801A8818(void) {
    nofralloc
    b ARAlloc
}

asm void fn_801A881C(void) {
    nofralloc
    b ARFree
}

asm void fn_801A8820(void) {
    nofralloc
    b ARGetSize
}

asm void fn_801A8824(void) {
    nofralloc
    b ARSetSize
}

asm void fn_801A8828(void) {
    nofralloc
    b HuSprBegin
}

asm void fn_801A882C(void) {
    nofralloc
    b HuSprCall
}

asm void fn_801A8830(void) {
    nofralloc
    b HuSprFinish
}

asm void fn_801A8834(void) {
    nofralloc
    b HuSprAnimRead
}

asm void fn_801A8838(void) {
    nofralloc
    b HuSprCreate
}

asm void fn_801A883C(void) {
    nofralloc
    b HuSprGrpCreate
}

asm void fn_801A8840(void) {
    nofralloc
    b HuSprGrpMemberSet
}

asm void fn_801A8844(void) {
    nofralloc
    b HuSprGrpMemberKill
}

asm void fn_801A8848(void) {
    nofralloc
    b HuSprGrpKill
}

asm void fn_801A884C(void) {
    nofralloc
    b HuSprKill
}

asm void fn_801A8850(void) {
    nofralloc
    b HuSprAnimKill
}

asm void fn_801A8854(void) {
    nofralloc
    b HuSprAttrSet
}

asm void fn_801A8858(void) {
    nofralloc
    b HuSprAttrReset
}

asm void fn_801A885C(void) {
    nofralloc
    b HuSprAttrGet
}

asm void fn_801A8860(void) {
    nofralloc
    b HuSprPosSet
}

asm void fn_801A8864(void) {
    nofralloc
    b HuSprScaleSet
}

asm void fn_801A8868(void) {
    nofralloc
    b HuSprZRotSet
}

asm void fn_801A886C(void) {
    nofralloc
    b HuSprGrpPosSet
}

asm void fn_801A8870(void) {
    nofralloc
    b HuSprGrpZRotSet
}

asm void fn_801A8874(void) {
    nofralloc
    b HuSprGrpScaleSet
}

asm void fn_801A8878(void) {
    nofralloc
    b HuSprTPLvlSet
}

asm void fn_801A887C(void) {
    nofralloc
    b HuSprColorSet
}

asm void fn_801A8880(void) {
    nofralloc
    b HuSprSpeedSet
}

asm void fn_801A8884(void) {
    nofralloc
    b HuSprBankSet
}

asm void fn_801A8888(void) {
    nofralloc
    b HuSprGrpDrawNoSet
}

asm void fn_801A888C(void) {
    nofralloc
    b HuSprDrawNoSet
}

asm void fn_801A8890(void) {
    nofralloc
    b HuSprPriSet
}

asm void fn_801A8894(void) {
    nofralloc
    b HuSprFuncCreate
}

asm void fn_801A8898(void) {
    nofralloc
    b HuSprAnimMake
}

asm void fn_801A889C(void) {
    nofralloc
    b HuSprGrpCenterSet
}

asm void fn_801A88A0(void) {
    nofralloc
    b HuSprAnimLock
}

asm void fn_801A88A4(void) {
    nofralloc
    b AnimDebug
}

asm void fn_801A88A8(void) {
    nofralloc
    b HuSprExecLayerSet
}

asm void fn_801A88AC(void) {
    nofralloc
    b HuSprSprBGSet
}

asm void fn_801A88B0(void) {
    nofralloc
    b HuSprBGSet
}

asm void fn_801A88B4(void) {
    nofralloc
    b HuSprGrpScissorSet
}

asm void fn_801A88B8(void) {
    nofralloc
    b HuSprScissorSet
}

asm void fn_801A88BC(void) {
    nofralloc
    b HuSprGrpTPLvlSet
}

asm void fn_801A88C0(void) {
    nofralloc
    b HuSprExecLayerCameraSet
}

asm void fn_801A88C4(void) {
    nofralloc
    b HuSprAnimNoSet
}

asm void fn_801A88C8(void) {
    nofralloc
    b HuSprAnimNoSetPause
}

asm void fn_801A88CC(void) {
    nofralloc
    b HuARMalloc
}

asm void fn_801A88D0(void) {
    nofralloc
    b HuARFree
}

asm void fn_801A88D4(void) {
    nofralloc
    b HuAR_DVDtoARAM
}

asm void fn_801A88D8(void) {
    nofralloc
    b HuAR_MRAMtoARAM
}

asm void fn_801A88DC(void) {
    nofralloc
    b HuAR_MRAMtoARAM2
}

asm void fn_801A88E0(void) {
    nofralloc
    b HuAR_ARAMtoMRAM
}

asm void fn_801A88E4(void) {
    nofralloc
    b HuAR_ARAMtoMRAMNum
}

asm void fn_801A88E8(void) {
    nofralloc
    b HuARDMACheck
}

asm void fn_801A88EC(void) {
    nofralloc
    b HuARDirCheck
}

asm void fn_801A88F0(void) {
    nofralloc
    b HuARDirFree
}

asm void fn_801A88F4(void) {
    nofralloc
    b HuAR_ARAMtoMRAMFileRead
}

asm void fn_801A88F8(void) {
    nofralloc
    b HuAudFXListnerSetEX
}

asm void fn_801A88FC(void) {
    nofralloc
    b HuWindowInit
}

asm void fn_801A8900(void) {
    nofralloc
    b HuWinInit
}

asm void fn_801A8904(void) {
    nofralloc
    b HuWinCreate
}

asm void fn_801A8908(void) {
    nofralloc
    b HuWinKill
}

asm void fn_801A890C(void) {
    nofralloc
    b HuWinAllKill
}

asm void fn_801A8910(void) {
    nofralloc
    b HuWinMesSet
}

asm void fn_801A8914(void) {
    nofralloc
    b HuWinInsertMesSet
}

asm void fn_801A8918(void) {
    nofralloc
    b HuWinChoiceGet
}

asm void fn_801A891C(void) {
    nofralloc
    b HuWinChoiceSet
}

asm void fn_801A8920(void) {
    nofralloc
    b HuWinChoiceNumGet
}

asm void fn_801A8924(void) {
    nofralloc
    b HuWinMesWait
}

asm void fn_801A8928(void) {
    nofralloc
    b HuWinSprKill
}

asm void fn_801A892C(void) {
    nofralloc
    b HuWinMesRead
}

asm void fn_801A8930(void) {
    nofralloc
    b HuWinAnimSet
}

asm void fn_801A8934(void) {
    nofralloc
    b HuWinSprSet
}

asm void fn_801A8938(void) {
    nofralloc
    b HuWinSprPosSet
}

asm void fn_801A893C(void) {
    nofralloc
    b HuWinSprIDGet
}

asm void fn_801A8940(void) {
    nofralloc
    b HuWinMesMaxSizeGet
}

asm void fn_801A8944(void) {
    nofralloc
    b HuWinInsertMesSizeGet
}

asm void fn_801A8948(void) {
    nofralloc
    b HuWinMesMaxSizeBetGet
}

asm void fn_801A894C(void) {
    nofralloc
    b HuWinExCreate
}

asm void fn_801A8950(void) {
    nofralloc
    b HuWinDispOn
}

asm void fn_801A8954(void) {
    nofralloc
    b HuWinDispOff
}

asm void fn_801A8958(void) {
    nofralloc
    b HuWinExOpen
}

asm void fn_801A895C(void) {
    nofralloc
    b HuWinExClose
}

asm void fn_801A8960(void) {
    nofralloc
    b HuWinExKill
}

asm void fn_801A8964(void) {
    nofralloc
    b HuWinExSpeakerSet
}

asm void fn_801A8968(void) {
    nofralloc
    b HuWinComKeyWait
}

asm void fn_801A896C(void) {
    nofralloc
    b HuWinComKeySet
}

asm void fn_801A8970(void) {
    nofralloc
    b HuWinComKeyReset
}

asm void fn_801A8974(void) {
    nofralloc
    b HuWinDrawNoSet
}

asm void fn_801A8978(void) {
    nofralloc
    b HuWinAttrSet
}

asm void fn_801A897C(void) {
    nofralloc
    b HuWinAttrReset
}

asm void fn_801A8980(void) {
    nofralloc
    b HuWinBGTPLvlSet
}

asm void fn_801A8984(void) {
    nofralloc
    b HuWinMesSpeedSet
}

asm void fn_801A8988(void) {
    nofralloc
    b HuWinBGColSet
}

asm void fn_801A898C(void) {
    nofralloc
    b HuWinChoiceDisable
}

asm void fn_801A8990(void) {
    nofralloc
    b HuWinKeyWaitEntry
}

asm void fn_801A8994(void) {
    nofralloc
    b HuWinCenterPosSet
}

asm void fn_801A8998(void) {
    nofralloc
    b HuWinPosSet
}

asm void fn_801A899C(void) {
    nofralloc
    b HuWinZRotSet
}

asm void fn_801A89A0(void) {
    nofralloc
    b HuWinScaleSet
}

asm void fn_801A89A4(void) {
    nofralloc
    b HuWinChoiceNowGet
}

asm void fn_801A89A8(void) {
    nofralloc
    b HuWinStatGet
}

asm void fn_801A89AC(void) {
    nofralloc
    b HuWinMesColSet
}

asm void fn_801A89B0(void) {
    nofralloc
    b HuWinScissorSet
}

asm void fn_801A89B4(void) {
    nofralloc
    b HuWinExCreateFrame
}

asm void fn_801A89B8(void) {
    nofralloc
    b HuWinPriSet
}

asm void fn_801A89BC(void) {
    nofralloc
    b HuWinSprPriSet
}

asm void fn_801A89C0(void) {
    nofralloc
    b HuWinKeyWaitNumGet
}

asm void fn_801A89C4(void) {
    nofralloc
    b HuWinMesSizeCancelCRSet
}

asm void fn_801A89C8(void) {
    nofralloc
    b HuWinMesPalSet
}

asm void fn_801A89CC(void) {
    nofralloc
    b HuWinHomeClear
}

asm void fn_801A89D0(void) {
    nofralloc
    b HuWinPushKeySet
}

asm void fn_801A89D4(void) {
    nofralloc
    b HuWinDisablePlayerSet
}

asm void fn_801A89D8(void) {
    nofralloc
    b HuWinDisablePlayerReset
}

asm void fn_801A89DC(void) {
    nofralloc
    b HuWinMesPtrGet
}

asm void fn_801A89E0(void) {
    nofralloc
    b HuWinMesMaxDirGet
}

asm void fn_801A89E4(void) {
    nofralloc
    b HuWinMesMaxNumGet
}

asm void fn_801A89E8(void) {
    nofralloc
    b CharInit
}

asm void fn_801A89EC(void) {
    nofralloc
    b CharMotionInit
}

asm void fn_801A89F0(void) {
    nofralloc
    b CharMotionInitAsync
}

asm void fn_801A89F4(void) {
    nofralloc
    b CharDataClose
}

asm void fn_801A89F8(void) {
    nofralloc
    b CharModelKill
}

asm void fn_801A89FC(void) {
    nofralloc
    b CharClose
}

asm void fn_801A8A00(void) {
    nofralloc
    b CharModelCreate
}

asm void fn_801A8A04(void) {
    nofralloc
    b CharMotionCreate
}

asm void fn_801A8A08(void) {
    nofralloc
    b CharMotionNoSet
}

asm void fn_801A8A0C(void) {
    nofralloc
    b CharMotionKill
}

asm void fn_801A8A10(void) {
    nofralloc
    b CharMotionDataClose
}

asm void fn_801A8A14(void) {
    nofralloc
    b CharModelDataClose
}

asm void fn_801A8A18(void) {
    nofralloc
    b CharMotionAMemPGet
}

asm void fn_801A8A1C(void) {
    nofralloc
    b CharMotionSet
}

asm void fn_801A8A20(void) {
    nofralloc
    b CharMotionTimeSet
}

asm void fn_801A8A24(void) {
    nofralloc
    b CharMotionTimeGet
}

asm void fn_801A8A28(void) {
    nofralloc
    b CharMotionMaxTimeGet
}

asm void fn_801A8A2C(void) {
    nofralloc
    b CharMotionEndCheck
}

asm void fn_801A8A30(void) {
    nofralloc
    b CharMotionShiftIDGet
}

asm void fn_801A8A34(void) {
    nofralloc
    b CharMotionShiftSet
}

asm void fn_801A8A38(void) {
    nofralloc
    b CharMotionShiftTimeGet
}

asm void fn_801A8A3C(void) {
    nofralloc
    b CharMotionSpeedSet
}

asm void fn_801A8A40(void) {
    nofralloc
    b CharModelHookDustCreate
}

asm void fn_801A8A44(void) {
    nofralloc
    b CharEffectSmokeCreate
}

asm void fn_801A8A48(void) {
    nofralloc
    b CharEffectCoinGlowCreate
}

asm void fn_801A8A4C(void) {
    nofralloc
    b CharModelHitCreate
}

asm void fn_801A8A50(void) {
    nofralloc
    b CharEffectHitCreate
}

asm void fn_801A8A54(void) {
    nofralloc
    b CharEffectShoeHitCreate
}

asm void fn_801A8A58(void) {
    nofralloc
    b CharModelShoeHitCreate
}

asm void fn_801A8A5C(void) {
    nofralloc
    b GWCharColorGet
}

asm void fn_801A8A60(void) {
    nofralloc
    b CharEffectLayerSet
}

asm void fn_801A8A64(void) {
    nofralloc
    b charEyeBmpNameTbl
}

asm void fn_801A8A68(void) {
    nofralloc
    b CharModelEyeBmpGet
}

asm void fn_801A8A6C(void) {
    nofralloc
    b CharMotionVoiceOnSet
}

asm void fn_801A8A70(void) {
    nofralloc
    b CharNpcDustVoiceOffSet
}

asm void fn_801A8A74(void) {
    nofralloc
    b CharModelStepFxSet
}

asm void fn_801A8A78(void) {
    nofralloc
    b CharModelVoicePanAutoSet
}

asm void fn_801A8A7C(void) {
    nofralloc
    b CharModelFxFlagSet
}

asm void fn_801A8A80(void) {
    nofralloc
    b CharModelLandDustCreate
}

asm void fn_801A8A84(void) {
    nofralloc
    b CharModelAttrSet
}

asm void fn_801A8A88(void) {
    nofralloc
    b CharModelAttrReset
}

asm void fn_801A8A8C(void) {
    nofralloc
    b CharMotionStartEndSet
}

asm void fn_801A8A90(void) {
    nofralloc
    b CharModelHeightGet
}

asm void fn_801A8A94(void) {
    nofralloc
    b CharModelMotListCreate
}

asm void fn_801A8A98(void) {
    nofralloc
    b CharEffectDustCreate
}

asm void fn_801A8A9C(void) {
    nofralloc
    b CharEffectCryCreate
}

asm void fn_801A8AA0(void) {
    nofralloc
    b CharModelCryCreate
}

asm void fn_801A8AA4(void) {
    nofralloc
    b CharModelTimingHookNoGet
}

asm void fn_801A8AA8(void) {
    nofralloc
    b CharMotionUpdateSet
}

asm void fn_801A8AAC(void) {
    nofralloc
    b CharModelVoicePanSet
}

asm void fn_801A8AB0(void) {
    nofralloc
    b CharModelVoiceVolSet
}

asm void fn_801A8AB4(void) {
    nofralloc
    b CharWinLoseVoicePlay
}

asm void fn_801A8AB8(void) {
    nofralloc
    b CharLoseVoicePlay
}

asm void fn_801A8ABC(void) {
    nofralloc
    b CharMotionTotalTimeGet
}

asm void fn_801A8AC0(void) {
    nofralloc
    b CharMotionExtraTimeGet
}

asm void fn_801A8AC4(void) {
    nofralloc
    b CharNpcDustSet
}

asm void fn_801A8AC8(void) {
    nofralloc
    b HuPrcSetStat
}

asm void fn_801A8ACC(void) {
    nofralloc
    b HuPrcResetStat
}

asm void fn_801A8AD0(void) {
    nofralloc
    b omGameSysInit
}

asm void fn_801A8AD4(void) {
    nofralloc
    b omResetStatBit
}

asm void fn_801A8AD8(void) {
    nofralloc
    b omCurrentOvlGet
}

asm void fn_801A8ADC(void) {
    nofralloc
    b omPauseChk
}

asm void fn_801A8AE0(void) {
    nofralloc
    b omOvlHisChg
}

asm void fn_801A8AE4(void) {
    nofralloc
    b omOvlHisGet
}

asm void fn_801A8AE8(void) {
    nofralloc
    b omovlevtno
}

asm void fn_801A8AEC(void) {
    nofralloc
    b omovlstat
}

asm void fn_801A8AF0(void) {
    nofralloc
    b AddX
}

asm void fn_801A8AF4(void) {
    nofralloc
    b AddZ
}

asm void fn_801A8AF8(void) {
    nofralloc
    b MapObject
}

asm void fn_801A8AFC(void) {
    nofralloc
    b CharObject
}

asm void fn_801A8B00(void) {
    nofralloc
    b nMap
}

asm void fn_801A8B04(void) {
    nofralloc
    b nChar
}

asm void fn_801A8B08(void) {
    nofralloc
    b MapWall
}

asm void fn_801A8B0C(void) {
    nofralloc
    b MapPos
}

asm void fn_801A8B10(void) {
    nofralloc
    b HitFaceVec
}

asm void fn_801A8B14(void) {
    nofralloc
    b HitFace
}

asm void fn_801A8B18(void) {
    nofralloc
    b HitFaceCount
}

asm void fn_801A8B1C(void) {
    nofralloc
    b GwPlayer
}

asm void fn_801A8B20(void) {
    nofralloc
    b GwSystem
}

asm void fn_801A8B24(void) {
    nofralloc
    b HuTHPSprCreateVol
}

asm void fn_801A8B28(void) {
    nofralloc
    b HuTHPSprCreate
}

asm void fn_801A8B2C(void) {
    nofralloc
    b HuTHP3DCreateVol
}

asm void fn_801A8B30(void) {
    nofralloc
    b HuTHP3DCreate
}

asm void fn_801A8B34(void) {
    nofralloc
    b HuTHPStop
}

asm void fn_801A8B38(void) {
    nofralloc
    b HuTHPClose
}

asm void fn_801A8B3C(void) {
    nofralloc
    b HuTHPRestart
}

asm void fn_801A8B40(void) {
    nofralloc
    b HuTHPEndCheck
}

asm void fn_801A8B44(void) {
    nofralloc
    b HuTHPFrameGet
}

asm void fn_801A8B48(void) {
    nofralloc
    b HuTHPTotalFrameGet
}

asm void fn_801A8B4C(void) {
    nofralloc
    b HuTHPSetVolume
}

asm void fn_801A8B50(void) {
    nofralloc
    b THPSimpleGetFrameRate
}

asm void fn_801A8B54(void) {
    nofralloc
    b HuTHPMatHook
}

asm void fn_801A8B58(void) {
    nofralloc
    b HuTHPStartCheck
}

asm void fn_801A8B5C(void) {
    nofralloc
    b HuCardCheck
}

asm void fn_801A8B60(void) {
    nofralloc
    b HuCardMount
}

asm void fn_801A8B64(void) {
    nofralloc
    b HuCardFormat
}

asm void fn_801A8B68(void) {
    nofralloc
    b HuCardOpen
}

asm void fn_801A8B6C(void) {
    nofralloc
    b HuCardRead
}

asm void fn_801A8B70(void) {
    nofralloc
    b HuCardCreate
}

asm void fn_801A8B74(void) {
    nofralloc
    b HuCardClose
}

asm void fn_801A8B78(void) {
    nofralloc
    b HuCardWrite
}

asm void fn_801A8B7C(void) {
    nofralloc
    b HuCardDelete
}

asm void fn_801A8B80(void) {
    nofralloc
    b HuCardSectorSizeGet
}

asm void fn_801A8B84(void) {
    nofralloc
    b HuCardFreeSpaceGet
}

asm void fn_801A8B88(void) {
    nofralloc
    b HuCardSlotCheck
}

asm void fn_801A8B8C(void) {
    nofralloc
    b SLFileOpen
}

asm void fn_801A8B90(void) {
    nofralloc
    b SLFileCreate
}

asm void fn_801A8B94(void) {
    nofralloc
    b SLFileWrite
}

asm void fn_801A8B98(void) {
    nofralloc
    b SLFileClose
}

asm void fn_801A8B9C(void) {
    nofralloc
    b SLFileRead
}

asm void fn_801A8BA0(void) {
    nofralloc
    b SLSaveEmptyMark
}

asm void fn_801A8BA4(void) {
    nofralloc
    b SLCurSlotNoSet
}

asm void fn_801A8BA8(void) {
    nofralloc
    b SLCurSlotNoGet
}

asm void fn_801A8BAC(void) {
    nofralloc
    b SLSaveDataMake
}

asm void fn_801A8BB0(void) {
    nofralloc
    b SLSaveDataSlotMake
}

asm void fn_801A8BB4(void) {
    nofralloc
    b SLCommonSet
}

asm void fn_801A8BB8(void) {
    nofralloc
    b SLBoardSave
}

asm void fn_801A8BBC(void) {
    nofralloc
    b SLBoardSaveStory
}

asm void fn_801A8BC0(void) {
    nofralloc
    b SLSave
}

asm void fn_801A8BC4(void) {
    nofralloc
    b SLCommonLoad
}

asm void fn_801A8BC8(void) {
    nofralloc
    b SLBoardLoad
}

asm void fn_801A8BCC(void) {
    nofralloc
    b SLBoardLoadStory
}

asm void fn_801A8BD0(void) {
    nofralloc
    b SLLoad
}

asm void fn_801A8BD4(void) {
    nofralloc
    b SLCurBoxNoSet
}

asm void fn_801A8BD8(void) {
    nofralloc
    b SLCurBoxNoGet
}

asm void fn_801A8BDC(void) {
    nofralloc
    b SLSaveFlagSet
}

asm void fn_801A8BE0(void) {
    nofralloc
    b SLSaveFlagGet
}

asm void fn_801A8BE4(void) {
    nofralloc
    b SLCheckSumCheck
}

asm void fn_801A8BE8(void) {
    nofralloc
    b SLCheckSumBoxSlotCheck
}

asm void fn_801A8BEC(void) {
    nofralloc
    b SLCheckSumGet
}

asm void fn_801A8BF0(void) {
    nofralloc
    b SLCheckSumSlotGet
}

asm void fn_801A8BF4(void) {
    nofralloc
    b SLSerialNoGet
}

asm void fn_801A8BF8(void) {
    nofralloc
    b SLSerialNoCheck
}

asm void fn_801A8BFC(void) {
    nofralloc
    b saveExecF
}

asm void fn_801A8C00(void) {
    nofralloc
    b SLWinIdSet
}

asm void fn_801A8C04(void) {
    nofralloc
    b SLBoxBackupLoad
}

asm void fn_801A8C08(void) {
    nofralloc
    b SLBoxBackupSlotLoad
}

asm void fn_801A8C0C(void) {
    nofralloc
    b SLCheckSumBoxSet
}

asm void fn_801A8C10(void) {
    nofralloc
    b SLBoxDataOffsetGet
}

asm void fn_801A8C14(void) {
    nofralloc
    b SLSaveBoardTurnExec
}

asm void fn_801A8C18(void) {
    nofralloc
    b SLSaveBoardEndExec
}

asm void fn_801A8C1C(void) {
    nofralloc
    b SLSaveStoryExec
}

asm void fn_801A8C20(void) {
    nofralloc
    b SLSaveStaffExec
}

asm void fn_801A8C24(void) {
    nofralloc
    b SLSaveModeExec
}

asm void fn_801A8C28(void) {
    nofralloc
    b curSlotNo
}

asm void fn_801A8C2C(void) {
    nofralloc
    b UnMountCnt
}

asm void fn_801A8C30(void) {
    nofralloc
    b SLSdSave
}

asm void fn_801A8C34(void) {
    nofralloc
    b SLSdLoad
}

asm void fn_801A8C38(void) {
    nofralloc
    b SLCommonSaveCopy
}

asm void fn_801A8C3C(void) {
    nofralloc
    b SLCommonLoadCopy
}

asm void fn_801A8C40(void) {
    nofralloc
    b SLSaveSdExec
}

asm void fn_801A8C44(void) {
    nofralloc
    b _CheckFlag
}

asm void fn_801A8C48(void) {
    nofralloc
    b _SetFlag
}

asm void fn_801A8C4C(void) {
    nofralloc
    b _ClearFlag
}

asm void fn_801A8C50(void) {
    nofralloc
    b mgDataTbl
}

asm void fn_801A8C54(void) {
    nofralloc
    b mgMatchGameType
}

asm void fn_801A8C58(void) {
    nofralloc
    b sdHealthLoss
}

asm void fn_801A8C5C(void) {
    nofralloc
    b lbl_80288A30
}

asm void fn_801A8C60(void) {
    nofralloc
    b mgModeWork
}

asm void fn_801A8C64(void) {
    nofralloc
    b lbl_80288A30
}

asm void fn_801A8C68(void) {
    nofralloc
    b GwCommonBackup
}

asm void fn_801A8C6C(void) {
    nofralloc
    b lbl_80288A28
}

asm void fn_801A8C70(void) {
    nofralloc
    b mgExitStartF
}

asm void fn_801A8C74(void) {
    nofralloc
    b mgPauseExitF
}

asm void fn_801A8C78(void) {
    nofralloc
    b mgBoard2Force
}

asm void fn_801A8C7C(void) {
    nofralloc
    b MgNoGet
}

asm void fn_801A8C80(void) {
    nofralloc
    b m562CtrlNo
}

asm void fn_801A8C84(void) {
    nofralloc
    b mgSubMode
}

asm void fn_801A8C88(void) {
    nofralloc
    b MgSubModeGet
}

asm void fn_801A8C8C(void) {
    nofralloc
    b lbl_80288A2C
}

asm void fn_801A8C90(void) {
    nofralloc
    b MgDecaScoreCalc
}

asm void fn_801A8C94(void) {
    nofralloc
    b mgInstExitF
}

asm void fn_801A8C98(void) {
    nofralloc
    b GWMgRecordSet
}

asm void fn_801A8C9C(void) {
    nofralloc
    b GWMgRecordGet
}

asm void fn_801A8CA0(void) {
    nofralloc
    b GWPlayNumAdd
}

asm void fn_801A8CA4(void) {
    nofralloc
    b GWPlayNumSet
}

asm void fn_801A8CA8(void) {
    nofralloc
    b GWPlayNumGet
}

asm void fn_801A8CAC(void) {
    nofralloc
    b GWCharPlayNumInc
}

asm void fn_801A8CB0(void) {
    nofralloc
    b GWCharPlayNumGet
}

asm void fn_801A8CB4(void) {
    nofralloc
    b GWCharPlayNumSet
}

asm void fn_801A8CB8(void) {
    nofralloc
    b GWBoardMaxStarSet
}

asm void fn_801A8CBC(void) {
    nofralloc
    b GWBoardMaxStarGet
}

asm void fn_801A8CC0(void) {
    nofralloc
    b GWBoardMaxCoinSet
}

asm void fn_801A8CC4(void) {
    nofralloc
    b GWBoardMaxCoinGet
}

asm void fn_801A8CC8(void) {
    nofralloc
    b GWTotalStarSet
}

asm void fn_801A8CCC(void) {
    nofralloc
    b GWTotalStarAdd
}

asm void fn_801A8CD0(void) {
    nofralloc
    b GWTotalStarGet
}

asm void fn_801A8CD4(void) {
    nofralloc
    b GWPlayerStarAdd
}

asm void fn_801A8CD8(void) {
    nofralloc
    b GWPlayerStarGet
}

asm void fn_801A8CDC(void) {
    nofralloc
    b GWPlayerStarSet
}

asm void fn_801A8CE0(void) {
    nofralloc
    b GWPlayerCoinAdd
}

asm void fn_801A8CE4(void) {
    nofralloc
    b GWPlayerCoinSet
}

asm void fn_801A8CE8(void) {
    nofralloc
    b GWPlayerCoinGet
}

asm void fn_801A8CEC(void) {
    nofralloc
    b GWMgCustomReset
}

asm void fn_801A8CF0(void) {
    nofralloc
    b GWMgCustomSet
}

asm void fn_801A8CF4(void) {
    nofralloc
    b GWMgCustomGet
}

asm void fn_801A8CF8(void) {
    nofralloc
    b GWMgUnlockGet
}

asm void fn_801A8CFC(void) {
    nofralloc
    b GWSdCommonInit
}

asm void fn_801A8D00(void) {
    nofralloc
    b GWSaveCompleteSet
}

asm void fn_801A8D04(void) {
    nofralloc
    b sdWorkInt
}

asm void fn_801A8D08(void) {
    nofralloc
    b sdWorkFloat
}

// b GwSdCommon+0x148
asm void fn_801A8D0C(void) {
    nofralloc
    opword 0x4808263C
}

asm void fn_801A8D10(void) {
    nofralloc
    b GwSdBackupNo
}

asm void fn_801A8D14(void) {
    nofralloc
    b fmod
}

asm void fn_801A8D18(void) {
    nofralloc
    b _savegpr_15
}

asm void fn_801A8D1C(void) {
    nofralloc
    b _restgpr_15
}

asm void fn_801A8D20(void) {
    nofralloc
    b _savegpr_16
}

asm void fn_801A8D24(void) {
    nofralloc
    b _restgpr_16
}

asm void fn_801A8D28(void) {
    nofralloc
    b _savegpr_14
}

asm void fn_801A8D2C(void) {
    nofralloc
    b _restgpr_14
}

asm void fn_801A8D30(void) {
    nofralloc
    b lbl_80288888
}

asm void fn_801A8D34(void) {
    nofralloc
    b omDBGSystemKeyCheckSetup
}

asm void fn_801A8D38(void) {
    nofralloc
    b msmSeSetListener
}

asm void fn_801A8D3C(void) {
    nofralloc
    b msmSeUpdataListener
}

asm void fn_801A8D40(void) {
    nofralloc
    b msmSeGetIndexPtr
}

asm void fn_801A8D44(void) {
    nofralloc
    b msmMusSetMasterVolume
}

asm void fn_801A8D48(void) {
    nofralloc
    b msmSysGetOutputMode
}

asm void fn_801A8D4C(void) {
    nofralloc
    b msmSysSetGroupLoadMode
}

asm void fn_801A8D50(void) {
    nofralloc
    b WipeCreate
}

asm void fn_801A8D54(void) {
    nofralloc
    b WipeColorSet
}

asm void fn_801A8D58(void) {
    nofralloc
    b omOvlReturnEx
}

asm void fn_801A8D5C(void) {
    nofralloc
    b HuDataGetAsyncStat
}

asm void fn_801A8D60(void) {
    nofralloc
    b omVibrate
}

asm void fn_801A8D64(void) {
    nofralloc
    b GameMesOvlPrev
}

asm void fn_801A8D68(void) {
    nofralloc
    b MgTimerCreate
}

asm void fn_801A8D6C(void) {
    nofralloc
    b MgTimerKill
}

asm void fn_801A8D70(void) {
    nofralloc
    b MgTimerModeGet
}

asm void fn_801A8D74(void) {
    nofralloc
    b MgTimerModeOnSet
}

asm void fn_801A8D78(void) {
    nofralloc
    b MgTimerModeOffSet
}

asm void fn_801A8D7C(void) {
    nofralloc
    b MgTimerParamSet
}

asm void fn_801A8D80(void) {
    nofralloc
    b MgTimerValueGet
}

asm void fn_801A8D84(void) {
    nofralloc
    b MgTimerDoneCheck
}

asm void fn_801A8D88(void) {
    nofralloc
    b MgTimerPosSet
}

asm void fn_801A8D8C(void) {
    nofralloc
    b MgTimerPosGet
}

asm void fn_801A8D90(void) {
    nofralloc
    b MgTimerWinColorSet
}

asm void fn_801A8D94(void) {
    nofralloc
    b MgTimerDigitColorSet
}

asm void fn_801A8D98(void) {
    nofralloc
    b MgTimerRecordSet
}

asm void fn_801A8D9C(void) {
    nofralloc
    b MgTimerRecordDispOn
}

asm void fn_801A8DA0(void) {
    nofralloc
    b MgTimerRecordDispOff
}

asm void fn_801A8DA4(void) {
    nofralloc
    b MgScoreInit
}

asm void fn_801A8DA8(void) {
    nofralloc
    b MgScoreKill
}

asm void fn_801A8DAC(void) {
    nofralloc
    b MgScoreModeGet
}

asm void fn_801A8DB0(void) {
    nofralloc
    b MgScoreValueSet
}

asm void fn_801A8DB4(void) {
    nofralloc
    b MgScoreValueGet
}

asm void fn_801A8DB8(void) {
    nofralloc
    b MgScoreMaxDigitSet
}

asm void fn_801A8DBC(void) {
    nofralloc
    b MgScoreMaxDigitGet
}

asm void fn_801A8DC0(void) {
    nofralloc
    b MgScorePosSet
}

asm void fn_801A8DC4(void) {
    nofralloc
    b MgScorePosGet
}

asm void fn_801A8DC8(void) {
    nofralloc
    b MgScoreScaleSet
}

asm void fn_801A8DCC(void) {
    nofralloc
    b MgScoreScaleGet
}

asm void fn_801A8DD0(void) {
    nofralloc
    b MgScoreZRotSet
}

asm void fn_801A8DD4(void) {
    nofralloc
    b MgScoreZRotGet
}

asm void fn_801A8DD8(void) {
    nofralloc
    b MgScoreDigitWidthSet
}

asm void fn_801A8DDC(void) {
    nofralloc
    b MgScoreDigitWidthGet
}

asm void fn_801A8DE0(void) {
    nofralloc
    b MgScoreDispOn
}

asm void fn_801A8DE4(void) {
    nofralloc
    b MgScoreDispOff
}

asm void fn_801A8DE8(void) {
    nofralloc
    b MgScoreTPLvlSet
}

asm void fn_801A8DEC(void) {
    nofralloc
    b MgScoreTPLvlGet
}

asm void fn_801A8DF0(void) {
    nofralloc
    b MgScoreModeDefaultSet
}

asm void fn_801A8DF4(void) {
    nofralloc
    b MgScoreCreate
}

asm void fn_801A8DF8(void) {
    nofralloc
    b MgScoreColorSet
}

asm void fn_801A8DFC(void) {
    nofralloc
    b MgScoreDigitScaleSet
}

asm void fn_801A8E00(void) {
    nofralloc
    b MgScorePriSet
}

asm void fn_801A8E04(void) {
    nofralloc
    b MgSeqCreate
}

asm void fn_801A8E08(void) {
    nofralloc
    b MgSeqCreatePrio
}

asm void fn_801A8E0C(void) {
    nofralloc
    b MgSeqKill
}

asm void fn_801A8E10(void) {
    nofralloc
    b MgSeqModeGet
}

asm void fn_801A8E14(void) {
    nofralloc
    b MgSeqModeNext
}

asm void fn_801A8E18(void) {
    nofralloc
    b MgSeqModeSet
}

asm void fn_801A8E1C(void) {
    nofralloc
    b MgSeqRecordSet
}

asm void fn_801A8E20(void) {
    nofralloc
    b MgSeqModeChangeOff
}

asm void fn_801A8E24(void) {
    nofralloc
    b MgSeqModeChangeOn
}

asm void fn_801A8E28(void) {
    nofralloc
    b MgSeqStatGet
}

asm void fn_801A8E2C(void) {
    nofralloc
    b MgSeqWinnerSet
}

asm void fn_801A8E30(void) {
    nofralloc
    b MgSeqDrawSet
}

asm void fn_801A8E34(void) {
    nofralloc
    b fn_8006C2E0
}

asm void fn_801A8E38(void) {
    nofralloc
    b MgSeqModeDelaySet
}

asm void fn_801A8E3C(void) {
    nofralloc
    b MgSeqModeHookAdd
}

asm void fn_801A8E40(void) {
    nofralloc
    b MgSeqModeHookReset
}

asm void fn_801A8E44(void) {
    nofralloc
    b MgSeqTimerValueGet
}

asm void fn_801A8E48(void) {
    nofralloc
    b MgSeqFrameNoGet
}

asm void fn_801A8E4C(void) {
    nofralloc
    b MgSeqGameMesIdGet
}

asm void fn_801A8E50(void) {
    nofralloc
    b MgSeqMaxTimeSet
}

asm void fn_801A8E54(void) {
    nofralloc
    b MgSeqStatBitSet
}

asm void fn_801A8E58(void) {
    nofralloc
    b MgSeqStatBitReset
}

asm void fn_801A8E5C(void) {
    nofralloc
    b omCameraViewInit
}

asm void fn_801A8E60(void) {
    nofralloc
    b omCameraViewSetMulti
}

asm void fn_801A8E64(void) {
    nofralloc
    b omCameraViewSet
}

asm void fn_801A8E68(void) {
    nofralloc
    b omCameraViewMoveSimpleMulti
}

asm void fn_801A8E6C(void) {
    nofralloc
    b omCameraViewMoveSimple
}

asm void fn_801A8E70(void) {
    nofralloc
    b omCameraViewMoveMulti
}

asm void fn_801A8E74(void) {
    nofralloc
    b omCameraViewMove
}

asm void fn_801A8E78(void) {
    nofralloc
    b omCameraViewCheck
}

asm void fn_801A8E7C(void) {
    nofralloc
    b MgActorObjectSetup
}

asm void fn_801A8E80(void) {
    nofralloc
    b MgActorColMapInit
}

asm void fn_801A8E84(void) {
    nofralloc
    b MgPlayerPadSet
}

asm void fn_801A8E88(void) {
    nofralloc
    b MgPlayerModeFuncSet
}

asm void fn_801A8E8C(void) {
    nofralloc
    b MgPlayerCreate
}

asm void fn_801A8E90(void) {
    nofralloc
    b MgPlayerCreateJumpAlt
}

asm void fn_801A8E94(void) {
    nofralloc
    b MgActorCreate
}

asm void fn_801A8E98(void) {
    nofralloc
    b MgActorKill
}

asm void fn_801A8E9C(void) {
    nofralloc
    b MgActorExec
}

asm void fn_801A8EA0(void) {
    nofralloc
    b MgPlayerModeLandSet
}

asm void fn_801A8EA4(void) {
    nofralloc
    b MgPlayerModeSet
}

asm void fn_801A8EA8(void) {
    nofralloc
    b MgPlayerComStkOn
}

asm void fn_801A8EAC(void) {
    nofralloc
    b MgPlayerComStkOff
}

asm void fn_801A8EB0(void) {
    nofralloc
    b MgPlayerVecChase
}

asm void fn_801A8EB4(void) {
    nofralloc
    b MgActorVecChase
}

asm void fn_801A8EB8(void) {
    nofralloc
    b MgActorColAttrSet
}

asm void fn_801A8EBC(void) {
    nofralloc
    b MgActorColAttrReset
}

asm void fn_801A8EC0(void) {
    nofralloc
    b MgActorColAttrGet
}

asm void fn_801A8EC4(void) {
    nofralloc
    b MgActorColMapPolyGet
}

asm void fn_801A8EC8(void) {
    nofralloc
    b MgActorPosUpdate
}

asm void fn_801A8ECC(void) {
    nofralloc
    b MgActorPosSet
}

asm void fn_801A8ED0(void) {
    nofralloc
    b MgActorPosGet
}

asm void fn_801A8ED4(void) {
    nofralloc
    b MgPlayerPauseOn
}

asm void fn_801A8ED8(void) {
    nofralloc
    b MgPlayerPauseOff
}

asm void fn_801A8EDC(void) {
    nofralloc
    b MgActorPauseOn
}

asm void fn_801A8EE0(void) {
    nofralloc
    b MgActorPauseOff
}

asm void fn_801A8EE4(void) {
    nofralloc
    b MgPlayerVibrateCreate
}

asm void fn_801A8EE8(void) {
    nofralloc
    b MgPlayerVibrateKill
}

asm void fn_801A8EEC(void) {
    nofralloc
    b MgActorColAttrParamSet
}

asm void fn_801A8EF0(void) {
    nofralloc
    b MgActorColAttrParamGet
}

asm void fn_801A8EF4(void) {
    nofralloc
    b MgActorColMapMaskSet
}

asm void fn_801A8EF8(void) {
    nofralloc
    b MgActorColMapMaskGet
}

asm void fn_801A8EFC(void) {
    nofralloc
    b MgActorColMaskSet
}

asm void fn_801A8F00(void) {
    nofralloc
    b MgActorColMaskGet
}

asm void fn_801A8F04(void) {
    nofralloc
    b MgPlayerAttrCheck
}

asm void fn_801A8F08(void) {
    nofralloc
    b MgPlayerAttrSet
}

asm void fn_801A8F0C(void) {
    nofralloc
    b MgPlayerAttrReset
}

asm void fn_801A8F10(void) {
    nofralloc
    b MgPlayerModeAttrCheck
}

asm void fn_801A8F14(void) {
    nofralloc
    b MgPlayerModeAttrReset
}

asm void fn_801A8F18(void) {
    nofralloc
    b MgPlayerModeAttrSet
}

asm void fn_801A8F1C(void) {
    nofralloc
    b MgPlayerVibAttrCheck
}

asm void fn_801A8F20(void) {
    nofralloc
    b MgPlayerVibAttrSet
}

asm void fn_801A8F24(void) {
    nofralloc
    b MgPlayerStunSet
}

asm void fn_801A8F28(void) {
    nofralloc
    b MgActorColCylReset
}

asm void fn_801A8F2C(void) {
    nofralloc
    b MgActorColCylSet
}

asm void fn_801A8F30(void) {
    nofralloc
    b CharModelFileNumGet
}

asm void fn_801A8F34(void) {
    nofralloc
    b CharMotionFileNumGet
}

asm void fn_801A8F38(void) {
    nofralloc
    b lbl_80288138
}

asm void fn_801A8F3C(void) {
    nofralloc
    b lbl_8028813C
}

asm void fn_801A8F40(void) {
    nofralloc
    b lbl_80288140
}

asm void fn_801A8F44(void) {
    nofralloc
    b _savefpr_22
}

asm void fn_801A8F48(void) {
    nofralloc
    b _restfpr_22
}

asm void fn_801A8F4C(void) {
    nofralloc
    b _savefpr_24
}

asm void fn_801A8F50(void) {
    nofralloc
    b _restfpr_24
}

asm void fn_801A8F54(void) {
    nofralloc
    b _savefpr_27
}

asm void fn_801A8F58(void) {
    nofralloc
    b _restfpr_27
}

asm void fn_801A8F5C(void) {
    nofralloc
    b _savefpr_28
}

asm void fn_801A8F60(void) {
    nofralloc
    b _restfpr_28
}

asm void fn_801A8F64(void) {
    nofralloc
    b __construct_array
}

asm void fn_801A8F68(void) {
    nofralloc
    b __destroy_arr
}

asm void fn_801A8F6C(void) {
    nofralloc
    b HuDataDirCancelAsync
}

asm void fn_801A8F70(void) {
    nofralloc
    b HuDataDirCloseAsync
}

asm void fn_801A8F74(void) {
    nofralloc
    b HuTHPProcCheck
}

asm void fn_801A8F78(void) {
    nofralloc
    b MBPartySaveInit
}

asm void fn_801A8F7C(void) {
    nofralloc
    b MBPlayerSaveInit
}

asm void fn_801A8F80(void) {
    nofralloc
    b MBStorySaveInit
}

asm void fn_801A8F84(void) {
    nofralloc
    b fn_801A7E90
}

asm void fn_801A8F88(void) {
    nofralloc
    b fn_801A7F78
}

asm void fn_801A8F8C(void) {
    nofralloc
    b MBBranchInit
}

asm void fn_801A8F90(void) {
    nofralloc
    b MBBranchExec
}

asm void fn_801A8F94(void) {
    nofralloc
    b MBBranchExecDebug
}

asm void fn_801A8F98(void) {
    nofralloc
    b MBBranchFlagSet
}

asm void fn_801A8F9C(void) {
    nofralloc
    b MBBranchFlagReset
}

asm void fn_801A8FA0(void) {
    nofralloc
    b MBBranchFlagInit
}

asm void fn_801A8FA4(void) {
    nofralloc
    b MBBranchFlagGet
}

asm void fn_801A8FA8(void) {
    nofralloc
    b MBCameraCreate
}

asm void fn_801A8FAC(void) {
    nofralloc
    b MBCameraZoomSet
}

asm void fn_801A8FB0(void) {
    nofralloc
    b MBCameraZoomGet
}

asm void fn_801A8FB4(void) {
    nofralloc
    b MBCameraRotSetV
}

asm void fn_801A8FB8(void) {
    nofralloc
    b MBCameraRotSet
}

asm void fn_801A8FBC(void) {
    nofralloc
    b MBCameraRotGet
}

asm void fn_801A8FC0(void) {
    nofralloc
    b MBCameraPosTargetSetV
}

asm void fn_801A8FC4(void) {
    nofralloc
    b MBCameraPosTargetSet
}

asm void fn_801A8FC8(void) {
    nofralloc
    b MBCameraPosTargetGet
}

asm void fn_801A8FCC(void) {
    nofralloc
    b MBCameraPosSetV
}

asm void fn_801A8FD0(void) {
    nofralloc
    b MBCameraPosSet
}

asm void fn_801A8FD4(void) {
    nofralloc
    b MBCameraPosGet
}

asm void fn_801A8FD8(void) {
    nofralloc
    b MBCameraOffsetSetV
}

asm void fn_801A8FDC(void) {
    nofralloc
    b MBCameraOffsetSet
}

asm void fn_801A8FE0(void) {
    nofralloc
    b MBCameraOffsetGet
}

asm void fn_801A8FE4(void) {
    nofralloc
    b MBCameraDirGet
}

asm void fn_801A8FE8(void) {
    nofralloc
    b MBCameraPosDirGet
}

asm void fn_801A8FEC(void) {
    nofralloc
    b MBCameraPosHookSet
}

asm void fn_801A8FF0(void) {
    nofralloc
    b MBCameraBitSet
}

asm void fn_801A8FF4(void) {
    nofralloc
    b MBCameraFovSet
}

asm void fn_801A8FF8(void) {
    nofralloc
    b MBCameraScissorSet
}

asm void fn_801A8FFC(void) {
    nofralloc
    b MBCameraNearFarSet
}

asm void fn_801A9000(void) {
    nofralloc
    b MBCameraNearFarGet
}

asm void fn_801A9004(void) {
    nofralloc
    b MBCameraMotionEnd
}

asm void fn_801A9008(void) {
    nofralloc
    b MBCameraGet
}

asm void fn_801A900C(void) {
    nofralloc
    b MBCameraPush
}

asm void fn_801A9010(void) {
    nofralloc
    b MBCameraPop
}

asm void fn_801A9014(void) {
    nofralloc
    b MBCameraViewNoSet
}

asm void fn_801A9018(void) {
    nofralloc
    b MBCameraSkipSet
}

asm void fn_801A901C(void) {
    nofralloc
    b MBCameraSpeedSet
}

asm void fn_801A9020(void) {
    nofralloc
    b MBCameraFocusPlayerAdd
}

asm void fn_801A9024(void) {
    nofralloc
    b MBCameraFocusPlayerSet
}

asm void fn_801A9028(void) {
    nofralloc
    b MBCameraFocusAdd
}

asm void fn_801A902C(void) {
    nofralloc
    b MBCameraFocusSet
}

asm void fn_801A9030(void) {
    nofralloc
    b MBCameraFocusMasuAdd
}

asm void fn_801A9034(void) {
    nofralloc
    b MBCameraFocusMasuSet
}

asm void fn_801A9038(void) {
    nofralloc
    b MBCameraPosViewSet
}

asm void fn_801A903C(void) {
    nofralloc
    b MBCameraPlayerViewSet
}

asm void fn_801A9040(void) {
    nofralloc
    b MBCameraModelViewSet
}

asm void fn_801A9044(void) {
    nofralloc
    b MBCameraMasuViewSet
}

asm void fn_801A9048(void) {
    nofralloc
    b MBCameraCullCheck
}

asm void fn_801A904C(void) {
    nofralloc
    b MBCameraQuakeSet
}

asm void fn_801A9050(void) {
    nofralloc
    b MBCameraQuakeReset
}

asm void fn_801A9054(void) {
    nofralloc
    b MBCameraMotionCheck
}

asm void fn_801A9058(void) {
    nofralloc
    b MBCameraMotionWait
}

asm void fn_801A905C(void) {
    nofralloc
    b MBCameraViewGet
}

asm void fn_801A9060(void) {
    nofralloc
    b MBCameraLookAtGet
}

asm void fn_801A9064(void) {
    nofralloc
    b MBCameraLookAtGetInv
}

asm void fn_801A9068(void) {
    nofralloc
    b MBCameraFocusPlayerAddAll
}

asm void fn_801A906C(void) {
    nofralloc
    b MBCameraMaxTimeSet
}

asm void fn_801A9070(void) {
    nofralloc
    b MBCameraViewNoGet
}

asm void fn_801A9074(void) {
    nofralloc
    b MBCameraModelKeySet
}

asm void fn_801A9078(void) {
    nofralloc
    b MBCameraPointFocusSet
}

asm void fn_801A907C(void) {
    nofralloc
    b MBCapsuleSelExec
}

asm void fn_801A9080(void) {
    nofralloc
    b MBCapMachineExec
}

asm void fn_801A9084(void) {
    nofralloc
    b MBCapMachineInit
}

asm void fn_801A9088(void) {
    nofralloc
    b MBCapMachineClose
}

asm void fn_801A908C(void) {
    nofralloc
    b MBCapMachineCreateAll
}

asm void fn_801A9090(void) {
    nofralloc
    b MBCapMachineObjCreate
}

asm void fn_801A9094(void) {
    nofralloc
    b MBCapsuleSelStoryExec
}

asm void fn_801A9098(void) {
    nofralloc
    b MBCapsuleAddStory
}

asm void fn_801A909C(void) {
    nofralloc
    b MBCapMachineTutorialExec
}

asm void fn_801A90A0(void) {
    nofralloc
    b MBCapsuleSelModelUpdate
}

asm void fn_801A90A4(void) {
    nofralloc
    b MBCapsuleExec
}

asm void fn_801A90A8(void) {
    nofralloc
    b MBCapsuleNoGet
}

asm void fn_801A90AC(void) {
    nofralloc
    b MBSaiHiddenExec
}

asm void fn_801A90B0(void) {
    nofralloc
    b MBKettouExec
}

asm void fn_801A90B4(void) {
    nofralloc
    b MBCircuitKettouExec
}

asm void fn_801A90B8(void) {
    nofralloc
    b MBCapsuleKupaGetExec
}

asm void fn_801A90BC(void) {
    nofralloc
    b MB3MiracleGetExec
}

asm void fn_801A90C0(void) {
    nofralloc
    b MBDonkeyOpeningExec
}

asm void fn_801A90C4(void) {
    nofralloc
    b MBDonkeyExec
}

asm void fn_801A90C8(void) {
    nofralloc
    b MBKupaExec
}

asm void fn_801A90CC(void) {
    nofralloc
    b MBCircuitKupaExec
}

asm void fn_801A90D0(void) {
    nofralloc
    b MBLast5Exec
}

asm void fn_801A90D4(void) {
    nofralloc
    b MBGameEndExec
}

asm void fn_801A90D8(void) {
    nofralloc
    b MBVsMgExec
}

asm void fn_801A90DC(void) {
    nofralloc
    b MBKettouMgEndExec
}

asm void fn_801A90E0(void) {
    nofralloc
    b MBCircuitKettouMgEndExec
}

asm void fn_801A90E4(void) {
    nofralloc
    b MBDonkeyMgEndExec
}

asm void fn_801A90E8(void) {
    nofralloc
    b MBKupaMgEndExec
}

asm void fn_801A90EC(void) {
    nofralloc
    b MBCircuitKupaMgEndExec
}

asm void fn_801A90F0(void) {
    nofralloc
    b MBVsMgEndExec
}

asm void fn_801A90F4(void) {
    nofralloc
    b MBKillerExec
}

asm void fn_801A90F8(void) {
    nofralloc
    b MBKillerMultiExec
}

asm void fn_801A90FC(void) {
    nofralloc
    b MBKillerEventExec
}

asm void fn_801A9100(void) {
    nofralloc
    b MBKillerEventCheck
}

asm void fn_801A9104(void) {
    nofralloc
    b MBKillerEventCheckAll
}

asm void fn_801A9108(void) {
    nofralloc
    b MBBankCoinReset
}

asm void fn_801A910C(void) {
    nofralloc
    b MBMasuBomheiSet
}

asm void fn_801A9110(void) {
    nofralloc
    b MBCapsuleDonkeyAddRandom
}

asm void fn_801A9114(void) {
    nofralloc
    b MBCapsuleDonkeyAdd
}

asm void fn_801A9118(void) {
    nofralloc
    b MBCapsuleOpeningAdd
}

asm void fn_801A911C(void) {
    nofralloc
    b MBCapsuleBowserAdd
}

asm void fn_801A9120(void) {
    nofralloc
    b MBBankCoinGet
}

asm void fn_801A9124(void) {
    nofralloc
    b MBCapsuleEffHookSet
}

asm void fn_801A9128(void) {
    nofralloc
    b MBCapsuleEffHookCall
}

asm void fn_801A912C(void) {
    nofralloc
    b MBCapsuleEffHookStoryCall
}

asm void fn_801A9130(void) {
    nofralloc
    b MBKettouCoinLoseGet
}

asm void fn_801A9134(void) {
    nofralloc
    b MBKettouOppCoinLoseGet
}

asm void fn_801A9138(void) {
    nofralloc
    b MBKettouCoinLoseGet2
}

asm void fn_801A913C(void) {
    nofralloc
    b MBKettouOppCoinLoseGet2
}

asm void fn_801A9140(void) {
    nofralloc
    b MBCapsuleUseExec
}

asm void fn_801A9144(void) {
    nofralloc
    b MBCapsuleStub
}

asm void fn_801A9148(void) {
    nofralloc
    b MBCapsuleStub0
}

asm void fn_801A914C(void) {
    nofralloc
    b MBCapsuleThrowStart
}

asm void fn_801A9150(void) {
    nofralloc
    b MBCapsuleThrowCheck
}

asm void fn_801A9154(void) {
    nofralloc
    b MBCapsuleColCreate
}

asm void fn_801A9158(void) {
    nofralloc
    b MBCapsuleColCheck
}

asm void fn_801A915C(void) {
    nofralloc
    b MBCapsuleThrowAutoExec
}

asm void fn_801A9160(void) {
    nofralloc
    b MBCapsuleThrowAutoCheck
}

asm void fn_801A9164(void) {
    nofralloc
    b MBCapsulePosSelStart
}

asm void fn_801A9168(void) {
    nofralloc
    b MBCapsulePosSelCheck
}

asm void fn_801A916C(void) {
    nofralloc
    b MBCapsulePosSelResultGet
}

asm void fn_801A9170(void) {
    nofralloc
    b MBCapsulePosSetExec
}

asm void fn_801A9174(void) {
    nofralloc
    b MBCapsuleMasuSet
}

asm void fn_801A9178(void) {
    nofralloc
    b MBCapsuleMdlGet
}

asm void fn_801A917C(void) {
    nofralloc
    b MBCapsuleMesGet
}

asm void fn_801A9180(void) {
    nofralloc
    b MBCapsuleMasuPatNoGet
}

asm void fn_801A9184(void) {
    nofralloc
    b MBCapsuleColorNoGet
}

asm void fn_801A9188(void) {
    nofralloc
    b MBCapsuleCostGet
}

asm void fn_801A918C(void) {
    nofralloc
    b MBCapsuleNoUseCheck
}

asm void fn_801A9190(void) {
    nofralloc
    b MBCapsuleListGet
}

asm void fn_801A9194(void) {
    nofralloc
    b MBCapsuleNextGet
}

asm void fn_801A9198(void) {
    nofralloc
    b MBComCapsuleSelGet
}

asm void fn_801A919C(void) {
    nofralloc
    b MBCapsulePosAutoSelCheck
}

asm void fn_801A91A0(void) {
    nofralloc
    b MBCapsuleCodeGet
}

asm void fn_801A91A4(void) {
    nofralloc
    b MBCapsuleWinCreate
}

asm void fn_801A91A8(void) {
    nofralloc
    b MBCapsuleObjInit
}

asm void fn_801A91AC(void) {
    nofralloc
    b MBCapsuleObjCreate
}

asm void fn_801A91B0(void) {
    nofralloc
    b MBCapsuleObjKill
}

asm void fn_801A91B4(void) {
    nofralloc
    b MBCapsuleObjPosSet
}

asm void fn_801A91B8(void) {
    nofralloc
    b MBCapsuleObjRotSet
}

asm void fn_801A91BC(void) {
    nofralloc
    b MBCapsuleObjScaleSet
}

asm void fn_801A91C0(void) {
    nofralloc
    b MBCapsuleObjPosSetV
}

asm void fn_801A91C4(void) {
    nofralloc
    b MBCapsuleObjRotSetV
}

asm void fn_801A91C8(void) {
    nofralloc
    b MBCapsuleObjScaleSetV
}

asm void fn_801A91CC(void) {
    nofralloc
    b MBCapsuleObjPosGet
}

asm void fn_801A91D0(void) {
    nofralloc
    b MBCapsuleObjRotGet
}

asm void fn_801A91D4(void) {
    nofralloc
    b MBCapsuleObjScaleGet
}

asm void fn_801A91D8(void) {
    nofralloc
    b MBCapsuleObjLayerSet
}

asm void fn_801A91DC(void) {
    nofralloc
    b MBCapsuleObjLayerGet
}

asm void fn_801A91E0(void) {
    nofralloc
    b MBCapsuleObjAttrSet
}

asm void fn_801A91E4(void) {
    nofralloc
    b MBCapsuleObjAttrReset
}

asm void fn_801A91E8(void) {
    nofralloc
    b MBCapsuleObjDispSet
}

asm void fn_801A91EC(void) {
    nofralloc
    b MBCapsuleObjAlphaSet
}

asm void fn_801A91F0(void) {
    nofralloc
    b MBCapsuleObjMtxSet
}

asm void fn_801A91F4(void) {
    nofralloc
    b MBCapsuleObjMtxGet
}

asm void fn_801A91F8(void) {
    nofralloc
    b MBCoinInit
}

asm void fn_801A91FC(void) {
    nofralloc
    b MBCoinClose
}

asm void fn_801A9200(void) {
    nofralloc
    b MBCoinEffGet
}

asm void fn_801A9204(void) {
    nofralloc
    b MBCoinEffCreate
}

asm void fn_801A9208(void) {
    nofralloc
    b MBCoinEffKill
}

asm void fn_801A920C(void) {
    nofralloc
    b MBCoinEffCheck
}

asm void fn_801A9210(void) {
    nofralloc
    b MBCoinPosSetV
}

asm void fn_801A9214(void) {
    nofralloc
    b MBCoinPosSet
}

asm void fn_801A9218(void) {
    nofralloc
    b MBCoinPosGet
}

asm void fn_801A921C(void) {
    nofralloc
    b MBCoinRotSetV
}

asm void fn_801A9220(void) {
    nofralloc
    b MBCoinRotSet
}

asm void fn_801A9224(void) {
    nofralloc
    b MBCoinRotGet
}

asm void fn_801A9228(void) {
    nofralloc
    b MBCoinScaleSetV
}

asm void fn_801A922C(void) {
    nofralloc
    b MBCoinScaleSet
}

asm void fn_801A9230(void) {
    nofralloc
    b MBCoinScaleGet
}

asm void fn_801A9234(void) {
    nofralloc
    b MBCoinEffAttrSet
}

asm void fn_801A9238(void) {
    nofralloc
    b MBCoinEffAttrReset
}

asm void fn_801A923C(void) {
    nofralloc
    b MBCoinHitExec
}

asm void fn_801A9240(void) {
    nofralloc
    b MBCoinParManCreate
}

asm void fn_801A9244(void) {
    nofralloc
    b MBCoinParManKill
}

asm void fn_801A9248(void) {
    nofralloc
    b MBCoinDispKill
}

asm void fn_801A924C(void) {
    nofralloc
    b MBCoinDispKillCheck
}

asm void fn_801A9250(void) {
    nofralloc
    b MBCoinDispCreateSe
}

asm void fn_801A9254(void) {
    nofralloc
    b MBCoinDispCreate
}

asm void fn_801A9258(void) {
    nofralloc
    b MBCoinAddProcExec
}

asm void fn_801A925C(void) {
    nofralloc
    b MBCoinAddDispExec
}

asm void fn_801A9260(void) {
    nofralloc
    b MBCoinAddExec
}

asm void fn_801A9264(void) {
    nofralloc
    b MBCoinAddAllProcExec
}

asm void fn_801A9268(void) {
    nofralloc
    b MBCoinAddAllDispExec
}

asm void fn_801A926C(void) {
    nofralloc
    b MBCoinAddAllExec
}

asm void fn_801A9270(void) {
    nofralloc
    b MBComChoiceSetLeft
}

asm void fn_801A9274(void) {
    nofralloc
    b MBComChoiceSetUp
}

asm void fn_801A9278(void) {
    nofralloc
    b MBComChoiceSetRight
}

asm void fn_801A927C(void) {
    nofralloc
    b MBComChoiceSetDown
}

asm void fn_801A9280(void) {
    nofralloc
    b MBComMasuPathNoGet
}

asm void fn_801A9284(void) {
    nofralloc
    b MBPauseOptionExec
}

asm void fn_801A9288(void) {
    nofralloc
    b MBPauseDispCopyKill
}

asm void fn_801A928C(void) {
    nofralloc
    b MBPauseDispCopyCreate
}

asm void fn_801A9290(void) {
    nofralloc
    b MBPadDStkRepGetAll
}

asm void fn_801A9294(void) {
    nofralloc
    b MBPadBtnDownGetAll
}

asm void fn_801A9298(void) {
    nofralloc
    b MBOpeningExec
}

asm void fn_801A929C(void) {
    nofralloc
    b MBStoryOpeningExec
}

asm void fn_801A92A0(void) {
    nofralloc
    b MBStoryEndProcExec
}

asm void fn_801A92A4(void) {
    nofralloc
    b MBSaiInit
}

asm void fn_801A92A8(void) {
    nofralloc
    b MBSaiPlayerExec
}

asm void fn_801A92AC(void) {
    nofralloc
    b MBSaiExec
}

asm void fn_801A92B0(void) {
    nofralloc
    b MBSaiTutorialExec
}

asm void fn_801A92B4(void) {
    nofralloc
    b MBSaiChanceTradeExec
}

asm void fn_801A92B8(void) {
    nofralloc
    b MBSaiChanceCharExec
}

asm void fn_801A92BC(void) {
    nofralloc
    b MBSaiKill
}

asm void fn_801A92C0(void) {
    nofralloc
    b MBSaiClose
}

asm void fn_801A92C4(void) {
    nofralloc
    b MBSaiKillCheck
}

asm void fn_801A92C8(void) {
    nofralloc
    b MBSaiKillCheckAll
}

asm void fn_801A92CC(void) {
    nofralloc
    b MBSaiResultGet
}

asm void fn_801A92D0(void) {
    nofralloc
    b MBSaiHitHookSet
}

asm void fn_801A92D4(void) {
    nofralloc
    b MBSaiNumKill
}

asm void fn_801A92D8(void) {
    nofralloc
    b MBSaiNumShrinkSet
}

asm void fn_801A92DC(void) {
    nofralloc
    b MBSaiNumStopCheck
}

asm void fn_801A92E0(void) {
    nofralloc
    b MBSaiStub
}

asm void fn_801A92E4(void) {
    nofralloc
    b MBSaiNumObjCreate
}

asm void fn_801A92E8(void) {
    nofralloc
    b MBSaiPadBtnHookSet
}

asm void fn_801A92EC(void) {
    nofralloc
    b MBSaiMotHookSet
}

asm void fn_801A92F0(void) {
    nofralloc
    b MBEffConfettiCreate
}

asm void fn_801A92F4(void) {
    nofralloc
    b MBEffConfettiKill
}

asm void fn_801A92F8(void) {
    nofralloc
    b MBEffConfettiReset
}

asm void fn_801A92FC(void) {
    nofralloc
    b MBEffFadeOutSet
}

asm void fn_801A9300(void) {
    nofralloc
    b MBEffFadeCreate
}

asm void fn_801A9304(void) {
    nofralloc
    b MBEffFadeDoneCheck
}

asm void fn_801A9308(void) {
    nofralloc
    b MBEffFadeCheck
}

asm void fn_801A930C(void) {
    nofralloc
    b MBEffFadeCameraSet
}

asm void fn_801A9310(void) {
    nofralloc
    b MBEffCreate
}

asm void fn_801A9314(void) {
    nofralloc
    b MBEffKill
}

asm void fn_801A9318(void) {
    nofralloc
    b MBEffHookSet
}

asm void fn_801A931C(void) {
    nofralloc
    b MBEffAttrSet
}

asm void fn_801A9320(void) {
    nofralloc
    b MBEffAttrReset
}

asm void fn_801A9324(void) {
    nofralloc
    b MBEffUnkTotalGet
}

asm void fn_801A9328(void) {
    nofralloc
    b MBEffDataCreate
}

asm void fn_801A932C(void) {
    nofralloc
    b MBGateInit
}

asm void fn_801A9330(void) {
    nofralloc
    b MBGateClose
}

asm void fn_801A9334(void) {
    nofralloc
    b MBGateCreate
}

asm void fn_801A9338(void) {
    nofralloc
    b MBGateMasuExec
}

asm void fn_801A933C(void) {
    nofralloc
    b MBGateBattanSearch
}

asm void fn_801A9340(void) {
    nofralloc
    b MBGateBattanExec
}

asm void fn_801A9344(void) {
    nofralloc
    b MBGateBattanKill
}

asm void fn_801A9348(void) {
    nofralloc
    b MBGateDossunKill
}

asm void fn_801A934C(void) {
    nofralloc
    b MBGateDossunSearch
}

asm void fn_801A9350(void) {
    nofralloc
    b MBGuideInit
}

asm void fn_801A9354(void) {
    nofralloc
    b MBGuideCreateIn
}

asm void fn_801A9358(void) {
    nofralloc
    b MBGuideCreateDirect
}

asm void fn_801A935C(void) {
    nofralloc
    b MBGuideEnd
}

asm void fn_801A9360(void) {
    nofralloc
    b MBGuideKill
}

asm void fn_801A9364(void) {
    nofralloc
    b MBGuideMdlPosSet
}

asm void fn_801A9368(void) {
    nofralloc
    b MBGuideMdlPosSetV
}

asm void fn_801A936C(void) {
    nofralloc
    b MBGuideMdlPosGet
}

asm void fn_801A9370(void) {
    nofralloc
    b MBGuideNoGet
}

asm void fn_801A9374(void) {
    nofralloc
    b MBGuideSpeakerNoGet
}

asm void fn_801A9378(void) {
    nofralloc
    b MBGuideScreenPosSet
}

asm void fn_801A937C(void) {
    nofralloc
    b MBGuideScreenPosGet
}

asm void fn_801A9380(void) {
    nofralloc
    b MBGuideCreateFlag
}

asm void fn_801A9384(void) {
    nofralloc
    b MBGuideCreate
}

asm void fn_801A9388(void) {
    nofralloc
    b MBPauseWatchProcCreate
}

asm void fn_801A938C(void) {
    nofralloc
    b MBPauseWatchProcStop
}

asm void fn_801A9390(void) {
    nofralloc
    b MBKillCheck
}

asm void fn_801A9394(void) {
    nofralloc
    b MBPauseWatchProcGet
}

asm void fn_801A9398(void) {
    nofralloc
    b MBObjectSetup
}

asm void fn_801A939C(void) {
    nofralloc
    b MBPauseFlagSet
}

asm void fn_801A93A0(void) {
    nofralloc
    b MBPauseFlagReset
}

asm void fn_801A93A4(void) {
    nofralloc
    b MBPauseFlagCheck
}

asm void fn_801A93A8(void) {
    nofralloc
    b MBLightSet
}

asm void fn_801A93AC(void) {
    nofralloc
    b MBLightReset
}

asm void fn_801A93B0(void) {
    nofralloc
    b MBLightHookSet
}

asm void fn_801A93B4(void) {
    nofralloc
    b MBDataDirReadAsync
}

asm void fn_801A93B8(void) {
    nofralloc
    b MBDataAsyncWait
}

asm void fn_801A93BC(void) {
    nofralloc
    b MBEventMgCheck
}

asm void fn_801A93C0(void) {
    nofralloc
    b MBOvlGoto
}

asm void fn_801A93C4(void) {
    nofralloc
    b MBDataClose
}

asm void fn_801A93C8(void) {
    nofralloc
    b MBPreTurnHookSet
}

asm void fn_801A93CC(void) {
    nofralloc
    b MBPostTurnHookSet
}

asm void fn_801A93D0(void) {
    nofralloc
    b fn_8008D448
}

asm void fn_801A93D4(void) {
    nofralloc
    b fn_8008D450
}

asm void fn_801A93D8(void) {
    nofralloc
    b fn_8008D458
}

asm void fn_801A93DC(void) {
    nofralloc
    b fn_8008D460
}

asm void fn_801A93E0(void) {
    nofralloc
    b MBScrollInit
}

asm void fn_801A93E4(void) {
    nofralloc
    b MBScrollClose
}

asm void fn_801A93E8(void) {
    nofralloc
    b MBStarScrollCreate
}

asm void fn_801A93EC(void) {
    nofralloc
    b MBStarScrollDoneCheck
}

asm void fn_801A93F0(void) {
    nofralloc
    b MBStarScrollStart
}

asm void fn_801A93F4(void) {
    nofralloc
    b MBStarScrollKill
}

asm void fn_801A93F8(void) {
    nofralloc
    b MBMapViewCameraSet
}

asm void fn_801A93FC(void) {
    nofralloc
    b MBMapViewHookSet
}

asm void fn_801A9400(void) {
    nofralloc
    b MBMapViewExec
}

asm void fn_801A9404(void) {
    nofralloc
    b MBMasuCreate
}

asm void fn_801A9408(void) {
    nofralloc
    b MBMasuKill
}

asm void fn_801A940C(void) {
    nofralloc
    b MBMasuWalkEndEventExec
}

asm void fn_801A9410(void) {
    nofralloc
    b MBMasuWalkPostHookSet
}

asm void fn_801A9414(void) {
    nofralloc
    b MBMasuHatenaHookSet
}

asm void fn_801A9418(void) {
    nofralloc
    b MBMasuWalkPreHookSet
}

asm void fn_801A941C(void) {
    nofralloc
    b MBMasuWalkPreExec
}

asm void fn_801A9420(void) {
    nofralloc
    b MBMasuWalkPostExec
}

asm void fn_801A9424(void) {
    nofralloc
    b MBMasuWalkEndExec
}

asm void fn_801A9428(void) {
    nofralloc
    b MBMasuWalkExec
}

asm void fn_801A942C(void) {
    nofralloc
    b MBMasuCameraSet
}

asm void fn_801A9430(void) {
    nofralloc
    b MBMasuCornerRotPosGet
}

asm void fn_801A9434(void) {
    nofralloc
    b MBMasuTypeChange
}

asm void fn_801A9438(void) {
    nofralloc
    b MBMasuNumGet
}

asm void fn_801A943C(void) {
    nofralloc
    b MBMasuGet
}

asm void fn_801A9440(void) {
    nofralloc
    b MBMasuFlagPosGet
}

asm void fn_801A9444(void) {
    nofralloc
    b MBMasuFlagGet
}

asm void fn_801A9448(void) {
    nofralloc
    b MBMasuTypeLinkGet
}

asm void fn_801A944C(void) {
    nofralloc
    b MBMasuPosGet
}

asm void fn_801A9450(void) {
    nofralloc
    b MBMasuRotGet
}

asm void fn_801A9454(void) {
    nofralloc
    b MBMasuDataRead
}

asm void fn_801A9458(void) {
    nofralloc
    b MBMasuDispMaskReset
}

asm void fn_801A945C(void) {
    nofralloc
    b MBMasuDispMaskSet
}

asm void fn_801A9460(void) {
    nofralloc
    b MBMasuTypeSet
}

asm void fn_801A9464(void) {
    nofralloc
    b MBMasuDispSet
}

asm void fn_801A9468(void) {
    nofralloc
    b MBMasuIdStarCheck
}

asm void fn_801A946C(void) {
    nofralloc
    b MBMasuStarGet
}

asm void fn_801A9470(void) {
    nofralloc
    b MBMasuStub
}

asm void fn_801A9474(void) {
    nofralloc
    b MBMasuSaiHiddenSet
}

asm void fn_801A9478(void) {
    nofralloc
    b MBMasuEffSet
}

asm void fn_801A947C(void) {
    nofralloc
    b MBMasuEffClear
}

asm void fn_801A9480(void) {
    nofralloc
    b MBMasuMtxSet
}

asm void fn_801A9484(void) {
    nofralloc
    b MBMasuMtxGet
}

asm void fn_801A9488(void) {
    nofralloc
    b MBMasuCornerPosGet
}

asm void fn_801A948C(void) {
    nofralloc
    b MBMasuCapsuleClear
}

asm void fn_801A9490(void) {
    nofralloc
    b MBMasuFlagMatchFindLink
}

asm void fn_801A9494(void) {
    nofralloc
    b MBMasuFlagFindLink
}

asm void fn_801A9498(void) {
    nofralloc
    b MBMasuFlagMatchFind
}

asm void fn_801A949C(void) {
    nofralloc
    b MBMasuFlagFind
}

asm void fn_801A94A0(void) {
    nofralloc
    b MBMasuCapsuleSet
}

asm void fn_801A94A4(void) {
    nofralloc
    b MBMasuCapsuleGet
}

asm void fn_801A94A8(void) {
    nofralloc
    b MBMasuPathCheckHookSet
}

asm void fn_801A94AC(void) {
    nofralloc
    b MBMasuPathNoLoopCheck
}

asm void fn_801A94B0(void) {
    nofralloc
    b MBMasuPathCheck
}

asm void fn_801A94B4(void) {
    nofralloc
    b MBMasuPathTypeLenGet
}

asm void fn_801A94B8(void) {
    nofralloc
    b MBMasuPathTypeWrapLenGet
}

asm void fn_801A94BC(void) {
    nofralloc
    b MBMasuPathFlagLenGet
}

asm void fn_801A94C0(void) {
    nofralloc
    b MBMasuPathFlagMatchLenGet
}

asm void fn_801A94C4(void) {
    nofralloc
    b MBMasuPathMasuGet
}

asm void fn_801A94C8(void) {
    nofralloc
    b MBMasuPathMasuWrapGet
}

asm void fn_801A94CC(void) {
    nofralloc
    b MBMasuEventFlagGet
}

asm void fn_801A94D0(void) {
    nofralloc
    b MBMasuCapsuleFind
}

asm void fn_801A94D4(void) {
    nofralloc
    b MBMasuColorSet
}

asm void fn_801A94D8(void) {
    nofralloc
    b MBMasuPlayerLightSet
}

asm void fn_801A94DC(void) {
    nofralloc
    b MBMasuDispMaskGet
}

asm void fn_801A94E0(void) {
    nofralloc
    b MBMasuDispGet
}

asm void fn_801A94E4(void) {
    nofralloc
    b MBMasuCarTargetGet
}

asm void fn_801A94E8(void) {
    nofralloc
    b MBMasuTargetGet
}

asm void fn_801A94EC(void) {
    nofralloc
    b MBMasuCarNextGet
}

asm void fn_801A94F0(void) {
    nofralloc
    b MBMasuCarPrevGet
}

asm void fn_801A94F4(void) {
    nofralloc
    b MBMasuDonkeySet
}

asm void fn_801A94F8(void) {
    nofralloc
    b MBMasuDonkeyGet
}

asm void fn_801A94FC(void) {
    nofralloc
    b MBMasuDonkeyNumGet
}

asm void fn_801A9500(void) {
    nofralloc
    b MBMasuPathWrapLenGet
}

asm void fn_801A9504(void) {
    nofralloc
    b MBMasuPathLenGet
}

asm void fn_801A9508(void) {
    nofralloc
    b MBVecMagCheck
}

asm void fn_801A950C(void) {
    nofralloc
    b MBAngleAdd
}

asm void fn_801A9510(void) {
    nofralloc
    b MBAngleMoveTo
}

asm void fn_801A9514(void) {
    nofralloc
    b MBVecDistXZ
}

asm void fn_801A9518(void) {
    nofralloc
    b MBMtxLookAtCalc
}

asm void fn_801A951C(void) {
    nofralloc
    b MBAngleWrapV
}

asm void fn_801A9520(void) {
    nofralloc
    b MBAngleWrap
}

asm void fn_801A9524(void) {
    nofralloc
    b MBVecDistXZCheck
}

asm void fn_801A9528(void) {
    nofralloc
    b MBBezierCalc
}

asm void fn_801A952C(void) {
    nofralloc
    b MBBezierCalcV
}

asm void fn_801A9530(void) {
    nofralloc
    b MBBezierCalcVList
}

asm void fn_801A9534(void) {
    nofralloc
    b MBBezierCalcSlope
}

asm void fn_801A9538(void) {
    nofralloc
    b MBBezierCalcSlopeV
}

asm void fn_801A953C(void) {
    nofralloc
    b MBHermiteCalc
}

asm void fn_801A9540(void) {
    nofralloc
    b MBHermiteCalcV
}

asm void fn_801A9544(void) {
    nofralloc
    b MBHermiteCalcSlope
}

asm void fn_801A9548(void) {
    nofralloc
    b MB3Dto2D
}

asm void fn_801A954C(void) {
    nofralloc
    b MB2Dto3D
}

asm void fn_801A9550(void) {
    nofralloc
    b MBAngleLerp
}

asm void fn_801A9554(void) {
    nofralloc
    b MBAngleLerpSin
}

asm void fn_801A9558(void) {
    nofralloc
    b MBAngleLerpCos
}

asm void fn_801A955C(void) {
    nofralloc
    b MBPointDepthScale
}

asm void fn_801A9560(void) {
    nofralloc
    b MBTelopPlayerCreate
}

asm void fn_801A9564(void) {
    nofralloc
    b MBTelopCreate
}

asm void fn_801A9568(void) {
    nofralloc
    b MBTelopCheck
}

asm void fn_801A956C(void) {
    nofralloc
    b MBTelopLast5Create
}

asm void fn_801A9570(void) {
    nofralloc
    b MBTelopComNumCreate
}

asm void fn_801A9574(void) {
    nofralloc
    b MBPadStkXGet
}

asm void fn_801A9578(void) {
    nofralloc
    b MBPadStkYGet
}

asm void fn_801A957C(void) {
    nofralloc
    b MBTauntInit
}

asm void fn_801A9580(void) {
    nofralloc
    b MBTauntKill
}

asm void fn_801A9584(void) {
    nofralloc
    b MBModelInit
}

asm void fn_801A9588(void) {
    nofralloc
    b MBModelClose
}

asm void fn_801A958C(void) {
    nofralloc
    b MBModelManDummy
}

asm void fn_801A9590(void) {
    nofralloc
    b MBModelKill
}

asm void fn_801A9594(void) {
    nofralloc
    b MBModelStubValSet
}

asm void fn_801A9598(void) {
    nofralloc
    b MBModelStubVal2Set
}

asm void fn_801A959C(void) {
    nofralloc
    b MBModelIdGet
}

asm void fn_801A95A0(void) {
    nofralloc
    b MBModelAlphaSet
}

asm void fn_801A95A4(void) {
    nofralloc
    b MBMotionNoSet
}

asm void fn_801A95A8(void) {
    nofralloc
    b MBMotionShiftIDGet
}

asm void fn_801A95AC(void) {
    nofralloc
    b MBMotionShiftSet
}

asm void fn_801A95B0(void) {
    nofralloc
    b MBModelAttrSet
}

asm void fn_801A95B4(void) {
    nofralloc
    b MBModelAttrReset
}

asm void fn_801A95B8(void) {
    nofralloc
    b MBMotionTimeSet
}

asm void fn_801A95BC(void) {
    nofralloc
    b MBMotionSpeedSet
}

asm void fn_801A95C0(void) {
    nofralloc
    b MBMotionSpeedGet
}

asm void fn_801A95C4(void) {
    nofralloc
    b MBMotionStartEndSet
}

asm void fn_801A95C8(void) {
    nofralloc
    b MBMotionLoopSet
}

asm void fn_801A95CC(void) {
    nofralloc
    b MBMotionShapeSet
}

asm void fn_801A95D0(void) {
    nofralloc
    b MBMotionShapeTimeGet
}

asm void fn_801A95D4(void) {
    nofralloc
    b MBMotionShapeMaxTimeGet
}

asm void fn_801A95D8(void) {
    nofralloc
    b MBMotionShapeSpeedSet
}

asm void fn_801A95DC(void) {
    nofralloc
    b MBMotionShapeSpeedGet
}

asm void fn_801A95E0(void) {
    nofralloc
    b MBMotionShapeEndCheck
}

asm void fn_801A95E4(void) {
    nofralloc
    b MBMotionShapeStartEndSet
}

asm void fn_801A95E8(void) {
    nofralloc
    b MBModelMtxSet
}

asm void fn_801A95EC(void) {
    nofralloc
    b MBModelMtxGet
}

asm void fn_801A95F0(void) {
    nofralloc
    b MBModelRotYSet
}

asm void fn_801A95F4(void) {
    nofralloc
    b MBModelRotYGet
}

asm void fn_801A95F8(void) {
    nofralloc
    b MBModelPosSetV
}

asm void fn_801A95FC(void) {
    nofralloc
    b MBModelRotSetV
}

asm void fn_801A9600(void) {
    nofralloc
    b MBModelScaleSetV
}

asm void fn_801A9604(void) {
    nofralloc
    b MBModelPosSet
}

asm void fn_801A9608(void) {
    nofralloc
    b MBModelRotSet
}

asm void fn_801A960C(void) {
    nofralloc
    b MBModelScaleSet
}

asm void fn_801A9610(void) {
    nofralloc
    b MBModelPosGet
}

asm void fn_801A9614(void) {
    nofralloc
    b MBModelRotGet
}

asm void fn_801A9618(void) {
    nofralloc
    b MBModelScaleGet
}

asm void fn_801A961C(void) {
    nofralloc
    b MBModelOffsetSet
}

asm void fn_801A9620(void) {
    nofralloc
    b MBModelOffsetSetV
}

asm void fn_801A9624(void) {
    nofralloc
    b MBModelOffsetGet
}

asm void fn_801A9628(void) {
    nofralloc
    b MBModelUnkSpeedSet
}

asm void fn_801A962C(void) {
    nofralloc
    b MBModelDispSet
}

asm void fn_801A9630(void) {
    nofralloc
    b MBModelDispGet
}

asm void fn_801A9634(void) {
    nofralloc
    b MBModelLayerSet
}

asm void fn_801A9638(void) {
    nofralloc
    b MBModelLayerGet
}

asm void fn_801A963C(void) {
    nofralloc
    b MBModelCameraSet
}

asm void fn_801A9640(void) {
    nofralloc
    b MBModelZWriteOffSet
}

asm void fn_801A9644(void) {
    nofralloc
    b MBModelUnkFlagSet
}

asm void fn_801A9648(void) {
    nofralloc
    b MBModelHookSet
}

asm void fn_801A964C(void) {
    nofralloc
    b MBModelHookReset
}

asm void fn_801A9650(void) {
    nofralloc
    b MBModelHookObjReset
}

asm void fn_801A9654(void) {
    nofralloc
    b MBMotionEndCheck
}

asm void fn_801A9658(void) {
    nofralloc
    b MBMotionTimeGet
}

asm void fn_801A965C(void) {
    nofralloc
    b MBMotionMaxTimeGet
}

asm void fn_801A9660(void) {
    nofralloc
    b MBMotionCreate
}

asm void fn_801A9664(void) {
    nofralloc
    b MBMotionKill
}

asm void fn_801A9668(void) {
    nofralloc
    b MBModelCreate
}

asm void fn_801A966C(void) {
    nofralloc
    b MBModelCreateChar
}

asm void fn_801A9670(void) {
    nofralloc
    b MBModelCreateParam
}

asm void fn_801A9674(void) {
    nofralloc
    b MBModelLayerSetAll
}

asm void fn_801A9678(void) {
    nofralloc
    b MBModelCameraSetAll
}

asm void fn_801A967C(void) {
    nofralloc
    b MBModelDispOffAll
}

asm void fn_801A9680(void) {
    nofralloc
    b MBModelDispOffCamera
}

asm void fn_801A9684(void) {
    nofralloc
    b MBModelAmbSet
}

asm void fn_801A9688(void) {
    nofralloc
    b MBModelAmbSetAll
}

asm void fn_801A968C(void) {
    nofralloc
    b MBMotionVoiceOnSet
}

asm void fn_801A9690(void) {
    nofralloc
    b MBModelStub
}

asm void fn_801A9694(void) {
    nofralloc
    b MBModelSePlay
}

asm void fn_801A9698(void) {
    nofralloc
    b MBOpeningProcExec
}

asm void fn_801A969C(void) {
    nofralloc
    b MBOpeningViewSet
}

asm void fn_801A96A0(void) {
    nofralloc
    b MBOpeningViewZoomGet
}

asm void fn_801A96A4(void) {
    nofralloc
    b MBOpeningViewRotGet
}

asm void fn_801A96A8(void) {
    nofralloc
    b MBOpeningViewFocusGet
}

asm void fn_801A96AC(void) {
    nofralloc
    b MBPauseProcCreate
}

asm void fn_801A96B0(void) {
    nofralloc
    b MBPauseStartCheck
}

asm void fn_801A96B4(void) {
    nofralloc
    b MBPauseProcCheck
}

asm void fn_801A96B8(void) {
    nofralloc
    b MBPauseDisableSet
}

asm void fn_801A96BC(void) {
    nofralloc
    b MBPauseDisableGet
}

asm void fn_801A96C0(void) {
    nofralloc
    b MBPauseHookPush
}

asm void fn_801A96C4(void) {
    nofralloc
    b MBPauseHookPop
}

asm void fn_801A96C8(void) {
    nofralloc
    b MBPauseSet
}

asm void fn_801A96CC(void) {
    nofralloc
    b MBPlayerInit
}

asm void fn_801A96D0(void) {
    nofralloc
    b MBPlayerClose
}

asm void fn_801A96D4(void) {
    nofralloc
    b MBTurnExecParty
}

asm void fn_801A96D8(void) {
    nofralloc
    b MBTurnExecStory
}

asm void fn_801A96DC(void) {
    nofralloc
    b MBPlayerNameMesGet
}

asm void fn_801A96E0(void) {
    nofralloc
    b MBPlayerNameGet
}

asm void fn_801A96E4(void) {
    nofralloc
    b MBPlayerColorGet
}

asm void fn_801A96E8(void) {
    nofralloc
    b MBPlayerAmbSet
}

asm void fn_801A96EC(void) {
    nofralloc
    b MBPlayerWorkGet
}

asm void fn_801A96F0(void) {
    nofralloc
    b MBPlayerAllComCheck
}

asm void fn_801A96F4(void) {
    nofralloc
    b MBPlayerModelGet
}

asm void fn_801A96F8(void) {
    nofralloc
    b MBPlayerDispSet
}

asm void fn_801A96FC(void) {
    nofralloc
    b MBPlayerLayerSet
}

asm void fn_801A9700(void) {
    nofralloc
    b MBPlayerCameraSet
}

asm void fn_801A9704(void) {
    nofralloc
    b MBPlayerUnkSpeedSet
}

asm void fn_801A9708(void) {
    nofralloc
    b MBPlayerStubValSet
}

asm void fn_801A970C(void) {
    nofralloc
    b MBPlayerMtxSet
}

asm void fn_801A9710(void) {
    nofralloc
    b MBPlayerPosSet
}

asm void fn_801A9714(void) {
    nofralloc
    b MBPlayerPosSetV
}

asm void fn_801A9718(void) {
    nofralloc
    b MBPlayerPosGet
}

asm void fn_801A971C(void) {
    nofralloc
    b MBPlayerRotSet
}

asm void fn_801A9720(void) {
    nofralloc
    b MBPlayerRotSetV
}

asm void fn_801A9724(void) {
    nofralloc
    b MBPlayerRotGet
}

asm void fn_801A9728(void) {
    nofralloc
    b MBPlayerRotYSet
}

asm void fn_801A972C(void) {
    nofralloc
    b MBPlayerRotYGet
}

asm void fn_801A9730(void) {
    nofralloc
    b MBPlayerScaleSet
}

asm void fn_801A9734(void) {
    nofralloc
    b MBPlayerScaleSetV
}

asm void fn_801A9738(void) {
    nofralloc
    b MBPlayerScaleGet
}

asm void fn_801A973C(void) {
    nofralloc
    b MBPlayerMotionNoGet
}

asm void fn_801A9740(void) {
    nofralloc
    b MBPlayerMotionEndCheck
}

asm void fn_801A9744(void) {
    nofralloc
    b MBPlayerMotionEndCheckAll
}

asm void fn_801A9748(void) {
    nofralloc
    b MBPlayerMotionEndWait
}

asm void fn_801A974C(void) {
    nofralloc
    b MBPlayerMotionMaxTimeGet
}

asm void fn_801A9750(void) {
    nofralloc
    b MBPlayerMotionTimeGet
}

asm void fn_801A9754(void) {
    nofralloc
    b MBPlayerMotionNoSet
}

asm void fn_801A9758(void) {
    nofralloc
    b MBPlayerMotionVoiceOnSet
}

asm void fn_801A975C(void) {
    nofralloc
    b MBPlayerMotionNoShiftSet
}

asm void fn_801A9760(void) {
    nofralloc
    b MBPlayerMotionCreate
}

asm void fn_801A9764(void) {
    nofralloc
    b MBPlayerMotionKill
}

asm void fn_801A9768(void) {
    nofralloc
    b MBPlayerMotionSpeedSet
}

asm void fn_801A976C(void) {
    nofralloc
    b MBPlayerMotionTimeSet
}

asm void fn_801A9770(void) {
    nofralloc
    b MBPlayerMotionStartEndSet
}

asm void fn_801A9774(void) {
    nofralloc
    b MBPlayerModelAttrSet
}

asm void fn_801A9778(void) {
    nofralloc
    b MBPlayerModelAttrReset
}

asm void fn_801A977C(void) {
    nofralloc
    b MBPlayerMotIdleSet
}

asm void fn_801A9780(void) {
    nofralloc
    b MBPlayerRotateStart
}

asm void fn_801A9784(void) {
    nofralloc
    b MBPlayerRotateCheck
}

asm void fn_801A9788(void) {
    nofralloc
    b MBPlayerRotateCheckAll
}

asm void fn_801A978C(void) {
    nofralloc
    b MBPlayerEyeMatDarkSet
}

asm void fn_801A9790(void) {
    nofralloc
    b MBPlayerRankGet
}

asm void fn_801A9794(void) {
    nofralloc
    b MBPlayerCapsuleUseGet
}

asm void fn_801A9798(void) {
    nofralloc
    b MBPlayerCapsuleUseSet
}

asm void fn_801A979C(void) {
    nofralloc
    b MBPlayerCapsuleRemove
}

asm void fn_801A97A0(void) {
    nofralloc
    b MBPlayerCapsuleFind
}

asm void fn_801A97A4(void) {
    nofralloc
    b MBPlayerCapsuleAdd
}

asm void fn_801A97A8(void) {
    nofralloc
    b MBPlayerCapsuleNumGet
}

asm void fn_801A97AC(void) {
    nofralloc
    b MBPlayerCapsuleGet
}

asm void fn_801A97B0(void) {
    nofralloc
    b MBPlayerCapsuleMaxGet
}

asm void fn_801A97B4(void) {
    nofralloc
    b MBPlayerCoinAdd
}

asm void fn_801A97B8(void) {
    nofralloc
    b MBPlayerCoinSet
}

asm void fn_801A97BC(void) {
    nofralloc
    b MBPlayerCoinGet
}

asm void fn_801A97C0(void) {
    nofralloc
    b MBPlayerMaxCoinGet
}

asm void fn_801A97C4(void) {
    nofralloc
    b MBPlayerStarAdd
}

asm void fn_801A97C8(void) {
    nofralloc
    b MBPlayerStarSet
}

asm void fn_801A97CC(void) {
    nofralloc
    b MBPlayerStarGet
}

asm void fn_801A97D0(void) {
    nofralloc
    b MBPlayerGrpFind
}

asm void fn_801A97D4(void) {
    nofralloc
    b MBPlayerGrpFindOther
}

asm void fn_801A97D8(void) {
    nofralloc
    b MBPlayerGrpCoinSet
}

asm void fn_801A97DC(void) {
    nofralloc
    b MBPlayerGrpCoinGet
}

asm void fn_801A97E0(void) {
    nofralloc
    b MBPlayerGrpStarSet
}

asm void fn_801A97E4(void) {
    nofralloc
    b MBPlayerGrpStarGet
}

asm void fn_801A97E8(void) {
    nofralloc
    b MBPlayerGrpRankGet
}

asm void fn_801A97EC(void) {
    nofralloc
    b MBPlayerGrpFindPlayer
}

asm void fn_801A97F0(void) {
    nofralloc
    b MBPlayerGrpCapsuleGet
}

asm void fn_801A97F4(void) {
    nofralloc
    b MBPlayerGrpCapsuleNumGet
}

asm void fn_801A97F8(void) {
    nofralloc
    b MBPlayerWalkSpeedGet
}

asm void fn_801A97FC(void) {
    nofralloc
    b MBPlayerWalkExec
}

asm void fn_801A9800(void) {
    nofralloc
    b MBPlayerWalkMain
}

asm void fn_801A9804(void) {
    nofralloc
    b MBPlayerPosFixEvent
}

asm void fn_801A9808(void) {
    nofralloc
    b MBPlayerPosFixSet
}

asm void fn_801A980C(void) {
    nofralloc
    b MBWalkNumCreateColor
}

asm void fn_801A9810(void) {
    nofralloc
    b MBWalkNumCreate
}

asm void fn_801A9814(void) {
    nofralloc
    b MBWalkNumKill
}

asm void fn_801A9818(void) {
    nofralloc
    b MBWalkNumDispSet
}

asm void fn_801A981C(void) {
    nofralloc
    b MBPlayerMasuWalkTo
}

asm void fn_801A9820(void) {
    nofralloc
    b MBPlayerMasuWalk
}

asm void fn_801A9824(void) {
    nofralloc
    b MBPlayerMasuWalkPos
}

asm void fn_801A9828(void) {
    nofralloc
    b MBPlayerMasuWalkSpeed
}

asm void fn_801A982C(void) {
    nofralloc
    b MBPlayerPosFixFlagSet
}

asm void fn_801A9830(void) {
    nofralloc
    b MBPlayerPosFixPlayer
}

asm void fn_801A9834(void) {
    nofralloc
    b MBPlayerPosFix
}

asm void fn_801A9838(void) {
    nofralloc
    b MBPlayerPosFixWarp
}

asm void fn_801A983C(void) {
    nofralloc
    b MBPlayerPosFixCheck
}

asm void fn_801A9840(void) {
    nofralloc
    b MBPlayerBestPathGet
}

asm void fn_801A9844(void) {
    nofralloc
    b MBPlayerPosReset
}

asm void fn_801A9848(void) {
    nofralloc
    b MBPlayerPosRestoreAll
}

asm void fn_801A984C(void) {
    nofralloc
    b MBPlayerMasuCornerSet
}

asm void fn_801A9850(void) {
    nofralloc
    b MBPlayerMasuCornerGet
}

asm void fn_801A9854(void) {
    nofralloc
    b MBPlayerSaiMotExec
}

asm void fn_801A9858(void) {
    nofralloc
    b MBPlayerAliveCheck
}

asm void fn_801A985C(void) {
    nofralloc
    b MBPlayerDeadCheck
}

asm void fn_801A9860(void) {
    nofralloc
    b MBPlayerAliveGet
}

asm void fn_801A9864(void) {
    nofralloc
    b MBPlayerDeadGet
}

asm void fn_801A9868(void) {
    nofralloc
    b MBPlayerMoveCheck
}

asm void fn_801A986C(void) {
    nofralloc
    b MBPlayerStoryLoseCheck
}

asm void fn_801A9870(void) {
    nofralloc
    b MBPlayerStoryAliveReset
}

asm void fn_801A9874(void) {
    nofralloc
    b MBPlayerStoryLoseExec
}

asm void fn_801A9878(void) {
    nofralloc
    b MBPlayerStoryPlayerCheck
}

asm void fn_801A987C(void) {
    nofralloc
    b MBPlayerStoryComCheck
}

asm void fn_801A9880(void) {
    nofralloc
    b MBPlayerStoryPlayerGet
}

asm void fn_801A9884(void) {
    nofralloc
    b MBPlayerAlivePlayerGet
}

asm void fn_801A9888(void) {
    nofralloc
    b MBPlayerDeadComGet
}

asm void fn_801A988C(void) {
    nofralloc
    b MBPlayerKettouCheck
}

asm void fn_801A9890(void) {
    nofralloc
    b MBPlayerKettouStoryCheck
}

asm void fn_801A9894(void) {
    nofralloc
    b MBPlayerBlackoutSet
}

asm void fn_801A9898(void) {
    nofralloc
    b MBPlayerBlackoutGet
}

asm void fn_801A989C(void) {
    nofralloc
    b MBPlayerWinLoseVoicePlay
}

asm void fn_801A98A0(void) {
    nofralloc
    b MBPlayerVoicePlay
}

asm void fn_801A98A4(void) {
    nofralloc
    b MBPlayerVoicePanPlay
}

asm void fn_801A98A8(void) {
    nofralloc
    b MBPlayerPosFixCurr
}

asm void fn_801A98AC(void) {
    nofralloc
    b MBPlayerPreTurnHookSet
}

asm void fn_801A98B0(void) {
    nofralloc
    b MBPlayerPostTurnHookSet
}

asm void fn_801A98B4(void) {
    nofralloc
    b MBPlayerSaiTypeGet
}

asm void fn_801A98B8(void) {
    nofralloc
    b MBPlayerPosFixOrderSet
}

asm void fn_801A98BC(void) {
    nofralloc
    b MBRouletteCreate
}

asm void fn_801A98C0(void) {
    nofralloc
    b MBRouletteKaneCreate
}

asm void fn_801A98C4(void) {
    nofralloc
    b MBRouletteCheck
}

asm void fn_801A98C8(void) {
    nofralloc
    b MBRouletteWait
}

asm void fn_801A98CC(void) {
    nofralloc
    b MBRouletteResultGet
}

asm void fn_801A98D0(void) {
    nofralloc
    b MBRouletteMaxSpeedSet
}

asm void fn_801A98D4(void) {
    nofralloc
    b MBRouletteComValueSet
}

asm void fn_801A98D8(void) {
    nofralloc
    b MBMusPlay
}

asm void fn_801A98DC(void) {
    nofralloc
    b MBMusFadeOutDefault
}

asm void fn_801A98E0(void) {
    nofralloc
    b MBMusFadeOut
}

asm void fn_801A98E4(void) {
    nofralloc
    b MBMusStub
}

asm void fn_801A98E8(void) {
    nofralloc
    b MBMusParamSet
}

asm void fn_801A98EC(void) {
    nofralloc
    b MBMusPauseFadeOut
}

asm void fn_801A98F0(void) {
    nofralloc
    b MBMusStatGet
}

asm void fn_801A98F4(void) {
    nofralloc
    b MBAudClose
}

asm void fn_801A98F8(void) {
    nofralloc
    b MBAudInit
}

asm void fn_801A98FC(void) {
    nofralloc
    b MBAudStub1
}

asm void fn_801A9900(void) {
    nofralloc
    b MBAudStub2
}

asm void fn_801A9904(void) {
    nofralloc
    b MBMusMainPlay
}

asm void fn_801A9908(void) {
    nofralloc
    b MBAudFXPlay
}

asm void fn_801A990C(void) {
    nofralloc
    b MBAudFXStop
}

asm void fn_801A9910(void) {
    nofralloc
    b MBMusCheck
}

asm void fn_801A9914(void) {
    nofralloc
    b MBMusEndCheck
}

asm void fn_801A9918(void) {
    nofralloc
    b MBMusStopCheck
}

asm void fn_801A991C(void) {
    nofralloc
    b MBMusPlayJingle
}

asm void fn_801A9920(void) {
    nofralloc
    b MBMusJingleStatGet
}

asm void fn_801A9924(void) {
    nofralloc
    b MBAudFXSet
}

asm void fn_801A9928(void) {
    nofralloc
    b MBAudFXCreate
}

asm void fn_801A992C(void) {
    nofralloc
    b MBAudFXVolSet
}

asm void fn_801A9930(void) {
    nofralloc
    b MBAudFXKill
}

asm void fn_801A9934(void) {
    nofralloc
    b MBAudFXClose
}

asm void fn_801A9938(void) {
    nofralloc
    b MBAudFXEmiterSet
}

asm void fn_801A993C(void) {
    nofralloc
    b MBAudFXEmiterCreate
}

asm void fn_801A9940(void) {
    nofralloc
    b MBAudFXEmiterUpdate
}

asm void fn_801A9944(void) {
    nofralloc
    b MBAudFXEmiterPosSet
}

asm void fn_801A9948(void) {
    nofralloc
    b MBAudFXRefSet
}

asm void fn_801A994C(void) {
    nofralloc
    b MBAudFXPosPlay
}

asm void fn_801A9950(void) {
    nofralloc
    b MBAudFXPosPanGet
}

asm void fn_801A9954(void) {
    nofralloc
    b MBMasuStarExec
}

asm void fn_801A9958(void) {
    nofralloc
    b MBStarGetProcExec
}

asm void fn_801A995C(void) {
    nofralloc
    b MBStarGetExec
}

asm void fn_801A9960(void) {
    nofralloc
    b MBStarMapViewExec
}

asm void fn_801A9964(void) {
    nofralloc
    b MBStarMapViewProcExec
}

asm void fn_801A9968(void) {
    nofralloc
    b MBStarInit
}

asm void fn_801A996C(void) {
    nofralloc
    b MBStarClose
}

asm void fn_801A9970(void) {
    nofralloc
    b MBStarCreate
}

asm void fn_801A9974(void) {
    nofralloc
    b MBStarNoReset
}

asm void fn_801A9978(void) {
    nofralloc
    b MBStarNumSet
}

asm void fn_801A997C(void) {
    nofralloc
    b MBStarNumGet
}

asm void fn_801A9980(void) {
    nofralloc
    b MBStarFlagInit
}

asm void fn_801A9984(void) {
    nofralloc
    b MBStarFlagSet
}

asm void fn_801A9988(void) {
    nofralloc
    b MBStarFlagReset
}

asm void fn_801A998C(void) {
    nofralloc
    b MBStarFlagGet
}

asm void fn_801A9990(void) {
    nofralloc
    b MBStarNextNoSet
}

asm void fn_801A9994(void) {
    nofralloc
    b MBStarNextNoGet
}

asm void fn_801A9998(void) {
    nofralloc
    b MBStarNoSet
}

asm void fn_801A999C(void) {
    nofralloc
    b MBStarNoRandGet
}

asm void fn_801A99A0(void) {
    nofralloc
    b MBStarNoInit
}

asm void fn_801A99A4(void) {
    nofralloc
    b MBStarObjDispSet
}

asm void fn_801A99A8(void) {
    nofralloc
    b MBStarDispSet
}

asm void fn_801A99AC(void) {
    nofralloc
    b MBStarMasuDispSet
}

asm void fn_801A99B0(void) {
    nofralloc
    b MBStarDispSetAll
}

asm void fn_801A99B4(void) {
    nofralloc
    b MBStarTutorialExec
}

asm void fn_801A99B8(void) {
    nofralloc
    b MBStatusInit
}

asm void fn_801A99BC(void) {
    nofralloc
    b MBStatusClose
}

asm void fn_801A99C0(void) {
    nofralloc
    b MBStatusReinit
}

asm void fn_801A99C4(void) {
    nofralloc
    b MBStatusDispGet
}

asm void fn_801A99C8(void) {
    nofralloc
    b MBStatusDispSet
}

asm void fn_801A99CC(void) {
    nofralloc
    b MBStatusDispFocusSet
}

asm void fn_801A99D0(void) {
    nofralloc
    b MBStatusDispSetAll
}

asm void fn_801A99D4(void) {
    nofralloc
    b MBStatusDispForceSet
}

asm void fn_801A99D8(void) {
    nofralloc
    b MBStatusDispForceSetAll
}

asm void fn_801A99DC(void) {
    nofralloc
    b MBStatusMoveCheck
}

asm void fn_801A99E0(void) {
    nofralloc
    b MBSpriteCreate
}

asm void fn_801A99E4(void) {
    nofralloc
    b MBStatusPosGet
}

asm void fn_801A99E8(void) {
    nofralloc
    b MBStatusNoPosGet
}

asm void fn_801A99EC(void) {
    nofralloc
    b MBStatusCapsuleDispSet
}

asm void fn_801A99F0(void) {
    nofralloc
    b MBStatusKaoNoSet
}

asm void fn_801A99F4(void) {
    nofralloc
    b MBSpriteNumSet
}

asm void fn_801A99F8(void) {
    nofralloc
    b MBStatusMoveTo
}

asm void fn_801A99FC(void) {
    nofralloc
    b MBStatusMoveSet
}

asm void fn_801A9A00(void) {
    nofralloc
    b MBStatusPosOnGet
}

asm void fn_801A9A04(void) {
    nofralloc
    b MBStatusPosOffGet
}

asm void fn_801A9A08(void) {
    nofralloc
    b MBStatusRainbowSet
}

asm void fn_801A9A0C(void) {
    nofralloc
    b MBStatusColorSet
}

asm void fn_801A9A10(void) {
    nofralloc
    b MBStatusColorGet
}

asm void fn_801A9A14(void) {
    nofralloc
    b MBStatusLayoutSet
}

asm void fn_801A9A18(void) {
    nofralloc
    b MBStatusCapsuleFocusSet
}

asm void fn_801A9A1C(void) {
    nofralloc
    b MBStatusNoGet
}

asm void fn_801A9A20(void) {
    nofralloc
    b MBStatusNoMoveSet
}

asm void fn_801A9A24(void) {
    nofralloc
    b MBStatusDispBackup
}

asm void fn_801A9A28(void) {
    nofralloc
    b MBStatusDispRestore
}

asm void fn_801A9A2C(void) {
    nofralloc
    b MBTutorialWatchProcCreate
}

asm void fn_801A9A30(void) {
    nofralloc
    b MBTutorialExec
}

asm void fn_801A9A34(void) {
    nofralloc
    b MBTutorialSprDispOn
}

asm void fn_801A9A38(void) {
    nofralloc
    b MBTutorialSprDispOff
}

asm void fn_801A9A3C(void) {
    nofralloc
    b MBTutorialExitFlagGet
}

asm void fn_801A9A40(void) {
    nofralloc
    b MBWinInit
}

asm void fn_801A9A44(void) {
    nofralloc
    b MBWinClose
}

asm void fn_801A9A48(void) {
    nofralloc
    b MBWinCreate
}

asm void fn_801A9A4C(void) {
    nofralloc
    b MBWinCreateChoice
}

asm void fn_801A9A50(void) {
    nofralloc
    b MBWinCreateHelp
}

asm void fn_801A9A54(void) {
    nofralloc
    b MBWinKillAll
}

asm void fn_801A9A58(void) {
    nofralloc
    b MBWinKill
}

asm void fn_801A9A5C(void) {
    nofralloc
    b MBTopWinKill
}

asm void fn_801A9A60(void) {
    nofralloc
    b MBWinPosSet
}

asm void fn_801A9A64(void) {
    nofralloc
    b MBTopWinPosSet
}

asm void fn_801A9A68(void) {
    nofralloc
    b MBWinPosGet
}

asm void fn_801A9A6C(void) {
    nofralloc
    b MBTopWinPosGet
}

asm void fn_801A9A70(void) {
    nofralloc
    b MBWinSizeSet
}

asm void fn_801A9A74(void) {
    nofralloc
    b MBTopWinSizeSet
}

asm void fn_801A9A78(void) {
    nofralloc
    b MBWinMesMaxSizeGet
}

asm void fn_801A9A7C(void) {
    nofralloc
    b MBTopWinMesMaxSizeGet
}

asm void fn_801A9A80(void) {
    nofralloc
    b MBWinScaleSet
}

asm void fn_801A9A84(void) {
    nofralloc
    b MBTopWinScaleSet
}

asm void fn_801A9A88(void) {
    nofralloc
    b MBWinScaleGet
}

asm void fn_801A9A8C(void) {
    nofralloc
    b MBTopWinScaleGet
}

asm void fn_801A9A90(void) {
    nofralloc
    b MBWinChoiceGet
}

asm void fn_801A9A94(void) {
    nofralloc
    b MBWinLastChoiceGet
}

asm void fn_801A9A98(void) {
    nofralloc
    b MBWinPause
}

asm void fn_801A9A9C(void) {
    nofralloc
    b MBTopWinPause
}

asm void fn_801A9AA0(void) {
    nofralloc
    b MBWinInsertMesSet
}

asm void fn_801A9AA4(void) {
    nofralloc
    b MBTopWinInsertMesSet
}

asm void fn_801A9AA8(void) {
    nofralloc
    b MBWinDoneCheck
}

asm void fn_801A9AAC(void) {
    nofralloc
    b MBTopWinDoneCheck
}

asm void fn_801A9AB0(void) {
    nofralloc
    b MBWinWait
}

asm void fn_801A9AB4(void) {
    nofralloc
    b MBTopWinWait
}

asm void fn_801A9AB8(void) {
    nofralloc
    b MBWinAttrSet
}

asm void fn_801A9ABC(void) {
    nofralloc
    b MBTopWinAttrSet
}

asm void fn_801A9AC0(void) {
    nofralloc
    b MBWinAttrReset
}

asm void fn_801A9AC4(void) {
    nofralloc
    b MBTopWinAttrReset
}

asm void fn_801A9AC8(void) {
    nofralloc
    b MBWinChoiceDisable
}

asm void fn_801A9ACC(void) {
    nofralloc
    b MBTopWinChoiceDisable
}

asm void fn_801A9AD0(void) {
    nofralloc
    b MBWinMesSpeedSet
}

asm void fn_801A9AD4(void) {
    nofralloc
    b MBTopWinMesSpeedSet
}

asm void fn_801A9AD8(void) {
    nofralloc
    b MBWinMesColSet
}

asm void fn_801A9ADC(void) {
    nofralloc
    b MBTopWinMesColSet
}

asm void fn_801A9AE0(void) {
    nofralloc
    b MBWinChoiceNowGet
}

asm void fn_801A9AE4(void) {
    nofralloc
    b MBTopWinChoiceNowGet
}

asm void fn_801A9AE8(void) {
    nofralloc
    b MBWinPriSet
}

asm void fn_801A9AEC(void) {
    nofralloc
    b MBTopWinPriSet
}

asm void fn_801A9AF0(void) {
    nofralloc
    b MBWinChoiceNowGet2
}

asm void fn_801A9AF4(void) {
    nofralloc
    b MBTopWinChoiceNowGet2
}

asm void fn_801A9AF8(void) {
    nofralloc
    b MBWinPlayerDisable
}

asm void fn_801A9AFC(void) {
    nofralloc
    b MBTopWinPlayerDisable
}

asm void fn_801A9B00(void) {
    nofralloc
    b MBWinIDGet
}

asm void fn_801A9B04(void) {
    nofralloc
    b MBTopWinIDGet
}

asm void fn_801A9B08(void) {
    nofralloc
    b MBWinDispSet
}

asm void fn_801A9B0C(void) {
    nofralloc
    b MBTopWinDispSet
}

asm void fn_801A9B10(void) {
    nofralloc
    b MBWinPauseHook
}

asm void fn_801A9B14(void) {
    nofralloc
    b MBWinGet
}

asm void fn_801A9B18(void) {
    nofralloc
    b MBWinCenterGet
}

asm void fn_801A9B1C(void) {
    nofralloc
    b MBMgCallInit
}

asm void fn_801A9B20(void) {
    nofralloc
    b MBMgCallExec
}

asm void fn_801A9B24(void) {
    nofralloc
    b MBMgCallKettouExec
}

asm void fn_801A9B28(void) {
    nofralloc
    b MBMgCallDonkeyExec
}

asm void fn_801A9B2C(void) {
    nofralloc
    b MBMgCallKupaExec
}

asm void fn_801A9B30(void) {
    nofralloc
    b MBMgCallVsExec
}

asm void fn_801A9B34(void) {
    nofralloc
    b MBMgCallDataClose
}

asm void fn_801A9B38(void) {
    nofralloc
    b MBMgCallTutorialExec
}

asm void fn_801A9B3C(void) {
    nofralloc
    b MBMgCallDispSet
}

asm void fn_801A9B40(void) {
    nofralloc
    b MBCircuitExec
}

asm void fn_801A9B44(void) {
    nofralloc
    b MBCircuitMgEndExec
}

asm void fn_801A9B48(void) {
    nofralloc
    b MBCircuitReset
}

asm void fn_801A9B4C(void) {
    nofralloc
    b MBCircuitCarMoveExec
}

asm void fn_801A9B50(void) {
    nofralloc
    b MBCircuitCarInit
}

asm void fn_801A9B54(void) {
    nofralloc
    b MBCircuitKettouSaiExec
}

asm void fn_801A9B58(void) {
    nofralloc
    b MBCircuitGoalCheck
}

#pragma force_active reset
