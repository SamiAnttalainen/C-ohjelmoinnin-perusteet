#include <stdio.h>

// Tekijä: Sami Anttalainen
// Tehtävä L2T1
// Ohjelma alkaa
int main(void) {
    int iMaara;

    printf("Anna palautettujen tehtävien lukumäärä: ");
    scanf("%d", &iMaara);

    if (iMaara < 15) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 0.\n", iMaara);
    } else if (iMaara >= 15 && iMaara < 18) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 1.\n", iMaara);
    } else if (iMaara >= 18 && iMaara < 21) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 2.\n", iMaara);
    } else if (iMaara >= 21 && iMaara < 24) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 3.\n", iMaara);
    } else if (iMaara >= 24 && iMaara < 27) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 4.\n", iMaara);
    } else if (iMaara >= 27 && iMaara < 31) {
        printf("Olet palauttanut %d tehtävää, joten arvosanasi on 5.\n", iMaara);
    } else {
        printf("Kurssilla on vain 30 tehtävää.\n");
    }
    return(0);

}

// Ohjelma päättyy.