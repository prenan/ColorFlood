# Color Flood (IPI2 - THOR)

## Instructions d'installation (pré-requis)

Pour décompresser l'archive dans un terminal :
```
unzip ColorFlood_THOR.zip 
```
Pour installer la bibliothèque SDL dans un terminal :
```
sudo apt-get install libsdl1.2-dev
```
Pour installer la bibliothèque SDL_ttf dans un terminal :
```
sudo apt-get install libsdl-ttf2.0-dev
```
Pour installer la bibliothèque FreeType dans un terminal :
```
sudo apt-get install libfreetype6-dev
```
Pour la documentation avec Doxygen :
```
sudo apt install doxygen
```
Pour les tests unitaires avec CUnit :
```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```


## Instructions d'utilisation

Dans un terminal,
* pour compiler

```
make
./colorflood     exécuter (avec interface graphique SDL)
./console        exécuter (mode console)

```
* pour tester l'absence de fuites de mémoire (Valgrind)

```
make valgrind
```
* pour les tests unitaires

```
make test
./test
```
* pour générer la documentation (Doxygen)

```
make doxygen
ouvrir html/index.html
```

* pour nettoyer le répertoire
```
make clean
```

* pour compacter les fichiers
```
make dist
```

## Équipe THOR


* **ESTEOULLE Thomas** *(TPS)*
* **FAIQ Othman** *(ENSIIE)*
* **LIU Hao** *(ENSIIE)*
* **PINCEMIN Renan** *(TPS)*
