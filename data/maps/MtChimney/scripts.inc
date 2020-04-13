MtChimney_MapScripts:: @ 822EDC1
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition: @ 822EDCC
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume: @ 822EDD2
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie:: @ 822EDD5
	lock
	applymovement 2, Maxie_moves
	waitmovement 0
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	faceplayer
	msgbox MtChimney_EventScript_ArchieTxt, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Player_moves
	waitmovement 0
	applymovement 2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement 1, Archie_moves
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end
Maxie_moves:
	face_left
	step_end
Player_moves:
	walk_down
	walk_left
	face_right
	step_end
Archie_moves:
	walk_left
	walk_down
	walk_down
	walk_down
	face_up
	step_end
MtChimney_EventScript_ArchieTxt:
	.string "Archie: ¡Maxie no escuchará razones!\p"
	.string "¡Ya lo he vencido en una batalla,\n"
	.string "y ha curado a su equipo! Parece que\l"
	.string "no me escuchará. Deberás vencerlo tú.$"
MtChimney_EventScript_ArchieGoStopTeamMagma:: @ 822EDF9
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting:: @ 822EE02
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie:: @ 822EE0B
	lockall
	playbgm MUS_MGM0, 0
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement 2, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 2, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject 2
	removeobject 29
	removeobject 3
	removeobject 22
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm 1, 10, 12
	addobject 1
	compare VAR_FACING, DIR_EAST
	call_if_eq MtChimney_EventScript_ArchieApproachPlayerEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_EAST
	call_if_eq MtChimney_EventScript_ArchieExitEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq MtChimney_EventScript_ArchieExitNorth
	removeobject 1
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast:: @ 822EEC7
	applymovement 1, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth:: @ 822EED2
	applymovement 1, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast:: @ 822EEDD
	applymovement 1, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth:: @ 822EEE8
	applymovement 1, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady:: @ 822EEF3
	lock
	faceplayer
	showmoneybox 0, 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200, 0
	compare VAR_RESULT, FALSE
	goto_if_eq MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE, 1
	compare VAR_RESULT, TRUE
	call_if_eq MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	compare VAR_RESULT, FALSE
	goto_if_eq MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull:: @ 822EF51
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney:: @ 822EF5E
	removemoney 200, 0
	updatemoneybox 0, 0
	return

MtChimney_EventScript_DeclineLavaCookie:: @ 822EF69
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney:: @ 822EF76
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast: @ 822EF83
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast: @ 822EF8B
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth: @ 822EF94
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth: @ 822EF9C
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1: @ 822EFA6
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2: @ 822EFB8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3: @ 822EFC1
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4: @ 822EFD0
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5: @ 822EFE9
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6: @ 822EFF4
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7: @ 822F004
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8: @ 822F015
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

MtChimney_Movement_Unused9: @ 822F01D
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10: @ 822F02B
	walk_down
	step_end

MtChimney_Movement_Unused11: @ 822F02D
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12: @ 822F035
	delay_16
	delay_16
	walk_in_place_fastest_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13: @ 822F03F
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14: @ 822F04A
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15: @ 822F04F
	walk_left
	walk_in_place_fastest_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1:: @ 822F053
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2:: @ 822F05C
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3:: @ 822F065
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha:: @ 822F06E
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2:: @ 822F085
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1:: @ 822F09C
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2:: @ 822F0A5
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3:: @ 822F0AE
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4:: @ 822F0B7
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5:: @ 822F0C0
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6:: @ 822F0C9
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena:: @ 822F0D2
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena:: @ 822F0DB
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine:: @ 822F0E4
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone:: @ 822F123
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff:: @ 822F12D
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn:: @ 822F137
	special HealPlayerParty
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign:: @ 822F141
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby:: @ 822F14A
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby:: @ 822F176
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby:: @ 822F195
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa:: @ 822F1AC
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila:: @ 822F1C3
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley:: @ 822F1DA
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1:: @ 822F1F1
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer:: @ 822F208
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated:: @ 822F234
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch:: @ 822F253
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano: @ 822F26A
	.string "Maxie: El poder del Meteorito…\p"
	.string "Que se amplifica con esta máquina,\n"
	.string "tiene la capacidad de revivir este\l"
	.string "volcán inactivo…\p"
	.string "¡Incluso tiene el poder de curar a\n"
	.string "los Pokémon que estén cerca de ella…!\l"
	.string "Ese Archie cree que podrá pararme…$"

MtChimney_Text_MaxieIntro: @ 822F32E
	.string "MAXIE: ¿Hm?\n"
	.string "¿Quién eres tú?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Escuché a Archie hablar sobre un\n"
	.string "niño que se ha estado entrometiendo\l"
	.string "con sus planes.\p"
	.string "Seguro se refería a ti…\p"
	.string "¡ARGH! ¡¿PRIMERO UN VULPIX ALOLA\n"
	.string "Y AHORA UN NIÑO!? ¿¡QUÉ FALTA!?\p"
	.string "¿¡QUE ME HAGA FIRMAR LA ADOPCIÓN POR ÉL!?.\n"
	.string "{PLAYER}: ¡¿Q-qué?! ¡Yo vengo a detener\l"
	.string "tus tontos planer!\p"
	.string "Maxie: ¡MPH! Como sea… Hace mucho, la\n"
	.string "vida solía aflorecer en la tierra,\l"
	.string "salvaje. ¡Pero el humano tomó ese derecho!\n"
	.string "¡Por eso debo expandir la tierra!\p"
	.string "¡Sólo un tercio del mundo no basta!\n"
	.string "Necesitamos más espacio de cultivo,\l"
	.string "ganadería, etc. Y los Pokémon necesitan\p"
	.string "más espacio para vivir en paz…\p"
	.string "Y para lograr ese objetivo, usaré\n"
	.string "el poder de estre volcán dormido…\p"
	.string "¡! Pues, no era necesario que lo sepas,\n"
	.string "pero el conocimiento debe ser compartido.\p"
	.string "¡De todas formas!\n"
	.string "¡Te daré el conocimiento de lo que\l"
	.string "pasa cuando te metes con Maxie!$"

MtChimney_Text_MaxieDefeat: @ 822F5CF
	.string "Maxie: ¡¿QUÉ?!\p"
	.string "¡¿YO, EL PODEROSO MAXIE, DERROTADO?!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma: @ 822F5F7
	.string "Maxie: Suficiente… Si curo una\n"
	.string "vez más, el poder no bastará…\p"
	.string "Pero no te creas que esta es la última\n"
	.string "you've seen of TEAM MAGMA.\p"
	.string "¡! Ja ja ja…\p"
	.string "Hasta sin ese Meteorito…\n"
	.string "Lograré mi objetivo…\l"
	.string "¡Llendo a la fuente, el ORBE!$"

MtChimney_Text_TabithaIntro: @ 822F6AA
	.string "Hehehe!\p"
	.string "So you've come all the way here!\p"
	.string "But you're too late!\n"
	.string "I've already delivered the METEORITE\l"
	.string "from METEOR FALLS to the BOSS!$"

MtChimney_Text_TabithaDefeat: @ 822F72C
	.string "Hehehe…\p"
	.string "Even though I've lost, if our leader\n"
	.string "awakens that thing…$"

MtChimney_Text_TabithaPostBattle: @ 822F76D
	.string "BOSS, hurry!\n"
	.string "Give it the METEORITE's energy!\p"
	.string "Hehehe…$"

MtChimney_Text_Grunt2Intro: @ 822F7A2
	.string "We of TEAM MAGMA are working hard for\n"
	.string "everyone's sake.\p"
	.string "Like, if that thing's power made more\n"
	.string "land, there'd be more places to live.\p"
	.string "Everyone'd be happy!$"

MtChimney_Text_Grunt2Defeat: @ 822F83A
	.string "Hunh?\n"
	.string "What do you mean I lost?$"

MtChimney_Text_Grunt2PostBattle: @ 822F859
	.string "Our BOSS says, “It will make everyone\n"
	.string "happy.”\p"
	.string "But why does everyone keep getting\n"
	.string "in our way?$"

MtChimney_Text_Grunt1Intro: @ 822F8B6
	.string "If there were more land, I'd be able\n"
	.string "to get a big house of my own!\p"
	.string "I'm going to build it on hardened lava!$"

MtChimney_Text_Grunt1Defeat: @ 822F921
	.string "My dream of a big house…$"

MtChimney_Text_Grunt1PostBattle: @ 822F93A
	.string "A kid like you, you ought to be\n"
	.string "splashing about in the waves!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans: @ 822F978
	.string "That annoying TEAM AQUA…\n"
	.string "They always mess with our plans!$"

MtChimney_Text_MeteoritesPackAmazingPower: @ 822F9B2
	.string "METEORITES pack amazing power!$"

MtChimney_Text_YouBetterNotMessWithUs: @ 822F9D1
	.string "You'd better not mess with us!\p"
	.string "We're trying to awaken that thing\n"
	.string "for the benefit of everyone!$"

MtChimney_Text_AquasNameSimilar: @ 822FA2F
	.string "We're TEAM MAGMA!\p"
	.string "They're TEAM AQUA!\p"
	.string "It totally annoys me that they'd\n"
	.string "use a name like ours!$"

MtChimney_Text_DouseThemInFire: @ 822FA8B
	.string "Yeah!\n"
	.string "Douse them in fire!$"

MtChimney_Text_KeepMakingMoreLand: @ 822FAA5
	.string "We're going to keep making more land!$"

MtChimney_Text_Bufoh: @ 822FACB
	.string "Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma: @ 822FAD2
	.string "Archie: ¿¡PERO QUÉ HACES!?\n"
	.string "¡REACCIONA! ¡ACTIVAR EL VOLCÁN\l"
	.string "PROVOCARÁ UNA MASIVA DESTRUCCIÓN!\p"
	.string "Maxie: Claro, Archie, destrucción.\p"
	.string "Tenemos todo controlado, reactivar\n"
	.string "el Volcán sólo subirá la temperatura\l"
	.string "del área circundante, evaporando toda\p"
	.string "el agua del lugar.\p"
	.string "Archie: ¡¿Q-QUÉ?! ¿ESTO ES POR\n"
	.string "EL VULPIX DE ALOLA?\l"
	.string "¡DEJA LAS TONTERÍAS, ESTO\n"
	.string "DESTRUIRÁ EL EQUILIBRIO NATURAL!\p"
	.string "Maxie: Pfff… Eso harán TUS planes…\n"
	.string "¿Inundar el mundo, eso te parece mejor?\p"
	.string "Archie: ¡PUES AL MENOS ESO SALVARÍA\n"
	.string "LA VIDA DE LOS POKÉMON DE AGUA!\p"
	.string "Maxie: No, eso no pasará.\p"
	.string "Se mezclarían las aguas salada\n"
	.string "y dulce, causando la muerte del\l"
	.string "noventa por ciento de la vida\p"
	.string "marina y… ¿?\p"
	.string "{PLAYER}: Umh… Esto es incómodo…p"
	.string "Archie: ¡YA, NO ME IMPORTA!$"

MtChimney_Text_ArchieIHaveMyHandsFull: @ 822FBC7
	.string "ARCHIE: Grrr…\p"
	.string "¡Tienes que derrotar a Maxie!\n"
	.string "¡No me escuchará, aunque lo derrote!\p"
	.string "¡Seguro si lo haces tú, podrás detenerlo!\n"
	.string "¡Ataca con todo tu poder!$"

MtChimney_Text_ArchieThankYou: @ 822FC3D
	.string "ARCHIE: ¡{PLAYER}!\n"
	.string "¡Gracias!\p"
	.string "¡Con tu ayuda, hemos podido parar\n"
	.string "los planes del TEAM MAGAMA!\p"
	.string "Pero, aún así…\n"
	.string "¿De qué lado estás? ¿Estás conmigo\l"
	.string "o con Maxie?\p"
	.string "{PLAYER}: Umh… Yo creo que ambos\n"
	.string "están locos…\p"
	.string "Archie: Bah, eso no importa ahora.\p"
	.string "Seguiré a Maxie, junto con su equipo\n"
	.string "para evitar una próxima catástrofe…\p"
	.string "¡{PLAYER}, espero volverte a ver!$"

MtChimney_Text_MagmaOutnumbersUs: @ 822FD1F
	.string "Demonios… ¡TEAM MAGMA nos supera!\n"
	.string "¡No podemos con ellos!$"

MtChimney_Text_LessHabitatForWaterPokemon: @ 822FD5B
	.string "¡Si expanden la tierra, habrá menos\n"
	.string "hábitat para los Pokémon Marinos!$"

MtChimney_Text_MagmasNameSimilar: @ 822FDA1
	.string "¡Somos TEAM AQUA!\p"
	.string "¡Y ellos TEAM MAGMA!\p"
	.string "¡Me molesta que hayan usado casi\n"
	.string "nuestro mismo nombre!$"

MtChimney_Text_Bushaa: @ 822FDFC
	.string "¡Bushaaaa!$"

MtChimney_Text_LavaCookiesJust200: @ 822FE04
	.string "Las Galleta Lava son la\n"
	.string "especialidad del MT. CHIMENEA.\p"
	.string "Cada una vale ¥200, ¡Una ganga!.$"

MtChimney_Text_ThankYouDear: @ 822FE4D
	.string "¡Gracias, querido!$"

MtChimney_Text_YouveNotGotTheMoney: @ 822FE5E
	.string "Ay, cielito. Lamento decirte que\n"
	.string "la vida no es gratis, y mucho menos\l"
	.string "lo son mis Galletas Lava…$"

MtChimney_Text_OhFineThen: @ 822FE9B
	.string "Ah, bueno…$"

MtChimney_Text_MetoriteFittedOnMachine: @ 822FEAA
	.string "El Meteorito está en una máquina\n"
	.string "poderosa…\p"
	.string "La máquina parece haber sanado a tu Equipo,\n"
	.string "y estar drenando el poder del Meteorito.$"

MtChimney_Text_RemoveTheMeteorite: @ 822FF12
	.string "Un Meteorito en una misteriosa\n"
	.string "máquina…\p"
	.string "¿Lo saco?$"

MtChimney_Text_PlayerRemovedMeteorite: @ 822FF66
	.string "{PLAYER} quitó el Meteorito\n"
	.string "de la máquina rara.$"

MtChimney_Text_PlayerLeftMeteorite: @ 822FF9C
	.string "{PLAYER} dejó el Meteorito en\n"
	.string "su lugar.$"

MtChimney_Text_MachineMakesNoResponse: @ 822FFC0
	.string "Esta máquina…\n"
	.string "Y pensar que pudo haber destruido\n"
	.string "el mundo entero…$"

MtChimney_Text_RouteSign: @ 822FFFA
	.string "{DOWN_ARROW} JAGGED PATH\n"
	.string "LAVARIDGE TOWN AHEAD$"

MtChimney_Text_ShelbyIntro: @ 823001D
	.string "Me bañé en aguas termales y\n"
	.string "se me relajaron hasta los huesos.\l"
	.string "¡Ahora estoy preparada!$"

MtChimney_Text_ShelbyDefeat: @ 8230076
	.string "Ah, ¿porqué?\n"
	.string "¡Eres fuerte!$"

MtChimney_Text_ShelbyPostBattle: @ 82300A2
	.string "Bueno, al parecer ya perdí.\n"
	.string "Ya no puedo ser llamada Experta…$"

MtChimney_Text_ShelbyRegister: @ 82300E3
	.string "Thank you, child. It was fun, as if\n"
	.string "I were battling my own grandchild.\p"
	.string "Please, come see me again for\n"
	.string "a rematch.$"

MtChimney_Text_ShelbyRematchIntro: @ 8230153
	.string "If you can mesh your heart with those\n"
	.string "of your POKéMON, why, you should be\l"
	.string "able to achieve great things.$"

MtChimney_Text_ShelbyRematchDefeat: @ 82301BB
	.string "Oh, my goodness.\n"
	.string "Now, aren't you something!$"

MtChimney_Text_ShelbyPostRematch: @ 82301E7
	.string "Perhaps your heart has become one\n"
	.string "with the hearts of your POKéMON.$"

MtChimney_Text_MelissaIntro: @ 823022A
	.string "I've got the fire in me, baby.\n"
	.string "I can't stand it! I have to battle!$"

MtChimney_Text_MelissaDefeat: @ 823026D
	.string "Ooh, that was a scorching-hot match!$"

MtChimney_Text_MelissaPostBattle: @ 8230292
	.string "The heat of MT. CHIMNEY warms\n"
	.string "me up, baby!$"

MtChimney_Text_SheilaIntro: @ 82302BD
	.string "I've finally made it to MT. CHIMNEY.\n"
	.string "I want to make my POKéMON battle!$"

MtChimney_Text_SheilaDefeat: @ 8230304
	.string "The way you battle…\n"
	.string "It's like a MT. CHIMNEY eruption!$"

MtChimney_Text_SheilaPostBattle: @ 823033A
	.string "Like I said, I've finally made it to\n"
	.string "MT. CHIMNEY. It would be a shame if\l"
	.string "I only do a little sightseeing…\p"
	.string "I want to get in some battles and buy\n"
	.string "COOKIES as souvenirs.$"

MtChimney_Text_ShirleyIntro: @ 82303DF
	.string "Since I bathed in the hot springs,\n"
	.string "I've been feeling great!\l"
	.string "I'm sure I'm going to win!$"

MtChimney_Text_ShirleyDefeat: @ 8230436
	.string "Yowch!\n"
	.string "I'm getting a chill out of the water.$"

MtChimney_Text_ShirleyPostBattle: @ 8230463
	.string "I'll have to take another dip in the\n"
	.string "hot springs. Want to join me?\p"
	.string "Just joking!$"

MtChimney_Text_SawyerIntro: @ 82304B3
	.string "This is one fine mountain! Plenty of\n"
	.string "hot people around for company!$"

MtChimney_Text_SawyerDefeat: @ 82304F7
	.string "Oh, you're a real firebrand, too!$"

MtChimney_Text_SawyerPostBattle: @ 8230519
	.string "I think I need a dip in LAVARIDGE\n"
	.string "HOT SPRING with the locals!$"

MtChimney_Text_SawyerRegister: @ 8230557
	.string "I like little fireballs like you.\n"
	.string "Let me register you in my POKéNAV.$"

MtChimney_Text_SawyerRematchIntro: @ 823059C
	.string "I'm happily surrounded by hot people\n"
	.string "around these parts. I won't lose!$"

MtChimney_Text_SawyerRematchDefeat: @ 82305E3
	.string "Gosh, you're still the same\n"
	.string "firebrand as before!$"

MtChimney_Text_SawyerPostRematch: @ 8230614
	.string "Actually, it really is hot here.$"
