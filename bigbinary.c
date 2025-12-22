#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FONCTIONS INTERNES (PRIVÉES)

/**
 * Supprime les zéros non significatifs d'un BigBinary
 * Retourne un nouveau BigBinary normalisé
 */
static BigBinary normaliserBigBinary(BigBinary nb) {
    int premier = 0;
    while (premier < nb.Taille && nb.Tdigits[premier] == 0) {
        premier++;
    }
    
    if (premier == nb.Taille) {
        libereBigBinary(&nb);
        return initBigBinary(0, 0);
    }
    
    if (premier == 0) {
        return nb;
    }
    
    BigBinary resultat = initBigBinary(nb.Taille - premier, 1);
    for (int i = 0; i < resultat.Taille; i++) {
        resultat.Tdigits[i] = nb.Tdigits[premier + i];
    }
    
    libereBigBinary(&nb);
    return resultat;
}

// FONCTIONS DE BASE

BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Taille = taille;
    nb.Signe = signe;
    
    if (taille > 0) {
        nb.Tdigits = malloc(sizeof(int) * taille);
        for (int i = 0; i < taille; i++) {
            nb.Tdigits[i] = 0;
        }
    } else {
        nb.Tdigits = NULL;
    }
    
    return nb;
}

void libereBigBinary(BigBinary *nb) {
    if (nb->Tdigits != NULL) {
        free(nb->Tdigits);
        nb->Tdigits = NULL;
    }
    nb->Taille = 0;
    nb->Signe = 0;
}

void libereMultipleBigBinary(BigBinary *tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        libereBigBinary(tableau[i]);
    }
}

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

BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    int n = strlen(chaine);
    
    int nbBits = 0;
    for (int i = 0; i < n; i++) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nbBits++;
        }
    }
    
    BigBinary nb = initBigBinary(nbBits, 1);
    int index = 0;
    bool tousZeros = true;
    
    for (int i = 0; i < n; i++) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            if (nb.Tdigits[index] == 1) {
                tousZeros = false;
            }
            index++;
        }
    }
    
    if (tousZeros) {
        nb.Signe = 0;
    }
    
    return nb;
}

BigBinary copieBigBinary(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) {
        return initBigBinary(0, 0);
    }
    
    BigBinary copie = initBigBinary(A.Taille, A.Signe);
    for (int i = 0; i < A.Taille; i++) {
        copie.Tdigits[i] = A.Tdigits[i];
    }
    return copie;
}

BigBinary creerBigBinaryDepuisEntier(int valeur) {
    if (valeur == 0) {
        return initBigBinary(0, 0);
    }
    
    int signe = (valeur < 0) ? -1 : 1;
    int val = (valeur < 0) ? -valeur : valeur;
    
    // Compter le nombre de bits nécessaires
    int nbBits = 0;
    int temp = val;
    while (temp > 0) {
        nbBits++;
        temp /= 2;
    }
    
    BigBinary nb = initBigBinary(nbBits, signe);
    
    // Remplir les bits (MSB à gauche)
    for (int i = nbBits - 1; i >= 0; i--) {
        nb.Tdigits[i] = val % 2;
        val /= 2;
    }
    
    return nb;
}

void afficheBigBinaryOctet(BigBinary nb) {
    if (nb.Signe == -1) {
        printf("-");
    }
    
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf("0000 0000");
        return;
    }
    
    // Calculer le nombre de bits nécessaires pour un multiple de 8
    int nbOctets = (nb.Taille + 7) / 8;
    int totalBits = nbOctets * 8;
    int padding = totalBits - nb.Taille;
    
    int bitCount = 0;
    
    // Afficher les zéros de padding
    for (int i = 0; i < padding; i++) {
        printf("0");
        bitCount++;
        if (bitCount % 4 == 0 && bitCount < totalBits) {
            printf(" ");
        }
    }
    
    // Afficher les bits du nombre
    for (int i = 0; i < nb.Taille; i++) {
        printf("%d", nb.Tdigits[i]);
        bitCount++;
        if (bitCount % 4 == 0 && bitCount < totalBits) {
            printf(" ");
        }
    }
}

int bigBinaryVersEntier(BigBinary nb) {
    if (nb.Signe == 0 || nb.Taille == 0) {
        return 0;
    }
    
    int valeur = 0;
    for (int i = 0; i < nb.Taille; i++) {
        valeur = valeur * 2 + nb.Tdigits[i];
    }
    
    return valeur * nb.Signe;
}

// COMPARAISONS (Phase 1)

bool Egal(BigBinary A, BigBinary B) {
    if (A.Signe != B.Signe) return false;
    if (A.Signe == 0 && B.Signe == 0) return true;
    if (A.Taille != B.Taille) return false;
    
    for (int i = 0; i < A.Taille; i++) {
        if (A.Tdigits[i] != B.Tdigits[i]) return false;
    }
    return true;
}

bool Inferieur(BigBinary A, BigBinary B) {
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
    
    if (A.Signe == -1) {
        resultat = !resultat;
    }
    
    return resultat;
}

// FONCTIONS UTILITAIRES

bool estPair(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) return true;
    return A.Tdigits[A.Taille - 1] == 0;
}

BigBinary decalageDroite(BigBinary A) {
    if (A.Signe == 0 || A.Taille <= 1) {
        return initBigBinary(0, 0);
    }
    
    BigBinary resultat = initBigBinary(A.Taille - 1, 1);
    for (int i = 0; i < resultat.Taille; i++) {
        resultat.Tdigits[i] = A.Tdigits[i];
    }
    
    return normaliserBigBinary(resultat);
}

BigBinary decalageGauche(BigBinary A) {
    if (A.Signe == 0 || A.Taille == 0) {
        return initBigBinary(0, 0);
    }
    
    BigBinary resultat = initBigBinary(A.Taille + 1, A.Signe);
    for (int i = 0; i < A.Taille; i++) {
        resultat.Tdigits[i] = A.Tdigits[i];
    }
    resultat.Tdigits[A.Taille] = 0;
    
    return resultat;
}

// OPÉRATIONS ARITHMÉTIQUES (Phase 1)

BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    if (A.Signe == 0) return copieBigBinary(B);
    if (B.Signe == 0) return copieBigBinary(A);
    
    int maxTaille = (A.Taille > B.Taille) ? A.Taille : B.Taille;
    BigBinary resultat = initBigBinary(maxTaille + 1, 1);
    
    int retenue = 0;
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

BigBinary soustractionBigBinary(BigBinary A, BigBinary B) {
    if (B.Signe == 0) return copieBigBinary(A);
    if (A.Signe == 0) {
        BigBinary resultat = copieBigBinary(B);
        resultat.Signe = -1;
        return resultat;
    }
    
    // Si A < B, on calcule B - A et on met le signe négatif
    if (Inferieur(A, B)) {
        BigBinary resultat = soustractionBigBinary(B, A);
        resultat.Signe = -1;
        return resultat;
    }
    
    // Cas normal : A >= B
    BigBinary resultat = initBigBinary(A.Taille, 1);
    int emprunt = 0;
    
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

// FONCTIONS AVANCÉES (Phase 2)

BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    if (B.Signe == 0) {
        printf("Erreur: Modulo par zero!\n");
        return initBigBinary(0, 0);
    }
    
    if (A.Signe == 0) return initBigBinary(0, 0);
    if (Inferieur(A, B)) return copieBigBinary(A);
    if (Egal(A, B)) return initBigBinary(0, 0);
    
    BigBinary reste = copieBigBinary(A);
    
    for (int i = 0; i < A.Taille; i++) {
        int decalage = A.Taille - B.Taille - i;
        if (decalage < 0) continue;
        
        BigBinary diviseurDecale = initBigBinary(B.Taille + decalage, 1);
        for (int j = 0; j < B.Taille; j++) {
            diviseurDecale.Tdigits[j] = B.Tdigits[j];
        }
        
        while (!Inferieur(reste, diviseurDecale)) {
            BigBinary nouveauReste = soustractionBigBinary(reste, diviseurDecale);
            libereBigBinary(&reste);
            reste = nouveauReste;
        }
        
        libereBigBinary(&diviseurDecale);
    }
    
    return reste;
}

BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    if (A.Signe == 0) return copieBigBinary(B);
    if (B.Signe == 0) return copieBigBinary(A);
    if (Egal(A, B)) return copieBigBinary(A);
    
    BigBinary u = copieBigBinary(A);
    BigBinary v = copieBigBinary(B);
    
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
    
    while (estPair(u)) {
        BigBinary temp = decalageDroite(u);
        libereBigBinary(&u);
        u = temp;
    }
    
    while (v.Signe != 0) {
        while (estPair(v)) {
            BigBinary temp = decalageDroite(v);
            libereBigBinary(&v);
            v = temp;
        }
        
        if (Inferieur(v, u)) {
            BigBinary temp = u;
            u = v;
            v = temp;
        }
        
        BigBinary diff = soustractionBigBinary(v, u);
        libereBigBinary(&v);
        v = diff;
    }
    
    BigBinary resultat = copieBigBinary(u);
    libereBigBinary(&u);
    libereBigBinary(&v);
    
    for (int i = 0; i < k; i++) {
        BigBinary temp = decalageGauche(resultat);
        libereBigBinary(&resultat);
        resultat = temp;
    }
    
    return resultat;
}