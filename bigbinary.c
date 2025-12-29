#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alloue un BigBinary de taille 'size'
BigBinary createBigBinary(int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0;
    return bb;
}

// Libère la mémoire d'un BigBinary
void libereBigBinary(BigBinary *nb) {
    if (nb->Tdigits != NULL) {
        free(nb->Tdigits);
        nb->Tdigits = NULL;
    }
    nb->Taille = 0;
    nb->Signe = 0;
}

// Affiche un BigBinary à l'écran
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) {
        printf("-");
    }
    
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < nb.Taille; i++) {
        printf("%d", nb.Tdigits[i]);
    }
    printf("\n");
}

// Crée un BigBinary à partir d'une chaîne binaire (ex: "1010")
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    int longueur = strlen(chaine);
    int debut = 0;
    int signe = 1;
    
    // Gestion du signe négatif
    if (chaine[0] == '-') {
        signe = -1;
        debut = 1;
        longueur--;
    }
    
    // Ignore les zéros en tête
    while (debut < (int)strlen(chaine) && chaine[debut] == '0') {
        debut++;
        longueur--;
    }
    
    // Cas où le nombre est zéro
    if (longueur <= 0) {
        BigBinary bb;
        bb.Tdigits = NULL;
        bb.Taille = 0;
        bb.Signe = 0;
        return bb;
    }
    
    BigBinary bb = createBigBinary(longueur);
    bb.Signe = signe;
    
    // Convertit chaque caractère en chiffre
    for (int i = 0; i < longueur; i++) {
        bb.Tdigits[i] = chaine[debut + i] - '0';
    }
    
    return bb;
}

// Supprime les zéros inutiles en tête du nombre
static BigBinary normaliserBigBinary(BigBinary nb) {
    int premier = 0;
    // Trouve le premier chiffre non-zéro
    while (premier < nb.Taille && nb.Tdigits[premier] == 0) {
        premier++;
    }
    
    // Tout est zéro
    if (premier == nb.Taille) {
        libereBigBinary(&nb);
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Pas de zéros en tête
    if (premier == 0) {
        return nb;
    }
    
    // Crée un nouveau tableau sans les zéros en tête
    BigBinary resultat = createBigBinary(nb.Taille - premier);
    resultat.Signe = 1;
    for (int i = 0; i < resultat.Taille; i++) {
        resultat.Tdigits[i] = nb.Tdigits[premier + i];
    }
    
    libereBigBinary(&nb);
    return resultat;
}

// Crée une copie indépendante d'un BigBinary
static BigBinary copieBigBinary(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    BigBinary copie = createBigBinary(A.Taille);
    copie.Signe = A.Signe;
    for (int i = 0; i < A.Taille; i++) {
        copie.Tdigits[i] = A.Tdigits[i];
    }
    return copie;
}

// Vérifie si un nombre est pair (dernier bit = 0)
static bool estPair(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) return true;
    return A.Tdigits[A.Taille - 1] == 0;
}

// Division par 2 (décalage à droite = supprime le dernier bit)
static BigBinary decalageDroite(BigBinary A) {
    if (A.Signe == 0 || A.Taille <= 1) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    BigBinary resultat = createBigBinary(A.Taille - 1);
    resultat.Signe = 1;
    for (int i = 0; i < resultat.Taille; i++) {
        resultat.Tdigits[i] = A.Tdigits[i];
    }
    
    return normaliserBigBinary(resultat);
}

// Multiplication par 2 (décalage à gauche = ajoute un 0 à droite)
static BigBinary decalageGauche(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    BigBinary resultat = createBigBinary(A.Taille + 1);
    resultat.Signe = A.Signe;
    for (int i = 0; i < A.Taille; i++) {
        resultat.Tdigits[i] = A.Tdigits[i];
    }
    resultat.Tdigits[A.Taille] = 0;
    
    return resultat;
}

// Retourne true si A == B
bool Egal(BigBinary A, BigBinary B) {
    if (A.Signe != B.Signe) return false;
    if (A.Signe == 0 && B.Signe == 0) return true;
    if (A.Taille != B.Taille) return false;
    
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    }
    return true;
}

// Retourne true si A < B
bool Inferieur(BigBinary A, BigBinary B) {
    if (A.Signe < B.Signe) return true;
    if (A.Signe > B.Signe) return false;
    if (A.Signe == 0 && B.Signe == 0) return false;
    
    bool resultat;
    
    // Compare d'abord par la taille
    if (A.Taille < B.Taille) {
        resultat = true;
    } else if (A.Taille > B.Taille) {
        resultat = false;
    } else {
        // Même taille : compare bit par bit
        resultat = false;
        for (int i = 0; i < A.Taille; i++) {
            if (A.Tdigits[i] < B.Tdigits[i]) {
                resultat = true;
                break;
            } else if (A.Tdigits[i] > B.Tdigits[i]) {
                resultat = false;
                break;
            }
        }
    }
    
    // Inverse le résultat pour les nombres négatifs
    if (A.Signe == -1) {
        resultat = !resultat;
    }
    
    return resultat;
}

// Addition : A + B
BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    if (A.Signe == 0) return copieBigBinary(B);
    if (B.Signe == 0) return copieBigBinary(A);
    
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary resultat = createBigBinary(maxTaille + 1);
    resultat.Signe = 1;
    
    int retenue = 0;
    // Additionne bit par bit de droite à gauche
    for (int i = 0; i < maxTaille; i++) {
        int bitA = (i < A.Taille) ? A.Tdigits[A.Taille - 1 - i] : 0;
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        
        int somme = bitA + bitB + retenue;
        resultat.Tdigits[maxTaille - i] = somme % 2;
        retenue = somme / 2;
    }
    resultat.Tdigits[0] = retenue;
    
    return normaliserBigBinary(resultat);
}

// Soustraction : A - B
BigBinary soustractionBigBinary(BigBinary A, BigBinary B) {
    if (B.Signe == 0) return copieBigBinary(A);
    if (A.Signe == 0) {
        BigBinary resultat = copieBigBinary(B);
        resultat.Signe = -1;
        return resultat;
    }
    
    // Si A < B, calcule B - A et inverse le signe
    if (Inferieur(A, B)) {
        BigBinary resultat = soustractionBigBinary(B, A);
        resultat.Signe = -1;
        return resultat;
    }
    
    BigBinary resultat = createBigBinary(A.Taille);
    resultat.Signe = 1;
    int emprunt = 0;
    
    // Soustrait bit par bit de droite à gauche
    for (int i = 0; i < A.Taille; i++) {
        int bitA = A.Tdigits[A.Taille - 1 - i];
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        
        int diff = bitA - bitB - emprunt;
        
        if (diff < 0) {
            diff += 2;
            emprunt = 1;
        } else {
            emprunt = 0;
        }
        
        resultat.Tdigits[A.Taille - 1 - i] = diff;
    }
    
    return normaliserBigBinary(resultat);
}

// Modulo : A mod B (reste de la division)
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    // Division par zéro
    if (B.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // 0 mod B = 0
    if (A.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Si A < B, le reste est A
    if (Inferieur(A, B)) return copieBigBinary(A);
    
    // Si A == B, le reste est 0
    if (Egal(A, B)) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    BigBinary reste = copieBigBinary(A);
    
    // Division par soustractions successives avec décalages
    for (int i = 0; i < A.Taille; i++) {
        int decalage = A.Taille - B.Taille - i;
        if (decalage < 0) continue;
        
        // Décale B vers la gauche
        BigBinary diviseurDecale = createBigBinary(B.Taille + decalage);
        diviseurDecale.Signe = 1;
        for (int j = 0; j < B.Taille; j++) {
            diviseurDecale.Tdigits[j] = B.Tdigits[j];
        }
        for (int j = B.Taille; j < B.Taille + decalage; j++) {
            diviseurDecale.Tdigits[j] = 0;
        }
        
        // Soustrait tant que possible
        while (!Inferieur(reste, diviseurDecale)) {
            BigBinary nouveauReste = soustractionBigBinary(reste, diviseurDecale);
            libereBigBinary(&reste);
            reste = nouveauReste;
        }
        
        libereBigBinary(&diviseurDecale);
    }
    
    return reste;
}

// PGCD avec l'algorithme binaire de Stein
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    if (A.Signe == 0) return copieBigBinary(B);
    if (B.Signe == 0) return copieBigBinary(A);
    if (Egal(A, B)) return copieBigBinary(A);
    
    BigBinary u = copieBigBinary(A);
    BigBinary v = copieBigBinary(B);
    
    // Compte les facteurs 2 communs
    int k = 0;
    while (estPair(u) && estPair(v)) {
        BigBinary tempU = decalageDroite(u);
        BigBinary tempV = decalageDroite(v);
        libereBigBinary(&u);
        libereBigBinary(&v);
        u = tempU;
        v = tempV;
        k++;
    }
    
    // Retire les facteurs 2 restants de u
    while (estPair(u)) {
        BigBinary temp = decalageDroite(u);
        libereBigBinary(&u);
        u = temp;
    }
    
    // Boucle principale de l'algorithme de Stein
    while (v.Signe != 0) {
        while (estPair(v)) {
            BigBinary temp = decalageDroite(v);
            libereBigBinary(&v);
            v = temp;
        }
        
        // Assure que u <= v
        if (Inferieur(v, u)) {
            BigBinary temp = u;
            u = v;
            v = temp;
        }
        
        // v = v - u
        BigBinary diff = soustractionBigBinary(v, u);
        libereBigBinary(&v);
        v = diff;
    }
    
    BigBinary resultat = copieBigBinary(u);
    libereBigBinary(&u);
    libereBigBinary(&v);
    
    // Multiplie par 2^k pour restaurer les facteurs communs
    for (int i = 0; i < k; i++) {
        BigBinary temp = decalageGauche(resultat);
        libereBigBinary(&resultat);
        resultat = temp;
    }
    
    return resultat;
}

// Multiplication : A * B
BigBinary BigBinary_mult(BigBinary A, BigBinary B) {
    if (A.Signe == 0 || B.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Détermine le signe du résultat
    int signeResultat = (A.Signe == B.Signe) ? 1 : -1;
    
    BigBinary resultat;
    resultat.Tdigits = NULL;
    resultat.Taille = 0;
    resultat.Signe = 0;
    
    BigBinary a = copieBigBinary(A);
    BigBinary b = copieBigBinary(B);
    
    a.Signe = 1;
    b.Signe = 1;
    
    // Multiplication par additions et décalages successifs
    while (b.Signe != 0) {
        // Si b est impair, ajoute a au résultat
        if (!estPair(b)) {
            BigBinary temp = additionBigBinary(resultat, a);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // a = a * 2
        BigBinary tempA = decalageGauche(a);
        libereBigBinary(&a);
        a = tempA;
        
        // b = b / 2
        BigBinary tempB = decalageDroite(b);
        libereBigBinary(&b);
        b = tempB;
    }
    
    libereBigBinary(&a);
    libereBigBinary(&b);
    
    resultat.Signe = signeResultat;
    return resultat;
}

// Exponentiation modulaire : M^exp mod mod
BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod) {
    if (mod.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // x^0 = 1
    if (exp == 0) {
        BigBinary un = createBigBinary(1);
        un.Signe = 1;
        un.Tdigits[0] = 1;
        return un;
    }
    
    // 0^n = 0
    if (M.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Initialise le résultat à 1
    BigBinary resultat = createBigBinary(1);
    resultat.Signe = 1;
    resultat.Tdigits[0] = 1;
    
    BigBinary base = BigBinary_mod(M, mod);
    
    // Exponentiation rapide (square and multiply)
    while (exp > 0) {
        // Si exp est impair, multiplie le résultat par base
        if (exp % 2 == 1) {
            BigBinary produit = BigBinary_mult(resultat, base);
            BigBinary temp = BigBinary_mod(produit, mod);
            libereBigBinary(&produit);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // base = base² mod mod
        BigBinary carre = BigBinary_mult(base, base);
        BigBinary tempBase = BigBinary_mod(carre, mod);
        libereBigBinary(&carre);
        libereBigBinary(&base);
        base = tempBase;
        
        exp = exp / 2;
    }
    
    libereBigBinary(&base);
    
    return resultat;
}