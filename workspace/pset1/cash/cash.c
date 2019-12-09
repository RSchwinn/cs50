#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float n;
    do
    {
        n = get_float("How much change?");
    }
    while (n < 0);

    int cents = round(n * 100);

    int quarters = cents / 25;
    int leftover = cents - (quarters * 25);

    int dimes = leftover / 10;
    leftover = leftover - (dimes * 10);

    int nickels = leftover / 5;
    leftover = leftover - (nickels * 5);

    int pennies = leftover / 1;
    leftover = leftover - (pennies * 1);

    int total = quarters + dimes + nickels + pennies;
    printf("%i\n", total);
}