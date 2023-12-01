// C program to implement
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char m[100][4]; // memory
char buffer[40];
char R[4];  // general purpose register
char ir[4]; // instruction register ie instruction is stored here
int c;      // counter (will be incremented after one instruction is read)
bool t;

FILE *ptr;
FILE *ptr2;

void getdata()
{
    int l = 0;
    int z = atoi(&ir[2]); // get address
    int j = atoi(&ir[3]);
    int i = (z ) + j;
    printf("%d\n",i);
    fgets(buffer, sizeof(buffer), ptr);
        printf("%d\n",i);
        printf("%d\n",i);
        int Q=0;

    for (int q = i; q < i + 10; q++)
    {
        for (int j = 0; j < 4; j++)
        {
            
            if (Q==0 )
            {
            m[q][j] = buffer[l];
            printf("++%d\n",l);
            l++;
            }
            if(buffer[l]=='\n')
            {
                Q=1;
            }
        }
    }
    //  strcpy(buffer, m[i]); // copy address to buffer
}

void putdata()
{
    int l = 0;
    int z = atoi(&ir[2]); // get address
    int j = atoi(&ir[3]);
    int i = (z ) + j;
    for (int q = i; q < i + 10; q++)
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[l] = m[q][j];

            l++;
        }
    }
    fputs(buffer, ptr2);
    fputc('\n',ptr2);
    // printf("%s", buffer);
}

void load()
{
    int i = atoi(&ir[2]); // get address
    int j = atoi(&ir[3]);
    i = i  + j;
      int l = 0;
     for (int q = i; q < i + 10; q++)
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[l] = m[q][j];

            l++;

        }
    }
    // for (int p = 0; p < 40; p++)
    // {
    //     printf("\n\n*%s*\n", buffer);
    // }
}

void compare()
{
    int count = 0;
    int i = atoi(&ir[2]); // get address
    int j = atoi(&ir[3]);
    i = i  + j;
    int l = 0;
      for (int q = i; q < i + 10; q++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("\n*%c\t%d\t%d\t%c*%d\n", buffer[l],l,q,m[q][j],count);

            if (buffer[l] == m[q][j])
            {
                count++;
            }
            l++;
        }
    }
    if (count == 40)
    {
        t = true;
    }
    else
    {
        t = false;
    }
}

int branched()
{
    if (t == true)
    {
        int i = atoi(&ir[2]); // get address
        int j = atoi(&ir[3]);
        i = i  + j;

        c = i;
    }
    else
    {
        c++;
    }
    return c;
}

void freebuffer()
{
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = ' ';
    }
}

void execute()
{
    c = 0;
 for (int j = 0; j < 4; j++)
    {
        ir[j] = m[c][j];
    }
                        printf("@@%s@@\n",ir);

    while (ir[0] != 'H')
    {
        if (ir[0] == 'G' && ir[1] == 'D')
        {
                    printf("%s\n",ir);

            getdata();
            c++;
            freebuffer();
        }
        else if (ir[0] == 'P' && ir[1] == 'D')
        {
                                printf("%s\n",ir);

            putdata();
            c++;
            freebuffer();
        }
        else if (ir[0] == 'L' && ir[1] == 'R')
        {
            printf("%s\n",ir);
            load();
            c++;
        }
        else if (ir[0] == 'C' && ir[1] == 'R')
        {
            printf("%s\n",ir);
            compare();
            freebuffer();
            c++;
            
        }
        else if (ir[0] == 'B' && ir[1] == 'T')
        {
            printf("%s\n",ir);
            c = branched();
            freebuffer();
        }
        else
        {
            c++;
        }
         for (int j = 0; j < 4; j++)
    {
        ir[j] = m[c][j];
    }
    }
}

// Driver code
int main()
{
    char ch;

    // Opening file in reading mode
    ptr = fopen("input.txt", "r");
    ptr2 = fopen("output.txt", "w");

    if (NULL == ptr || NULL == ptr2)
    {
        printf("file can't be opened \n");
    }

    // Printing what is written in file
    // character by character using loop.

    int i = 0, j = 0;
    // fputs("test",ptr2);
    do
    {
        ch = fgetc(ptr);

        if (ch == ' ')
        {
            continue;
        }
        else if (ch == '\n')
        {
            if(buffer[0]=='\0')
            {
               j=0;
            }
            else
            {
            for (int k = j; k < 4; k++)
            {
                buffer[k] = '\0';
                k++;
            }
            j = 4;
            }
        }
        else
        {
            buffer[j] = ch;
            j++;
        }

        if (j == 4)
        {
            if (strcmp(buffer, "$AMJ") == 0)
            {
                printf("1)AMJ\n");
                i = 0;
            }
            else if (strcmp(buffer, "$DTA") == 0)
            {
                ch=fgetc(ptr);
                printf("2)DTA\n");
                execute();
            }
            else if (strcmp(buffer, "$END") == 0)
            {
                printf("3)END\n");
                
            }
            else // for storing the data in main memory
            {

                strcpy(m[i], buffer);
                i++;
              
            }
              for (int q = 0; q < 40; q++)
                {
                    buffer[q] = '\0';
                }
            j = 0;
            // free(buffer);
        }
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);

    // checking if input working correctly
    printf("\nInstruction Block\n"); // remove later
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c\t", m[i][j]);
        }
        printf("\t%d\t", i);
        printf("\n");
    }
    // Closing the file
    fclose(ptr);

    return 0;
}