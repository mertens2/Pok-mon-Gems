RustboroCity_MapScripts:: @ 81E06BD
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_OnFrame
	.byte 0

RustboroCity_OnTransition: @ 81E06C8
	setflag FLAG_VISITED_RUSTBORO_CITY
	call Common_EventScript_SetupRivalGfxId
	compare VAR_RUSTBORO_CITY_STATE, 6
	call_if_eq RustboroCity_EventScript_HideMapNamePopup
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_RUSTBORO_CITY_STATE, 6
	goto_if_eq RustboroCity_EventScript_PositionScientistForExit
	end

RustboroCity_EventScript_PositionScientistForExit:: @ 81E06EC
	compare VAR_TEMP_0, 11
	goto_if_eq RustboroCity_EventScript_PositionScientistLeftExit
	setobjectxyperm 15, 12, 15
	end

RustboroCity_EventScript_PositionScientistLeftExit:: @ 81E06FF
	setobjectxyperm 15, 11, 15
	end

RustboroCity_EventScript_HideMapNamePopup:: @ 81E0707
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

RustboroCity_OnFrame: @ 81E070B
	map_script_2 VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_EventScript_ScientistAddMatchCall
	.2byte 0

RustboroCity_EventScript_ScientistAddMatchCall:: @ 81E0715
	lockall
	setvar VAR_ROUTE104_STATE, 1
	applymovement OBJ_EVENT_ID_PLAYER, RustboroCity_Movement_PlayerWalkDown
	waitmovement 0
	playse SE_KAIDAN
	delay 10
	addobject 15
	applymovement 15, RustboroCity_Movement_ScientistApproachPlayer
	waitmovement 0
	playse SE_PIN
	applymovement 15, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 15, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement 15, RustboroCity_Movement_ScientistWalkInPlaceDown
	waitmovement 0
	msgbox RustboroCity_Text_DevelopedNewPokenavFeature, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HAS_MATCH_CALL
	applymovement 15, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_TK_KASYA
	delay 10
	playse SE_TK_KASYA
	delay 10
	playse SE_TK_KASYA
	delay 10
	playse SE_TK_KASYA
	delay 20
	applymovement 15, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox RustboroCity_Text_AddedMatchCallPleaseCallMrStone, MSGBOX_DEFAULT
	closemessage
	delay 20
	goto RustboroCity_EventScript_MatchCallTutorial

RustboroCity_EventScript_PleaseSelectPokenav:: @ 81E07AC
	msgbox RustboroCity_Text_PleaseSelectPokenav, MSGBOX_DEFAULT
	closemessage
	delay 10
	goto RustboroCity_EventScript_MatchCallTutorial

RustboroCity_EventScript_MatchCallTutorial:: @ 81E07BD
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	special ScriptMenu_CreateStartMenuForPokenavTutorial
	waitstate
	switch VAR_RESULT
	case 0, RustboroCity_EventScript_PleaseSelectPokenav
	case 1, RustboroCity_EventScript_PleaseSelectPokenav
	case 2, RustboroCity_EventScript_PleaseSelectPokenav
	case 4, RustboroCity_EventScript_PleaseSelectPokenav
	case 5, RustboroCity_EventScript_PleaseSelectPokenav
	case 6, RustboroCity_EventScript_PleaseSelectPokenav
	case 7, RustboroCity_EventScript_PleaseSelectPokenav
	case MULTI_B_PRESSED, RustboroCity_EventScript_PleaseSelectPokenav
	special OpenPokenavForTutorial
	waitstate
	delay 20
	msgbox RustboroCity_Text_IdBetterGetBackToWork, MSGBOX_DEFAULT
	closemessage
	applymovement 15, RustboroCity_Movement_ScientistLeave
	waitmovement 0
	playse SE_KAIDAN
	removeobject 15
	setflag FLAG_HIDE_RUSTBORO_CITY_SCIENTIST
	setvar VAR_RUSTBORO_CITY_STATE, 7
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	releaseall
	end

RustboroCity_Movement_ScientistWalkInPlaceDown: @ 81E084E
	walk_in_place_down
	step_end

RustboroCity_Movement_PlayerWalkDown: @ 81E0850
	walk_down
	step_end

RustboroCity_Movement_ScientistApproachPlayer: @ 81E0852
	walk_down
	delay_16
	step_end

@ Unused
RustboroCity_Movement_ScientistWalkAroundPlayer: @ 81E0855
	delay_16
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_fastest_up
	delay_16
	step_end

RustboroCity_Movement_ScientistLeave: @ 81E085D
	walk_up
	step_end

RustboroCity_EventScript_FatMan:: @ 81E085F
	lock
	faceplayer
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_EventScript_FatManSawGrunt
	msgbox RustboroCity_Text_WeShortenItToDevon, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_FatManSawGrunt:: @ 81E0874
	msgbox RustboroCity_Text_SneakyLookingManWentAroundCorner, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_DevonEmployee2:: @ 81E087E
	lock
	faceplayer
	msgbox RustboroCity_Text_YoureNewAroundHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Woman:: @ 81E088A
	msgbox RustboroCity_Text_GymLeaderIsntEasyWithFire, MSGBOX_NPC
	end

RustboroCity_EventScript_Man1:: @ 81E0893
	lock
	faceplayer
	goto_if_set FLAG_BADGE01_GET, RustboroCity_EventScript_Man1HaveBadge
	msgbox RustboroCity_Text_HaveYouChallengedGym, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Man1HaveBadge:: @ 81E08A8
	msgbox RustboroCity_Text_HeyThatsRustborosGymBadge, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Boy2:: @ 81E08B2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_EventScript_Boy2BrineyLeftTunnel
	msgbox RustboroCity_Text_MrBrineyWalksInTheTunnel, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Boy2BrineyLeftTunnel:: @ 81E08C7
	msgbox RustboroCity_Text_MrBrineyLovesPeeko, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_Twin:: @ 81E08D1
	msgbox RustboroCity_Text_WowYouHavePokemon, MSGBOX_NPC
	end

RustboroCity_EventScript_NinjaBoy:: @ 81E08DA
	msgbox RustboroCity_Text_CatchRarePokemonIfIGoToSchool, MSGBOX_SIGN
	end

RustboroCity_EventScript_TunnelSign:: @ 81E08E3
	msgbox RustboroCity_Text_TunnelNearingCompletion, MSGBOX_SIGN
	end

RustboroCity_EventScript_DevonCorpSign:: @ 81E08EC
	msgbox RustboroCity_Text_DevonCorpSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_GymSign:: @ 81E08F5
	msgbox RustboroCity_Text_GymSign, MSGBOX_SIGN
	end

@ Unused
RustboroCity_EventScript_DevonCorpBranchOfficeSign:: @ 81E08FE
	msgbox RustboroCity_Text_DevonCorpBranchOfficeSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_CitySign:: @ 81E0907
	msgbox RustboroCity_Text_CitySign, MSGBOX_SIGN
	end

RustboroCity_EventScript_TrainersSchoolSign:: @ 81E0910
	msgbox RustboroCity_Text_TrainersSchoolSign, MSGBOX_SIGN
	end

RustboroCity_EventScript_CuttersHouseSign:: @ 81E0919
	msgbox RustboroCity_Text_CuttersHouse, MSGBOX_SIGN
	end

RustboroCity_EventScript_LittleBoy:: @ 81E0922
	lock
	faceplayer
	msgbox RustboroCity_Text_PokemonCanChangeLookFromExp, MSGBOX_DEFAULT
	applymovement 7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_EventScript_LittleGirl:: @ 81E0938
	lock
	faceplayer
	msgbox RustboroCity_Text_PokemonChangeShape, MSGBOX_DEFAULT
	applymovement 8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_EventScript_Man2:: @ 81E094E
	lock
	faceplayer
	msgbox RustboroCity_Text_TradePokemonGrowFast, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_StolenGoodsTrigger0:: @ 81E095A
	lockall
	setobjectxyperm 9, 14, 21
	setobjectmovementtype 9, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 0
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger1:: @ 81E0971
	lockall
	setobjectxyperm 9, 14, 21
	setobjectmovementtype 9, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 1
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger2:: @ 81E0988
	lockall
	setobjectxyperm 9, 14, 21
	setobjectmovementtype 9, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 2
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger3:: @ 81E099F
	lockall
	setobjectxyperm 9, 14, 21
	setobjectmovementtype 9, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 3
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsTrigger4:: @ 81E09B6
	lockall
	setobjectxyperm 9, 14, 21
	setobjectmovementtype 9, MOVEMENT_TYPE_FACE_RIGHT
	setvar VAR_0x8004, 4
	goto RustboroCity_EventScript_StolenGoodsScene
	end

RustboroCity_EventScript_StolenGoodsScene:: @ 81E09CD
	msgbox RustboroCity_Text_OutOfTheWay, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_AQA_0, 0
	addobject 10
	addobject 9
	applymovement 10, RustboroCity_Movement_GruntEscape
	waitmovement 0
	removeobject 10
	applymovement 9, RustboroCity_Movement_EmployeeChaseGrunt1
	waitmovement 0
	msgbox RustboroCity_Text_WaitDontTakeMyGoods, MSGBOX_DEFAULT
	closemessage
	applymovement 9, RustboroCity_Movement_EmployeeChaseGrunt2
	waitmovement 0
	fadedefaultbgm
	removeobject 9
	setobjectxyperm 9, 30, 10
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
	setflag FLAG_DEVON_GOODS_STOLEN
	setvar VAR_RUSTBORO_CITY_STATE, 2
	setvar VAR_RUSTURF_TUNNEL_STATE, 2
	setvar VAR_ROUTE116_STATE, 1
	clearflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	releaseall
	end

@ Unused
RustboroCity_EventScript_ShadyCharacterTookOff:: @ 81E0A3B
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	return

@ Unused
RustboroCity_EventScript_YouGotItThankYou:: @ 81E0A44
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
	return

@ Unknown, unused employee movements. Based on the differences in movement theyre for approaching an object (probably the player) in different positions
RustboroCity_EventScript_EmployeeApproachUp:: @ 81E0A4D
	applymovement 9, RustboroCity_Movement_EmployeeApproachUp
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachLeft:: @ 81E0A58
	applymovement 9, RustboroCity_Movement_EmployeeApproachLeft
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachRight:: @ 81E0A63
	applymovement 9, RustboroCity_Movement_EmployeeApproachRight
	waitmovement 0
	return

@ Unused, see above
RustboroCity_EventScript_EmployeeApproachDown:: @ 81E0A6E
	applymovement 9, RustboroCity_Movement_EmployeeApproachDown
	waitmovement 0
	return

@ Unused, similar movement to the above scripts
RustboroCity_EventScript_EmployeeApproachPlayerFar:: @ 81E0A79
	applymovement 9, RustboroCity_Movement_EmployeeApproachPlayerFar
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

@ Unused
RustboroCity_Movement_GruntEscapeExtended: @ 81E0A8E
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

RustboroCity_Movement_GruntEscape: @ 81E0AA0
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

RustboroCity_Movement_EmployeeChaseGrunt1: @ 81E0AB1
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

RustboroCity_Movement_EmployeeChaseGrunt2: @ 81E0AB9
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachUp: @ 81E0AC1
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachLeft: @ 81E0AC5
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachRight: @ 81E0ACA
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachDown: @ 81E0ACF
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

@ Functionally unused
RustboroCity_Movement_EmployeeApproachPlayerFar: @ 81E0AD5
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

RustboroCity_EventScript_DevonEmployee1:: @ 81E0ADD
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_EventScript_ReturnGoodsSpokeToEmployee
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
	release
	end

RustboroCity_EventScript_ReturnGoodsSpokeToEmployee:: @ 81E0AF2
	waitse
	setvar VAR_TEMP_1, 4
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger0:: @ 81E0AFE
	lockall
	setvar VAR_TEMP_1, 0
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger1:: @ 81E0B0A
	lockall
	setvar VAR_TEMP_1, 1
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger2:: @ 81E0B16
	lockall
	setvar VAR_TEMP_1, 2
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_HelpGetGoodsTrigger3:: @ 81E0B22
	lockall
	setvar VAR_TEMP_1, 3
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
	end

RustboroCity_EventScript_EmployeeAskToGetGoods:: @ 81E0B2E
	compare VAR_TEMP_1, 0
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerUp1
	compare VAR_TEMP_1, 1
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerLeft1
	compare VAR_TEMP_1, 2
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerDown1
	compare VAR_TEMP_1, 3
	call_if_eq RustboroCity_EventScript_EmployeeApproachPlayerDown1
	setflag FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN
	setvar VAR_RUSTBORO_CITY_STATE, 3
	copyobjectxytoperm 9
	msgbox RustboroCity_Text_HelpMeIWasRobbed, MSGBOX_DEFAULT
	releaseall
	end

@ The below movement scripts are either partially or fully duplicated by the movement scripts when the player returns the goods
RustboroCity_EventScript_EmployeeFacePlayerUp1:: @ 81E0B6F
	applymovement 9, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerLeft1:: @ 81E0B9B
	applymovement 9, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerDown1:: @ 81E0BC7
	applymovement 9, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeApproachPlayerDown1:: @ 81E0BF3
	applymovement 9, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement 9, RustboroCity_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_Movement_EmployeeApproachPlayerDown: @ 81E0C29
	walk_down
	step_end

RustboroCity_EventScript_ReturnGoodsTrigger0:: @ 81E0C2B
	lockall
	setvar VAR_TEMP_1, 0
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger1:: @ 81E0C37
	lockall
	setvar VAR_TEMP_1, 1
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger2:: @ 81E0C43
	lockall
	setvar VAR_TEMP_1, 2
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoodsTrigger3:: @ 81E0C4F
	lockall
	setvar VAR_TEMP_1, 3
	goto RustboroCity_EventScript_ReturnGoods
	end

RustboroCity_EventScript_ReturnGoods:: @ 81E0C5B
	compare VAR_TEMP_1, 0
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerUp2
	compare VAR_TEMP_1, 1
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerLeft2
	compare VAR_TEMP_1, 2
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerDown2
	compare VAR_TEMP_1, 3
	call_if_eq RustboroCity_EventScript_EmployeeApproachPlayerDown2
	compare VAR_TEMP_1, 4
	call_if_eq RustboroCity_EventScript_EmployeeFacePlayerRight
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
	giveitem ITEM_GREAT_BALL
	compare VAR_RESULT, FALSE
	call_if_eq RustboroCity_EventScript_BagFull
	msgbox RustboroCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RETURNED_DEVON_GOODS
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
	setvar VAR_RUSTBORO_CITY_STATE, 5
	delay 30
	warp MAP_RUSTBORO_CITY_DEVON_CORP_3F, 255, 2, 2
	waitstate
	releaseall
	end

RustboroCity_EventScript_BagFull:: @ 81E0CD3
	msgbox RustboroCity_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
	return

RustboroCity_EventScript_EmployeeFacePlayerUp2:: @ 81E0CDC
	applymovement 9, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerLeft2:: @ 81E0D08
	applymovement 9, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerDown2:: @ 81E0D34
	applymovement 9, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeApproachPlayerDown2:: @ 81E0D60
	applymovement 9, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	applymovement 9, RustboroCity_Movement_EmployeeApproachPlayerDown
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	return

RustboroCity_EventScript_EmployeeFacePlayerRight:: @ 81E0D96
	applymovement 9, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement 9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 9, Common_Movement_Delay48
	waitmovement 0
	return

RustboroCity_EventScript_Rival:: @ 81E0DB8
	lockall
	call_if_unset FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_FacePlayer
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_PlayRivalMusic:: @ 81E0DD1
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RustboroCity_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	goto_if_eq RustboroCity_EventScript_PlayBrendanMusic
	return

RustboroCity_EventScript_PlayMayMusic:: @ 81E0DE9
	playbgm MUS_GIRL_SUP, 1
	return

RustboroCity_EventScript_PlayBrendanMusic:: @ 81E0DEE
	playbgm MUS_BOY_SUP, 1
	return

RustboroCity_EventScript_RivalTrigger0:: @ 81E0DF3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger1:: @ 81E0E33
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger2:: @ 81E0E73
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger3:: @ 81E0EB3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger4:: @ 81E0EF3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer4
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger5:: @ 81E0F33
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer5
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger6:: @ 81E0F73
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer6
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalTrigger7:: @ 81E0FB3
	lockall
	call RustboroCity_EventScript_PlayRivalMusic
	applymovement 14, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	playse SE_PIN
	applymovement 14, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 14, Common_Movement_Delay48
	waitmovement 0
	applymovement 14, RustboroCity_Movement_RivalApproachPlayer7
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	goto RustboroCity_EventScript_RivalEncounter

RustboroCity_EventScript_RivalEncounter:: @ 81E0FF3
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RustboroCity_EventScript_MayEncounter
	compare VAR_RESULT, FEMALE
	goto_if_eq RustboroCity_EventScript_BrendanEncounter
	end

RustboroCity_EventScript_MayEncounter:: @ 81E100B
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_MayBrineyHint
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_MayAskToBattle
	setflag FLAG_MET_RIVAL_RUSTBORO
	msgbox RustboroCity_Text_MayHiLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox RustboroCity_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	setvar VAR_0x8008, 0
	msgbox RustboroCity_Text_MayPassedBrineyWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleMay
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	call RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_MayAskToBattle:: @ 81E1070
	setvar VAR_0x8008, 1
	msgbox RustboroCity_Text_MayWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleMay
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_EventScript_BattleMay:: @ 81E1092
	msgbox RustboroCity_Text_MayImNotGoingToLose, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, RustboroCity_EventScript_BattleMayTreecko
	case 1, RustboroCity_EventScript_BattleMayTorchic
	case 2, RustboroCity_EventScript_BattleMayMudkip
	end

RustboroCity_EventScript_MayBrineyHint:: @ 81E10C1
	msgbox RustboroCity_Text_MayMrBrineyHint, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_RestoreBgm:: @ 81E10D6
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

RustboroCity_EventScript_BattleMayTreecko:: @ 81E10DB
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BattleMayTorchic:: @ 81E10EE
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BattleMayMudkip:: @ 81E1101
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, RustboroCity_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_MayBrineyHint
	end

RustboroCity_EventScript_BrendanEncounter:: @ 81E1114
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanBrineyHint
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanAskToBattle
	setflag FLAG_MET_RIVAL_RUSTBORO
	msgbox RustboroCity_Text_BrendanHiLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox RustboroCity_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	msgbox RustboroCity_Text_BrendanPassedBrineyWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleBrendan
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
	call RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_BrendanAskToBattle:: @ 81E1174
	msgbox RustboroCity_Text_BrendanWantToBattle, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_EventScript_BattleBrendan
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_EventScript_BattleBrendan:: @ 81E1191
	msgbox RustboroCity_Text_BrendanIWontGoEasy, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, RustboroCity_EventScript_BattleBrendanTreecko
	case 1, RustboroCity_EventScript_BattleBrendanTorchic
	case 2, RustboroCity_EventScript_BattleBrendanMudkip
	end

RustboroCity_EventScript_BrendanBrineyHint:: @ 81E11C0
	msgbox RustboroCity_Text_BrendanMrBrineyHint, MSGBOX_DEFAULT
	compare VAR_0x8008, 0
	call_if_eq RustboroCity_EventScript_RestoreBgm
	releaseall
	end

RustboroCity_EventScript_BattleBrendanTreecko:: @ 81E11D5
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_EventScript_BattleBrendanTorchic:: @ 81E11E8
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_EventScript_BattleBrendanMudkip:: @ 81E11FB
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, RustboroCity_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
	goto RustboroCity_EventScript_BrendanBrineyHint
	end

RustboroCity_Movement_RivalApproachPlayer0: @ 81E120E
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer1: @ 81E1215
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer2: @ 81E121B
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer3: @ 81E1220
	walk_down
	walk_left
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer4: @ 81E1224
	walk_down
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer5: @ 81E1227
	walk_down
	walk_right
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer6: @ 81E122B
	walk_down
	walk_right
	walk_right
	walk_down
	step_end

RustboroCity_Movement_RivalApproachPlayer7: @ 81E1230
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	step_end

RustboroCity_EventScript_Boy1:: @ 81E1236
	msgbox RustboroCity_Text_YouCanHave2On2Battle, MSGBOX_NPC
	end

RustboroCity_Text_WeShortenItToDevon: @ 81E123F
    .string "La Corporación Devon…\p"
    .string "Una de las empresas más poderosas\n"
    .string "de la región, quizá hasta del mundo.\p"
    .string "Todos acortamos su nombre a\n"
    .string "'Devon'. Suena menos malvado, ¿No\l"
    .string "lo crees?$"

RustboroCity_Text_SneakyLookingManWentAroundCorner: @ 81E12AC
    .string "{PLAYER}: ¿Ha visto a un hombre\n"
    .string "sospechoso por aquí?\p"
    .string "Transeúnte: ¿Mhh? Eh… No tengo idea\n"
    .string "de qué responder, ni qué te parece\l"
    .string "'sospechoso'… Pero sí vi a un\p"
    .string "tipo vestido como pirata yendo hacia\n"
    .string "Devon hace un rato…$"

RustboroCity_Text_HaveYouChallengedGym: @ 81E130D
    .string "En el momento en el que ganes la\n"
    .string "brillante Medalla del Gimnasio, todos\l"
    .string "comenzarán a respetarte más…\p"
    .string "Es horrible cuando no tienes una\n"
    .string "y todos se burlan, pero así es la\l"
    .string "vida de un 'No Entrenador', ¿No?$"

RustboroCity_Text_HeyThatsRustborosGymBadge: @ 81E139E
    .string "Mmm… Al parecer, ya tienes la Medalla\n"
    .string "de esta ciudad… Escucha, si te llegas\l"
    .string "a convertir en Campeón, prométeme\p"
    .string "que no se te subirá la fama\n"
    .string "a la cabeza, justo como Steven Stone…\l"
    .string "Aunque al Campeón actual… Sí le pasó…$"

RustboroCity_Text_YoureNewAroundHere: @ 81E1407
    .string "¿Huh? A ti no te conozco, pero no\n"
    .string "conozco a mucha gente que digamos,\l"
    .string "tampoco, así que no es de sorprender.$"

RustboroCity_Text_GymLeaderIsntEasyWithFire: @ 81E1480
    .string "La Líder tiene Pokémon con ventaja\n"
    .string "contra mi Talonflame… Aún con una\l"
    .string "evolución final, no consigo ganar…\p"
    .string "Quizá si tuviera Movimientos de\n"
    .string "Cobertura podría ganar, pero sólo\l"
    .string "conoce Picotazo, Ascuas, Ataque Ala\p"
    .string "y Gruñido… Debería reconsiderar\n"
    .string "mi estrategia de atacar a lo loco…$"


RustboroCity_Text_MrBrineyWalksInTheTunnel: @ 81E1520
    .string "El Señor Briney vive cerca del mar.\p"
    .string "He oído que él y su viejo Peecko aún\n"
    .string "eran amigos para cuando el Sr. era\l"
    .string "joven… Eso sí que fue hace mucho…$"


RustboroCity_Text_MrBrineyLovesPeeko: @ 81E1589
    .string "El Sr. Briney AMA a su Peecko,\n"
    .string "después de todo, han estado juntos\l"
    .string "desde que Briney era un niño de 9.$"

RustboroCity_Text_WowYouHavePokemon: @ 81E1633
    .string "¿Así que entrenas Pokémon?\n"
    .string "Pues eso no es lo único de la vida.\p"
    .string "También puedes ir a los Concursos\n"
    .string "o jugar con amigos a quién atrapa\l"
    .string "más Pokémon más rápido.\p"
    .string "{PLAYER}: Mhh, curioso que lo digas,\n"
    .string "yo mismo hago eso con {RIVAL}.$"


RustboroCity_Text_CatchRarePokemonIfIGoToSchool: @ 81E1695
	.string "¡Escuela de Entrenadres!$"

RustboroCity_Text_PokemonCanChangeLookFromExp: @ 81E16F4
    .string "La evolución es misteriosa, pero se\n"
    .string "sabe que está relacionada con la\l"
    .string "Energía Infinita, o eso dicen todos.$"


RustboroCity_Text_PokemonChangeShape: @ 81E174B
    .string "¿¡QUÉ ENERGÍA INFINITA NI QUÉ\n"
    .string "SHEDINJA CON MITAD DE VIDA!?\p"
    .string "¡ES TODO UNA CONSPIRACIÓN\n"
    .string "PARA ENCUBRIR EL PROYECTO!$"


RustboroCity_Text_TradePokemonGrowFast: @ 81E1789
    .string "Un Pokémon intercambiado crece más\n"
    .string "rápido, pero también puede llegar a\l"
    .string "desobedecer…$"


RustboroCity_Text_OutOfTheWay: @ 81E17FE
	.string "¡Largo!\n"
	.string "¡Fuera del camino!$"

RustboroCity_Text_WaitDontTakeMyGoods: @ 81E1817
	.string "¡NOOOO ALTOOOO!\p"
	.string "¡DAME ESAS PARTES!$"

RustboroCity_Text_HelpMeIWasRobbed: @ 81E183E
    .string "¡Ey, eres tú! \p"
    .string "¡Eres quien me salvó en el Bosque!\n"
    .string "Debes recuperar mis Partes, ese\l"
    .string "Recluta de bajo estatus las robó…$"


RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel: @ 81E1904
    .string "Se fue corriendo hacia el\n"
    .string "Túnel Rusturf como si no hubiera\l"
    .string "un mañana…$"


RustboroCity_Text_YouGotItThankYou: @ 81E194D
    .string "¿Volviste? Espera… ¡!\n"
    .string "¡SÍ, TRAJISTE LAS PARTES!\p"
    .string "Podré mantener el empleo otro mes…\p"
    .string "¡AQUÍ TIENES UNA SUPERBALL!$"


RustboroCity_Text_YoureLoadedWithItems: @ 81E19E5
	.string "You're loaded with items.\n"
	.string "I can't give you this GREAT BALL.$"

RustboroCity_Text_PleaseComeWithMe: @ 81E1A21
    .string "¡Sígueme, sígueme!$"


RustboroCity_Text_MayHiLetsRegister: @ 81E1A49
    .string "May: ¿EH? ¡¿DESQUICIADO YA TIENE\n"
    .string "UNA MEDALLA DEL GIMNASIO!?\p"
    .string "Como sea… Mi padre me dijo que te\n"
    .string "diera mi número, para checkear tu\l"
    .string "Pokédex de vez en cuando…\p"
    .string "…$"

RustboroCity_Text_RegisteredMay: @ 81E1ADB
	.string "Registered MAY\n"
	.string "in the POKéNAV.$"

RustboroCity_Text_MayPassedBrineyWantToBattle: @ 81E1AFA
    .string "May: Por cierto, ya tengo registrados\n"
    .string "más de 25 Pokémon en la Pokédex.\p"
    .string "Muchos más que tú, pues yo ya\n"
    .string "cuento con la SúperCaña. Pero toma,\l"
    .string "me divertiré vien--\p"
    .string "¡SOLO SI ME VENCES EN COMBATE!\p"


RustboroCity_Text_MayOhHaventRaisedPokemonEnough: @ 81E1BD3
    .string "May: ¡JAJAJA! Desquiciado, ¿tienes\n"
    .string "miedo de perder ante mí?\l"
    .string "Sí, debe ser eso, ¡JA, JA, JA!\p"
    .string "{PLAYER}: {COLOR LIGHT_BLUE} {SHADOW BLUE}(Esa fue la risa más\n"
    .string "sarcástica que haya escuchado…)$"


RustboroCity_Text_MayWantToBattle: @ 81E1C48
    .string "¿¡YA ESTÁ LISTO EL BEBÉ!?\n"
    .string "¡VAMOS, COMBÁTEME!$"


RustboroCity_Text_MayImNotGoingToLose: @ 81E1C84
    .string "May: ¡JA! Pues perderás, no hay nada\n"
    .string "que puedas hacer para vencerme...$"


RustboroCity_Text_MayDefeat: @ 81E1CC1
    .string "¿?\n"
    .string "...\l"
    .string "P-pero...\p"
    .string "¡ARGH! ¿¡PORQUÉ SI HE ATRAPADO\n"
    .string "MÁS POKÉMON!?, ¡YO DEBERÍA GANAR!$"

RustboroCity_Text_MayMrBrineyHint: @ 81E1CE7
    .string "¿Sabes qué? Ahora no te doy nada...\p"
    .string "Por cierto, ese viejo te estaba\n"
    .string "buscando, Desquiciado...$"


RustboroCity_Text_BrendanHiLetsRegister: @ 81E1D7D
	.string "BRENDAN: Oh, hey, {PLAYER}!\p"
	.string "You had a MATCH CALL feature put\n"
	.string "on your POKéNAV! Cool!\p"
	.string "Let's register each other so we can\n"
	.string "get in touch anytime!\p"
	.string "… … … … … …$"

RustboroCity_Text_RegisteredBrendan: @ 81E1E11
	.string "Registered BRENDAN\n"
	.string "in the POKéNAV.$"

RustboroCity_Text_BrendanPassedBrineyWantToBattle: @ 81E1E34
	.string "BRENDAN: By the way, {PLAYER}, I walked\n"
	.string "by MR. BRINEY in PETALBURG WOODS.\p"
	.string "I bet he was on his way home to his\n"
	.string "cottage by the sea.\p"
	.string "{PLAYER}, how's your POKéDEX?\n"
	.string "Have you filled in any pages yet?\p"
	.string "Mine rules.\p"
	.string "Want to have a battle to test how\n"
	.string "far you've progressed?$"

RustboroCity_Text_BrendanNoConfidenceInPokemon: @ 81E1F2F
	.string "BRENDAN: What's the matter? Don't have\n"
	.string "any confidence in your POKéMON?$"

RustboroCity_Text_BrendanWantToBattle: @ 81E1F76
	.string "BRENDAN: What's up?\n"
	.string "Want to have a battle with me?$"

RustboroCity_Text_BrendanIWontGoEasy: @ 81E1FA9
	.string "BRENDAN: I know you just became\n"
	.string "a TRAINER, but I won't go easy!$"

RustboroCity_Text_BrendanDefeat: @ 81E1FE9
	.string "Hmm…\n"
	.string "You're pretty good.$"

RustboroCity_Text_BrendanMrBrineyHint: @ 81E2002
	.string "BRENDAN: By the way, you know\n"
	.string "MR. BRINEY? The guy I just passed?\p"
	.string "I bet you didn't know this, since you\n"
	.string "just moved here, {PLAYER}, but\l"
	.string "MR. BRINEY was once a great sailor.$"

RustboroCity_Text_TunnelNearingCompletion: @ 81E20A6
	.string "“Timesaving tunnel nearing\n"
	.string "completion!”\p"
	.string "…Is what it says on the sign, but\n"
	.string "there's also a big “X” splashed\l"
	.string "across it in red paint…$"

RustboroCity_Text_DevonCorpSign: @ 81E2128
	.string "DEVON CORPORATION\p"
	.string "“For all your living needs, we make\n"
	.string "it all.”$"

RustboroCity_Text_GymSign: @ 81E2167
	.string "RUSTBORO CITY POKéMON GYM\n"
	.string "LEADER: ROXANNE\p"
	.string "“The ROCK-loving honors student!”$"

RustboroCity_Text_DevonCorpBranchOfficeSign: @ 81E21B3
	.string "DEVON CORP. BRANCH OFFICE\p"
	.string "“Access limited to DEVON employees\n"
	.string "and authorized personnel.”$"

RustboroCity_Text_CitySign: @ 81E220B
	.string "RUSTBORO CITY\p"
	.string "“The city probing the integration of\n"
	.string "nature and science.”$"

RustboroCity_Text_TrainersSchoolSign: @ 81E2253
	.string "POKéMON TRAINER'S SCHOOL\p"
	.string "“We'll teach you anything about\n"
	.string "POKéMON!”$"

RustboroCity_Text_CuttersHouse: @ 81E2296
	.string "CUTTER'S HOUSE$"

RustboroCity_Text_DevelopedNewPokenavFeature: @ 81E22A5
    .string "He estado desarrollando una\n"
    .string "función extra para el Pokénav.\p"
    .string "Es un regalo de mi parte por\n"
    .string "ayudarme a recuperar las Partes.$"


RustboroCity_Text_AddedMatchCallPleaseCallMrStone: @ 81E2331
    .string "¡Ahí lo tienes, {PLAYER}!\n"
    .string "¡He añadido la funcionalidad de\l"
    .string "Celular a tu Pokénav!\p"
    .string "Con ella, podrás llamar a--\p"
    .string "{PLAYER}: Entonces, es un Celular\n"
    .string "común y corriente, ¿verdad?\p"
    .string "Investigador: Uhhh… ¿S-sí?\n"
    .string "¡P-pero añadido al Pokénav!\p"
    .string "Como sea, necesito que sepas\p"
	.string "que nadie en Devon sabe de\n"
	.string "las 'Partes'.\p"
	.string "Ahora, ¡Llama al Presidente y\n"
	.string "prueba la función de celular!$"


RustboroCity_Text_PleaseSelectPokenav: @ 81E2449
	.string "Ahora, llama al Presidente.$"

RustboroCity_Text_IdBetterGetBackToWork: @ 81E2464
	.string "Debería volver a trabajar…\n"
	.string "¡Cuídate, {PLAYER}!$"

RustboroCity_Text_YouCanHave2On2Battle: @ 81E249D
	.string "Did you know this?\p"
	.string "You can have a 2-on-2 battle even\n"
	.string "if you're not with another TRAINER.\p"
	.string "If you catch the eyes of two TRAINERS\n"
	.string "when you have two or more POKéMON,\l"
	.string "they'll both challenge you.\p"
	.string "Don't you think it'd be cool if you\n"
	.string "could beat two TRAINERS by yourself?$"
