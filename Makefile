CC=g++				#compiler
SRC=main.cpp		#source
OUT=Output/out.exe	#output

all:
	$(CC) -Isrc/Include -Lsrc/lib -o $(OUT) $(SRC) -lmingw32 -lSDL2main -lSDL2 -mwindows -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic