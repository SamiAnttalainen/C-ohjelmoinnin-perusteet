// Tekijä: Sami Anttalainen
// Opiskelijanro: 001067291
// Tehtävä L2T4
// Ohjelma alkaa
#include <stdio.h>
#define Pi 3.141

int main(void) {
    int iValinta;
    float fSade, fAla, fKeha;

    printf("Anna ympyrän säde: ");
    scanf("%f", &fSade);
    printf("\n");

    printf("Valikko:\n");
    printf("1) Laske ympyrän kehän pituus\n");
    printf("2) Laske ympyrän pinta-ala\n");
    printf("Valitse: ");
    scanf("%d", &iValinta);

    switch (iValinta)
    {
    case 1:
        fKeha = 2 * Pi * fSade;
        printf("Ympyrän säde on %.3f ja sen kehän pituus %.3f.\n", fSade, fKeha);
        break;

    case 2:
        fAla = Pi * fSade * fSade;
        printf("Ympyrän säde on %.3f ja sen pinta-ala on %.3f.\n", fSade, fAla);
        break;
    
    default:
        printf("Tuntematon valinta.\n");
        break;
    }


    return(0);
}


// Ohjelma päättyy