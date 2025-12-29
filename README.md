# Projet BigBinary

## Introduction

Bibliothèque C pour la manipulation de "grands entiers" en binaire, développée dans le cadre du cursus d'ingénieur ESIEA (3A S5).

## Organisation du Projet

```
PROJET_C/
├── bigbinary.h     - Déclarations (structures et prototypes)
├── bigbinary.c     - Implémentation des fonctions
├── main.c          - Programme de test
└── README.md       - Ce fichier
```

## Compilation et Exécution

```bash
# Compiler
gcc main.c bigbinary.c -o project.exe

# Exécuter
./project.exe
```

## Structure BigBinary

```c
#define BASE 2

typedef struct {
    int *Tdigits;   // Tableau de bits : Tdigits[0] = MSB, Tdigits[Taille-1] = LSB
    int Taille;     // Nombre de bits significatifs
    int Signe;      // +1 (positif), -1 (négatif), 0 (nul)
} BigBinary;
```

## Fonctionnalités Implémentées

### Fonctions de Base (Phase 1)

| Fonction | Description |
|----------|-------------|
| `createBigBinary(size)` | Crée un BigBinary vide |
| `libereBigBinary(nb)` | Libère la mémoire |
| `afficheBigBinary(nb)` | Affiche le nombre binaire |
| `creerBigBinaryDepuisChaine(chaine)` | Crée depuis "101010..." |

### Opérations Arithmétiques (Phase 1)

| Fonction | Description |
|----------|-------------|
| `additionBigBinary(A, B)` | A + B (A, B positifs ou nuls) |
| `soustractionBigBinary(A, B)` | A - B (A >= B) |

### Comparaisons (Phase 1)

| Fonction | Description |
|----------|-------------|
| `Egal(A, B)` | Renvoit true si A == B, sinon false |
| `Inferieur(A, B)` | Renvoit true si A < B, sinon false |

### Fonctions Avancées (Phase 2)

| Fonction | Description |
|----------|-------------|
| `BigBinary_PGCD(A, B)` | PGCD avec algorithme binaire d'Euclide |
| `BigBinary_mod(A, B)` | A mod B (algorithme sans division) |
| `BigBinary_mult(A, B)` | Multiplication Égyptienne |
| `BigBinary_expMod(M, exp, mod)` | Exponentiation modulaire rapide (exp: unsigned int) |

## Phases du Projet

### Phase 1 - Fonctionnalités de base
- [x] Structure BigBinary (avec Tdigits, Taille, Signe)
- [x] Fonction createBigBinary
- [x] Fonction afficheBigBinary
- [x] Fonction libereBigBinary
- [x] Fonction creerBigBinaryDepuisChaine
- [x] Addition (algorithme naïf)
- [x] Soustraction (A >= B)
- [x] Egal(A, B) et Inferieur(A, B)

### Phase 2 - Fonctionnalités avancées
- [x] BigBinary_PGCD(A, B) : Algorithme binaire d'Euclide
- [x] BigBinary_mod(A, B) : Modulo sans division
- [x] BigBinary_mult(A, B) : Multiplication Égyptienne
- [x] BigBinary_expMod(M, exp, mod) : Exponentiation modulaire rapide

## Remarques

- **Addition/Soustraction** : Algorithme "naïf" (méthode de l'école primaire)
- **PGCD** : Algorithme binaire d'Euclide (sans division)
- **Modulo** : Algorithme sans division (soustraction successive)
- **Multiplication** : Multiplication Égyptienne (additions et décalages)
- **Exponentiation** : Exposant limité à unsigned int (64 bits max)
