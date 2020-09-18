GraniteCave_StevensRoom_MapScripts:: @ 822DC7A
	.byte 0

GraniteCave_StevensRoom_EventScript_Steven:: @ 822DC7B
	lock
	faceplayer
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	msgbox GraniteCave_StevensRoom_Text_ThankYouTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM47
	compare VAR_RESULT, FALSE
	call_if_eq GraniteCave_StevensRoom_EventScript_BagFull
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen 1
	special ChoosePartyMon
	waitstate
	perfectIvs VAR_0x8004
	playfanfare MUS_FANFA1
	fadescreen 0
	waitfanfare
	delay 30
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
	playfanfare MUS_ME_TORE_EYE
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitNorth
	compare VAR_FACING, DIR_SOUTH
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitSouth
	compare VAR_FACING, DIR_WEST
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	compare VAR_FACING, DIR_EAST
	call_if_eq GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_KAIDAN
	removeobject 1
	release
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth:: @ 822DD0D
	applymovement 1, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast:: @ 822DD18
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement 1, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth:: @ 822DD2A
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement 1, GraniteCave_StevensRoom_Movement_StevenExitSouth
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_BagFull:: @ 822DD3C
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
	return

GraniteCave_StevensRoom_Movement_StevenExit: @ 822DD45
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit: @ 822DD4C
	delay_16
	delay_16
	delay_16
	walk_in_place_fastest_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth: @ 822DD51
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Text_ImStevenLetterForMe: @ 822DD5A
	.string "{PLAYER}: ¡Steven!\p"
    .string "Steven: … ¿Te conozco?\n"
    .string "{PLAYER}: No, pero eso no importa,\l"
    .string "unos tipos disfrazados de piratas\p"
    .string "han estado robando Partes Devon y\n"
    .string "ahora se han llevado una Piedra…\p"
    .string "Aunque no sé qué clase de Piedra es…\p"
    .string "Steven: … Ya veo… Pues, les hecharé\n"
    .string "un ojo, aunque lo de la “Piedra” no\l"
    .string "me parece malo en lo absoluto…\p"
    .string "Steven: … … … ¿huh?\n"
    .string "Eso que llevas en tu mano… ¿No será\l"
    .string "una Carta? ¿Una de mi padre?\p"
    .string "{PLAYER}: ¿Huh? Pues, sí, tome.$"


GraniteCave_StevensRoom_Text_ThankYouTakeThis: @ 822DDBD
    .string "Steven: ¡Gracias! Pasaste por esos\n"
    .string "problemas sólo para darme esta\l"
    .string "carta… Debería recompensártelo…\p"
    .string "¡Ah!\n"
    .string "¿Qué tal si te doy mi MT favorita?\p"
    .string "{PLAYER}: ¿MT? ¿No es demasiado?\p"
    .string "Steven: ¡Tonterías, niño! Además,\n"
    .string "mis Pokémon ya son demasiado\l"
    .string "fuertes para este ataque tan débil…$"


GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister: @ 822DE6B
    .string "{PLAYER}: ¡Gracias, Señor Steven!\n"
    .string "¡Es usted muy amable!\p"
    .string "Steven: ¿Eso crees…?\n"
    .string "… … …\p"
    .string "Espera… ¿Has vencido a esos tres\n"
    .string "seguidos con menos de tres medallas?\p"
    .string "{PLAYER}: Umh… Supongo… ¿Es eso\n"
    .string "tan importante?\p"
    .string "Steven: … … … …\n"
    .string "… … (es fuerte… Quizá sea capaz…)\p"
    .string "Steven: Oye, ¿Quieres participar\n"
    .string "en la Liga Hoenn, no?\p"
    .string "Steven: ¡Pues haré a tus Pokémon\n"
    .string "más fuertes. Pero elige bien, {COLOR LIGHT_RED}{SHADOW RED}sólo\l"
    .string "será una vez.{COLOR DARK_GREY}{SHADOW LIGHT_GREY} Verás los cambios una\p"
    .string "vez deposites tus Pokémon en el PC,\n"
    .string "o en el momento en que suban de\l"
    .string "nivel. ¿Has entendido?\p"
    .string "{PLAYER}: S-supongo… ¡Quiero\n"
    .string "intentarlo, señor!$"


GraniteCave_StevensRoom_Text_RegisteredSteven: @ 822DF6A
    .string "Steven: ¡Hey, aprovechemos para\n"
    .string "cambiar números de Pokénav!\p"
    .string "… … … …\n"
    .string "… … … …\l"
    .string "¡Registrado Steven en el Pokénav!$"


GraniteCave_StevensRoom_Text_IveGotToHurryAlong: @ 822DF8C
	.string "Steve: ¡Bueno, me voy!$"

GraniteCave_StevensRoom_Text_OhBagIsFull: @ 822DFAA
	.string "Qué mal, Mochila llena.$"

