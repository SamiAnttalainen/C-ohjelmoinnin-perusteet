// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 30.1.2023
// Tehtävä: L3T1.c

#include <stdio.h>

float laskeAla(float fLuku1, float fLuku2);

int main(void) {
    float fKanta, fKorkeus, fTulos;
    printf("Tämä ohjelma laskee suorakulmion pinta-alan.\n");
    printf("Anna suorakulmion kanta: ");
    scanf("%f", &fKanta);
    printf("Anna suorakulmion korkeus: ");
    scanf("%f", &fKorkeus);

    fTulos = laskeAla(fKanta, fKorkeus);
    printf("Suorakulmion pinta-ala on %.2f.\n", fTulos);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

float laskeAla(float fLuku1, float fLuku2) {
    float fTulos;
    fTulos = fLuku1 * fLuku2;
    return fTulos;
}

// eof //