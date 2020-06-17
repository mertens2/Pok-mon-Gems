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
	goto Atacando
	end
Atacando::
	specialvar VAR_RESULT, CountPartyNonEggMons
	compare VAR_RESULT, 2
	goto_if_lt PelearUnoPorUno
	setvar VAR_0x8004, SPECIAL_BATTLE_DOUBLE_AQUA_1
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	applymovement 3, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox AyQueInutiles, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F2, IMPOSIBLEF1_Dewford
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 5
	removeobject 4
	removeobject 3
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Monologo_Dewford
	end
AquaMale_Dewford:: @ 8224157
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, TRAINER_AQUA_GRUNT_M, 0, AquaMale_Dewford_Perdi, AquaMale_Dewford_Perdi
	end
AquaFemale_Dewford:: @ 8224166
	trainerbattle TRAINER_BATTLE_SET_TRAINER_B, TRAINER_AQUA_GRUNT_F1, 0, AquaFemale_Dewford_Perdi, AquaFemale_Dewford_Perdi
	end
SoloAtacar::
	applymovement 3, Common_Movement_FacePlayer
	applymovement 4, Common_Movement_FacePlayer
	applymovement 5, Common_Movement_FacePlayer
	waitmovement 0
	goto Atacando
	end
PelearUnoPorUno::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_M, AquaMale_Dewford_Perdi
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F1, AquaFemale_Dewford_Perdi
	applymovement 3, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight 
	waitmovement 0
	trainerbattle_no_intro TRAINER_AQUA_GRUNT_F2, IMPOSIBLEF1_Dewford
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox NoPuedeSer, MSGBOX_DEFAULT
	closemessage
	fadescreen 1
	removeobject 5
	removeobject 4
	removeobject 3
	setflag FLAG_DEWFORDTEAMAQUADEFEATED
	goto Monologo_Dewford
	end
Monologo_Dewford::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox ESPEREN, MSGBOX_DEFAULT
	fadescreen 0
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox QueHaran, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox Quehago, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox Debodecirle, MSGBOX_DEFAULT
	release
	end
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
ConversacionImportante:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Supervisora {COLOR DARK_GREY}{SHADOW LIGHT_GREY}: Y… ¿Qué es lo que\n"
    .string "quiere el Jefe después de todo?\p"
    .string "{COLOR LIGHT_BLUE}{SHADOW BLUE}Recluta Hombre{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: Pues… ¿Qué no era\n"
    .string "algo con el {COLOR LIGHT_BLUE}{SHADOW BLUE}agua y el mar{COLOR DARK_GREY}{SHADOW LIGHT_GREY}, que eran\l"
    .string "vitales? Algo así recuerdo…\p"
    .string "{COLOR LIGHT_RED}{SHADOW RED}Recluta Mujer{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: Mhh… Yo creí que\n"
    .string "sólo hacía esto para arruinar los\l"
    .string "planes de su {COLOR LIGHT_RED}{SHADOW RED}rival{COLOR DARK_GREY}{SHADOW LIGHT_GREY}, ¿No es así?\p"
    .string "{COLOR LIGHT_RED}{SHADOW RED}Supervisora{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: Esa no fue mi pregunta, pero\n"
    .string "creo que deberíamos… Espera…\l"
    .string "Todos: ¿¡QUIÉN ES ESE!?$"
NoDeberias:
    .string "{COLOR LIGHT_RED}{SHADOW RED}SV{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¡Oye, tú! ¡No deberías haber\n"
    .string "escuchado lo que escuchaste!\p"
    .string "{PLAYER}: Lo único que escuché, fue\n"
    .string "a unos empleados tan estúpidos que\l"
    .string "no recuerdan lo que les dijo su Jefe…\p"
    .string "{COLOR LIGHT_RED}{SHADOW RED}R.M{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¿Ah, sí? ¡Pues ya verás, hasta\n"
    .string "si no escuchaste nada!\l"
    .string "Todos: ¡ATAQUEN, {COLOR LIGHT_BLUE}{SHADOW BLUE}TEAM AQUA{COLOR DARK_GREY}{SHADOW LIGHT_GREY}!$"
IMPOSIBLEF1_Dewford:
    .string "¡¿QUÉ?!\p"
    .string "¡PERO SI YO ERA LA SUPERVISORA!\l"
    .string "¡SE SUPONE QUE SOY LA\l"
    .string "MÁS FUERTE!$"

SinPokes:
    .string "¡AL ATAQUE!$"
AquaMale_Dewford_Perdi:
    .string "¡AAAARRGGH!\n"
    .string "¡Nos bajarán tanto el sueldo que\l"
    .string "terminaremos pagando para trabajar!$"
AquaFemale_Dewford_Perdi:
    .string "¡Maldita sea!\n"
    .string "¡No puedo creer que nos haya\l"
    .string "vencido un simple niño!$"
NoPuedeSer:
    .string "Todos: ¡NO PUEDE SER!\n"
    .string "… … … … … … … … … …\l"
    .string "… … … … … … … … … … … …\p"
    .string "{COLOR LIGHT_BLUE}{SHADOW BLUE}R.H{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¡Ah! ¡Lo recordé!\n"
    .string "Je je je… Ya tenemos la {COLOR LIGHT_BLUE}{SHADOW BLUE}Piedra{COLOR DARK_GREY}{SHADOW LIGHT_GREY}…\l"
    .string "¡NO HAY OTRA RAZÓN PARA ESTAR AQUÍ!\p"
    .string "{COLOR LIGHT_RED}{SHADOW RED}R.M{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¿Sólo era eso? Yo creo recordar\n"
    .string "que nos falta hacer algo…\p"
    .string "{COLOR LIGHT_RED}{SHADOW RED}SV{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: Nah, no creo… Pero aún así me\n"
    .string "pregunto… ¿Para qué quiere el Jefe\l"
    .string "esa {COLOR LIGHT_BLUE}{SHADOW BLUE}extraña Piedra{COLOR DARK_GREY}{SHADOW LIGHT_GREY}…?\p"
    .string "{COLOR LIGHT_BLUE}{SHADOW BLUE}R.H{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¡¡¡SHHH!!! ¡ES ULTRA SECRETO,\n"
    .string "NI NOSOTROS LO SABEMOS!\l"
    .string "{PLAYER}: {COLOR BLUE}{SHADOW LIGHT_BLUE}(¿una Piedra…?)\p"
    .string "(¿pero qué tiene de especial una\n"
    .string "simple Piedra…?)$"
AyQueInutiles:
    .string "{COLOR LIGHT_RED}{SHADOW RED}Supervisora{COLOR DARK_GREY}{SHADOW LIGHT_GREY}: ¡Qué inútiles!\n"
    .string "¡Yo me encargo ahora!$"
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
    .string "harían con una simple Piedra… Si no,\n"
    .string "¿Qué harían con Piedras en general?\l"
    .string "… Piedras… ¿Evolutivas…?$"
Quehago:
    .string "Bueno, pero ahora eso no importa…\n"
    .string "Lo que importa es… ¿Qué hago yo con\l"
    .string "esta información? Vencí a todos los\p"
    .string "Reclutas con los que me topé, pero…\p"
    .string "Eso no significa que no hayan\n"
    .string "Reclutas más fuertes por ahí…\l"
    .string "¿Qué hago, le digo a la Policía?\p"
    .string "¿O a la Policía Internacional?\n"
    .string "No, eso es demasiado. Por ahora,\l"
    .string "son solo unos locos disfrazados.$"
Debodecirle:
    .string "{PLAYER}: Quizá… Deba hablar de\n"
    .string "todo esto con ÉL…\p"
	.string "…\p"
    .string "Steven Stone… Tengo su carta y todo…\p"
    .string "Él es una autoridad y un hombre muy\n"
    .string "poderoso… Quizá también deba hablar\l"
    .string "con los Líderes más fuertes de Hoenn…$"
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
	goto_if_eq SoloAtacar
	compare VAR_FACING, DIR_NORTH
	goto_if_eq SoloAtacar
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq SoloAtacar
Atacar2::
	applymovement 4, HombreCorrer1
	applymovement 5, Mujer2Correr2
	waitmovement 0
	delay 16
	goto Atacando
	end
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
	goto SoloAtacar

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

