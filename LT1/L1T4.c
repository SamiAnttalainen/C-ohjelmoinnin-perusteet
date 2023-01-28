#include <stdio.h>
int main(void) {
    char Merkki[1];
    char Merkkijono[20];
    printf("Anna merkki: ");
    scanf("%s", Merkki);
    printf("Annoit merkin '%s'.\n", Merkki);
    printf("Anna korkeintaan 20 merkkiä pitkä merkkijono: ");
    scanf("%s", Merkkijono);
    printf("Annoit merkkijonon '%s'.\n", Merkkijono);
    return(0);

}