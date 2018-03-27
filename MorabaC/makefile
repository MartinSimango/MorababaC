all: MorabaClient MorabaServer

MorabaClient: client.c MorabaC.c stdafx.c board.c mills.c gameStructure.c coordsList.c game.c
	cc -o build/MorabaClient client.c MorabaC.c stdafx.c board.c mills.c gameStructure.c coordsList.c game.c

MorabaServer:server.c MorabaC.c stdafx.c board.c mills.c gameStructure.c coordsList.c game.c
	cc -o build/MorabaServer server.c MorabaC.c stdafx.c board.c mills.c gameStructure.c coordsList.c game.c

