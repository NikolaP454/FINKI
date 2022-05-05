#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CertificateCov19{
    int den;
    int mesec;
    int godina;
    char ime[50];
    int red;

} certification;

typedef struct Patient{
    char ime[50];
    char embg[13];
    certification sertifikat;

} patient;

int isValid(patient p, int d, int m, int y){
    if(p.sertifikat.red != 2) return 0;

    int razlika = (y - p.sertifikat.godina) * 12;
    razlika += (m - p.sertifikat.mesec);

    return (razlika == 6);
}

void valid(patient * p, int n, int d, int m, int y){
    printf("Pacienti koi treba da primat 3ta doza vakcina na %d/%d/%d se:\n", d, m, y);

    for(int i = 0; i < n; i++){
        if(!isValid(p[i], d, m, y)) continue;

        printf("Ime: %s - embg: %s\n", p[i].ime, p[i].embg);
    }
}

int treta(patient * p, int n){
    int br = 0;

    for(int i = 0; i < n; i++){
        if(p[i].sertifikat.red > 2)
            ++br;
    }

    return br;
}


int main()
{
    int n;
    scanf("%d", &n);

    patient pacienti[100];
    for(int i = 0; i < n; i++){
        scanf("%s", pacienti[i].ime);
        scanf("%s", pacienti[i].embg);
        scanf("%s", pacienti[i].sertifikat.ime);

        scanf("%d/%d/%d", &pacienti[i].sertifikat.den, &pacienti[i].sertifikat.mesec, &pacienti[i].sertifikat.godina);
        scanf("%d", &pacienti[i].sertifikat.red);
    }

    int d,m,y;
    scanf("%d/%d/%d", &d, &m, &y);

    valid(pacienti, n, d, m, y);

    printf("Procentualno se vakcinirale so treta doza %.2f%% od pacientite", (float)( treta(pacienti, n) * 100 ) / n );
    return 0;
}
