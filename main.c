#include "bigbinary.h"
#include <stdio.h>

/* ============================================================================
 * PROGRAMME PRINCIPAL
 * ============================================================================ */

int main() {
    printf("=== TESTS DE LA BIBLIOTHEQUE BIGBINARY ===\n\n");

    /* ------------------------------------------------------------------------
     * TEST 1 : Création et Affichage
     * ------------------------------------------------------------------------ */
    printf("TEST 1 : Creation et Affichage\n\n");
    
    BigBinary nb1 = creerBigBinaryDepuisChaine("1010011");  // 83
    printf("  nb1 (83) : ");
    afficheBigBinary(nb1);
    
    BigBinary zero = initBigBinary(0, 0);
    printf("  zero     : ");
    afficheBigBinary(zero);
    
    BigBinary neg = creerBigBinaryDepuisChaine("111");  // 7
    neg.Signe = -1;
    printf("  neg (-7) : ");
    afficheBigBinary(neg);

    /* ------------------------------------------------------------------------
     * TEST 2 : Addition
     * ------------------------------------------------------------------------ */
    printf("\nTEST 2 : Addition\n\n");
    
    BigBinary nb2 = creerBigBinaryDepuisChaine("1011");  // 11
    printf("  83 + 11 = ");
    BigBinary sum1 = additionBigBinary(nb1, nb2);
    afficheBigBinary(sum1);
    printf("  (attendu: 1011110 = 94)\n\n");
    
    BigBinary nb3 = creerBigBinaryDepuisChaine("1111");  // 15
    BigBinary nb4 = creerBigBinaryDepuisChaine("1");     // 1
    printf("  15 + 1 = ");
    BigBinary sum2 = additionBigBinary(nb3, nb4);
    afficheBigBinary(sum2);
    printf("  (attendu: 10000 = 16)\n");

    /* ------------------------------------------------------------------------
     * TEST 3 : Soustraction
     * ------------------------------------------------------------------------ */
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
    printf("  (attendu: 101 = 5)\n");

    /* ------------------------------------------------------------------------
     * TEST 4 : Comparaisons (Egal et Inferieur)
     * ------------------------------------------------------------------------ */
    printf("\nTEST 4 : Comparaisons\n\n");
    
    BigBinary nb7 = creerBigBinaryDepuisChaine("101");  // 5
    BigBinary nb8 = creerBigBinaryDepuisChaine("101");  // 5
    
    printf("  Egal(5, 5)   ? %s\n", Egal(nb7, nb8) ? "[OK] true" : "[X] false");
    printf("  Egal(5, 11)  ? %s\n", !Egal(nb7, nb2) ? "[OK] false" : "[X] true");
    printf("  Inferieur(5, 11) ? %s\n", Inferieur(nb7, nb2) ? "[OK] true" : "[X] false");
    printf("  Inferieur(11, 5) ? %s\n", !Inferieur(nb2, nb7) ? "[OK] false" : "[X] true");

    /* ------------------------------------------------------------------------
     * TEST 5 : BigBinary_mod (Modulo)
     * ------------------------------------------------------------------------ */
    printf("\nTEST 5 : BigBinary_mod\n\n");
    
    BigBinary mod1 = creerBigBinaryDepuisChaine("1011");   // 11
    BigBinary mod2 = creerBigBinaryDepuisChaine("11");     // 3
    printf("  11 mod 3 = ");
    BigBinary reste1 = BigBinary_mod(mod1, mod2);
    afficheBigBinary(reste1);
    printf("  (attendu: 10 = 2)\n\n");
    
    BigBinary mod3 = creerBigBinaryDepuisChaine("10100");  // 20
    BigBinary mod4 = creerBigBinaryDepuisChaine("110");    // 6
    printf("  20 mod 6 = ");
    BigBinary reste2 = BigBinary_mod(mod3, mod4);
    afficheBigBinary(reste2);
    printf("  (attendu: 10 = 2)\n\n");
    
    printf("  11 mod 20 = ");
    BigBinary reste3 = BigBinary_mod(mod1, mod3);
    afficheBigBinary(reste3);
    printf("  (attendu: 1011 = 11)\n");

    /* ------------------------------------------------------------------------
     * TEST 6 : BigBinary_PGCD (Algorithme binaire d'Euclide)
     * ------------------------------------------------------------------------ */
    printf("\nTEST 6 : BigBinary_PGCD\n\n");
    
    BigBinary pgcd1 = creerBigBinaryDepuisChaine("110000");  // 48
    BigBinary pgcd2 = creerBigBinaryDepuisChaine("10010");   // 18
    printf("  PGCD(48, 18) = ");
    BigBinary gcd1 = BigBinary_PGCD(pgcd1, pgcd2);
    afficheBigBinary(gcd1);
    printf("  (attendu: 110 = 6)\n\n");
    
    BigBinary pgcd3 = creerBigBinaryDepuisChaine("1100100");  // 100
    BigBinary pgcd4 = creerBigBinaryDepuisChaine("101000");   // 40
    printf("  PGCD(100, 40) = ");
    BigBinary gcd2 = BigBinary_PGCD(pgcd3, pgcd4);
    afficheBigBinary(gcd2);
    printf("  (attendu: 10100 = 20)\n\n");
    
    BigBinary pgcd5 = creerBigBinaryDepuisChaine("10101");   // 21
    BigBinary pgcd6 = creerBigBinaryDepuisChaine("1110");    // 14
    printf("  PGCD(21, 14) = ");
    BigBinary gcd3 = BigBinary_PGCD(pgcd5, pgcd6);
    afficheBigBinary(gcd3);
    printf("  (attendu: 111 = 7)\n");

    /* ------------------------------------------------------------------------
     * Libération de la mémoire
     * ------------------------------------------------------------------------ */
    printf("\n=== NETTOYAGE DE LA MEMOIRE ===\n");
    
    BigBinary *aLiberer[] = {
        &nb1, &nb2, &nb3, &nb4, &nb5, &nb6, &nb7, &nb8,
        &zero, &neg, &sum1, &sum2, &diff1, &diff2,
        &mod1, &mod2, &mod3, &mod4, &reste1, &reste2, &reste3,
        &pgcd1, &pgcd2, &pgcd3, &pgcd4, &pgcd5, &pgcd6, &gcd1, &gcd2, &gcd3
    };
    
    libereMultipleBigBinary(aLiberer, sizeof(aLiberer) / sizeof(aLiberer[0]));
    
    printf("[OK] Memoire liberee avec succes\n\n");
    printf("=== FIN DES TESTS ===\n");
    
    return 0;
}