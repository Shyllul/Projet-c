#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Phase 1

BigBinary createBigBinary (int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0; // Par défaut nul
    return bb;
}

// Création depuis une chaîne binaire
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;

    // Comptons uniquement les caractères valides ('0' ou '1')
    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Taille++;
        }
    }

    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = +1;
    int index = 0;
    int tousZeros = 1;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    if (tousZeros) nb.Signe = 0;
    return nb;
}

// Affichage du nombre binaire
void afficheBigBinary (BigBinary nb) {
    if (nb.Signe == -1) printf ("-") ;
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf ("0\n");
        return;
    }
    for (int i = 0; i < nb.Taille; ++i) {
        printf ("%d", nb.Tdigits[i]);
    }
    printf ("\n");
}   

// Libèration de la mémoire
void libereBigBinary (BigBinary * nb) {
    free (nb->Tdigits) ;
    nb->Tdigits = NULL ;
    nb->Taille = 0;
    nb->Signe = 0;
}

// Addition : A + B
BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    // Cas où A est zéro
    if (A.Signe == 0) {
        if (B.Signe == 0) {
            BigBinary zero;
            zero.Tdigits = NULL;
            zero.Taille = 0;
            zero.Signe = 0;
            return zero;
        }
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = B.Signe;
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    // Cas où B est zéro
    if (B.Signe == 0) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary resultat = createBigBinary(maxTaille + 1);
    resultat.Signe = 1;
    
    int retenue = 0;
    for (int i = 0; i < maxTaille; i++) {
        int bitA = (i < A.Taille) ? A.Tdigits[A.Taille - 1 - i] : 0;
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        int somme = bitA + bitB + retenue;
        resultat.Tdigits[maxTaille - i] = somme % 2;
        retenue = somme / 2;
    }
    resultat.Tdigits[0] = retenue;
    
    // Supprime les zéros en tête
    int premier = 0;
    while (premier < resultat.Taille && resultat.Tdigits[premier] == 0) premier++;
    
    if (premier == resultat.Taille) {
        libereBigBinary(&resultat);
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    if (premier > 0) {
        BigBinary nouveau = createBigBinary(resultat.Taille - premier);
        nouveau.Signe = 1;
        for (int i = 0; i < nouveau.Taille; i++) {
            nouveau.Tdigits[i] = resultat.Tdigits[premier + i];
        }
        libereBigBinary(&resultat);
        return nouveau;
    }
    return resultat;
}

// Soustraction : A - B
BigBinary soustractionBigBinary(BigBinary A, BigBinary B) {
    // Cas où B est zéro
    if (B.Signe == 0) {
        if (A.Signe == 0) {
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
    
    // Cas où A est zéro
    if (A.Signe == 0) {
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = -1;
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    // Si A < B, on fait B - A et on inverse le signe
    if (Inferieur(A, B)) {
        BigBinary resultat = soustractionBigBinary(B, A);
        resultat.Signe = -1;
        return resultat;
    }
    
    BigBinary resultat = createBigBinary(A.Taille);
    resultat.Signe = 1;
    int emprunt = 0;
    
    for (int i = 0; i < A.Taille; i++) {
        int bitA = A.Tdigits[A.Taille - 1 - i];
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        int diff = bitA - bitB - emprunt;
        if (diff < 0) { diff += 2; emprunt = 1; } 
        else { emprunt = 0; }
        resultat.Tdigits[A.Taille - 1 - i] = diff;
    }
    
    // Supprime les zéros en tête
    int premier = 0;
    while (premier < resultat.Taille && resultat.Tdigits[premier] == 0) premier++;
    
    if (premier == resultat.Taille) {
        libereBigBinary(&resultat);
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    if (premier > 0) {
        BigBinary nouveau = createBigBinary(resultat.Taille - premier);
        nouveau.Signe = 1;
        for (int i = 0; i < nouveau.Taille; i++) {
            nouveau.Tdigits[i] = resultat.Tdigits[premier + i];
        }
        libereBigBinary(&resultat);
        return nouveau;
    }
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
    if (A.Taille < B.Taille) resultat = true;
    else if (A.Taille > B.Taille) resultat = false;
    else {
        resultat = false;
        for (int i = 0; i < A.Taille; i++) {
            if (A.Tdigits[i] < B.Tdigits[i]) { resultat = true; break; }
            else if (A.Tdigits[i] > B.Tdigits[i]) { resultat = false; break; }
        }
    }
    if (A.Signe == -1) resultat = !resultat;
    return resultat;
}

// PGCD par soustractions (Euclide simple)
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    // Cas A == 0
    if (A.Signe == 0) {
        if (B.Signe == 0) {
            BigBinary zero;
            zero.Tdigits = NULL;
            zero.Taille = 0;
            zero.Signe = 0;
            return zero;
        }
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = B.Signe;
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    // Cas B == 0
    if (B.Signe == 0) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Copie de travail de A
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) {
        a.Tdigits[i] = A.Tdigits[i];
    }
    
    // Copie de travail de B
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) {
        b.Tdigits[i] = B.Tdigits[i];
    }
    
    // Algorithme d'Euclide par soustractions
    while (!Egal(a, b)) {
        if (Inferieur(a, b)) {
            BigBinary temp = soustractionBigBinary(b, a);
            libereBigBinary(&b);
            b = temp;
        } else {
            BigBinary temp = soustractionBigBinary(a, b);
            libereBigBinary(&a);
            a = temp;
        }
    }
    
    libereBigBinary(&b);
    return a;
}

// Modulo avec décalages (optimisé)
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    // Division par zéro ou 0 mod B
    if (B.Signe == 0 || A.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Si A < B, le reste est A
    if (Inferieur(A, B)) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Copie de travail de A
    BigBinary reste = createBigBinary(A.Taille);
    reste.Signe = A.Signe;
    for (int i = 0; i < A.Taille; i++) {
        reste.Tdigits[i] = A.Tdigits[i];
    }
    
    // Division par soustractions avec décalages
    for (int i = 0; i < A.Taille; i++) {
        int decalage = A.Taille - B.Taille - i;
        if (decalage < 0) continue;
        
        // Décale B vers la gauche (B * 2^decalage)
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

// Multiplication Égyptienne : A * B
BigBinary BigBinary_mult(BigBinary A, BigBinary B) {
    if (A.Signe == 0 || B.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    int signeResultat = (A.Signe == B.Signe) ? 1 : -1;
    
    BigBinary resultat;
    resultat.Tdigits = NULL;
    resultat.Taille = 0;
    resultat.Signe = 0;
    
    // Copie de travail de A
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) {
        a.Tdigits[i] = A.Tdigits[i];
    }
    
    // Copie de travail de B
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) {
        b.Tdigits[i] = B.Tdigits[i];
    }
    
    // Multiplication par décalages (méthode égyptienne)
    while (b.Signe != 0) {
        // Si b est impair (dernier bit = 1), ajoute a au résultat
        if (b.Taille > 0 && b.Tdigits[b.Taille - 1] == 1) {
            BigBinary temp = additionBigBinary(resultat, a);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // a = a * 2 (décalage à gauche : ajoute un 0 à droite)
        if (a.Signe != 0) {
            BigBinary tempA = createBigBinary(a.Taille + 1);
            tempA.Signe = a.Signe;
            for (int i = 0; i < a.Taille; i++) {
                tempA.Tdigits[i] = a.Tdigits[i];
            }
            tempA.Tdigits[a.Taille] = 0;
            libereBigBinary(&a);
            a = tempA;
        }
        
        // b = b / 2 (décalage à droite : supprime le dernier bit)
        if (b.Taille > 1) {
            BigBinary tempB = createBigBinary(b.Taille - 1);
            tempB.Signe = 1;
            for (int i = 0; i < tempB.Taille; i++) {
                tempB.Tdigits[i] = b.Tdigits[i];
            }
            libereBigBinary(&b);
            b = tempB;
        } else {
            libereBigBinary(&b);
            b.Tdigits = NULL;
            b.Taille = 0;
            b.Signe = 0;
        }
    }
    
    libereBigBinary(&a);
    libereBigBinary(&b);
    
    if (resultat.Signe != 0) {
        resultat.Signe = signeResultat;
    }
    return resultat;
}

// Exponentiation modulaire
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
    
    // Résultat = 1
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
        
        // Divise l'exposant par 2
        exp = exp / 2;
        
        // Si exp > 0, on continue avec base = base²
        if (exp > 0) {
            BigBinary carre = BigBinary_mult(base, base);
            BigBinary tempBase = BigBinary_mod(carre, mod);
            libereBigBinary(&carre);
            libereBigBinary(&base);
            base = tempBase;
        }
    }
    
    libereBigBinary(&base);
    return resultat;
}
