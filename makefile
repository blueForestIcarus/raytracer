SOURCE = src/main.cpp
EXE = raygun.latest

CC = g++
CFLAGS = -w
LFLAGS = -lSDL2 -lSDL2_gfx


#This is the target that compiles our executable
all : $(SOURCE)
	$(CC) $(SOURCE) $(CFLAGS) $(LFLAGS) -o $(EXE)
