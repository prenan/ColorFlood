APPLI = colorflood
CSRC = grille.c fichier.c pile.c main.c coordonnees.c
CC = gcc

CFLAGS = -Wall -Wextra
COBJ = $(CSRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ)


test:
	$(CC) $(CFLAGS) grille.c coordonnees.c fichier.c pile.c tests_unitaires.c -o test -lcunit

valgrind:
	valgrind --leak-check=yes ./colorflood

doxygen:
	doxygen Doxyfile

clean:
	-rm *.o colorflood test