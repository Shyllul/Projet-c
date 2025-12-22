# Projet BigBinary

## Introduction

Bienvenue sur mon Projet en C appelé **BigBinary**, une bibliothèque C développée dans le cadre de mon cursus d'ingénieur à l'ESIEA. Ce projet de programmation vise à développer une (petite) bibliothèque en langage C permettant la manipulation en binaire de "grands entiers" stockés dans des tableaux et tableaux dynamiques pour mieux gérer la mémoire.

## Organisation du Projet

```
PROJET_C/
├── bigbinary.h     - Déclarations (structures et prototypes)
├── bigbinary.c     - Implémentation des fonctions
├── main.c          - Calculatrice interactive
├── project.exe     - Exécutable Windows
├── docs/           - Documents du projet
│   ├── Phase_1.pdf
│   └── Phase_2.pdf
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
    int *Tdigits;   // Tableau de bits (MSB à gauche, LSB à droite)
    int Taille;     // Nombre de bits significatifs
    int Signe;      // +1 (positif), -1 (négatif), 0 (nul)
} BigBinary;
```

### Exemple : Le nombre 83

```
Décimal : 83
Binaire : 1010011

Tdigits = [1, 0, 1, 0, 0, 1, 1]
           ↑                 ↑
          MSB               LSB
Taille = 7
Signe = +1
```

## Fonctionnalités Implémentées

### Fonctions de Base

| Fonction | Description |
|----------|-------------|
| `initBigBinary(taille, signe)` | Initialise un BigBinary vide |
| `libereBigBinary(nb)` | Libère la mémoire |
| `libereMultipleBigBinary(tableau, taille)` | Libère plusieurs BigBinary |
| `afficheBigBinary(nb)` | Affiche le nombre binaire |
| `afficheBigBinaryOctet(nb)` | Affiche en format octet (0000 1100) |
| `creerBigBinaryDepuisChaine(chaine)` | Crée depuis "101010..." |
| `creerBigBinaryDepuisEntier(valeur)` | Crée depuis un entier décimal |
| `bigBinaryVersEntier(nb)` | Convertit en entier décimal |
| `copieBigBinary(A)` | Crée une copie d'un BigBinary |

### Opérations Arithmétiques (Phase 1)

| Fonction | Description | Exemple |
|----------|-------------|---------|
| `additionBigBinary(A, B)` | A + B | 10 + 3 = 13 |
| `soustractionBigBinary(A, B)` | A - B (supporte résultat négatif) | 13 - 15 = -2 |

### Comparaisons (Phase 1)

| Fonction | Description |
|----------|-------------|
| `Egal(A, B)` | Renvoit true si A == B, sinon false |
| `Inferieur(A, B)` | Renvoit true si A < B, sinon false |

### Fonctions Avancées (Phase 2)

| Fonction | Description | Exemple |
|----------|-------------|---------|
| `BigBinary_PGCD(A, B)` | PGCD avec algorithme binaire d'Euclide | PGCD(48, 18) = 6 |
| `BigBinary_mod(A, B)` | A mod B (reste) | 11 mod 3 = 2 |

### Fonctions Utilitaires

| Fonction | Description |
|----------|-------------|
| `estPair(A)` | Vérifie si un BigBinary est pair |
| `decalageDroite(A)` | Division par 2 (décalage binaire) |
| `decalageGauche(A)` | Multiplication par 2 (décalage binaire) |

## Calculatrice Interactive

Le programme `main.c` est une **calculatrice interactive** qui :

1. Demande 2 nombres décimaux à l'utilisateur
2. Affiche les valeurs en binaire (format octet) avec leur équivalent décimal
3. Effectue toutes les opérations : Addition, Soustraction, Comparaisons, Modulo, PGCD

### Exemple d'exécution

```
CALCULATRICE BIGBINARY

Entrez le premier nombre (decimal) : 12
Entrez le deuxieme nombre (decimal) : 5

VALEURS SAISIES

  Nombre 1 : 0000 1100 (12)
  Nombre 2 : 0000 0101 (5)

ADDITION

  12 + 5 = 0001 0001 (17)

SOUSTRACTION

  12 - 5 = 0000 0111 (7)

COMPARAISONS

  12 == 5 ? Non
  12 < 5  ? Non
  12 > 5  ? Oui

MODULO

  12 mod 5 = 0000 0010 (2)

PGCD

  PGCD(12, 5) = 0000 0001 (1)
```

## Phases du Projet

### Phase 1 
- [x] Structure BigBinary (avec Tdigits, Taille, Signe)
- [x] Fonction d'initialisation (vide et depuis une chaîne binaire)
- [x] Fonction d'affichage (afficheBigBinary)
- [x] Fonction libereBigBinary pour éviter les fuites mémoire
- [x] Fonction d'addition (algorithme "naïf")
- [x] Fonction de soustraction (supporte A < B avec résultat négatif)
- [x] Fonctions de comparaison : Egal(A, B) et Inferieur(A, B)

### Phase 2 
- [x] BigBinary_PGCD(A, B) : Algorithme binaire d'Euclide
- [x] BigBinary_mod(A, B) : Calcul du modulo
- [ ] BigBinary_expMod(M, exp, mod) : Exponentiation modulaire rapide

### Améliorations récentes
- [x] Saisie de nombres décimaux (conversion automatique en binaire)
- [x] Affichage en format octet (0000 1100)
- [x] Affichage binaire + décimal pour tous les résultats
- [x] Soustraction avec résultat négatif

## Remarques Importantes

- **Addition/Soustraction** : Algorithme "naïf" (méthode de l'école primaire)
- **PGCD** : Algorithme binaire d'Euclide (optimisé pour le binaire, sans division)
- **Modulo** : Basé sur la soustraction successive avec décalage
- **Mémoire** : Gestion correcte, pas de fuites
- **Affichage** : Format octet espacé (4 bits séparés par un espace)
