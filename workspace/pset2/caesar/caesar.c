#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    if (argc >= 2)
    {

        // Changes string to integer and takes mod 26
        int cipher = atoi(argv[1]);
        cipher = cipher % 26;

        // Requests input from the user
        string plain = get_string("plaintext: ");

        // Provides the encrypted text
        printf("ciphertext: ");

        // Loops through the letters of input text
        for (int i = 0, n = strlen(plain); i < n; i++)
        {
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
                    printf("%c", plain[i]);
                }
        }
        printf("\n");
        exit(0);
    }
    else
    {
        printf("You forgot to enter a command-line argument for the cipher.\n");
        exit(1);
    }

}