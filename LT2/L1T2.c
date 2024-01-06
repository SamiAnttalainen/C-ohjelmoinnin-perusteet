#include <stdio.h>
int main(void) {
    int Luku;
    float Desimaali;
    printf("Anna kokonaisluku: ");
    scanf("%d", &Luku);
    printf("Anna liukuluku: ");
    scanf("%f", &Desimaali);
    printf("Annoit luvut %d ja %.2f.\n", Luku, Desimaali);
    return(0);
}