APPLI = colorflood
CSRC = grille.c fichier.c SDL.c solveur.c main.c
CC = gcc

CFLAGS = -Wall -Wextra -g
LFLAGS = -lm -lSDL -lSDL_ttf -lSDL_mixer
COBJ = $(CSRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ) $(LFLAGS)

console:
	$(CC) -o $(APPLI) grille.c fichier.c solveur.c main_console.c -o console -lm

test:
	$(CC) $(CFLAGS) grille.c fichier.c tests_unitaires.c -o test -lcunit -g -lm

valgrind:
	valgrind --leak-check=yes ./colorflood

doxygen:
	doxygen Doxyfile

clean:
	-rm *.o -f colorflood test console