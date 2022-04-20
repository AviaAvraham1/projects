AsciiArtTool: RLEList.o main.o AsciiArt.o
	gcc RLEList.o main.o AsciiArt.o -o AsciiArtTool

RLEList.o: RLEList.c RLEList.h
	gcc -c RLEList.c

AsciiArt.o: AsciiArt.c AsciiArt.h RLEList.h
	gcc -c AsciiArt.c

#RLEList.h?????
main.o: main.c AsciiArt.h
	gcc -c main.c

clean:
	rm -f RLEList.o main.o AsciiArt.o AsciiArtTool