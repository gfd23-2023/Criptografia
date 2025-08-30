CC = gcc
CFLAGS = -Wall -g
MAIN = main

#Programa Principal
$(MAIN): $(MAIN).o playfair.o
	$(CC) -o $(MAIN) $(MAIN).o playfair.o $(CFLAGS)

$(MAIN).o: $(MAIN).c playfair.h
	$(CC) $(CFLAGS) -c $(MAIN).c

#Playfair
playfair.o: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c

#Debug
debug: CFLAGS += -O0 -DDEBUG
debug clean: $(MAIN)

clean:
	rm -f *.o*~ $(MAIN)
	find . -name "*.sw*" -delete