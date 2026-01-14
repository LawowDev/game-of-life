#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <locale.h>

int height = 100;
int width = 100;

void randomize(int** state)
{
    srand(time(NULL));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            state[i][j] = rand() % 2;
        }
    }
}

void draw_state(int** state)
{
    clear();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (state[i][j] == 1)
            {
                mvprintw(i, 2*j, "██");
            }
            else
            {
                mvprintw(i, 2*j, "  ");
            }
        }
    }

    refresh();
}

void add_around(int** tab, int a, int b)
{
    for (int i = a-1; i < a+2; i++)
    {
        for (int j = b-1; j < b+2; j++)
        {
            if (i < height && j < width && i >= 0 && j >= 0 && (i != a || j != b)) tab[i][j] += 1;
        }
    }
}

void next_state(int** state)
{

    int** proximity_tab = malloc(sizeof(int*)*height);
    for (int i = 0; i < height; i++)
    {
        int* temp = calloc(width, sizeof(int));
        proximity_tab[i] = temp;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (state[i][j] == 1)
            {
                add_around(proximity_tab, i, j);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (proximity_tab[i][j])
            {
                case 3:
                    state[i][j] = 1;
                    break;
                
                case 2:
                    break;
                
                default:
                    state[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        free(proximity_tab[i]);
    }

    free(proximity_tab);
}



int main(void)
{
    int** state_tab = malloc(sizeof(int*)*height);
    for (int i = 0; i < height; i++)
    {
        int* temp = malloc(sizeof(int)*width);
        state_tab[i] = temp;
    }

    setlocale(LC_ALL, "");
    initscr();
    randomize(state_tab);
    draw_state(state_tab);

    while (1)
    {
        char input = getch();

        if (input == 'a')
        {
            next_state(state_tab);
            draw_state(state_tab);
        }

        if (input == 'w')
        {
            break;
        }
    }

    for (int i = 0; i < height; i++)
    {
        free(state_tab[i]);
    }

    free(state_tab);
    return EXIT_SUCCESS;
}
