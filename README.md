# Projet BigBinary

## Introduction

Bienvenue sur mon Projet en C appelé **BigBinary**, une bibliothèque C développée dans le cadre de mon cursus d'ingénieur à l'ESIEA. Ce projet de programmation vise à développer une (petite) bibliothèque en langage C permettant la manipulation en binaire de "grands entiers" stockés dans des tableaux et tableaux dynamiques pour mieux gérer la mémoire.

## Organisation du Projet

```
PROJET_C/
├── bigbinary.h     - Déclarations (structures et prototypes)
├── bigbinary.c     - Implémentation des fonctions
├── main.c          - Programme principal avec tests
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
| `afficheBigBinary(nb)` | Affiche le nombre binaire |
| `creerBigBinaryDepuisChaine(chaine)` | Crée depuis "101010..." |

### Opérations Arithmétiques (Phase 1)

| Fonction | Description | Exemple |
|----------|-------------|---------|
| `additionBigBinary(A, B)` | A + B | 10 + 3 = 13 |
| `soustractionBigBinary(A, B)` | A - B (A ≥ B) | 10 - 3 = 7 |

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

## Tests Inclus

Le programme `main.c` exécute 6 suites de tests :

| Test | Description | Exemples |
|------|-------------|----------|
| 1 | Création/Affichage | 83, 0, -7 |
| 2 | Addition | 83+11=94, 15+1=16 |
| 3 | Soustraction | 83-11=72, 8-3=5 |
| 4 | Egal / Inferieur | Egal(5,5)=true, Inferieur(5,11)=true |
| 5 | BigBinary_mod | 11 mod 3=2, 20 mod 6=2 |
| 6 | BigBinary_PGCD | PGCD(48,18)=6, PGCD(21,14)=7 |

## Phases du Projet

### Phase 1 
- [x] Structure BigBinary (avec Tdigits, Taille, Signe)
- [x] Fonction d'initialisation (vide et depuis une chaîne binaire)
- [x] Fonction d'affichage (afficheBigBinary)
- [x] Fonction libereBigBinary pour éviter les fuites mémoire
- [x] Fonction d'addition (algorithme "naïf")
- [x] Fonction de soustraction (avec A ≥ B uniquement, algorithme "naïf")
- [x] Fonctions de comparaison : Egal(A, B) et Inferieur(A, B)

### Phase 2 
- [x] BigBinary_PGCD(A, B) : Algorithme binaire d'Euclide
- [x] BigBinary_mod(A, B) : Calcul du modulo
- [ ] BigBinary_expMod(M, exp, mod) : Exponentiation modulaire rapide

### Phase 3 (Bonus)
- [ ] BigBinary_RSA_encrypt(message, e, n) : Chiffrement RSA
- [ ] BigBinary_RSA_decrypt(cipher, d, n) : Déchiffrement RSA

## Remarques Importantes

- **Addition/Soustraction** : Algorithme "naïf" (méthode de l'école primaire)
- **PGCD** : Algorithme binaire d'Euclide (optimisé pour le binaire, sans division)
- **Modulo** : Basé sur la soustraction successive avec décalage
- **Mémoire** : Gestion correcte, pas de fuites
- **Restrictions** : 
  - L'addition fonctionne uniquement avec A et B positifs ou nuls
  - La soustraction nécessite A ≥ B
- Tous les tests passent avec succès

## Auteur

Projet réalisé dans le cadre d'un cours de programmation en C - ESIEA 3A S5.
