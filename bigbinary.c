#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FONCTIONS DE BASE :

// Initialise un BigBinary vide

BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(sizeof(int) * taille);
    
    for (int i = 0; i < taille; ++i) {
        nb.Tdigits[i] = 0;
    }
    
    return nb;
}


// Libère la mémoire d'un BigBinary

void libereBigBinary(BigBinary *nb) {
    if (nb->Tdigits != NULL) {
        free(nb->Tdigits);
    }
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}

// Affiche un BigBinary

void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf("-");
    
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0\n");
        return;
    }
    
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);
    }
    printf("\n");
}

// Crée un BigBinary depuis une chaîne binaire

BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.Taille = 0;
    
    // Compter les bits valides
    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Taille++;
        }
    }
    
    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = +1;
    int index = 0;
    int tousZeros = 1;

    // Remplir le tableau
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

// OPÉRATIONS ARITHMÉTIQUES

/*
 * Addition : A + B
 * Restriction : A, B positifs ou nuls
 */
BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    // Cas spéciaux
    if (A.Signe == 0) {
        BigBinary result = initBigBinary(B.Taille, B.Signe);
        for (int i = 0; i < B.Taille; i++) {
            result.Tdigits[i] = B.Tdigits[i];
        }
        return result;
    }
    
    if (B.Signe == 0) {
        BigBinary result = initBigBinary(A.Taille, A.Signe);
        for (int i = 0; i < A.Taille; i++) {
            result.Tdigits[i] = A.Tdigits[i];
        }
        return result;
    }
    
    // Addition de droite à gauche
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary result = initBigBinary(maxTaille + 1, 1);
    int carry = 0;
    
    for (int i = 0; i < maxTaille; i++) {
        int bitA = (i < A.Taille) ? A.Tdigits[A.Taille - 1 - i] : 0;
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        
        int sum = bitA + bitB + carry;
        result.Tdigits[maxTaille - i] = sum % 2;
        carry = sum / 2;
    }
    result.Tdigits[0] = carry;
    
    // Supprimer les zéros non significatifs
    int firstOne = 0;
    while (firstOne < result.Taille && result.Tdigits[firstOne] == 0) {
        firstOne++;
    }
    
    if (firstOne == result.Taille) {
        libereBigBinary(&result);
        return initBigBinary(0, 0);
    }
    
    BigBinary finalResult = initBigBinary(result.Taille - firstOne, 1);
    for (int i = 0; i < finalResult.Taille; i++) {
        finalResult.Tdigits[i] = result.Tdigits[firstOne + i];
    }
    
    libereBigBinary(&result);
    return finalResult;
}

/*
 * Soustraction : A - B
 * Restriction : A, B positifs et A >= B
 */
BigBinary soustractionBigBinary(BigBinary A, BigBinary B) {
    // Cas spéciaux
    if (B.Signe == 0) {
        BigBinary result = initBigBinary(A.Taille, A.Signe);
        for (int i = 0; i < A.Taille; i++) {
            result.Tdigits[i] = A.Tdigits[i];
        }
        return result;
    }
    
    if (A.Signe == 0) {
        return initBigBinary(0, 0);
    }
    
    // Soustraction de droite à gauche
    BigBinary result = initBigBinary(A.Taille, 1);
    int borrow = 0;
    
    for (int i = 0; i < A.Taille; i++) {
        int bitA = A.Tdigits[A.Taille - 1 - i];
        int bitB = (i < B.Taille) ? B.Tdigits[B.Taille - 1 - i] : 0;
        
        int diff = bitA - bitB - borrow;
        
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.Tdigits[A.Taille - 1 - i] = diff;
    }
    
    // Supprimer les zéros non significatifs
    int firstOne = 0;
    while (firstOne < result.Taille && result.Tdigits[firstOne] == 0) {
        firstOne++;
    }
    
    if (firstOne == result.Taille) {
        libereBigBinary(&result);
        return initBigBinary(0, 0);
    }
    
    BigBinary finalResult = initBigBinary(result.Taille - firstOne, 1);
    for (int i = 0; i < finalResult.Taille; i++) {
        finalResult.Tdigits[i] = result.Tdigits[firstOne + i];
    }
    
    libereBigBinary(&result);
    return finalResult;
}

// COMPARAISONS

// Vérifie si A == B

bool egalBigBinary(BigBinary A, BigBinary B) {
    if (A.Signe != B.Signe) return false;
    if (A.Signe == 0 && B.Signe == 0) return true;
    if (A.Taille != B.Taille) return false;
    
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    }
    
    return true;
}

// Vérifie si A < B

bool inferieurBigBinary(BigBinary A, BigBinary B) {
    if (A.Signe < B.Signe) return true;
    if (A.Signe > B.Signe) return false;
    if (A.Signe == 0 && B.Signe == 0) return false;
    
    bool resultat;
    
    if (A.Taille < B.Taille) {
        resultat = true;
    } else if (A.Taille > B.Taille) {
        resultat = false;
    } else {
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
    
    if (A.Signe == -1) resultat = !resultat;
    
    return resultat;
}

//test