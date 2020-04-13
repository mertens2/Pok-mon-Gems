EventScript_UseSurf:: @ 8271EA0
	goto_if_unset FLAG_BADGE05_GET, EventScript_CantSurf
	checkMonType TYPE_WATER
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_CantSurf
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox WantToUseSurf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_ReleaseUseSurf
	msgbox PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf:: @ 8271ED5
	releaseall
	end
EventScript_CantSurf::
	msgbox CantSurf, MSGBOX_DEFAULT
	releaseall
	end
PlayerUsedSurf:
	.string "¡{PLAYER} se monta\n"
	.string "en {STR_VAR_1}!$"
WantToUseSurf:
	.string "El agua se ve hermosa.\n"
	.string "¿Quieres Surfear?$"
CantSurf::
	.string "El agua se ve hermosa.$"
EventScript_EndUseSurf:: @ 8271ED6
	end
