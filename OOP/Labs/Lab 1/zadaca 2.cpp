#include<stdio.h>
#include<ctype.h>
#include<string.h>

typedef struct Tocka{
    double x;
    double y;
} tocka;

typedef struct Otsecka{
    tocka t1;
    tocka t2;
} otsecka;

double delta(tocka a, tocka b, int dalix){
    if(dalix) return a.x - b.x;
    return a.y - b.y;
}

double min(double a, double b){
    return a < b? a : b;
}

double max(double a, double b){
    return a < b? b : a;
}

int CheckIntersect(otsecka a, otsecka b){
    double minx = min(a.t1.x, a.t2.x);
    double maxx = max(a.t1.x, a.t2.x);

    double miny = min(a.t1.y, a.t2.y);
    double maxy = max(a.t1.y, a.t2.y);

    double x1 = b.t1.x;
    double x2 = b.t2.x;

    if(x1 < minx && x2 < minx) return 0;
    if(x1 > maxx && x2 > maxx) return 0;

    double y1 = b.t1.y;
    double y2 = b.t2.y;

    if(y1 < miny && y2 < miny) return 0;
    if(y1 > maxy && y2 > maxy) return 0;

    return 1;
}

int InLine(tocka t, otsecka a){
    double minx = min(a.t1.x, a.t2.x);
    double maxx = max(a.t1.x, a.t2.x);

    double miny = min(a.t1.y, a.t2.y);
    double maxy = max(a.t1.y, a.t2.y);

    if(!(minx <= t.x && t.x <= maxx)) return 0;
    if(!(miny <= t.y && t.y <= maxy)) return 0;

    return 1;
}

int se_secat(otsecka a, otsecka b){
    double arr1[3] = {0};
    double arr2[3] = {0};

    arr1[0] = delta(a.t1, a.t2, 0);
    arr1[1] = -delta(a.t1, a.t2, 1);
    arr1[2] = delta(a.t1, a.t2, 0) * a.t1.x - delta(a.t1, a.t2, 1) * a.t1.y;

    arr2[0] = delta(b.t1, b.t2, 0);
    arr2[1] = -delta(b.t1, b.t2, 1);
    arr2[2] = delta(b.t1, b.t2, 0) * b.t1.x - delta(b.t1, b.t2, 1) * b.t1.y;

    double deltaa  = (arr1[0] * arr2[1] - arr1[1] * arr2[0]);
    double deltax = (arr1[2] * arr2[1] - arr1[1] * arr2[2]);
    double deltay = (arr1[0] * arr2[2] - arr1[2] * arr2[0]);

    if(!deltaa){
        if(deltax == deltay){
            return CheckIntersect(a,b);
        }
        else return 0;
    }

    tocka t = {deltax/deltaa, deltay/deltaa};
    //printf("%lf %lf\n", deltax/deltaa, deltay/deltaa);
    return (InLine(t, a) && InLine(t,b));
}

int main() {
    double x1, y1, x2, y2;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    tocka t1 = { x1, y1 };
    tocka t2 = { x2, y2 };
    otsecka o1 = { t1, t2 };
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    tocka t3 = { x1, y1 };
    tocka t4 = { x2, y2 };
    otsecka o2 = { t3, t4 };
    printf("%d\n", se_secat(o1, o2));
    return 0;
}
