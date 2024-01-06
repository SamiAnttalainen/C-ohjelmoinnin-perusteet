// Tekijä: Sami Anttalainen
// Päivämäärä: 30.1.2023
// Tehtävä: L3T4.c

#include <stdio.h>
#include <stdlib.h>

#define Koko 60

int laskePituus(char *cMerkkijono);

char *yhdistaMerkkijonot(char *cMerkkijono1, char *cMerkkijono2, int i);

int main(void) {
    int iPituus1, iPituus2, iPituus3;
    char cMerkkijono1[Koko], cMerkkijono2[Koko], *cMerkkijono3;
    printf("Anna ensimmäinen merkkijono (max 30 merkkiä): ");
    fgets(cMerkkijono1, 60, stdin);
    //scanf("%s", cMerkkijono1);
    printf("Anna toinen merkkijono (max 30 merkkiä): ");
    fgets(cMerkkijono2, 60, stdin);
    //scanf("%s", cMerkkijono2);
    iPituus1 = laskePituus(cMerkkijono1);
    iPituus2 = laskePituus(cMerkkijono2);
    iPituus3 = iPituus1 + iPituus2;
    if (iPituus3 > 60) {
        printf("Merkkijonojen yhteenlaskettu pituus on liian pitkä ohjelman muistialueelle.\n");
    } else {
        cMerkkijono3 = yhdistaMerkkijonot(cMerkkijono1, cMerkkijono2, iPituus1);
        printf("Yhdistetty merkkijono on:\n");
        printf("'%s'\n", cMerkkijono3);
    }
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}


int laskePituus(char *cMerkkijono) {
    int i;
    for (i=0; cMerkkijono[i] != '\n'; ++i);
    return(i);
}

char *yhdistaMerkkijonot(char *cMerkkijono1, char *cMerkkijono2, int i) {
    int j;
    for (j = 0; cMerkkijono2[j] != '\n'; ++j, ++i) {
        cMerkkijono1[i] = cMerkkijono2[j];
    }
    return cMerkkijono1;
}
