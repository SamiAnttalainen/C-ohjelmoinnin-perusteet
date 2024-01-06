/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Sami Anttalainen
* Päivämäärä: 8.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTTavoite, tiedoston nimi HTPerusKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HTPerusKirjasto.h"

int valikko() {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("4) Viikonpäiväanalyysi\n");
    printf("5) Kielitasoanalyysi\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

void annaTiedostoNimi(char *pNimi) {
    printf("Anna tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return;
}

TIEDOT *varaaMuistiTietueelle(TIEDOT *pUusi) {

    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }
    return pUusi;
}

TIEDOT *vapautaMuisti(TIEDOT *pAlku) {
    TIEDOT *ptr = pAlku;

    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return pAlku;
}

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi) {
    TIEDOT *pUusi, *ptr;
    char *aSarake1, *aSarake2, *aSarake3, *aSarake4, aRivi[KOKO];
    FILE *Tiedosto;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, KOKO, Tiedosto); // Ohitetaan tiedoston otsikkorivi.

    // Luetaan tiedosto, pilkotaan rivit ja lisätään tiedot tietueisiin sekä lopuksi linkitettyyn listaan
    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {

        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake2 = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake3 = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake4 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }


        // Varataan muisti tietueelle
        pUusi = varaaMuistiTietueelle(pUusi);

        // Lisätään tiedot tietueeseen
        strcpy(pUusi->aSana, aSarake1);
        pUusi->iLuokkaNro = atoi(aSarake2);
        pUusi->iTaso = atoi(aSarake3);
        memset(&pUusi->tm, 0, sizeof(pUusi->tm));
        strptime(aSarake4, "%d-%m-%Y %H:%M:%S", &pUusi->tm);
        pUusi->pSeuraava = NULL;

        // Lisätään tietue linkitettyyn listaan
        if (pAlku == NULL) {
            pAlku = pUusi;
        }
        else {
            ptr = pAlku;
            while (ptr->pSeuraava != NULL) {
                ptr = ptr->pSeuraava;
            }
            ptr->pSeuraava = pUusi;
        }
    }
    // Suljetaan tiedosto
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return pAlku;
}

TULOKSET *analysoiTiedot(TIEDOT *pAlku, TULOKSET *pTiedot) {
    int iLkm = 0, iSumma = 0, iPituus;
    float fKeskiarvo;
    TIEDOT *ptr = pAlku;
    // Alustetaan analyysimuuttujat linkitetyn listan ekoilla arvoilla
    int iMaxPituus = strlen(pAlku->aSana), iMinPituus = strlen(pAlku->aSana);
    char aLyhinSana[KOKO], aPisinSana[KOKO], aEkaSana[KOKO], aVikaSana[KOKO];
    strcpy(aLyhinSana, pAlku->aSana);
    strcpy(aPisinSana, pAlku->aSana);
    strcpy(aEkaSana, pAlku->aSana);
    strcpy(aVikaSana, pAlku->aSana);
    
    // Luetaan linkitetty lista ja analysoidaan tiedot
    while (ptr != NULL) {
        iPituus = strlen(ptr->aSana);
        iSumma += iPituus;
        iLkm += 1;

        if (iPituus < iMinPituus) {
            iMinPituus = iPituus;
            strcpy(aLyhinSana, ptr->aSana);
        }
        if (iPituus > iMaxPituus) {
            iMaxPituus = iPituus;
            strcpy(aPisinSana, ptr->aSana);
        }
        if (strcmp(ptr->aSana, aEkaSana) < 0) {
            strcpy(aEkaSana, ptr->aSana);
        }
        if (strcmp(ptr->aSana, aVikaSana) > 0) {
            strcpy(aVikaSana, ptr->aSana);
        }
        ptr = ptr->pSeuraava;
    }

    // Varataan muisti tulostietueelle
    if ((pTiedot = (TULOKSET*)malloc(sizeof(TULOKSET))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }

    // Lisätään analyysin tulokset tietueeseen
    fKeskiarvo = (float) iSumma / iLkm;
    pTiedot->iLkm = iLkm;
    pTiedot->fKeskiarvo = fKeskiarvo;
    pTiedot->iMinimiPituus = iMinPituus;
    pTiedot->iMaksimiPituus = iMaxPituus;
    strcpy(pTiedot->aLyhinSana, aLyhinSana);
    strcpy(pTiedot->aPisinSana, aPisinSana);
    strcpy(pTiedot->aEkaSana, aEkaSana);
    strcpy(pTiedot->aVikaSana, aVikaSana);

    printf("Analysoitu %d sanaa.\n", iLkm);
    return pTiedot;
}

TULOKSET *analysoiSanat(TIEDOT *pAlku, TULOKSET *pTiedot) {
    int i;
    TIEDOT *ptr = pAlku;

    // Alustetaan tulokset tietuetaulukon arvot
    for (i = 0; i < LEN; i++) {
        pTiedot->aSanatTietueet[i].iLuokkaNumero = i + 1;
        pTiedot->aSanatTietueet[i].iLkm = 0;
    }

    // Analysoidaan sanaluokkiin kuuluvien sanojen määrät
    while (ptr != NULL) {
        i = ptr->iLuokkaNro - 1;
        pTiedot->aSanatTietueet[i].iLkm += 1;
        ptr = ptr->pSeuraava;
    }

    printf("Sanaluokittaiset lukumäärät analysoitu.\n");
    return pTiedot;
}

void kirjoitaTiedosto(char *pNimi, TULOKSET *pTiedot) {
    FILE *Tiedosto;

    // Tulostetaan tulokset
    tulostaTulokset(stdout, pTiedot);

    // Avataan tiedosto
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Kirjoitetaan tiedot tiedostoon
    tulostaTulokset(Tiedosto, pTiedot);

    // Suljetaan tiedosto
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

void tulostaTulokset(FILE *Tiedosto, TULOKSET *pTiedot) {
    int i;

    // Kirjoitetaan tiedot tiedostoon
    fprintf(Tiedosto, "Tilastotiedot %d sanasta:\n", pTiedot->iLkm);
    fprintf(Tiedosto, "Keskimääräinen sanan pituus on %.1f merkkiä.\n", pTiedot->fKeskiarvo);
    fprintf(Tiedosto, "Pisin sana '%s' on %d merkkiä pitkä.\n", pTiedot->aPisinSana, pTiedot->iMaksimiPituus);
    fprintf(Tiedosto, "Lyhyin sana '%s' on %d merkkiä pitkä.\n", pTiedot->aLyhinSana, pTiedot->iMinimiPituus);
    fprintf(Tiedosto, "Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", pTiedot->aEkaSana);
    fprintf(Tiedosto, "Aakkosjärjestyksessä viimeinen sana on '%s'.\n", pTiedot->aVikaSana);
    fprintf(Tiedosto, "\n");
    fprintf(Tiedosto, "Sanaluokka;Lkm\n");
    for (i = 0; i < LEN; i++) {
        fprintf(Tiedosto, "Luokka %d;%d\n", pTiedot->aSanatTietueet[i].iLuokkaNumero, pTiedot->aSanatTietueet[i].iLkm);
    }
    return;
}
