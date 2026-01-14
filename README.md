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
1. Additionclear
2. Soustraction
3. Comparaisons
4. PGCD
5. Modulo
6. Multiplication
7. Exponentiation modulaire


## Fonctions

| Fonction | Description |
|----------|-------------|
| `createBigBinary(size)` | Crée un BigBinary vide de taille donnée | 
| `libereBigBinary(&nb)` | Libère la mémoire |
| `afficheBigBinary(nb)` | Affiche le nombre en binaire |
| `creerBigBinaryDepuisChaine(chaine)` | Crée un BigBinary depuis une chaine binaire |
| `additionBigBinary(A, B)` | Additionne A + B |
| `soustractionBigBinary(A, B)` | Soustrait A - B |
| `Egal(A, B)` | Teste l'égalité |
| `Inferieur(A, B)` | Teste si A < B |
| `BigBinary_PGCD(A, B)` | Calcule le PGCD |
| `BigBinary_mod(A, B)` | Calcule A mod B |
| `BigBinary_mult(A, B)` | Multiplie A × B |
| `BigBinary_expMod(M, exp, mod)` | Calcule M^exp mod mod |
