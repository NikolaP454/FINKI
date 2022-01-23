#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check(char s[], char c){
    int n = strlen(s);

    int br = 0;
    for(int i = 0; i < n; i++)
        br += (s[i] == c);

    return br;
}


int main()
{
    char c;
    scanf("%c", &c);

    int x;
    scanf("%d", &x);

    char ans[4][100] = {"", "", "", ""};


    for(;;){
        char s[100];
        fgets(s, sizeof(s), stdin);

        if(s[0] == '#' && strlen(s) == 2) break;

        if(!(check(s, c) == x)) continue;

        strcpy(ans[3], s);
        for(int i = 0; i < 4; i++){
            for(int j = i+1; j < 4; j++){
                if(strlen(ans[i]) < strlen(ans[j])){
                    char temp[100];
                    strcpy(temp, ans[i]);
                    strcpy(ans[i], ans[j]);
                    strcpy(ans[j], temp);
                }
            }
        }
    }


    for(int i = 0; i < 3; i++){
        printf("%s", ans[i]);
    }
    return 0;
}
