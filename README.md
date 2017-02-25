# Color Flood (IPI2 - THOR)

## Instructions d'installation (pré-requis)

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
* pour compiler et exécuter

```
make
./colorflood
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


## Équipe THOR


* **ESTEOULLE Thomas** *(TPS)*
* **FAIQ Othman** *(ENSIIE)*
* **LIU Hao** *(ENSIIE)*
* **PINCEMIN Renan** *(TPS)*
