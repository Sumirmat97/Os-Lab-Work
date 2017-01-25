# Dependencies are: main.c myFile.c

CC := gcc
CFLAGS := -fopenmp -Wall
SOURCES := main.c myFile.c -lm
OUT_FILE := a.out

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUT_FILE) $(SOURCES)

clean:
	rm -f $(OUT_FILE)

rebuild: clean build

all: build

