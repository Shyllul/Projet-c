#include "bigbinary.h"
#include <stdio.h>

int main() {

    // TEST 1 : Création et Affichage
    printf("TEST 1 : Creation et Affichage\n\n");
    
    BigBinary nb1 = creerBigBinaryDepuisChaine("1010011");  // 83 en decimal
    printf("  nb1 (83 en decimal) : ");
    afficheBigBinary(nb1);
    
    BigBinary zero = initBigBinary(0, 0);
    printf("  zero : ");
    afficheBigBinary(zero);
    
    BigBinary neg = creerBigBinaryDepuisChaine("111");  // 7 en decimal
    neg.Signe = -1;
    printf("  neg (-7 en decimal) : ");
    afficheBigBinary(neg);

    
    // TEST 2 : Addition
    printf("\nTEST 2 : Addition\n\n");
    
    BigBinary nb2 = creerBigBinaryDepuisChaine("1011");  // 11 en decimal
    printf("  nb1 = 1010011 (83)\n");
    printf("  nb2 = 1011 (11)\n");
    printf("  83 + 11 = ");
    BigBinary sum1 = additionBigBinary(nb1, nb2);
    afficheBigBinary(sum1);
    printf("  (attendu: 1011110 = 94)\n\n");
    
    BigBinary nb3 = creerBigBinaryDepuisChaine("1111");  // 15
    BigBinary nb4 = creerBigBinaryDepuisChaine("1");     // 1
    printf("  15 + 1 = ");
    BigBinary sum2 = additionBigBinary(nb3, nb4);
    afficheBigBinary(sum2);
    printf(" (attendu: 10000 = 16)\n");
    

    // TEST 3 : Soustraction
    printf("\nTEST 3 : Soustraction\n\n");
    
    printf("  83 - 11 = ");
    BigBinary diff1 = soustractionBigBinary(nb1, nb2);
    afficheBigBinary(diff1);
    printf("  (attendu: 1001000 = 72)\n\n");
    
    BigBinary nb5 = creerBigBinaryDepuisChaine("1000");  // 8
    BigBinary nb6 = creerBigBinaryDepuisChaine("11");    // 3
    printf("  8 - 3 = ");
    BigBinary diff2 = soustractionBigBinary(nb5, nb6);
    afficheBigBinary(diff2);
    printf("(attendu: 101 = 5)\n");
    

    // TEST 4 : Égalité
    printf("\nTEST 4 : Comparaison d'Egalite\n\n");
    
    BigBinary nb7 = creerBigBinaryDepuisChaine("101");
    BigBinary nb8 = creerBigBinaryDepuisChaine("101");
    
    printf("  101 == 101 ? %s\n", 
           egalBigBinary(nb7, nb8) ? "[OK] true" : "[X] false");
    
    printf("  101 == 1011 ? %s\n", 
           egalBigBinary(nb7, nb2) ? "[X] true" : "[OK] false");

    // TEST 5 : Comparaison Inférieur
    printf("\nTEST 5 : Comparaison Inferieur (<)\n\n");
    
    printf("  101 (5) < 1011 (11) ? %s\n", 
           inferieurBigBinary(nb7, nb2) ? "[OK] true" : "[X] false");
    
    printf("  1011 (11) < 101 (5) ? %s\n", 
           inferieurBigBinary(nb2, nb7) ? "[X] true" : "[OK] false");
    
    printf("  101 (5) < 101 (5) ? %s\n", 
           inferieurBigBinary(nb7, nb8) ? "[X] true" : "[OK] false");
    

    // Libération mémoire
    printf("\nNettoyage de la memoire\n");
    
    libereBigBinary(&nb1);
    libereBigBinary(&nb2);
    libereBigBinary(&nb3);
    libereBigBinary(&nb4);
    libereBigBinary(&nb5);
    libereBigBinary(&nb6);
    libereBigBinary(&nb7);
    libereBigBinary(&nb8);
    libereBigBinary(&zero);
    libereBigBinary(&neg);
    libereBigBinary(&sum1);
    libereBigBinary(&sum2);
    libereBigBinary(&diff1);
    libereBigBinary(&diff2);
    
    printf("[OK] Memoire liberee avec succes\n");
    
    return 0;
}