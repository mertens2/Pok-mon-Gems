RustboroCity_Gym_MapScripts:: @ 8212F30
	.byte 0

RustboroCity_Gym_EventScript_Roxanne:: @ 8212F31
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM39, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated:: @ 8212F66
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb:: @ 8212FA4
	giveitem ITEM_TM39
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM39
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch:: @ 8212FC8
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh:: @ 8212FE3
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy:: @ 8212FFA
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc:: @ 8213011
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Trigger0::
	lock
	applymovement 4, Trigger0
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Player_face
	waitmovement 0
	setvar VAR_GYMSTUFF, 1
	goto RustboroCity_Gym_EventScript_GymGuide
	end
Trigger0:
	walk_left
	face_down
	step_end
Player_face:
	face_up
	step_end
RustboroCity_Gym_EventScript_Trigger1::
	lock
	applymovement 4, Trigger1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Player_face
	waitmovement 0
	setvar VAR_GYMSTUFF, 2
	goto RustboroCity_Gym_EventScript_GymGuide
	end
Trigger1:
	walk_right
	walk_right
	face_down
	step_end
RustboroCity_Gym_EventScript_Trigger2::
	lock
	applymovement 4, Trigger2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Player_face_left
	waitmovement 0
	setvar VAR_GYMSTUFF, 3
	goto RustboroCity_Gym_EventScript_GymGuide
	end
Trigger2:
	face_right
	step_end
Player_face_left:
	face_left
	step_end
RustboroCity_Gym_EventScript_GymGuide:: @ 8213028
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_gt RustboroCity_Gym_EventScript_GymGuideMoreThan2
	goto_if_lt RustboroCity_Gym_EventScript_GymGuideLessThan2
	release
	end
RustboroCity_Gym_EventScript_GymGuideMoreThan2::
	lock
	faceplayer
	msgbox RustboroCity_Gym_Text_YouHaveMore, MSGBOX_DEFAULT
	compare VAR_GYMSTUFF, 1
	goto_if_eq RustboroCity_Gym_EventScript_move1
	compare VAR_GYMSTUFF, 2
	goto_if_eq RustboroCity_Gym_EventScript_move2
	compare VAR_GYMSTUFF, 3
	goto_if_eq RustboroCity_Gym_EventScript_move3
	release
	end
RustboroCity_Gym_EventScript_move1::
	applymovement 4, empujar1
	applymovement OBJ_EVENT_ID_PLAYER, empujado1
	waitmovement 0
	setvar VAR_GYMSTUFF, 0
	release
	end
	
empujar1:
	walk_down
	delay_8
	face_right
	delay_8
	walk_up
	walk_right
	step_end
	
empujado1:
	walk_right
	delay_8
	face_left
	delay_8
	face_up
	step_end
	
RustboroCity_Gym_EventScript_move2::
	applymovement 4, empujar2
	applymovement OBJ_EVENT_ID_PLAYER, empujado2
	waitmovement 0
	setvar VAR_GYMSTUFF, 0
	release
	end
	
empujar2:
	walk_down
	delay_8
	face_left
	delay_8
	walk_up
	walk_left
	walk_left
	face_down
	step_end
	
empujado2:
	walk_left
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	step_end
	
RustboroCity_Gym_EventScript_move3::
	applymovement 4, empujar3
	applymovement OBJ_EVENT_ID_PLAYER, empujado3
	waitmovement 0
	setvar VAR_GYMSTUFF, 0
	release
	end
	
empujar3:
	walk_right
	delay_8
	face_down
	delay_8
	walk_left
	face_down
	step_end
	
empujado3:
	walk_down
	delay_8
	face_up
	delay_8
	face_left
	step_end
	
RustboroCity_Gym_Text_YouHaveMore:
    .string "¡ESPERA! ¡TÚ TIENES MÁS DE DOS!\p"
    .string "Lo lamento, pero reglas son reglas.\n"
    .string "No puedes participar en el Gimnasio\l"
    .string "si tienes más de dos Pokémon...\p"
    .string "Así lo ha querido nuestra querida\n"
    .string "Roxxane, y así se quedará. Ve a\l"
    .string "dejar algunos Pokémon en el PC,\p"
    .string "piensa bien tu equipo, y vuelve\n"
    .string "cuando tengas dos Pokémon o menos.\p"
    .string "¿Entendido?$"


RustboroCity_Gym_EventScript_GymGuideLessThan2::
	lock
	faceplayer
	compare VAR_GYMSTUFF, 0
	goto_if_gt RustboroCity_Gym_EventScript_GymGuideLessThan2NoItem
	msgbox RustboroCity_Gym_Text_YouAreJustFineWater, MSGBOX_DEFAULT
	giveitem ITEM_FRESH_WATER, 1
	applymovement 4, MovementUp
	waitmovement 0
	setvar VAR_TRIGGER_GYMS, 1
	release
	end
	
RustboroCity_Gym_Text_YouAreJustFineWater:
    .string "¡OH! Veo que ya tienes sólo dos\n"
    .string "Pokémon. ¡Eso es fantástico!\p"
    .string "Ahora te dejaré que vayas con la\n"
    .string "Líder. Pero no sin antes decirte que\l"
    .string "necesitarás esto.\p"
    .string "Es un Agua Fresca. Recupera más PS\n"
    .string "que una Poción y las Bayas\l"
    .string "Aranja juntas. Espero te sirva.\p"
    .string "¡Adelante, Joven Promesa!$"

RustboroCity_Gym_EventScript_GymGuideLessThan2NoItem::
	lock
	faceplayer
	msgbox RustboroCity_Gym_Text_YouAreJustFine, MSGBOX_DEFAULT
	applymovement 4, MovementUp
	waitmovement 0
	release
	end
MovementUp:
	walk_up
	face_down
	step_end
RustboroCity_Gym_Text_YouAreJustFine:
    .string "¡OH! Veo que ya tienes sólo dos\n"
    .string "Pokémon. ¡Eso es fantástico!\p"
    .string "Ahora te dejaré que vayas con la\n"
    .string "Líder.\l"
    .string "¡Adelante, Joven Promesa!$"
RustboroCity_Gym_EventScript_GymGuidePostVictory:: @ 821303D
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue:: @ 8213047
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue:: @ 8213057
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified:: @ 8213067
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue:: @ 8213071
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne:: @ 821307B
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice: @ 821309D
    .string "¡Hola! ¿Cómo va todo?\p"
    .string "¡Escúchame, amigo mío! ¡Esto es un\n"
    .string "Gimnasio Pokémon. Aquí, los\l"
    .string "Entrenadores se ponen a prueba.\p"
    .string "Cada Gimnasio tiene un Puzzle o un\n"
    .string "requisito para entrar. Este Gimnasio\l"
    .string "requiere que uses sólo dos Pokémon.$"


RustboroCity_Gym_Text_GymGuidePostVictory: @ 82132E2
    .string "¡Wow! ¡Esa fue una victoria que quita\n"
    .string "el aliento! ¡Sin dudas te mereces\l"
    .string "portar esa Medalla de Gimnasio!\p"
    .string "Creo que serás capaz de vencer\n"
    .string "a cualquier rival que se te presente.\p"
    .string "¿No crees?$"


RustboroCity_Gym_Text_JoshIntro: @ 82133E9
    .string "¡No nos tomes a la ligera, nosotros,\n"
    .string "los Entrenadores del Gimnasio,\l"
    .string "hemos entrenado hasta el cansancio!$"

RustboroCity_Gym_Text_JoshDefeat: @ 821342D
    .string "Fuiste demasiado para mí…$"


RustboroCity_Gym_Text_JoshPostBattle: @ 8213447
    .string "¡Aún no conoces el poder de los\n"
    .string "Pokémon del Tipo Roca!$"


RustboroCity_Gym_Text_TommyIntro: @ 8213486
    .string "Si no me vences, no durarás nada\n"
    .string "luchando contra la magnífica Roxxane.$"


RustboroCity_Gym_Text_TommyDefeat: @ 82134C6
    .string "¡Wow! ¡Tu potencial es magnífico!\n"
    .string "¡Casi tanto como Roxxane!$"


RustboroCity_Gym_Text_TommyPostBattle: @ 82134E6
    .string "Roxxane es sin lugar a dudas, la\n"
    .string "estudiante de la Escuela más fuerte.\p"
    .string "A su corta edad, ya es Líder de\n"
    .string "un Gimnasio oficial…$"

RustboroCity_Gym_Text_MarcIntro: @ 8213533
    .string "Vivo en un apartamento\n"
    .string "¿¡PERO ESO QUÉ!? ¡Son felices!$"


RustboroCity_Gym_Text_MarcDefeat: @ 8213589
    .string "¡Ay, hombre!\n"
    .string "¡Un estúpido me venció!$"

RustboroCity_Gym_Text_MarcPostBattle: @ 82135C0
    .string "Se lo dejaré a la Líder. Ella te\n"
    .string "aplastará.$"

RustboroCity_Gym_Text_RoxanneIntro: @ 821362A
    .string "¡Hola, Joven Promesa!\n"
    .string "Soy Roxanne, la Líder del Gimnasio.\p"
    .string "Me convertí en Líder para incentivar\n"
    .string "a los Entrenadores a unirse\l"
    .string "a la Escuela Rustboro.\p"
    .string "¡Demuéstrame el poder\n"
    .string "que portan tus Pokémon!$"


RustboroCity_Gym_Text_RoxanneDefeat: @ 821370B
    .string "Y…\n"
    .string "Parece que…\l"
    .string "He perdido…\p"
    .string "Ya comprendo…\n"
    .string "Tengo mucho que aprender aún.\p"
    .string "Pues, acepta esta Medalla del\n"
    .string "Gimnasio, es la prueba que demuestra\l"
    .string "que me venciste.$"


RustboroCity_Gym_Text_ReceivedStoneBadge: @ 82137EC
    .string "{PLAYER} recibió la Medalla Roca\n"
    .string "de las manos de Roxanne.$"


RustboroCity_Gym_Text_StoneBadgeInfoTakeThis: @ 8213816
    .string "La Medalla Roca te permitirá usar\n"
    .string "Corte fuera de combate. Quizá\l"
    .string "quieras esto, también.$"


RustboroCity_Gym_Text_ExplainRockTomb: @ 82138B1
    .string "Es la MT Tumba Rocas. Tumba Rocas\n"
    .string "es un Movimiento que no sólo causa\l"
    .string "daño, si no que baja la velocidad.\p"
	.string "Las MT tienen usos infinitos.$"


RustboroCity_Gym_Text_RoxannePostBattle: @ 82139A7
    .string "Ya que eres tan fuerte, deberías\n"
    .string "visitar y vencer todos los Gimnasios.$"


RustboroCity_Gym_Text_GymStatue: @ 8213A21
	.string "RUSTBORO CITY POKéMON GYM$"

RustboroCity_Gym_Text_GymStatueCertified: @ 8213A3B
	.string "RUSTBORO CITY POKéMON GYM\p"
	.string "ROXANNE'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall: @ 8213A76
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "ROXANNE: Oh, hello, {PLAYER}?\n"
	.string "This is ROXANNE of RUSTBORO CITY.\p"
	.string "I heard from BRAWLY that you're\n"
	.string "moving up through the ranks of\l"
	.string "TRAINERS at an incredible clip.\p"
	.string "Well, I'd rather not think that\n"
	.string "I can't beat you.\p"
	.string "I promise, I will shape up my GYM\n"
	.string "so that you may challenge us again.\p"
	.string "I hope you'll be looking forward to\n"
	.string "that occasion as much as me!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

RustboroCity_Gym_Text_RegisteredRoxanne: @ 8213C01
	.string "Registered GYM LEADER ROXANNE\n"
	.string "in the POKéNAV.$"

RustboroCity_Gym_Text_RoxannePreRematch: @ 8213C2F
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become. Let us battle!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat: @ 8213CF9
	.string "Grr…\n"
	.string "Again, I have lost…$"

RustboroCity_Gym_Text_RoxannePostRematch: @ 8213D12
	.string "ROXANNE: I still have much to learn\n"
	.string "when it comes to battling POKéMON.\p"
	.string "That awareness makes me love battling\n"
	.string "all that much more!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons: @ 8213D93
	.string "ROXANNE: I'm so glad to see you again.\n"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
	.string "I'm sure we've both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we've become…\p"
	.string "Oh, no…\n"
	.string "You only have one POKéMON with you?\p"
	.string "Please return with at least one more\n"
	.string "POKéMON.$"
