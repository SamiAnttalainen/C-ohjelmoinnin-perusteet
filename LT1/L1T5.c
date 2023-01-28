#include <stdio.h>
int main(void) {
    char Nimi[30], Rotu[30];
    int Ika;
    float Paino;
    printf("Anna lemmikin nimi: ");
    scanf("%s", Nimi);
    printf("Anna lemmikin rotu: ");
    scanf("%s", Rotu);
    printf("Anna lemmikin ikä: ");
    scanf("%d", &Ika);
    printf("Anna lemmikin paino: ");
    scanf("%f", &Paino);
    printf("Lemmikin nimi on %s ja rotu on %s.\nSen ikä on %d vuotta ja paino %.1f kg.\n", Nimi, Rotu, Ika, Paino);
    return(0);
}