#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef struct Tocka2D{
    float x;
    float y;
} tocka2D;

typedef struct Tocka3D{
    float x;
    float y;
    float z;
} tocka3D;

typedef struct Otsecka{
    tocka2D t1;
    tocka2D t2;
} otsecka;

float min(float a, float b){
    return a < b? a : b;
}

float max(float a, float b){
    return a < b? b : a;
}



float rastojanie3D(tocka3D a, tocka3D b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

float rastojanie(tocka2D a, tocka2D b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double delta(tocka2D a, tocka2D b, int dalix){
    if(dalix) return a.x - b.x;
    return a.y - b.y;
}

int ista_prava(tocka2D a, tocka2D b, tocka2D c){
    double arr[3] = {0};

    otsecka o = {a,b};

    arr[0] = delta(o.t1, o.t2, 0);
    arr[1] = -delta(o.t1, o.t2, 1);
    arr[2] = delta(o.t1, o.t2, 0) * o.t1.x - delta(o.t1, o.t2, 1) * o.t1.y;

    return c.x * arr[0] + c.y * arr[1] == arr[2];
}

int main() {
    float x1, y1, x2, y2;
    scanf("%f %f", &x1, &y1);
	scanf("%f %f", &x2, &y2);
	tocka2D t1 = { x1, y1 };
	tocka2D t2 = { x2, y2 };
	printf("%.2f\n", rastojanie(t1, t2));
    float z1, z2;
    scanf("%f %f", &z1, &z2);
    tocka3D t3 = {x1, y1, z1};
    tocka3D t4 = {x2, y2, z2};
    printf("%.2f\n", rastojanie3D(t3, t4));
    tocka2D t5 = {z1, z2};
    printf("%d\n", ista_prava(t1, t2, t5));
	return 0;
}

