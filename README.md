# BigBinary

## Description

Ce projet implémente une structure `BigBinary` qui permet de stocker et manipuler des nombres binaires de taille arbitraire. Les nombres sont représentés comme un tableau de bits (0 ou 1) avec un signe.

## Compilation

```bash
gcc -o project.exe main.c bigbinary.c
```

```bash
./project.exe
```

## Fonctionnalités

### Phase 1

Fonctionnalités de base :
- Création d'un nombre depuis une chaîne binaire
- Affichage d'un nombre (sans les zéros en tête)
- Libération de la mémoire
- Addition de deux nombres
- Soustraction de deux nombres
- Comparaison d'égalité
- Comparaison d'infériorité
- Multiplication (méthode égyptienne)

### Phase 2

Fonctionnalités avancées :
- Calcul du PGCD (algorithme d'Euclide par soustractions)
- Calcul du modulo (division par soustractions avec décalages)
- Exponentiation modulaire (méthode square and multiply)

## Fichiers

- `bigbinary.h` : Déclarations des types et fonctions
- `bigbinary.c` : Implémentation de la bibliothèque
- `main.c` : Programme de test