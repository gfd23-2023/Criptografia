CC = gcc
CFLAGS = -Wall -g
MAIN = cifra
MAIN2 = decifra
TEMPO = -lrt

#Compila tudo
all: $(MAIN) $(MAIN2)

#Programa Principal - CIFRA
$(MAIN): $(MAIN).o playfair.o rail_fence.o tempo.o aes.o
	$(CC) -o $(MAIN) $(MAIN).o playfair.o rail_fence.o tempo.o aes.o $(CFLAGS) $(TEMPO)

$(MAIN).o: $(MAIN).c playfair.h rail_fence.h tempo.h aes.h
	$(CC) $(CFLAGS) -c $(MAIN).c $(TEMPO)

#Programa Principal - DECIFRA
$(MAIN2): $(MAIN2).o playfair.o rail_fence.o tempo.o aes.o
	$(CC) -o $(MAIN2) $(MAIN2).o playfair.o rail_fence.o tempo.o aes.o $(CFLAGS) $(TEMPO)

$(MAIN2).o: $(MAIN2).c playfair.h rail_fence.h tempo.h aes.h
	$(CC) $(CFLAGS) -c $(MAIN2).c $(TEMPO)

#Playfair
playfair.o: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c

#Rail Fence
rail_fence.o: rail_fence.c rail_fence.h
	$(CC) $(CFLAGS) -c rail_fence.c

#Tempo
tempo.o: tempo.c tempo.h
	$(CC) $(CFLAGS) -c tempo.c $(TEMPO)

#AES
aes.o: aes.o aes.h
	$(CC) $(CFLAGS) -c aes.c

#Debug
debug: CFLAGS += -O0 -DDEBUG
debug clean: $(MAIN) $(MAIN2)

clean:
	rm -f *.o *~ $(MAIN) $(MAIN2)
	find . -name "*.sw*" -delete