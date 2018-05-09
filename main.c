#include <stdio.h>
#include <string.h>

struct Field {
    int value;
    int valid;
    int possibility[10];
} sudoku[9][9];

// TODO sudoku is pass through a global namespace, consider passing via arguments

void readSudoku(char *sudokuFile) {
    char filename[128];
    sprintf(filename, "./../data/%s", sudokuFile);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        printf("Unable to open file %s\n", filename);
    }
    int c, value, col, row, i = 0;
    while ((c = getc(fp)) != EOF) {
        if (c == 32) {
            continue;
        } else if (c >= 48 && c <= 57) {
            value = c - 48;
            row = i / 9;
            col = i % 9;
            sudoku[row][col].value = value;
            if (value > 0) {
                sudoku[row][col].valid = 1;
            } else {
                sudoku[row][col].valid = 0;
            }
            i++;
        } else {
            perror("Invalid input data structure (digits should be separated with space)");
        }
    }
    if (i != 81) {
        perror("Invalid input data length (file should has 81 space separated digits)");
    }
    fclose(fp);
}

void writeSudoku(char *sudokuFile) {
    char filename[128];
    sprintf(filename, "./../solutions/%s", sudokuFile);
    FILE *fp = fopen(filename, "w+");
    if (!fp) {
        perror("Failed to open file");
        printf("Unable to open file %s\n", filename);
    }

    char chunk[3];
    char output[256];
    memset(output, 0, sizeof(output));
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sprintf(chunk, "%d ", sudoku[row][col].value);
            strcat(output, chunk);
        }
    }
    output[strlen(output) - 1] = NULL;
    fputs(output, fp);
    fclose(fp);
}

void printSudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            printf("%d ", sudoku[row][col].value);
        }
        printf("\n");
    }
}

int main() {
    readSudoku("sudoku04.txt");
    printSudoku();
    writeSudoku("sudoku04.txt");
    return 0;
}