CasaBraggMcFadden_MapScripts::
	.byte 0
CasaBraggMcFadden_Gordo::
	lock
	faceplayer
	msgbox CasaBraggMcFadden_GordoTexto, MSGBOX_DEFAULT
	release
	end
CasaBraggMcFadden_Hijo::
	lock
	faceplayer
	msgbox CasaBraggMcFadden_HijoTexto, MSGBOX_DEFAULT
	release
	end
CasaBraggMcFadden_Trigger::
	lock
	faceplayer
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	msgbox CasaBraggMcFadden_NoEntres, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, CasaBraggMcFadden_Abajo
	waitmovement 0
	release
	end
CasaBraggMcFadden_Abajo:
	walk_down
	step_end
CasaBraggMcFadden_Gordo2::
	lock
	faceplayer
	msgbox CasaBraggMcFadden_Gordo2Texto, MSGBOX_DEFAULT
	release
	end
CasaBraggMcFadden_GordoTexto:
    .string "¡Oh, hola!\p"
    .string "¿Tu padre es Norman, verdad?\n"
    .string "Me alegro de que hayas llegado\l"
    .string "en una sola pieza.\p"
    .string "Viajar desde Johto no es algo\n"
    .string "para tomarse a la ligera. Ve a\l"
    .string "caminar y despéjate.\p"
    .string "Oh, y por cierto. ¿No habrás visto\n"
    .string "a otro Gordo como yo\l"
    .string "por ahí afuera, no?\p"
    .string "Lo he estado llamando desde hace un\n"
    .string "buen rato y parece que no\l"
    .string "quisiera venir a comer…$"

CasaBraggMcFadden_HijoTexto:
    .string "Mi papi se la pasa afuera caminando\n"
    .string "como le recomendó el médico.\p"
    .string "Pero parece que a mi papá no le\n"
    .string "hace mucha gracia que se salte las\l"
    .string "horas de la comida…$"

CasaBraggMcFadden_NoEntres:
    .string "¿¡PERO, QUÉ HACES!?\p"
    .string "¡No puedes entrar así a los cuartos\n"
    .string "de las personas!\p"
    .string "Es de mala educación hacerlo,\n"
    .string "así que ni se te ocurra entrar,\l"
    .string "¿Queda claro?$"

CasaBraggMcFadden_Gordo2Texto:
    .string "El médico al final me dijo que me\n"
    .string "relajara y que mientras coma cosas\l"
    .string "saludables, estaré bien.\p"
    .string "Mi esposo es un genio de la cocina,\n"
    .string "así que no tendré que preocuparme\l"
    .string "del sabor de la comida.$"
