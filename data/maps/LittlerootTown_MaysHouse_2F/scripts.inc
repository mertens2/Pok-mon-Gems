LittlerootTown_MaysHouse_2F_MapScripts:: @ 81F9296
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_MaysHouse_2F_OnWarp
	.byte 0

LittlerootTown_MaysHouse_2F_OnTransition: @ 81F92A1
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	call_if_lt LittlerootTown_MaysHouse_2F_EventScript_CheckSetReadyToMeetMay
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	call_if_ge LittlerootTown_MaysHouse_2F_EventScript_CheckShouldUpdateMayPos
	compare VAR_LITTLEROOT_INTRO_STATE, 4
	call_if_eq PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckShouldUpdateMayPos:: @ 81F92CD
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos
	compare VAR_BIRCH_LAB_STATE, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_Ret
	goto LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos

LittlerootTown_MaysHouse_2F_EventScript_TryUpdateMayPos:: @ 81F92E6
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_Ret
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
	goto_if_ge LittlerootTown_MaysHouse_2F_EventScript_Ret
	setobjectxyperm 1, 8, 2
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_2F_EventScript_Ret:: @ 81F9309
	return

LittlerootTown_MaysHouse_2F_EventScript_CheckSetReadyToMeetMay:: @ 81F930A
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_SetReadyToMeetMay
	return

LittlerootTown_MaysHouse_2F_EventScript_SetReadyToMeetMay:: @ 81F9317
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

LittlerootTown_MaysHouse_2F_OnWarp: @ 81F931D
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_MaysHouse_2F_EventScript_CheckInitDecor
	.2byte 0

LittlerootTown_MaysHouse_2F_EventScript_CheckInitDecor:: @ 81F9327
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq SecretBase_EventScript_InitDecorations
	end

LittlerootTown_MaysHouse_2F_EventScript_RivalsPokeBall:: @ 81F9334
	lockall
	compare VAR_LITTLEROOT_RIVAL_STATE, 2
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMay
	msgbox RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_MeetMay:: @ 81F934A
	delay 10
	addobject 1
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayEnters
	waitmovement 0
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 1, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_GIRL_SUP, 1
	compare VAR_FACING, DIR_NORTH
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMaySouth
	compare VAR_FACING, DIR_WEST
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayWest
	compare VAR_FACING, DIR_EAST
	call_if_eq LittlerootTown_MaysHouse_2F_EventScript_MeetMayEast
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_MeetMayNorth:: @ 81F93BA
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayNorth
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCNorth
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMaySouth:: @ 81F93E9
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerSouth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMaySouth
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCSouth
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMayWest:: @ 81F9418
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCWest
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_EventScript_MeetMayEast:: @ 81F9440
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox RivalsHouse_2F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayEast
	applymovement 1, LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCEast
	waitmovement 0
	return

LittlerootTown_MaysHouse_2F_Movement_MayEnters: @ 81F946F
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerNorth: @ 81F9473
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCNorth: @ 81F9479
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayNorth: @ 81F9483
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerSouth: @ 81F948B
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCSouth: @ 81F948F
	walk_up
	walk_in_place_fastest_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMaySouth: @ 81F9497
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerWest: @ 81F949D
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCWest: @ 81F94A4
	walk_up
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayWest: @ 81F94A9
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayApproachPlayerEast: @ 81F94AD
	walk_right
	walk_right
	walk_down
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_2F_Movement_MayWalkToPCEast: @ 81F94B2
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_2F_Movement_PlayerWatchMayEast: @ 81F94BB
	delay_16
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

RivalsHouse_2F_EventScript_Rival:: @ 81F94C1
	lockall
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, RivalsHouse_2F_EventScript_RivalPostLilycove
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RivalsHouse_2F_EventScript_May
	compare VAR_RESULT, FEMALE
	goto_if_eq RivalsHouse_2F_EventScript_Brendan
	end

RivalsHouse_2F_EventScript_May:: @ 81F94E3
	msgbox RivalsHouse_2F_Text_MayGettingReady, MSGBOX_DEFAULT
	releaseall
	end

RivalsHouse_2F_EventScript_Brendan:: @ 81F94ED
	msgbox RivalsHouse_2F_Text_BrendanGettingReady, MSGBOX_DEFAULT
	releaseall
	end

RivalsHouse_2F_EventScript_RivalPostLilycove:: @ 81F94F7
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq RivalsHouse_2F_EventScript_MayPostLilycove
	compare VAR_RESULT, FEMALE
	call_if_eq RivalsHouse_2F_EventScript_BrendanPostLilycove
	setflag FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE
	releaseall
	end

RivalsHouse_2F_EventScript_MayPostLilycove:: @ 81F951D
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, RivalsHouse_2F_EventScript_MayWhereShouldIGoNext
	msgbox RivalsHouse_2F_Text_MayJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_BrendanPostLilycove:: @ 81F952F
	goto_if_set FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext
	msgbox RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_MayWhereShouldIGoNext:: @ 81F9541
	msgbox RivalsHouse_2F_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
	return

RivalsHouse_2F_EventScript_BrendanWhereShouldIGoNext:: @ 81F954A
	msgbox RivalsHouse_2F_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
	return

LittlerootTown_MaysHouse_2F_EventScript_PC:: @ 81F9553
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_CheckRivalsPC
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_2F_EventScript_CheckPlayersPC
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckRivalsPC:: @ 81F956C
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_CheckPlayersPC:: @ 81F9576
	setvar VAR_0x8004, 2
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

LittlerootTown_MaysHouse_2F_EventScript_TurnOffPlayerPC:: @ 81F958F
	setvar VAR_0x8004, 2
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

MaysHouse_2F_EventScript_Zapatillas::
	lockall
	msgbox MaysHouse_2F_Text_Zapatos, MSGBOX_DEFAULT
	removeobject 17
	setflag FLAG_SYS_B_DASH
	playfanfare MUS_FANFA4
	waitfanfare
	setflag FLAG_ZAPATOS
	releaseall
	end

MaysHouse_2F_Text_Zapatos:
	.string "Son Zapatos... Debería calzarme.\n"
	.string "{PLAYER} se calzó$"

RivalsHouse_2F_Text_MayWhoAreYou: @ 81F959C
	.string "¿Eh?\n"
	.string "¡¿QUIÉN ERES Y QUÉ HACES EN\n"
	.string "MI CUARTO?!\n"
	.string "¡…! … … ¿…? … … … …\p"
	.string "Oh, eres {PLAYER}{KUN}.\n"
	.string "Eh... Perdón por el golpe...\p"
	.string "Yo… Soy MAY. Te diré DESQUICIADO\n"
	.string "Encantada de conocerte, supongo\p"
	.string "Yo… Quiero ayudar a mi padre\n"
	.string "con su investigación, para\l"
	.string "que pase más tiempo en casa...\p"
	.string "Me contó mucho sobre ti, también.\n"
	.string "Acabas de mudarte desde Johto, ¿no?.\p"
	.string "Me dijo que debíamos ser amigos,\n"
	.string "{PLAYER}{KUN}, pero eso sería una\l"
	.string "distracción en mi investigación.\p"
	.string "Además, apenas te conozco.\p"
	.string "Ah, si. Adiós. Debo irme.\p"
	.string "Atraparé algunos POKéMON raros\n"
	.string "para ayudar a papá. Si consigues\n"
	.string "POKéMON, ¡Te destrozaré en combate!\p"
	.string "¡Desquiciado, vete de mi cuarto!$"

RivalsHouse_2F_Text_MayGettingReady: @ 81F978A
	.string "¡POKéMON ya curados!\n"
	.string "Objetos listos y…$"

RivalsHouse_2F_Text_BrendanWhoAreYou: @ 81F97B4
	.string "¡Hey!\n"
	.string "Tú…\p"
	.string "¡¿QUÉ HACES EN MI CUARTO, LOCA?!\p"
	.string "Ah, eres {PLAYER}... Igual, loca.\n"
	.string "¿Te mudaste desde Johto, y lo\l"
	.string "primero que se te ocurre es esto?\p"
	.string "Seguro mamá te dejó entrar, es así\n"
	.string "de tonta... Como sea, eres hija de\l"
	.string "un Líder del Gimnasio, ¿No?\p"
	.string "Soy BRENDAN, y mi padre tampco está\n"
	.string "en casa mucho tiempo...\p"
	.string "Por eso quiero ayudarlo a invesigar,\n"
	.string "para que termine más rápido y pase\l"
	.string "más tiempo con nosotros...\p"
	.string "Hablando del tema…\p"
	.string "Debo ir a recolectar información\n"
	.string "sobre POKéMON salvajes.\p"
	.string "¡Hasta luego, loca!$"

RivalsHouse_2F_Text_BrendanGettingReady: @ 81F9962
	.string "POKéMON al fin curados…\n"
	.string "Objetos guardados y…$"

RivalsHouse_2F_Text_ItsRivalsPokeBall: @ 81F9991
	.string "¡Es la Ball de {RIVAL}! Tirada...\p"
	.string "¿Qué no tienen estantes?.$"

RivalsHouse_2F_Text_MayJustCheckingMyPokedex: @ 81F99C9
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "I was just checking my POKéDEX.\p"
	.string "There's still a lot of POKéMON that\n"
	.string "I've seen but haven't caught.\p"
	.string "And there are many others that\n"
	.string "I think will evolve.\p"
	.string "I wonder where I should go catch\n"
	.string "some POKéMON next?$"

RivalsHouse_2F_Text_MayWhereShouldIGoNext: @ 81F9A9E
	.string "MAY: I wonder where I should go catch\n"
	.string "some POKéMON next?\p"
	.string "Wouldn't it be funny if we ran into each\n"
	.string "other, {PLAYER}{KUN}?$"

RivalsHouse_2F_Text_BrendanJustCheckingMyPokedex: @ 81F9B0D
	.string "BRENDAN: Hey, it's {PLAYER}.\p"
	.string "I was just checking out my POKéDEX.\p"
	.string "There are still many POKéMON that\n"
	.string "I need to catch, I know, but this\l"
	.string "is looking pretty good.\p"
	.string "Checking this POKéDEX out gives me\n"
	.string "the urge to hit the road again.$"

RivalsHouse_2F_Text_BrendanWhereShouldIGoNext: @ 81F9BE7
	.string "BRENDAN: I'm having a hard time deciding\n"
	.string "where I should catch POKéMON next.\p"
	.string "Hey, {PLAYER}, if I see you while I'm out\n"
	.string "catching POKéMON, I can pitch you a\l"
	.string "battle if you'd like.$"
