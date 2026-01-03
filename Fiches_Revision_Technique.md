# Fiche de Révision - BigBinary

## Structure BigBinary

```c
typedef struct {
    int *Tdigits;  // Tableau des bits (0 ou 1)
    int Taille;    // Nombre de bits
    int Signe;     // 1 = positif, -1 = négatif, 0 = zéro
} BigBinary;
```

**Important** : Les bits sont stockés de gauche à droite (MSB → LSB).
Exemple : `1101` est stocké comme `[1, 1, 0, 1]` avec Taille = 4.

---

## Fonctions de Base

### createBigBinary(size)
**But** : Créer un BigBinary vide de taille `size`.

**Étapes** :
1. Allouer la mémoire avec `malloc(sizeof(int) * size)`
2. Mettre Taille = size
3. Mettre Signe = 0 (zéro par défaut)

---

### creerBigBinaryDepuisChaine(chaine)
**But** : Convertir une chaîne comme `"1101"` en BigBinary.

**Étapes** :
1. Compter les caractères valides ('0' ou '1')
2. Allouer la mémoire
3. Copier chaque bit dans le tableau
4. Si tous les bits sont 0, mettre Signe = 0

**Astuce** : `chaine[i] - '0'` convertit le caractère '0' en entier 0, et '1' en 1.

---

### libereBigBinary(nb)
**But** : Libérer la mémoire d'un BigBinary.

**Étapes** :
1. `free(nb->Tdigits)` - libère le tableau
2. `nb->Tdigits = NULL` - évite les pointeurs invalides
3. Remettre Taille et Signe à 0

**Important** : Toujours libérer après utilisation pour éviter les fuites mémoire !

---

## Addition

### additionBigBinary(A, B)
**But** : Calculer A + B en binaire.

**Principe** : Comme l'addition posée à la main, mais en base 2.

```
    1 1 0 1   (13)
  + 0 1 1 0   (6)
  ---------
  1 0 0 1 1   (19)
```

**Étapes** :
1. Trouver maxTaille = max(A.Taille, B.Taille)
2. Créer résultat de taille maxTaille + 1 (pour la retenue)
3. Pour i de 0 à maxTaille-1 :
   - bitA = bit de A à la position i (depuis la droite)
   - bitB = bit de B à la position i
   - somme = bitA + bitB + retenue
   - résultat[i] = somme % 2
   - retenue = somme / 2
4. Mettre la retenue finale au début

**Règles d'addition binaire** :
| bitA | bitB | retenue | résultat | nouvelle retenue |
|------|------|---------|----------|------------------|
| 0    | 0    | 0       | 0        | 0                |
| 0    | 1    | 0       | 1        | 0                |
| 1    | 0    | 0       | 1        | 0                |
| 1    | 1    | 0       | 0        | 1                |
| 1    | 1    | 1       | 1        | 1                |

---

## Soustraction

### soustractionBigBinary(A, B)
**But** : Calculer A - B en binaire.

**Cas spéciaux** :
- Si B = 0 → retourner A
- Si A = 0 → retourner -B
- Si A < B → calculer B - A et mettre signe négatif

**Principe** : Comme la soustraction posée, avec emprunts.

**Étapes** (cas A ≥ B) :
1. Pour i de 0 à A.Taille-1 :
   - diff = bitA - bitB - emprunt
   - Si diff < 0 : diff += 2, emprunt = 1
   - Sinon : emprunt = 0
   - résultat[i] = diff

---

## Comparaisons

### Egal(A, B)
**But** : Vérifier si A == B.

**Étapes** :
1. Si signes différents → false
2. Ignorer les zéros en tête (trouver le premier 1)
3. Comparer les tailles effectives
4. Comparer bit par bit

### Inferieur(A, B)
**But** : Vérifier si A < B.

**Étapes** :
1. Comparer les signes (-1 < 0 < 1)
2. Ignorer les zéros en tête
3. Le nombre avec plus de bits est plus grand
4. Si même taille : comparer bit par bit de gauche à droite

---

## PGCD (Plus Grand Commun Diviseur)

### BigBinary_PGCD(A, B)
**But** : Trouver le plus grand diviseur commun de A et B.

**Algorithme d'Euclide par soustractions** :
```
Tant que A ≠ B :
    Si A < B : B = B - A
    Sinon    : A = A - B
Retourner A
```

**Exemple** : PGCD(12, 8)
- 12 > 8 → A = 12 - 8 = 4
- 8 > 4 → B = 8 - 4 = 4
- A == B → PGCD = 4

---

## Modulo

### BigBinary_mod(A, B)
**But** : Calculer A mod B (reste de la division).

**Principe** : Soustraire B décalé de A tant que possible.

**Étapes** :
1. Si A < B → retourner A
2. Pour chaque décalage possible :
   - Créer B_décalé = B × 2^décalage
   - Tant que reste ≥ B_décalé : reste = reste - B_décalé
3. Retourner le reste

---

## Multiplication

### BigBinary_mult(A, B)
**But** : Calculer A × B.

**Méthode égyptienne (paysanne russe)** :
```
résultat = 0
Tant que B > 0 :
    Si B est impair : résultat += A
    A = A × 2  (décalage gauche)
    B = B ÷ 2  (décalage droite)
Retourner résultat
```

**Exemple** : 5 × 6
| A  | B | B impair? | résultat |
|----|---|-----------|----------|
| 5  | 6 | Non       | 0        |
| 10 | 3 | Oui       | 10       |
| 20 | 1 | Oui       | 30       |
| 40 | 0 | Stop      | **30** ✓ |

---

## Exponentiation Modulaire

### BigBinary_expMod(M, exp, mod)
**But** : Calculer M^exp mod modulo.

**Méthode "square and multiply"** :
```
résultat = 1
base = M mod modulo
Tant que exp > 0 :
    Si exp impair : résultat = (résultat × base) mod modulo
    exp = exp ÷ 2
    base = (base × base) mod modulo
Retourner résultat
```
