// Tekijä: Sami Anttalainen
// Tehtävä L2T4
// Ohjelma alkaa

#include <stdio.h>

int main(void) {
    int iLuku1, iLuku2, iValinta;

    printf("Anna kokonaisluku: ");
    scanf("%d", &iLuku1);
    printf("\n");

    do {
        printf("Valikko:\n");
        printf("1) Lisää lukuun\n");
        printf("2) Vähennä luvusta\n");
        printf("0) Lopeta\n");
        printf("Valintasi: ");
        scanf("%d", &iValinta);
        printf("\n");

        if (iValinta == 1) {
            printf("Anna lukuun lisättävä kokonaisluku: ");
            scanf("%d", &iLuku2);
            iLuku1 += iLuku2;
            printf("Luku on nyt %d.\n", iLuku1);
            printf("\n");
        } else if (iValinta == 2) {
            printf("Anna luvusta vähennettävä kokonaisluku: ");
            scanf("%d", &iLuku2);
            iLuku1 -= iLuku2;
            printf("Luku on nyt %d.\n", iLuku1);
            printf("\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        }
        
         else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
            printf("\n");
        }
    } while (iValinta != 0);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
    
}

// Ohjelma päättyy
