DewfordTown_MapScripts:: @ 81E9507
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_OnTransition
	.byte 0
Dewford_Load::
	end
Dewford_Wally::
	lock
	applymovement 7, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 7, Common_Movement_FacePlayer
	waitmovement 0
	msgbox OhPlayer, MSGBOX_DEFAULT
	applymovement 7, Common_Movement_FaceRight
	waitmovement 0
	msgbox Enfrentare, MSGBOX_DEFAULT
	closemessage
	applymovement 7, Common_Movement_FacePlayer
	waitmovement 0
	msgbox Ralts, MSGBOX_DEFAULT
	closemessage
	applymovement 7, Common_Movement_FaceUp
	waitmovement 0
	opendoor 8,17
	waitdooranim
	delay 12
	msgbox Tupuedes, MSGBOX_DEFAULT
	closemessage
	applymovement 7, Walkup
	removeobject 7
	waitmovement 0
	delay 16
	closedoor 8,17
	waitdooranim
	compare VAR_FACING, DIR_WEST
	goto_if_eq Player1
	compare VAR_FACING, DIR_EAST
	goto_if_eq Player3
	compare VAR_FACING, DIR_NORTH
	goto_if_eq Player2
	compare VAR_FACING, DIR_SOUTH
	goto_if_eq Player2
	end
Player1::
	applymovement OBJ_EVENT_ID_PLAYER, Observar
	waitmovement 0
	delay 16
	goto WallyResto
	end
Player2::
	applymovement OBJ_EVENT_ID_PLAYER, Observar2
	waitmovement 0
	delay 16
	goto WallyResto
	end
Player3::
	applymovement OBJ_EVENT_ID_PLAYER, Observar3
	waitmovement 0
	delay 16
	goto WallyResto
	end
WallyResto::
	msgbox NoVeo, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_MEDITITE, 0
	waitmoncry
	delay 16
	playmoncry SPECIES_RALTS, 0
	waitmoncry
	msgbox Batalla, MSGBOX_DEFAULT
	playmoncry SPECIES_RALTS, 0
	msgbox ralts, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playmoncry SPECIES_KIRLIA, 0
	msgbox evolucionaste, MSGBOX_DEFAULT
	waitmoncry
	fadescreen 1
	opendoor 8,17
	waitdooranim
	addobject 7
	applymovement 7, Walkup
	waitmovement 0
	fadescreen 0
	applymovement 7, Common_Movement_FaceDown
	waitmovement 0
	applymovement 7, Walkdown
	closedoor 8,17
	waitdooranim
	applymovement 7, Common_Movement_FacePlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox ehganado, MSGBOX_DEFAULT
	release
	end

ehganado:
    .string "(Uff… Tú puedes, Wally. Tú puedes.)$"
Tupuedes:
    .string "(Uff… Tú puedes, Wally. Tú puedes.)$"
NoVeo:
    .string "Wally: ¡AAAHH! ¡Está todo oscuro,\n"
    .string "no puedo ver!\p"
    .string "Supongo que tendremos que\n"
    .string "arreglárnosla con lo que tenemos,\l"
    .string "Ralts.\p"
    .string "…\n"
    .string "………\l"
    .string "… ¡…AHH! ¡Un Entrenador!\p"
    .string "¡Ve, Ralts!\n"
    .string "¡Meditite, al centro y al frente!$"

Batalla:
    .string "¿Huh? ¿Ya contra el líder?\p"
    .string "¡Bueno, 'COF' vamos allá, Ralts!\p"
    .string "Ralts, ¡Usa Confusión!\n"
    .string "¡Vamos, ahora usa Conjuro!\l"
    .string "…\p"
    .string "Y-ya… 'COF'……'COF' Queda… 'COF'\n"
    .string "¡…POCO!\p"
    .string "¡Una última Confusión!$"
ralts:
	.string "¡RALTS……………!$"

evolucionaste:
	.string "¡……………KIRLIA!\p"
    .string "Wally: ¿U-uh?\n"
    .string "¿A-acaso…?\p"
    .string "¡EVOLUCIONASTE! ¡Y…! Y…\p"
    .string "He… He… G-ganado…\p"
    .string "'COF' ¡No lo puedo creer, Ralts eh…\n"
    .string "…digo, Kirlia! ¡Es increíble!$"

Walkdown:
	walk_down
	step_end
	
Walkup:
	walk_up
	step_end
	
Wallyentra:
	walk_down
	walk_right
	walk_right
	delay_8
	face_up
	step_end
	
Mirar:
	face_down
	delay_8
	face_right
	delay_16
	step_end
	
Observar:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end
Observar2:
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	step_end
Observar3:
	walk_fast_left
	walk_fast_up
	step_end
OhPlayer:
    .string "Wally: ¡Oh, {PLAYER}!\p"
    .string "¿Cómo has estado? ¿Has atrapado\n"
    .string "algún nuevo Pokémon?\p"
    .string "Yo Quiero participar en el desafío\n"
    .string "de los Gimnasios, quizá eso me\l"
    .string "'COF' ayude a mejorar mi condición.$"
Enfrentare:
    .string "Wally: Enfrentaré este Gimnasio\n"
    .string "primero, porque parece el más\l"
    .string "fácil para mi Ralts.\p"
    .string "¿Sabes? No tengo mucha confianza\n"
    .string "en poder ganar, no he podido ganarte\l"
    .string "antes…\p"
    .string "Realmente espero que ellos no\n"
    .string "tengan razón…\p"
    .string "{PLAYER}: ¿Ellos?\p"
    .string "Wally: Sí, mis vecinos allá en\n"
    .string "Verdantuff… Ellos me burlaban por\l"
    .string "no contar con ningún Pokémon.\p"
    .string "La situación no ha cambiado en lo\n"
    .string "absoluto en Petalburg, tampoco.\p"
    .string "No hay tantos niños allá, pero los\n"
    .string "adultos hablan en mi espalda de mis\l"
    .string "padres, porque siempre estoy enfermo.$"
Ralts:
    .string "Wally: ¡Pero bueno! 'COF'\p"
    .string "No debo dejar que lo que me dicen\n"
    .string "quite lo mejor de mí. ¡Debo\l"
    .string "continuar! ¿No?\p"
    .string "Pero bueno, mi Ralts tiene ventaja\n"
    .string "en este Gimnasio, con su Confusión\l"
    .string "podré ganar. Y cuando lo haga……\p"
    .string "Quizá podamos forjar una\n"
    .string "amistad…$"


Dewford_Grunt::
	lock
	setvar VAR_DEWFORD_GRUNT, 1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	applymovement 6, Common_Movement_FacePlayer
	waitmovement 0
	message Incomodo
	delay 120
	closemessage
	applymovement 6, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	msgbox Wooops, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement 6, Escape
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, FollowHim
	waitmovement 0
	removeobject 6
	msgbox Quefuetodoeso, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	setflag FLAG_DEWFORDGRUNT
	release
	end
FollowHim:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	delay_8
	face_up
	step_end
	step_end
Quefuetodoeso:
	.string "{PLAYER}: ¿Q-qué fue todo eso?\n"
	.string "¿Ese era un pirata?\l"
	.string "… … … … … …\p"
	.string "¡Ah!\n"
	.string "¡Es uno de esos tipos del\l"
	.string "Kilo Agua o lo que sea!\p"
	.string "¡Tengo que seguirlo,\n"
	.string "seguro quiere robar\l"
	.string "algo más! … … …\p"
	.string "P-pero el Gimnasio…$"
Escape:
	jump_in_place_left_right
	jump_in_place_down_up
	walk_fastest_down
	delay_16
	lock_facing_direction
	walk_slow_up
	unlock_facing_direction
	walk_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	step_end
Wooops:
	.string "Recluta: … … … … ¡Me voy!$"
Incomodo:
	.string ". . . . . . . . . . . .\n"
	.string ". . . . . . . . . . . .$"
DewfordTown_OnTransition: @ 81E950D
	setflag FLAG_VISITED_DEWFORD_TOWN
	end

DewfordTown_EventScript_Briney:: @ 81E9511
	lock
	faceplayer
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, DewfordTown_EventScript_ReturnToPetalburgPrompt
	message DewfordTown_Text_WhereAreWeBound
	waitmessage
	multichoicedefault 21, 6, MULTI_BRINEY_ON_DEWFORD, 2, 0
	switch VAR_RESULT
	case 0, DewfordTown_EventScript_ChoosePetalburg
	case 1, DewfordTown_EventScript_ChooseSlateport
	case 2, DewfordTown_EventScript_CancelSailSelect
	case MULTI_B_PRESSED, DewfordTown_EventScript_CancelSailSelect
	end

DewfordTown_EventScript_ChoosePetalburg:: @ 81E955A
	msgbox DewfordTown_Text_PetalburgWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	release
	end

DewfordTown_EventScript_ChooseSlateport:: @ 81E956A
	msgbox DewfordTown_Text_SlateportWereSettingSail, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToSlateport
	release
	end

DewfordTown_EventScript_CancelSailSelect:: @ 81E957A
	msgbox DewfordTown_Text_JustTellMeWhenYouNeedToSetSail, MSGBOX_DEFAULT
	closemessage
	release
	end

DewfordTown_EventScript_ReturnToPetalburgPrompt:: @ 81E9585
	msgbox DewfordTown_Text_SetSailBackToPetalburg, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_SailBackToPetalburg
	msgbox DewfordTown_Text_GoDeliverIllBeWaiting, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailBackToPetalburg:: @ 81E95A2
	msgbox DewfordTown_Text_PetalburgWereSettingSail2, MSGBOX_DEFAULT
	closemessage
	goto DewfordTown_EventScript_SailToPetalburg
	end

DewfordTown_EventScript_Woman:: @ 81E95B1
	msgbox DewfordTown_Text_TinyIslandCommunity, MSGBOX_NPC
	end

DewfordTown_EventScript_TownSign:: @ 81E95BA
	msgbox DewfordTown_Text_TownSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_GymSign:: @ 81E95C3
	msgbox DewfordTown_Text_GymSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_HallSign:: @ 81E95CC
	msgbox DewfordTown_Text_HallSign, MSGBOX_SIGN
	end

DewfordTown_EventScript_OldRodFisherman:: @ 81E95D5
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, DewfordTown_EventScript_HowsFishing
	msgbox DewfordTown_Text_GettingItchToFish, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_GiveOldRod
	compare VAR_RESULT, NO
	goto_if_eq DewfordTown_EventScript_NotGettingItchToFish
	end

DewfordTown_EventScript_GiveOldRod:: @ 81E95FF
	msgbox DewfordTown_Text_GiveYouOneOfMyRods, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox DewfordTown_Text_ThrowInFishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_NotGettingItchToFish:: @ 81E9620
	msgbox DewfordTown_Text_ThatsTooBadThen, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_HowsFishing:: @ 81E962A
	message DewfordTown_Text_HowsYourFishing
	waitmessage
	multichoice 20, 8, MULTI_HOWS_FISHING, 1
	compare VAR_RESULT, 0
	goto_if_eq DewfordTown_EventScript_FishingExcellent
	compare VAR_RESULT, 1
	goto_if_eq DewfordTown_EventScript_FishingNotSoGood
	end

DewfordTown_EventScript_FishingExcellent:: @ 81E964C
	msgbox DewfordTown_Text_GreatHaulInSomeBigOnes, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_FishingNotSoGood:: @ 81E9656
	msgbox DewfordTown_Text_FishingAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_SailToPetalburg:: @ 81E9660
	call EventScript_BackupMrBrineyLocation
	setobjectpriority 2, MAP_DEWFORD_TOWN, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN, 0
	applymovement 2, DewfordTown_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject 2
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement 4, DewfordTown_Movement_SailToPetalburg
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_SailToPetalburg
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	call Common_EventScript_StopBrineysBoatMusic
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_ExitBoatPetalburg
	waitmovement 0
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat 4, MAP_DEWFORD_TOWN
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 2
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	warp MAP_ROUTE104_MR_BRINEYS_HOUSE, 255, 5, 4
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	waitstate
	release
	end

DewfordTown_EventScript_SailToSlateport:: @ 81E96E7
	call EventScript_BackupMrBrineyLocation
	setobjectpriority 2, MAP_DEWFORD_TOWN, 0
	setobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN, 1
	applymovement 2, DewfordTown_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject 2
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	call Common_EventScript_PlayBrineysBoatMusic
	applymovement 4, DewfordTown_Movement_SailToSlateport
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_SailToSlateport
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE109
	applymovement OBJ_EVENT_ID_PLAYER, DewfordTown_Movement_ExitBoatSlateport
	waitmovement 0
	setobjectxyperm 2, 21, 26
	addobject 2
	setobjectpriority 2, MAP_ROUTE109, 0
	applymovement 2, DewfordTown_Movement_BrineyExitBoat
	waitmovement 0
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY
	addobject 1
	clearflag FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT
	setflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	hideobjectat 4, MAP_DEWFORD_TOWN
	call_if_unset FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateportDeliverGoods
	call_if_set FLAG_DELIVERED_DEVON_GOODS, DewfordTown_EventScript_LandedSlateport
	closemessage
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectpriority OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	resetobjectpriority 2, MAP_ROUTE109
	copyobjectxytoperm 2
	release
	end

DewfordTown_EventScript_LandedSlateportDeliverGoods:: @ 81E9790
	msgbox DewfordTown_Text_BrineyLandedInSlateportDeliverGoods, MSGBOX_DEFAULT
	return

DewfordTown_EventScript_LandedSlateport:: @ 81E9799
	msgbox DewfordTown_Text_BrineyLandedInSlateport, MSGBOX_DEFAULT
	return

DewfordTown_Movement_SailToPetalburg: @ 81E97A2
	walk_up
	walk_up
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
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_SailToSlateport: @ 81E9865
	walk_right
	walk_fast_right
	walk_fast_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fastest_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
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

DewfordTown_Movement_PlayerBoardBoat: @ 81E9911
	walk_right
	walk_up
	step_end

DewfordTown_Movement_ExitBoatPetalburg: @ 81E9914
	walk_up
	walk_up
	walk_up
	step_end

DewfordTown_Movement_ExitBoatSlateport: @ 81E9918
	walk_up
	walk_up
	walk_up
	walk_in_place_fastest_down
	step_end

DewfordTown_Movement_BrineyBoardBoat: @ 81E991D
	walk_up
	step_end

DewfordTown_Movement_BrineyExitBoat: @ 81E991F
	walk_up
	walk_up
	step_end
DewfordTown_EventScript_TrendyPhraseBoy::
	lock
	faceplayer
	multichoice  20, 0, MULTI_BADGESDEBUG 0
	switch VAR_RESULT
	case 0, DewfordTown_EventScript_Badge1
	case 1, DewfordTown_EventScript_Badge2
	case 2, DewfordTown_EventScript_Badge3
	case 3, DewfordTown_EventScript_Badge4
	case 4, DewfordTown_EventScript_Badge5
	case 5, DewfordTown_EventScript_Badge6
	case 6, DewfordTown_EventScript_Badge7
	case 7, DewfordTown_EventScript_Badge8	
	end
DewfordTown_EventScript_Badge1::
	setflag FLAG_BADGE01_GET
	release
	end
DewfordTown_EventScript_Badge2::
	setflag FLAG_BADGE02_GET
	release
	end
DewfordTown_EventScript_Badge3::
	setflag FLAG_BADGE03_GET
	release
	end
DewfordTown_EventScript_Badge4::
	setflag FLAG_BADGE04_GET
	release
	end
DewfordTown_EventScript_Badge5::
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	setflag FLAG_BADGE05_GET
	release
	end
DewfordTown_EventScript_Badge6::
	setflag FLAG_BADGE06_GET
	release
	end
DewfordTown_EventScript_Badge7::
	setflag FLAG_BADGE07_GET
	release
	end
DewfordTown_EventScript_Badge8::
	setflag FLAG_BADGE08_GET
	release
	end

DewfordTown_EventScript_DadordeMedallas:: @ 81E9922
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Text_XIsTheBiggestHappeningThingRight, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_EventScript_ConfirmTrendyPhrase
	compare VAR_RESULT, NO
	goto_if_eq DewfordTown_EventScript_RejectTrendyPhrase
	end

DewfordTown_EventScript_ConfirmTrendyPhrase:: @ 81E9948
	msgbox DewfordTown_Text_YeahDefinitionOfInRightNow, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_RejectTrendyPhrase:: @ 81E9952
	msgbox DewfordTown_Text_TellMeWhatsNewAndIn, MSGBOX_DEFAULT
	setvar VAR_0x8004, EASY_CHAT_TYPE_TRENDY_PHRASE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	compare VAR_RESULT, 1
	goto_if_eq DewfordTown_EventScript_GiveNewTrendyPhrase
	compare VAR_RESULT, 0
	goto_if_eq DewfordTown_EventScript_CancelNewTrendyPhrase
	end

DewfordTown_EventScript_GiveNewTrendyPhrase:: @ 81E997D
	incrementgamestat GAME_STAT_STARTED_TRENDS
	compare VAR_0x8004, 0
	goto_if_eq DewfordTown_EventScript_PhraseNotTrendyEnough
	msgbox DewfordTown_Text_OfCourseIKnowAboutThat, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_CancelNewTrendyPhrase:: @ 81E9994
	msgbox DewfordTown_Text_HearOfAnyTrendsComeShareWithMe, MSGBOX_DEFAULT
	release
	end

DewfordTown_EventScript_PhraseNotTrendyEnough:: @ 81E999E
	msgbox DewfordTown_Text_XHuhIThinkYIsCool, MSGBOX_DEFAULT
	release
	end

DewfordTown_Text_TinyIslandCommunity: @ 81E99A8
    .string "He escuchado que han caído {COLOR LIGHT_BLUE}{SHADOW BLUE}pedazos\n"
    .string "de Luna desde el cielo recientemente.\p"
    .string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}Me pregunto a qué se deberá eso...$"

DewfordTown_Text_TownSign: @ 81E9A0F
	.string "{COLOR LIGHT_BLUE}{SHADOW BLUE}¡PUEBLO DEWFORD!\n"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}“Una isla cerca del mar.”$"

DewfordTown_Text_GymSign: @ 81E9A3D
	.string "{COLOR LIGHT_RED}{SHADOW RED}GIMNASIO DEWFORD\n"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}LÍDER: BRAWLY\l"
	.string "“¡Una chocante ola!”$"

DewfordTown_Text_HallSign: @ 81E9A7F
	.string "{COLOR LIGHT_RED}{SHADOW RED}SALÓN DEWFORD\n"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}“¡Lo que está de moda se sabe aquí!”$"

Route104_Text_LandedInDewfordDeliverLetter: @ 81E9AAF
	.string "MR. BRINEY: Ahoy!\n"
	.string "We've hit land in DEWFORD.\p"
	.string "I suppose you're off to deliver that\n"
	.string "LETTER to, who was it now, STEVEN!$"

DewfordTown_Text_SetSailBackToPetalburg: @ 81E9B24
	.string "MR. BRINEY: Have you delivered your\n"
	.string "LETTER?\p"
	.string "Or were you meaning to sail back to\n"
	.string "PETALBURG?$"

DewfordTown_Text_PetalburgWereSettingSail2: @ 81E9B7F
	.string "MR. BRINEY: PETALBURG it is, then!\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_GoDeliverIllBeWaiting: @ 81E9BD9
	.string "MR. BRINEY: Then you go on and deliver\n"
	.string "the LETTER. I'll be waiting.$"

DewfordTown_Text_BrineyLandedInDewford: @ 81E9C1D
	.string "MR. BRINEY: Ahoy!\n"
	.string "We've hit land in DEWFORD!\p"
	.string "You just go on and tell me whenever\n"
	.string "you want to set sail again!$"

DewfordTown_Text_WhereAreWeBound: @ 81E9C8A
	.string "MR. BRINEY: Ahoy!\n"
	.string "For you, I'll go out to sea anytime!\p"
	.string "Now, my friend, where are we bound?$"

DewfordTown_Text_PetalburgWereSettingSail: @ 81E9CE5
	.string "MR. BRINEY: PETALBURG, is it?\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_SlateportWereSettingSail: @ 81E9D3A
	.string "MR. BRINEY: SLATEPORT, is it?\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we're setting sail, my darling!$"

DewfordTown_Text_JustTellMeWhenYouNeedToSetSail: @ 81E9D8F
	.string "MR. BRINEY: You just tell me whenever\n"
	.string "you need to set sail again!$"

DewfordTown_Text_GettingItchToFish: @ 81E9DD1
	.string "This is a renowned fishing spot.\n"
	.string "Are you getting the itch to fish?$"

DewfordTown_Text_GiveYouOneOfMyRods: @ 81E9E14
	.string "I hear you, and I like what\n"
	.string "you're saying!\p"
	.string "I'll give you one of my fishing RODS.$"

DewfordTown_Text_ThrowInFishingAdvice: @ 81E9E65
	.string "And, as an added bonus, I'll even throw\n"
	.string "in a little fishing advice!\p"
	.string "First, you want to face the water,\n"
	.string "then use the ROD.\p"
	.string "Focus your mind…\n"
	.string "If you get a bite, pull on the ROD.\p"
	.string "Sometimes you can snag something\n"
	.string "immediately, but with bigger catches,\l"
	.string "you need to time the pulls on your ROD\l"
	.string "to haul them in.$"

DewfordTown_Text_ThatsTooBadThen: @ 81E9F92
	.string "Oh, is that so?\n"
	.string "That's too bad, then.$"

DewfordTown_Text_HowsYourFishing: @ 81E9FB8
	.string "Yo!\n"
	.string "How's your fishing?$"

DewfordTown_Text_GreatHaulInSomeBigOnes: @ 81E9FD0
	.string "Is that right! That's great!\n"
	.string "Haul in some big ones!$"

DewfordTown_Text_FishingAdvice: @ 81EA004
	.string "Oh, hey, don't get down on yourself!\n"
	.string "I'll give you a little fishing advice.\p"
	.string "First, you want to face the water,\n"
	.string "then use the ROD.\p"
	.string "Focus your mind…\n"
	.string "If you get a bite, pull the ROD.\p"
	.string "Sometimes you can snag something\n"
	.string "immediately, but with bigger catches,\l"
	.string "you need to time the pulls on your ROD\l"
	.string "to haul them in.$"

DewfordTown_Text_XIsTheBiggestHappeningThingRight: @ 81EA136
	.string "I like what's hip, happening, and trendy.\n"
	.string "I'm always checking it out.\p"
	.string "Listen, have you heard about this new\n"
	.string "“{STR_VAR_1}”?\p"
	.string "That's right!\n"
	.string "Of course you know!\p"
	.string "I mean, sheesh,\n"
	.string "“{STR_VAR_1}”…\l"
	.string "It's the hottest thing in cool!\p"
	.string "Wherever you're from,\n"
	.string "“{STR_VAR_1}”\l"
	.string "is the biggest happening thing, right?$"

DewfordTown_Text_TellMeWhatsNewAndIn: @ 81EA242
	.string "Hunh?\n"
	.string "It's not the hip and happening thing?\p"
	.string "Well, hey, you have to tell me,\n"
	.string "what's new and what's “in”?$"

DewfordTown_Text_OfCourseIKnowAboutThat: @ 81EA2AA
	.string "Hunh?\n"
	.string "“{STR_VAR_2}”?\p"
	.string "… …\p"
	.string "…Uh… Yeah! That's right!\n"
	.string "Yeah, I knew that! Knew it all along!\p"
	.string "Of course I know about that!\n"
	.string "“{STR_VAR_2},” right?\p"
	.string "Yeah, that's it, it's there!\n"
	.string "Isn't “{STR_VAR_2}”\l"
	.string "the coolest, or what?\p"
	.string "It's the hippest thing in hip.\n"
	.string "You think I'd not know about it?\p"
	.string "“{STR_VAR_1}”…\n"
	.string "It's, like, so five minutes ago.\p"
	.string "Now, “{STR_VAR_2}” is\n"
	.string "what's vital and in tune with the times!$"

DewfordTown_Text_XHuhIThinkYIsCool: @ 81EA3FE
	.string "Hmm…\n"
	.string "“{STR_VAR_2},” huh?\p"
	.string "But personally, I think\n"
	.string "“{STR_VAR_1}”\l"
	.string "is what's real in cool.$"

DewfordTown_Text_HearOfAnyTrendsComeShareWithMe: @ 81EA443
	.string "Well, if you hear of any happening new\n"
	.string "trends, come share them with me, okay?$"

DewfordTown_Text_YeahDefinitionOfInRightNow: @ 81EA491
	.string "Yeah, absolutely right!\p"
	.string "“{STR_VAR_1}” is the\n"
	.string "definition of “in” right now.$"
