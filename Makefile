SRC := src/
INCLUDES := src/
CFLAGS := -lm -g 

all:
	gcc main.c $(wildcard $(SRC)*.c) -I $(INCLUDES) -o app $(CFLAGS)

run:
	./app

debug:
	gdb app

clean:
	rm app
