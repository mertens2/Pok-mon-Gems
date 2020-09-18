LittlerootTown_BrendansHouse_1F_MapScripts:: @ 81F7755
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad: @ 81F7765
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_lt LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes:: @ 81F777A
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, 1
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, 1
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual:: @ 81F778D
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual:: @ 81F779A
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, 1
	return

LittlerootTown_BrendansHouse_1F_OnTransition: @ 81F77A4
	compare VAR_LITTLEROOT_INTRO_STATE, 3
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	compare VAR_LITTLEROOT_INTRO_STATE, 5
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	compare VAR_LITTLEROOT_INTRO_STATE, 6
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs:: @ 81F77C6
	setobjectxyperm 1, 8, 4
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV:: @ 81F77D2
	setobjectxyperm 1, 4, 5
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor:: @ 81F77DE
	setobjectxyperm 1, 9, 8
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame: @ 81F77EA
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock:: @ 81F7814
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement 1, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 255, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs: @ 81F783A
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn:: @ 81F783C
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport:: @ 81F784D
	lockall
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 1  @ Object event ID for Mom
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor:: @ 81F785E
	lockall
	playse SE_PIN
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 4, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement 4, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach: @ 81F789C
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom:: @ 81F78A3
	lockall
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0:: @ 81F78BE
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1:: @ 81F78CA
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2:: @ 81F78D6
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival:: @ 81F78E2
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
	call_if_ne LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_BOY_SUP, 1
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 0
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	compare VAR_0x8008, 1
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	compare VAR_0x8008, 2
	call_if_eq LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_KAIDAN
	removeobject 7
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan:: @ 81F7981
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0:: @ 81F798C
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1:: @ 81F7997
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2:: @ 81F79A2
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0: @ 81F79AD
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1: @ 81F79B5
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2: @ 81F79B9
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0:: @ 81F79C1
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1:: @ 81F79D3
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2:: @ 81F79E5
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement 7, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0: @ 81F79F7
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1: @ 81F79FB
	delay_16
	delay_8
	walk_in_place_fastest_right
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2: @ 81F7A02
	delay_16
	delay_8
	walk_in_place_fastest_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0: @ 81F7A06
	walk_in_place_fastest_right
	walk_right
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1: @ 81F7A0C
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

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2: @ 81F7A16
	walk_in_place_fastest_left
	walk_left
	walk_in_place_fastest_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere: @ 81F7A1C
	.string "Mamá: ¿Hermoso, no, {PLAYER}?\n"
	.string "¡Aquí dormiré! Aunque cuando te\l"
	.string "vayas, dormiré en tu cuarto…$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock: @ 81F7A46
	.string "Los Vigoroth hacen todo el trabajo\n"
	.string "con su increíble Fuerza.\p"
	.string "No es parte del servicio limpiar, pero\n"
	.string "no dejarán la casa hecha un desastre…\p"
	.string "{PLAYER}, ve al cuarto, que está arriba.\n"
	.string "¡Mira cada rincón!\p"
	.string "Papá te compró un Reloj de Pared\n"
	.string "cuando veníamos hacia aquí.\l"
	.string "¡Ponlo en hora! Sabré si no lo haces.$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom: @ 81F7B24
	.string "Mamá: ¿Y, {PLAYER}?\p"
	.string "¿Que tal está tu nuevo\n"
	.string "cuarto? ¿La cama es cómoda?$"

PlayersHouse_1F_Text_GoSetTheClock: @ 81F7B67
	.string "Mamá: {PLAYER}.\p"
	.string "No te vas a ir hasta preparar el reloj.$"

PlayersHouse_1F_Text_OhComeQuickly: @ 81F7B96
	.string "Mamá: ¡Oh! ¡{PLAYER}, {PLAYER}!\n"
	.string "¡Mira, mira!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn: @ 81F7BBC
	.string "Mamá: Es el GIMNASIO PETALBURG!\n"
	.string "¡Tu padre se ve hermoso en TV!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim: @ 81F7BF1
	.string "Mamá: Oh… Muy tarde.\p"
	.string "Te perdiste a tu papá muy nervioso\n"
	.string "como para hablar. Fue adorable, ¡ja ja!.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor: @ 81F7C35
	.string "¡Ah, sí!\n"
	.string "El amigo de la infancia de tu padre\p"
	.string "vive literalmente al lado de casa.\p"
	.string "El Profe seguro estará encantado\n"
	.string "de volver a verte.$"

PlayersHouse_1F_Text_SeeYouHoney: @ 81F7CC3
	.string "Mamá: ¡Hasta luego, hijito!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch: @ 81F7CD8
	.string "Mamá: ¿Ya saludaste al Profe BIRCH?$"

PlayersHouse_1F_Text_YouShouldRestABit: @ 81F7D08
	.string "Mamá: ¿Cómo vas, {PLAYER}?\n"
	.string "Te ves cansado…\p"
	.string "Dormir un poco te hará bien.$"

PlayersHouse_1F_Text_TakeCareHoney: @ 81F7D5C
	.string "Mamá: ¡Cuídate, cielo!\n"
	.string "¡Que no te lleve Drifloon!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom: @ 81F7D73
	.string "Mamá: ¿Oh? ¿Tu papá te dio esa Medalla?\p"
	.string "Debí haber estado ahí, seguro tu padre se\n"
	.string "veía hermoso al combatir… O tal vez no.\p"
	.string "¡Como sea, yo también te daré algo!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard: @ 81F7DBE
	.string "No te sobreexijas, hijito.\n"
	.string "Siempre puedes venir a descansar.\p"
	.string "¡Tú puedes, campeón!$"

PlayersHouse_1F_Text_IsThatAPokenav: @ 81F7E0E
	.string "Mamá: ¿Qué es esa cosa? ¿Un POKéNAV?\n"
	.string "Es sin dudas un invento de Devon, que mal\l"
	.string "diseño. El mío personalizado es mejor…\n"
	.string "¡Como sea, ten mi número!\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom: @ 81F7E89
	.string "Registrada Mamá.$"

PlayersHouse_1F_Text_Vigoroth1: @ 81F7EA8
	.string "¡Vigo!$"

PlayersHouse_1F_Text_Vigoroth2: @ 81F7EB3
	.string "Rot rot rot…\n"
	.string "Parece sobreexplotado…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym: @ 81F7EC6
	.string "ENTREVISTADOR: Señor Norman… ¿A\n"
	.string "dónde va?\p"
	.string "Creo haber visto que estaba sonrojado…\n"
	.string "Seguro se puso nervioso por la cámara…\l"
	.string "Como sea… Aquí termina el show.$"

PlayersHouse_1F_Text_TheresAMovieOnTV: @ 81F7F0F
	.string "Están dando un programa de Galar.\p"
	.string "Dos tipos con un sentido dudoso de\n"
	.string "la moda están combatiendo…\p"
	.string "¡Vamos, hombre de la campera rara!$"

PlayersHouse_1F_Text_RunningShoesManual: @ 81F7F66
	.string "Aquí dice ”Agua de dieta”…$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou: @ 81F800E
	.string "Ppaá: ¿Hm?\p"
	.string "¡Hey, es {PLAYER}!\p"
	.string "Seguro estás disfrutando ser campeón,\n"
	.string "deberíamos entrenar un día de estos.\p"
	.string "Ya das la talla para Líder de Gimnasio,\n"
	.string "incluso a tu corta edad. Justo como un\l"
	.string "presumido pelopincho, que es Líder\p"
	.string "de Ciudad Verde. Sin dudas, combina\n"
	.string "con su nombre. Escuché que a su novio\l"
	.string "no le hace gracia que se la pase\p"
	.string "en el Gimnasio siempre…\p"
	.string "¡Ja! Lo mismo que me dice tu madre.\p"
	.string "¡Ah, sí! Tengo algo que darte…\n"
	.string "Esto te lo entrega el Sr. BRINEY,\l"
	.string "antiguo mentor de Wallace.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove: @ 81F80FE
	.string "Papá: ¿Eh, un TICKET para el ferry?\p"
	.string "Si me acuerto bien, hay puertos en\n"
	.string "SLATEPORT y LILYCOVE.$"

PlayersHouse_1F_Text_BetterGetBackToGym: @ 81F815B
	.string "Debería volver al GIMNASIO PETALBURG…\p"
	.string "Un día de estos deberías ir y retarme,\n"
	.string "¡Aceptaré un reto siempre! Si me ganas,\l"
	.string "quizá te deje encargarte del Gimnasio\p"
	.string "mientras salgo a comer con tu madre,\n"
	.string "¿Te parece?\p"
	.string "Amor, gracias por cuidar la casa mientras\n"
	.string "no estoy.$"

PlayersHouse_1F_Text_DadShouldStayLonger: @ 81F81B9
	.string "Mamá: Ese padre tuyo…\p"
	.string "Viene por primera vez desde hace un año\n"
	.string "y sólo habla de POKéMON.\p"
	.string "Si no fuera por lo delicioso que cocina,\n"
	.string "porque me manda sus almuerzos desde el\l"
	.string "GIMNASIO y porque es así de hermoso,\p"
	.string "probablemente estaría por ahí buscándome\n"
	.string "un mejor marido… O quizá podría tener\l"
	.string "algunas amigas… Me han dicho que Lorelei,\p"
	.string "de la región Kanto y Candice, de Sinnoh son\n"
	.string "agradables…\p"
	.string "De todas formas, debería relajarse más tiempo…$"

PlayersHouse_1F_Text_IsThatABreakingStory: @ 81F824B
	.string "Mamá: ¿Es una noticia?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash: @ 81F826F
	.string "¡EMERGENCIA DE COLOR BZZZ!\n"
	.string "¡! ¡!\p"
	.string "¡Varios locales de Hoenn, han visto\n"
	.string "POKéMON de color BZZ en el cielo!\l"
	.string "…\p"
	.string "La identidad de los POKéMON aún se\n"
	.string "desconoce.\p"
	.string "Ahora, volvemos al doceavo combate\n"
	.string "de Red y Green por el título de campeón.$"

PlayersHouse_1F_Text_WhatColorDidTheySay: @ 81F8351
	.string "Mamá: {PLAYER}, ¿Lo entendiste?\p"
	.string "¿De qué color era el POKéMON\n"
	.string "que está aterrorizando Hoenn?$"

PlayersHouse_1F_Text_StillUnknownPokemon: @ 81F83A1
	.string "Mamá: ¡Bueno, algo es algo!\n"
	.string "Aún hay POKéMON que no se conocen…$"
