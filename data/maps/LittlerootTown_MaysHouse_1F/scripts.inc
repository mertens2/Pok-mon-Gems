LittlerootTown_MaysHouse_1F_MapScripts:: @ 81F88A5
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_MaysHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_MaysHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_MaysHouse_1F_OnFrame
	.byte 0

LittlerootTown_MaysHouse_1F_OnLoad: @ 81F88B5
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_lt LittlerootTown_MaysHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_MaysHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_MaysHouse_1F_EventScript_SetMovingBoxes:: @ 81F88CA
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, 1
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, 1
	return

LittlerootTown_MaysHouse_1F_EventScript_CheckShowShoesManual:: @ 81F88DD
	checkplayergender
	compare VAR_RESULT, FEMALE
	goto_if_eq LittlerootTown_MaysHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_MaysHouse_1F_EventScript_ShowRunningShoesManual:: @ 81F88EA
	setmetatile 6, 7, METATILE_BrendansMaysHouse_BookOnTable, 1
	return

LittlerootTown_MaysHouse_1F_OnTransition: @ 81F88F4
	compare VAR_LITTLEROOT_INTRO_STATE, 3
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToDoor
	compare VAR_LITTLEROOT_INTRO_STATE, 5
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToStairs
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToStairs:: @ 81F8916
	setobjectxyperm 1, 2, 4
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToTV:: @ 81F8922
	setobjectxyperm 1, 6, 5
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_MaysHouse_1F_EventScript_MoveMomToDoor:: @ 81F892E
	setobjectxyperm 1, 1, 8
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
LittlerootTown_MaysHouse_1F_OnFrame: @ 81F893A
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_MaysHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_MaysHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_MaysHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1, LittlerootTown_MaysHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_MaysHouse_1F_EventScript_GoUpstairsToSetClock:: @ 81F8964
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs
	applymovement 1, LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_MAYS_HOUSE_2F, 255, 1, 1
	waitstate
	releaseall
	end

LittlerootTown_MaysHouse_1F_Movement_PushTowardStairs: @ 81F898A
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_EventScript_EnterHouseMovingIn:: @ 81F898C
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, FEMALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_MaysHouse_1F_EventScript_PetalburgGymReport:: @ 81F899D
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	goto PlayersHouse_1F_EventScript_PetalburgGymReportFemale
	end

LittlerootTown_MaysHouse_1F_EventScript_YoureNewNeighbor:: @ 81F89AE
	lockall
	playse SE_PIN
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 4, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	applymovement 4, LittlerootTown_MaysHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2
	releaseall
	end

LittlerootTown_MaysHouse_1F_Movement_RivalMomApproach: @ 81F89EC
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RivalsHouse_1F_EventScript_RivalMom:: @ 81F89F3
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE103, RivalsHouse_1F_EventScript_GoHomeEverySoOften
	goto_if_set FLAG_SYS_POKEMON_GET, RivalsHouse_1F_EventScript_RivalIsOnRoute103
	compare VAR_LITTLEROOT_RIVAL_STATE, 3
	goto_if_eq RivalsHouse_1F_EventScript_RivalTooBusy
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_LikeChildLikeFather, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalTooBusy:: @ 81F8A1F
	msgbox RivalsHouse_1F_Text_TooBusyToNoticeVisit, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalIsOnRoute103:: @ 81F8A29
	msgbox RivalsHouse_1F_Text_WentOutToRoute103, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_GoHomeEverySoOften:: @ 81F8A33
	msgbox RivalsHouse_1F_Text_ShouldGoHomeEverySoOften, MSGBOX_DEFAULT
	release
	end

RivalsHouse_1F_EventScript_RivalSibling:: @ 81F8A3D
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	msgbox RivalsHouse_1F_Text_DoYouHavePokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_MaysHouse_1F_EventScript_GoSeeRoom:: @ 81F8A4C
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, FEMALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival0:: @ 81F8A67
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival1:: @ 81F8A73
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival2:: @ 81F8A7F
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_MaysHouse_1F_EventScript_MeetRival
	end

LittlerootTown_MaysHouse_1F_EventScript_MeetRival:: @ 81F8A8B
	playse SE_KAIDAN
	delay 10
	addobject 7
	delay 30
	playse SE_PIN
	applymovement 7, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 7, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 1
	call_if_ne LittlerootTown_MaysHouse_1F_EventScript_PlayerFaceMay
	playbgm MUS_GIRL_SUP, 1
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer2
	msgbox RivalsHouse_1F_Text_MayWhoAreYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs2
	playse SE_KAIDAN
	removeobject 7
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MAY
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_MaysHouse_1F_EventScript_PlayerFaceMay:: @ 81F8B2A
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer0:: @ 81F8B35
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer0
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer1:: @ 81F8B40
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer1
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayApproachPlayer2:: @ 81F8B4B
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer2
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer0: @ 81F8B56
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer1: @ 81F8B5E
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayApproachPlayer2: @ 81F8B62
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs0:: @ 81F8B6A
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit0
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs0
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs1:: @ 81F8B7C
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit1
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs1
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_EventScript_MayGoUpstairs2:: @ 81F8B8E
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit2
	applymovement 7, LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs2
	waitmovement 0
	return

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit0: @ 81F8BA0
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit1: @ 81F8BA4
	delay_16
	delay_8
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_PlayerWatchMayExit2: @ 81F8BAB
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs0: @ 81F8BAF
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs1: @ 81F8BB5
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	step_end

LittlerootTown_MaysHouse_1F_Movement_MayGoUpstairs2: @ 81F8BBF
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end
RivalsHouse_1F_Text_OhYoureTheNewNeighbor: @ 81F8BC5
	.string "¡Hola, {PLAYER}{KUN}!, ¡Al fin\n"
	.string "vuelve Norman a su pueblito!\p"
	.string "Nuestro retoño debe tener tu misma\n"
	.string "edad, poco más, poco menos.\p"
	.string "Parecía que no le importaba si tenía\n"
	.string "o no nuevos amigos…\p"
	.string "Es todo un caso…$"

RivalsHouse_1F_Text_LikeChildLikeFather: @ 81F8CA5
	.string "De tal palo, tal astilla.\p"
	.string "Mi esposo está en busca de Pokémon\n"
	.string "salvajes para nuestro retoño.\p"
	.string "Si no está en el Laboratorio, estará\n"
	.string "buscando info seguro, ja ja ja.$"

RivalsHouse_1F_Text_TooBusyToNoticeVisit: @ 81F8D37
	.string "¡{RIVAL} es todo un caso!\p"
	.string "Creo que está con la mente muy\n"
	.string "ocupada pensando en Pokémon como\l"
	.string "para saber que viniste, {PLAYER}{KUN}.$"

RivalsHouse_1F_Text_WentOutToRoute103: @ 81F8D93
	.string "Ah sí, {RIVAL} fue a la Ruta 103\n"
	.string "Hace poco. Creo que está investigando.\p"
	.string "De tal palo, tal astilla.\n"
	.string "{RIVAL} no puede quedarse en casa.$"
	
RivalsHouse_1F_Text_ShouldGoHomeEverySoOften: @ 81F8E01
	.string "Creo que es fantástico para las\n"
	.string "personas viajar con los Pokémon.\p"
	.string "Pero deberías volver a tu casa de\n"
	.string "vez en cuando, no seas como tu padre.\p"
	.string "Quizá no lo diga, pero tu madre se\n"
	.string "preocupa por ti, {PLAYER}{KUN}.$"

RivalsHouse_1F_Text_MayWhoAreYou: @ 81F8EC6
	.string "¿Eh?\p"
	.string "¡¿QUIÉN ERES Y QUÉ HACÍAS EN\n"
	.string "MI CUARTO?!\l"
	.string "¡…! … … ¿…? … … … …\p"
	.string "Oh, eres {PLAYER}{KUN}.\n"
	.string "Eh… Perdón por el golpe…\p"
	.string "Soy MAY. Te diré DESQUICIADO\n"
	.string "Encantada de conocerte, supongo…\p"
	.string "Yo… Quiero ayudar a mi padre\n"
	.string "con su investigación, para\l"
	.string "que pase más tiempo en casa…\p"
	.string "Me contó mucho sobre ti, también.\n"
	.string "Acabas de mudarte desde Johto, ¿no?.\p"
	.string "Me dijo que debíamos ser amigos,\n"
	.string "{PLAYER}{KUN}, pero eso sería una\l"
	.string "distracción en mi investigación.\p"
	.string "Además, apenas te conozco.\p"
	.string "Ah, si. Adiós. Debo irme.\p"
	.string "Atraparé algunos Pokémon raros\n"
	.string "para ayudar a papá. Si consigues\l"
	.string "Pokémon, ¡Te destrozaré en combate!\p"
	.string "¡Desquiciado, vete de mi casa!$"

RivalsHouse_1F_Text_BrendanWhoAreYou: @ 81F90B4
	.string "¡Hey!\n"
	.string "Tú…\p"
	.string "¡¿QUÉ HACÍAS EN MI CUARTO, LOCA?!\p"
	.string "Ah, eres {PLAYER}… Igual, loca.\n"
	.string "¿Te mudaste desde Johto, y lo\l"
	.string "primero que se te ocurre es esto?\p"
	.string "Seguro mamá te dejó entrar, es así\n"
	.string "de tonta… Como sea, eres hija de\l"
	.string "un Líder del Gimnasio, ¿No?\p"
	.string "Soy BRENDAN, y mi padre tampco está\n"
	.string "en casa mucho tiempo…\p"
	.string "Por eso quiero ayudarlo a invesigar,\n"
	.string "para que termine más rápido y pase\l"
	.string "más tiempo con nosotros…\p"
	.string "Hablando del tema…\p"
	.string "Debo ir a recolectar información\n"
	.string "sobre Pokémon salvajes.\p"
	.string "¡Hasta luego, loca!$"

RivalsHouse_1F_Text_DoYouHavePokemon: @ 81F9262
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Ya no eres inútil y ya\n"
	.string "conseguiste un Pokémon?$"
