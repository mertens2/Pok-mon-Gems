OldaleTown_Mart_MapScripts:: @ 81FC23F
	.byte 0

OldaleTown_Mart_EventScript_Clerk:: @ 81FC240
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_Pokemart_Basic: @ 81FC260
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_ExpandedItems:: @ 81FC26C
	pokemart OldaleTown_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Expanded: @ 81FC27C
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_RING_TARGET
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_EventScript_Woman:: @ 81FC28A
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock:: @ 81FC29F
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy:: @ 81FC2A9
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut: @ 81FC2B2
	.string "Ya se han vendido todas las Pokéball...$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls: @ 81FC2F3
	.string "¡AHORA QUE HAY, COMPRARÉ\n"
	.string "MUCHAS POKÉBALL!$"

OldaleTown_Mart_Text_RestoreHPWithPotion: @ 81FC338
	.string "Hay Objetos con usos curiosos.\p"
	.string "El Blanco, por ejemplo, elimina las\n"
	.string "inmunidades de tipo. Hay movimientos\l"
	.string "curiosos también, como Truco.\p"
	.string "Mhh... Truco intercambia los objetos.\n"
	.string "¡Sería buena idea para enfrentar\l"
	.string "Pokémon con muchas inmunidades!$"

