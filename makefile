all: ortografia.c dicionario.o ortografia


ortografia: ortografia.o dicionario.o
				gcc ortografia.o dicionario.o -o ortografia
ortografia.o: ortografia.c dicionario.h
				gcc -c ortografia.c -Wall
dicionario.o: dicionario.c dicionario.h
				gcc -c dicionario.c -Wall
				
clean: 
				-rm -f *.o 
purge: clean
				-rm -f ortografia 