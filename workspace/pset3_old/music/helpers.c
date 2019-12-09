// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    if (fraction[0] == '1')
    {
        if (fraction[2] == '8')
        {
            return 1;
        }

        if (fraction[2] == '4')
        {
            return 2;
        }

        if (fraction[2] == '2')
        {
            return 4;
        }

    }
    else if (fraction[0] == '3')
    {
        return 3;
    }
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // variable to temporarily save frequency
    double hertz = 0.0;
    hertz = 440.0;

    // A4 is 440 and Use 2^(n/12) × 4400
    // pow(x, y), here x is base while y is exponent (x^y)
    switch (note[0])
    {
        case 'A':
            break;

        case 'B':
            hertz *= pow(2.0, (2.0 / 12.0));
            break;

        case 'C':
            hertz /= pow(2.0, (9.0 / 12.0));
            break;

        case 'D':
            hertz /= pow(2.0, (7.0 / 12.0));
            break;

        case 'E':
            hertz /= pow(2.0, (5.0 / 12.0));
            break;

        case 'F':
            hertz /= pow(2.0, (4.0 / 12.0));
            break;

        case 'G':
            hertz /= pow(2.0, (2.0 / 12.0));
            break;

    }


    // Adjusts for flats and sharps
    switch (note[1])
    {
        case 'b':
            hertz /= pow(2.0, (1.0 / 12.0));
            break;

        case '#':
            hertz *= pow(2.0, (1.0 / 12.0));
            break;
    }

    // Adjusts the octave
    int oct = note[strlen(note) - 1];

    switch (oct)
    {
        case '0':
            hertz /= 16.0;
            break;

        case '1':
            hertz /= 8.0;
            break;

        case '2':
            hertz /= 4.0;
            break;

        case '3':
            hertz /= 2.0;
            break;

        case '5':
            hertz *= 2.0;
            break;

        case '6':
            hertz *= 4.0;
            break;

        case '7':
            hertz *= 8.0;
            break;

        case '8':
            hertz *= 16.0;
            break;

    }

    // return hertz;

    // If only integer frequencies are accepted we must round
    int rhertz = round(hertz);
    return rhertz;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // if (strcmp(s, "") == 0)

    if (strncmp(s, "", 1))
    {
        return false;
    }
    else
    {
        return true;
    }

}
