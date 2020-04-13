Route116_MapScripts:: @ 81F2C0C
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route116_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route116_OnFrame
	.byte 0

Route116_OnTransition: @ 81F2C1C
	call_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_SetWandasBoyfriendPos
	compare VAR_SHOULD_END_ABNORMAL_WEATHER, 1
	call_if_eq AbnormalWeather_EventScript_HideMapNamePopup
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH
	call_if_eq AbnormalWeather_StartGroudonWeather
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH
	call_if_eq AbnormalWeather_StartGroudonWeather
	end

Route116_EventScript_SetWandasBoyfriendPos:: @ 81F2C47
	setobjectxyperm 21, 38, 10
	return

Route116_OnLoad: @ 81F2C4F
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute116North
	compare VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH
	call_if_eq AbnormalWeather_EventScript_PlaceTilesRoute116South
	end

Route116_OnFrame: @ 81F2C66
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route116_EventScript_WandasBoyfriend:: @ 81F2C70
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_BoyfriendGruntLeftTunnel
	goto_if_set FLAG_DEVON_GOODS_STOLEN, Route116_EventScript_BoyfriendGruntInTunnel
	msgbox Route116_Text_WantToDigTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntLeftTunnel:: @ 81F2C8E
	msgbox Route116_Text_GoonHightailedItOutOfTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntInTunnel:: @ 81F2C98
	msgbox Route116_Text_DiggingTunnelWhenGoonOrderedMeOut, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_DevonEmployee:: @ 81F2CA2
	lock
	faceplayer
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, Route116_EventScript_TryGiveRepeatBallAgain
	msgbox Route116_Text_ThankYouTokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_GiveRepeatBall:: @ 81F2CBB
	setflag FLAG_MET_DEVON_EMPLOYEE
	giveitem ITEM_REPEAT_BALL
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_NoRoomForRepeatBall
	msgbox Route116_Text_NewBallAvailableAtMart, MSGBOX_DEFAULT
	closemessage
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_SOUTH
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_WEST
	call_if_eq Route116_EventScript_DevonEmployeeExit
	compare VAR_FACING, DIR_EAST
	call_if_eq Route116_EventScript_DevonEmployeeExitEast
	removeobject VAR_LAST_TALKED
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setflag FLAG_RECEIVED_REPEAT_BALL
	release
	end

Route116_EventScript_DevonEmployeeExit:: @ 81F2D15
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExit
	waitmovement 0
	return

Route116_EventScript_DevonEmployeeExitEast:: @ 81F2D20
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExitEast
	waitmovement 0
	return

Route116_EventScript_TryGiveRepeatBallAgain:: @ 81F2D2B
	msgbox Route116_Text_TokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_NoRoomForRepeatBall:: @ 81F2D39
	msgbox Route116_Text_BagIsJamPacked, MSGBOX_DEFAULT
	release
	end

Route116_Movement_DevonEmployeeExit: @ 81F2D43
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_DevonEmployeeExitEast: @ 81F2D4C
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_RouteSignRustboro:: @ 81F2D57
	msgbox Route116_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route116_EventScript_RusturfTunnelSign:: @ 81F2D60
	msgbox Route116_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

Route116_EventScript_TunnelersRestHouseSign:: @ 81F2D69
	msgbox Route116_Text_TunnelersRestHouse, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBToStopEvolution:: @ 81F2D72
	msgbox Route116_Text_TrainerTipsBToStopEvolution, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBagHasPockets:: @ 81F2D7B
	msgbox Route116_Text_TrainerTipsBagHasPockets, MSGBOX_SIGN
	end

Route116_EventScript_Briney:: @ 81F2D84
	lock
	faceplayer
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	release
	end

Route116_EventScript_BrineyTrigger:: @ 81F2D95
	lockall
	applymovement 11, Common_Movement_WalkInPlaceFastestRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	releaseall
	end

Route116_EventScript_GlassesMan:: @ 81F2DB6
	lock
	faceplayer
	checkitem ITEM_BLACK_GLASSES, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_PlayerHasGlasses
	specialvar VAR_RESULT, FoundBlackGlasses
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_FoundGlassesNotOnPlayer
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesNotOnPlayer:: @ 81F2DE2
	msgbox Route116_Text_CantFindGlassesNotHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_PlayerHasGlasses:: @ 81F2DF1
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	msgbox Route116_Text_MayISeeThoseGlasses, MSGBOX_DEFAULT
	specialvar VAR_RESULT, FoundBlackGlasses
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_FoundGlassesOnPlayer
	msgbox Route116_Text_NotWhatImLookingFor, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesOnPlayer:: @ 81F2E1B
	msgbox Route116_Text_NotWhatImLookingForMaybeTheyArentHere, MSGBOX_DEFAULT
	giveitem ITEM_NUGGET, 1
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_GlassesManExit:: @ 81F2E2A
	delay 20
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_SOUTH
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_WEST
	call_if_eq Route116_EventScript_GlassesManExitNormal
	compare VAR_FACING, DIR_EAST
	call_if_eq Route116_EventScript_GlassesManExitEast
	removeobject VAR_LAST_TALKED
	release
	end

Route116_EventScript_GlassesManExitNormal:: @ 81F2E5E
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExit
	waitmovement 0
	return

Route116_EventScript_GlassesManExitEast:: @ 81F2E69
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExitEast
	waitmovement 0
	return

Route116_Movement_GlassesManExit: @ 81F2E74
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_GlassesManExitEast: @ 81F2E7E
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_EventScript_Joey:: @ 81F2E89
	trainerbattle_single TRAINER_JOEY, Route116_Text_JoeyIntro, Route116_Text_JoeyDefeat
	msgbox Route116_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jose:: @ 81F2EA0
	trainerbattle_single TRAINER_JOSE, Route116_Text_JoseIntro, Route116_Text_JoseDefeat
	msgbox Route116_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jerry:: @ 81F2EB7
	trainerbattle_single TRAINER_JERRY_1, Route116_Text_JerryIntro, Route116_Text_JerryDefeat, Route116_EventScript_TryRegisterJerryAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_RematchJerry
	setvar VAR_0x8004, TRAINER_JERRY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_TryRegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterJerryAfterBattle:: @ 81F2EF8
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerryAfterBattle
	release
	end

Route116_EventScript_RegisterJerryAfterBattle:: @ 81F2F03
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_JerryRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_TryRegisterJerry:: @ 81F2F22
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterJerry:: @ 81F2F35
	msgbox Route116_Text_JerryRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_RematchJerry:: @ 81F2F4E
	trainerbattle_rematch TRAINER_JERRY_1, Route116_Text_JerryRematchIntro, Route116_Text_JerryRematchDefeat
	msgbox Route116_Text_JerryPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Clark:: @ 81F2F65
	trainerbattle_single TRAINER_CLARK, Route116_Text_ClarkIntro, Route116_Text_ClarkDefeat
	msgbox Route116_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Janice:: @ 81F2F7C
	trainerbattle_single TRAINER_JANICE, Route116_Text_JaniceIntro, Route116_Text_JaniceDefeat
	msgbox Route116_Text_JanicePostBattle, MSGBOX_AUTOCLOSE
	end
Route116_EventScript_Pokemon::
	msgbox OhDosVelozBall, MSGBOX_NPC
	giveitem ITEM_QUICK_BALL 2
	removeobject 8
	setflag FLAG_ITEM_ROUTE_116_REPEL
	end
OhDosVelozBall:
	.string "¡OH! ¡Genial, dos Veloz\n"
	.string "Ball! ¡Es fantástico!$"
Route116_EventScript_Karen:: @ 81F2F93
	trainerbattle_single TRAINER_KAREN_1, Route116_Text_KarenIntro, Route116_Text_KarenDefeat, Route116_EventScript_TryRegisterKarenAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route116_EventScript_RematchKaren
	setvar VAR_0x8004, TRAINER_KAREN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_TryRegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterKarenAfterBattle:: @ 81F2FD4
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKarenAfterBattle
	release
	end

Route116_EventScript_RegisterKarenAfterBattle:: @ 81F2FDF
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_KarenRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_TryRegisterKaren:: @ 81F2FFE
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterKaren:: @ 81F3011
	msgbox Route116_Text_KarenRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_RematchKaren:: @ 81F302A
	trainerbattle_rematch TRAINER_KAREN_1, Route116_Text_KarenRematchIntro, Route116_Text_KarenRematchDefeat
	msgbox Route116_Text_KarenPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Sarah:: @ 81F3041
	trainerbattle_single TRAINER_SARAH, Route116_Text_SarahIntro, Route116_Text_SarahDefeat
	msgbox Route116_Text_SarahPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Dawson:: @ 81F3058
	trainerbattle_single TRAINER_DAWSON, Route116_Text_DawsonIntro, Route116_Text_DawsonDefeat
	msgbox Route116_Text_DawsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Devan:: @ 81F306F
	trainerbattle_single TRAINER_DEVAN, Route116_Text_DevanIntro, Route116_Text_DevanDefeat
	msgbox Route116_Text_DevanPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Johnson:: @ 81F3086
	trainerbattle_single TRAINER_JOHNSON, Route116_Text_JohnsonIntro, Route116_Text_JohnsonDefeat
	msgbox Route116_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_Text_ScoundrelMadeOffWithPeeko: @ 81F309D
	.string "Ahh… ¿Y ahora qué voy a hacer?\p"
	.string "Estaba aquí, jugando con Peeko…\n"
	.string "¡Y alguien se lo llevó a la cueva…!\p"
	.string "¡NOOOOOOOOOOOoOoOoOooooOOoo! ¡PEEKO!$"

Route116_Text_WantToDigTunnel: @ 81F3140
	.string "¡Nnn… Roar!\p"
	.string "¡YA QUIERO CAVAR ESE TÚNEL!$"

Route116_Text_DiggingTunnelWhenGoonOrderedMeOut: @ 81F3166
	.string "¡Nnn… Roar!\n"
	.string "¿Qué pasa?\p"
	.string "¡Estaba cavando ese túnel sin ninguna\n"
	.string "herramienta cuando alguien me !\p"
	.string "Dijeron que la cueva está llena de Pokémon\n"
	.string "que reaccionan con los ruidos…\l"
	.string "Incluso podrían armar un Alboroto…$"

Route116_Text_GoonHightailedItOutOfTunnel: @ 81F32C1
	.string "¡Nnn… Roar!\p"
	.string "¡Ese idiota me lo impide!\n"
	.string "¡No puedo seguir cavando!$"

Route116_Text_ThankYouTokenOfAppreciation: @ 81F3317
	.string "¡Ah, eres tú!\p"
	.string "Eres la persona que me ayudó en el\n"
	.string "bosque… ¡Y ahora recuperas mi paquete\l"
	.string "robado! ¡Eres un alma caritativa!\l"
	.string "Tengo que agradecértelo de alguna\n"
	.string "forma…\p"
	.string "¡Ya sé, toma esta nueva Poké Ball\n"
	.string "en la que he estado trabajando!$"

Route116_Text_NewBallAvailableAtMart: @ 81F3521
	.string "Nuestra nueva Ball estará disponible\n"
	.string "en la Tienda Pokémon de Rustboro.$"

Route116_Text_BagIsJamPacked: @ 81F3593
	.string "Your BAG is jam-packed.\n"
	.string "I can't give you this REPEAT BALL.$"

Route116_Text_TokenOfAppreciation: @ 81F35CE
	.string "¡Gracias, en serio! ¡Toma esta Ball!$"

Route116_Text_CanYouHelpMeFindGlasses: @ 81F3657
	.string "Se me cayeron las gafas…\n"
	.string "{PLAYER}: Emhh… No, las tienes puestas…\l"
	.string "¡ESAS NO! ¡Las oscuras!$"

Route116_Text_MayISeeThoseGlasses: @ 81F3688
	.string "¡Esas gafas!\n"
	.string "¿Me dejas verlas?$"

Route116_Text_NotWhatImLookingForMaybeTheyArentHere: @ 81F36B4
	.string "Hmm…\n"
	.string "¡SON LAS QUE BUSCO! ¡ACEPTA ESTO COMO RECOMPENSA!$"

Route116_Text_CantFindGlassesNotHere: @ 81F3718
	.string "Hmm…\n"
	.string "Quizá haya más…$"

Route116_Text_NotWhatImLookingFor: @ 81F375E
	.string "Hmm…\n"
	.string "No te daré más regalos…$"

Route116_Text_RouteSignRustboro: @ 81F379D
	.string "ROUTE 116\n"
	.string "{LEFT_ARROW} RUSTBORO CITY$"

Route116_Text_RusturfTunnelSign: @ 81F37B7
	.string "TÚNEL RUSTURF\n"
	.string "“Cancelado.”$"

Route116_Text_TunnelersRestHouse: @ 81F380F
	.string "TUNNELER'S REST HOUSE$"

Route116_Text_TrainerTipsBToStopEvolution: @ 81F3825
	.string "¡TRAINER TIPS!\p"
	.string "El nuevo PC Portátil no\n"
	.string "tiene señal en cuevas…$"

Route116_Text_TrainerTipsBagHasPockets: @ 81F38D4
	.string "¡TRAINER TIPS!\p"
	.string "¡Recuerda ser precavido!\p"
	.string "Lleva siempre muchas Ball, en caso\n"
	.string "de encontrar un Pokémon fuerte, pero\l"
	.string "también lleva muchas Bayas…$"

