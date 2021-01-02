/*
 *  2K implementation of Conway's Game of Life created by Henry Wilson
 */

 // Disable warnings for freopen in visual studio
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdint.h>     // uint8_t
#include <stddef.h>     // size_t 
#include <stdbool.h>	// booleans
#include <stdio.h>      // putchar, feof, fgetc, freopen
#include <stdlib.h>     // malloc, system

 // Cell states
#define CELL_DEAD 0
#define CELL_ALIVE 1

// Used to access 1D array as 2D array
#define at(x, y) [(x) + (y) * board_width]

#define in_bounds(x,y) ((x) >= 0 && (x) < board_width && (y) >= 0 && (y) < board_height)


typedef uint8_t board_t;

// Smaller version of atoi
int atoi(char* ch) {
    int num = 0;
    while (*ch) {
        num = (num << 3) + (num << 1) + (*ch) - '0';
        ch++;
    }
    return num;
}

int readNumerics(FILE* fp)
{
    char atoi_buf[9];
    char ch = 0;

    while (ch < '0' || ch > '9') { ch = fgetc(fp); }
    int i = 0;
    while (ch >= '0' && ch <= '9')
    {
        atoi_buf[i++] = ch;
        ch = fgetc(fp);
    }
    atoi_buf[i] = '\0';
    return atoi(atoi_buf);
}

int main()
{
    /* IMPORT STARTING STATE */
#pragma region 
    // Stores the run_count as a string
    // 19 is the maximum length of a decimal number that will fit into a int
    char atoi_buf[9];

    // stdin file pointer
    FILE* fp = stdin;

    // Current character
    char ch = 0;

    // Skip comments, get offsets#
    int o[2] = { 0, 0 };
    // Used to store sign
    int offset;
    do 
    {
        ch = fgetc(fp);
        if (fgetc(fp) == 'P')
        {
            // Wait until the board width and height have been calculated before calculating the final offset
            o[0] = readNumerics(fp);
            o[1] = readNumerics(fp);
            ch = fgetc(fp);
        }
    } while (ch != 'x');

    // Board dimensions
    int dim[2];
#define board_width dim[0]
#define board_height dim[1]
    // Get board_width and board_height values
    for (int i = 0; i < 2; i++)
    {
        dim[i] = readNumerics(fp);
    }

    // Calculate the final offset value
    offset = o[0] + o[1] * board_width;

    // Allocate board space and scratch space
    board_t* board = (board_t*)calloc(board_width * board_height, sizeof(board_t));
    board_t* buf = (board_t*)calloc(board_width * board_height, sizeof(board_t));

    // The amount of times the RLE copies the cell
    int run_count = 0;
    int run_sum = 0;

    // Convert file contents to board state
    while (!feof(fp))
    {
        // Stores cell state of cell which is being copied for RLE 
        int cell_state;

        // Get run_count
        ch = fgetc(fp);
        int i = 0;
        atoi_buf[0] = '\0';
        while (ch >= '0' && ch <= '9')
        {
            atoi_buf[i++] = ch;
            ch = fgetc(fp);
        }
        atoi_buf[i] = '\0';
        run_count = atoi(atoi_buf);

        // Add cell(s) to board
        if (ch == 'b')
        {
            cell_state = CELL_DEAD;
        }
        else if (ch == 'o')
        {
            cell_state = CELL_ALIVE;
        }
        else if (ch == '$')
        {
            // Pad Lines
            run_sum = board_width - run_sum + 1;
            while (run_sum-- > 1)
            {
                board[offset++] = CELL_DEAD;
            }
            continue;
        }
        else
        {
            continue;
        }

        do
        {
            run_sum++;
            run_count--;
            board[offset++] = cell_state;
        } while (run_count > 0);
    }

    // Redirect stdin to console
    freopen("conin$", "r", fp);
#pragma endregion

    /* MAIN LOOP */
    while (true)
    {
        system("cls");
        /* PROGRESS LIFE BY ONE STEP */
#pragma region 
        // For each cell
        for (int y = 0; y < board_height; y++)
        {
            for (int x = 0; x < board_width; x++)
            {
                // Get living neighbours
                uint8_t neighbours = 0;
                for (int i = -1; i < 2; i++)
                    for (int j = -1; j < 2; j++)
                    {
                        neighbours += (in_bounds(x + i, y + j) &&     // Only compute if in bounds
                            board at(x + i, y + j) == CELL_ALIVE) &&  // Returns 1 if cell is alive
                            !(i == 0 && j == 0);                      // Return 0 if cell is current cell
                    }

                int p = x + y * board_width;

                if (board[p] == CELL_ALIVE)
                {
                    if (neighbours < 2)
                    {
                        buf[p] = CELL_DEAD;   /* CELL UNDER POPULATED */
                    }
                    else if (neighbours < 4)
                    {
                        buf[p] = CELL_ALIVE;  /* CELL FINE */
                    }
                    else
                    {
                        buf[p] = CELL_DEAD;   /* CELL OVER POPULATED */
                    }
                }
                else if (neighbours == 3)
                {
                    buf[p] = CELL_ALIVE;      /* CELL REPRODUCES */
                }
                else
                {
                    buf[p] = CELL_DEAD;       /* CELL UNCHANGED */
                }


                // Display board
                if (board[p] == 1)
                {
                    putchar('*');
                }
                else
                {
                    putchar(' ');
                }
            }
            putchar('\n');
        }

        // Swap buffers
        board_t* temp = board;
        board = buf;
        buf = temp;
#pragma endregion

        /* INPUT */
        if (fgetc(fp) == 'e')
            break;
    }

    return 0;
}
