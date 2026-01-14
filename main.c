#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("TESTS BIGBINARY - VERSION LONGUE (200+ bits)\n\n");
    
    //PHASE 1 
    
    //TEST ADDITION : A1 + B1
    printf("TEST ADDITION\n");
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
    
    //TEST COMPARAISONS : A2 == B2, A2 > C2
    printf("\nTEST COMPARAISONS\n");
    BigBinary A2 = creerBigBinaryDepuisChaine("11001110111000001101101111110100110000001010101010001000000110010010001110000100001110010011");
    BigBinary B2 = creerBigBinaryDepuisChaine("10110100101100011101100011110100101110111100000100111000110000001001000100110110100100110000");
    BigBinary C2 = creerBigBinaryDepuisChaine("11100001000100000000100110010110010010100100111011011100001100000110011101101000101010010000");
    
    printf("A2 = ");
    afficheBigBinary(A2);
    printf("B2 = ");
    afficheBigBinary(B2);
    printf("C2 = ");
    afficheBigBinary(C2);
    
    printf("Egal(A2, B2) = %s\n", Egal(A2, B2) ? "true" : "false");
    printf("Inferieur(A2, B2) = %s\n", Inferieur(A2, B2) ? "true" : "false");
    printf("Inferieur(A2, C2) = %s\n", Inferieur(A2, C2) ? "true" : "false");
    printf("Inferieur(C2, A2) = %s (A2 > C2)\n", Inferieur(C2, A2) ? "true" : "false");
    
    libereBigBinary(&A2);
    libereBigBinary(&B2);
    libereBigBinary(&C2);
    
    //PHASE 2 
    
    //TEST PGCD
    printf("\nTEST PGCD\n");
    BigBinary PGCD_A = creerBigBinaryDepuisChaine("11110001111000100111100100001010110100110010110000100111001100110010111001010111101101110");
    BigBinary PGCD_B = creerBigBinaryDepuisChaine("11100110011111011000000111111110110001110000011001111100111011011010101110110111000110111");
    
    printf("PGCD_A = ");
    afficheBigBinary(PGCD_A);
    printf("PGCD_B = ");
    afficheBigBinary(PGCD_B);
    
    BigBinary pgcd = BigBinary_PGCD(PGCD_A, PGCD_B);
    printf("PGCD(A, B) = ");
    afficheBigBinary(pgcd);
    
    libereBigBinary(&PGCD_A);
    libereBigBinary(&PGCD_B);
    libereBigBinary(&pgcd);
    
    //TEST MODULO
    printf("\nTEST MODULO\n");
    BigBinary MOD_A = creerBigBinaryDepuisChaine("11001110000111010001010110000101101001111000010001001110011100110100000110000010011011010");
    BigBinary MOD_B = creerBigBinaryDepuisChaine("11001001100000010001111000000101111110010111111011101010001000010100010001111111010011010");
    
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
    
    //TEST EXPONENTIATION MODULAIRE
    //Valeurs de l'exercice : A^17 mod N = 2
    printf("\nTEST EXPONENTIATION MODULAIRE\n");
    
    //A = 18437032639754944118572129431363063890647413010085012961351793046159338238438
    BigBinary EXP_A = creerBigBinaryDepuisChaine("10100011000010111111011001110010101101100100111110001101000001001111000000110000111010111010111001110001000000000111000100001011110101001111100110111100000110100100110110110010111000101101001011110100011011010110110111100000000110100100111111000111100110");
    //e = 17
    BigBinary EXP_E = creerBigBinaryDepuisChaine("10001");
    //N = 115792089237342390393211096473342943949313232746809673270778931389365205055153
    BigBinary EXP_N = creerBigBinaryDepuisChaine("10000000000000000000000000000000000000000001111111010110100101011011011001011001010111010011000101010011000101010100010100111001000000000000000010010110000101101110001010011010011001001100001111111110111101100000001000100100011010000010001111011011010110001");
    
    printf("A = ");
    afficheBigBinary(EXP_A);
    printf("e = ");
    afficheBigBinary(EXP_E);
    printf("N = ");
    afficheBigBinary(EXP_N);
    
    BigBinary expResult = BigBinary_expMod(EXP_A, EXP_E, EXP_N);
    printf("A^e mod N = ");
    afficheBigBinary(expResult);
    
    libereBigBinary(&EXP_A);
    libereBigBinary(&EXP_E);
    libereBigBinary(&EXP_N);
    libereBigBinary(&expResult);
    
    printf("\nFIN DES TESTS\n");
    
    return 0;
}