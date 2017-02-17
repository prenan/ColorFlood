APPLI=colorflood
CSRC= grille.c main.c fichier.c pile.c 
CC = gcc

CFLAGS = -Wall -Wextra -ansi -I. 

COBJ=$(CSRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

$(APPLI):	$(COBJ)
	$(CC) -o $(APPLI) $(COBJ)

clean:
	-rm *.o colorflood
