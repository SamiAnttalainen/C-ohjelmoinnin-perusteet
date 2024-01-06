// Tekijä: Sami Anttalainen
// Päivämäärä: 6.2.2023
// Tehtävä: L4T2.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i = 0;
    char aRivi[100];
    //printf("1 on %s", argv[1]);
    //printf("2 on %d\n", j);

    if (argc > 3) {
        printf("Annoit liikaa parametreja.\n");
    } else if (argc < 3) {
        printf("Et antanut tarpeeksi parametreja.\n");
    }

    else {
        FILE *Tiedosto;

        if ((Tiedosto = fopen(argv[1], "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
        }
        int j = atoi(argv[2]);
        while (i < j) {
            fgets(aRivi, 100, Tiedosto);
            if (feof(Tiedosto) != 0) {
                break;
            } else {
                printf("%s", aRivi);
            }
            i++;
        }
    printf("\n");
    if (feof(Tiedosto) != 0) {
        printf("Tiedostossa ei ole enempää rivejä luettavaksi.\n");
    }
    fclose(Tiedosto);
    printf("Tiedostosta '%s' luettu %d riviä.\n", argv[1], i);
    return(0);
    }
}    
// eof
