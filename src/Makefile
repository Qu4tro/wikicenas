CC = gcc
CFLAGS = -Wall -std=c11 -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -g `pkg-config --cflags glib-2.0 libxml-2.0` -D_GNU_SOURCE
LIBS = `pkg-config --libs libxml-2.0 glib-2.0`

DATASETS = $(wildcard datasets/*)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

OUT = program

all: parser.o interface.o structs.o tst.o pqueue.o topN.o
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUT) $(LIBS)

run: $(OUT)
	./$(OUT) $(DATASETS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(LIBS) $< -o $@

clean:
	rm -f $(OUT) $(OBJECTS)
