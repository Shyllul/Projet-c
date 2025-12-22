#include "bigbinary.h"
#include <stdio.h>

// PROGRAMME PRINCIPAL

int main() {
    int val1, val2;
    
    printf("CALCULATRICE BIGBINARY\n\n");
    
    // SAISIE DES 2 NOMBRES DECIMAUX
    printf("Entrez le premier nombre (decimal) : ");
    scanf("%d", &val1);
    
    printf("Entrez le deuxieme nombre (decimal) : ");
    scanf("%d", &val2);
    
    // Création des BigBinary à partir des valeurs décimales
    BigBinary nb1 = creerBigBinaryDepuisEntier(val1);
    BigBinary nb2 = creerBigBinaryDepuisEntier(val2);
    
    printf("\nVALEURS SAISIES\n\n");
    printf("  Nombre 1 : ");
    afficheBigBinaryOctet(nb1);
    printf(" (%d)\n", val1);
    printf("  Nombre 2 : ");
    afficheBigBinaryOctet(nb2);
    printf(" (%d)\n", val2);


    // ADDITION
    printf("\nADDITION\n\n");
    BigBinary somme = additionBigBinary(nb1, nb2);
    printf("  %d + %d = ", val1, val2);
    afficheBigBinaryOctet(somme);
    printf(" (%d)\n", bigBinaryVersEntier(somme));


    // SOUSTRACTION
    printf("\nSOUSTRACTION\n\n");
    BigBinary difference = soustractionBigBinary(nb1, nb2);
    printf("  %d - %d = ", val1, val2);
    afficheBigBinaryOctet(difference);
    printf(" (%d)\n", bigBinaryVersEntier(difference));


    // COMPARAISONS
    printf("\nCOMPARAISONS\n\n");
    printf("  %d == %d ? %s\n", val1, val2, Egal(nb1, nb2) ? "Oui" : "Non");
    printf("  %d < %d  ? %s\n", val1, val2, Inferieur(nb1, nb2) ? "Oui" : "Non");
    printf("  %d > %d  ? %s\n", val1, val2, Inferieur(nb2, nb1) ? "Oui" : "Non");


    // MODULO
    printf("\nMODULO\n\n");
    BigBinary reste = BigBinary_mod(nb1, nb2);
    printf("  %d mod %d = ", val1, val2);
    afficheBigBinaryOctet(reste);
    printf(" (%d)\n", bigBinaryVersEntier(reste));


    // PGCD
    printf("\nPGCD\n\n");
    BigBinary pgcd = BigBinary_PGCD(nb1, nb2);
    printf("  PGCD(%d, %d) = ", val1, val2);
    afficheBigBinaryOctet(pgcd);
    printf(" (%d)\n", bigBinaryVersEntier(pgcd));

    
    // Libération de la mémoire
    printf("\nNETTOYAGE DE LA MEMOIRE\n");
    
    BigBinary *aLiberer[] = {
        &nb1, &nb2, &somme, &difference, &reste, &pgcd
    };
    
    libereMultipleBigBinary(aLiberer, sizeof(aLiberer) / sizeof(aLiberer[0]));
    
    printf("[OK] Memoire liberee avec succes\n\n");
    printf("FIN DES CALCULS\n");
    
    return 0;
}