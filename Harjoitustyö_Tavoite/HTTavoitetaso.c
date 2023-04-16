/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Sami Anttalainen
* Opiskelijanumero: 001067291
* Päivämäärä: 8.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTTavoite, tiedoston nimi HTTavoitetaso.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HTPerusKirjasto.h"

int main(void) {
    int iValinta;
    char aTiedostoNimi[KOKO];
    TIEDOT *pAlku = NULL;
    TULOKSET *pTulosTietue = NULL;

    do {

        iValinta = valikko();

        if (iValinta == 1) {
            annaTiedostoNimi(aTiedostoNimi);
            if (pAlku != NULL) {
                pAlku = vapautaMuisti(pAlku);
            }
            pAlku = lueTiedosto(pAlku, aTiedostoNimi);
        }

        else if (iValinta == 2) {
            if (pAlku != NULL) {
                if (pTulosTietue != NULL) {
                    free(pTulosTietue);
                    pTulosTietue = NULL;
                }
                pTulosTietue = analysoiTiedot(pAlku, pTulosTietue);
                pTulosTietue = analysoiSanat(pAlku, pTulosTietue);
            }
            else {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
        }

        else if (iValinta == 3) {
            if (pTulosTietue != NULL) {
                annaTiedostoNimi(aTiedostoNimi);
                kirjoitaTiedosto(aTiedostoNimi, pTulosTietue);
            }
            else {
                printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
        }

        else if (iValinta == 4) {
            if (pAlku != NULL) {
                annaTiedostoNimi(aTiedostoNimi);
                analysoiViikonPaivat(pAlku, aTiedostoNimi);
            }
            else {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
            }
        }

        else if (iValinta == 5) {
            if (pAlku != NULL) {
                annaTiedostoNimi(aTiedostoNimi);
                analysoiKieliTasot(pAlku, aTiedostoNimi);
            }
            else {
                printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n");
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

    // Vapautetaan varatut muistit
    free(pTulosTietue);
    pTulosTietue = NULL;
    pAlku = vapautaMuisti(pAlku); // Palauttaa NULL:n
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}



// eof