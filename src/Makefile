CC = gcc
CFLAGS = -Wall -std=c11 -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

OUT = program

all: 
	@echo "Invocação é:"
	@echo "\tmake program"
	@echo "\tmake run"
	@echo "\tmake clean"

program: parser.o
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUT) $(LIBS)

%.o: %.c
	$(CC) -c $(CC_FLAGS) $(XML) $< -o $@

clean:
	rm -f $(OUT) $(OBJECTS)
