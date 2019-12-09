#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float x = get_float("x: ");

    float y = get_float("y: ");

    printf("%f divided by %f is %.10f\n", x, y, x / y);
}