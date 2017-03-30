APPLI = colorflood
CSRC = grille.c fichier.c pile.c coordonnees.c
CC = gcc

CFLAGS = -Wall -Wextra -g -std=c99
LFLAGS = -lm -lSDL -lSDL_ttf
COBJ = $(CSRC:.c=.o)

DIST_FILES =  grille.h fichier.h pile.h coordonnees.h SDL.h n_arbres.h\
		      grille.c fichier.c pile.c coordonnees.c SDL.c n_arbres.c\
			  fichier_grille.txt fichier_grille_2.txt\
			  liberation.ttf tests_unitaires.c\
			  ourteam.bmp\
			  plateau.txt\
			  Doxyfile\
			  README.md\
			  main_console.c\
			  main.c\
			  Makefile

DIR := $(shell basename `pwd`)
DISTNAME := $(DIR)_THOR.tar.gz


all : colorflood console

main.o: fichier.h grille.h pile.h coordonnees.h SDL.h n_tree.h main.c
	$(CC) -c $(CFLAGS) main.c $(LFLAGS)

SDL.o : SDL.h SDL.c
	$(CC) -c $(CFLAGS) SDL.c

n_ltree.o : grille.h n_tree.h n_tree.c
	$(CC) -c $(CFLAGS) n_ltree.c

main_console.o: fichier.h grille.h pile.h coordonnees.h main_console.c
	$(CC) -c $(CFLAGS) main_console.c

colorflood:$(COBJ) main.o SDL.o n_ltree.o
		@echo "Building $@"
		$(CC) -o $@ $(COBJ) SDL.o main.o n_ltree.o $(LFLAGS) 

console:$(COBJ) main_console.o
		@echo "Building $@"
		$(CC) -o $@ $(COBJ) main_console.o -lm 

test:
	$(CC) $(CFLAGS) grille.c fichier.c pile.c coordonnees.c tests_unitaires.c -o test -lcunit -g -lm

valgrind:
	valgrind --leak-check=yes ./colorflood

doxygen:
	doxygen Doxyfile

clean:
	@rm -f $(TARGETS) *.o *~ colorflood console test

dist: $(DIST_FILES)
	@echo "* creating $(DIR)"
	@rm -rf $(DIR)
	@mkdir "$(DIR)"
	@cp $(DIST_FILES) $(DIR)
	@tar cvfz $(DISTNAME) $(DIR)
	@rm -rf $(DIR)
	@echo "* -> $(DISTNAME) built."