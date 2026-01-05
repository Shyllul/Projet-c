#define BIGBINARY_H
#define BASE 2
#include <stdio.h>
#include <stdbool.h>

// Structure représentant un grand nombre binaire
typedef struct {
    int *Tdigits;  // Tableau des chiffres binaires (0 ou 1)
    int Taille;    // Nombre de chiffres
    int Signe;     // 1 = positif, -1 = négatif, 0 = zéro
} BigBinary;

//Création et gestion mémoire
BigBinary createBigBinary(int size);
void libereBigBinary(BigBinary *nb);
void afficheBigBinary(BigBinary nb);
BigBinary creerBigBinaryDepuisChaine(const char *chaine);

//Conversion décimale binaire
BigBinary creerBigBinaryDepuisDecimal(unsigned long long nombre);
unsigned long long bigBinaryVersDecimal(BigBinary nb);

//Opérations arithmétiques de base
BigBinary additionBigBinary(BigBinary A, BigBinary B);
BigBinary soustractionBigBinary(BigBinary A, BigBinary B);

//Comparaisons
bool Egal(BigBinary A, BigBinary B);
bool Inferieur(BigBinary A, BigBinary B);

//Opérations avancées
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B);
BigBinary BigBinary_mod(BigBinary A, BigBinary B);
BigBinary BigBinary_mult(BigBinary A, BigBinary B);
BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod);