OldaleTown_House1_MapScripts:: @ 81FBE85
	.byte 0

OldaleTown_House1_EventScript_Woman:: @ 81FBE86
	checkitemspace ITEM_FOCUS_SASH, 2
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_House1_Noespacio
	checkitem ITEM_FOCUS_SASH, 1
	goto_if_eq OldaleTown_House1_EventScript_Woman2
	msgbox OldaleTown_House1_Text_LeftPokemonGoesOutFirst, MSGBOX_NPC
	giveitem ITEM_FOCUS_SASH, 2
	closemessage
	end
OldaleTown_House1_EventScript_Woman2::
	msgbox OldaleTown_House1_Text_NO, MSGBOX_NPC
	closemessage
	end
OldaleTown_House1_Text_NO:
	.string "No te daré más Bandas Focus.$"
OldaleTown_House1_Noespacio::
	msgbox OldaleTown_House1_Text_NoTienesEspacio, MSGBOX_NPC
	end
OldaleTown_House1_Text_NoTienesEspacio:
	.string "Espera. ¡A ESA MOCHILA NO LE ENTRA\n"
	.string "NI EL AIRE! Mejor vende algún\l"
	.string "objeto inútil y vuelve aquí.$"
OldaleTown_House1_Text_LeftPokemonGoesOutFirst: @ 81FBE8F
	.string "Hay veces en las que es mejor\n"
	.string "sacrificar un Pokémon para curar.\p"
	.string "Pero mejor siempre tén una estrategia\n"
	.string "real. Por eso, quiero que tengas\l"
	.string "esto. Dáselo a un Pokémon.\p"
	.string "Podría darte alguna ventaja…$"

