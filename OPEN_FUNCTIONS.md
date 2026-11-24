# Open functions: Mario Party 5 (US)

Generated from the objdiff report of a build of this repository. Regenerate rather than edit
by hand.

**Columns.** *match*: objdiff's score for the function as it builds now (100% is identical).
*bytes*: size of the original function. Functions at 0% either have no C yet or have C whose
shape differs from the original (functions merged or split, wrong inlining).

**Summary:** 1,552 functions short of 100%: 401 at 95% or better, 332 at 80-95%, 240 below 80%, 579 at 0%; in 329 units.

## Started, not matching yet

Best first: near the top, the remaining difference is usually register allocation, instruction
order or one wrong type.

| match | function | unit | bytes |
|--:|---|---|--:|
| 99.97% | `fn_1_4F98` | `m527Dll/REL/m527Dll/m527` | 11,972 |
| 99.95% | `fn_1_393C4` | `carddll/REL/carddll/status` | 17,340 |
| 99.92% | `fn_1_FC8` | `m542dll/REL/m542dll/m542` | 5,332 |
| 99.92% | `fn_1_C708` | `m566Dll/REL/m566Dll/m566` | 5,060 |
| 99.91% | `fn_1_DF94` | `sdroomdll/REL/sdroomdll/garage` | 13,412 |
| 99.88% | `fn_1_12B60` | `mgmatchDll/REL/mgmatchDll/score` | 3,416 |
| 99.88% | `BlockProc` | `partyresultdll/REL/partyresultdll/result` | 3,240 |
| 99.84% | `fn_1_8C8` | `m561dll/REL/m561dll/m561` | 5,060 |
| 99.83% | `PResStatMain` | `partyresultdll/REL/partyresultdll/stat` | 7,156 |
| 99.83% | `fn_1_85C4` | `mgmatchDll/REL/mgmatchDll/mgmatch` | 4,736 |
| 99.82% | `__ct__Q24m5176CChoroFv` | `m517Dll/REL/m517Dll/choro` | 2,176 |
| 99.81% | `fn_1_654` | `m525Dll/REL/m525Dll/m525` | 21,212 |
| 99.81% | `fn_1_5B4` | `m527Dll/REL/m527Dll/m527` | 18,916 |
| 99.81% | `fn_1_4B80` | `m518dll/REL/m518dll/m518` | 8,332 |
| 99.80% | `PResResultCreate` | `partyresultdll/REL/partyresultdll/result` | 3,928 |
| 99.79% | `fn_1_F014` | `m562dll/REL/m562dll/koopa` | 1,904 |
| 99.76% | `fn_1_7084` | `m567Dll/REL/m567Dll/m567` | 3,376 |
| 99.76% | `__ct__Q24m5117CPlayerFi` | `m511Dll/REL/m511Dll/player` | 1,660 |
| 99.75% | `playRounds__Q24m53211CGameMasterFv` | `m532Dll/REL/m532Dll/game_master` | 1,572 |
| 99.73% | `fn_1_2AD4` | `m548dll/REL/m548dll/game` | 1,480 |
| 99.72% | `fn_1_6E08` | `m518dll/REL/m518dll/m518` | 2,816 |
| 99.70% | `fn_1_730` | `m575dll/REL/m575dll/m575` | 1,324 |
| 99.67% | `__ct__Q24m5175CBallFi` | `m517Dll/REL/m517Dll/effect` | 1,228 |
| 99.67% | `__ct__Q24m5225CSoloFi` | `m522Dll/REL/m522Dll/player` | 1,212 |
| 99.67% | `procMain__Q24m5136CHeihoFv` | `m513Dll/REL/m513Dll/heiho` | 1,204 |
| 99.65% | `__ct__Q24m5177CPlayerFi` | `m517Dll/REL/m517Dll/player` | 2,264 |
| 99.62% | `fn_1_BDA4` | `m562dll/REL/m562dll/koopa` | 4,204 |
| 99.61% | `fn_1_C538` | `sdroomdll/REL/sdroomdll/garage` | 6,148 |
| 99.61% | `ObjectSetup` | `sdroomdll/REL/sdroomdll/sdroom` | 1,020 |
| 99.61% | `fn_1_4114` | `mgmatchDll/REL/mgmatchDll/mgmatch` | 9,116 |
| 99.59% | `fn_1_4D48` | `m542dll/REL/m542dll/game` | 984 |
| 99.59% | `fn_1_4900` | `m523Dll/REL/m523Dll/player` | 972 |
| 99.59% | `PushOthers__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 968 |
| 99.57% | `BlockPlayerProc` | `partyresultdll/REL/partyresultdll/result` | 940 |
| 99.57% | `fn_1_2244` | `m563dll/REL/m563dll/m563` | 1,876 |
| 99.57% | `UpdateBite__Q24m5799CFishLineFv` | `m579Dll/REL/m579Dll/fishline` | 928 |
| 99.57% | `fn_1_EE4C` | `m565dll/REL/m565dll/ending` | 3,696 |
| 99.57% | `fn_1_13C1C` | `mgmatchDll/REL/mgmatchDll/score` | 1,844 |
| 99.55% | `procRecover__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 896 |
| 99.53% | `QuatRotArc__4m568FP10QuaternionPC3VecPC3Vec` | `m568Dll/REL/m568Dll/misc` | 860 |
| 99.52% | `MB5Ev_Rocket` | `w05sDll/REL/w05sDll/world05` | 5,836 |
| 99.51% | `__ct__Q24m5135CLeafFiP3VecP3Vec` | `m513Dll/REL/m513Dll/leaf` | 816 |
| 99.51% | `fn_1_3D50` | `m533dll/REL/m533dll/m533` | 816 |
| 99.51% | `__ct__Q24m5685CTubeFii` | `m568Dll/REL/m568Dll/tube` | 812 |
| 99.50% | `StatScorePosSet` | `partyresultdll/REL/partyresultdll/stat` | 1,616 |
| 99.50% | `M550ObjCreate` | `m550dll/REL/m550dll/m550` | 2,408 |
| 99.49% | `__ct__Q24m5796CJugemFv` | `m579Dll/REL/m579Dll/zako` | 788 |
| 99.49% | `fn_1_2DF0` | `m572dll/REL/m572dll/m572` | 780 |
| 99.48% | `fn_1_4334` | `m540Dll/REL/m540Dll/m540` | 2,312 |
| 99.48% | `fn_1_8DF0` | `m523Dll/REL/m523Dll/player` | 764 |
| 99.47% | `DVDConvertPathToEntrynum` | `main/dolphin/dvd/dvdfs` | 756 |
| 99.45% | `UpdateMain__Q24m5117CPlayerFPQ24m5117CPlayer` | `m511Dll/REL/m511Dll/player` | 728 |
| 99.45% | `__ct__Q24m5137CPlayerFib` | `m513Dll/REL/m513Dll/player` | 1,456 |
| 99.45% | `__ct__Q24m5396CScoreFi` | `m539Dll/REL/m539Dll/score` | 1,456 |
| 99.40% | `OSGetResetButtonState` | `main/dolphin/os/OSResetSW` | 664 |
| 99.39% | `QuatGetAxis__4m513FP3VecPC10Quaternioni` | `m513Dll/REL/m513Dll/misc` | 656 |
| 99.39% | `QuatGetAxis__4m517FP3VecPC10Quaternioni` | `m517Dll/REL/m517Dll/misc` | 656 |
| 99.39% | `QuatGetAxis__4m568FP3VecPC10Quaternioni` | `m568Dll/REL/m568Dll/misc` | 656 |
| 99.38% | `Update__Q24m5179CInputComFv` | `m517Dll/REL/m517Dll/input` | 644 |
| 99.37% | `avoidObstacle__Q24m56813CInputComTeamFPQ34m5686CInput4DataPQ24m5685CTube` | `m568Dll/REL/m568Dll/input` | 636 |
| 99.37% | `erase__Q210Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>FQ310Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>13__iterator<0>Q310Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>13__iterator<0>` | `m537Dll/REL/m537Dll/player` | 1,268 |
| 99.37% | `erase__Q210Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>FQ310Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>Q310Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>` | `m521Dll/REL/m521Dll/driver` | 1,268 |
| 99.36% | `fn_1_10D4` | `m508Dll/REL/m508Dll/m508` | 1,248 |
| 99.33% | `fn_1_6A30` | `m542dll/REL/m542dll/game` | 2,380 |
| 99.32% | `fn_1_290BC` | `carddll/REL/carddll/player` | 592 |
| 99.32% | `Update__Q24m51713CInputComSoloFv` | `m517Dll/REL/m517Dll/input` | 584 |
| 99.31% | `fn_1_5420` | `m542dll/REL/m542dll/game` | 2,320 |
| 99.29% | `UpdateCourse__Q24m5117CPlayerFv` | `m511Dll/REL/m511Dll/player` | 1,700 |
| 99.29% | `fn_1_2D3C` | `mdbeachDll/REL/mdbeachDll/mdbeach` | 1,132 |
| 99.29% | `fn_1_A3C` | `m508Dll/REL/m508Dll/m508` | 1,688 |
| 99.28% | `fn_1_5D30` | `m542dll/REL/m542dll/game` | 3,328 |
| 99.28% | `fn_1_3674` | `m534Dll/REL/m534Dll/stage` | 1,108 |
| 99.27% | `fn_1_29DC` | `m551Dll/REL/m551Dll/m551` | 2,196 |
| 99.27% | `fn_1_15060` | `sdroomdll/REL/sdroomdll/garagesave` | 2,176 |
| 99.25% | `__ct__Q24m5129CHeihoManFv` | `m512Dll/REL/m512Dll/heiho` | 532 |
| 99.25% | `procJump__Q24m5795CPukuFv` | `m579Dll/REL/m579Dll/puku2` | 2,128 |
| 99.24% | `M550GameUnk49F0` | `m550dll/REL/m550dll/game` | 528 |
| 99.24% | `fn_1_6418` | `m569Dll/REL/m569Dll/kuribo` | 1,584 |
| 99.23% | `__ct__Q24m5327CMapManFv` | `m532Dll/REL/m532Dll/man_map` | 1,044 |
| 99.22% | `mcmdStartSample` | `main/musyx/runtime/synthmacros` | 512 |
| 99.21% | `fn_1_4B50` | `m542dll/REL/m542dll/game` | 504 |
| 99.19% | `fn_1_B614` | `mgwarsDll/REL/mgwarsDll/mgwars` | 2,952 |
| 99.18% | `fn_1_3700` | `m571dll/REL/m571dll/m571` | 488 |
| 99.17% | `MdOptionStoryRecordUpdate` | `mdoptionDll/REL/mdoptionDll/stage` | 1,932 |
| 99.17% | `proc_catch__Q24m5327CPlayerFv` | `m532Dll/REL/m532Dll/player` | 480 |
| 99.16% | `thread_exec__Q24m56811CGameMasterFi` | `m568Dll/REL/m568Dll/game_master` | 2,372 |
| 99.15% | `fn_1_4AB58` | `carddll/REL/carddll/status` | 3,304 |
| 99.13% | `fn_1_2908` | `m548dll/REL/m548dll/game` | 460 |
| 99.12% | `createMotions__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 456 |
| 99.12% | `procHold__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 456 |
| 99.10% | `checkEnd__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 444 |
| 99.09% | `GetTurnDir__Q24m5216CClockFi` | `m521Dll/REL/m521Dll/clock` | 876 |
| 99.09% | `ObjectSetup` | `storymodedll/REL/storymodedll/storymode` | 1,752 |
| 99.07% | `KillPlayers__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 432 |
| 99.07% | `fn_1_12934` | `mgmatchDll/REL/mgmatchDll/score` | 432 |
| 99.07% | `procLoseFall__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 428 |
| 99.05% | `GetTurnDist__Q24m5216CClockFi` | `m521Dll/REL/m521Dll/clock` | 840 |
| 99.03% | `M524WeightFall` | `m524Dll/REL/m524Dll/m524` | 828 |
| 99.03% | `fn_1_1A958` | `sdroomdll/REL/sdroomdll/picture` | 3,304 |
| 99.01% | `M550GameUnk4C00` | `m550dll/REL/m550dll/game` | 404 |
| 99.00% | `msmSysGroupInit` | `main/msm/msmsys` | 804 |
| 99.00% | `fn_1_1C0` | `m554dll/REL/m554dll/m554` | 1,608 |
| 99.00% | `fn_1_17A28` | `m562dll/REL/m562dll/mini_mechakoopa` | 2,004 |
| 99.00% | `mcmdPlayMacro` | `main/musyx/runtime/synthmacros` | 396 |
| 98.98% | `__ct__Q24m5397CMapManFv` | `m539Dll/REL/m539Dll/man_map` | 1,176 |
| 98.97% | `fn_1_1B294` | `mdoptionDll/REL/mdoptionDll/record` | 388 |
| 98.97% | `setStartPos__Q24m5687CPlayerFff` | `m568Dll/REL/m568Dll/player` | 388 |
| 98.96% | `FindObstacle__Q24m56813CInputComTeamFP3VecPC3Vec` | `m568Dll/REL/m568Dll/input` | 384 |
| 98.96% | `fn_1_5120` | `m542dll/REL/m542dll/game` | 768 |
| 98.95% | `KillPlayers__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 380 |
| 98.94% | `SetStartPos__Q24m5177CPlayerFff` | `m517Dll/REL/m517Dll/player` | 376 |
| 98.94% | `showRecord__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 376 |
| 98.92% | `MB3Ev_RollRock` | `w03Dll/REL/w03Dll/world03` | 2,232 |
| 98.91% | `fn_1_CA4` | `carddll/REL/carddll/cardmain` | 13,640 |
| 98.91% | `fn_1_A64` | `m554dll/REL/m554dll/m554` | 1,104 |
| 98.89% | `on_setup__Q24m56811CGameMasterFP9Process_s` | `m568Dll/REL/m568Dll/game_master` | 360 |
| 98.88% | `DuckAll__Q24m5179CChoroManFv` | `m517Dll/REL/m517Dll/choro` | 356 |
| 98.88% | `stateDuckIntro__Q24m5179CChoroManFv` | `m517Dll/REL/m517Dll/choro` | 356 |
| 98.86% | `fn_1_162C` | `m547dll/REL/m547dll/m547` | 1,404 |
| 98.86% | `fn_1_19A98` | `m562dll/REL/m562dll/firering` | 3,152 |
| 98.84% | `M524PlayerMain` | `m524Dll/REL/m524Dll/m524` | 344 |
| 98.82% | `nearest__Q24m56813CInputComSoloFPC3Vec` | `m568Dll/REL/m568Dll/input` | 340 |
| 98.82% | `snd_handle_irq` | `main/musyx/runtime/hardware` | 340 |
| 98.78% | `M538Unk765C` | `m538Dll/REL/m538Dll/m538` | 328 |
| 98.78% | `result__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 328 |
| 98.77% | `__ct__Q24m5136CHeihoFi` | `m513Dll/REL/m513Dll/heiho` | 652 |
| 98.75% | `MgCameraMoveEntry` | `m523Dll/REL/m523Dll/m523` | 316 |
| 98.75% | `MgCameraMoveEntry` | `m524Dll/REL/m524Dll/m524` | 316 |
| 98.75% | `MgCameraMoveEntry` | `m530Dll/REL/m530Dll/m530` | 316 |
| 98.75% | `MgCameraMoveEntry` | `m564Dll/REL/m564Dll/m564` | 316 |
| 98.75% | `MgCameraMoveEntry` | `m569Dll/REL/m569Dll/m569` | 316 |
| 98.75% | `MgCameraMoveEntry` | `m570Dll/REL/m570Dll/m570` | 316 |
| 98.74% | `fn_1_8150` | `storymodedll/REL/storymodedll/opening` | 2,532 |
| 98.73% | `fn_1_3110` | `m516Dll/REL/m516Dll/player` | 1,572 |
| 98.71% | `fn_1_359C` | `m563dll/REL/m563dll/m563` | 1,240 |
| 98.67% | `createMotions__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 300 |
| 98.66% | `fn_1_9984` | `mgmatchDll/REL/mgmatchDll/mgmatch` | 2,976 |
| 98.65% | `fn_1_4AA0` | `m548dll/REL/m548dll/game` | 1,188 |
| 98.65% | `M550Unk719C` | `m550dll/REL/m550dll/stage` | 2,660 |
| 98.63% | `on_new_mode__Q24m5686CStageFi` | `m568Dll/REL/m568Dll/stage` | 288 |
| 98.63% | `__ct__Q24m5217CPlayerFii` | `m521Dll/REL/m521Dll/player` | 1,164 |
| 98.62% | `MB4_CoinUpdate` | `w04Dll/REL/w04Dll/world04` | 2,604 |
| 98.62% | `MB4_CoinUpdate` | `w04sDll/REL/w04sDll/world04` | 2,604 |
| 98.60% | `fn_1_3270` | `m551Dll/REL/m551Dll/m551` | 2,280 |
| 98.57% | `fn_1_37B0` | `m542dll/REL/m542dll/game` | 560 |
| 98.55% | `createMotions__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 276 |
| 98.53% | `fn_1_16350` | `m562dll/REL/m562dll/fire` | 1,904 |
| 98.52% | `fn_1_6BE4` | `m575dll/REL/m575dll/com` | 1,896 |
| 98.51% | `M550ItemPosUpdate` | `m550dll/REL/m550dll/m550` | 536 |
| 98.48% | `fn_1_39E0` | `m542dll/REL/m542dll/game` | 1,576 |
| 98.46% | `checkEnd__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 260 |
| 98.46% | `M550ItemPosUpdateOne` | `m550dll/REL/m550dll/m550` | 520 |
| 98.44% | `MgCameraAngleGet` | `m523Dll/REL/m523Dll/m523` | 1,028 |
| 98.44% | `MgCameraAngleGet` | `m524Dll/REL/m524Dll/m524` | 1,028 |
| 98.44% | `MgCameraAngleGet` | `m530Dll/REL/m530Dll/m530` | 1,028 |
| 98.44% | `MgCameraAngleGet` | `m564Dll/REL/m564Dll/m564` | 1,028 |
| 98.44% | `MgCameraAngleGet` | `m569Dll/REL/m569Dll/m569` | 1,028 |
| 98.44% | `MgCameraAngleGet` | `m570Dll/REL/m570Dll/m570` | 1,028 |
| 98.44% | `__VIInit` | `main/dolphin/vi/vi` | 512 |
| 98.41% | `CreateAll__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 252 |
| 98.41% | `M529PlayerScoreBandUpdate` | `m529dll/REL/m529dll/m529` | 252 |
| 98.41% | `setResult__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 252 |
| 98.40% | `M573PreWinnerHook` | `m573dll/REL/m573dll/m573` | 752 |
| 98.40% | `aramInit` | `main/musyx/runtime/hw_aramdma` | 740 |
| 98.39% | `__init__Q23std36__vector_pod<c,Q23std12allocator<c>>FUlRCc` | `m579Dll/REL/m579Dll/watereff` | 248 |
| 98.36% | `MgDebugCameraMain` | `m524Dll/REL/m524Dll/m524` | 1,460 |
| 98.35% | `fn_1_3DCC` | `m548dll/REL/m548dll/game` | 2,188 |
| 98.35% | `fn_1_1980` | `m545Dll/REL/m545Dll/m545` | 972 |
| 98.35% | `fn_1_FADC` | `m505Dll/REL/m505Dll/m505` | 7,028 |
| 98.34% | `fn_1_118E8` | `m504dll/REL/m504dll/ending` | 4,088 |
| 98.33% | `M570CrowdIdleSet` | `m570Dll/REL/m570Dll/player` | 236 |
| 98.33% | `setMotion__Q24m52211CPlayerBaseFUlb` | `m522Dll/REL/m522Dll/player` | 240 |
| 98.31% | `fn_1_22694` | `m562dll/REL/m562dll/light` | 5,668 |
| 98.29% | `MB4_CoinInit` | `w04Dll/REL/w04Dll/world04` | 468 |
| 98.29% | `MB4_CoinInit` | `w04sDll/REL/w04sDll/world04` | 468 |
| 98.28% | `M538Unk77A4` | `m538Dll/REL/m538Dll/m538` | 232 |
| 98.28% | `checkRecord__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 232 |
| 98.28% | `fn_1_737C` | `m542dll/REL/m542dll/game` | 928 |
| 98.26% | `fn_1_48B4` | `mgtourDll/REL/mgtourDll/mgtournament` | 3,212 |
| 98.26% | `on_update__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 688 |
| 98.25% | `fn_1_8F1C` | `m567Dll/REL/m567Dll/m567` | 916 |
| 98.25% | `MgDebugCameraMain` | `m523Dll/REL/m523Dll/m523` | 1,144 |
| 98.25% | `MgDebugCameraMain` | `m530Dll/REL/m530Dll/m530` | 1,144 |
| 98.25% | `MgDebugCameraMain` | `m564Dll/REL/m564Dll/m564` | 1,144 |
| 98.25% | `MgDebugCameraMain` | `m569Dll/REL/m569Dll/m569` | 1,144 |
| 98.25% | `MgDebugCameraMain` | `m570Dll/REL/m570Dll/m570` | 1,144 |
| 98.25% | `GetData__Q24m5688CArchiveFPCc` | `m568Dll/REL/m568Dll/archive` | 228 |
| 98.25% | `setResult__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 228 |
| 98.21% | `IsGoal__4m568Fv` | `m568Dll/REL/m568Dll/game_master` | 224 |
| 98.21% | `salExitDspCtrl` | `main/musyx/runtime/hw_dspctrl` | 224 |
| 98.18% | `DrawObj__Q24m5225CFireFiPA4_fPA4_fPPQ24m5224Tile` | `m522Dll/REL/m522Dll/fire` | 1,320 |
| 98.16% | `SdStageMachineCol` | `sd00dll/REL/sd00dll/stage` | 4,572 |
| 98.16% | `fn_1_E2D4` | `m519dll/REL/m519dll/m519` | 1,088 |
| 98.16% | `updateShot__Q24m5367CPlayerFv` | `m536Dll/REL/m536Dll/player` | 2,172 |
| 98.15% | `fn_1_6590` | `m545Dll/REL/m545Dll/game` | 216 |
| 98.15% | `SdSeqMachineUpdate` | `sd00dll/REL/sd00dll/sd00` | 3,020 |
| 98.14% | `fn_1_3904` | `m518dll/REL/m518dll/m518` | 3,440 |
| 98.11% | `FindPublic__Q24m5688CArchiveFPCc` | `m568Dll/REL/m568Dll/archive` | 212 |
| 98.11% | `fn_1_4534` | `mgwarsDll/REL/mgwarsDll/mgwars` | 1,060 |
| 98.09% | `procFinished__Q24m5137CPlayerFv` | `m513Dll/REL/m513Dll/player` | 628 |
| 98.09% | `procTimeout__Q24m5137CPlayerFv` | `m513Dll/REL/m513Dll/player` | 628 |
| 98.08% | `SetAllIdle__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 208 |
| 98.08% | `SetAllIntro__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 208 |
| 98.08% | `SetAllPlay__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 208 |
| 98.08% | `setSuper__Q24m5016CJointFPQ24m5016CJoint` | `m501Dll/REL/m501Dll/joint` | 208 |
| 98.07% | `on_update__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 828 |
| 98.00% | `PlayLoseVoice__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 200 |
| 97.98% | `M506PlayerUpdate` | `m506Dll/REL/m506Dll/player` | 396 |
| 97.96% | `fn_1_A3C4` | `m535Dll/REL/m535Dll/m535` | 3,928 |
| 97.96% | `IsAllOut__4m568Fv` | `m568Dll/REL/m568Dll/game_master` | 196 |
| 97.88% | `procReturnSolo__Q24m5177CPlayerFv` | `m517Dll/REL/m517Dll/player` | 1,888 |
| 97.87% | `on_new_mode__Q24m5129CHeihoManFi` | `m512Dll/REL/m512Dll/heiho` | 184 |
| 97.87% | `StartAll__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 376 |
| 97.85% | `pushOut__Q24m5097CPlayerFffffii` | `m509Dll/REL/m509Dll/player` | 744 |
| 97.85% | `Draw__Q24m5797CRippleFPA3_A4_f` | `m579Dll/REL/m579Dll/water` | 1,116 |
| 97.83% | `fn_1_A524` | `mgmatchDll/REL/mgmatchDll/mgmatch` | 3,508 |
| 97.83% | `LoadMotion__Q24m5377CDorrieFv` | `m537Dll/REL/m537Dll/dorrie` | 184 |
| 97.83% | `cheerHeiho__Q24m5137CPlayerFv` | `m513Dll/REL/m513Dll/player` | 184 |
| 97.83% | `EscapeDir__Q24m56813CInputComTeamFUlff` | `m568Dll/REL/m568Dll/input` | 368 |
| 97.81% | `MB2_YajiUpdate` | `w02sDll/REL/w02sDll/world02` | 548 |
| 97.80% | `AIInit` | `main/dolphin/ai/ai` | 364 |
| 97.79% | `updateModel__Q24m5795CPukuFv` | `m579Dll/REL/m579Dll/puku2` | 544 |
| 97.79% | `BonusFadeEffHook` | `partyresultdll/REL/partyresultdll/result` | 2,720 |
| 97.79% | `fn_1_3AE4` | `m553Dll/REL/m553Dll/game` | 9,600 |
| 97.78% | `FindSoloTube__Q24m56813CInputComTeamFv` | `m568Dll/REL/m568Dll/input` | 180 |
| 97.78% | `giveLeaf__Q24m5136CHeihoFv` | `m513Dll/REL/m513Dll/heiho` | 180 |
| 97.78% | `on_update__Q24m56811CGameMasterFv` | `m568Dll/REL/m568Dll/game_master` | 540 |
| 97.73% | `IsAllIdle__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 176 |
| 97.73% | `IsAllIdle__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 176 |
| 97.73% | `MB7Ev_HouPlayerUpdate` | `w07Dll/REL/w07Dll/world07` | 880 |
| 97.71% | `HitHands__Q24m5216CClockFPC3VecP3VecPf` | `m521Dll/REL/m521Dll/clock` | 1,048 |
| 97.70% | `M550ItemPosSet` | `m550dll/REL/m550dll/m550` | 348 |
| 97.69% | `fn_1_227A4` | `carddll/REL/carddll/player` | 11,424 |
| 97.67% | `resetBeat__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 172 |
| 97.67% | `updateKuribo__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 344 |
| 97.67% | `__ct__Q24m5797CPlayerFi` | `m579Dll/REL/m579Dll/player` | 1,200 |
| 97.66% | `MB7Ev_HouPlayerUpdate` | `w07sDll/REL/w07sDll/world07` | 856 |
| 97.63% | `update__Q24m5396CScoreFv` | `m539Dll/REL/m539Dll/score` | 1,180 |
| 97.62% | `M538Unk7F04` | `m538Dll/REL/m538Dll/m538` | 168 |
| 97.62% | `__ct__Q24m5688CArchiveFi` | `m568Dll/REL/m568Dll/archive` | 168 |
| 97.62% | `fn_1_6924` | `storymodedll/REL/storymodedll/opening` | 168 |
| 97.56% | `KillChoros__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 164 |
| 97.56% | `KillEffects__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 164 |
| 97.56% | `KillHeihos__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 164 |
| 97.56% | `KillKuribos__Q24m51311CGameMasterFv` | `m513Dll/REL/m513Dll/gamemaster` | 164 |
| 97.52% | `M529DebugFreeCameraMain` | `m529dll/REL/m529dll/m529` | 960 |
| 97.52% | `fn_1_A6B0` | `m543Dll/REL/m543Dll/game` | 11,608 |
| 97.50% | `FinishAll__Q24m51711CGameMasterFv` | `m517Dll/REL/m517Dll/gamemaster` | 160 |
| 97.47% | `__OSInitSram` | `main/dolphin/os/OSRtc` | 316 |
| 97.46% | `fn_1_5CCC` | `m554dll/REL/m554dll/game` | 1,572 |
| 97.44% | `ResCardSpotUpdate` | `rescardDll/REL/rescardDll/rescard` | 10,008 |
| 97.44% | `GetPublicData__Q24m5688CArchiveFi` | `m568Dll/REL/m568Dll/archive` | 156 |
| 97.44% | `fn_1_6F5C` | `storymodedll/REL/storymodedll/opening` | 156 |
| 97.37% | `MB2Ev_HatenaTaiyo` | `w02sDll/REL/w02sDll/world02` | 6,836 |
| 97.36% | `M560PlayerMain` | `m560dll/REL/m560dll/m560` | 1,516 |
| 97.33% | `selectTarget__Q24m56813CInputComSoloFPC3Vec` | `m568Dll/REL/m568Dll/input` | 748 |
| 97.30% | `setSuperJoint__Q24m5016CJointFPQ24m5016CJoint` | `m501Dll/REL/m501Dll/joint` | 148 |
| 97.27% | `__ct__Q24m5397CEffectFP3Vec` | `m539Dll/REL/m539Dll/effect` | 440 |
| 97.26% | `__ct__Q24m5687CPlayerFi` | `m568Dll/REL/m568Dll/player` | 1,608 |
| 97.24% | `initRipple__Q24m5319CCleanEffFv` | `m531Dll/REL/m531Dll/cleaneff` | 580 |
| 97.24% | `Rotate__Q24m5216CClockFif` | `m521Dll/REL/m521Dll/clock` | 1,160 |
| 97.22% | `fn_1_30FC` | `m572dll/REL/m572dll/m572` | 428 |
| 97.20% | `hwSetADSR` | `main/musyx/runtime/hardware` | 428 |
| 97.17% | `fn_1_1BA0` | `m571dll/REL/m571dll/m571` | 420 |
| 97.14% | `DVDReadPrio` | `main/dolphin/dvd/dvdfs` | 280 |
| 97.14% | `procControl__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 840 |
| 97.12% | `M506ScoreCreate` | `m506Dll/REL/m506Dll/object` | 548 |
| 97.12% | `procReturnTeam__Q24m5177CPlayerFv` | `m517Dll/REL/m517Dll/player` | 1,668 |
| 97.11% | `fn_1_7014` | `m520Dll/REL/m520Dll/m520` | 2,076 |
| 97.10% | `M529DebugModelCacheGet` | `m529dll/REL/m529dll/m529` | 276 |
| 97.09% | `MB2Ev_Rainbow` | `w02Dll/REL/w02Dll/world02` | 4,536 |
| 97.08% | `MB2_YajiUpdate` | `w02Dll/REL/w02Dll/world02` | 548 |
| 97.08% | `fn_1_3D40` | `m516Dll/REL/m516Dll/player` | 1,368 |
| 97.06% | `StageKinokoUpdate` | `sd00dll/REL/sd00dll/stage` | 3,540 |
| 97.06% | `MgPadStkAngleGet` | `m523Dll/REL/m523Dll/m523` | 272 |
| 97.06% | `MgPadStkAngleGet` | `m524Dll/REL/m524Dll/m524` | 272 |
| 97.06% | `MgPadStkAngleGet` | `m530Dll/REL/m530Dll/m530` | 272 |
| 97.06% | `MgPadStkAngleGet` | `m564Dll/REL/m564Dll/m564` | 272 |
| 97.06% | `MgPadStkAngleGet` | `m569Dll/REL/m569Dll/m569` | 272 |
| 97.06% | `MgPadStkAngleGet` | `m570Dll/REL/m570Dll/m570` | 272 |
| 97.02% | `MB2_ParticleCreate` | `w02Dll/REL/w02Dll/world02` | 1,208 |
| 97.02% | `MB2_ParticleCreate` | `w02sDll/REL/w02sDll/world02` | 1,208 |
| 97.01% | `fn_1_2AD0` | `m542dll/REL/m542dll/game` | 268 |
| 97.00% | `DoCrossTalk` | `main/musyx/runtime/StdReverb/reverb` | 388 |
| 96.99% | `fn_1_3B98` | `m508Dll/REL/m508Dll/m508` | 1,464 |
| 96.97% | `on_update__Q24m5126CScoreFv` | `m512Dll/REL/m512Dll/score` | 1,056 |
| 96.96% | `fn_1_60F8` | `m567Dll/REL/m567Dll/m567` | 2,236 |
| 96.94% | `StaffMain` | `staffDll/REL/staffDll/staff` | 8,500 |
| 96.93% | `InsertData` | `main/musyx/runtime/s_data` | 652 |
| 96.88% | `OSExceptionInit` | `main/dolphin/os/OS` | 640 |
| 96.88% | `sort<PQ23std9pair<i,i>,PFRCQ23std9pair<i,i>RCQ23std9pair<i,i>_b>__3stdFPQ23std9pair<i,i>PQ23std9pair<i,i>PFRCQ23std9pair<i,i>RCQ23std9pair<i,i>_b` | `m539Dll/REL/m539Dll/game_master` | 1,152 |
| 96.84% | `fn_1_7C88` | `m548dll/REL/m548dll/stage` | 2,276 |
| 96.84% | `fn_1_94C8` | `m545Dll/REL/m545Dll/stage` | 2,276 |
| 96.84% | `fn_1_A124` | `m547dll/REL/m547dll/stage` | 2,276 |
| 96.84% | `fn_1_BEDC` | `m544Dll/REL/m544Dll/stage` | 2,276 |
| 96.84% | `fn_1_CE14` | `m546Dll/REL/m546Dll/stage` | 2,276 |
| 96.84% | `fn_1_3EEC` | `m567Dll/REL/m567Dll/m567` | 632 |
| 96.83% | `fn_1_A5C` | `m559dll/REL/m559dll/m559` | 1,260 |
| 96.79% | `fn_1_108DC` | `m580Dll/REL/m580Dll/score` | 872 |
| 96.77% | `fn_1_9350` | `m572dll/REL/m572dll/m572` | 124 |
| 96.75% | `fn_1_13B1C` | `sdroomdll/REL/sdroomdll/garagesave` | 492 |
| 96.73% | `insert__Q23std60__vector_pod<Q24m5225Flare,Q23std24allocator<Q24m5225Flare>>FPQ24m5225FlareUlRCQ24m5225Flare` | `m522Dll/REL/m522Dll/fire` | 2,936 |
| 96.71% | `fn_1_5DC` | `m502dll/REL/m502dll/m502` | 2,556 |
| 96.68% | `StageKinokoCheck` | `sd00dll/REL/sd00dll/stage` | 2,292 |
| 96.67% | `fn_1_6C0C` | `m518dll/REL/m518dll/m518` | 240 |
| 96.65% | `SIInterruptHandler` | `main/dolphin/si/SIBios` | 836 |
| 96.64% | `UpdateFish__Q24m5799CFishLineFv` | `m579Dll/REL/m579Dll/fishline` | 596 |
| 96.57% | `move__Q24m5097CPlayerFP3Vec` | `m509Dll/REL/m509Dll/player` | 932 |
| 96.53% | `stateFly__Q24m5367CKillerFv` | `m536Dll/REL/m536Dll/killer` | 1,152 |
| 96.51% | `updateModel__Q24m5687CPlayerFv` | `m568Dll/REL/m568Dll/player` | 688 |
| 96.51% | `on_hook__Q24m5319CConfettiFPA4_f` | `m531Dll/REL/m531Dll/polish` | 1,260 |
| 96.44% | `proc_throw__Q24m5327CPlayerFv` | `m532Dll/REL/m532Dll/player` | 900 |
| 96.43% | `fn_1_111B8` | `m540Dll/REL/m540Dll/m540` | 672 |
| 96.40% | `on_hook__Q24m5318CSparkleFPA4_f` | `m531Dll/REL/m531Dll/polish` | 1,444 |
| 96.40% | `__assign<PC3Vec>__Q23std42__vector_pod<3Vec,Q23std15allocator<3Vec>>FPC3VecPC3VecQ23std20forward_iterator_tag` | `m522Dll/REL/m522Dll/fire` | 888 |
| 96.35% | `MB2Ev_Rainbow` | `w02sDll/REL/w02sDll/world02` | 4,056 |
| 96.32% | `getComInput__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 652 |
| 96.30% | `OSLoadContext` | `main/dolphin/os/OSContext` | 216 |
| 96.30% | `fn_1_5AB0` | `m554dll/REL/m554dll/game` | 540 |
| 96.30% | `procPlay__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 756 |
| 96.27% | `on_hook__Q24m5316CSprayFPA4_f` | `m531Dll/REL/m531Dll/polish` | 644 |
| 96.27% | `MB4Ev_Iruka` | `w04sDll/REL/w04sDll/world04` | 4,820 |
| 96.26% | `updateReel__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 856 |
| 96.25% | `UpdateShadow__Q24m5686CStageFv` | `m568Dll/REL/m568Dll/stage` | 640 |
| 96.23% | `move__Q24m5797CPlayerFP3Vec` | `m579Dll/REL/m579Dll/player` | 956 |
| 96.23% | `assign__Q23std42__vector_pod<3Vec,Q23std15allocator<3Vec>>FUlRC3Vec` | `m522Dll/REL/m522Dll/fire` | 848 |
| 96.22% | `procPlay__Q24m5097CPlayerFv` | `m509Dll/REL/m509Dll/player` | 740 |
| 96.21% | `PResStatRankTeamCreate` | `partyresultdll/REL/partyresultdll/stat` | 2,744 |
| 96.19% | `proc_enterLand__Q24m5397CPlayerFv` | `m539Dll/REL/m539Dll/player` | 420 |
| 96.18% | `__SITransfer` | `main/dolphin/si/SIBios` | 524 |
| 96.18% | `fn_1_1ED4` | `m514Dll/REL/m514Dll/player` | 524 |
| 96.14% | `fn_1_1B1C` | `m559dll/REL/m559dll/m559` | 1,036 |
| 96.09% | `procReel__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 1,228 |
| 96.09% | `M573Unk12B8` | `m573dll/REL/m573dll/m573` | 1,124 |
| 96.07% | `SdStageRandomPosGet` | `sd00dll/REL/sd00dll/stage` | 1,936 |
| 96.06% | `fn_1_5CB8` | `m523Dll/REL/m523Dll/player` | 1,320 |
| 96.06% | `ResultBonusExec` | `partyresultdll/REL/partyresultdll/result` | 7,608 |
| 96.04% | `burn__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 808 |
| 96.03% | `fn_1_13A24` | `m562dll/REL/m562dll/koopaboss` | 504 |
| 96.03% | `fn_1_2D88` | `mdstoryDll/REL/mdstoryDll/mdstory` | 1,712 |
| 96.02% | `MB3_ObjectCreate` | `w03Dll/REL/w03Dll/world03` | 1,708 |
| 96.00% | `on_update__Q24m5216CScoreFv` | `m521Dll/REL/m521Dll/score` | 800 |
| 96.00% | `fn_1_4A88` | `mdoptionDll/REL/mdoptionDll/mdoption` | 2,200 |
| 95.92% | `procWin__Q24m5097CPlayerFv` | `m509Dll/REL/m509Dll/player` | 784 |
| 95.89% | `fn_1_32C` | `m567Dll/REL/m567Dll/m567` | 3,212 |
| 95.83% | `DVDReadAsyncPrio` | `main/dolphin/dvd/dvdfs` | 192 |
| 95.83% | `fn_1_383C` | `m574Dll/REL/m574Dll/stage` | 480 |
| 95.81% | `updateDisp__Q24m5116CScoreFPQ34m5116CScore5Entry` | `m511Dll/REL/m511Dll/score` | 764 |
| 95.76% | `fn_1_CB8` | `storymodedll/REL/storymodedll/storymode` | 472 |
| 95.76% | `fn_1_2994` | `mgmatchDll/REL/mgmatchDll/mgmatch` | 1,508 |
| 95.74% | `procFinishReel__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 1,128 |
| 95.68% | `SdStageCreate` | `sd00dll/REL/sd00dll/stage` | 3,056 |
| 95.67% | `result__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 832 |
| 95.65% | `MgAngleApproach` | `m523Dll/REL/m523Dll/m523` | 368 |
| 95.65% | `MgAngleApproach` | `m524Dll/REL/m524Dll/m524` | 368 |
| 95.65% | `MgAngleApproach` | `m530Dll/REL/m530Dll/m530` | 368 |
| 95.65% | `MgAngleApproach` | `m564Dll/REL/m564Dll/m564` | 368 |
| 95.65% | `MgAngleApproach` | `m569Dll/REL/m569Dll/m569` | 368 |
| 95.65% | `MgAngleApproach` | `m570Dll/REL/m570Dll/m570` | 368 |
| 95.62% | `fn_1_E7B4` | `m518dll/REL/m518dll/m518` | 548 |
| 95.62% | `procPlay__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 548 |
| 95.56% | `proc00__Q24m52111CDriverAsAIFRQ34m5217CDriver4INFO` | `m521Dll/REL/m521Dll/driver` | 360 |
| 95.54% | `fn_1_4D28` | `m574Dll/REL/m574Dll/stage` | 448 |
| 95.52% | `diff__Q24m5226CAngleFff` | `m522Dll/REL/m522Dll/player` | 536 |
| 95.52% | `diff__Q24m5326CAngleFff` | `m532Dll/REL/m532Dll/player` | 536 |
| 95.52% | `diff__Q24m5376CAngleFff` | `m537Dll/REL/m537Dll/player` | 536 |
| 95.38% | `MgCameraAngleApply` | `m523Dll/REL/m523Dll/m523` | 1,732 |
| 95.38% | `MgCameraAngleApply` | `m524Dll/REL/m524Dll/m524` | 1,732 |
| 95.38% | `MgCameraAngleApply` | `m530Dll/REL/m530Dll/m530` | 1,732 |
| 95.38% | `MgCameraAngleApply` | `m564Dll/REL/m564Dll/m564` | 1,732 |
| 95.38% | `MgCameraAngleApply` | `m569Dll/REL/m569Dll/m569` | 1,732 |
| 95.38% | `MgCameraAngleApply` | `m570Dll/REL/m570Dll/m570` | 1,732 |
| 95.35% | `fn_1_E90C` | `m549Dll/REL/m549Dll/game` | 1,980 |
| 95.35% | `MgDebugCameraCreate` | `m523Dll/REL/m523Dll/m523` | 172 |
| 95.35% | `MgDebugCameraCreate` | `m524Dll/REL/m524Dll/m524` | 172 |
| 95.35% | `MgDebugCameraCreate` | `m530Dll/REL/m530Dll/m530` | 172 |
| 95.35% | `MgDebugCameraCreate` | `m564Dll/REL/m564Dll/m564` | 172 |
| 95.35% | `MgDebugCameraCreate` | `m569Dll/REL/m569Dll/m569` | 172 |
| 95.35% | `MgDebugCameraCreate` | `m570Dll/REL/m570Dll/m570` | 172 |
| 95.35% | `cbForStateError` | `main/dolphin/dvd/dvd` | 172 |
| 95.35% | `SteerAround__Q24m56813CInputComTeamFPQ34m5686CInput4DataPQ24m5685CTubePQ24m5685CTube` | `m568Dll/REL/m568Dll/input` | 344 |
| 95.35% | `__iter__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>CFUl` | `m521Dll/REL/m521Dll/driver` | 344 |
| 95.35% | `__iter__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>FUl` | `m521Dll/REL/m521Dll/driver` | 344 |
| 95.32% | `on_update__Q24m5366CScoreFv` | `m536Dll/REL/m536Dll/score` | 684 |
| 95.29% | `CompleteTransfer` | `main/dolphin/si/SIBios` | 764 |
| 95.24% | `on_new_mode__Q24m5099CStartSprFi` | `m509Dll/REL/m509Dll/startspr` | 80 |
| 95.22% | `on_hook__Q24m53110CLandSmokeFPA4_f` | `m531Dll/REL/m531Dll/polish` | 1,256 |
| 95.20% | `macStart` | `main/musyx/runtime/synthmacros` | 1,080 |
| 95.19% | `getMoveDir__Q24m5017CPlayerFP3Vec` | `m501Dll/REL/m501Dll/player` | 1,664 |
| 95.19% | `macHandleActive` | `main/musyx/runtime/synthmacros` | 3,988 |
| 95.18% | `__iter__Q23std35__deque_imp<b,Q23std12allocator<b>>CFUl` | `m537Dll/REL/m537Dll/player` | 332 |
| 95.18% | `__iter__Q23std35__deque_imp<b,Q23std12allocator<b>>FUl` | `m537Dll/REL/m537Dll/player` | 332 |
| 95.16% | `M550GameUnk4898` | `m550dll/REL/m550dll/game` | 248 |
| 95.15% | `fn_1_2A3C` | `mdcardDll/REL/mdcardDll/mdcard` | 6,844 |
| 95.12% | `hwGetPos` | `main/musyx/runtime/hardware` | 164 |
| 95.12% | `fn_1_3A44` | `m508Dll/REL/m508Dll/m508` | 328 |
| 95.12% | `PushOut__Q24m5216CClockFP3Vec` | `m521Dll/REL/m521Dll/clock` | 1,148 |
| 95.06% | `Launch__Q24m5795CPukuFb` | `m579Dll/REL/m579Dll/puku2` | 324 |
| 95.06% | `update__Q24m5225CFireFv` | `m522Dll/REL/m522Dll/fire` | 324 |
| 95.06% | `M524PlayerInit` | `m524Dll/REL/m524Dll/m524` | 648 |
| 95.01% | `fn_1_9BC8` | `mgwarsDll/REL/mgwarsDll/mgwars` | 6,732 |
| 94.94% | `GetStartPos__Q24m5797CPlayerFP3Veci` | `m579Dll/REL/m579Dll/player` | 316 |
| 94.89% | `fn_1_B668` | `m553Dll/REL/m553Dll/game` | 4,072 |
| 94.89% | `ResCardFlowDraw` | `rescardDll/REL/rescardDll/rescard` | 548 |
| 94.84% | `proc_main__Q24m5127CPlayerFv` | `m512Dll/REL/m512Dll/player` | 1,008 |
| 94.84% | `CheckFall__Q24m5377CPlayerFPQ24m5377CPlayer` | `m537Dll/REL/m537Dll/player` | 852 |
| 94.74% | `cbForStateMotorStopped` | `main/dolphin/dvd/dvd` | 228 |
| 94.69% | `mode0__Q24m5315CFlowFv` | `m531Dll/REL/m531Dll/flow` | 2,108 |
| 94.63% | `fn_1_4A3C` | `m534Dll/REL/m534Dll/stage` | 4,392 |
| 94.62% | `updatePath__Q24m5327CPlayerFv` | `m532Dll/REL/m532Dll/player` | 520 |
| 94.62% | `fn_1_4DB4` | `m516Dll/REL/m516Dll/stage` | 1,040 |
| 94.55% | `update__Q24m5685CTubeFv` | `m568Dll/REL/m568Dll/tube` | 1,028 |
| 94.52% | `fn_1_15D40` | `m562dll/REL/m562dll/fire` | 1,240 |
| 94.51% | `salInitDspCtrl` | `main/musyx/runtime/hw_dspctrl` | 948 |
| 94.50% | `fn_1_D58` | `m571dll/REL/m571dll/m571` | 800 |
| 94.50% | `hwInitSamplePlayback` | `main/musyx/runtime/hardware` | 436 |
| 94.47% | `insert__Q210Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>FQ310Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>13__iterator<0>UlRCPb` | `m537Dll/REL/m537Dll/player` | 4,052 |
| 94.47% | `insert__Q210Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>FQ310Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>UlRCPQ34m52111CDriverAsAI4Node` | `m521Dll/REL/m521Dll/driver` | 4,052 |
| 94.46% | `fn_1_11658` | `mdminiDll/REL/mdminiDll/mdmini` | 13,132 |
| 94.43% | `M506ParticleUpdate` | `m506Dll/REL/m506Dll/object` | 1,580 |
| 94.36% | `proc02__Q24m52111CDriverAsAIFRQ34m5217CDriver4INFO` | `m521Dll/REL/m521Dll/driver` | 780 |
| 94.35% | `get__Q24m56813CInputComTeamFPQ34m5686CInput4DataPQ24m5685CTube` | `m568Dll/REL/m568Dll/input` | 1,204 |
| 94.34% | `M538Unk94DC` | `m538Dll/REL/m538Dll/m538` | 1,832 |
| 94.33% | `procOut__Q24m5177CPlayerFv` | `m517Dll/REL/m517Dll/player` | 1,552 |
| 94.32% | `stateIdle__Q24m5217CPlayerFv` | `m521Dll/REL/m521Dll/player` | 352 |
| 94.32% | `fn_1_11F88` | `m580Dll/REL/m580Dll/reflect` | 704 |
| 94.32% | `fn_1_8C94` | `m574Dll/REL/m574Dll/collide` | 704 |
| 94.32% | `hwSetVolume` | `main/musyx/runtime/hardware` | 704 |
| 94.29% | `__dt__Q23std57__vector_base<9HuVec2f_s,Q23std21allocator<9HuVec2f_s>,0>Fv` | `m501Dll/REL/m501Dll/player` | 140 |
| 94.29% | `setMotion__Q24m5127CPlayerFib` | `m512Dll/REL/m512Dll/player` | 280 |
| 94.29% | `OSDumpStopwatch` | `main/dolphin/os/OSStopwatch` | 420 |
| 94.29% | `__ct__Q24m5226CFlareFP3Vecffi` | `m522Dll/REL/m522Dll/fire` | 560 |
| 94.21% | `fn_1_91A8` | `mgfreeDll/REL/mgfreeDll/decide` | 2,488 |
| 94.20% | `procEnter__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 1,104 |
| 94.20% | `fn_1_85AC` | `m504dll/REL/m504dll/player` | 1,172 |
| 94.17% | `procFall__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 480 |
| 94.12% | `stateCoverClosed` | `main/dolphin/dvd/dvd` | 204 |
| 94.12% | `diff__Q24m5377CAngleDFdd` | `m537Dll/REL/m537Dll/dorrie` | 408 |
| 94.12% | `sort<PUi>__3stdFPUiPUi` | `m521Dll/REL/m521Dll/gamemaster` | 612 |
| 94.12% | `sort<PUi>__3stdFPUiPUi` | `m531Dll/REL/m531Dll/flow` | 612 |
| 94.08% | `Update__Q24m5217CPlayerFv` | `m521Dll/REL/m521Dll/player` | 1,352 |
| 94.07% | `MB2Ev_Zen2` | `w02Dll/REL/w02Dll/world02` | 7,144 |
| 94.03% | `M550StageModelCreate` | `m550dll/REL/m550dll/stage` | 2,076 |
| 93.94% | `on_new_mode__Q24m5016CStageFi` | `m501Dll/REL/m501Dll/stage` | 124 |
| 93.94% | `on_new_mode__Q24m52211CSunFireManFi` | `m522Dll/REL/m522Dll/sunfire` | 124 |
| 93.94% | `on_new_mode__Q24m53210CObjectManFi` | `m532Dll/REL/m532Dll/man_object` | 124 |
| 93.88% | `ARInit` | `main/dolphin/ar/ar` | 196 |
| 93.88% | `hwInit` | `main/musyx/runtime/hardware` | 196 |
| 93.75% | `IsPressA__Q24m5377CPlayerFi` | `m537Dll/REL/m537Dll/player` | 64 |
| 93.75% | `setMotion__Q24m5377CPlayerFib` | `m537Dll/REL/m537Dll/player` | 256 |
| 93.75% | `SetPos__Q24m5175CBallFPC3Vec` | `m517Dll/REL/m517Dll/effect` | 320 |
| 93.70% | `procIdle__Q24m5225CSoloFv` | `m522Dll/REL/m522Dll/player` | 1,016 |
| 93.65% | `fn_1_21AC` | `mgfreeDll/REL/mgfreeDll/mgfree` | 2,708 |
| 93.65% | `M538Unk7FAC` | `m538Dll/REL/m538Dll/m538` | 1,448 |
| 93.60% | `MB4Ev_Blow` | `w04Dll/REL/w04Dll/world04` | 4,752 |
| 93.58% | `fn_1_CDD8` | `m549Dll/REL/m549Dll/game` | 748 |
| 93.56% | `procIntro__Q24m5177CPlayerFv` | `m517Dll/REL/m517Dll/player` | 2,732 |
| 93.55% | `on_new_mode__Q24m5095CMazeFi` | `m509Dll/REL/m509Dll/maze` | 116 |
| 93.55% | `__PADDisableRecalibration` | `main/dolphin/pad/Pad` | 124 |
| 93.52% | `fn_1_3438` | `mdstoryDll/REL/mdstoryDll/mdstory` | 2,036 |
| 93.44% | `fn_1_3C2C` | `mdstoryDll/REL/mdstoryDll/mdstory` | 2,744 |
| 93.42% | `on_update__Q24m5095CMazeFv` | `m509Dll/REL/m509Dll/maze` | 1,276 |
| 93.41% | `SLSaveSdBExec` | `main/game/saveload` | 2,308 |
| 93.33% | `getInput__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 240 |
| 93.33% | `pop_front__Q23std35__deque_imp<b,Q23std12allocator<b>>Fv` | `m537Dll/REL/m537Dll/player` | 300 |
| 93.33% | `updateDisp__Q24m5126CScoreFPQ34m5126CScore5Entry` | `m512Dll/REL/m512Dll/score` | 480 |
| 93.33% | `__ct__Q24m5224CSunFv` | `m522Dll/REL/m522Dll/fire` | 540 |
| 93.27% | `stateIntro__Q24m5179CChoroManFv` | `m517Dll/REL/m517Dll/choro` | 892 |
| 93.27% | `setVerticalRegs` | `main/dolphin/vi/vi` | 416 |
| 93.27% | `M529AuxControllerInit` | `m529dll/REL/m529dll/m529` | 824 |
| 93.27% | `fn_1_2A14` | `m571dll/REL/m571dll/m571` | 832 |
| 93.26% | `PathCheck` | `w04Dll/REL/w04Dll/world04` | 1,424 |
| 93.24% | `UnlockSram` | `main/dolphin/os/OSRtc` | 828 |
| 93.19% | `__add_back__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>FUlRQ210Metrowerks80cdeque<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>RUlUl` | `m521Dll/REL/m521Dll/driver` | 1,644 |
| 93.17% | `__add_back__Q23std35__deque_imp<b,Q23std12allocator<b>>FUlRQ210Metrowerks32cdeque<Pb,Q23std13allocator<Pb>>RUlUl` | `m537Dll/REL/m537Dll/player` | 1,640 |
| 93.16% | `updateDisp__Q24m5216CScoreFPQ34m5216CScore5Entry` | `m521Dll/REL/m521Dll/score` | 468 |
| 93.16% | `updateDisp__Q24m5366CScoreFPQ34m5366CScore5Entry` | `m536Dll/REL/m536Dll/score` | 468 |
| 93.06% | `Update__Q24m5395CDrumFv` | `m539Dll/REL/m539Dll/drum` | 288 |
| 93.01% | `procFinish__Q24m5797CPlayerFv` | `m579Dll/REL/m579Dll/player` | 916 |
| 92.86% | `ARQInit` | `main/dolphin/ar/arq` | 112 |
| 92.86% | `Project__Q24m5686CStageFP3VecPC3Vec` | `m568Dll/REL/m568Dll/stage` | 168 |
| 92.86% | `update__Q24m5396CHeihoFv` | `m539Dll/REL/m539Dll/heiho` | 784 |
| 92.83% | `DrawOctNode__Q24m5686CStageFPCQ24m5687OctNode` | `m568Dll/REL/m568Dll/stage` | 892 |
| 92.78% | `M560PlayerBurn` | `m560dll/REL/m560dll/m560` | 720 |
| 92.78% | `fn_1_5038` | `m559dll/REL/m559dll/m559` | 720 |
| 92.70% | `fn_1_39A8` | `m535Dll/REL/m535Dll/m535` | 6,736 |
| 92.47% | `NarrowHook__Q24m5225CTeamFP16ColNarrowParam_sP16ColNarrowParam_s` | `m522Dll/REL/m522Dll/player` | 372 |
| 92.47% | `get__Q24m56813CInputComSoloFPQ34m5686CInput4DataPQ24m5685CTube` | `m568Dll/REL/m568Dll/input` | 372 |
| 92.44% | `Init__Q24m5688CArchiveFPvi` | `m568Dll/REL/m568Dll/archive` | 476 |
| 92.34% | `MB7Ev_KoopaWalkUpdate` | `w07Dll/REL/w07Dll/world07` | 5,052 |
| 92.31% | `fn_1_245C` | `m534Dll/REL/m534Dll/player` | 780 |
| 92.16% | `MgPlayerConfSet` | `m523Dll/REL/m523Dll/m523` | 204 |
| 92.16% | `MgPlayerConfSet` | `m524Dll/REL/m524Dll/m524` | 204 |
| 92.16% | `MgPlayerConfSet` | `m530Dll/REL/m530Dll/m530` | 204 |
| 92.16% | `MgPlayerConfSet` | `m564Dll/REL/m564Dll/m564` | 204 |
| 92.16% | `MgPlayerConfSet` | `m569Dll/REL/m569Dll/m569` | 204 |
| 92.16% | `MgPlayerConfSet` | `m570Dll/REL/m570Dll/m570` | 204 |
| 92.13% | `PlaySe__Q24m57910CCameraObjFP3Veci` | `m579Dll/REL/m579Dll/camera` | 356 |
| 92.07% | `streamHandle` | `main/musyx/runtime/stream` | 2,220 |
| 92.07% | `fn_1_3A1C` | `m559dll/REL/m559dll/m559` | 908 |
| 92.06% | `s3dKillEmitterByFXID` | `main/musyx/runtime/snd3d` | 252 |
| 91.82% | `DVDCancelAsync` | `main/dolphin/dvd/dvd` | 636 |
| 91.82% | `StartPlayerWin__Q24m5017CPlayerFv` | `m501Dll/REL/m501Dll/player` | 636 |
| 91.81% | `M570FadeInHook` | `m570Dll/REL/m570Dll/m570` | 1,368 |
| 91.71% | `fn_1_566C` | `m540Dll/REL/m540Dll/m540` | 2,848 |
| 91.62% | `__ct__Q24m5377CPlayerFiPQ24m5377CDorrie` | `m537Dll/REL/m537Dll/player` | 664 |
| 91.59% | `GetStickData__Q24m5017CPlayerFPcPccc` | `m501Dll/REL/m501Dll/player` | 1,332 |
| 91.58% | `fn_1_6AA0` | `m504dll/REL/m504dll/player` | 3,184 |
| 91.55% | `Undo` | `main/dolphin/os/OSLink` | 568 |
| 91.49% | `proc_debug__Q24m53610CCameraObjFv` | `m536Dll/REL/m536Dll/camera` | 188 |
| 91.46% | `CheckAisu__Q24m5017CPlayerFPQ24m5017CPlayer` | `m501Dll/REL/m501Dll/player` | 328 |
| 91.45% | `fn_1_5D40` | `m563dll/REL/m563dll/m563` | 468 |
| 91.45% | `MdModelCreate` | `mdoptionDll/REL/mdoptionDll/stage` | 4,164 |
| 91.45% | `__ct__Q24m53211CRefereeManFv` | `m532Dll/REL/m532Dll/man_referee` | 608 |
| 91.43% | `IsApproaching__Q24m5216CClockFii` | `m521Dll/REL/m521Dll/clock` | 832 |
| 91.43% | `fn_1_AC4` | `m562dll/REL/m562dll/main` | 1,260 |
| 91.41% | `Spawn__Q24m5179CChoroManFv` | `m517Dll/REL/m517Dll/choro` | 792 |
| 91.35% | `PathCheck` | `w02Dll/REL/w02Dll/world02` | 740 |
| 91.33% | `fn_1_8D58` | `m514Dll/REL/m514Dll/score` | 692 |
| 91.30% | `sndEmitterVoiceID` | `main/musyx/runtime/snd3d` | 92 |
| 91.30% | `fn_1_D2A4` | `m503Dll/REL/m503Dll/score` | 552 |
| 91.23% | `fn_1_2253C` | `m562dll/REL/m562dll/light` | 228 |
| 91.21% | `fn_1_EF4C` | `m580Dll/REL/m580Dll/score` | 364 |
| 91.18% | `procFall__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 544 |
| 91.06% | `mode3__Q24m5315CFlowFv` | `m531Dll/REL/m531Dll/flow` | 492 |
| 91.03% | `M524PlayerModeWin` | `m524Dll/REL/m524Dll/m524` | 312 |
| 90.97% | `StageTrialDistCalc` | `sd00dll/REL/sd00dll/stage` | 576 |
| 90.97% | `__ct__Q24m5799CWaterEffFv` | `m579Dll/REL/m579Dll/watereff` | 576 |
| 90.91% | `hwSetPolyPhaseFilter` | `main/musyx/runtime/hardware` | 44 |
| 90.91% | `hwSetSRCType` | `main/musyx/runtime/hardware` | 44 |
| 90.81% | `MdOptionStoryTotalRecordUpdate` | `mdoptionDll/REL/mdoptionDll/stage` | 1,916 |
| 90.79% | `M524FlowPlay` | `m524Dll/REL/m524Dll/m524` | 304 |
| 90.79% | `MB7Ev_KoopaCube` | `w07Dll/REL/w07Dll/world07` | 5,428 |
| 90.70% | `fn_1_9080` | `m540Dll/REL/m540Dll/m540` | 4,080 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m509Dll/REL/m509Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m511Dll/REL/m511Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m512Dll/REL/m512Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m513Dll/REL/m513Dll/heiho` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m517Dll/REL/m517Dll/kuribo` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m521Dll/REL/m521Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m522Dll/REL/m522Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m532Dll/REL/m532Dll/man_referee` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m536Dll/REL/m536Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m537Dll/REL/m537Dll/dorrie` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m539Dll/REL/m539Dll/player` | 944 |
| 90.68% | `insert__Q23std36__vector_pod<s,Q23std12allocator<s>>FPsUlRCs` | `m579Dll/REL/m579Dll/player` | 944 |
| 90.65% | `fn_1_32D0` | `m559dll/REL/m559dll/m559` | 1,412 |
| 90.65% | `fn_1_53F8` | `m535Dll/REL/m535Dll/m535` | 13,560 |
| 90.62% | `M570CrowdCreate` | `m570Dll/REL/m570Dll/player` | 764 |
| 90.62% | `fn_1_4ED4` | `m523Dll/REL/m523Dll/player` | 1,492 |
| 90.60% | `M538Unk4714` | `m538Dll/REL/m538Dll/m538` | 596 |
| 90.59% | `Reposition__Q24m5377CPlayerFv` | `m537Dll/REL/m537Dll/player` | 340 |
| 90.58% | `fn_1_3DA8` | `m559dll/REL/m559dll/m559` | 764 |
| 90.57% | `M524FlowExit` | `m524Dll/REL/m524Dll/m524` | 416 |
| 90.57% | `ShadowSetup__FsP3VecP3Vecff` | `m532Dll/REL/m532Dll/m532` | 636 |
| 90.57% | `ShadowSetup__FsP3VecP3Vecff` | `m539Dll/REL/m539Dll/m539` | 636 |
| 90.52% | `__ct__Q24m5139CTaimatsuFP3Vec` | `m513Dll/REL/m513Dll/taimatsu` | 464 |
| 90.48% | `sndRemoveEmitter` | `main/musyx/runtime/snd3d` | 168 |
| 90.39% | `M538Unk4F74` | `m538Dll/REL/m538Dll/m538` | 1,620 |
| 90.39% | `fn_1_B600` | `m540Dll/REL/m540Dll/m540` | 1,748 |
| 90.29% | `fn_1_2160` | `mdoptionDll/REL/mdoptionDll/mdoption` | 3,008 |
| 90.20% | `PlayDamageSound` | `sd00dll/REL/sd00dll/sd00` | 204 |
| 90.17% | `fn_1_FDB0` | `m549Dll/REL/m549Dll/game` | 6,136 |
| 90.13% | `fn_1_13D08` | `sdroomdll/REL/sdroomdll/garagesave` | 2,756 |
| 90.06% | `ResCardFlowWin` | `rescardDll/REL/rescardDll/rescard` | 1,288 |
| 90.00% | `hwKeyOff` | `main/musyx/runtime/hardware` | 40 |
| 90.00% | `hwSetPitch` | `main/musyx/runtime/hardware` | 120 |
| 90.00% | `MB2_SplashEffCreateRandX` | `w02Dll/REL/w02Dll/world02` | 600 |
| 90.00% | `MB2_SplashEffCreateRandX` | `w02sDll/REL/w02sDll/world02` | 600 |
| 89.95% | `fn_1_7710` | `m504dll/REL/m504dll/player` | 3,740 |
| 89.74% | `sndInit` | `main/musyx/runtime/snd_init` | 288 |
| 89.74% | `MoveSolo__Q24m5177CPlayerF3Vec` | `m517Dll/REL/m517Dll/player` | 1,208 |
| 89.72% | `fn_1_E98` | `m574Dll/REL/m574Dll/player` | 428 |
| 89.67% | `fn_1_2C74` | `m540Dll/REL/m540Dll/m540` | 4,260 |
| 89.66% | `steer__Q24m5227CComPadFP3Vec` | `m522Dll/REL/m522Dll/player` | 580 |
| 89.62% | `fn_1_2290` | `m534Dll/REL/m534Dll/player` | 424 |
| 89.44% | `msmStreamPauseOff` | `main/msm/msmstream` | 720 |
| 89.39% | `Change__Q24m52111CDriverAsAIFMQ24m52111CDriverAsAIFPCvPvRQ34m5217CDriver4INFO_v` | `m521Dll/REL/m521Dll/driver` | 264 |
| 89.36% | `M538FinishHook` | `m538Dll/REL/m538Dll/m538` | 564 |
| 89.29% | `OSCheckStopwatch` | `main/dolphin/os/OSStopwatch` | 112 |
| 89.29% | `fn_1_1058` | `mdcardDll/REL/mdcardDll/mdcard` | 1,008 |
| 89.23% | `CheckImpact__Q24m5176CChoroFv` | `m517Dll/REL/m517Dll/choro` | 520 |
| 88.98% | `fn_1_1E6A8` | `sdroomdll/REL/sdroomdll/tournament` | 472 |
| 88.89% | `__init_hardware` | `main/dolphin/os/__ppc_eabi_init` | 36 |
| 88.84% | `MBCapsuleKettouExec` | `main/game/board/capmain` | 18,356 |
| 88.73% | `fn_1_4554` | `m565dll/REL/m565dll/stage` | 1,420 |
| 88.63% | `sndPushGroup` | `main/musyx/runtime/s_data` | 844 |
| 88.61% | `__ct__Q24m52111CDriverAsAIFPQ24m5217CPlayer` | `m521Dll/REL/m521Dll/driver` | 304 |
| 88.51% | `__start` | `main/dolphin/os/__start` | 348 |
| 88.40% | `fn_1_7FD8` | `m574Dll/REL/m574Dll/collide` | 724 |
| 88.31% | `VIConfigure` | `main/dolphin/vi/vi` | 2,088 |
| 88.24% | `on_new_mode__Q24m5126CScoreFi` | `m512Dll/REL/m512Dll/score` | 60 |
| 88.24% | `on_new_mode__Q24m5366CScoreFi` | `m536Dll/REL/m536Dll/score` | 60 |
| 88.24% | `fn_1_17C` | `m547dll/REL/m547dll/m547` | 2,312 |
| 88.10% | `fn_1_9798` | `m523Dll/REL/m523Dll/player` | 336 |
| 88.09% | `__ct__Q24m5137CKuriboFP3VecP3Vec` | `m513Dll/REL/m513Dll/kuribo` | 940 |
| 87.93% | `fn_1_46A8` | `m508Dll/REL/m508Dll/m508` | 232 |
| 87.93% | `fn_1_479C` | `m508Dll/REL/m508Dll/m508` | 232 |
| 87.79% | `MB3Ev_Turuhasi` | `w03Dll/REL/w03Dll/world03` | 4,552 |
| 87.78% | `M538Unk4968` | `m538Dll/REL/m538Dll/m538` | 720 |
| 87.76% | `DSPInit` | `main/dolphin/dsp/dsp` | 196 |
| 87.75% | `fn_1_6DA4` | `m523Dll/REL/m523Dll/player` | 1,012 |
| 87.66% | `M524CoinCreate` | `m524Dll/REL/m524Dll/m524` | 616 |
| 87.61% | `draw__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 452 |
| 87.59% | `MgVecOrbit` | `m523Dll/REL/m523Dll/m523` | 568 |
| 87.59% | `MgVecOrbit` | `m524Dll/REL/m524Dll/m524` | 568 |
| 87.59% | `MgVecOrbit` | `m530Dll/REL/m530Dll/m530` | 568 |
| 87.59% | `MgVecOrbit` | `m564Dll/REL/m564Dll/m564` | 568 |
| 87.59% | `MgVecOrbit` | `m569Dll/REL/m569Dll/m569` | 568 |
| 87.59% | `MgVecOrbit` | `m570Dll/REL/m570Dll/m570` | 568 |
| 87.53% | `ResCardDrawStarUpdate` | `rescardDll/REL/rescardDll/rescard` | 3,968 |
| 87.51% | `MB4_SakanaDraw` | `w04Dll/REL/w04Dll/world04` | 5,892 |
| 87.51% | `MB4_SakanaDraw` | `w04sDll/REL/w04sDll/world04` | 5,892 |
| 87.50% | `hwSetVirtualSampleLoopBuffer` | `main/musyx/runtime/hardware` | 32 |
| 87.50% | `sndCheckEmitter` | `main/musyx/runtime/snd3d` | 32 |
| 87.50% | `salDeactivateVoice` | `main/musyx/runtime/hw_dspctrl` | 96 |
| 87.50% | `salActivateVoice` | `main/musyx/runtime/hw_dspctrl` | 160 |
| 87.50% | `stateBusy` | `main/dolphin/dvd/dvd` | 800 |
| 87.43% | `Relocate` | `main/dolphin/os/OSLink` | 700 |
| 87.38% | `fn_1_CEBC` | `m502dll/REL/m502dll/bat` | 4,056 |
| 87.29% | `fn_1_ADDC` | `m549Dll/REL/m549Dll/game` | 4,440 |
| 87.20% | `pop_back__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>Fv` | `m521Dll/REL/m521Dll/driver` | 500 |
| 87.10% | `ObjectSetup` | `m524Dll/REL/m524Dll/m524` | 712 |
| 87.06% | `M506PlayerModeFall` | `m506Dll/REL/m506Dll/player` | 4,044 |
| 87.03% | `proc_winner_move__Q24m5017CPlayerFv` | `m501Dll/REL/m501Dll/player` | 1,388 |
| 86.86% | `msmStreamSlotInit` | `main/msm/msmstream` | 548 |
| 86.84% | `CountGrounded__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 152 |
| 86.82% | `__ct__Q24m51311CLeafEffectFP3Vec` | `m513Dll/REL/m513Dll/leaf` | 516 |
| 86.73% | `fn_1_1448` | `mdcardDll/REL/mdcardDll/mdcard` | 2,472 |
| 86.67% | `hwStart` | `main/musyx/runtime/hardware` | 60 |
| 86.67% | `GXSetChanAmbColor` | `main/dolphin/gx/GXLight` | 240 |
| 86.67% | `GXSetChanMatColor` | `main/dolphin/gx/GXLight` | 240 |
| 86.61% | `fn_1_2FE0` | `m571dll/REL/m571dll/m571` | 1,344 |
| 86.54% | `M529StageJointMotionUpdate` | `m529dll/REL/m529dll/m529` | 416 |
| 86.52% | `fn_1_EA90` | `m576Dll/REL/m576Dll/score` | 564 |
| 86.48% | `fn_1_39DC` | `m523Dll/REL/m523Dll/player` | 1,420 |
| 86.44% | `GXSetIndTexOrder` | `main/dolphin/gx/GXBump` | 236 |
| 86.42% | `fn_1_C2CC` | `m540Dll/REL/m540Dll/m540` | 1,296 |
| 86.36% | `OSInitAlarm` | `main/dolphin/os/OSAlarm` | 88 |
| 86.36% | `msmStreamPackStartStereo` | `main/msm/msmstream` | 1,144 |
| 86.27% | `fn_1_2B90` | `m563dll/REL/m563dll/m563` | 204 |
| 86.14% | `fn_1_12404` | `mgmatchDll/REL/mgmatchDll/score` | 1,328 |
| 86.08% | `M560KupaVolGet` | `m560dll/REL/m560dll/m560` | 316 |
| 86.05% | `fn_1_153A4` | `m562dll/REL/m562dll/fire` | 344 |
| 85.97% | `movePlayer__Q24m5017CPlayerFP3Vec` | `m501Dll/REL/m501Dll/player` | 1,996 |
| 85.96% | `M524PlayerPrizeCreate` | `m524Dll/REL/m524Dll/m524` | 228 |
| 85.83% | `M538Unk4534` | `m538Dll/REL/m538Dll/m538` | 480 |
| 85.71% | `DVDLowClearCallback` | `main/dolphin/dvd/dvdlow` | 28 |
| 85.61% | `fn_1_1668` | `m559dll/REL/m559dll/m559` | 556 |
| 85.33% | `fn_1_90EC` | `m523Dll/REL/m523Dll/player` | 300 |
| 85.08% | `fn_1_1394` | `m559dll/REL/m559dll/m559` | 724 |
| 85.03% | `M550CharModelCreate` | `m550dll/REL/m550dll/stage` | 668 |
| 85.00% | `hwBreak` | `main/musyx/runtime/hardware` | 80 |
| 84.96% | `fn_1_2D68` | `m535Dll/REL/m535Dll/m535` | 452 |
| 84.95% | `msmStreamPackStartMono` | `main/msm/msmstream` | 744 |
| 84.91% | `GetObjPos__Q24m5377CDorrieFiP3Vec` | `m537Dll/REL/m537Dll/dorrie` | 212 |
| 84.91% | `MgFlowEntry` | `m523Dll/REL/m523Dll/m523` | 212 |
| 84.91% | `MgFlowEntry` | `m524Dll/REL/m524Dll/m524` | 212 |
| 84.91% | `MgFlowEntry` | `m530Dll/REL/m530Dll/m530` | 212 |
| 84.91% | `MgFlowEntry` | `m564Dll/REL/m564Dll/m564` | 212 |
| 84.91% | `MgFlowEntry` | `m569Dll/REL/m569Dll/m569` | 212 |
| 84.91% | `MgFlowEntry` | `m570Dll/REL/m570Dll/m570` | 212 |
| 84.85% | `hwRemoveSample` | `main/musyx/runtime/hardware` | 132 |
| 84.78% | `PADControlMotor` | `main/dolphin/pad/Pad` | 184 |
| 84.78% | `update__Q24m5227CBubbleFv` | `m522Dll/REL/m522Dll/bubble` | 552 |
| 84.76% | `StageTrialFloorCheck` | `sd00dll/REL/sd00dll/stage` | 656 |
| 84.73% | `Grow__Q24m5135CLeafFf` | `m513Dll/REL/m513Dll/leaf` | 2,096 |
| 84.44% | `M506MakeRotMtx` | `m506Dll/REL/m506Dll/object` | 180 |
| 84.42% | `fn_1_6168` | `m574Dll/REL/m574Dll/stage` | 308 |
| 84.22% | `procCom__Q24m5225CTeamFv` | `m522Dll/REL/m522Dll/player` | 1,724 |
| 84.13% | `__DVDInterruptHandler` | `main/dolphin/dvd/dvdlow` | 736 |
| 83.96% | `M573PlayerMain` | `m573dll/REL/m573dll/m573` | 1,264 |
| 83.93% | `fn_1_7198` | `m523Dll/REL/m523Dll/player` | 448 |
| 83.78% | `fn_1_73A8` | `sdroomdll/REL/sdroomdll/garage` | 4,956 |
| 83.72% | `fn_1_5B14` | `m563dll/REL/m563dll/m563` | 172 |
| 83.51% | `fn_1_1210` | `m559dll/REL/m559dll/m559` | 388 |
| 83.44% | `__VIRetraceHandler` | `main/dolphin/vi/vi` | 628 |
| 83.33% | `OSGetTime` | `main/dolphin/os/OSTime` | 24 |
| 83.10% | `fn_1_633C` | `m534Dll/REL/m534Dll/effect` | 284 |
| 83.10% | `fn_1_681C` | `m534Dll/REL/m534Dll/effect` | 284 |
| 82.79% | `M506FlowStopCheck` | `m506Dll/REL/m506Dll/object` | 488 |
| 82.61% | `GXSetChanCtrl` | `main/dolphin/gx/GXLight` | 184 |
| 82.59% | `fn_1_12940` | `sdroomdll/REL/sdroomdll/garage` | 3,400 |
| 82.51% | `DrawRibbon__Q24m5375CRopeFv` | `m537Dll/REL/m537Dll/center_obj` | 1,688 |
| 82.50% | `GetPan__4m532FP3Vec` | `m532Dll/REL/m532Dll/player` | 160 |
| 82.50% | `GetPan__4m537FP3Vec` | `m537Dll/REL/m537Dll/player` | 160 |
| 82.50% | `getVoicePan__Q24m5017CPlayerFP3Vec` | `m501Dll/REL/m501Dll/player` | 160 |
| 82.50% | `fn_1_52C4` | `m533dll/REL/m533dll/m533` | 640 |
| 82.26% | `M538Unk91D8` | `m538Dll/REL/m538Dll/m538` | 492 |
| 82.24% | `fn_1_F4A0` | `m549Dll/REL/m549Dll/game` | 2,320 |
| 82.24% | `M560BillPartEmit` | `m560dll/REL/m560dll/m560` | 608 |
| 82.24% | `fn_1_7C28` | `m559dll/REL/m559dll/m559` | 608 |
| 82.16% | `cbForStateBusy` | `main/dolphin/dvd/dvd` | 1,592 |
| 82.14% | `msmStreamGetStatus` | `main/msm/msmstream` | 224 |
| 82.13% | `MB4Ev_Iruka` | `w04Dll/REL/w04Dll/world04` | 5,640 |
| 81.88% | `SelectThread` | `main/dolphin/os/OSThread` | 552 |
| 81.63% | `M529DebugProjectXToRange` | `m529dll/REL/m529dll/m529` | 196 |
| 81.63% | `M529DebugProjectYToRange` | `m529dll/REL/m529dll/m529` | 196 |
| 81.58% | `VIGetCurrentLine` | `main/dolphin/vi/vi` | 152 |
| 81.51% | `ObjectSetup` | `mdomakeDll/REL/mdomakeDll/mdomake` | 1,748 |
| 81.40% | `__AIDHandler` | `main/dolphin/ai/ai` | 172 |
| 81.40% | `fn_1_15C` | `m548dll/REL/m548dll/m548` | 1,892 |
| 81.25% | `PADReceiveCheckCallback` | `main/dolphin/pad/Pad` | 320 |
| 81.08% | `fn_1_6E9C` | `mdbeachDll/REL/mdbeachDll/mdbeach` | 2,896 |
| 80.80% | `ObjectSetup` | `mdminiDll/REL/mdminiDll/mdmini` | 1,896 |
| 80.78% | `MB4Ev_Kihon` | `w04Dll/REL/w04Dll/world04` | 8,360 |
| 80.77% | `fn_1_7300` | `m553Dll/REL/m553Dll/game` | 104 |
| 80.67% | `MgCameraMoveMain` | `m523Dll/REL/m523Dll/m523` | 476 |
| 80.67% | `MgCameraMoveMain` | `m524Dll/REL/m524Dll/m524` | 476 |
| 80.67% | `MgCameraMoveMain` | `m530Dll/REL/m530Dll/m530` | 476 |
| 80.67% | `MgCameraMoveMain` | `m564Dll/REL/m564Dll/m564` | 476 |
| 80.67% | `MgCameraMoveMain` | `m569Dll/REL/m569Dll/m569` | 476 |
| 80.67% | `MgCameraMoveMain` | `m570Dll/REL/m570Dll/m570` | 476 |
| 80.65% | `fn_1_2280` | `m541Dll/REL/m541Dll/m541` | 248 |
| 80.65% | `fn_1_3350` | `m553Dll/REL/m553Dll/m553` | 248 |
| 80.65% | `fn_1_3558` | `m543Dll/REL/m543Dll/m543` | 248 |
| 80.65% | `fn_1_5860` | `m551Dll/REL/m551Dll/m551` | 248 |
| 80.56% | `fn_1_28F4` | `m571dll/REL/m571dll/m571` | 288 |
| 80.54% | `msmStreamDvdCallback` | `main/msm/msmstream` | 1,100 |
| 80.49% | `GetObjMtx__Q24m5377CDorrieFiPA4_f` | `m537Dll/REL/m537Dll/dorrie` | 164 |
| 80.39% | `fn_1_5BD4` | `m567Dll/REL/m567Dll/m567` | 816 |
| 80.30% | `M560BillPartCreate` | `m560dll/REL/m560dll/m560` | 264 |
| 80.30% | `fn_1_79C0` | `m559dll/REL/m559dll/m559` | 264 |
| 80.06% | `fn_1_6800` | `m523Dll/REL/m523Dll/player` | 1,444 |
| 80.00% | `hwGetSampleID` | `main/musyx/runtime/hardware` | 20 |
| 80.00% | `hwGetSampleType` | `main/musyx/runtime/hardware` | 20 |
| 80.00% | `hwGetVirtualSampleState` | `main/musyx/runtime/hardware` | 20 |
| 80.00% | `hwSetPriority` | `main/musyx/runtime/hardware` | 20 |
| 80.00% | `hwSetStreamLoopPS` | `main/musyx/runtime/hardware` | 20 |
| 80.00% | `OSStartStopwatch` | `main/dolphin/os/OSStopwatch` | 60 |
| 80.00% | `fn_1_B5F4` | `m553Dll/REL/m553Dll/game` | 96 |
| 80.00% | `GetStartPos__Q24m5097CPlayerFP3Veci` | `m509Dll/REL/m509Dll/player` | 160 |
| 80.00% | `M570ScoreWinCreate` | `m570Dll/REL/m570Dll/m570` | 380 |
| 79.93% | `SPEC2_MakeStatus` | `main/dolphin/pad/Pad` | 1,136 |
| 79.66% | `fn_1_9BC8` | `m575dll/REL/m575dll/tubo` | 708 |
| 79.48% | `M524PlayerModeWait` | `m524Dll/REL/m524Dll/m524` | 916 |
| 79.45% | `stateReady` | `main/dolphin/dvd/dvd` | 560 |
| 79.25% | `fn_1_1970` | `m551Dll/REL/m551Dll/m551` | 212 |
| 79.10% | `fn_1_69C` | `m535Dll/REL/m535Dll/m535` | 9,932 |
| 78.57% | `ICInvalidateRange` | `main/dolphin/os/OSCache` | 52 |
| 78.57% | `fn_1_F34` | `m523Dll/REL/m523Dll/m523` | 224 |
| 78.43% | `M570StageMotionSet` | `m570Dll/REL/m570Dll/player` | 204 |
| 78.21% | `fn_1_1474` | `m567Dll/REL/m567Dll/m567` | 7,768 |
| 78.10% | `IsPushSide__Q24m5216CClockFPC3Veci` | `m521Dll/REL/m521Dll/clock` | 1,224 |
| 78.05% | `fn_1_F0C8` | `m549Dll/REL/m549Dll/game` | 984 |
| 77.94% | `PADReset` | `main/dolphin/pad/Pad` | 272 |
| 77.78% | `__ct__Q24m5375CRopeFiPC3Vec` | `m537Dll/REL/m537Dll/center_obj` | 324 |
| 77.67% | `fn_1_762C` | `m549Dll/REL/m549Dll/game` | 1,684 |
| 77.66% | `M524PlayerOrderInit` | `m524Dll/REL/m524Dll/m524` | 368 |
| 77.59% | `removeOtherTargets__Q24m5017CPlayerFRQ23std30vector<i,Q23std12allocator<i>>` | `m501Dll/REL/m501Dll/player` | 232 |
| 77.42% | `Create__Q24m5399CModelManFUl` | `m539Dll/REL/m539Dll/drum` | 372 |
| 77.36% | `synthFXStart` | `main/musyx/runtime/synth` | 212 |
| 77.19% | `stateCheckID` | `main/dolphin/dvd/dvd` | 224 |
| 77.11% | `fn_1_A690` | `m525Dll/REL/m525Dll/m525` | 4,768 |
| 76.92% | `DCFlushRange` | `main/dolphin/os/OSCache` | 48 |
| 76.92% | `DCStoreRange` | `main/dolphin/os/OSCache` | 48 |
| 76.87% | `fn_1_280C8` | `m562dll/REL/m562dll/evt_koopagrow` | 7,472 |
| 76.83% | `MgCameraShakeMain` | `m523Dll/REL/m523Dll/m523` | 328 |
| 76.83% | `MgCameraShakeMain` | `m524Dll/REL/m524Dll/m524` | 328 |
| 76.83% | `MgCameraShakeMain` | `m530Dll/REL/m530Dll/m530` | 328 |
| 76.83% | `MgCameraShakeMain` | `m564Dll/REL/m564Dll/m564` | 328 |
| 76.83% | `MgCameraShakeMain` | `m569Dll/REL/m569Dll/m569` | 328 |
| 76.83% | `MgCameraShakeMain` | `m570Dll/REL/m570Dll/m570` | 328 |
| 76.65% | `fn_1_43F8` | `m551Dll/REL/m551Dll/m551` | 2,232 |
| 76.31% | `fn_1_2B280` | `carddll/REL/carddll/player` | 13,000 |
| 76.19% | `fn_1_AD78` | `m549Dll/REL/m549Dll/game` | 80 |
| 76.09% | `__sys_free` | `main/Runtime.PPCEABI.H/GCN_mem_alloc` | 184 |
| 76.03% | `msmSysLoadGroupSub` | `main/msm/msmsys` | 1,068 |
| 75.94% | `M524PlayerModeCrank` | `m524Dll/REL/m524Dll/m524` | 1,696 |
| 75.65% | `fn_1_7488` | `m523Dll/REL/m523Dll/player` | 460 |
| 75.53% | `M538Unk1DC8` | `m538Dll/REL/m538Dll/m538` | 3,008 |
| 75.34% | `fn_1_8948` | `m553Dll/REL/m553Dll/game` | 3,844 |
| 75.00% | `OSCreateAlarm` | `main/dolphin/os/OSAlarm` | 16 |
| 75.00% | `hwIsActive` | `main/musyx/runtime/hardware` | 32 |
| 75.00% | `hwVoiceInStartup` | `main/musyx/runtime/hardware` | 32 |
| 75.00% | `on_new_mode__Q24m5096CStageFi` | `m509Dll/REL/m509Dll/stage` | 40 |
| 75.00% | `on_new_mode__Q24m5126CStageFi` | `m512Dll/REL/m512Dll/stage` | 40 |
| 75.00% | `on_new_mode__Q24m5366CCloudFi` | `m536Dll/REL/m536Dll/stage` | 40 |
| 75.00% | `on_new_mode__Q24m5366CStageFi` | `m536Dll/REL/m536Dll/stage` | 40 |
| 75.00% | `DCFlushRangeNoSync` | `main/dolphin/os/OSCache` | 44 |
| 75.00% | `DCInvalidateRange` | `main/dolphin/os/OSCache` | 44 |
| 75.00% | `DCStoreRangeNoSync` | `main/dolphin/os/OSCache` | 44 |
| 75.00% | `DCZeroRange` | `main/dolphin/os/OSCache` | 44 |
| 75.00% | `GetAisuModel__Q24m50111CGameMasterFv` | `m501Dll/REL/m501Dll/gamemaster` | 48 |
| 75.00% | `GetConeModel__Q24m50111CGameMasterFv` | `m501Dll/REL/m501Dll/gamemaster` | 48 |
| 75.00% | `GXSetScissorBoxOffset` | `main/dolphin/gx/GXTransform` | 64 |
| 75.00% | `fn_1_AF64` | `m519dll/REL/m519dll/m519` | 160 |
| 74.83% | `DEMOInitCaption` | `main/dolphin/demo/DEMOPuts` | 604 |
| 74.72% | `push_back__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>FRCQ34m52111CDriverAsAI4Node` | `m521Dll/REL/m521Dll/driver` | 712 |
| 74.54% | `MB2Ev_Thunder` | `w02Dll/REL/w02Dll/world02` | 6,488 |
| 74.51% | `__ct__Q24m5689CObstacleFiPC3Vec` | `m568Dll/REL/m568Dll/octtree` | 408 |
| 74.19% | `M529DebugSequenceFadeOut` | `m529dll/REL/m529dll/m529` | 108 |
| 73.91% | `hwSetITDMode` | `main/musyx/runtime/hardware` | 92 |
| 72.73% | `PSQUATInverse` | `main/dolphin/mtx/quat` | 88 |
| 72.63% | `fn_1_85A8` | `m523Dll/REL/m523Dll/player` | 716 |
| 72.55% | `OSStopStopwatch` | `main/dolphin/os/OSStopwatch` | 204 |
| 72.41% | `sal_update_hostplayinfo` | `main/musyx/runtime/hw_dspctrl` | 116 |
| 72.41% | `M529DebugVecEase90` | `m529dll/REL/m529dll/m529` | 348 |
| 72.11% | `sndStreamFrq` | `main/musyx/runtime/stream` | 1,640 |
| 72.09% | `M570SePlay` | `m570Dll/REL/m570Dll/m570` | 172 |
| 72.00% | `fn_1_7674` | `m564Dll/REL/m564Dll/bomb` | 100 |
| 71.84% | `OSResetSystem` | `main/dolphin/os/OSReset` | 696 |
| 71.53% | `__GXInitGX` | `main/dolphin/gx/GXInit` | 2,360 |
| 71.43% | `msmStreamStopAll` | `main/msm/msmstream` | 180 |
| 71.40% | `GXInit` | `main/dolphin/gx/GXInit` | 1,944 |
| 70.85% | `fn_1_5558` | `mdminiDll/REL/mdminiDll/mdmini` | 6,752 |
| 70.59% | `PADOriginUpdateCallback` | `main/dolphin/pad/Pad` | 204 |
| 70.26% | `HandleDepopVoice` | `main/musyx/runtime/hw_dspctrl` | 780 |
| 70.21% | `fn_1_48F8` | `m566Dll/REL/m566Dll/m566` | 17,956 |
| 70.13% | `create__Q24m5399CModelManFUl` | `m539Dll/REL/m539Dll/drum` | 308 |
| 70.00% | `hwGetVirtualSampleID` | `main/musyx/runtime/hardware` | 40 |
| 69.64% | `synthStartSound` | `main/musyx/runtime/synth` | 1,120 |
| 69.41% | `AddStartingEmitter` | `main/musyx/runtime/snd3d` | 340 |
| 69.23% | `moveNode__Q24m5799CFishLineFiP3Vecf` | `m579Dll/REL/m579Dll/fishman` | 292 |
| 68.99% | `push_back__Q23std35__deque_imp<b,Q23std12allocator<b>>FRCb` | `m537Dll/REL/m537Dll/player` | 632 |
| 68.54% | `fn_1_7C84` | `m523Dll/REL/m523Dll/player` | 2,340 |
| 68.44% | `MB2Ev_Zen4` | `w02Dll/REL/w02Dll/world02` | 9,112 |
| 68.12% | `PADRecalibrate` | `main/dolphin/pad/Pad` | 276 |
| 68.03% | `M529PlayerInit` | `m529dll/REL/m529dll/m529` | 1,464 |
| 68.00% | `M506PointLerp` | `m506Dll/REL/m506Dll/object` | 100 |
| 67.89% | `OSInit` | `main/dolphin/os/OS` | 984 |
| 67.18% | `M538Unk32C4` | `m538Dll/REL/m538Dll/m538` | 1,816 |
| 66.67% | `aramRemoveData` | `main/musyx/runtime/hw_aramdma` | 24 |
| 66.67% | `__OSPSInit` | `main/dolphin/os/OS` | 84 |
| 66.67% | `DVDInit` | `main/dolphin/dvd/dvd` | 204 |
| 66.67% | `findDanger__Q24m5225CTeamFP3Vecf` | `m522Dll/REL/m522Dll/player` | 564 |
| 66.59% | `fn_1_38EC` | `m561dll/REL/m561dll/m561` | 6,824 |
| 66.58% | `fn_1_14350` | `mgmatchDll/REL/mgmatchDll/score` | 4,368 |
| 66.43% | `sndAddListenerEx` | `main/musyx/runtime/snd3d` | 544 |
| 66.17% | `MB2Ev_Rain` | `w02Dll/REL/w02Dll/world02` | 7,036 |
| 65.45% | `dataAddSampleReference` | `main/musyx/runtime/synthdata` | 220 |
| 65.06% | `Get__Q24m52111CDriverAsAIFRQ34m5217CDriver4INFO` | `m521Dll/REL/m521Dll/driver` | 1,248 |
| 64.97% | `msmSysLoadGroupBase` | `main/msm/msmsys` | 708 |
| 64.71% | `PSVECMag` | `main/dolphin/mtx/vec` | 68 |
| 64.13% | `fn_1_8954` | `sdroomdll/REL/sdroomdll/garage` | 5,720 |
| 64.08% | `M538Unk2CB8` | `m538Dll/REL/m538Dll/m538` | 1,548 |
| 63.67% | `VIInit` | `main/dolphin/vi/vi` | 1,200 |
| 63.40% | `fn_1_35A0` | `mdminiDll/REL/mdminiDll/mdmini` | 8,120 |
| 63.22% | `MB4Ev_Kaisoo` | `w04Dll/REL/w04Dll/world04` | 7,744 |
| 62.86% | `MB1_MainObjUpdate` | `w01sDll/REL/w01sDll/world01` | 140 |
| 61.70% | `fn_1_2F2C` | `m535Dll/REL/m535Dll/m535` | 2,684 |
| 61.66% | `fn_1_1D9F8` | `m562dll/REL/m562dll/firering` | 4,048 |
| 61.54% | `dataRemoveSampleReference` | `main/musyx/runtime/synthdata` | 156 |
| 61.29% | `proc_lose__Q24m5017CPlayerFv` | `m501Dll/REL/m501Dll/player` | 192 |
| 61.29% | `proc_win__Q24m5017CPlayerFv` | `m501Dll/REL/m501Dll/player` | 248 |
| 61.28% | `M506ComInputCheck` | `m506Dll/REL/m506Dll/player` | 716 |
| 61.06% | `fn_1_49C` | `sdroomdll/REL/sdroomdll/sdroom` | 4,272 |
| 60.81% | `M560KupaMain` | `m560dll/REL/m560dll/m560` | 3,548 |
| 60.38% | `sndPopGroup` | `main/musyx/runtime/s_data` | 848 |
| 60.01% | `MB4_CapsuleEffHook` | `w04Dll/REL/w04Dll/world04` | 5,612 |
| 60.01% | `MB4_CapsuleEffHook` | `w04sDll/REL/w04sDll/world04` | 5,612 |
| 60.00% | `M529ComRearDecision` | `m529dll/REL/m529dll/m529` | 68 |
| 60.00% | `cbForStateReadingFST` | `main/dolphin/dvd/dvd` | 140 |
| 59.85% | `PADInit` | `main/dolphin/pad/Pad` | 336 |
| 59.04% | `fn_1_79EC` | `mdbeachDll/REL/mdbeachDll/mdbeach` | 8,232 |
| 58.86% | `M529PlayerHopUpdate` | `m529dll/REL/m529dll/m529` | 700 |
| 58.82% | `seqPlaySong` | `main/musyx/runtime/s_data` | 340 |
| 58.53% | `M529PlayerTargetSequenceUpdate` | `m529dll/REL/m529dll/m529` | 1,736 |
| 58.46% | `M524FlowCameraOut` | `m524Dll/REL/m524Dll/m524` | 260 |
| 58.23% | `M529DebugCameraEaseAll` | `m529dll/REL/m529dll/m529` | 996 |
| 57.56% | `fn_1_8DF0` | `mgwarsDll/REL/mgwarsDll/mgwars` | 3,544 |
| 57.50% | `getTiming` | `main/dolphin/vi/vi` | 160 |
| 55.65% | `__assign<Q210Metrowerks130__assign_iterator<Q310Metrowerks80cdeque<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>>>__Q210Metrowerks86__cdeque_imp<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>FQ210Metrowerks130__assign_iterator<Q310Metrowerks80cdeque<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>>Q210Metrowerks130__assign_iterator<Q310Metrowerks80cdeque<PQ34m52111CDriverAsAI4Node,Q23std37allocator<PQ34m52111CDriverAsAI4Node>>13__iterator<0>>Q23std20forward_iterator_tag` | `m521Dll/REL/m521Dll/driver` | 920 |
| 55.65% | `__assign<Q210Metrowerks82__assign_iterator<Q310Metrowerks32cdeque<Pb,Q23std13allocator<Pb>>13__iterator<0>>>__Q210Metrowerks38__cdeque_imp<Pb,Q23std13allocator<Pb>>FQ210Metrowerks82__assign_iterator<Q310Metrowerks32cdeque<Pb,Q23std13allocator<Pb>>13__iterator<0>>Q210Metrowerks82__assign_iterator<Q310Metrowerks32cdeque<Pb,Q23std13allocator<Pb>>13__iterator<0>>Q23std20forward_iterator_tag` | `m537Dll/REL/m537Dll/player` | 920 |
| 54.76% | `SetTargetUp__Q24m5685CTubeFPC3Vec` | `m568Dll/REL/m568Dll/tube` | 168 |
| 54.68% | `__destroy__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>FQ33std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>13__iterator<0>Q33std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>13__iterator<0>` | `m521Dll/REL/m521Dll/driver` | 812 |
| 54.65% | `__free__Q23std35__deque_imp<b,Q23std12allocator<b>>Fv` | `m537Dll/REL/m537Dll/player` | 688 |
| 54.65% | `__free__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>Fv` | `m521Dll/REL/m521Dll/driver` | 688 |
| 54.55% | `OSInitStopwatch` | `main/dolphin/os/OSStopwatch` | 44 |
| 53.95% | `VIFlush` | `main/dolphin/vi/vi` | 304 |
| 53.77% | `__destroy__Q23std35__deque_imp<b,Q23std12allocator<b>>FQ33std35__deque_imp<b,Q23std12allocator<b>>13__iterator<0>Q33std35__deque_imp<b,Q23std12allocator<b>>13__iterator<0>` | `m537Dll/REL/m537Dll/player` | 796 |
| 53.33% | `SIInit` | `main/dolphin/si/SIBios` | 180 |
| 52.94% | `M529PlayerInputReady` | `m529dll/REL/m529dll/m529` | 60 |
| 52.94% | `M529PlayerScoreReady` | `m529dll/REL/m529dll/m529` | 60 |
| 52.78% | `M529DebugNodeAdd` | `m529dll/REL/m529dll/m529` | 136 |
| 51.85% | `MB4_CapsuleBubbleUpdate` | `w04Dll/REL/w04Dll/world04` | 6,028 |
| 51.85% | `MB4_CapsuleBubbleUpdate` | `w04sDll/REL/w04sDll/world04` | 6,028 |
| 51.85% | `update__Q24m5226CFlareFv` | `m522Dll/REL/m522Dll/fire` | 840 |
| 51.63% | `s3dHandle` | `main/musyx/runtime/snd3d` | 1,716 |
| 51.61% | `VIGetTvFormat` | `main/dolphin/vi/vi` | 104 |
| 51.45% | `inpInit` | `main/musyx/runtime/snd_midictrl` | 692 |
| 50.73% | `M529DebugCameraEase` | `m529dll/REL/m529dll/m529` | 820 |
| 50.70% | `M529DebugAngleApproach` | `m529dll/REL/m529dll/m529` | 260 |
| 50.68% | `sndSeqPlayEx` | `main/musyx/runtime/s_data` | 292 |
| 50.54% | `fn_1_57A8` | `mdbeachDll/REL/mdbeachDll/mdbeach` | 5,876 |
| 50.00% | `LCQueueWait` | `main/dolphin/os/OSCache` | 20 |
| 50.00% | `OSResetStopwatch` | `main/dolphin/os/OSStopwatch` | 40 |
| 49.39% | `aramStoreData` | `main/musyx/runtime/hw_aramdma` | 988 |
| 48.80% | `DrawDebug__Q24m52111CDriverAsAIFPA3_A4_f` | `m521Dll/REL/m521Dll/driver` | 1,828 |
| 48.70% | `AddEmitter` | `main/musyx/runtime/snd3d` | 1,076 |
| 47.73% | `PSMTXRotTrig` | `main/dolphin/mtx/mtx` | 176 |
| 47.71% | `__ct__Q23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>FRCQ23std83__deque_imp<Q34m52111CDriverAsAI4Node,Q23std36allocator<Q34m52111CDriverAsAI4Node>>` | `m521Dll/REL/m521Dll/driver` | 872 |
| 47.62% | `M529ExitAfterWipe` | `m529dll/REL/m529dll/m529` | 220 |
| 47.37% | `cbForStateCheckID2` | `main/dolphin/dvd/dvd` | 228 |
| 46.73% | `ObjectSetup` | `m529dll/REL/m529dll/m529` | 1,344 |
| 45.45% | `MdLightSetupModel` | `rescardDll/REL/rescardDll/object` | 44 |
| 45.36% | `msmStreamStopSub` | `main/msm/msmstream` | 388 |
| 44.88% | `M529ScoreUpdate` | `m529dll/REL/m529dll/m529` | 324 |
| 44.44% | `M529ComFrontButtonDown` | `m529dll/REL/m529dll/m529` | 252 |
| 44.06% | `__ct__Q23std35__deque_imp<b,Q23std12allocator<b>>FRCQ23std35__deque_imp<b,Q23std12allocator<b>>` | `m537Dll/REL/m537Dll/player` | 808 |
| 43.90% | `M529DebugNodeRemove` | `m529dll/REL/m529dll/m529` | 164 |
| 42.86% | `PSVECDistance` | `main/dolphin/mtx/vec` | 84 |
| 42.75% | `ChooseHand__Q24m5216CClockFv` | `m521Dll/REL/m521Dll/clock` | 3,312 |
| 42.55% | `PADRead` | `main/dolphin/pad/Pad` | 768 |
| 41.18% | `M529EffectsFadeOut` | `m529dll/REL/m529dll/m529` | 272 |
| 41.08% | `MakeTrialStageMesh` | `sd00dll/REL/sd00dll/stage` | 4,060 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m501Dll/REL/m501Dll/m501` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m509Dll/REL/m509Dll/m509` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m511Dll/REL/m511Dll/m511` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m512Dll/REL/m512Dll/m512` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m513Dll/REL/m513Dll/m513` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m517Dll/REL/m517Dll/m517` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m521Dll/REL/m521Dll/m521` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m522Dll/REL/m522Dll/m522` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m532Dll/REL/m532Dll/m532` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m536Dll/REL/m536Dll/m536` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m537Dll/REL/m537Dll/m537` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m539Dll/REL/m539Dll/m539` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m568Dll/REL/m568Dll/m568` | 1,704 |
| 39.20% | `MergeSort__FPFP9CLinkNodeP9CLinkNode_bP9CLinkNode` | `m579Dll/REL/m579Dll/m579` | 1,704 |
| 38.50% | `msmStreamFade` | `main/msm/msmstream` | 904 |
| 38.46% | `aramAllocateStreamBuffer` | `main/musyx/runtime/hw_aramdma` | 312 |
| 38.37% | `__OSThreadInit` | `main/dolphin/os/OSThread` | 344 |
| 37.63% | `__OSUnhandledException` | `main/dolphin/os/OSError` | 744 |
| 35.70% | `fn_1_668` | `m566Dll/REL/m566Dll/m566` | 17,040 |
| 34.88% | `sndUpdateListener` | `main/musyx/runtime/snd3d` | 372 |
| 34.51% | `voiceBlock` | `main/musyx/runtime/synthvoice` | 452 |
| 32.67% | `OnReset` | `main/dolphin/pad/Pad` | 188 |
| 29.91% | `OSUnlink` | `main/dolphin/os/OSLink` | 468 |
| 27.59% | `__ct__6CModelFPFP11Hu3DModel_sPA3_A4_f_v` | `m501Dll/REL/m501Dll/m501` | 116 |
| 27.03% | `stateReadingFST` | `main/dolphin/dvd/dvd` | 148 |
| 27.01% | `inpSetRPNDec` | `main/musyx/runtime/snd_midictrl` | 548 |
| 27.01% | `inpSetRPNInc` | `main/musyx/runtime/snd_midictrl` | 548 |
| 26.59% | `msmSysLoadGroup` | `main/msm/msmsys` | 1,384 |
| 26.23% | `OSCreateThread` | `main/dolphin/os/OSThread` | 488 |
| 24.66% | `StartContinousEmitters` | `main/musyx/runtime/snd3d` | 2,060 |
| 24.59% | `msmStreamPeriodicProc` | `main/msm/msmstream` | 244 |
| 23.50% | `msmStreamData` | `main/msm/msmstream` | 748 |
| 23.08% | `stateTimeout` | `main/dolphin/dvd/dvd` | 52 |
| 22.73% | `init__Q24m50110CAsiatoManFv` | `m501Dll/REL/m501Dll/asiato` | 88 |
| 21.74% | `M529ComDelay` | `m529dll/REL/m529dll/m529` | 80 |
| 21.57% | `msmStreamPlay` | `main/msm/msmstream` | 204 |
| 21.43% | `msmStreamDvdCallback2` | `main/msm/msmstream` | 260 |
| 20.59% | `M529PlayerMain` | `m529dll/REL/m529dll/m529` | 3,048 |
| 20.39% | `CalcEmitter` | `main/musyx/runtime/snd3d` | 1,628 |
| 19.44% | `__init_registers` | `main/dolphin/os/__start` | 144 |
| 19.00% | `M529TargetUpdate` | `m529dll/REL/m529dll/m529` | 1,116 |
| 18.95% | `msmStreamStop` | `main/msm/msmstream` | 612 |
| 18.75% | `Run` | `main/dolphin/os/OSReboot` | 16 |
| 17.89% | `msmSysDelGroupBase` | `main/msm/msmsys` | 760 |
| 16.55% | `_GetInputValue` | `main/musyx/runtime/snd_midictrl` | 1,184 |
| 15.98% | `__ARChecksize` | `main/dolphin/ar/ar` | 6,132 |
| 15.00% | `inpSetRPNHi` | `main/musyx/runtime/snd_midictrl` | 480 |
| 14.29% | `s3dInit` | `main/musyx/runtime/snd3d` | 56 |
| 14.29% | `VIGetNextField` | `main/dolphin/vi/vi` | 156 |
| 13.16% | `sndUpdateEmitter` | `main/musyx/runtime/snd3d` | 216 |
| 11.76% | `strcat` | `main/MSL_C.PPCEABI.bare.H/string` | 44 |
| 11.11% | `fn_1_C360` | `sdroomdll/REL/sdroomdll/garage` | 36 |
| 10.77% | `PSMTXRotAxisRad` | `main/dolphin/mtx/mtx` | 112 |
| 8.60% | `voiceAllocate` | `main/musyx/runtime/synthvoice` | 272 |
| 8.33% | `__OSInitMemoryProtection` | `main/dolphin/os/OSMemory` | 280 |
| 8.17% | `__OSReboot` | `main/dolphin/os/OSReboot` | 832 |
| 6.25% | `dataInitStack` | `main/musyx/runtime/s_data` | 64 |
| 2.70% | `OSLink` | `main/dolphin/os/OSLink` | 36 |
| 2.04% | `calloc` | `main/MSL_C.PPCEABI.bare.H/alloc` | 196 |
| 1.85% | `soft_allocate_from_var_pools` | `main/MSL_C.PPCEABI.bare.H/alloc` | 216 |
| 1.35% | `FixBlock_construct` | `main/MSL_C.PPCEABI.bare.H/alloc` | 296 |
| 0.88% | `allocate_from_fixed_pools` | `main/MSL_C.PPCEABI.bare.H/alloc` | 452 |
| 0.84% | `Block_subBlock` | `main/MSL_C.PPCEABI.bare.H/alloc` | 476 |
| 0.78% | `inpSetMidiCtrl` | `main/musyx/runtime/snd_midictrl` | 1,308 |
| 0.75% | `OSSetErrorHandler` | `main/dolphin/os/OSError` | 536 |
| 0.68% | `allocate_from_var_pools` | `main/MSL_C.PPCEABI.bare.H/alloc` | 584 |
| 0.04% | `salBuildCommandList` | `main/musyx/runtime/hw_dspctrl` | 9,564 |

## By unit

Every unit with a function short of 100%, largest remaining code first.

| unit | source | open | functions | open bytes |
|---|---|--:|--:|--:|
| `systemDll/REL/systemDll/nel` | (no source yet) | 159 | 159 | 116,136 |
| `w04Dll/REL/w04Dll/world04` | `src/REL/w04Dll/world04.c` | 10 | 66 | 48,524 |
| `e3setupdll/REL/e3setupdll/e3setup` | (no source yet) | 34 | 34 | 44,412 |
| `m566Dll/REL/m566Dll/m566` | `src/REL/m566Dll/m566.c` | 3 | 17 | 40,056 |
| `systemDll/REL/systemDll/stage` | (no source yet) | 71 | 71 | 37,476 |
| `w02Dll/REL/w02Dll/world02` | `src/REL/w02Dll/world02.c` | 9 | 73 | 37,412 |
| `m535Dll/REL/m535Dll/m535` | `src/REL/m535Dll/m535.c` | 6 | 19 | 37,292 |
| `sdroomdll/REL/sdroomdll/garage` | `src/REL/sdroomdll/garage.c` | 6 | 31 | 33,672 |
| `m527Dll/REL/m527Dll/m527` | `src/REL/m527Dll/m527.c` | 2 | 16 | 30,888 |
| `mdminiDll/REL/mdminiDll/mdmini` | `src/REL/mdminiDll/mdmini.c` | 4 | 58 | 29,900 |
| `m529dll/REL/m529dll/m529` | `src/REL/m529dll/m529.c` | 47 | 54 | 29,280 |
| `m525Dll/REL/m525Dll/m525` | `src/REL/m525Dll/m525.c` | 2 | 18 | 25,980 |
| `w04sDll/REL/w04sDll/world04` | `src/REL/w04sDll/world04.c` | 6 | 59 | 25,424 |
| `carddll/REL/carddll/player` | `src/REL/carddll/player.c` | 3 | 43 | 25,016 |
| `mgmatchDll/REL/mgmatchDll/mgmatch` | `src/REL/mgmatchDll/mgmatch.c` | 5 | 93 | 21,844 |
| `sd00dll/REL/sd00dll/stage` | `src/REL/sd00dll/stage.c` | 8 | 71 | 20,688 |
| `carddll/REL/carddll/status` | `src/REL/carddll/status.c` | 2 | 59 | 20,644 |
| `m567Dll/REL/m567Dll/m567` | `src/REL/m567Dll/m567.c` | 7 | 55 | 18,956 |
| `partyresultdll/REL/partyresultdll/result` | `src/REL/partyresultdll/result.c` | 5 | 23 | 18,436 |
| `m549Dll/REL/m549Dll/game` | `src/REL/m549Dll/game.c` | 8 | 42 | 18,372 |
| `main/game/board/capmain` | `src/game/board/capmain.c` | 1 | 300 | 18,356 |
| `mdbeachDll/REL/mdbeachDll/mdbeach` | `src/REL/mdbeachDll/mdbeach.c` | 4 | 54 | 18,136 |
| `m553Dll/REL/m553Dll/game` | `src/REL/m553Dll/game.c` | 5 | 28 | 17,716 |
| `m540Dll/REL/m540Dll/m540` | `src/REL/m540Dll/m540.c` | 7 | 226 | 17,216 |
| `m521Dll/REL/m521Dll/driver` | `src/REL/m521Dll/driver.cpp` | 17 | 51 | 16,940 |
| `m537Dll/REL/m537Dll/player` | `src/REL/m537Dll/player.cpp` | 24 | 73 | 16,608 |
| `rescardDll/REL/rescardDll/rescard` | `src/REL/rescardDll/rescard.c` | 4 | 44 | 15,812 |
| `m518dll/REL/m518dll/m518` | `src/REL/m518dll/m518.c` | 5 | 122 | 15,376 |
| `main/TRK_MINNOW_DOLPHIN/__exception` | (no source yet) | 3 | 3 | 15,312 |
| `m538Dll/REL/m538Dll/m538` | `src/REL/m538Dll/m538.c` | 14 | 89 | 14,852 |
| `m524Dll/REL/m524Dll/m524` | `src/REL/m524Dll/m524.c` | 25 | 76 | 14,784 |
| `m522Dll/REL/m522Dll/player` | `src/REL/m522Dll/player.cpp` | 22 | 86 | 14,332 |
| `mgwarsDll/REL/mgwarsDll/mgwars` | `src/REL/mgwarsDll/mgwars.c` | 4 | 93 | 14,288 |
| `carddll/REL/carddll/cardmain` | `src/REL/carddll/cardmain.c` | 1 | 28 | 13,640 |
| `m542dll/REL/m542dll/game` | `src/REL/m542dll/game.c` | 10 | 30 | 13,616 |
| `w02sDll/REL/w02sDll/world02` | `src/REL/w02sDll/world02.c` | 5 | 62 | 13,248 |
| `m523Dll/REL/m523Dll/player` | `src/REL/m523Dll/player.c` | 13 | 51 | 13,024 |
| `main/musyx/runtime/hw_dspctrl` | `src/musyx/runtime/hw_dspctrl.c` | 7 | 15 | 11,888 |
| `m561dll/REL/m561dll/m561` | `src/REL/m561dll/m561.c` | 2 | 71 | 11,884 |
| `m517Dll/REL/m517Dll/player` | `src/REL/m517Dll/player.cpp` | 7 | 45 | 11,688 |
| `m543Dll/REL/m543Dll/game` | `src/REL/m543Dll/game.c` | 1 | 30 | 11,608 |
| `partyresultdll/REL/partyresultdll/stat` | `src/REL/partyresultdll/stat.c` | 3 | 15 | 11,516 |
| `mgmatchDll/REL/mgmatchDll/score` | `src/REL/mgmatchDll/score.c` | 5 | 14 | 11,388 |
| `w07Dll/REL/w07Dll/world07` | `src/REL/w07Dll/world07.c` | 3 | 52 | 11,360 |
| `m521Dll/REL/m521Dll/clock` | `src/REL/m521Dll/clock.cpp` | 8 | 47 | 10,440 |
| `m579Dll/REL/m579Dll/player` | `src/REL/m579Dll/player.cpp` | 11 | 43 | 10,372 |
| `mdcardDll/REL/mdcardDll/mdcard` | `src/REL/mdcardDll/mdcard.c` | 3 | 39 | 10,324 |
| `m570Dll/REL/m570Dll/m570` | `src/REL/m570Dll/m570.c` | 15 | 65 | 8,740 |
| `m559dll/REL/m559dll/m559` | `src/REL/m559dll/m559.c` | 11 | 80 | 8,640 |
| `main/musyx/runtime/snd3d` | `src/musyx/runtime/snd3d.c` | 13 | 16 | 8,552 |
| `staffDll/REL/staffDll/staff` | `src/REL/staffDll/staff.c` | 1 | 8 | 8,500 |
| `w03Dll/REL/w03Dll/world03` | `src/REL/w03Dll/world03.c` | 3 | 40 | 8,492 |
| `m501Dll/REL/m501Dll/player` | `src/REL/m501Dll/player.cpp` | 12 | 56 | 8,464 |
| `main/msm/msmstream` | `src/msm/msmstream.c` | 15 | 28 | 8,264 |
| `m522Dll/REL/m522Dll/fire` | `src/REL/m522Dll/fire.cpp` | 8 | 55 | 8,256 |
| `m504dll/REL/m504dll/player` | `src/REL/m504dll/player.c` | 3 | 13 | 8,096 |
| `mdoptionDll/REL/mdoptionDll/stage` | `src/REL/mdoptionDll/stage.c` | 3 | 63 | 8,012 |
| `motchkDll/REL/motchkDll/motchk` | (no source yet) | 9 | 9 | 7,900 |
| `m562dll/REL/m562dll/evt_koopagrow` | `src/REL/m562dll/evt_koopagrow.c` | 1 | 1 | 7,472 |
| `m562dll/REL/m562dll/firering` | `src/REL/m562dll/firering.c` | 2 | 24 | 7,200 |
| `m551Dll/REL/m551Dll/m551` | `src/REL/m551Dll/m551.c` | 5 | 53 | 7,168 |
| `m523Dll/REL/m523Dll/m523` | `src/REL/m523Dll/m523.c` | 13 | 60 | 7,044 |
| `m505Dll/REL/m505Dll/m505` | `src/REL/m505Dll/m505.c` | 1 | 19 | 7,028 |
| `m560dll/REL/m560dll/m560` | `src/REL/m560dll/m560.c` | 6 | 64 | 6,972 |
| `m530Dll/REL/m530Dll/m530` | `src/REL/m530Dll/m530.c` | 12 | 64 | 6,820 |
| `m564Dll/REL/m564Dll/m564` | `src/REL/m564Dll/m564.c` | 12 | 61 | 6,820 |
| `m569Dll/REL/m569Dll/m569` | `src/REL/m569Dll/m569.c` | 12 | 54 | 6,820 |
| `main/musyx/runtime/synthmacros` | `src/musyx/runtime/synthmacros.c` | 6 | 52 | 6,496 |
| `mdstoryDll/REL/mdstoryDll/mdstory` | `src/REL/mdstoryDll/mdstory.c` | 3 | 43 | 6,492 |
| `main/dolphin/vi/vi` | `src/dolphin/vi/vi.c` | 13 | 23 | 6,416 |
| `main/dolphin/ar/ar` | `src/dolphin/ar/ar.c` | 2 | 12 | 6,328 |
| `safDll/REL/safDll/saf` | (no source yet) | 5 | 5 | 6,180 |
| `m562dll/REL/m562dll/koopa` | `src/REL/m562dll/koopa.c` | 2 | 14 | 6,108 |
| `safDll/REL/safDll/safanim` | (no source yet) | 7 | 7 | 6,108 |
| `m573dll/REL/m573dll/m573` | `src/REL/m573dll/m573.c` | 6 | 77 | 5,916 |
| `m562dll/REL/m562dll/light` | `src/REL/m562dll/light.c` | 2 | 5 | 5,896 |
| `systemDll/REL/systemDll/math` | (no source yet) | 19 | 19 | 5,856 |
| `w05sDll/REL/w05sDll/world05` | `src/REL/w05sDll/world05.c` | 1 | 19 | 5,836 |
| `m534Dll/REL/m534Dll/stage` | `src/REL/m534Dll/stage.c` | 2 | 32 | 5,500 |
| `sdroomdll/REL/sdroomdll/garagesave` | `src/REL/sdroomdll/garagesave.c` | 3 | 23 | 5,424 |
| `m550dll/REL/m550dll/stage` | `src/REL/m550dll/stage.c` | 3 | 20 | 5,404 |
| `m542dll/REL/m542dll/m542` | `src/REL/m542dll/m542.c` | 1 | 19 | 5,332 |
| `main/dolphin/dvd/dvd` | `src/dolphin/dvd/dvd.c` | 15 | 47 | 5,324 |
| `m548dll/REL/m548dll/game` | `src/REL/m548dll/game.c` | 4 | 21 | 5,316 |
| `sdroomdll/REL/sdroomdll/sdroom` | `src/REL/sdroomdll/sdroom.c` | 2 | 9 | 5,292 |
| `mdoptionDll/REL/mdoptionDll/mdoption` | `src/REL/mdoptionDll/mdoption.c` | 2 | 24 | 5,208 |
| `m508Dll/REL/m508Dll/m508` | `src/REL/m508Dll/m508.c` | 6 | 164 | 5,192 |
| `m506Dll/REL/m506Dll/player` | `src/REL/m506Dll/player.c` | 3 | 11 | 5,156 |
| `m517Dll/REL/m517Dll/choro` | `src/REL/m517Dll/choro.cpp` | 6 | 35 | 5,092 |
| `main/musyx/runtime/snd_midictrl` | `src/musyx/runtime/snd_midictrl.c` | 10 | 35 | 5,064 |
| `m511Dll/REL/m511Dll/player` | `src/REL/m511Dll/player.cpp` | 4 | 51 | 5,032 |
| `systemDll/REL/systemDll/window` | (no source yet) | 17 | 17 | 4,888 |
| `main/msm/msmsys` | `src/msm/msmsys.c` | 5 | 23 | 4,724 |
| `main/dolphin/gx/GXInit` | `src/dolphin/gx/GXInit.c` | 3 | 5 | 4,704 |
| `m531Dll/REL/m531Dll/polish` | `src/REL/m531Dll/polish.cpp` | 4 | 19 | 4,604 |
| `m568Dll/REL/m568Dll/input` | `src/REL/m568Dll/input.cpp` | 9 | 24 | 4,576 |
| `systemDll/REL/systemDll/camera` | (no source yet) | 10 | 10 | 4,336 |
| `m509Dll/REL/m509Dll/player` | `src/REL/m509Dll/player.cpp` | 6 | 42 | 4,304 |
| `m571dll/REL/m571dll/m571` | `src/REL/m571dll/m571.c` | 6 | 87 | 4,172 |
| `m504dll/REL/m504dll/ending` | `src/REL/m504dll/ending.c` | 1 | 2 | 4,088 |
| `m502dll/REL/m502dll/bat` | `src/REL/m502dll/bat.c` | 1 | 8 | 4,056 |
| `m563dll/REL/m563dll/m563` | `src/REL/m563dll/m563.c` | 5 | 75 | 3,960 |
| `m513Dll/REL/m513Dll/gamemaster` | `src/REL/m513Dll/gamemaster.cpp` | 13 | 35 | 3,952 |
| `main/musyx/runtime/stream` | `src/musyx/runtime/stream.c` | 2 | 18 | 3,860 |
| `m521Dll/REL/m521Dll/player` | `src/REL/m521Dll/player.cpp` | 4 | 46 | 3,812 |
| `m550dll/REL/m550dll/m550` | `src/REL/m550dll/m550.c` | 4 | 21 | 3,812 |
| `main/dolphin/pad/Pad` | `src/dolphin/pad/Pad.c` | 10 | 19 | 3,808 |
| `safDll/REL/safDll/safmotion` | (no source yet) | 3 | 3 | 3,752 |
| `m547dll/REL/m547dll/m547` | `src/REL/m547dll/m547.c` | 2 | 28 | 3,716 |
| `m565dll/REL/m565dll/ending` | `src/REL/m565dll/ending.c` | 1 | 1 | 3,696 |
| `m568Dll/REL/m568Dll/game_master` | `src/REL/m568Dll/game_master.cpp` | 5 | 24 | 3,692 |
| `main/musyx/runtime/hardware` | `src/musyx/runtime/hardware.c` | 26 | 44 | 3,504 |
| `m562dll/REL/m562dll/fire` | `src/REL/m562dll/fire.c` | 3 | 23 | 3,488 |
| `main/dolphin/os/OSThread` | `src/dolphin/os/OSThread.c` | 7 | 25 | 3,472 |
| `m513Dll/REL/m513Dll/leaf` | `src/REL/m513Dll/leaf.cpp` | 3 | 19 | 3,428 |
| `sdroomdll/REL/sdroomdll/picture` | `src/REL/sdroomdll/picture.c` | 1 | 13 | 3,304 |
| `sd00dll/REL/sd00dll/sd00` | `src/REL/sd00dll/sd00.c` | 2 | 58 | 3,224 |
| `m531Dll/REL/m531Dll/flow` | `src/REL/m531Dll/flow.cpp` | 3 | 26 | 3,212 |
| `mgtourDll/REL/mgtourDll/mgtournament` | `src/REL/mgtourDll/mgtournament.c` | 1 | 76 | 3,212 |
| `m536Dll/REL/m536Dll/player` | `src/REL/m536Dll/player.cpp` | 2 | 37 | 3,116 |
| `main/musyx/runtime/s_data` | `src/musyx/runtime/s_data.c` | 7 | 7 | 3,056 |
| `m579Dll/REL/m579Dll/puku2` | `src/REL/m579Dll/puku2.cpp` | 3 | 18 | 2,996 |
| `m513Dll/REL/m513Dll/heiho` | `src/REL/m513Dll/heiho.cpp` | 4 | 22 | 2,980 |
| `m516Dll/REL/m516Dll/player` | `src/REL/m516Dll/player.c` | 2 | 20 | 2,940 |
| `m506Dll/REL/m506Dll/object` | `src/REL/m506Dll/object.c` | 5 | 64 | 2,896 |
| `m513Dll/REL/m513Dll/player` | `src/REL/m513Dll/player.cpp` | 4 | 23 | 2,896 |
| `m517Dll/REL/m517Dll/gamemaster` | `src/REL/m517Dll/gamemaster.cpp` | 10 | 34 | 2,880 |
| `storymodedll/REL/storymodedll/opening` | `src/REL/storymodedll/opening.c` | 3 | 40 | 2,856 |
| `m554dll/REL/m554dll/m554` | `src/REL/m554dll/m554.c` | 2 | 20 | 2,712 |
| `mgfreeDll/REL/mgfreeDll/mgfree` | `src/REL/mgfreeDll/mgfree.c` | 1 | 33 | 2,708 |
| `m568Dll/REL/m568Dll/player` | `src/REL/m568Dll/player.cpp` | 3 | 34 | 2,684 |
| `m539Dll/REL/m539Dll/score` | `src/REL/m539Dll/score.cpp` | 2 | 23 | 2,636 |
| `main/dolphin/si/SIBios` | `src/dolphin/si/SIBios.c` | 5 | 24 | 2,620 |
| `m532Dll/REL/m532Dll/player` | `src/REL/m532Dll/player.cpp` | 5 | 77 | 2,596 |
| `e3setupdll/REL/e3setupdll/toueidisp` | (no source yet) | 4 | 4 | 2,572 |
| `m502dll/REL/m502dll/m502` | `src/REL/m502dll/m502.c` | 1 | 33 | 2,556 |
| `main/dolphin/os/OSLink` | `src/dolphin/os/OSLink.c` | 5 | 8 | 2,508 |
| `mgfreeDll/REL/mgfreeDll/decide` | `src/REL/mgfreeDll/decide.c` | 1 | 38 | 2,488 |
| `m532Dll/REL/m532Dll/m532` | `src/REL/m532Dll/m532.cpp` | 2 | 153 | 2,340 |
| `m539Dll/REL/m539Dll/m539` | `src/REL/m539Dll/m539.cpp` | 2 | 149 | 2,340 |
| `main/game/saveload` | `src/game/saveload.c` | 1 | 54 | 2,308 |
| `m544Dll/REL/m544Dll/stage` | `src/REL/m544Dll/stage.c` | 1 | 15 | 2,276 |
| `m545Dll/REL/m545Dll/stage` | `src/REL/m545Dll/stage.c` | 1 | 14 | 2,276 |
| `m546Dll/REL/m546Dll/stage` | `src/REL/m546Dll/stage.c` | 1 | 15 | 2,276 |
| `m547dll/REL/m547dll/stage` | `src/REL/m547dll/stage.c` | 1 | 14 | 2,276 |
| `m548dll/REL/m548dll/stage` | `src/REL/m548dll/stage.c` | 1 | 14 | 2,276 |
| `m512Dll/REL/m512Dll/player` | `src/REL/m512Dll/player.cpp` | 3 | 42 | 2,232 |
| `storymodedll/REL/storymodedll/storymode` | `src/REL/storymodedll/storymode.c` | 2 | 10 | 2,224 |
| `main/MSL_C.PPCEABI.bare.H/alloc` | `src/MSL_C.PPCEABI.bare.H/alloc.c` | 6 | 10 | 2,220 |
| `m554dll/REL/m554dll/game` | `src/REL/m554dll/game.c` | 2 | 24 | 2,112 |
| `main/musyx/runtime/hw_aramdma` | `src/musyx/runtime/hw_aramdma.c` | 5 | 13 | 2,100 |
| `main/musyx/runtime/synthvoice` | `src/musyx/runtime/synthvoice.c` | 5 | 21 | 2,096 |
| `m520Dll/REL/m520Dll/m520` | `src/REL/m520Dll/m520.c` | 1 | 29 | 2,076 |
| `m537Dll/REL/m537Dll/center_obj` | `src/REL/m537Dll/center_obj.cpp` | 2 | 42 | 2,012 |
| `m568Dll/REL/m568Dll/tube` | `src/REL/m568Dll/tube.cpp` | 3 | 33 | 2,008 |
| `m562dll/REL/m562dll/mini_mechakoopa` | `src/REL/m562dll/mini_mechakoopa.c` | 1 | 8 | 2,004 |
| `m568Dll/REL/m568Dll/stage` | `src/REL/m568Dll/stage.cpp` | 4 | 28 | 1,988 |
| `m501Dll/REL/m501Dll/m501` | `src/REL/m501Dll/m501.cpp` | 4 | 150 | 1,916 |
| `m537Dll/REL/m537Dll/dorrie` | `src/REL/m537Dll/dorrie.cpp` | 5 | 27 | 1,912 |
| `m575dll/REL/m575dll/com` | `src/REL/m575dll/com.c` | 1 | 8 | 1,896 |
| `m548dll/REL/m548dll/m548` | `src/REL/m548dll/m548.c` | 1 | 21 | 1,892 |
| `meschkdll/REL/meschkDll/meschk` | (no source yet) | 6 | 6 | 1,892 |
| `mdomakeDll/REL/mdomakeDll/mdomake` | `src/REL/mdomakeDll/mdomake.c` | 1 | 30 | 1,748 |
| `main/dolphin/os/OS` | `src/dolphin/os/OS.c` | 3 | 18 | 1,708 |
| `m509Dll/REL/m509Dll/m509` | `src/REL/m509Dll/m509.cpp` | 1 | 138 | 1,704 |
| `m511Dll/REL/m511Dll/m511` | `src/REL/m511Dll/m511.cpp` | 1 | 145 | 1,704 |
| `m512Dll/REL/m512Dll/m512` | `src/REL/m512Dll/m512.cpp` | 1 | 147 | 1,704 |
| `m513Dll/REL/m513Dll/m513` | `src/REL/m513Dll/m513.cpp` | 1 | 155 | 1,704 |
| `m517Dll/REL/m517Dll/m517` | `src/REL/m517Dll/m517.cpp` | 1 | 147 | 1,704 |
| `m521Dll/REL/m521Dll/m521` | `src/REL/m521Dll/m521.cpp` | 1 | 147 | 1,704 |
| `m522Dll/REL/m522Dll/m522` | `src/REL/m522Dll/m522.cpp` | 1 | 153 | 1,704 |
| `m536Dll/REL/m536Dll/m536` | `src/REL/m536Dll/m536.cpp` | 1 | 147 | 1,704 |
| `m537Dll/REL/m537Dll/m537` | `src/REL/m537Dll/m537.cpp` | 1 | 145 | 1,704 |
| `m568Dll/REL/m568Dll/m568` | `src/REL/m568Dll/m568.cpp` | 1 | 135 | 1,704 |
| `m579Dll/REL/m579Dll/m579` | `src/REL/m579Dll/m579.cpp` | 1 | 147 | 1,704 |
| `m512Dll/REL/m512Dll/score` | `src/REL/m512Dll/score.cpp` | 3 | 21 | 1,596 |
| `m569Dll/REL/m569Dll/kuribo` | `src/REL/m569Dll/kuribo.c` | 1 | 14 | 1,584 |
| `m532Dll/REL/m532Dll/game_master` | `src/REL/m532Dll/game_master.cpp` | 1 | 11 | 1,572 |
| `m532Dll/REL/m532Dll/man_referee` | `src/REL/m532Dll/man_referee.cpp` | 2 | 32 | 1,552 |
| `m572dll/REL/m572dll/m572` | `src/REL/m572dll/m572.c` | 5 | 88 | 1,552 |
| `m517Dll/REL/m517Dll/effect` | `src/REL/m517Dll/effect.cpp` | 2 | 28 | 1,548 |
| `systemDll/REL/systemDll/object` | (no source yet) | 10 | 10 | 1,536 |
| `m579Dll/REL/m579Dll/fishline` | `src/REL/m579Dll/fishline.cpp` | 2 | 32 | 1,524 |
| `m568Dll/REL/m568Dll/misc` | `src/REL/m568Dll/misc.cpp` | 2 | 7 | 1,516 |
| `m533dll/REL/m533dll/m533` | `src/REL/m533dll/m533.c` | 2 | 50 | 1,456 |
| `main/dolphin/os/OSRtc` | `src/dolphin/os/OSRtc.c` | 4 | 17 | 1,440 |
| `m574Dll/REL/m574Dll/collide` | `src/REL/m574Dll/collide.c` | 2 | 16 | 1,428 |
| `m565dll/REL/m565dll/stage` | `src/REL/m565dll/stage.c` | 1 | 18 | 1,420 |
| `m509Dll/REL/m509Dll/maze` | `src/REL/m509Dll/maze.cpp` | 2 | 40 | 1,392 |
| `m539Dll/REL/m539Dll/player` | `src/REL/m539Dll/player.cpp` | 2 | 30 | 1,364 |
| `e3setupdll/REL/e3setupdll/mgname` | (no source yet) | 2 | 2 | 1,336 |
| `main/musyx/runtime/synth` | `src/musyx/runtime/synth.c` | 2 | 27 | 1,332 |
| `m575dll/REL/m575dll/m575` | `src/REL/m575dll/m575.c` | 1 | 47 | 1,324 |
| `main/dolphin/os/OSError` | `src/dolphin/os/OSError.c` | 2 | 3 | 1,280 |
| `m521Dll/REL/m521Dll/score` | `src/REL/m521Dll/score.cpp` | 2 | 9 | 1,268 |
| `m562dll/REL/m562dll/main` | `src/REL/m562dll/main.c` | 1 | 18 | 1,260 |
| `m519dll/REL/m519dll/m519` | `src/REL/m519dll/m519.c` | 2 | 142 | 1,248 |
| `m568Dll/REL/m568Dll/archive` | `src/REL/m568Dll/archive.cpp` | 5 | 9 | 1,240 |
| `m574Dll/REL/m574Dll/stage` | `src/REL/m574Dll/stage.c` | 3 | 40 | 1,236 |
| `m580Dll/REL/m580Dll/score` | `src/REL/m580Dll/score.c` | 2 | 17 | 1,236 |
| `m517Dll/REL/m517Dll/input` | `src/REL/m517Dll/input.cpp` | 2 | 21 | 1,228 |
| `main/dolphin/dvd/dvdfs` | `src/dolphin/dvd/dvdfs.c` | 3 | 11 | 1,228 |
| `m536Dll/REL/m536Dll/score` | `src/REL/m536Dll/score.cpp` | 3 | 9 | 1,212 |
| `m534Dll/REL/m534Dll/player` | `src/REL/m534Dll/player.c` | 2 | 13 | 1,204 |
| `m570Dll/REL/m570Dll/player` | `src/REL/m570Dll/player.c` | 3 | 24 | 1,204 |
| `m550dll/REL/m550dll/game` | `src/REL/m550dll/game.c` | 3 | 26 | 1,180 |
| `m539Dll/REL/m539Dll/man_map` | `src/REL/m539Dll/man_map.cpp` | 1 | 15 | 1,176 |
| `m536Dll/REL/m536Dll/killer` | `src/REL/m536Dll/killer.cpp` | 1 | 21 | 1,152 |
| `m539Dll/REL/m539Dll/game_master` | `src/REL/m539Dll/game_master.cpp` | 1 | 23 | 1,152 |
| `m579Dll/REL/m579Dll/water` | `src/REL/m579Dll/water.cpp` | 1 | 38 | 1,116 |
| `m532Dll/REL/m532Dll/man_map` | `src/REL/m532Dll/man_map.cpp` | 1 | 19 | 1,044 |
| `m516Dll/REL/m516Dll/stage` | `src/REL/m516Dll/stage.c` | 1 | 24 | 1,040 |
| `m545Dll/REL/m545Dll/m545` | `src/REL/m545Dll/m545.c` | 1 | 32 | 972 |
| `m539Dll/REL/m539Dll/drum` | `src/REL/m539Dll/drum.cpp` | 3 | 34 | 968 |
| `m517Dll/REL/m517Dll/kuribo` | `src/REL/m517Dll/kuribo.cpp` | 1 | 19 | 944 |
| `m513Dll/REL/m513Dll/kuribo` | `src/REL/m513Dll/kuribo.cpp` | 1 | 11 | 940 |
| `main/dolphin/os/OSStopwatch` | `src/dolphin/os/OSStopwatch.c` | 6 | 6 | 880 |
| `w07sDll/REL/w07sDll/world07` | `src/REL/w07sDll/world07.c` | 1 | 31 | 856 |
| `main/dolphin/os/OSReboot` | `src/dolphin/os/OSReboot.c` | 2 | 3 | 848 |
| `m579Dll/REL/m579Dll/watereff` | `src/REL/m579Dll/watereff.cpp` | 2 | 17 | 824 |
| `main/dolphin/dvd/dvdlow` | `src/dolphin/dvd/dvdlow.c` | 3 | 21 | 820 |
| `m579Dll/REL/m579Dll/zako` | `src/REL/m579Dll/zako.cpp` | 1 | 35 | 788 |
| `m539Dll/REL/m539Dll/heiho` | `src/REL/m539Dll/heiho.cpp` | 1 | 5 | 784 |
| `m511Dll/REL/m511Dll/score` | `src/REL/m511Dll/score.cpp` | 1 | 21 | 764 |
| `m512Dll/REL/m512Dll/heiho` | `src/REL/m512Dll/heiho.cpp` | 2 | 10 | 716 |
| `m575dll/REL/m575dll/tubo` | `src/REL/m575dll/tubo.c` | 1 | 4 | 708 |
| `m580Dll/REL/m580Dll/reflect` | `src/REL/m580Dll/reflect.c` | 1 | 15 | 704 |
| `main/dolphin/os/OSReset` | `src/dolphin/os/OSReset.c` | 1 | 5 | 696 |
| `m514Dll/REL/m514Dll/score` | `src/REL/m514Dll/score.c` | 1 | 20 | 692 |
| `main/dolphin/pad/Padclamp` | `src/dolphin/pad/Padclamp.c` | 2 | 2 | 692 |
| `main/dolphin/gx/GXLight` | `src/dolphin/gx/GXLight.c` | 3 | 13 | 664 |
| `main/dolphin/os/OSResetSW` | `src/dolphin/os/OSResetSW.c` | 1 | 2 | 664 |
| `m513Dll/REL/m513Dll/misc` | `src/REL/m513Dll/misc.cpp` | 1 | 19 | 656 |
| `m517Dll/REL/m517Dll/misc` | `src/REL/m517Dll/misc.cpp` | 1 | 19 | 656 |
| `main/game/code_801A7E90` | (no source yet) | 3 | 3 | 652 |
| `m521Dll/REL/m521Dll/gamemaster` | `src/REL/m521Dll/gamemaster.cpp` | 1 | 27 | 612 |
| `main/dolphin/demo/DEMOPuts` | `src/dolphin/demo/DEMOPuts.c` | 1 | 3 | 604 |
| `m531Dll/REL/m531Dll/cleaneff` | `src/REL/m531Dll/cleaneff.cpp` | 1 | 34 | 580 |
| `m534Dll/REL/m534Dll/effect` | `src/REL/m534Dll/effect.c` | 2 | 8 | 568 |
| `m576Dll/REL/m576Dll/score` | `src/REL/m576Dll/score.c` | 1 | 5 | 564 |
| `m503Dll/REL/m503Dll/score` | `src/REL/m503Dll/score.c` | 1 | 8 | 552 |
| `m522Dll/REL/m522Dll/bubble` | `src/REL/m522Dll/bubble.cpp` | 1 | 27 | 552 |
| `main/Runtime.PPCEABI.H/NMWException` | `src/Runtime.PPCEABI.H/NMWException.cpp` | 3 | 8 | 552 |
| `main/dolphin/mtx/mtx` | `src/dolphin/mtx/mtx.c` | 4 | 18 | 548 |
| `main/dolphin/ai/ai` | `src/dolphin/ai/ai.c` | 2 | 20 | 536 |
| `m514Dll/REL/m514Dll/player` | `src/REL/m514Dll/player.c` | 1 | 23 | 524 |
| `main/dolphin/os/__start` | `src/dolphin/os/__start.c` | 5 | 7 | 516 |
| `m562dll/REL/m562dll/koopaboss` | `src/REL/m562dll/koopaboss.c` | 1 | 21 | 504 |
| `sdroomdll/REL/sdroomdll/tournament` | `src/REL/sdroomdll/tournament.c` | 1 | 18 | 472 |
| `m513Dll/REL/m513Dll/taimatsu` | `src/REL/m513Dll/taimatsu.cpp` | 1 | 8 | 464 |
| `m539Dll/REL/m539Dll/effect` | `src/REL/m539Dll/effect.cpp` | 1 | 6 | 440 |
| `m574Dll/REL/m574Dll/player` | `src/REL/m574Dll/player.c` | 1 | 17 | 428 |
| `m568Dll/REL/m568Dll/octtree` | `src/REL/m568Dll/octtree.cpp` | 1 | 6 | 408 |
| `main/musyx/runtime/StdReverb/reverb` | `src/musyx/runtime/StdReverb/reverb.c` | 1 | 5 | 388 |
| `mdoptionDll/REL/mdoptionDll/record` | `src/REL/mdoptionDll/record.c` | 1 | 7 | 388 |
| `e3setupdll/REL/e3setupdll/stage` | (no source yet) | 1 | 1 | 380 |
| `main/musyx/runtime/synthdata` | `src/musyx/runtime/synthdata.c` | 2 | 27 | 376 |
| `main/Runtime.PPCEABI.H/GCN_mem_alloc` | `src/Runtime.PPCEABI.H/GCN_mem_alloc.c` | 2 | 2 | 368 |
| `m501Dll/REL/m501Dll/joint` | `src/REL/m501Dll/joint.cpp` | 2 | 8 | 356 |
| `m579Dll/REL/m579Dll/camera` | `src/REL/m579Dll/camera.cpp` | 1 | 16 | 356 |
| `main/dolphin/os/OSCache` | `src/dolphin/os/OSCache.c` | 8 | 19 | 344 |
| `m501Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m509Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m511Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m512Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m513Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m517Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m521Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m522Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m531Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m532Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m536Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m537Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m539Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m568Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `m579Dll/REL/ptmf` | (no source yet) | 7 | 7 | 328 |
| `main/dolphin/os/OSSemaphore` | (no source yet) | 3 | 3 | 296 |
| `m579Dll/REL/m579Dll/fishman` | `src/REL/m579Dll/fishman.cpp` | 1 | 7 | 292 |
| `main/musyx/runtime/snd_init` | `src/musyx/runtime/snd_init.c` | 1 | 3 | 288 |
| `main/dolphin/os/OSMemory` | `src/dolphin/os/OSMemory.c` | 1 | 8 | 280 |
| `main/dolphin/os/OSAlarm` | `src/dolphin/os/OSAlarm.c` | 3 | 8 | 264 |
| `m501Dll/REL/m501Dll/asiato` | `src/REL/m501Dll/asiato.cpp` | 3 | 14 | 252 |
| `m541Dll/REL/m541Dll/m541` | `src/REL/m541Dll/m541.c` | 1 | 40 | 248 |
| `m543Dll/REL/m543Dll/m543` | `src/REL/m543Dll/m543.c` | 1 | 46 | 248 |
| `m553Dll/REL/m553Dll/m553` | `src/REL/m553Dll/m553.c` | 1 | 47 | 248 |
| `main/dolphin/dvd/dvdidutils` | (no source yet) | 1 | 1 | 248 |
| `main/dolphin/gx/GXBump` | `src/dolphin/gx/GXBump.c` | 1 | 11 | 236 |
| `m545Dll/REL/m545Dll/game` | `src/REL/m545Dll/game.c` | 1 | 26 | 216 |
| `main/dolphin/os/OSContext` | `src/dolphin/os/OSContext.c` | 1 | 13 | 216 |
| `main/dolphin/dsp/dsp` | `src/dolphin/dsp/dsp.c` | 1 | 9 | 196 |
| `m536Dll/REL/m536Dll/camera` | `src/REL/m536Dll/camera.cpp` | 1 | 13 | 188 |
| `main/dolphin/mtx/vec` | `src/dolphin/mtx/vec.c` | 2 | 12 | 152 |
| `mdstoryDll/REL/mdstoryDll/object` | `src/REL/mdstoryDll/object.c` | 1 | 56 | 148 |
| `w01sDll/REL/w01sDll/world01` | `src/REL/w01sDll/world01.c` | 1 | 70 | 140 |
| `m501Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m509Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m511Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m512Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m513Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m517Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m521Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m522Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m531Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m532Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m536Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m537Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m539Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m568Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m579Dll/REL/global_destructor_chain` | (no source yet) | 2 | 2 | 136 |
| `m501Dll/REL/m501Dll/stage` | `src/REL/m501Dll/stage.cpp` | 1 | 6 | 124 |
| `m522Dll/REL/m522Dll/sunfire` | `src/REL/m522Dll/sunfire.cpp` | 1 | 24 | 124 |
| `m532Dll/REL/m532Dll/man_object` | `src/REL/m532Dll/man_object.cpp` | 1 | 22 | 124 |
| `main/dolphin/ar/arq` | `src/dolphin/ar/arq.c` | 1 | 5 | 112 |
| `m501Dll/REL/m501Dll/gamemaster` | `src/REL/m501Dll/gamemaster.cpp` | 3 | 17 | 104 |
| `m564Dll/REL/m564Dll/bomb` | `src/REL/m564Dll/bomb.c` | 1 | 36 | 100 |
| `m522Dll/REL/m522Dll/stage` | `src/REL/m522Dll/stage.cpp` | 1 | 15 | 88 |
| `main/dolphin/mtx/quat` | `src/dolphin/mtx/quat.c` | 1 | 8 | 88 |
| `m509Dll/REL/m509Dll/startspr` | `src/REL/m509Dll/startspr.cpp` | 1 | 5 | 80 |
| `m536Dll/REL/m536Dll/stage` | `src/REL/m536Dll/stage.cpp` | 2 | 22 | 80 |
| `main/dolphin/gx/GXTransform` | `src/dolphin/gx/GXTransform.c` | 1 | 16 | 64 |
| `main/dolphin/dvd/dvdFatal` | (no source yet) | 1 | 1 | 48 |
| `main/MSL_C.PPCEABI.bare.H/string` | `src/MSL_C.PPCEABI.bare.H/string.c` | 1 | 7 | 44 |
| `rescardDll/REL/rescardDll/object` | `src/REL/rescardDll/object.c` | 1 | 64 | 44 |
| `m509Dll/REL/m509Dll/stage` | `src/REL/m509Dll/stage.cpp` | 1 | 5 | 40 |
| `m512Dll/REL/m512Dll/stage` | `src/REL/m512Dll/stage.cpp` | 1 | 8 | 40 |
| `main/dolphin/os/__ppc_eabi_init` | `src/dolphin/os/__ppc_eabi_init.c` | 1 | 5 | 36 |
| `main/dolphin/os/OSTime` | `src/dolphin/os/OSTime.c` | 1 | 5 | 24 |
| `m511Dll/REL/m511Dll/boat` | `src/REL/m511Dll/boat.cpp` | 1 | 19 | 4 |
| `main/game/code_801A811C` | `src/game/code_801A811C.c` | 1 | 1680 | 4 |
