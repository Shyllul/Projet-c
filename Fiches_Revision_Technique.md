# Fiches de Révision Technique - Projet BigBinary

Ce document détaille le fonctionnement interne de chaque fonction du projet BigBinary. Il est conçu pour servir de support de révision technique, expliquant la logique algorithmique, la gestion de la mémoire et les cas particuliers.

## 1. Gestion de la Mémoire et Initialisation

### `createBigBinary`
*   **Signature**: `BigBinary createBigBinary(int size)`
*   **But**: Allouer et initialiser une structure `BigBinary` vide d'une taille donnée.
*   **Fonctionnement**:
    1.  Déclare une variable `BigBinary`.
    2.  Alloue dynamiquement (`malloc`) un tableau d'entiers `Tdigits` de la taille demandée (`size`).
    3.  Initialise `Taille` avec `size`.
    4.  Initialise `Signe` à 0 (neutre) par défaut.
    5.  Retourne la structure.
*   **Points Clés**:
    *   Ne remplit pas le tableau `Tdigits` avec des valeurs (contenu indéterminé après malloc).
    *   Le signe est 0, ce qui signifie "nul" tant qu'on n'a pas défini de valeur.

### `libereBigBinary`
*   **Signature**: `void libereBigBinary(BigBinary *nb)`
*   **But**: Libérer proprement la mémoire allouée pour un `BigBinary` afin d'éviter les fuites mémoire.
*   **Fonctionnement**:
    1.  Appelle `free` sur le pointeur `nb->Tdigits`.
    2.  Met le pointeur `Tdigits` à `NULL` (sécurité pour éviter les *dangling pointers*).
    3.  Met `Taille` et `Signe` à 0.
*   **Points Clés**:
    *   Prend un pointeur (`BigBinary *`) pour pouvoir modifier la structure originale.
    *   Indispensable après chaque utilisation temporaire de `BigBinary`.

### `creerBigBinaryDepuisChaine`
*   **Signature**: `BigBinary creerBigBinaryDepuisChaine(const char *chaine)`
*   **But**: Convertir une chaîne de caractères (ex: "1011") en structure `BigBinary`.
*   **Fonctionnement**:
    1.  Parcourt la chaîne une première fois pour compter uniquement les caractères valides ('0' et '1'). Cela détermine la `Taille`.
    2.  Alloue le tableau `Tdigits`.
    3.  Initialise `Signe` à +1 par défaut.
    4.  Parcourt la chaîne une seconde fois :
        *   Convertit chaque '0' ou '1' en entier (`char - '0'`) et le stocke dans `Tdigits`.
        *   Détecte si le nombre est entièrement nul (tous les bits à 0).
    5.  Si le nombre est entièrement nul, force `Signe` à 0.
*   **Points Clés**:
    *   Robustesse : ignore les caractères qui ne sont pas '0' ou '1'.
    *   Gère automatiquement le cas zéro (Signe = 0).

### `afficheBigBinary`
*   **Signature**: `void afficheBigBinary(BigBinary nb)`
*   **But**: Afficher le nombre binaire dans la console.
*   **Fonctionnement**:
    1.  Si `Signe` est -1, affiche le signe " - ".
    2.  Si `Signe` est 0 ou `Taille` est 0, affiche "0" et termine.
    3.  Sinon, boucle sur `Tdigits` de 0 à `Taille-1` et affiche chaque chiffre.
*   **Points Clés**:
    *   Gère l'affichage du signe négatif.
    *   Gère le cas particulier du zéro.

---

## 2. Opérations de Base

### `additionBigBinary`
*   **Signature**: `BigBinary additionBigBinary(BigBinary A, BigBinary B)`
*   **But**: Calculer A + B.
*   **Fonctionnement**:
    1.  **Cas Triviaux**: Si A est 0, retourne une copie de B. Si B est 0, retourne une copie de A.
    2.  **Préparation**:
        *   Détermine la taille maximale (`maxTaille`) entre A et B.
        *   Crée `resultat` de taille `maxTaille + 1` (pour gérer une éventuelle retenue finale).
        *   Initialise `retenue` à 0.
    3.  **Boucle d'addition** (de la droite vers la gauche):
        *   Récupère le bit de A et B (ou 0 si l'indice dépasse la taille).
        *   Calcule `somme = bitA + bitB + retenue`.
        *   Le bit résultat est `somme % 2`.
        *   Nouvelle `retenue` est `somme / 2`.
    4.  Place la retenue finale dans `resultat.Tdigits[0]`.
    5.  **Normalisation**: Supprime les zéros non significatifs en tête (crée un nouveau tableau plus petit si nécessaire).
*   **Points Clés**:
    *   Gère des nombres de tailles différentes.
    *   Gère la retenue (carry).
    *   Nettoie le résultat (suppression des zéros inutiles).

### `soustractionBigBinary`
*   **Signature**: `BigBinary soustractionBigBinary(BigBinary A, BigBinary B)`
*   **But**: Calculer A - B (suppose A et B positifs pour la logique de base, mais gère les signes via `Inferieur`).
*   **Fonctionnement**:
    1.  **Cas Triviaux**: Si B=0 -> A. Si A=0 -> -B.
    2.  **Inversion**: Si A < B, calcule `-(B - A)`. Appelle récursivement `soustractionBigBinary(B, A)` et change le signe.
    3.  **Algorithme principal** (A >= B) :
        *   Crée `resultat` de taille A.
        *   Boucle de la droite vers la gauche (LSB vers MSB).
        *   Calcule `diff = bitA - bitB - emprunt`.
        *   Si `diff < 0`, ajoute 2 (base binaire) à `diff` et met `emprunt` à 1. Sinon `emprunt` à 0.
        *   Stocke `diff`.
*   **Points Clés**:
    *   Utilise la notion d'**emprunt** (borrow).
    *   Gère intelligemment le cas où le résultat serait négatif en inversant les opérandes.

---

## 3. Comparaisons

### `Egal`
*   **Signature**: `bool Egal(BigBinary A, BigBinary B)`
*   **But**: Vérifier si A == B.
*   **Fonctionnement**:
    1.  Compare les signes. Si différents -> Faux.
    2.  Compare les cas zéros (Signe 0).
    3.  Compare les tailles. Si différentes -> Faux.
    4.  Compare chaque chiffre un par un. Au premier différent -> Faux.
    5.  Si tout correspond -> Vrai.

### `Inferieur`
*   **Signature**: `bool Inferieur(BigBinary A, BigBinary B)`
*   **But**: Vérifier si A < B.
*   **Fonctionnement**:
    1.  Vérifie les signes (Positif > Négatif).
    2.  Compare les tailles : un nombre positif avec plus de bits est forcément plus grand (car pas de zéros inutiles en tête).
    3.  Si tailles égales, parcourt du MSB au LSB (gauche à droite).
        *   Si `A[i] < B[i]` -> Vrai (car MSB plus petit signifie nombre plus petit).
        *   Si `A[i] > B[i]` -> Faux.
    4.  Ajuste la logique si les nombres sont négatifs (la logique s'inverse).

---

## 4. Opérations Avancées

### `BigBinary_mult` (Multiplication Égyptienne / Russe)
*   **Signature**: `BigBinary BigBinary_mult(BigBinary A, BigBinary B)`
*   **But**: Calculer A * B.
*   **Fonctionnement**:
    1.  Gère le signe du résultat (`SigneA * SigneB`).
    2.  Utilise deux copies de travail, `a` et `b`.
    3.  **Boucle Tant que b != 0**:
        *   Si `b` est impair (dernier bit à 1) : `resultat = resultat + a`.
        *   `a = a * 2` (Décalage vers la gauche : ajout d'un 0 à la fin).
        *   `b = b / 2` (Décalage vers la droite : suppression du dernier bit).
    4.  Libère les mémoires temporaires.
*   **Points Clés**:
    *   N'utilise pas la multiplication chiffre à chiffre classique mais des additions et décalages.
    *   C'est l'algo de la "multiplication à la russe" ou "paysanne".

### `BigBinary_PGCD` (Algorithme d'Euclide)
*   **Signature**: `BigBinary BigBinary_PGCD(BigBinary A, BigBinary B)`
*   **But**: Plus Grand Commun Diviseur.
*   **Fonctionnement**:
    1.  Gère les cas A=0 ou B=0 (le PGCD est l'autre nombre).
    2.  Crée des copies positives de A et B.
    3.  **Boucle Tant que A != B**:
        *   Si A < B : `B = B - A`
        *   Sinon : `A = A - B`
    4.  Retourne A (qui est égal à B à la fin).
*   **Points Clés**:
    *   Implémentation par soustractions successives (plus simple mais plus lent que le modulo pour les très grands nombres, mais suffisant ici).

### `BigBinary_mod` (Modulo optimisé)
*   **Signature**: `BigBinary BigBinary_mod(BigBinary A, BigBinary B)`
*   **But**: Reste de la division A % B.
*   **Fonctionnement**:
    1.  Si A < B, retourne A.
    2.  Copie A dans `reste`.
    3.  **Boucle d'alignement** :
        *   Tente de soustraire B décalé vers la gauche (multiplié par des puissances de 2) autant que possible.
        *   Pour chaque position `i`, crée un `diviseurDecale` (B avec des 0 ajoutés à droite).
        *   Tant que `reste >= diviseurDecale` (vérifié par `!Inferieur`), fait `reste = reste - diviseurDecale`.
    4.  Retourne le `reste`.
*   **Points Clés**:
    *   Beaucoup plus rapide que la soustraction simple répétée.
    *   Simule une division euclidienne bit à bit (comme la division posée à la main).

### `BigBinary_expMod` (Exponentiation Modulaire Rapide)
*   **Signature**: `BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod)`
*   **But**: Calculer `(M ^ exp) % mod` efficacement.
*   **Fonctionnement** (Algorithme *Square and Multiply*) :
    1.  Initialise `resultat` à 1.
    2.  Calcule `base = M % mod`.
    3.  **Boucle Tant que exp > 0**:
        *   Si `exp` est impair (bit de poids faible à 1) :
            *   `resultat = (resultat * base) % mod`.
        *   `exp = exp / 2` (décalage binaire vers la droite).
        *   `base = (base * base) % mod`.
    4.  Retourne `resultat`.
*   **Points Clés**:
    *   **Crucial pour la cryptographie (RSA)**.
    *   Complexité logarithmique par rapport à l'exposant (beaucoup plus rapide que de multiplier `exp` fois).
    *   Applique le modulo à chaque étape pour éviter que les nombres ne deviennent gigantesques.
