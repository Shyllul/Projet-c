#include "bigbinary.h"
#include <stdio.h>

int main() {
    printf("TESTS BIGBINARY - DONNEES EXTRAITES DU PDF\n\n");

    // ========== PHASE 1 ==========
    printf("PHASE 1\n\n");
    
    // Test de l'addition
    printf("Test Addition : A1 + B1\n");
    BigBinary A1 = creerBigBinaryDepuisChaine("10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001");
    BigBinary B1 = creerBigBinaryDepuisChaine("11001011011111111000110000111010000000110101011000000100000010110101101001100011110001011000");
    
    printf("A1 = ");
    afficheBigBinary(A1);
    printf("B1 = ");
    afficheBigBinary(B1);
    
    BigBinary somme = additionBigBinary(A1, B1);
    printf("A1 + B1 = ");
    afficheBigBinary(somme);
    
    libereBigBinary(&A1);
    libereBigBinary(&B1);
    libereBigBinary(&somme);
    
    // Test des comparaisons
    printf("\nTest Comparaisons\n");
    BigBinary A2 = creerBigBinaryDepuisChaine("11001110111000001101101111110100110000001010101010001000000110010010001110000100001110010011");
    BigBinary B2 = creerBigBinaryDepuisChaine("1011010010110001110110001111010010111011110000010011100011010000001001000100001001101101001001");
    BigBinary C2 = creerBigBinaryDepuisChaine("1110000100010000000010011001011001001010010011101101110000110000011001110110100010101001");
    
    printf("A2 = ");
    afficheBigBinary(A2);
    printf("B2 = ");
    afficheBigBinary(B2);
    printf("C2 = ");
    afficheBigBinary(C2);
    
    printf("\nEgal(A2, B2) = %s\n", Egal(A2, B2) ? "true" : "false");
    printf("Inferieur(A2, B2) = %s\n", Inferieur(A2, B2) ? "true" : "false");
    printf("Inferieur(C2, A2) = %s (A2 > C2)\n", Inferieur(C2, A2) ? "true" : "false");
    
    libereBigBinary(&A2);
    libereBigBinary(&B2);
    libereBigBinary(&C2);
    
    // ========== PHASE 2 ==========
    printf("\nPHASE 2\n\n");
    
    // Test du PGCD
    printf("Test PGCD\n");
    BigBinary PGCD_A = creerBigBinaryDepuisChaine("1111000111100010011110010000101011010011001011000010100111001100110010111001010111101101110");
    BigBinary PGCD_B = creerBigBinaryDepuisChaine("1110011001111101100000011111111011000111000001100111110011111011011010101110110111000110111");
    
    printf("PGCD_A = ");
    afficheBigBinary(PGCD_A);
    printf("PGCD_B = ");
    afficheBigBinary(PGCD_B);
    
    BigBinary pgcd = BigBinary_PGCD(PGCD_A, PGCD_B);
    printf("PGCD(PGCD_A, PGCD_B) = ");
    afficheBigBinary(pgcd);
    
    libereBigBinary(&PGCD_A);
    libereBigBinary(&PGCD_B);
    libereBigBinary(&pgcd);
    
    // Test du modulo
    printf("\nTest Modulo\n");
    BigBinary MOD_A = creerBigBinaryDepuisChaine("110011100001110100010101100001011010011110000100010011100011100110100000110000010011011010");
    BigBinary MOD_B = creerBigBinaryDepuisChaine("11001001100000010001111000000101111110010111111011101010110010111111011101010001000010100010001111111010011010");
    
    printf("MOD_A = ");
    afficheBigBinary(MOD_A);
    printf("MOD_B = ");
    afficheBigBinary(MOD_B);
    
    BigBinary mod = BigBinary_mod(MOD_A, MOD_B);
    printf("MOD_A mod MOD_B = ");
    afficheBigBinary(mod);
    
    libereBigBinary(&MOD_A);
    libereBigBinary(&MOD_B);
    libereBigBinary(&mod);
    
    // Test de l'exponentiation modulaire
    printf("\nTest Exponentiation Modulaire\n");
    BigBinary EXP_M = creerBigBinaryDepuisChaine("101100110000001100011011000000110010011101100100101001010111010010001011110110001001101100");
    unsigned int EXP_EXP = 37399;
    BigBinary EXP_MOD = creerBigBinaryDepuisChaine("101001110001111101100000111000110001110100000111111010001011100101101100101101101011000");
    
    printf("EXP_M = ");
    afficheBigBinary(EXP_M);
    printf("EXP_EXP = %u\n", EXP_EXP);
    printf("EXP_MOD = ");
    afficheBigBinary(EXP_MOD);
    
    BigBinary exp_result = BigBinary_expMod(EXP_M, EXP_EXP, EXP_MOD);
    printf("EXP_M ^ EXP_EXP mod EXP_MOD = ");
    afficheBigBinary(exp_result);
    
    libereBigBinary(&EXP_M);
    libereBigBinary(&EXP_MOD);
    libereBigBinary(&exp_result);
    
    printf("\nFIN DES TESTS\n");
    
    return 0;
}