Std_MsgboxNPC: @ 8271315
	lock
	faceplayer
	setmessagebox 0x1 0x2
	message 0x0
	waitmessage
	waitbuttonpress
	release
	return

Std_MsgboxSign: @ 8271320
	lockall
	setmessagebox 0x1 0x2
	message 0x0
	waitmessage
	waitbuttonpress
	releaseall
	return

Std_MsgboxDefault: @ 827132A
	setmessagebox 0x1 0x2
	message 0x0
	waitmessage
	waitbuttonpress
	return

Std_MsgboxYesNo: @ 8271332
	setmessagebox 0x1 0x2
	message 0x0
	waitmessage
	yesnobox 20, 8
	return

Std_MsgboxGetPoints: @ 827133C
	setmessagebox 0x1 0x2
	message 0x0
	playfanfare MUS_ME_POINTGET
	waitfanfare
	waitmessage
	return

Std_10: @ 8271347
	setmessagebox 0x1 0x2
	pokenavcall 0x0
	waitmessage
	return

EventScript_UnusedReturn: @ 827134E
	return

Common_EventScript_SaveGame:: @ 827134F
	special SaveGame
	waitstate
	return
