#Tema1 SO,Bucur Ionut-Cristian,333CA
CFLAGS = /W3 /nologo -D_CRT_SECURE_NO_DEPRECATE

build: tema1.exe

tema1.exe: tema1.obj utils.obj commands.obj hashtable.obj
	link /nologo /out:tema1.exe tema1.obj utils.obj commands.obj hashtable.obj hash.lib

tema1.obj: tema1.c
	cl $(CFLAGS) /Fotema1.obj /c tema1.c
	
utils.obj: utils.c
	cl $(CFLAGS) /Foutils.obj /c utils.c
	
hashtable.obj: hashtable.c
	cl $(CFLAGS) /Fohashtable.obj /c hashtable.c
	
commands.obj: commands.c
	cl $(CFLAGS) /Focommands.obj /c commands.c

hash.lib: hash.dll
	/nologo /dll /out:hash.dll /implib:hash.lib
	
clean:
	del *.obj *.exe