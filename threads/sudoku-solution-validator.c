#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define SIZE 9

// Structure for passing data to threads
typedef struct {
    int row;
    int column;
    int result;
} Parameters;

int sudoku[SIZE][SIZE] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

// Function to check if a number is valid in a particular row
void *isValidRow(void *args) {
    Parameters *params = (Parameters *)args;
    int row = params->row;
    int col = params->column;
    bool visited[SIZE] = {false};

    for (int j = col; j < col + SIZE; j++) {
        int num = sudoku[row][j % SIZE];
        if (num < 1 || num > SIZE || visited[num - 1]) {
            params->result = 0;
            pthread_exit(NULL);
        }
        visited[num - 1] = true;
    }

    params->result = 1;
    pthread_exit(NULL);
}

// Function to check if a number is valid in a particular column
void *isValidColumn(void *args) {
    Parameters *params = (Parameters *)args;
    int row = params->row;
    int col = params->column;
    bool visited[SIZE] = {false};

    for (int i = row; i < row + SIZE; i++) {
        int num = sudoku[i % SIZE][col];
        if (num < 1 || num > SIZE || visited[num - 1]) {
            params->result = 0;
            pthread_exit(NULL);
        }
        visited[num - 1] = true;
    }

    params->result = 1;
    pthread_exit(NULL);
}

// Function to check if a number is valid in a particular 3x3 square
void *isValidSquare(void *args) {
    Parameters *params = (Parameters *)args;
    int row = params->row;
    int col = params->column;
    bool visited[SIZE] = {false};

    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > SIZE || visited[num - 1]) {
                params->result = 0;
                pthread_exit(NULL);
            }
            visited[num - 1] = true;
        }
    }

    params->result = 1;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[SIZE + SIZE + SIZE]; // 9 rows + 9 columns + 9 subgrids
    Parameters params[SIZE + SIZE + SIZE];

    // Create threads to check rows
    for (int i = 0; i < SIZE; i++) {
        params[i].row = i;
        params[i].column = 0;
        pthread_create(&threads[i], NULL, isValidRow, &params[i]);
    }

    // Create threads to check columns
    for (int i = 0; i < SIZE; i++) {
        params[SIZE + i].row = 0;
        params[SIZE + i].column = i;
        pthread_create(&threads[SIZE + i], NULL, isValidColumn, &params[SIZE + i]);
    }

    // Create threads to check 3x3 squares
    for (int i = 0; i < SIZE; i++) {
        params[SIZE + SIZE + i].row = (i / 3) * 3;
        params[SIZE + SIZE + i].column = (i % 3) * 3;
        pthread_create(&threads[SIZE + SIZE + i], NULL, isValidSquare, &params[SIZE + SIZE + i]);
    }

    // Join threads and check results
    for (int i = 0; i < SIZE + SIZE + SIZE; i++) {
        pthread_join(threads[i], NULL);
        if (params[i].result == 0) {
            printf("Invalid Sudoku solution.\n");
            return 0;
        }
    }

    printf("Valid Sudoku solution.\n");
    return 0;
}