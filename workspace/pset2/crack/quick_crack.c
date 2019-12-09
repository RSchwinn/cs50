#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <crypt.h>
#include <unistd.h>


int main(int argc, string argv[])
{
    // Ensures correct number of parameters
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Isolates hash and salt
    string full_hash = argv[1];
    char the_salt[3];

    for (int j = 0; j < 2; j++)
    {
         the_salt[j] = full_hash[j];
    }

    int lfh = strlen(full_hash);
    char hash[lfh];

    for (int j = 2; j <= lfh ; j++)
    {
        int k = j-2;
         hash[k] = full_hash[j];
    }

    // Defines possible characters
    char pwkeys[94];
    for(int i = 0; i < 94; i++)
    {
        pwkeys[i] = (i + 33);
    }

    char it;
string one = "ROFL";
string two = "50";
    it = crypt(one,two)

printf("%s", it)
}