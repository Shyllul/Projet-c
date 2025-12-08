/**
 * @file bigbinary.h
 * @brief Bibliothèque pour la manipulation de grands nombres binaires
 * 
 * Structure BigBinary : représente un entier binaire de taille arbitraire
 * avec gestion du signe.
 */

#ifndef BIGBINARY_H
#define BIGBINARY_H

#include <stdbool.h>

#define BASE 2

/* ============================================================================
 * STRUCTURE
 * ============================================================================ */

typedef struct {
    int *Tdigits;   // Tableau de bits (MSB à gauche, LSB à droite)
    int Taille;     // Nombre de bits significatifs
    int Signe;      // +1 (positif), -1 (négatif), 0 (nul)
} BigBinary;

/* ============================================================================
 * FONCTIONS DE BASE
 * ============================================================================ */

// Initialise un BigBinary vide (tout à zéro)
BigBinary initBigBinary(int taille, int signe);

// Libère la mémoire allouée pour un BigBinary
void libereBigBinary(BigBinary *nb);

// Libère plusieurs BigBinary d'un coup
void libereMultipleBigBinary(BigBinary *tableau[], int taille);

// Affiche un BigBinary sur la sortie standard
void afficheBigBinary(BigBinary nb);

// Crée un BigBinary à partir d'une chaîne binaire (ex: "1010")
BigBinary creerBigBinaryDepuisChaine(const char *chaine);

// Crée une copie d'un BigBinary
BigBinary copieBigBinary(BigBinary A);

/* ============================================================================
 * OPÉRATIONS ARITHMÉTIQUES (Phase 1)
 * ============================================================================ */

// Addition : A + B (A, B positifs ou nuls)
BigBinary additionBigBinary(BigBinary A, BigBinary B);

// Soustraction : A - B (A >= B, positifs)
BigBinary soustractionBigBinary(BigBinary A, BigBinary B);

/* ============================================================================
 * COMPARAISONS (Phase 1)
 * ============================================================================ */

// Egal(A, B) : renvoit true si A == B, sinon false
bool Egal(BigBinary A, BigBinary B);

// Inferieur(A, B) : renvoit true si A < B, sinon false
bool Inferieur(BigBinary A, BigBinary B);

/* ============================================================================
 * FONCTIONS AVANCÉES (Phase 2)
 * ============================================================================ */

// PGCD avec l'algorithme binaire d'Euclide
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B);

// Modulo : A mod B
BigBinary BigBinary_mod(BigBinary A, BigBinary B);

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

// Vérifie si un BigBinary est pair
bool estPair(BigBinary A);

// Décalage à droite (division par 2)
BigBinary decalageDroite(BigBinary A);

// Décalage à gauche (multiplication par 2)
BigBinary decalageGauche(BigBinary A);

#endif // BIGBINARY_H