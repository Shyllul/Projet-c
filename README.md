# BigBinary - Bibliothèque d'Arithmétique Binaire en C

Une bibliothèque C permettant de manipuler de grands nombres en représentation binaire et d'effectuer des opérations arithmétiques sur ceux-ci.

## Fonctionnalités

- **Conversion** : Décimal ↔ Binaire
- **Opérations de base** : Addition, Soustraction, Multiplication
- **Comparaisons** : Égalité, Infériorité
- **Opérations avancées** : PGCD, Modulo, Exponentiation modulaire

## Structure du Projet

```
├── bigbinary.h    # Déclarations des types et fonctions
├── bigbinary.c    # Implémentation de la bibliothèque
├── main.c         # Programme de test interactif
└── project.exe    # Exécutable compilé
```

## Compilation

```bash
gcc -o project.exe main.c bigbinary.c
```

## Utilisation

```bash
./project.exe
```

Le programme propose des tests interactifs pour :
1. Addition
2. Soustraction
3. Comparaisons
4. PGCD
5. Modulo
6. Multiplication
7. Exponentiation modulaire

## Exemple

```
--- TEST ADDITION ---
Entrez le premier nombre (A): 10
Entrez le deuxieme nombre (B): 5
A = 10 = 1010
B = 5  = 101
A + B  = 1111 (15)
```

## Fonctions

| Fonction | Description |
|----------|-------------|
| `createBigBinary(size)` | Crée un BigBinary vide de taille donnée |
| `afficheBigBinary(nb)` | Affiche le nombre en binaire |
| `creerBigBinaryDepuisDecimal(n)` | Crée un BigBinary depuis un entier |
| `creerBigBinaryDepuisChaine(chaine)` | Crée un BigBinary depuis une chaine de caractères |
| `bigBinaryVersDecimal(nb)` | Convertit en décimal |
| `additionBigBinary(A, B)` | Additionne A + B |
| `soustractionBigBinary(A, B)` | Soustrait A - B |
| `BigBinary_mult(A, B)` | Multiplie A × B |
| `BigBinary_mod(A, B)` | Calcule A mod B |
| `BigBinary_PGCD(A, B)` | Calcule le PGCD |
| `BigBinary_expMod(M, exp, mod)` | Calcule M^exp mod mod |
| `Egal(A, B)` | Teste l'égalité |
| `Inferieur(A, B)` | Teste si A < B |
| `libereBigBinary(&nb)` | Libère la mémoire |
