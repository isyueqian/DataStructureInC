#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAXN 100000
#define MAXK 1e7
clock_t start, stop;
double duration;
double f1(int n, const double a[], double x);
double f2(int n, const double a[], double x);

int main()
{
    int i;
    double a[MAXN];
    for(i=0; i<MAXN; i++) {
        a[i] = (double) i;
    }

    start = clock();
    for (i=0; i<MAXK; i++) {
        f1(MAXN-1, a, 1.2);
    }
    stop = clock();
    duration = ((double) (stop - start)) / CLK_TCK / MAXK;
    printf("ticks1 = %f\n", (double) stop-start);
    printf("duration = %6.2e\n", duration);

    start = clock();
    for (i=0; i<MAXK; i++) {
        f2(MAXN-1, a, 1.2);
    }
    stop = clock();
    duration = ((double) (stop - start)) / CLK_TCK / MAXK;
    printf("ticks2 = %f\n", (double) stop-start);
    printf("duration = %6.2e\n", duration);

    printf("CLK_TCK: %d", CLK_TCK);

    return 0;
}

double f1(int n, const double a[], double x)
{
    int i;
    double p = a[0];
    for (i=1; i<=n; i++) {
        p += a[i] * pow(x, i);
    }
    return p;
}

double f2(int n, const double a[], double x)
{
    int i;
    double p = a[n];
    for (i=n; i>=0; i--) {
        p = a[i-1] + p*x;
    }
    return p;
}