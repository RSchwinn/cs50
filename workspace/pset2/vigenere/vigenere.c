#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Handles the wrong number of arguments
    if (argc != 2)
    {
        printf("You made a command-line argument error.\n");
        exit(1);
    }

    // Extracts ciphertext, checks length, and sets counter
    string ciphertext = argv[1];
    int lct = strlen(ciphertext);
    int nonalphacounter = 0;

    // Handles the wrong content of arguments
    for (int i = 0; i < lct; i++)
    {
        if (!isalpha(ciphertext[i]))
        {
            printf("You made a command-line argument error.\n");
            exit(1);
        }
    }

    // Requests input from the user
    string plain = get_string("plaintext: ");

    // Provides the encrypted text
    printf("ciphertext: ");

    // Loops through the letters of input text
    for (int i = 0, n = strlen(plain); i < n; i++)
    {

        // Decides which cipher to use
        int cipher_position = (i - nonalphacounter) % lct;
        int cipher = tolower(ciphertext[cipher_position]);

        // int cipher = atoi(ciphertemp);
        cipher = cipher - 97;

        // Handles upper case
        if (plain[i] >= 'A' && plain[i] <= 'Z')
        {
            if ('Z' < plain[i] + cipher)
            {
                char encoded_char = plain[i] + cipher - 26;
                printf("%c", encoded_char);
            }
            else
            {
                char encoded_char = plain[i] + cipher;
                printf("%c", encoded_char);
            }
        }
        else
            // Handles lower case
            if (plain[i] >= 'a' && plain[i] <= 'z')
            {
                if ('z' < plain[i] + cipher)
                {
                    char encoded_char = plain[i] + cipher - 26;
                    printf("%c", encoded_char);
                }
                else
                {
                    char encoded_char = plain[i] + cipher;
                    printf("%c", encoded_char);
                }
            }
            else
                // Handles non-characters
            {
                nonalphacounter++;
                printf("%c", plain[i]);
            }
    }
    printf("\n");
    exit(0);
}