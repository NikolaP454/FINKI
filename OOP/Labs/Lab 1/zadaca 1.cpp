#include<stdio.h>
#include<ctype.h>
#include<string.h>

typedef struct product{
    char ime[100];
    float cena;
    float kolicina;

} Product;

void Input(Product *p){
    scanf("%s %f%f", &p->ime, &p->cena, &p->kolicina);
}


int main() {
    int t;
    scanf("%d", &t);
    Product arr[t];

    float sum = 0;
    for(int i = 0; i < t; i++){
        Input(&arr[i]);
        sum += arr[i].cena * arr[i].kolicina;
    }

    for(int i = 0; i < t; i++){
        printf("%d. %s\t%.2f x %.1f = %.2f\n", i+1, arr[i].ime, arr[i].cena, arr[i].kolicina, arr[i].cena * arr[i].kolicina);
    }
    printf("Total: %.2f", sum);
    return 0;
}
