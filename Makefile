APPLI = colorflood
CSRC = grille.c fichier.c pile.c coordonnees.c SDL.c main.c
CC = gcc

CFLAGS = -Wall -Wextra -g -std=c99
LFLAGS = -lm -lSDL -lSDL_ttf
COBJ = $(CSRC:.c=.o)

DIST_FILES = grille.h fichier.h pile.h coordonnees.h SDL.h n_arbres.h\
		      grille.c\
			  fichier.c\
			  pile.c\
			  coordonnees.c\
			  SDL.c\
			  n_arbres.c\
			  liberation.ttf\
			  tests_unitaires.c\
			  main_console.c\
			  main.c\
			  fichier_grille.txt\
			  fichier_grille_2.txt\
			  plateau.txt\
			  README.md\
			  ourteam.bmp\
			  Makefile

DIR := $(shell basename `pwd`)
DISTNAME := $(DIR)_THOR.tar.gz

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	@echo "Building $@"
	$(CC) -o $(APPLI) $(COBJ) $(LFLAGS)

console:
	@echo "Building $@"
	$(CC) grille.c fichier.c pile.c coordonnees.c main_console.c -o console -lm

test:
	$(CC) $(CFLAGS) grille.c fichier.c pile.c coordonnees.c tests_unitaires.c -o test -lcunit -g -lm

valgrind:
	valgrind --leak-check=yes ./colorflood

doxygen:
	doxygen Doxyfile

clean:
	@rm -f $(TARGETS) *.o *~

dist: $(DIST_FILES)
	@echo "* creating $(DIR)"
	@rm -rf $(DIR)
	@mkdir "$(DIR)"
	@cp $(DIST_FILES) $(DIR)
	@tar cvfz $(DISTNAME) $(DIR)
	@rm -rf $(DIR)
	@echo "* -> $(DISTNAME) built."