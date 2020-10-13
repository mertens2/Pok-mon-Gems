LittlerootTown_MapScripts:: @ 81E7DCB
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition: @ 81E7DDB
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	compare VAR_LITTLEROOT_INTRO_STATE, 2
	call_if_eq LittlerootTown_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_SetTwinPos
	compare VAR_LITTLEROOT_TOWN_STATE, 3
	call_if_eq LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
	compare VAR_LITTLEROOT_HOUSES_STATE_MAY, 4
	call_if_eq LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	compare VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4
	call_if_eq LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	compare VAR_OLDALE_RIVAL_STATE, 1
	call_if_eq LittlerootTown_EventScript_MoveRivalFromOldale
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	call_if_eq LittlerootTown_EventScript_SetRivalLeftForRoute103
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1
	call_if_eq LittlerootTown_EventScript_HideMapNamePopup
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	call_if_eq LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	end

LittlerootTown_EventScript_LeftLabAfterDexUpgrade:: @ 81E7E45
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup:: @ 81E7E4B
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103:: @ 81E7E4F
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale:: @ 81E7E53
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent:: @ 81E7E5C
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveMomToMaysDoor:: @ 81E7E67
	setobjectxyperm 4, 14, 8
	return

LittlerootTown_EventScript_SetTwinPos:: @ 81E7E6F
	compare VAR_LITTLEROOT_TOWN_STATE, 0
	goto_if_eq LittlerootTown_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm 1, 10, 1
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetTwinGuardingRoutePos:: @ 81E7E86
	setobjectxyperm 1, 7, 2
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_DOWN
	return

LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos:: @ 81E7E92
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setobjectmovementtype 4, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_SetMomInFrontOfDoorMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale:: @ 81E7EB1
	setobjectxyperm 4, 5, 9
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale:: @ 81E7EB9
	setobjectxyperm 4, 14, 9
	return

LittlerootTown_OnFrame: @ 81E7EC1
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale:: @ 81E7EDB
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 255, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale:: @ 81E7EF9
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 255, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithMom:: @ 81E7F17
	delay 15
	playse SE_DANSA
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject 4
	applymovement 4, LittlerootTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement 4, LittlerootTown_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_MomExitHouse: @ 81E7F98
	walk_down
	step_end

LittlerootTown_Movement_MomApproachPlayerAtTruck: @ 81E7F9A
	walk_down
	walk_in_place_fastest_left
	step_end

LittlerootTown_Movement_MomApproachDoor: @ 81E7F9D
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse: @ 81E7FA1
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor: @ 81E7FA4
	delay_16
	delay_8
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse: @ 81E7FA9
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck: @ 81E7FAC
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_BeginDexUpgradeScene:: @ 81E7FB1
	lockall
	playse SE_PIN
	applymovement 8, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 255, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp: @ 81E7FE2
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade:: @ 81E7FEC
	addobject 8
	addobject 7
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale:: @ 81E8004
	setobjectxy 7, 6, 10
	setobjectxy 8, 5, 10
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale:: @ 81E8013
	setobjectxy 7, 13, 10
	setobjectxy 8, 14, 10
	end

LittlerootTown_EventScript_FatMan:: @ 81E8022
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_NPC
	end

LittlerootTown_EventScript_Boy:: @ 81E802B
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_NPC
	end

LittlerootTown_EventScript_Twin:: @ 81E8034
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
	compare VAR_LITTLEROOT_TOWN_STATE, 0
	goto_if_ne LittlerootTown_EventScript_GoSaveBirch
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoSaveBirch:: @ 81E805D
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement 1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

LittlerootTown_EventScript_YouSavedBirch:: @ 81E807A
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoodLuck:: @ 81E8087
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft:: @ 81E8091
	lockall
	applymovement 1, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement 1, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon:: @ 81E80AD
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement 1, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft: @ 81E80D1
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute: @ 81E80DF
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft: @ 81E80E1
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_fastest_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute: @ 81E80EB
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_EventScript_NeedPokemonTriggerRight:: @ 81E80EF
	lockall
	applymovement 1, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement 1, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_Movement_TwinApproachPlayerRight: @ 81E810B
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight: @ 81E8118
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

LittlerootTown_EventScript_GoSaveBirchTrigger:: @ 81E811F
	lockall
	applymovement 1, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement 1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_TownSign:: @ 81E8151
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end

LittlerootTown_EventScript_BirchsLabSign:: @ 81E815A
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end

LittlerootTown_EventScript_BrendansHouseSign:: @ 81E8163
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_PlayersHouseSignMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale:: @ 81E817D
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale:: @ 81E8186
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign:: @ 81E818F
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_BirchsHouseSignMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_BirchsHouseSignMale:: @ 81E81A9
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale:: @ 81E81B2
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	return

LittlerootTown_EventScript_GiveRunningShoesTrigger0:: @ 81E81BB
	lockall
	setvar VAR_0x8008, 0
	setobjectxy 4, 10, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger1:: @ 81E81CE
	lockall
	setvar VAR_0x8008, 1
	setobjectxy 4, 11, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger2:: @ 81E81E1
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger3:: @ 81E81ED
	lockall
	setvar VAR_0x8008, 3
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger4:: @ 81E81F9
	lockall
	setvar VAR_0x8008, 4
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger5:: @ 81E8205
	lockall
	setvar VAR_0x8008, 5
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger:: @ 81E8211
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_MomNoticePlayerMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_MomNoticePlayerFemale
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_SetHomeDoorCoordsMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_MomReturnHomeMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_MomReturnHomeFemale
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale:: @ 81E8281
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale:: @ 81E828C
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_MomNoticePlayerMale:: @ 81E8297
	applymovement 4, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

LittlerootTown_EventScript_MomNoticePlayerFemale:: @ 81E82A2
	applymovement 4, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale:: @ 81E82AD
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_EventScript_MomApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_EventScript_MomApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerMale2
	compare VAR_0x8008, 3
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerMale3
	compare VAR_0x8008, 4
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerMale4
	compare VAR_0x8008, 5
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerMale5
	return

LittlerootTown_EventScript_MomApproachPlayerFemale:: @ 81E82F0
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_EventScript_MomApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_EventScript_MomApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerFemale2
	compare VAR_0x8008, 3
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerFemale3
	compare VAR_0x8008, 4
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerFemale4
	compare VAR_0x8008, 5
	call_if_eq LittlerootTown_EventScript_MomApproachPlayerFemale5
	return

LittlerootTown_EventScript_MomApproachPlayer0:: @ 81E8333
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayer0
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayer1:: @ 81E8348
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayer1
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale2:: @ 81E835D
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerMale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale3:: @ 81E8372
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerMale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale4:: @ 81E8387
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerMale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale5:: @ 81E839C
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerMale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale2:: @ 81E83B1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerFemale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale3:: @ 81E83C6
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerFemale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale4:: @ 81E83DB
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerFemale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale5:: @ 81E83F0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	applymovement 4, LittlerootTown_Movement_MomApproachPlayerFemale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale:: @ 81E8405
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_EventScript_MomReturnHome0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_EventScript_MomReturnHome1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_EventScript_MomReturnHomeMale2
	compare VAR_0x8008, 3
	call_if_eq LittlerootTown_EventScript_MomReturnHomeMale3
	compare VAR_0x8008, 4
	call_if_eq LittlerootTown_EventScript_MomReturnHomeMale4
	compare VAR_0x8008, 5
	call_if_eq LittlerootTown_EventScript_MomReturnHomeMale5
	return

LittlerootTown_EventScript_MomReturnHomeFemale:: @ 81E8448
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_EventScript_MomReturnHome0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_EventScript_MomReturnHome1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_EventScript_MomReturnHomeFemale2
	compare VAR_0x8008, 3
	call_if_eq LittlerootTown_EventScript_MomReturnHomeFemale3
	compare VAR_0x8008, 4
	call_if_eq LittlerootTown_EventScript_MomReturnHomeFemale4
	compare VAR_0x8008, 5
	call_if_eq LittlerootTown_EventScript_MomReturnHomeFemale5
	return

LittlerootTown_EventScript_MomReturnHome0:: @ 81E848B
	applymovement 4, LittlerootTown_Movement_MomReturnHome0
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHome1:: @ 81E8496
	applymovement 4, LittlerootTown_Movement_MomReturnHome1
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale2:: @ 81E84A1
	applymovement 4, LittlerootTown_Movement_MomReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale3:: @ 81E84C7
	applymovement 4, LittlerootTown_Movement_MomReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale4:: @ 81E84ED
	applymovement 4, LittlerootTown_Movement_MomReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale5:: @ 81E8513
	applymovement 4, LittlerootTown_Movement_MomReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale2:: @ 81E8539
	applymovement 4, LittlerootTown_Movement_MomReturnHomeFemale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale3:: @ 81E855F
	applymovement 4, LittlerootTown_Movement_MomReturnHomeFemale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale4:: @ 81E8585
	applymovement 4, LittlerootTown_Movement_MomReturnHomeFemale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale5:: @ 81E85AB
	applymovement 4, LittlerootTown_Movement_MomReturnHomeFemale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_Movement_MomApproachPlayer0: @ 81E85D1
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayer1: @ 81E85D8
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayerMale2: @ 81E85DF
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale3: @ 81E85E4
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale4: @ 81E85EA
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale5: @ 81E85ED
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale2: @ 81E85F1
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale3: @ 81E85F5
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale4: @ 81E85F8
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale5: @ 81E85FE
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomReturnHome0: @ 81E8603
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHome1: @ 81E8609
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHomeMale2: @ 81E860F
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale3: @ 81E8615
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale4: @ 81E861C
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale5: @ 81E8620
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale2: @ 81E8625
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale3: @ 81E862A
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale4: @ 81E862E
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale5: @ 81E8635
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_Movement_MomExitThroughDoor: @ 81E863B
	walk_up
	step_end

LittlerootTown_EventScript_Mom:: @ 81E863D
	lock
	faceplayer
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LittlerootTown_EventScript_SetHomeDoorCoordsMale
	compare VAR_RESULT, FEMALE
	call_if_eq LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	applymovement 4, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement 4, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat 4, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetReceivedRunningShoes:: @ 81E8686
	removeobject 4
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

LittlerootTown_EventScript_GiveRunningShoes:: @ 81E8693
	msgbox LittlerootTown_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	changeframe 14
	msgbox LittlerootTown_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	changeframe 1
	giveegg SPECIES_SLAKOTH
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	removeobject 4
	closemessage
	delay 30
	return

LittlerootTown_SignGordo::
	msgbox LittlerootTown_Text_GordoHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end
LittlerootTown_SignNina::
	msgbox LittlerootTown_Text_NinaHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end
LittlerootTown_SignVacia::
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_ge LittlerootTown_SignTabithasHouse
	msgbox LittlerootTown_Text_EmptyHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end
LittlerootTown_SignTabithasHouse::
	msgbox LittlerootTown_Text_TabithaHouse, MSGBOX_SIGN, MSGBOX_SUB_DEFAULT
	end
LittlerootTown_Text_OurNewHomeLetsGoInside: @ 81E86BC
	.string "Mamá: ¡{PLAYER}, llegamos, cariño!\p"
	.string "Debió ser incómodo viajar en camión…\n"
	.string "Perdón, es que así era más barato…\p"
	.string "Bueno, esto es PUEBLO LITTLEROOT.\p"
	.string "¿A que es bonito? ¡Vamos a vivir\n"
	.string "en un pueblo con 7 habitantes!\p"
	.string "Sin dudas es aburrido, pero se siente\n"
	.string "la tranquilidad rural, ¿No crees?\p"
	.string "¡Hasta tienes cuarto, {PLAYER}!\p"
	.string "Bueno, ya, entremos.$"

LittlerootTown_Text_WaitPlayer: @ 81E87E1
	.string "Mamá: ¡Alto, {PLAYER}!$"

LittlerootTown_Text_WearTheseRunningShoes: @ 81E87F0
	.string "MOM: ¡{PLAYER}! ¿Ya te\n"
	.string "presentaste al Profesor Birch?\p"
	.string "¡Oh! ¡Que Pokémon más lindo!\n"
	.string "Seguro te lo dio el Profe Birch.\p"
	.string "¡Eres igual a tu padre!\n"
	.string "¡Ambos son adorables con los Pokémon!\p"
	.string "¡Oh! ¡Hablando de eso!\n"
	.string "Aquí tengo algo muy especial para\l"
	.string "ti, de parte de tu padre!$"

LittlerootTown_Text_ExplainRunningShoes: @ 81E894F
	.string "Mamá: ¡Es un Huevo Misterioso!$"

LittlerootTown_Text_ComeHomeIfAnythingHappens: @ 81E8A03
	.string "¡Te ves igual que tu padre\n"
	.string "y elegiste el mismo ínicial\l"
	.string "que él cuando viajó a Hoenn!\p"
	.string "¡Seguro viven grandes aventuras\n"
	.string "juntos, justo como él!\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Pensar que ahora tienes un Pokémon…\n"
	.string "Wow…\l"
	.string "Seguro tu padre estaría orgulloso.\p"
	.string "…Pero, en serio, sé cuidadoso.\p"
	.string "Hay unos locos por ahí discutiendo\n"
	.string "sobre agua y rocas… ¡Bueno adiós!$"

LittlerootTown_Text_CanUsePCToStoreItems: @ 81E8ACF
	.string "La PC permite guardar toda clase de\n"
	.string "cosas. ¡Hasta Pokémon!\p"
	.string "¡La tecnología es increíble!$"

LittlerootTown_Text_BirchSpendsDaysInLab: @ 81E8B25
	.string "El Profesor Birch pasa días estudiando\n"
	.string "en el Laboratorio, después, sale a hacer\l"
	.string "investigaciones de campo…\p"
	.string "¿Y ese gordo cuándo pasa tiempo con\n"
	.string "su familia?$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut: @ 81E8BB8
	.string "¡Um, um, um!\p"
	.string "Si vas ahora sin Pokémon, te van a\n"
	.string "atacar despiadados Pokémon salvajes!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon: @ 81E8C07
	.string "Es peligroso ir solo.\n"
	.string "Y no tengo espadas para darte…$"

LittlerootTown_Text_CanYouGoSeeWhatsHappening: @ 81E8C3A
	.string "¡Ey, hola!\p"
	.string "¡Allá fuera hay Pokémon horribles!\n"
	.string "¡Escucho sus Alaridos!\p"
	.string "Quisiera ir… Pero no tengo Pokémon.\n"
	.string "Tu vida parece no tener valor…\p"
	.string "¿Podrías ir a ver qué pasa por\n"
	.string "mí, y arriesgar tu vida?$"

LittlerootTown_Text_YouSavedBirch: @ 81E8CE3
	.string "¡Salvaste al Profe!\n"
	.string "¡Y no moriste!$"

LittlerootTown_Text_GoodLuckCatchingPokemon: @ 81E8D07
	.string "¿Quires atrapar Pokémon?\n"
	.string "¡Buena suerte!$"

LittlerootTown_Text_TownSign: @ 81E8D32
	.string "Pueblo littleroot\n"
	.string "“Un pueblo con matices hermosos.”$"

LittlerootTown_Text_ProfBirchsLab: @ 81E8D69
	.string "Laboratorio del Profe Birch$"

LittlerootTown_Text_PlayersHouse: @ 81E8D83
	.string "Familia Senri$"

LittlerootTown_Text_ProfBirchsHouse: @ 81E8D8E
	.string "Familia Birch$"
LittlerootTown_Text_GordoHouse:
	.string "Familia Bragg-McFadden$"
LittlerootTown_Text_NinaHouse:
	.string "Familia Jewel$"
LittlerootTown_Text_EmptyHouse:
	.string "----------$"
LittlerootTown_Text_TabithaHouse:
	.string "Casa de Tabitha$"
LittlerootTown_Text_BirchSomethingToShowYouAtLab: @ 81E8DA2
	.string "PROFE Birch: ¡Bueno, bueno {PLAYER}{KUN}!\n"
	.string "¡Eso fue fantástico, eres lo más!\p"
	.string "Sabía que podía esperar mucho del hijo\n"
	.string "de un Líder del Gimnasio, pero nunca\l"
	.string "esperé que me salvara de un Zigzagoon\p"
	.string "y luego completara la Dex de Hoenn…\n"
	.string "Por cierto, tráela al laboratorio,\p"
	.string "junto con el resto de ti, tengo un regalo\n"
	.string "que hacerte.$"
