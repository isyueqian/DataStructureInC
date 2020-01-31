#include <stdio.h>

int main(void)
{
    int res;
    int number;
    char operator;
    scanf("%d", &res);
    do {
        scanf("%c", &operator);
        if (operator=='=') {
            break;
        }
        scanf("%d", &number);
        if (operator == '+') {
            res += number;
        } else if (operator == '-') {
            res -= number;
        } else if (operator == '*') {
            res *= number;
        } else if (operator == '/') {
            if (number!=0) {
                res /= number;
            } else {
                printf("ERROR");
                return 0;
            }
        } else {
            printf("ERROR");
            return 0;
        }
    } while (1);

    printf("%d", res);

    return 0;
}