APPLI = colorflood
CSRC = grille.c fichier.c pile.c coordonnees.c main.c
CC = gcc

CFLAGS = -Wall -Wextra -g -lSDL
COBJ = $(CSRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ) -lm


test:
	$(CC) $(CFLAGS) grille.c fichier.c pile.c coordonnees.c tests_unitaires.c -o test -lcunit -g -lm

valgrind:
	valgrind --leak-check=yes ./colorflood

doxygen:
	doxygen Doxyfile

clean:
	-rm *.o colorflood test