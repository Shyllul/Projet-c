#ifndef BIGBINARY_H
#define BIGBINARY_H

#include <stdbool.h>

// STRUCTURE

typedef struct {
    int *Tdigits;  // Tableau de bits (MSB à LSB)
    int Taille;    // Nombre de bits
    int Signe;     // +1, -1, ou 0
} BigBinary;

// Fonctions de Base

BigBinary initBigBinary(int taille, int signe);
void libereBigBinary(BigBinary *nb);
void afficheBigBinary(BigBinary nb);
BigBinary creerBigBinaryDepuisChaine(const char *chaine);

// Opérations Arithmétiques

BigBinary additionBigBinary(BigBinary A, BigBinary B);
BigBinary soustractionBigBinary(BigBinary A, BigBinary B);

// Comparaisons

bool egalBigBinary(BigBinary A, BigBinary B);
bool inferieurBigBinary(BigBinary A, BigBinary B);

#endif