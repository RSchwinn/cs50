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
        printf("Wrong number of arguments.");
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
        int k = j - 2;
        hash[k] = full_hash[j];
    }

    // Defines possible characters
    char pwkeys[94];
    for (int i = 0; i < 94; i++)
    {
        pwkeys[i] = (i + 33);
    }


    string temphash;

    // One character passwords
    char a_password_1[2] = {};

    for (int i = 0; i < 94; i++)
    {

        a_password_1[0] = pwkeys[i];

        if (strcmp(crypt(a_password_1, the_salt), argv[1]) == 0)
        {
            printf("%s \n", a_password_1);
            exit(0);
        }

        // temphash = crypt(a_password_1, the_salt);
        // printf("The hash of %s is %s.\n", a_password_1, temphash);
    }

    // Two character passwords
    char a_password_2[3] = {};
    for (int i = 0; i < 94; i++)
    {
        for (int j = 0; j < 94; j++)
        {
            a_password_2[0] = pwkeys[i];
            a_password_2[1] = pwkeys[j];

            if (strcmp(crypt(a_password_2, the_salt), argv[1]) == 0)
            {
                printf("%s \n", a_password_2);
                exit(0);
            }
            // temphash = crypt(a_password_2, the_salt);
            // printf("The hash of %s is %s.\n", a_password_2, temphash);

        }
    }





    // Three character passwords
    char a_password_3[4] = {};

    for (int i = 0; i < 94; i++)
    {
        for (int j = 0; j < 94; j++)
        {
            for (int k = 0; k < 94; k++)
            {
                a_password_3[0] = pwkeys[i];
                a_password_3[1] = pwkeys[j];
                a_password_3[2] = pwkeys[k];

                if (strcmp(crypt(a_password_3, the_salt), argv[1]) == 0)
                {
                    printf("%s \n", a_password_3);
                    exit(0);
                }
                // temphash = crypt(a_password_3, the_salt);
                // printf("The hash of %s is %s.\n", a_password_3, temphash);

            }
        }
    }


    // Four character passwords
    char a_password_4[5] = {};

    for (int i = 0; i < 94; i++)
    {
        for (int j = 0; j < 94; j++)
        {
            for (int k = 0; k < 94; k++)
            {
                for (int l = 0; l < 94; l++)
                {

                    a_password_4[0] = pwkeys[i];
                    a_password_4[1] = pwkeys[j];
                    a_password_4[2] = pwkeys[k];
                    a_password_4[3] = pwkeys[l];

                    if (strcmp(crypt(a_password_4, the_salt), argv[1]) == 0)
                    {
                        printf("%s \n", a_password_4);
                        exit(0);
                    }
                    // temphash = crypt(a_password_4, the_salt);
                    // printf("The hash of %s is %s.\n", a_password_4, temphash);


                }
            }
        }
    }

    // Five character passwords
    char a_password_5[6] = {};
    for (int i = 0; i < 94; i++)
    {
        for (int j = 0; j < 94; j++)
        {
            for (int k = 0; k < 94; k++)
            {
                for (int l = 0; l < 94; l++)
                {
                    for (int m = 0; m < 94; m++)
                    {
                        a_password_5[0] = pwkeys[i];
                        a_password_5[1] = pwkeys[j];
                        a_password_5[2] = pwkeys[k];
                        a_password_5[3] = pwkeys[l];
                        a_password_5[4] = pwkeys[m];

                        if (strcmp(crypt(a_password_5, the_salt), argv[1]) == 0)
                        {
                            printf("%s \n", a_password_5);
                            exit(0);
                        }
                        // temphash = crypt(a_password_5, the_salt);
                        // printf("The hash of %s is %s.\n", a_password_5, temphash);

                    }
                }
            }
        }
    }
    printf("No five or fewer character password was found.");
    exit(1);
}