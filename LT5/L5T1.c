// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 13.2.2023
// Tehtävä: L5T1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30

char *varaaMuisti(char *pMuisti);

void annaMerkkijono(char *pOsoite);

int main(void) {
    char aMerkkijono[30];
    char *pMerkkijono;

    pMerkkijono = varaaMuisti(aMerkkijono);
    annaMerkkijono(pMerkkijono);
    printf("Annoit merkkijonon '%s'.\n", pMerkkijono);
    free(pMerkkijono);
    pMerkkijono = NULL;
    printf("Muisti vapautettu.\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);

}

char *varaaMuisti(char *pMuisti) {
    int iMuistiKoko = KOKO;
    if ((pMuisti = (char *)malloc(sizeof(char) * KOKO)) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
    printf("Muisti varattu %d merkille.\n", iMuistiKoko);
    return pMuisti;
}

void annaMerkkijono(char *pOsoite) {
    char aMerkkijono[KOKO];
    printf("Anna merkkijono: ");
    fgets(aMerkkijono, KOKO, stdin);
    aMerkkijono[strlen(aMerkkijono)-1] = '\0';
    strcpy(pOsoite, aMerkkijono);
}