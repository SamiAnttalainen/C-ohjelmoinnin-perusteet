# Makefile HTTavoitetaso.c
# Tekijä: Sami Anttalainen
# Opiskelijanumero: 001067291
# Päivämäärä: 8.3.2023
HTTavoitetaso.c: HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o
	gcc HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o -o HT

HTTavoitetaso.o: HTTavoitetaso.c HTPerusKirjasto.h
	gcc HTTavoitetaso.c -c -std=c99 -pedantic -Wall -g

HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc HTPerusKirjasto.c -c -std=c99 -pedantic -Wall -g

HTTavoiteKirjasto.o: HTTavoiteKirjasto.c HTPerusKirjasto.h
	gcc HTTavoiteKirjasto.c -c -std=c99 -pedantic -Wall -g