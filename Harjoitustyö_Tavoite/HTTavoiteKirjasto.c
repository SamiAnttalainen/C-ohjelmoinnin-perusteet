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
/* Tehtävä HTTavoite, tiedoston nimi HTTavoiteKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HTPerusKirjasto.h"

void analysoiViikonPaivat(TIEDOT *pAlku, char *pNimi) {
    int i, *aViikonPaivat;
    TIEDOT *ptr = pAlku;
    FILE *Tiedosto;

    // Varataan taulukolle muisti
    if ((aViikonPaivat = (int *)malloc(VIIKKO * sizeof(int))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }

    // Alustetaan taulukon arvot 0:lla
    for (i = 0; i < VIIKKO; i++) {
        aViikonPaivat[i] = 0;
    }

    // Analysoidaan viikonpäivät
    while (ptr != NULL) {
        i = ptr->tm.tm_wday;
        aViikonPaivat[i] += 1;
        ptr = ptr->pSeuraava;
    }

    // Avataan tiedosto
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Kirjoitetaan tiedot tiedostoon
    fprintf(Tiedosto, "Viikonpäivä;Ma;Ti;Ke;To;Pe;La;Su\n");
    fprintf(Tiedosto, "Lukumäärä;%d;%d;%d;%d;%d;%d;%d\n", aViikonPaivat[1], aViikonPaivat[2], aViikonPaivat[3], aViikonPaivat[4], aViikonPaivat[5], aViikonPaivat[6], aViikonPaivat[0]);

    // Suljetaan tiedosto
    fclose(Tiedosto);

    // Vapautetaan taulukon muisti
    free(aViikonPaivat);

    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

int **varaaMuistiMatriisille(int **pMatriisi, int iRiviLkm, int iEdellinenLkm) {
    int i;
    if ((pMatriisi = (int**)realloc(pMatriisi, iRiviLkm * sizeof(int *))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }
    for (i = iEdellinenLkm; i < iRiviLkm; i++) {
            if ((pMatriisi[i] = (int *)malloc(SARAKKEET * sizeof(int))) == NULL) {
                perror("Muistin varaaminen epäonnistui");
                exit(0);
            }
        }
    return pMatriisi;
}

void analysoiKieliTasot(TIEDOT *pAlku, char *pNimi) {
    int **aMatriisi = NULL, iRivi, iSarake, iRiviLkm = pAlku->iLuokkaNro, i, j, iEdellinenLkm = 0;
    TIEDOT *ptr = pAlku;
    FILE *Tiedosto;

    // Alustetaan matriisi
    aMatriisi = varaaMuistiMatriisille(aMatriisi, iRiviLkm, iEdellinenLkm);
    for (i = 0; i < iRiviLkm; i++) {
        for (j = 0; j < SARAKKEET; j++) {
            aMatriisi[i][j] = 0;
        }
    }

    // Analysoidaan tiedot
    while (ptr != NULL) {
        iRivi = ptr->iLuokkaNro;
        iSarake = ptr->iTaso;

        // Varataan muistia matriisille lisää ja alustetaan uudet rivit nollilla, jos luokkia löytyy lisää
        if (iRivi > iRiviLkm) {
            iEdellinenLkm = iRiviLkm;
            iRiviLkm = iRivi;
            aMatriisi = varaaMuistiMatriisille(aMatriisi, iRiviLkm, iEdellinenLkm);
            for (i = iEdellinenLkm; i < iRiviLkm; i++) {
                for (j = 0; j < SARAKKEET; j++) {
                    aMatriisi[i][j] = 0;
                }
            }
        }
        aMatriisi[iRivi-1][iSarake-1] += 1;
        ptr = ptr->pSeuraava;
    }

    // Avataan tiedosto
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // Kirjoitetaan tiedosto
    fprintf(Tiedosto, "Sanaluokka;A1;A2;B1;B2;C1\n");
    for (i = 0; i < iRiviLkm; i++) {
        fprintf(Tiedosto, "Luokka %d;", i+1);
        for (j = 0; j < SARAKKEET; j++) {
            if (j < SARAKKEET - 1) {
                fprintf(Tiedosto, "%d;", aMatriisi[i][j]);
            }
            else {
                fprintf(Tiedosto, "%d\n", aMatriisi[i][j]);
            }
        }
    }
    // Suljetaan tiedosto
    fclose(Tiedosto);
    
    // Vapautetaan matriisin muisti
    for (i = 0; i < iRiviLkm; i++) {
        free(aMatriisi[i]);
    }
    free(aMatriisi);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

// eof