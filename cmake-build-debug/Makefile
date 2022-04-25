#this is the old MakeFile
CC = gcc
OBJS = main.o RLEList.o AsciiArt.o
EXEC = AsciiArt
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG =-std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

AsciiArt.o: AsciiArt.c AsciiArt.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

#RLEList.h?????
main.o: main.c AsciiArt.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)



#more recent
CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG = -std=c99 -Wall -Werror -I.

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $(EXEC)

RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $<
AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $<
main.o: tool/main.c tool/AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $<

clean:
	rm -f $(OBJS) $(EXEC)