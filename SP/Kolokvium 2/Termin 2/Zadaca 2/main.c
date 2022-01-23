#include<stdio.h>
#include<ctype.h>
#include<string.h>

int valid(int x, int y, int n, int m){
    if(x < 0 || y < 0) return 0;
    if(x >= n || y >= m) return 0;

    return 1;
}


void wtf() {
    FILE *f = fopen("input.txt", "w");
    char c;
    while((c = getchar()) != '#') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {
    wtf();
    FILE *in = fopen("input.txt", "r");

    int n,m;
    fscanf(in, "%d%d", &n, &m);

    int mat[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            fscanf(in, "%d", &mat[i][j]);
    }

    double matKraj[n][m];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int br = 0;
            double ans = 0;

            int changex[4] = {-1, -1, 1, 1};
            int changey[4] = {-1, 1, -1, 1};

            for(int t = 0; t < 4; t++){
                int nx = i + changex[t];
                int ny = j + changey[t];

                while(valid(nx,ny,n,m)){
                    br++;
                    ans += mat[nx][ny];
                    nx += changex[t];
                    ny += changey[t];
                }
            }

            if(br)matKraj[i][j] = (double)ans/br;
            else matKraj[i][j] = 0;
        }
    }


    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            printf("%.2lf ", matKraj[i][j]);

        printf("\n");
    }
    return 0;
}
