/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Sami Anttalainen
* Opiskelijanumero: 001067291
* Päivämäärä: 2.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTPerus, tiedoston nimi HTPerustaso.c */

#include <stdio.h>
#include <stdlib.h>
#include "HTPerusKirjasto.h"


int main(void) {
    int iValinta;
    char aTiedostoNimi[KOKO];
    TIEDOT *pAlku = NULL;
    TULOKSET *tulosTietue = NULL;

    do {
        iValinta = valikko();

        if (iValinta == 1) {
            annaTiedostoNimi(aTiedostoNimi);

            if (pAlku != NULL) { // Tyhjennetään linkitetty lista, jos se on jo olemassa
                pAlku = vapautaMuisti(pAlku);
                pAlku = lueTiedosto(pAlku, aTiedostoNimi);

            }
            else {
                pAlku = lueTiedosto(pAlku, aTiedostoNimi);
            }
            
        }

        else if (iValinta == 2) {
            if (pAlku != NULL) {
                free(tulosTietue);
                tulosTietue = NULL;
                tulosTietue = analysoiTiedot(pAlku, tulosTietue);
                analysoiSanat(pAlku, tulosTietue);
            }
            else {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
        }

        else if (iValinta == 3) {
            if (tulosTietue != NULL) {
                annaTiedostoNimi(aTiedostoNimi);
                kirjoitaTiedosto(aTiedostoNimi, tulosTietue);
            }

            else {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
            
        }

        else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        }

        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
        
    } while (iValinta != 0);

    free(tulosTietue);
    tulosTietue = NULL;
    pAlku = vapautaMuisti(pAlku); // Palauttaa NULL:n
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

// eof



