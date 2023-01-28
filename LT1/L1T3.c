#include <stdio.h>
int main(void) {
    int Luku1, Luku2, Luku3 = 10, Tulo, Jako, Jakojaannos;
    char Merkki[] = "%";
 
    printf("Anna ensimmäinen kokonaisluku: ");
    scanf("%d", &Luku1);
    printf("Anna toinen kokonaisluku: ");
    scanf("%d", &Luku2);
    Tulo = (Luku1 + 1) * Luku2;
    printf("%d * %d = %d\n", (Luku1 + 1), Luku2, Tulo);
    Jako = (Luku1 / Luku2) - 10;
    printf("(%d / %d) - %d = %d\n", Luku1, Luku2, Luku3, Jako);
    Jakojaannos = Luku1 % (Luku2 - 1);
    printf("%d %s %d = %d\n", Luku1, Merkki, (Luku2 - 1), Jakojaannos);
    return(0); 



}