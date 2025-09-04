CC = gcc
CFLAGS = -Wall -g
MAIN = cifra
MAIN2 = decifra

#Programa Principal - CIFRA
$(MAIN): $(MAIN).o playfair.o
	$(CC) -o $(MAIN) $(MAIN).o playfair.o $(CFLAGS)

$(MAIN).o: $(MAIN).c playfair.h
	$(CC) $(CFLAGS) -c $(MAIN).c

#Programa Principal - DECIFRA
$(MAIN2): $(MAIN2).o playfair.o
	$(CC) -o $(MAIN2) $(MAIN2).o playfair.o $(CFLAGS)

$(MAIN2).o: $(MAIN2).c playfair.h
	$(CC) $(CFLAGS) -c $(MAIN2).c

#Playfair
playfair.o: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c

#Debug
debug: CFLAGS += -O0 -DDEBUG
debug clean: $(MAIN) $(MAIN2)

clean:
	rm -f *.o *~ $(MAIN) $(MAIN2)
	find . -name "*.sw*" -delete