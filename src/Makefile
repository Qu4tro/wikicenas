CC = gcc
CFLAGS = -Wall -std=c11 -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -g `pkg-config --cflags glib libxml-2.0` -D_GNU_SOURCE
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

OUT = program

all: 
	@echo "Invocação é:"
	@echo "\tmake program"
	@echo "\tmake run"
	@echo "\tmake clean"

program: parser.o interface.o structs.o tst.o
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUT) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(LIBS) $< -o $@

clean:
	rm -f $(OUT) $(OBJECTS)


#CC = gcc
#CFLAGS = = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
# LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

# OUT = program


# program: structs.o program.o
# 	$(CC) $(CFLAGS) -o program structs.o program.o  $(LIBS)


# structs.o: parser.o
# 	$(CC) $(CFLAGS) -c structs.c

# parser.o:
# 	$(CC) $(CFLAGS) -c parser.c
# program.o:
# 	$(CC) $(CFLAGS) -c program.c

# clean:
# 	rm *.o program 
