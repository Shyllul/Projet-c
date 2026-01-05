# Fiche de Révision Détaillée - BigBinary

## Structure BigBinary

```c
typedef struct {
    int *Tdigits;  // Tableau des bits (0 ou 1)
    int Taille;    // Nombre de bits
    int Signe;     // 1 = positif, -1 = négatif, 0 = zéro
} BigBinary;
```

**Stockage des bits** : Les bits sont stockés de gauche à droite (MSB → LSB).
- Exemple : `1101` (13 en décimal) est stocké comme `Tdigits = [1, 1, 0, 1]` avec `Taille = 4`.

---

# PHASE 1 : FONCTIONS DE BASE

---

## createBigBinary(size)

**Signature** : `BigBinary createBigBinary(int size)`

**But** : Créer un BigBinary vide de taille `size`.

**Code détaillé** :
```c
BigBinary createBigBinary(int size) {
    BigBinary bb;                              // Déclare une variable de type BigBinary
    bb.Tdigits = malloc(sizeof(int) * size);   // Alloue un tableau de 'size' entiers
    bb.Taille = size;                          // Stocke la taille
    bb.Signe = 0;                              // Par défaut, le nombre est zéro
    return bb;                                 // Retourne la structure
}
```

**Explication ligne par ligne** :
1. `BigBinary bb;` → Crée une variable locale `bb` de type `BigBinary`
2. `bb.Tdigits = malloc(sizeof(int) * size);` → Alloue dynamiquement un tableau de `size` entiers (4 octets × size)
3. `bb.Taille = size;` → Mémorise combien de bits on peut stocker
4. `bb.Signe = 0;` → Initialise à zéro (le tableau n'est pas rempli, donc le nombre vaut 0)
5. `return bb;` → Retourne la structure par valeur (copie)

**Note** : Le tableau alloué avec `malloc` n'est **pas initialisé** ! Il peut contenir des valeurs aléatoires.

---

## creerBigBinaryDepuisChaine(chaine)

**Signature** : `BigBinary creerBigBinaryDepuisChaine(const char *chaine)`

**But** : Convertir une chaîne comme `"1101"` en BigBinary.

**Code détaillé** :
```c
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int longueurChaine = strlen(chaine);       // Compte le nombre de caractères
    nb.Taille = 0;

    // ÉTAPE 1 : Compter les caractères valides ('0' ou '1')
    for (int i = 0; i < longueurChaine; i++) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Taille = nb.Taille + 1;         // Incrémente si c'est un bit valide
        }
    }

    // ÉTAPE 2 : Allouer la mémoire
    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = 1;                              // Positif par défaut
    int index = 0;
    int tousZeros = 1;                         // Flag pour détecter si tout est 0

    // ÉTAPE 3 : Copier les bits dans le tableau
    for (int i = 0; i < nb.Taille; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';  // '0'→0, '1'→1
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    // ÉTAPE 4 : Si tous les bits sont 0, le nombre est zéro
    if (tousZeros) nb.Signe = 0;
    
    return nb;
}
```

**Astuce clé** : `chaine[i] - '0'`
- Le caractère `'0'` a le code ASCII 48
- Le caractère `'1'` a le code ASCII 49
- Donc `'1' - '0'` = 49 - 48 = 1

---

## creerBigBinaryDepuisDecimal(nombre)

**Signature** : `BigBinary creerBigBinaryDepuisDecimal(unsigned long long nombre)`

**But** : Convertir un nombre décimal (ex: 13) en binaire (ex: 1101).

**Code détaillé** :
```c
BigBinary creerBigBinaryDepuisDecimal(unsigned long long nombre) {
    // Cas spécial : zéro
    if (nombre == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // ÉTAPE 1 : Compter le nombre de bits nécessaires
    int nbBits = 0;
    unsigned long long temp = nombre;
    while (temp > 0) {
        nbBits++;              // Compte un bit de plus
        temp = temp / 2;       // Division entière par 2
    }
    
    // ÉTAPE 2 : Créer le BigBinary
    BigBinary nb = createBigBinary(nbBits);
    nb.Signe = 1;
    
    // ÉTAPE 3 : Remplir les bits de droite à gauche
    temp = nombre;
    for (int i = nbBits - 1; i >= 0; i--) {
        nb.Tdigits[i] = temp % 2;  // Récupère le bit de poids faible
        temp = temp / 2;            // Passe au bit suivant
    }
    
    return nb;
}
```

**Exemple pour nombre = 13** :
| Étape | temp | temp % 2 | nb.Tdigits |
|-------|------|----------|------------|
| Comptage | 13→6→3→1→0 | - | nbBits = 4 |
| i=3 | 13 | 1 | [_, _, _, 1] |
| i=2 | 6 | 0 | [_, _, 0, 1] |
| i=1 | 3 | 1 | [_, 1, 0, 1] |
| i=0 | 1 | 1 | [1, 1, 0, 1] ✓ |

---

## bigBinaryVersDecimal(nb)

**Signature** : `unsigned long long bigBinaryVersDecimal(BigBinary nb)`

**But** : Convertir un BigBinary en nombre décimal.

**Code détaillé** :
```c
unsigned long long bigBinaryVersDecimal(BigBinary nb) {
    if (nb.Signe == 0 || nb.Taille == 0) {
        return 0;                      // Si zéro, retourner 0
    }
    
    unsigned long long resultat = 0;
    unsigned long long puissance = 1;  // Commence à 2^0 = 1
    
    // Parcourir les bits de droite à gauche
    for (int i = nb.Taille - 1; i >= 0; i--) {
        if (nb.Tdigits[i] == 1) {
            resultat = resultat + puissance;  // Ajoute 2^position
        }
        puissance = puissance * 2;            // Passe à la puissance suivante
    }
    
    return resultat;
}
```

**Principe** : Un nombre binaire `1101` = 1×2³ + 1×2² + 0×2¹ + 1×2⁰ = 8 + 4 + 0 + 1 = 13

**Exemple pour [1, 1, 0, 1]** :
| i | bit | puissance | résultat |
|---|-----|-----------|----------|
| 3 | 1 | 1 | 0 + 1 = 1 |
| 2 | 0 | 2 | 1 (pas d'ajout) |
| 1 | 1 | 4 | 1 + 4 = 5 |
| 0 | 1 | 8 | 5 + 8 = **13** ✓ |

---

## afficheBigBinary(nb)

**Signature** : `void afficheBigBinary(BigBinary nb)`

**But** : Afficher un BigBinary sur la console.

**Code détaillé** :
```c
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf(" -");     // Affiche le signe négatif
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");                    // Affiche "0" si le nombre est nul
        return;
    }   
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);      // Affiche chaque bit un par un
    }
    printf("\n");                         // Nouvelle ligne à la fin
}
```

---

## libereBigBinary(nb)

**Signature** : `void libereBigBinary(BigBinary *nb)`

**But** : Libérer la mémoire allouée pour un BigBinary.

**Code détaillé** :
```c
void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);        // Libère le tableau de bits
    nb->Tdigits = NULL;       // Évite les pointeurs invalides (dangling pointer)
    nb->Taille = 0;           // Remet la taille à 0
    nb->Signe = 0;            // Remet le signe à 0
}
```

**Pourquoi un pointeur ?** On passe `BigBinary *nb` (et non `BigBinary nb`) pour pouvoir modifier la structure originale, pas une copie.

**⚠️ Important** : Toujours appeler cette fonction après utilisation pour éviter les **fuites mémoire** !

---

# OPÉRATIONS ARITHMÉTIQUES

---

## additionBigBinary(A, B)

**Signature** : `BigBinary additionBigBinary(BigBinary A, BigBinary B)`

**But** : Calculer A + B en binaire.

**Principe** : Addition posée, identique à celle en base 10, mais en base 2.

```
    1 1 0 1   (13)
  + 0 1 1 0   (6)
  ---------
  1 0 0 1 1   (19)
```

**Code détaillé** :
```c
BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    
    // ÉTAPE 1 : Trouver la taille du plus grand nombre
    int maxTaille;
    if (A.Taille > B.Taille) {
        maxTaille = A.Taille;
    } else {
        maxTaille = B.Taille;
    }
    
    // ÉTAPE 2 : Créer le résultat (maxTaille + 1 pour la retenue possible)
    BigBinary resultat = createBigBinary(maxTaille + 1);
    resultat.Signe = 1;
    
    // ÉTAPE 3 : Additionner bit par bit, de droite à gauche
    int retenue = 0;
    
    for (int i = 0; i < maxTaille; i++) {
        // Récupérer le bit de A (en partant de la droite)
        int bitA;
        if (i < A.Taille) {
            bitA = A.Tdigits[A.Taille - 1 - i];  // Lecture de droite à gauche
        } else {
            bitA = 0;  // Si A est plus court, on complète avec des 0
        }
        
        // Récupérer le bit de B (en partant de la droite)
        int bitB;
        if (i < B.Taille) {
            bitB = B.Tdigits[B.Taille - 1 - i];
        } else {
            bitB = 0;
        }
        
        // Calculer la somme
        int somme = bitA + bitB + retenue;
        
        // Déterminer le bit résultat et la nouvelle retenue
        if (somme == 0) {
            resultat.Tdigits[maxTaille - i] = 0;
            retenue = 0;
        }
        else if (somme == 1) {
            resultat.Tdigits[maxTaille - i] = 1;
            retenue = 0;
        }
        else if (somme == 2) {
            resultat.Tdigits[maxTaille - i] = 0;  // 2 en binaire = "10"
            retenue = 1;
        }
        else if (somme == 3) {
            resultat.Tdigits[maxTaille - i] = 1;  // 3 en binaire = "11"
            retenue = 1;
        }
    }
    
    // ÉTAPE 4 : Mettre la retenue finale dans le premier bit
    resultat.Tdigits[0] = retenue;
    
    return resultat;
}
```

**Table d'addition binaire** :
| bitA | bitB | retenue | somme | résultat | nouvelle retenue |
|------|------|---------|-------|----------|------------------|
| 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 1 | 0 |
| 1 | 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 0 | 2 | 0 | 1 |
| 1 | 1 | 1 | 3 | 1 | 1 |

**Pourquoi `A.Taille - 1 - i` ?**
- Les bits sont stockés de gauche à droite : `[1, 1, 0, 1]`
- On veut lire de droite à gauche pour l'addition
- Pour i=0 (premier bit à droite) : `Taille-1-0 = 3` → on lit `Tdigits[3] = 1`

---

## soustractionBigBinary(A, B)

**Signature** : `BigBinary soustractionBigBinary(BigBinary A, BigBinary B)`

**But** : Calculer A - B en binaire.

**Cas spéciaux gérés** :
| Condition | Action |
|-----------|--------|
| B = 0 | Retourne une copie de A |
| A = 0 | Retourne -B (copie de B avec signe négatif) |
| A < B | Calcule B - A et met le signe négatif |

**Code détaillé (cas normal A ≥ B)** :
```c
// Cas normal : A >= B, on fait la soustraction classique
BigBinary resultat = createBigBinary(A.Taille);
resultat.Signe = 1;
int emprunt = 0;

// Soustraire bit par bit, de droite à gauche
for (int i = 0; i < A.Taille; i++) {
    // Récupérer le bit de A
    int bitA = A.Tdigits[A.Taille - 1 - i];
    
    // Récupérer le bit de B
    int bitB;
    if (i < B.Taille) {
        bitB = B.Tdigits[B.Taille - 1 - i];
    } else {
        bitB = 0;
    }
    
    // Calculer la différence
    int diff = bitA - bitB - emprunt;
    
    // Si la différence est négative, on emprunte
    if (diff < 0) {
        diff = diff + 2;  // En binaire, on emprunte 2 (pas 10 !)
        emprunt = 1;
    } else {
        emprunt = 0;
    }
    
    resultat.Tdigits[A.Taille - 1 - i] = diff;
}

return resultat;
```

**Exemple : 1101 - 0110 = ?** (13 - 6 = 7)
| Position (i) | bitA | bitB | emprunt avant | diff | emprunt après | résultat |
|--------------|------|------|---------------|------|---------------|----------|
| 0 (droite) | 1 | 0 | 0 | 1 | 0 | 1 |
| 1 | 0 | 1 | 0 | -1 → +2 = 1 | 1 | 1 |
| 2 | 1 | 1 | 1 | -1 → +2 = 1 | 1 | 1 |
| 3 | 1 | 0 | 1 | 0 | 0 | 0 |

Résultat : `0111` = 7 ✓

---

## Egal(A, B)

**Signature** : `bool Egal(BigBinary A, BigBinary B)`

**But** : Vérifier si A == B.

**Code détaillé** :
```c
bool Egal(BigBinary A, BigBinary B) {
    
    // ÉTAPE 1 : Comparer les signes
    if (A.Signe != B.Signe) {
        return false;  // Signes différents → pas égaux
    }
    
    // ÉTAPE 2 : Si les deux sont zéro
    if (A.Signe == 0 && B.Signe == 0) {
        return true;
    }
    
    // ÉTAPE 3 : Trouver le premier bit non-nul de A (ignorer les zéros en tête)
    int debutA = 0;
    while (debutA < A.Taille && A.Tdigits[debutA] == 0) {
        debutA = debutA + 1;
    }
    
    // ÉTAPE 4 : Trouver le premier bit non-nul de B
    int debutB = 0;
    while (debutB < B.Taille && B.Tdigits[debutB] == 0) {
        debutB = debutB + 1;
    }
    
    // ÉTAPE 5 : Calculer les tailles effectives
    int tailleA = A.Taille - debutA;  // Bits significatifs de A
    int tailleB = B.Taille - debutB;  // Bits significatifs de B
    
    // ÉTAPE 6 : Comparer les tailles effectives
    if (tailleA != tailleB) {
        return false;
    }
    
    // ÉTAPE 7 : Comparer bit par bit
    for (int i = 0; i < tailleA; i++) {
        if (A.Tdigits[debutA + i] != B.Tdigits[debutB + i]) {
            return false;
        }
    }
    
    return true;
}
```

**Pourquoi ignorer les zéros en tête ?**
- `0011` et `11` représentent tous les deux 3
- Sans cette étape, on les considérerait comme différents

---

## Inferieur(A, B)

**Signature** : `bool Inferieur(BigBinary A, BigBinary B)`

**But** : Vérifier si A < B.

**Logique principale** :
1. Comparer les signes : -1 < 0 < 1
2. Ignorer les zéros en tête
3. Le nombre avec plus de bits significatifs est plus grand
4. Si même taille : comparer bit par bit de gauche à droite

**Code détaillé** :
```c
bool Inferieur(BigBinary A, BigBinary B) {
    
    // Comparer les signes (-1 < 0 < 1)
    if (A.Signe < B.Signe) return true;
    if (A.Signe > B.Signe) return false;
    
    // Si les deux sont zéro, A n'est pas inférieur à B
    if (A.Signe == 0 && B.Signe == 0) return false;
    
    // Trouver les premiers bits non-nuls
    int debutA = 0, debutB = 0;
    while (debutA < A.Taille && A.Tdigits[debutA] == 0) debutA++;
    while (debutB < B.Taille && B.Tdigits[debutB] == 0) debutB++;
    
    // Calculer les tailles effectives
    int tailleA = A.Taille - debutA;
    int tailleB = B.Taille - debutB;
    
    bool resultat;
    
    if (tailleA < tailleB) {
        resultat = true;   // A a moins de bits → A < B
    }
    else if (tailleA > tailleB) {
        resultat = false;  // A a plus de bits → A > B
    }
    else {
        // Même nombre de bits : comparer bit par bit
        resultat = false;
        for (int i = 0; i < tailleA; i++) {
            if (A.Tdigits[debutA + i] < B.Tdigits[debutB + i]) {
                resultat = true;
                break;
            }
            else if (A.Tdigits[debutA + i] > B.Tdigits[debutB + i]) {
                resultat = false;
                break;
            }
        }
    }
    
    // Inverser pour les nombres négatifs (-5 < -3, mais 5 > 3)
    if (A.Signe == -1) {
        resultat = !resultat;
    }
    
    return resultat;
}
```

---

# PHASE 2 : FONCTIONS AVANCÉES

---

## BigBinary_PGCD(A, B)

**Signature** : `BigBinary BigBinary_PGCD(BigBinary A, BigBinary B)`

**But** : Trouver le Plus Grand Commun Diviseur de A et B.

**Algorithme d'Euclide par soustractions** :
```
Tant que A ≠ B :
    Si A < B : B = B - A
    Sinon    : A = A - B
Retourner A
```

**Cas spéciaux** :
- PGCD(0, B) = B
- PGCD(A, 0) = A
- PGCD(0, 0) = 0

**Code détaillé** :
```c
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    
    // Cas spéciaux : zéro
    if (A.Signe == 0) {
        if (B.Signe == 0) {
            // PGCD(0, 0) = 0
            BigBinary zero = {NULL, 0, 0};
            return zero;
        }
        // PGCD(0, B) = B → retourner une copie de B
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = B.Signe;
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    if (B.Signe == 0) {
        // PGCD(A, 0) = A → retourner une copie de A
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Créer des copies de travail (pour ne pas modifier les originaux)
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) a.Tdigits[i] = A.Tdigits[i];
    
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) b.Tdigits[i] = B.Tdigits[i];
    
    // Boucle principale : tant que a ≠ b
    while (Egal(a, b) == false) {
        if (Inferieur(a, b)) {
            // b > a, donc b = b - a
            BigBinary temp = soustractionBigBinary(b, a);
            libereBigBinary(&b);  // Libérer l'ancienne valeur
            b = temp;             // Nouvelle valeur
        } else {
            // a > b, donc a = a - b
            BigBinary temp = soustractionBigBinary(a, b);
            libereBigBinary(&a);
            a = temp;
        }
    }
    
    // Quand a == b, c'est le PGCD
    libereBigBinary(&b);
    return a;
}
```

**Exemple : PGCD(12, 8)**
| Étape | a | b | Action |
|-------|---|---|--------|
| 0 | 12 | 8 | a > b → a = 12-8 = 4 |
| 1 | 4 | 8 | a < b → b = 8-4 = 4 |
| 2 | 4 | 4 | a == b → PGCD = **4** ✓ |

---

## BigBinary_mod(A, B)

**Signature** : `BigBinary BigBinary_mod(BigBinary A, BigBinary B)`

**But** : Calculer A mod B (reste de la division de A par B).

**Principe** : Division par soustractions successives avec décalages.

**Code détaillé** :
```c
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    
    // Cas spéciaux
    if (B.Signe == 0 || A.Signe == 0) {
        BigBinary zero = {NULL, 0, 0};
        return zero;  // 0 mod B = 0, A mod 0 = 0 (évite div/0)
    }
    
    // Si A < B, le reste est A
    if (Inferieur(A, B)) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) copie.Tdigits[i] = A.Tdigits[i];
        return copie;
    }
    
    // Créer une copie de travail (le reste)
    BigBinary reste = createBigBinary(A.Taille);
    reste.Signe = A.Signe;
    for (int i = 0; i < A.Taille; i++) reste.Tdigits[i] = A.Tdigits[i];
    
    // Division par soustractions avec décalages
    for (int i = 0; i < A.Taille; i++) {
        int decalage = A.Taille - B.Taille - i;
        
        if (decalage < 0) continue;  // Décalage impossible
        
        // Créer B décalé = B × 2^decalage
        // Exemple : B = 101, decalage = 2 → B décalé = 10100
        BigBinary diviseurDecale = createBigBinary(B.Taille + decalage);
        diviseurDecale.Signe = 1;
        
        // Copier les bits de B
        for (int j = 0; j < B.Taille; j++) {
            diviseurDecale.Tdigits[j] = B.Tdigits[j];
        }
        // Ajouter les zéros à droite
        for (int j = B.Taille; j < B.Taille + decalage; j++) {
            diviseurDecale.Tdigits[j] = 0;
        }
        
        // Soustraire tant que reste >= diviseur décalé
        while (Inferieur(reste, diviseurDecale) == false) {
            BigBinary nouveauReste = soustractionBigBinary(reste, diviseurDecale);
            libereBigBinary(&reste);
            reste = nouveauReste;
        }
        
        libereBigBinary(&diviseurDecale);
    }
    
    return reste;
}
```

**Exemple : 13 mod 3** (1101 mod 11)
| Décalage | diviseurDecale | Action |
|----------|----------------|--------|
| 2 | 11**00** (12) | 1101 >= 1100 → 1101 - 1100 = 0001 |
| 1 | 11**0** (6) | 0001 < 110 → rien |
| 0 | 11 (3) | 0001 < 11 → rien |

Résultat : reste = 0001 = **1** ✓

---

## BigBinary_mult(A, B)

**Signature** : `BigBinary BigBinary_mult(BigBinary A, BigBinary B)`

**But** : Calculer A × B.

**Méthode égyptienne (paysanne russe)** :
```
résultat = 0
Tant que B > 0 :
    Si B est impair : résultat = résultat + A
    A = A × 2  (décalage gauche = ajouter un 0 à droite)
    B = B ÷ 2  (décalage droite = supprimer le dernier bit)
Retourner résultat
```

**Code détaillé** :
```c
BigBinary BigBinary_mult(BigBinary A, BigBinary B) {
    
    // Si l'un des nombres est zéro, le résultat est zéro
    if (A.Signe == 0 || B.Signe == 0) {
        BigBinary zero = {NULL, 0, 0};
        return zero;
    }
    
    // Déterminer le signe du résultat
    int signeResultat = (A.Signe == B.Signe) ? 1 : -1;
    
    // Initialiser le résultat à zéro
    BigBinary resultat = {NULL, 0, 0};
    
    // Créer des copies de travail
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) a.Tdigits[i] = A.Tdigits[i];
    
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) b.Tdigits[i] = B.Tdigits[i];
    
    // Boucle principale
    while (b.Signe != 0) {
        // Vérifier si b est impair (dernier bit = 1)
        int dernierBit = (b.Taille > 0) ? b.Tdigits[b.Taille - 1] : 0;
        
        if (dernierBit == 1) {
            // b est impair → ajouter a au résultat
            BigBinary temp = additionBigBinary(resultat, a);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // Doubler a (ajouter un 0 à droite)
        if (a.Signe != 0) {
            BigBinary tempA = createBigBinary(a.Taille + 1);
            tempA.Signe = a.Signe;
            for (int i = 0; i < a.Taille; i++) tempA.Tdigits[i] = a.Tdigits[i];
            tempA.Tdigits[a.Taille] = 0;  // Ajouter le 0
            libereBigBinary(&a);
            a = tempA;
        }
        
        // Diviser b par 2 (supprimer le dernier bit)
        if (b.Taille > 1) {
            BigBinary tempB = createBigBinary(b.Taille - 1);
            tempB.Signe = 1;
            for (int i = 0; i < tempB.Taille; i++) tempB.Tdigits[i] = b.Tdigits[i];
            libereBigBinary(&b);
            b = tempB;
        } else {
            // b n'a plus qu'un bit, il devient zéro
            libereBigBinary(&b);
            b = (BigBinary){NULL, 0, 0};
        }
    }
    
    libereBigBinary(&a);
    libereBigBinary(&b);
    
    // Appliquer le signe
    if (resultat.Signe != 0) resultat.Signe = signeResultat;
    
    return resultat;
}
```

**Exemple : 5 × 6**
| a | b | b impair? | résultat | Action |
|---|---|-----------|----------|--------|
| 101 (5) | 110 (6) | Non (0) | 0 | a×2, b÷2 |
| 1010 (10) | 11 (3) | Oui (1) | 0+10=10 | a×2, b÷2 |
| 10100 (20) | 1 (1) | Oui (1) | 10+20=**30** | b÷2=0, stop |

Résultat : **30** ✓

---

## BigBinary_expMod(M, exp, mod)

**Signature** : `BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod)`

**But** : Calculer M^exp mod modulo efficacement.

**Pourquoi cette méthode ?**
Calculer d'abord M^exp puis faire le modulo serait trop lent et créerait des nombres gigantesques. La méthode "square and multiply" applique le modulo à chaque étape.

**Cas spéciaux** :
| Condition | Résultat | Raison |
|-----------|----------|--------|
| mod = 0 | 0 | Division par zéro impossible |
| exp = 0 | 1 | x^0 = 1 pour tout x |
| M = 0 | 0 | 0^n = 0 pour tout n > 0 |

**Méthode "square and multiply"** :
```
résultat = 1
base = M mod modulo        ← Réduire M dès le début
Tant que exp > 0 :
    Si exp impair : 
        résultat = (résultat × base) mod modulo
    exp = exp ÷ 2          ← Division entière
    base = (base × base) mod modulo  ← Élever au carré
Retourner résultat
```

**Code détaillé** :
```c
BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod) {
    
    // Cas spéciaux
    if (mod.Signe == 0) {
        return (BigBinary){NULL, 0, 0};  // Division par zéro
    }
    
    if (exp == 0) {
        BigBinary un = createBigBinary(1);
        un.Signe = 1;
        un.Tdigits[0] = 1;
        return un;  // x^0 = 1
    }
    
    if (M.Signe == 0) {
        return (BigBinary){NULL, 0, 0};  // 0^n = 0
    }
    
    // Initialiser le résultat à 1
    BigBinary resultat = createBigBinary(1);
    resultat.Signe = 1;
    resultat.Tdigits[0] = 1;
    
    // Calculer M mod modulo pour commencer
    BigBinary base = BigBinary_mod(M, mod);
    
    // Boucle principale
    while (exp > 0) {
        // Si exp est impair
        if (exp % 2 == 1) {
            // resultat = (resultat × base) mod modulo
            BigBinary produit = BigBinary_mult(resultat, base);
            BigBinary temp = BigBinary_mod(produit, mod);
            libereBigBinary(&produit);    // ⚠️ Libérer le produit intermédiaire
            libereBigBinary(&resultat);   // ⚠️ Libérer l'ancien résultat
            resultat = temp;
        }
        
        // Diviser l'exposant par 2
        exp = exp / 2;
        
        // Si on continue, calculer base = base² mod modulo
        if (exp > 0) {
            BigBinary carre = BigBinary_mult(base, base);
            BigBinary tempBase = BigBinary_mod(carre, mod);
            libereBigBinary(&carre);      // ⚠️ Libérer le carré intermédiaire
            libereBigBinary(&base);       // ⚠️ Libérer l'ancienne base
            base = tempBase;
        }
    }
    
    libereBigBinary(&base);
    return resultat;
}
```

**Exemple détaillé : 3^5 mod 7**
| Étape | exp | exp impair? | résultat | base | Action |
|-------|-----|-------------|----------|------|--------|
| Init | 5 | - | 1 | 3 | base = 3 mod 7 = 3 |
| 1 | 5 | Oui | (1×3) mod 7 = **3** | 3²=9 mod 7 = **2** | exp=5/2=2 |
| 2 | 2 | Non | 3 | 2²=4 mod 7 = **4** | exp=2/2=1 |
| 3 | 1 | Oui | (3×4) mod 7 = **5** | - | exp=1/2=0, stop |

**Résultat** : 3^5 mod 7 = **5** ✓ (vérification : 243 mod 7 = 5)

**Complexité** : O(log₂(exp)) opérations au lieu de O(exp)
- Pour exp = 1000 : ~10 opérations au lieu de 1000 !

---

# Points Clés pour la Révision

## Gestion de la mémoire
1. Toujours appeler `libereBigBinary()` après utilisation
2. Dans les boucles, libérer les variables temporaires pour éviter les fuites
3. Après `free()`, mettre le pointeur à `NULL`

## Lecture des bits
- Stockage : MSB à gauche, LSB à droite → `[1, 1, 0, 1]` pour 13
- Pour lire de droite à gauche : `Tdigits[Taille - 1 - i]`

## Conversions utiles
- Caractère → Entier : `'1' - '0'` = 1
- Décimal → Binaire : divisions successives par 2, prendre les restes
- Binaire → Décimal : somme des 2^position pour chaque bit à 1
