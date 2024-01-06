// Tekijä: Sami Anttalainen
// Päivämäärä: 27.2.2023
// Tehtävä: L7T2
// Tiedosto: L7T2.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L7T2Kirjasto.h"
#define KOKO 30


int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Et antanut tarpeeksi parametreja.\n");
        exit(0);
    }

    if (argc > 2) {
        printf("Annoit liikaa parametreja.\n");
        exit(0);
    }

    int iTulos = atoi(argv[1]), iValinta, iLisatty = 0, iLuettu = 0;
    LASKUT *pAlku = NULL;
    char aTiedostoNimi[KOKO];
    printf("Annoit luvun %d.\n", iTulos);

    do {
        iValinta = valikko();

        if (iValinta == 1) {
            pAlku = lisaaLukuun(pAlku, iTulos, &iTulos);
            iLisatty = 1;
        }

        else if (iValinta == 2) {
            if (iLisatty == 0 && iLuettu == 0) {
                printf("\n");
                printf("Ei kirjoitettavia tietoja.\n");
            }
            else {
                printf("\n");
                annaTiedostoNimi(aTiedostoNimi, "kirjoitettavan");
                pAlku = kirjoitaTiedosto(pAlku, aTiedostoNimi);
            }

        }

        else if (iValinta == 3) {
            if (iLuettu == 0 && iLisatty == 1) {
                printf("\n");
                annaTiedostoNimi(aTiedostoNimi, "luettavan");
                pAlku = lueTiedosto(pAlku, aTiedostoNimi);
                iLuettu = 1;
            }

            else if (iLuettu == 0 && iLisatty == 0) {
                printf("\n");
                annaTiedostoNimi(aTiedostoNimi, "luettavan");
                pAlku = lueTiedosto(pAlku, aTiedostoNimi);
                iLuettu = 1;
            }

            else {
                printf("\n");
                pAlku = vapautaMuisti(pAlku);
                annaTiedostoNimi(aTiedostoNimi, "luettavan");
                pAlku = lueTiedosto(pAlku, aTiedostoNimi);
                iLuettu = 1;
            }
        }

        else if (iValinta == 4) {
            if (pAlku == NULL) {
                printf("\n");
                printf("Historiassa ei ole poistettavaa.\n");
            }
            else {
                pAlku = poistaViimeinen(pAlku, &iTulos);
            }
        }
        else if (iValinta == 0) {
            printf("\n");
            printf("Lopetetaan.\n");
        }

        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");

    } while (iValinta != 0);

    pAlku = vapautaMuisti(pAlku);
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

