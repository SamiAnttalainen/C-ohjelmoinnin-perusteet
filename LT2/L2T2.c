// Tekijä: Sami Anttalainen
// Tehtävä L2T2
// Ohjelma alkaa

#include <stdio.h>
#define iAlaraja 3
#define iYlaraja 10

int main(void) {
    int iLuku, i = 0, j = 0;

    printf("Anna kokonaisluku väliltä 3 - 10: ");
    scanf("%d", &iLuku);
    printf("\n");

    if (iLuku >= iAlaraja && iLuku <= iYlaraja) {
        for (i = 0; i < iLuku; i++) {
            for (j = 0; j <= iLuku; j++) {
                if (j != iLuku) {
                    printf("*");
                } else {
                    printf("\n");
                }
            }
        }
    } else if (iLuku < iAlaraja || iLuku > iYlaraja) {
        printf("Antamasi luku ei ole määritellyllä välillä.\n");
    }
    return(0);
}
// Ohjelma päättyy.
