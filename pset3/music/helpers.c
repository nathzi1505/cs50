// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int X = fraction[0] - 48;
    int Y = fraction[2] - 48;
    double factor = 8 / (Y * 1.0); // Stores the multiplication factor
    int f = X * factor;
    return f;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Notes in an octave
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    char alpha = note[0]; // Stores the alphabet in the note
    char accidental = note[1]; // Stores the accidental in the note
    int flag = 0; // To indicate whether accidental present or not
    if (accidental == '#' || accidental == 'b')
    {
        flag = 1;
        if (accidental == 'b')
        {
            if (alpha == 'A')
            {
                alpha = 'G';
            }
            else
            {
                alpha--;
            }
            accidental = '#'; // Converts a flat note into a sharp note
        }
    }
    else
    {
        accidental = '\0';
        flag = 0;
    }
    int octave = note[flag + 1] - 48;
    char key[3] = {alpha, accidental, '\0'};
    int counter = (octave - 4) * 12;
    int distance = 0;
    for (int i = 9; i <= 11; i++, distance++)
    {
        if (strcmp(NOTES[i], key) == 0) // Compares the string to a note
        {
            break;
        }
        if (i == 11)
        {
            counter -= 12;
            i = -1;
        }
    }
    int n = distance + counter; // stores the number of semi-tones away from A4
    double frequency = pow(2, n / 12.0) * 440;
    int f = (int) round(frequency);
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
