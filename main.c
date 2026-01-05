#include "bigbinary.h"
#include <stdio.h>

int main() {
    unsigned long long a, b;
    
    printf("=== TESTS BIGBINARY - SAISIE INTERACTIVE ===\n\n");
    
    // ========== TEST ADDITION ==========
    printf("--- TEST ADDITION ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A1 = creerBigBinaryDepuisDecimal(a);
    BigBinary B1 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A1);
    printf("B = %llu = ", b);
    afficheBigBinary(B1);
    
    BigBinary somme = additionBigBinary(A1, B1);
    printf("A + B = ");
    afficheBigBinary(somme);
    printf("       (%llu)\n", bigBinaryVersDecimal(somme));
    
    libereBigBinary(&A1);
    libereBigBinary(&B1);
    libereBigBinary(&somme);
    
    // ========== TEST SOUSTRACTION ==========
    printf("\n--- TEST SOUSTRACTION ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A2 = creerBigBinaryDepuisDecimal(a);
    BigBinary B2 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A2);
    printf("B = %llu = ", b);
    afficheBigBinary(B2);
    
    BigBinary diff = soustractionBigBinary(A2, B2);
    printf("A - B = ");
    afficheBigBinary(diff);
    printf("       (%llu)\n", bigBinaryVersDecimal(diff));
    
    libereBigBinary(&A2);
    libereBigBinary(&B2);
    libereBigBinary(&diff);
    
    // ========== TEST COMPARAISONS ==========
    printf("\n--- TEST COMPARAISONS ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A3 = creerBigBinaryDepuisDecimal(a);
    BigBinary B3 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A3);
    printf("B = %llu = ", b);
    afficheBigBinary(B3);
    
    printf("Egal(A, B) = %s\n", Egal(A3, B3) ? "true" : "false");
    printf("Inferieur(A, B) = %s\n", Inferieur(A3, B3) ? "true" : "false");
    
    libereBigBinary(&A3);
    libereBigBinary(&B3);
    
    // ========== TEST PGCD ==========
    printf("\n--- TEST PGCD ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A4 = creerBigBinaryDepuisDecimal(a);
    BigBinary B4 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A4);
    printf("B = %llu = ", b);
    afficheBigBinary(B4);
    
    BigBinary pgcd = BigBinary_PGCD(A4, B4);
    printf("PGCD(A, B) = ");
    afficheBigBinary(pgcd);
    printf("            (%llu)\n", bigBinaryVersDecimal(pgcd));
    
    libereBigBinary(&A4);
    libereBigBinary(&B4);
    libereBigBinary(&pgcd);
    
    // ========== TEST MODULO ==========
    printf("\n--- TEST MODULO ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A5 = creerBigBinaryDepuisDecimal(a);
    BigBinary B5 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A5);
    printf("B = %llu = ", b);
    afficheBigBinary(B5);
    
    BigBinary mod = BigBinary_mod(A5, B5);
    printf("A mod B = ");
    afficheBigBinary(mod);
    printf("         (%llu)\n", bigBinaryVersDecimal(mod));
    
    libereBigBinary(&A5);
    libereBigBinary(&B5);
    libereBigBinary(&mod);
    
    // ========== TEST MULTIPLICATION ==========
    printf("\n--- TEST MULTIPLICATION ---\n");
    printf("Entrez le premier nombre (A): ");
    scanf("%llu", &a);
    printf("Entrez le deuxieme nombre (B): ");
    scanf("%llu", &b);
    
    BigBinary A6 = creerBigBinaryDepuisDecimal(a);
    BigBinary B6 = creerBigBinaryDepuisDecimal(b);
    
    printf("A = %llu = ", a);
    afficheBigBinary(A6);
    printf("B = %llu = ", b);
    afficheBigBinary(B6);
    
    BigBinary produit = BigBinary_mult(A6, B6);
    printf("A * B = ");
    afficheBigBinary(produit);
    printf("       (%llu)\n", bigBinaryVersDecimal(produit));
    
    libereBigBinary(&A6);
    libereBigBinary(&B6);
    libereBigBinary(&produit);
    
    // ========== TEST EXPONENTIATION MODULAIRE ==========
    printf("\n--- TEST EXPONENTIATION MODULAIRE ---\n");
    unsigned int exp;
    unsigned long long m;
    printf("Entrez M (base): ");
    scanf("%llu", &m);
    printf("Entrez l'exposant: ");
    scanf("%u", &exp);
    printf("Entrez le modulo: ");
    scanf("%llu", &b);
    
    BigBinary M = creerBigBinaryDepuisDecimal(m);
    BigBinary modExp = creerBigBinaryDepuisDecimal(b);
    
    printf("M = %llu = ", m);
    afficheBigBinary(M);
    printf("Exposant = %u\n", exp);
    printf("Modulo = %llu = ", b);
    afficheBigBinary(modExp);
    
    BigBinary expResult = BigBinary_expMod(M, exp, modExp);
    printf("M^%u mod %llu = ", exp, b);
    afficheBigBinary(expResult);
    printf("              (%llu)\n", bigBinaryVersDecimal(expResult));
    
    libereBigBinary(&M);
    libereBigBinary(&modExp);
    libereBigBinary(&expResult);
    
    printf("\n=== FIN DES TESTS ===\n");
    
    return 0;
}