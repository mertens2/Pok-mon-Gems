OldaleTown_House2_MapScripts:: @ 81FBF5A
	.byte 0

OldaleTown_House2_EventScript_Woman:: @ 81FBF5B
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end
OldaleTown_House2_EventScript_NoEspacio::
	msgbox OldaleTown_House2_Text_DejaTodo, MSGBOX_NPC
	end
OldaleTown_House2_EventScript_Man:: @ 81FBF64
	checkitem ITEM_EXP_SHARE, 1
	compare VAR_RESULT, 1
	goto_if_eq	OldaleTown_House2_EventScript_No
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	checkitemspace ITEM_EXP_SHARE, 1
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_House2_EventScript_NoEspacio
	giveitem ITEM_EXP_SHARE, 1
	msgbox OldaleTown_House2_Text_EXP, MSGBOX_NPC
	end
OldaleTown_House2_EventScript_No::
	msgbox OldaleTown_House2_Text_YATIENES, MSGBOX_NPC
	closemessage
	end
OldaleTown_House2_Text_YATIENES:
	.string "¡SI YA TIENES UN REPARTIR\n"
	.string "EXP.! ¡NO NECESITAS ESTE!$"
OldaleTown_House2_Text_DejaTodo:
	.string "¡!\p"
	.string "¡DEJA TODO LO QUE NO NECESITES\n"
	.string "Y VEN A BUSCAR ESTE OBJETO,\l"
	.string "ES IMPORTANTÍSIMO!$"
OldaleTown_House2_Text_PokemonLevelUp: @ 81FBF6D
	.string "Cuando un Pokémon obtiene EXP,\n"
	.string "eventualmente sube de nivel.$"
OldaleTown_House2_Text_EXP:
	.string "El Repartir Xp. es un Objeto\n"
	.string "indispensable para cualquiera.\p"
	.string "Equípaselo a un Pokémon, y ganará XP.\n"
	.string "sin haber peleado. Sirve para entrenar\l"
	.string "a los nuevos integrantes del Equipo.$"
OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon: @ 81FBFB0
	.string "Como todos son diferentes, seguro que\n"
	.string "uno de tus Pokémon se quedará atrás\l"
	.string "si no combate, si es débil o nuevo.\p"
	.string "Esto debería evitar que eso pase…$"

