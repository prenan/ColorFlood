#ifndef GRILLE_H
#define GRILLE_H

typedef char ** grille;

grille initialize(int size);
void display(grille plateau, int size);
grille random(int size);

#endif