CC = g++
LDFLAGS = -lncurses -lm
CFLAGS = -Wall -Ofast
EXEC = ascii-ray-marching

default:
	$(CC) $(CFLAGS) -o $(EXEC) main.cpp $(LDFLAGS)


clean:
	rm -f $(EXEC)

.PHONY: clean