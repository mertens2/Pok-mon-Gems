MeteorFalls_1F_1R_MapScripts:: @ 822BD2A
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad: @ 822BD30
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	end

MeteorFalls_1F_1R_EventScript_OpenStevensCave:: @ 822BD3A
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, 1
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, 1
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, 0
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, 1
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene:: @ 822BD5F
	lockall
	playbgm MUS_MGM0, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement 5, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement 5, Common_Movement_WalkInPlaceFastestUp
	applymovement 6, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 5, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma, MSGBOX_DEFAULT
	closemessage
	applymovement 5, MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement 5, Common_Movement_WalkInPlaceFastestLeft
	applymovement 6, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	addobject 7
	addobject 8
	addobject 9
	playbgm MUS_AQA_0, 0
	applymovement 7, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement 8, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement 9, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement 5, Common_Movement_WalkInPlaceFastestLeft
	applymovement 6, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement 5, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement 6, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject 5
	removeobject 6
	applymovement 7, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement 8, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement 9, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement 7, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement 7, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement 7, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement 8, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement 9, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject 7
	removeobject 8
	removeobject 9
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	end

MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer: @ 822BEC0
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit: @ 822BEC4
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit: @ 822BECE
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive: @ 822BED9
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive: @ 822BEE0
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive: @ 822BEE8
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit: @ 822BEF0
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer: @ 822BEF8
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit: @ 822BEFE
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie: @ 822BF08
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit: @ 822BF0D
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie: @ 822BF18
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay: @ 822BF1D
	walk_in_place_fastest_down
	delay_4
	walk_in_place_fastest_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_EventScript_ProfCozmo:: @ 822BF25
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo:: @ 822BF3D
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Text_WithThisMeteorite: @ 822BF47
	.string "Recluta: ¡Je je je!\p"
	.string "Con el Meteorito, esa cosa en el\n"
	.string "MONTE CHIMNEY hará…$"

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma: @ 822BF84
	.string "Recluta: ¿Huh?\p"
	.string "No te conozco, niño. Pero si te metes\n"
	.string "con el TEAM MAGMA, ¡No esperes\l"
	.string "que seamos piadosos!$"

MeteorFalls_1F_1R_Text_HoldItRightThereMagma: @ 822BFE4
	.string "Archie: ¡Alto ahí, TEAM MAGMA!\p"
	.string "¡Están muy equivocados si creen que\n"
	.string "podrán arruinar así este mundo!$"

MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua: @ 822C04E
	.string "Maxie: ¿A quién tenemos aquí?\n"
	.string "¡Al final cambiaste de opinión!\p"
	.string "Y aunque no lo hubieras hecho…\n"
	.string "No puedes hacerte el héroe…\p"
	.string "¡Tú estás por destruir el mundo con\n"
	.string "tus estupideces, Archie!\p"
	.string "¡Pero no importa, ya tenemos el METEORITO!\p"
	.string "¡Cuida bien de ese Sandslash, Archie!\n"
	.string "¡Hasta luego, idiotas!$"

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore: @ 822C11C
	.string "ARCHIE: ¡ARGH! ¡Ese Maxie ya va a ver…!\n"
	.string "Espera…¿Qué no te vi en el MUSEO SLATERPORT?\p"
	.string "Ah, entonces te llamas {PLAYER}.\p"
	.string "En ese momento, creí que estabas con\n"
	.string "el estúpido TEAM MAGMA…\p"
	.string "Tú…\n"
	.string "Sin dudas eres raro. Pero te diré algo.\p"
	.string "Ten cuidado con ese TEAM MAGMA, y\n"
	.string "sobretodo con su líder, Maxie.\p"
	.string "Cuando quiere, puede causar mucho daño…\n"
	.string "Quieren erradicar el agua de la Tierra.\p"
	.string "¡Son rivales eternos de nosotros,\n"
	.string "el bondadoso TEAM AQUA!$"

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma: @ 822C268
	.string "Jefe, señor… Deberíamos perseguir a\n"
	.string "ese TEAM MAGMA…$"

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo: @ 822C292
	.string "ARCHIE: ¡Sí, sí, claro!\n"
	.string "Nos tenemos que ir. Ese Maxie no ganará.\p"
	.string "No hay límites de maldad para el TEAM MAGMA\n"
	.string "¡Seguro planean modificar el Volcán!$"

MeteorFalls_1F_1R_Text_ArchieFarewell: @ 822C2FC
	.string "ARCHIE: {PLAYER}, deberías mantenerte\n"
	.string "informado sobre el TEAM MAGMA.\p"
	.string "¡Avísame si hacen algo! ¡Adiós!$"

MeteorFalls_1F_1R_Text_MeetProfCozmo: @ 822C342
	.string "Hey… Soy Cozmo…\n"
	.string "Soy un Profesor…\p"
	.string "El TEAM MAGMA me dijo que investigaríamos\n"
	.string "la CATARATA METEORO…\p"
	.string "Pero me engañaron.\n"
	.string "Hasta me quitaron el Meteorito…\p"
	.string "Y el grupo rival, el TEAM AQUA,\n"
	.string "se presentó. No entendía sus peleas.\p"
	.string "Pero luego… El líder del TEAM MAGMA\n"
	.string "venció al administrador del TEAM AQUA.\p"
	.string "Se escaparon… Y cuando llegaste,\n"
	.string "es cuando vinieron con su líder. ¿Qué\n"
	.string "harán con el Meteorito en MONTE CHIMENEA?$"

MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney: @ 822C47D
	.string "Profe Cozmo: Me pregunto…\p"
	.string "¿Qué planean hacer los del TEAM MAGMA'\n"
	.string "¿Y cómo el TEAM AQUA los detendrá?$"
