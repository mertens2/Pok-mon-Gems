SlateportCity_OceanicMuseum_2F_MapScripts:: @ 820BAFF
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern:: @ 820BB00
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_AQA_0, 1
	addobject 3
	applymovement 3, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject 4
	applymovement 4, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement 3, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement 4, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	compare VAR_FACING, DIR_SOUTH
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	compare VAR_FACING, DIR_EAST
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	compare VAR_FACING, DIR_EAST
	msgbox  MuyTarde, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	call_if_ne SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	applymovement 4, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	compare VAR_FACING, DIR_SOUTH
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	compare VAR_FACING, DIR_WEST
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement 4, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement 3, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement 3, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement 3, Common_Movement_WalkInPlaceFastestDown
	applymovement 4, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject 2
	applymovement 2, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement 4, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement 2, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	msgbox SlateportCity_OceanicMuseum_2F_Desicion, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_OceanicMuseum_2F_EventScript_CaptSternOdio
	msgbox SlateportCity_OceanicMuseum_2F_Estabien, MSGBOX_DEFAULT
	closemessage
	addvar VAR_ARCHIES_TRUST, 1
	msgbox SlateportCity_OceanicMuseum_2F_BuenaDesicion, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_EresAliadoAqua, MSGBOX_DEFAULT
	givedecoration DECOR_BLUE_TENT
	giveitem ITEM_MYSTIC_WATER, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject 2
	removeobject 3
	removeobject 4
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_ME_ASA
	waitfanfare
	special HealPlayerParty
	removeobject 1
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	compare VAR_REGISTER_BIRCH_STATE, 0
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end
MuyTarde:
    .string "{PLAYER}: ¡Muy tarde!\n"
    .string "Tenga, Capitán Stern.$"
SlateportCity_OceanicMuseum_2F_NoloEstoy:
    .string "{PLAYER}: ¡NO!\n"
    .string "Es decir, sí, en el mar habitan\l"
    .string "Pokémon y eso, pero…\p"
    .string "{PLAYER}: ¡Todo se trata de\n"
    .string "equilibrio! En tierra firme habitan\l"
    .string "un sinnúmero de Pokémon…\p"
    .string "{PLAYER}: ¡Y también humanos!\n"
	.string "Nuestros seres amados…\p"
    .string "Es igual de importante… Y el\p"
    .string "crecimiento de los mares es\n"
    .string "alarmante, también…$"
SlateportCity_OceanicMuseum_2F_MalaDesicion:
    .string "Archie: … … …\n"
    .string "… … … … … …\l"
    .string "… … … … … … … … … … … …\p"
    .string "Archie: ¿¡TIERRA!? ¡CREÍ QUE NO\n"
    .string "ERAS DE ESOS DESGRACIADOS\l"
    .string "DEL EQUIPO MAGMA!\p"
    .string "{PLAYER}: Ya se lo dije, no lo soy…\p"
    .string "Archie: ¡PERO CLARO QUE LO ERES!\n"
    .string "¡SEGURO ERES UN ALIADO DE ELLOS!\l"
    .string "Me recuerdas a… ÉL…\p"
    .string "Archie: ¿Sabes? Por personas{COLOR RED}{SHADOW LIGHT_BLUE} cerradas\n"
    .string "y agresivas {COLOR DARK_GREY}{SHADOW LIGHT_GREY}como tú, el mundo está\l"
    .string "como está… Aunque seguro no lo sabes…\p"
    .string "Archie: No creo que comprendas la\n"
    .string "complejidad de la situación, debes\l"
    .string "estar confundido…\p"
    .string "Archie: Aunque sí entiendes algo…\n"
    .string "{COLOR BLUE}{SHADOW LIGHT_RED}Nuestros amados están en la tierra…{COLOR DARK_GREY}{SHADOW LIGHT_GREY}\l"
    .string "Y eso es… Importantísimo…\p"
    .string "Archie: … … … …$"

SlateportCity_OceanicMuseum_2F_Inteligente:
    .string "Archie: Aunque cegado, pareces\n"
    .string "bastante inteligente y bueno en las\l"
    .string "batallas Pokémon…\p"
    .string "Archie: Entonces, sabrás la\n"
    .string "inutilidad de estos en combate.\p"
    .string "Archie: Tómalo como un regalo\n"
    .string "por compasión… Del generoso Archie.$"

SlateportCity_OceanicMuseum_2F_EventScript_CaptSternOdio::
	msgbox SlateportCity_OceanicMuseum_2F_NoloEstoy, MSGBOX_DEFAULT
	closemessage
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_MalaDesicion, MSGBOX_DEFAULT
	closemessage
	applymovement 2, Common_Movement_FaceLeft
	waitmovement 0
	delay 8
	applymovement 2, Common_Movement_FaceRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Inteligente, MSGBOX_DEFAULT
	closemessage
	givedecoration DECOR_RED_TENT
	giveitem ITEM_RING_TARGET, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject 2
	removeobject 3
	removeobject 4
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_ME_ASA
	waitfanfare
	special HealPlayerParty
	removeobject 1
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	compare VAR_REGISTER_BIRCH_STATE, 0
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end
SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch:: @ 820BC8C
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts:: @ 820BC92
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts:: @ 820BC9D
	applymovement 1, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth:: @ 820BCA8
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest:: @ 820BCB3
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth: @ 820BCBE
	walk_left
	walk_down
	walk_in_place_fastest_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest: @ 820BCC2
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_fastest_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused: @ 820BCC8
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer: @ 820BCD6
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter: @ 820BCD8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle: @ 820BCE2
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter: @ 820BCE4
	walk_down
	walk_right
	walk_in_place_fastest_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach: @ 820BCE8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated: @ 820BCEF
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter: @ 820BCF3
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach: @ 820BCF5
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie: @ 820BCFE
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_fastest_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1:: @ 820BD0A
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2:: @ 820BD13
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment:: @ 820BD1C
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel:: @ 820BD25
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay:: @ 820BD2E
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay:: @ 820BD37
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica:: @ 820BD40
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica:: @ 820BD49
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica:: @ 820BD52
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica:: @ 820BD5B
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1:: @ 820BD64
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2:: @ 820BD6D
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3:: @ 820BD76
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Estabien:
    .string "{PLAYER}: ¡Por supuesto que lo estoy!\p"
    .string "Después de todo, el mar es increíble,\n"
    .string "¡Y es el hábitat de cientos de miles\l"
    .string "de Pokémon! Aunque…\p"
    .string "{PLAYER}: Creo que el submarino\n"
    .string "debería pasar por una seria ronda de\l"
    .string "pruebas antes de que sea usado…$"

SlateportCity_OceanicMuseum_2F_BuenaDesicion:
    .string "Archie: ¡Bien dicho, tú, bien dicho!\n"
    .string "Eres sin dudas, eres como yo…\l"
    .string "Has abierto mis ojos ante una\p"
    .string "posiblidad que no había previsto…\p"
    .string "Archie: Si el submarino llegara a\n"
    .string "tener un percance, ¡Toda la misión\l"
    .string "sería arruinada!\p"
    .string "{PLAYER}: Eh… Sí, sí, y probablemente\n"
    .string "no sobrevivirían a la presión del\l"
    .string "fondo marino…\p"
    .string "Archie: ¡Mi vida es lo de menos!\p"
    .string "El sueño del Equipo Aqua estaría\n"
    .string "comprometido! ¡Es inimaginable!$"
SlateportCity_OceanicMuseum_2F_EresAliadoAqua:
    .string "Archie: ¡Es grandioso contar con\n"
    .string "alguien tan {COLOR BLUE}{SHADOW LIGHT_RED}calmado y fuerte {COLOR DARK_GREY}{SHADOW LIGHT_GREY}como\l"
    .string "yo en el Equipo, alguien igual de\p"
    .string "pacífico como el fantástico Archie!…\p"
    .string "{PLAYER}: S-su equipo no lo parece\n"
    .string "tanto… Ya me atacaron en 4 ocasiones\l"
    .string "y una vez robaron mi mochila junto\p"
    .string "a varios de mis Pokémon…\p"
    .string "Archie: ¿Qué? ¿Esos ineptos?\n"
    .string "¡Te alegrará saber que ya no forman\l"
    .string "parte de mi equipo!\p"
    .string "Archie: ¡El Equipo Aqua tiene una\n"
    .string "reputación que mantener!\p"
    .string "Archie: Bueno, lo quieras o no, ahora\n"
    .string "eres un aliado del Equipo Aqua.\p"
    .string "Archie: Eso no significa que seas\n"
    .string "parte del equipo, sin embargo, y\l"
    .string "si interfieres cobrarás el mismo\p"
    .string "castigo que cobraría un Recluta del\n"
    .string "{COLOR LIGHT_RED}{SHADOW RED}Equipo Magma…{COLOR DARK_GREY}{SHADOW LIGHT_GREY}\p"
    .string "Archie: Creo… Que deberías tener\n"
    .string "esto, para recordar esa alianza.\l"
    .string "Es un regalo del generoso Archie.$"


SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts: @ 820BD8D
    .string "???: ¿Si? Si buscas a Stern, ese\n"
    .string "sería yo.\p"
    .string "Stern. ¡Ah! ¡Esas son las Partes que\n"
    .string "le ordené al científico de Devon!\p"
    .string "{PLAYER}: Sí, pero… ¿Porqué el\n"
    .string "Presidente Stone no sabía nada-?\p"
    .string "Stern: ¡Las conoce por otro nombre,\n"
    .string "así de simple!$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts: @ 820BE40
    .string "???: ¡Esas Partes son nuestras!\p"
    .string "???: ¡Sí, legalmente nuestras!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou: @ 820BE69
    .string "Stern: ¿EH? ¿Equi…én son estos?\p"
    .string "{PLAYER}: ¿Eh? {COLOR LIGHT_BLUE} {SHADOW BLUE}(No tiene cara de\n"
    .string "sorprendido, si no de culpa…){COLOR DARK_GREY} {SHADOW LIGHT_GREY}\p"
    .string "Recluta A: ¡Sabes quienes somos!\n"
    .string "Recluta B: ¡Pero igual lo diremos!$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua: @ 820BE93
    .string "Recluta A: ¡Somos el Equipo Aqua!\n"
    .string "Recluta B: ¡Y el Jefe solicitó las\l"
    .string "Partes que te pidió!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat: @ 820BEE2
	.string "¡AAAHHH!\n"
	.string "¡Este chico es fuerte!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious: @ 820BEFA
	.string "Ay, no, qué desastre…\n"
	.string "El Jefe no lo perdonará…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis: @ 820BF35
	.string "¡Ah, pero qué inútil!\n"
	.string "¡Yo terminaré con esto!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat: @ 820BF66
	.string "¡¿QUÉ?!\n"
	.string "¡PERDÍ TAMBIÉN!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid: @ 820BF7A
    .string "Recluta A: ¿Y ahora qué?\n"
    .string "¡Necesitábamos las Partes, pero ese\l"
    .string "niño nos destrozará de nuevo!\p"
    .string "Recluta B: ¡No lo sé, no contaba\n"
    .string "con que un simple niño nos pondría\l"
    .string "un freno!\p"
    .string "Recluta A: P-pero las Partes…\n"
    .string "Ambos: ¿No eran nuestras legalmente?$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong: @ 820BFF2
    .string "???: ¡¿Qué?!\n"
    .string "Vengo aquí para ver porqué tardan\l"
    .string "tanto en traer mi Parte, y ¿Qué veo?\p"
    .string "{PLAYER}: {COLOR LIGHT_BLUE} {SHADOW BLUE}(No sé quién sea él, pero\n"
    .string "sin dudas es imponente…){COLOR DARK_GREY} {SHADOW LIGHT_GREY}\p"
    .string "???: No importa qué digan, ese niño\n"
    .string "no tiene derecho a negarles lo que\l"
    .string "ya es mío. Debí haberlas venido a\p"
    .string "buscar yo…$"


SlateportCity_OceanicMuseum_2F_Text_ArchieWarning: @ 820C059
    .string "???: ¡Somos el gran Equipo Aqua!\n"
    .string "¡Liderado por el gran, poderoso y\l"
    .string "majestuoso Archie!\p"
    .string "{PLAYER}: ¿¡ARCHIE!?\p"
    .string "{COLOR LIGHT_BLUE} {SHADOW BLUE}(¿El mismo Archie al que tanto\n"
    .string "admiraban esos Reclutas?){COLOR DARK_GREY} {SHADOW LIGHT_GREY}\p"
    .string "Archie: Al parecer, este niño ya me\n"
    .string "conoce…\p"
    .string "Archie: ¿Tú quién eres, niño, eh?\n"
    .string "¡Responde!\p"
    .string "{PLAYER}: Ehh… Ehh… ¡Soy {PLAYER}!\p"
    .string "Archie: ¿{PLAYER}, eh? Me aseguraré\n"
    .string "de recordar ese nombre…\p"
    .string "Archie: Así sabré a quién ir a buscar\n"
    .string "cuando destroze los malvados planes\l"
    .string "del{COLOR LIGHT_RED}{SHADOW RED} Equipo Magma…{COLOR DARK_GREY}{SHADOW LIGHT_GREY}\p"
    .string "{PLAYER}: ¿E-Equipo Magma?\p"
    .string "Archie: ¿No los conoces?\p"
    .string "S-sí, ahora que lo pienso, no te\n"
    .string "vistes con esas ridículas ropas de\l"
    .string "cavernícola.\p"
    .string "… … … … … …\n"
    .string "… … … … … …\l"
    .string "… … … … … …\p"
    .string "Archie: Pokémon, gente… ¡Todos ellos\n"
    .string "pagarán el mismo precio, sufrirán\l"
    .string "el mismo destino por las egoístas\p"
    .string "acciones humanas.\p"
    .string "Archie: No soy diferente. ¡Pero\n"
    .string "pienso solucionar esos problemas!\p"
    .string "{PLAYER}: ¿De qué hablas? ¿Problemas?\p"
    .string "Archie: ¡Sí, problemas!\n"
    .string "¡La contaminación!\p"
    .string "¡El calentamiento de las aguas!\p"
    .string "Archie: ¡Todo eso provoca el cambio\n"
    .string "climático! ¡Sobretodo el\l"
    .string "calentamiento oceánico!\p"
    .string "Archie: Necesito saber, niño,\n"
    .string "¿Estás de acuerdo con lo que digo?\l"
    .string "¿Crees tu también que hay que\p"
    .string "hacer algo para arreglar eso?$"

SlateportCity_OceanicMuseum_2F_Desicion:
	.string "{PLAYER}: Eh… Y-yo…$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs: @ 820C2BE
    .string "Stern: ¡Lamento esos acontecimientos!\p"
    .string "¡No conozco a esos del Equipo\n"
    .string "Aqua, ni siquiera sabía de su\l"
    .string "existencia hasta hoy!\p"
    .string "{PLAYER}: Claaaaaaro, pero… No tiene\n"
    .string "que decírmelo, después de todo,\l"
    .string "parecen mantener un perfil bajo…\p"
    .string "Stern: Sí, sí, supongo que si fueran\n"
    .string "más ruidosos los habría conocido…\p"
    .string "{PLAYER}: Por cierto… Quien me pidió\n"
    .string "que viniera aquí a entregarlo fue\l"
    .string "atacado por el Equipo Aqua dos veces…\p"
    .string "Stern: Uh… Yo no me enteré de eso…\p"
    .string "{PLAYER}: Bueno, no es importante…\n"
    .string "¡Lo importante es que ya tienes las\l"
    .string "Partes!$"


SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo: @ 820C36C
    .string "{PLAYER}: Aún así… ¿Qué era todo\n"
    .string "eso de que eran suyas por derecho?\p"
    .string "Stern: Uh… ¡M-Mentiras de unos\n"
    .string "estúpidos hombres en cosplay!\p"
    .string "Stern: Probablemente sólo querían\n"
    .string "manipularte para que les\l"
    .string "des las Partes.\p"
    .string "{PLAYER}: Sí, tiene sentido… No se\n"
    .string "ven muy honestos ni confiables…\p"
    .string "Stern: ¡Pero yo sí que lo soy!\n"
    .string "¡Conmigo, este proyecto saldrá\l"
    .string "a flote, incluso sin Devon!\p"
    .string "Como sea… ¡Me t-tengo que ir!\n"
    .string "¡P-pero tómate tu tiempo para ver\l"
    .string "el museo!$"
SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip: @ 820C43F
	.string "I saw a model of a ship here.\p"
	.string "It reminded me of the ABANDONED SHIP\n"
	.string "near DEWFORD TOWN…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum: @ 820C495
	.string "Don't you dare run around inside\n"
	.string "the MUSEUM!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine: @ 820C4C2
	.string "Wow, the submarine's awesome!\n"
	.string "I want to go for a ride!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1: @ 820C4F9
	.string "“WATER QUALITY SAMPLE 1,” the\n"
	.string "label says.\p"
	.string "The sea is all connected, but the\n"
	.string "water seems to differ by region.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2: @ 820C566
	.string "“WATER QUALITY SAMPLE 2,” the\n"
	.string "label says.\p"
	.string "Does the saltiness of seawater differ\n"
	.string "by region, too?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment: @ 820C5C6
	.string "A rubber ball is expanding and\n"
	.string "shrinking.\p"
	.string "“In the sea, the weight of water itself\n"
	.string "exerts pressure.\p"
	.string "“In shallow water, the pressure is not\n"
	.string "very heavy.\p"
	.string "“However, in extremely deep water,\n"
	.string "the pressure can reach even tens of\l"
	.string "thousands of tons on a small area.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel: @ 820C6C7
	.string "“MODEL OF HOENN REGION”\p"
	.string "It's a miniature diorama of the\n"
	.string "HOENN region.\p"
	.string "Where is LITTLEROOT TOWN on this?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay: @ 820C72F
	.string "It's a display on the flow of seawater.\p"
	.string "“Near the bottom of the sea, water\n"
	.string "flows due to differences in such\l"
	.string "factors as temperature and salinity.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay: @ 820C7C1
	.string "It's a display on the flow of seawater.\p"
	.string "“Toward the surface, seawater flows\n"
	.string "as currents driven by the winds.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica: @ 820C82F
	.string "“THE FERRY S.S. TIDAL\p"
	.string "“A scale replica of the ship under\n"
	.string "construction at STERN'S SHIPYARD.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica: @ 820C88B
	.string "“SUBMARINE EXPLORER 1\p"
	.string "“A replica of the high-performance\n"
	.string "ocean floor exploration submarine.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica: @ 820C8E8
	.string "“SUBMERSIBLE POD\p"
	.string "“A replica of a compact, unmanned\n"
	.string "pod for seafloor exploration.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica: @ 820C93A
	.string "“S.S. ANNE\p"
	.string "“A replica of the luxury liner that\n"
	.string "circles the globe.”$"

