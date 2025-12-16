CFLAGS = -Wall -Wextra -O2 -I "C:\Users\harry\SDL\x86_64-w64-mingw32\include" 
LDFLAGS =  -L"C:\Users\harry\SDL\x86_64-w64-mingw32\lib" -lSDL3 

all: final

final: main.o algorithms.o sdlHelpers.o
	gcc $(CFLAGS) main.o algorithms.o sdlHelpers.o -o sorting_vis.exe $(LDFLAGS)

main.o: src/main.c headers/sdlHelpers.h headers/algorithms.h headers/constants.h
	gcc $(CFLAGS) -c src/main.c -o main.o

algorithms.o: src/algorithms.c headers/algorithms.h headers/sdlHelpers.h
	gcc $(CFLAGS) -c src/algorithms.c -o algorithms.o

sdlHelpers.o: src/sdlHelpers.c headers/sdlHelpers.h headers/constants.h
	gcc $(CFLAGS) -c src/sdlHelpers.c -o sdlHelpers.o

clean:
	rm -f main.o algorithms.o sdlHelpers.o sorting_vis.exe

.PHONY: all clean

