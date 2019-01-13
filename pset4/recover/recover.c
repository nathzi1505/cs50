// Recovers lost images (.jpeg) in a memory card

#include <stdio.h>
#include <stdlib.h>

#define buffsize 10

// Function to check whether jpeg or not
int check_jpeg(unsigned char *argv)
{
    unsigned int v1 = (int)argv[0];
    unsigned int v2 = (int)argv[1];
    unsigned int v3 = (int)argv[2];
    unsigned int v4 = (int)argv[3];
    if (v1 == 0xff && v2 == 0xd8 && v3 == 0xff)
    {
        switch (v4)
        {
            case 0xe0 :
            case 0xe1 :
            case 0xe2 :
            case 0xe3 :
            case 0xe4 :
            case 0xe5 :
            case 0xe6 :
            case 0xe7 :
            case 0xe9 :
            case 0xea :
            case 0xeb :
            case 0xec :
            case 0xed :
            case 0xee :
            case 0xef :
                return 1;
                break;
            default :
                return 0;
        }


    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{
    // Cautioning the user for wrong usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    // Opens the .raw file to begin inspection
    FILE *camera = fopen(argv[1], "r");

    // Checks the validity of the opened file
    if (camera == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 2;
    }


    int counter = -1; // Declaring and Initialising the counter
    int online = 0; // To know whether image is being written

    char *filename = malloc(buffsize); // To prevent segmentation fault
    FILE *outptr;

    while (1)
    {
        unsigned char *image = malloc(512); // So as to prevent addition of '1's in binary or 'f's in hexcode
        if (image == NULL)
        {
            fprintf(stderr, "Error creating pointer \n");
            return 200;
        }

        int blocksread = fread(image, 512, 1, camera); // Checks the number of blocks read
        if (blocksread == 1)
        {
            int flag = check_jpeg(image);
            if (flag == 1)
            {
                if (counter != -1)
                {
                    fclose(outptr);
                }
                counter ++;

                // Creating the output file pointer
                snprintf(filename, buffsize, "%03i.jpg", counter);
                outptr = fopen(filename, "w");

                if (outptr == NULL)
                {
                    fprintf(stderr, "Error opening file: %s\n", filename);
                    return 201;
                }

                // Writing to the file
                fwrite(image, 512, 1, outptr);
                online = 1;
            }
            else if (flag == 0 && online == 1)
            {
                fwrite(image, 512, 1, outptr); // Continue writing to the output file
            }
            free(image);
        }
        else
        {
            fclose(camera);
            fclose(outptr);
            return 0;
        }
    }
}