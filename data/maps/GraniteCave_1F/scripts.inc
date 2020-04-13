GraniteCave_1F_MapScripts:: @ 822DA5D
	.byte 0

GraniteCave_1F_EventScript_Hiker:: @ 822DA5E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM05, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_RARE_CANDY, 255
	setflag FLAG_RECEIVED_HM05
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash:: @ 822DA8A
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end
	
GraniteCave_AquaGruntM::
	lock
	msgbox ConversacionImportante, MSGBOX_DEFAULT
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	msgbox NoDeberias, MSGBOX_DEFAULT
	compare VAR_FACING, DIR_WEST
	goto_if_eq Atacar1
	compare VAR_FACING, DIR_EAST
	goto_if_eq SoloAtacar
	compare VAR_FACING, DIR_NORTH
	goto_if_eq SoloAtacar
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq SoloAtacar
Atacar1::
	applymovement 3, Mujer1Correr1
	applymovement 5, Mujer2Correr1
	waitmovement 0
	delay 16
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	trainerbattle_double TRAINER_AQUA_GRUNT_MF1, YaVerás, Perdimos, SinPokes, CombateDoble1
	end
CombateDoble1::
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerright 
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F2, Perdimos
	goto FinalCombate1
	end
Playerleft:
	face_left
	step_end
Playerright:
	face_right
	step_end
Playerup:
	face_up
	step_end
Playerdown:
	face_down
	step_end
FinalCombate1::
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 5
	removeobject 4
	removeobject 3
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end

SoloAtacar::
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	trainerbattle_double TRAINER_AQUA_GRUNT_MF1, YaVerás, Perdimos, SinPokes, CombateDoble15
	goto CombateDoble15
	end
CombateDoble15::
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerleft
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F2, Perdimos
	goto DespuesCombate10
	end
DespuesCombate10::
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 3
	removeobject 4
	removeobject 5
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end
SoloAtacarF1::
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerleft
	waitmovement 0
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	trainerbattle_double TRAINER_AQUA_GRUNT_F1F2, YaVerás, Perdimos, SinPokes, CombateDoble25
	goto CombateDoble25
	end
CombateDoble25::
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerdown
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_M, Perdimos
	goto DespuesCombate15
	end
DespuesCombate15::
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 3
	removeobject 4
	removeobject 5
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end
SoloAtacarF2::
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	trainerbattle_double TRAINER_AQUA_GRUNT_MF2, YaVerás, Perdimos, SinPokes, CombateDoble35
	goto CombateDoble35
	end
CombateDoble35::
	applymovement 4, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerup
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F1, Perdimos
	goto FinalCombate25
	end
FinalCombate25::
	applymovement 3, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 3
	removeobject 4
	removeobject 5
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end
PelearUnoPorUno::
	applymovement OBJ_EVENT_ID_PLAYER, Playerdown
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_M, Perdimos
	goto Sig1
	end
Sig1::
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerup
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F1, Perdimos
	goto Sig2
	end
Sig2::
	applymovement 3, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerright 
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F2, Perdimos
	goto Sig3
	end
Sig3::
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 5
	removeobject 4
	removeobject 3
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end
Warp_me::
	setobjectxyperm OBJ_EVENT_ID_PLAYER, 36, 19
	setobjectxyperm 3, 0, 0
	setobjectxyperm 4, 0, 0
	setobjectxyperm 5, 0, 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerdown
	waitmovement 0
	msgbox ESPEREN, MSGBOX_DEFAULT
	fadescreen 0
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, Playerup
	waitmovement 0
	msgbox QueHaran, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Playerright
	waitmovement 0
	msgbox Quehago, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Playerleft
	waitmovement 0
	msgbox Debodecirle, MSGBOX_DEFAULT
	release
	end
ESPEREN:
    .string "{PLAYER}: ¡ESPEREN!\n"
    .string "… … …\l"
    .string "¡AARGH! ¡Volví a dejarlos escapar!\p"
    .string "Piensa, {PLAYER}, piensa… ¿Qué\n"
    .string "harán con algo así?$"
QueHaran:
    .string "{PLAYER}: A ver, {PLAYER},\n"
    .string "repasa los hechos, ¿Qué sé de ellos?\l"
    .string "Sé que están locos, eso es algo…\p"
    .string "Pero… ¿Qué quieren…?\n"
    .string "… … …\p"
    .string "Mamá mencionó algo de unos locos\n"
    .string "peleando por agua y rocas…\l"
    .string "Agua… Rocas… Agua… Rocas… ¿Piedras?\p"
    .string "¡Piedra! Bien, bien… Espera…\n"
    .string "¿Qué clase de Piedra buscan?\l"
    .string "¡Ah! Quizá la pregunta no es qué\p"
    .string "harían con una simple Piedra… Si no\n"
    .string "¿Qué harían con Piedras en general?\l"
    .string "… Piedras… ¿Evolutivas…?$"
Quehago:
    .string "Bueno, pero ahora eso no importa…\n"
    .string "Lo que importa es… ¿Qué hago yo con\l"
    .string "esta información? Vencí a todos los\p"
    .string "reclutas con los que me topé, pero…\p"
    .string "Eso no significa que no hayan\n"
    .string "Reclutas más fuertes por ahí…\l"
    .string "¿Qué hago, le digo a la Policía?\p"
    .string "¿O a la Policía Internacional?\n"
    .string "No, eso es demasiado. Por ahora,\l"
    .string "son solo unos locos disfrazados.$"
Debodecirle:
    .string "{PLAYER}: Quizá… Deba hablar de\n"
    .string "todo esto con ÉL…\l"
    .string "Steven Stone… Tengo su carta y todo…\p"
    .string "Él es una autoridad y un hombre muy\n"
    .string "poderoso… Quizá también deba hablar\l"
    .string "con los Líderes más fuertes de Hoenn…$"

YaVerás:
    .string "RM1 RH: ¡Ya verás, te destrozaré!$"
Perdimos:
    .string "RM1: ¡Q-Q-QUÉ!\n"
    .string "RH: ¡ARGH! Ahora el Jefe nos\l"
    .string "rebajará aún más el sueldo…$"
SinPokes:
    .string "¡AL ATAQUE!$"
Mujer1Correr1:
	walk_right
	walk_down
	step_end
Mujer2Correr1:
	delay_16
	walk_right
	walk_up
	walk_right
	walk_right
	walk_down
	walk_down
	face_left
	step_end
GraniteCave_AquaGruntF1::
	lock
	msgbox ConversacionImportante, MSGBOX_DEFAULT
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	msgbox NoDeberias, MSGBOX_DEFAULT
	compare VAR_FACING, DIR_WEST
	goto_if_eq Atacar2
	compare VAR_FACING, DIR_EAST
	goto_if_eq SoloAtacarF1
	compare VAR_FACING, DIR_NORTH
	goto_if_eq SoloAtacarF1
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq SoloAtacarF1
Atacar2::
	applymovement 4, HombreCorrer1
	applymovement 5, Mujer2Correr2
	waitmovement 0
	delay 16
	msgbox SinPokes, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	trainerbattle_double TRAINER_AQUA_GRUNT_F1F2, YaVerás, Perdimos, SinPokes, CombateDoble20
	goto CombateDoble20
	end
CombateDoble20::
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Playerdown
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_M, Perdimos
	goto FinalCombate20
	end
FinalCombate20::
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 5
	removeobject 4
	removeobject 3
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Warp_me
	end
NoPuedeSer:
    .string "Todos: ¡NO PUEDE SER!\n"
    .string "… … … … … … … … … …\l"
    .string "… … … … … … … … … … … …\p"
    .string "RH: ¡Ah! ¡Lo recordé!\n"
    .string "Je je je… Ya tenemos la {COLOR LIGHT_BLUE}{SHADOW BLUE}Piedra{COLOR DARK_GREY}{COLOR LIGHT_GREY}…\l"
    .string "¡NO HAY OTRA RAZÓN PARA ESTAR AQUÍ!\p"
    .string "RM1: ¿Sólo era eso? Yo creo recordar\n"
    .string "que nos falta hacer algo…\p"
    .string "RM2: Nah, no creo… Pero aún así me\n"
    .string "pregunto… ¿Para qué quiere\l"
    .string "esa {COLOR LIGHT_BLUE}{SHADOW BLUE}extraña Piedra{COLOR DARK_GREY}{SHADOW LIGHT_GREY}…?\p"
    .string "RH: ¡¡¡SHHH!!! ¡ES ULTRA SECRETO,\n"
    .string "NI NOSOTROS LO SABEMOS!\l"
    .string "{PLAYER}: {COLOR BLUE}{SHADOW LIGHT_BLUE}(¿una Piedra…?)\p"
    .string "(¿pero qué tiene de especial una\n"
    .string "simple Piedra…?)$"


HombreCorrer1:
	walk_right
	walk_up
	step_end
Mujer2Correr2:
	delay_16
	walk_right
	walk_down
	walk_right
	walk_right
	walk_up
	walk_up
	face_left
	step_end
GraniteCave_AquaGruntF2::
	lock
	msgbox ConversacionImportante, MSGBOX_DEFAULT
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	msgbox NoDeberias, MSGBOX_DEFAULT
	goto SoloAtacarF2
ConversacionImportante:
    .string "Recluta Mujer 1: Y… ¿Qué es lo que\n"
    .string "quiere el Jefe después de todo?\p"
    .string "R.H: Pues… ¿Qué no era\n"
    .string "algo con el {COLOR LIGHT_BLUE}{SHADOW BLUE}agua y el mar{COLOR DARK_GREY}{SHADOW LIGHT_GREY}, que eran\l"
    .string "vitales? Algo así recuerdo…\p"
    .string "R.M. 2: Mhh… Yo creí que\n"
    .string "sólo hacía esto para arruinar los\l"
    .string "planes de su {COLOR LIGHT_RED}{SHADOW RED}rival{COLOR DARK_GREY}{SHADOW LIGHT_GREY}, ¿No es así?\p"
    .string "R.M. 1: Esa no fue mi pregunta, pero\n"
    .string "creo que deberíamos… Espera…\l"
    .string "Todos: ¿¡QUIÉN ES ESE!?$"
NoDeberias:
    .string "R.M 2: ¡Oye, tú! ¡No deberías haber\n"
    .string "escuchado lo que escuchaste!\p"
    .string "{PLAYER}: Lo único que escuché, fue\n"
    .string "a unos empleados tan estúpidos que\l"
    .string "no recuerdan lo que les dijo su Jefe…\p"
    .string "R.M 2: ¿Ah, sí? ¡Pues ya verás, hasta\n"
    .string "si no escuchaste nada!\l"
    .string "Todos: ¡ATAQUEN, {COLOR LIGHT_BLUE}{SHADOW BLUE}TEAM AQUA{COLOR DARK_GREY}{SHADOW LIGHT_GREY}!$"

GraniteCave_1F_Text_GetsDarkAheadHereYouGo: @ 822DA94
	.string "Hey, you.\n"
	.string "It gets awfully dark ahead.\l"
	.string "It'll be tough trying to explore.\p"
	.string "That guy who came by earlier…\n"
	.string "STEVEN, I think it was.\p"
	.string "He knew how to use FLASH, so he ought\n"
	.string "to be all right, but…\p"
	.string "Well, for us HIKERS, helping out those\n"
	.string "that we meet is our motto.\p"
	.string "Here you go, I'll pass this on to you.$"

GraniteCave_1F_Text_ExplainFlash: @ 822DBB7
	.string "Teach that hidden move FLASH to\n"
	.string "a POKéMON and use it.\p"
	.string "It lights up even the inky darkness\n"
	.string "of caves.\p"
	.string "But, to use it, you need the GYM BADGE\n"
	.string "from DEWFORD's POKéMON GYM.$"

