# BigBinary - Bibliothèque d'Arithmétique Binaire en C

Une bibliothèque C permettant de manipuler de grands nombres en représentation binaire et d'effectuer des opérations arithmétiques sur ceux-ci.

## Fonctionnalités

### Phase 1 : Fonctions de base
- **Création** : Création depuis une chaîne binaire
- **Affichage** : Affichage sans zéros en tête
- **Opérations de base** : Addition, Soustraction
- **Comparaisons** : Égalité (`Egal`), Infériorité (`Inferieur`)
- **Multiplication** : Méthode égyptienne (paysanne russe)

### Phase 2 : Fonctions avancées
- **PGCD** : Algorithme d'Euclide par soustractions
- **Modulo** : Division par soustractions avec décalages
- **Exponentiation modulaire** : Méthode "square and multiply"

## Structure du Projet

```
├── bigbinary.h    # Déclarations des types et fonctions
├── bigbinary.c    # Implémentation de la bibliothèque
├── main.c         # Programme de test
└── README.md      # Documentation
```

## Compilation et exécution

```bash
gcc -o project.exe main.c bigbinary.c
./project.exe
```

## Fonctions disponibles

| Fonction | Description |
|----------|-------------|
| `createBigBinary(size)` | Crée un BigBinary vide de taille donnée |
| `creerBigBinaryDepuisChaine(chaine)` | Crée un BigBinary depuis une chaîne binaire |
| `afficheBigBinary(nb)` | Affiche le nombre en binaire (sans zéros en tête) |
| `libereBigBinary(&nb)` | Libère la mémoire |
| `additionBigBinary(A, B)` | Additionne A + B |
| `soustractionBigBinary(A, B)` | Soustrait A - B |
| `Egal(A, B)` | Teste l'égalité (retourne `true` ou `false`) |
| `Inferieur(A, B)` | Teste si A < B (retourne `true` ou `false`) |
| `BigBinary_mult(A, B)` | Multiplie A × B |
| `BigBinary_PGCD(A, B)` | Calcule le PGCD de A et B |
| `BigBinary_mod(A, B)` | Calcule A mod B |
| `BigBinary_expMod(M, exp, mod)` | Calcule M^exp mod mod |

## Structure BigBinary

```c
typedef struct {
    int *Tdigits;  //Tableau des chiffres binaires (0 ou 1)
    int Taille;    //Nombre de chiffres
    int Signe;     //1 = positif, -1 = négatif, 0 = zéro
} BigBinary;
```