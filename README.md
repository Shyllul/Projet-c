# Projet BigBinary - Phase 1

Bibliotheque C pour manipuler des grands entiers en binaire

## ORGANISATION DU PROJET

```
PROJET_C/
├── bigbinary.h          - Declarations (structures)
├── bigbinary.c          - Implementations des fonctions
├── main.c               - Programme principal avec tests
├── project.exe          - Executable Windows
├── docs/       - Documents du projet
│   └── Phase_1.pdf
└── README.md            - Ce fichier
```

## COMPILATION ET EXECUTION

### Compiler
gcc main.c bigbinary.c -o project.exe

### Executer
./project.exe

## DESCRIPTION DES FICHIERS

### bigbinary.h
- Structure BigBinary
- Prototypes de toutes les fonctions
- A inclure dans les autres fichiers

### bigbinary.c 
- Implementation des fonctions
- Algorithmes d'addition, soustraction
- Fonctions de comparaison

### main.c
- Programme principal
- Tests de toutes les fonctionnalites
- Affichage des resultats


## FONCTIONNALITES IMPLEMENTEES (Phase 1)

| Fonction                          | Description                  | Statut    |
|-----------------------------------|------------------------------|-----------|
| initBigBinary()                   | Initialise un BigBinary vide | [OK]      |
| libereBigBinary()                 | Libere la memoire            | [OK]      |
| afficheBigBinary()                | Affiche le nombre binaire    | [OK]      |
| creerBigBinaryDepuisChaine()      | Cree depuis "101010..."      | [OK]      |
| additionBigBinary()               | Addition A + B               | [OK]      |
| soustractionBigBinary()           | Soustraction A - B (A >= B)  | [OK]      |
| egalBigBinary()                   | Teste si A == B              | [OK]      |
| inferieurBigBinary()              | Teste si A < B               | [OK]      |


## TESTS INCLUS

Le programme main.c teste automatiquement :

TEST 1 : Creation et affichage
  - 1010011 (83 en decimal)
  - 0
  - -111 (-7 en decimal)

TEST 2 : Addition
  - 83 + 11 = 94 (1011110)
  - 15 + 1 = 16 (10000)

TEST 3 : Soustraction
  - 83 - 11 = 72 (1001000)
  - 8 - 3 = 5 (101)

TEST 4 : Egalite
  - 101 == 101 → true
  - 101 == 1011 → false

TEST 5 : Comparaison
  - 101 < 1011 → true
  - 1011 < 101 → false
  - 101 < 101 → false


## STRUCTURE BIGBINARY

```c
typedef struct {
    int *Tdigits;  // Tableau de bits (MSB a LSB)
    int Taille;    // Nombre de bits
    int Signe;     // +1 (positif), -1 (negatif), 0 (nul)
} BigBinary;
```

### Exemple : Le nombre 83

En decimal : 83  
En binaire : 1010011

Representation en memoire :
```
Tdigits[0] = 1  <- MSB (bit de poids fort)
Tdigits[1] = 0
Tdigits[2] = 1
Tdigits[3] = 0
Tdigits[4] = 0
Tdigits[5] = 1
Tdigits[6] = 1  <- LSB (bit de poids faible)

Taille = 7
Signe = +1
```

## PHASES DU PROJET

### Phase 1 (Terminee)
- [X] Addition binaire
- [X] Soustraction binaire
- [X] Comparaisons (egal, inferieur)

### Phase 2 (A venir)
- [ ] PGCD binaire d'Euclide
- [ ] Modulo
- [ ] Exponentiation modulaire

### Phase 3 (Bonus)
- [ ] Chiffrement RSA
- [ ] Dechiffrement RSA


## REMARQUES IMPORTANTES

- Les fonctions d'addition et soustraction utilisent l'algorithme "naif" 
  (methode de l'ecole primaire)
- L'addition fonctionne uniquement avec A et B positifs ou nuls
- La soustraction necessite A >= B
- Tous les tests passent avec succes

- La gestion memoire est correcte (pas de fuites)
