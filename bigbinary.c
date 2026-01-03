#include "bigbinary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PHASE 1 : FONCTIONS DE BASE

// Crée un BigBinary vide avec une taille donnée
BigBinary createBigBinary(int size) {
    BigBinary bb;
    bb.Tdigits = malloc(sizeof(int) * size);
    bb.Taille = size;
    bb.Signe = 0;  // Par défaut nul
    return bb;
}

// Création depuis une chaîne de caractères
BigBinary creerBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int longueurChaine = strlen(chaine);
    nb.Taille = 0;

    // Comptons uniquement les caractères valides (’0’ ou ’1’)
    for (int i = 0; i < longueurChaine; i++) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Taille = nb.Taille + 1;
        }
    }

    nb.Tdigits = malloc(sizeof(int) * nb.Taille);
    nb.Signe = 1;  
    int index = 0;
    int tousZeros = 1; 

    for (int i = 0; i < nb.Taille; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            nb.Tdigits[index] = chaine[i] - '0';
            if (nb.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }

    if (tousZeros) nb.Signe = 0;
    
    return nb;
}

// Affichage du nombre binaire
void afficheBigBinary(BigBinary nb) {
    if (nb.Signe == -1) printf(" -");
    if (nb.Signe == 0 || nb.Taille == 0) {
        printf(" 0\n ") ;
        return ;
    }   
    for ( int i = 0; i < nb . Taille ; ++ i ) {
        printf ( " % d " , nb . Tdigits [ i ]) ;
    }
    printf ( "\n" ) ;
}

// Libération de la mémoire
void libereBigBinary(BigBinary *nb) {
    free(nb->Tdigits);
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}


// ADDITION : A + B

BigBinary additionBigBinary(BigBinary A, BigBinary B) {
    
    // Étape 1 : Trouver la taille du plus grand nombre
    int maxTaille;
    if (A.Taille > B.Taille) {
        maxTaille = A.Taille;
    } else {
        maxTaille = B.Taille;
    }
    
    // Étape 2 : Créer le résultat (on prend maxTaille + 1 pour la retenue possible)
    BigBinary resultat = createBigBinary(maxTaille + 1);
    resultat.Signe = 1;
    
    // Étape 3 : Additionner bit par bit, de droite à gauche
    int retenue = 0;
    
    for (int i = 0; i < maxTaille; i++) {
        // Récupérer le bit de A (en partant de la droite)
        int bitA;
        if (i < A.Taille) {
            bitA = A.Tdigits[A.Taille - 1 - i];  // On lit de droite à gauche
        } else {
            bitA = 0;  // Si A est plus court, on met 0
        }
        
        // Récupérer le bit de B (en partant de la droite)
        int bitB;
        if (i < B.Taille) {
            bitB = B.Tdigits[B.Taille - 1 - i];
        } else {
            bitB = 0;
        }
        
        // Calculer la somme : bit de A + bit de B + retenue
        int somme = bitA + bitB + retenue;
        
        // En binaire : 0+0=0, 0+1=1, 1+0=1, 1+1=10 (donc 0 avec retenue 1)
        // Le bit du résultat est le reste de la division par 2
        if (somme == 0) {
            resultat.Tdigits[maxTaille - i] = 0;
            retenue = 0;
        }
        else if (somme == 1) {
            resultat.Tdigits[maxTaille - i] = 1;
            retenue = 0;
        }
        else if (somme == 2) {
            resultat.Tdigits[maxTaille - i] = 0;
            retenue = 1;
        }
        else if (somme == 3) {
            resultat.Tdigits[maxTaille - i] = 1;
            retenue = 1;
        }
    }
    
    // Étape 4 : Mettre la retenue finale dans le premier bit
    resultat.Tdigits[0] = retenue;
    
    return resultat;
}

// SOUSTRACTION : A - B
BigBinary soustractionBigBinary(BigBinary A, BigBinary B) {
    
    // Cas spécial 1 : Si B est zéro, le résultat est A
    if (B.Signe == 0) {
        if (A.Signe == 0) {
            // 0 - 0 = 0
            BigBinary zero;
            zero.Tdigits = NULL;
            zero.Taille = 0;
            zero.Signe = 0;
            return zero;
        }
        // A - 0 = A (on fait une copie)
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Cas spécial 2 : Si A est zéro, le résultat est -B
    if (A.Signe == 0) {
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = -1;  // Négatif car 0 - B = -B
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    // Cas spécial 3 : Si A < B, on calcule B - A et on met le signe négatif
    if (Inferieur(A, B)) {
        BigBinary resultat = soustractionBigBinary(B, A);
        resultat.Signe = -1;
        return resultat;
    }
    
    // Cas normal : A >= B, on fait la soustraction classique
    BigBinary resultat = createBigBinary(A.Taille);
    resultat.Signe = 1;
    int emprunt = 0;
    
    // Soustraire bit par bit, de droite à gauche
    for (int i = 0; i < A.Taille; i++) {
        // Récupérer le bit de A
        int bitA = A.Tdigits[A.Taille - 1 - i];
        
        // Récupérer le bit de B
        int bitB;
        if (i < B.Taille) {
            bitB = B.Tdigits[B.Taille - 1 - i];
        } else {
            bitB = 0;
        }
        
        // Calculer la différence
        int diff = bitA - bitB - emprunt;
        
        // Si la différence est négative, on emprunte
        if (diff < 0) {
            diff = diff + 2;  // En binaire, on emprunte 2
            emprunt = 1;
        } else {
            emprunt = 0;
        }
        
        resultat.Tdigits[A.Taille - 1 - i] = diff;
    }
    
    return resultat;
}

// COMPARAISON : A == B ?

bool Egal(BigBinary A, BigBinary B) {
    
    // Si les signes sont différents, les nombres ne sont pas égaux
    if (A.Signe != B.Signe) {
        return false;
    }
    
    // Si les deux nombres sont zéro, ils sont égaux
    if (A.Signe == 0 && B.Signe == 0) {
        return true;
    }
    
    // Trouver le premier bit non-nul de A (ignorer les zéros en tête)
    int debutA = 0;
    while (debutA < A.Taille && A.Tdigits[debutA] == 0) {
        debutA = debutA + 1;
    }
    
    // Trouver le premier bit non-nul de B
    int debutB = 0;
    while (debutB < B.Taille && B.Tdigits[debutB] == 0) {
        debutB = debutB + 1;
    }
    
    // Calculer les tailles effectives (sans les zéros en tête)
    int tailleA = A.Taille - debutA;
    int tailleB = B.Taille - debutB;
    
    // Si les tailles effectives sont différentes, pas égaux
    if (tailleA != tailleB) {
        return false;
    }
    
    // Comparer les bits un par un
    for (int i = 0; i < tailleA; i++) {
        if (A.Tdigits[debutA + i] != B.Tdigits[debutB + i]) {
            return false;
        }
    }
    
    return true;
}

// COMPARAISON : A < B ?
bool Inferieur(BigBinary A, BigBinary B) {
    
    // Comparer d'abord les signes
    // -1 < 0 < 1, donc si A.Signe < B.Signe, alors A < B
    if (A.Signe < B.Signe) {
        return true;
    }
    if (A.Signe > B.Signe) {
        return false;
    }
    
    // Si les deux sont zéro, A n'est pas inférieur à B
    if (A.Signe == 0 && B.Signe == 0) {
        return false;
    }
    
    // Trouver le premier bit non-nul de A
    int debutA = 0;
    while (debutA < A.Taille && A.Tdigits[debutA] == 0) {
        debutA = debutA + 1;
    }
    
    // Trouver le premier bit non-nul de B
    int debutB = 0;
    while (debutB < B.Taille && B.Tdigits[debutB] == 0) {
        debutB = debutB + 1;
    }
    
    // Calculer les tailles effectives
    int tailleA = A.Taille - debutA;
    int tailleB = B.Taille - debutB;
    
    // En binaire, un nombre avec plus de bits est plus grand
    bool resultat;
    
    if (tailleA < tailleB) {
        // A a moins de bits, donc A < B
        resultat = true;
    }
    else if (tailleA > tailleB) {
        // A a plus de bits, donc A > B
        resultat = false;
    }
    else {
        // Même nombre de bits : comparer bit par bit
        resultat = false;
        for (int i = 0; i < tailleA; i++) {
            if (A.Tdigits[debutA + i] < B.Tdigits[debutB + i]) {
                resultat = true;
                break;  // On a trouvé la réponse, on arrête
            }
            else if (A.Tdigits[debutA + i] > B.Tdigits[debutB + i]) {
                resultat = false;
                break;
            }
            // Si égaux, on continue à comparer
        }
    }
    
    // Si les nombres sont négatifs, on inverse le résultat
    // Car -5 < -3 (mais 5 > 3)
    if (A.Signe == -1) {
        if (resultat == true) {
            resultat = false;
        } else {
            resultat = true;
        }
    }
    
    return resultat;
}


// PHASE 2 : FONCTIONS AVANCÉES

// PGCD : Plus Grand Commun Diviseur (algorithme d'Euclide par soustractions)
BigBinary BigBinary_PGCD(BigBinary A, BigBinary B) {
    
    // Cas spécial : Si A == 0, retourner B
    if (A.Signe == 0) {
        if (B.Signe == 0) {
            BigBinary zero;
            zero.Tdigits = NULL;
            zero.Taille = 0;
            zero.Signe = 0;
            return zero;
        }
        // Faire une copie de B
        BigBinary copie = createBigBinary(B.Taille);
        copie.Signe = B.Signe;
        for (int i = 0; i < B.Taille; i++) {
            copie.Tdigits[i] = B.Tdigits[i];
        }
        return copie;
    }
    
    // Cas spécial : Si B == 0, retourner A
    if (B.Signe == 0) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Faire des copies de travail (pour ne pas modifier les originaux)
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) {
        a.Tdigits[i] = A.Tdigits[i];
    }
    
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) {
        b.Tdigits[i] = B.Tdigits[i];
    }
    
    // Algorithme d'Euclide : tant que a != b, soustraire le plus petit du plus grand
    while (Egal(a, b) == false) {
        if (Inferieur(a, b)) {
            // b est plus grand, on fait b = b - a
            BigBinary temp = soustractionBigBinary(b, a);
            libereBigBinary(&b);
            b = temp;
        } else {
            // a est plus grand, on fait a = a - b
            BigBinary temp = soustractionBigBinary(a, b);
            libereBigBinary(&a);
            a = temp;
        }
    }
    
    // Quand a == b, on a trouvé le PGCD
    libereBigBinary(&b);
    return a;
}

// MODULO : A mod B (reste de la division de A par B)
BigBinary BigBinary_mod(BigBinary A, BigBinary B) {
    
    // Cas spécial : division par zéro ou 0 mod B
    if (B.Signe == 0 || A.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Si A < B, le reste est A
    if (Inferieur(A, B)) {
        BigBinary copie = createBigBinary(A.Taille);
        copie.Signe = A.Signe;
        for (int i = 0; i < A.Taille; i++) {
            copie.Tdigits[i] = A.Tdigits[i];
        }
        return copie;
    }
    
    // Copie de travail de A (le reste)
    BigBinary reste = createBigBinary(A.Taille);
    reste.Signe = A.Signe;
    for (int i = 0; i < A.Taille; i++) {
        reste.Tdigits[i] = A.Tdigits[i];
    }
    
    // Division par soustractions avec décalages
    // On décale B vers la gauche pour soustraire plus efficacement
    for (int i = 0; i < A.Taille; i++) {
        int decalage = A.Taille - B.Taille - i;
        
        if (decalage < 0) {
            continue;  // Passer à l'itération suivante
        }
        
        // Créer B décalé (B * 2^decalage)
        // Exemple : si B = 101 et decalage = 2, alors B décalé = 10100
        BigBinary diviseurDecale = createBigBinary(B.Taille + decalage);
        diviseurDecale.Signe = 1;
        
        // Copier les bits de B
        for (int j = 0; j < B.Taille; j++) {
            diviseurDecale.Tdigits[j] = B.Tdigits[j];
        }
        // Ajouter les zéros à droite
        for (int j = B.Taille; j < B.Taille + decalage; j++) {
            diviseurDecale.Tdigits[j] = 0;
        }
        
        // Soustraire tant que le reste est >= diviseur décalé
        while (Inferieur(reste, diviseurDecale) == false) {
            BigBinary nouveauReste = soustractionBigBinary(reste, diviseurDecale);
            libereBigBinary(&reste);
            reste = nouveauReste;
        }
        
        libereBigBinary(&diviseurDecale);
    }
    
    return reste;
}

// MULTIPLICATION : A * B (méthode égyptienne / paysanne russe)
BigBinary BigBinary_mult(BigBinary A, BigBinary B) {
    
    // Si l'un des nombres est zéro, le résultat est zéro
    if (A.Signe == 0 || B.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Déterminer le signe du résultat
    // Positif * Positif = Positif
    // Négatif * Négatif = Positif
    // Positif * Négatif = Négatif
    int signeResultat;
    if (A.Signe == B.Signe) {
        signeResultat = 1;
    } else {
        signeResultat = -1;
    }
    
    // Initialiser le résultat à zéro
    BigBinary resultat;
    resultat.Tdigits = NULL;
    resultat.Taille = 0;
    resultat.Signe = 0;
    
    // Copies de travail
    BigBinary a = createBigBinary(A.Taille);
    a.Signe = 1;
    for (int i = 0; i < A.Taille; i++) {
        a.Tdigits[i] = A.Tdigits[i];
    }
    
    BigBinary b = createBigBinary(B.Taille);
    b.Signe = 1;
    for (int i = 0; i < B.Taille; i++) {
        b.Tdigits[i] = B.Tdigits[i];
    }
    
    // Méthode égyptienne :
    // - Si b est impair, ajouter a au résultat
    // - Doubler a (décalage à gauche)
    // - Diviser b par 2 (décalage à droite)
    // - Répéter jusqu'à b == 0
    
    while (b.Signe != 0) {
        // Vérifier si b est impair (dernier bit = 1)
        int dernierBit = 0;
        if (b.Taille > 0) {
            dernierBit = b.Tdigits[b.Taille - 1];
        }
        
        if (dernierBit == 1) {
            // b est impair, ajouter a au résultat
            BigBinary temp = additionBigBinary(resultat, a);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // Doubler a (ajouter un 0 à droite)
        if (a.Signe != 0) {
            BigBinary tempA = createBigBinary(a.Taille + 1);
            tempA.Signe = a.Signe;
            for (int i = 0; i < a.Taille; i++) {
                tempA.Tdigits[i] = a.Tdigits[i];
            }
            tempA.Tdigits[a.Taille] = 0;  // Ajouter le 0 à droite
            libereBigBinary(&a);
            a = tempA;
        }
        
        // Diviser b par 2 (supprimer le dernier bit)
        if (b.Taille > 1) {
            BigBinary tempB = createBigBinary(b.Taille - 1);
            tempB.Signe = 1;
            for (int i = 0; i < tempB.Taille; i++) {
                tempB.Tdigits[i] = b.Tdigits[i];
            }
            libereBigBinary(&b);
            b = tempB;
        } else {
            // b n'a plus qu'un bit, il devient zéro
            libereBigBinary(&b);
            b.Tdigits = NULL;
            b.Taille = 0;
            b.Signe = 0;
        }
    }
    
    libereBigBinary(&a);
    libereBigBinary(&b);
    
    // Appliquer le signe au résultat
    if (resultat.Signe != 0) {
        resultat.Signe = signeResultat;
    }
    
    return resultat;
}

// EXPONENTIATION MODULAIRE : M^exp mod modulo
// Calcule M puissance exp, modulo un nombre
// Utilise la méthode "square and multiply" pour être efficace
BigBinary BigBinary_expMod(BigBinary M, unsigned int exp, BigBinary mod) {
    
    // Cas spécial : modulo zéro
    if (mod.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // x^0 = 1
    if (exp == 0) {
        BigBinary un = createBigBinary(1);
        un.Signe = 1;
        un.Tdigits[0] = 1;
        return un;
    }
    
    // 0^n = 0
    if (M.Signe == 0) {
        BigBinary zero;
        zero.Tdigits = NULL;
        zero.Taille = 0;
        zero.Signe = 0;
        return zero;
    }
    
    // Initialiser le résultat à 1
    BigBinary resultat = createBigBinary(1);
    resultat.Signe = 1;
    resultat.Tdigits[0] = 1;
    
    // Calculer M mod modulo pour commencer
    BigBinary base = BigBinary_mod(M, mod);
    
    // Méthode "square and multiply" :
    // - Si l'exposant est impair, multiplier le résultat par la base
    // - Élever la base au carré
    // - Diviser l'exposant par 2
    // - Appliquer modulo à chaque étape
    
    while (exp > 0) {
        // Si exp est impair
        if (exp % 2 == 1) {
            // resultat = resultat * base mod modulo
            BigBinary produit = BigBinary_mult(resultat, base);
            BigBinary temp = BigBinary_mod(produit, mod);
            libereBigBinary(&produit);
            libereBigBinary(&resultat);
            resultat = temp;
        }
        
        // Diviser l'exposant par 2
        exp = exp / 2;
        
        // Si on continue, calculer base = base² mod modulo
        if (exp > 0) {
            BigBinary carre = BigBinary_mult(base, base);
            BigBinary tempBase = BigBinary_mod(carre, mod);
            libereBigBinary(&carre);
            libereBigBinary(&base);
            base = tempBase;
        }
    }
    
    libereBigBinary(&base);
    return resultat;
}
