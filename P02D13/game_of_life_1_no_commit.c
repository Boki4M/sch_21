#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

int count_live_neighbors(char field[HEIGHT][WIDTH], int row, int col);
void update_field(char current[HEIGHT][WIDTH], char next[HEIGHT][WIDTH]);
void print_field(char field[HEIGHT][WIDTH]);
void initialize_field(char field[HEIGHT][WIDTH]);

int main() {
    char current[HEIGHT][WIDTH];
    char next[HEIGHT][WIDTH];

    initialize_field(current);
    initialize_field(next);

    while (1) {
        print_field(current);
        update_field(current, next);

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                current[i][j] = next[i][j];
            }
        }

        usleep(300000);
    }

    return 0;
}

int count_live_neighbors(char field[HEIGHT][WIDTH], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < HEIGHT && c >= 0 && c < WIDTH) {
                if (field[r][c] == '0') {
                    count++;
                }
            }
        }
    }
    return count;
}

void update_field(char current[HEIGHT][WIDTH], char next[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int live_neighbors = count_live_neighbors(current, i, j);
            if (current[i][j] == '0') {
                if (live_neighbors < 2 || live_neighbors > 3) {
                    next[i][j] = ' ';
                } else {
                    next[i][j] = '0';
                }
            } else {
                if (live_neighbors == 3) {
                    next[i][j] = '0';
                } else {
                    next[i][j] = ' ';
                }
            }
        }
    }
}

void print_field(char field[HEIGHT][WIDTH]) {
    printf("\033[H\033[J");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
    fflush(stdout);
}

void initialize_field(char field[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = ' ';
        }
    }

    field[5][23] = field[5][24] = field[5][25] = field[5][26] = field[5][27] = field[5][28] = field[5][29] =
        field[5][30] = field[5][31] = field[5][32] = field[5][39] = field[5][40] = field[5][41] = '0';
    field[6][23] = field[6][24] = field[6][25] = field[6][26] = field[6][27] = field[6][28] = field[6][29] =
        field[6][30] = field[6][31] = field[6][32] = field[6][39] = field[6][40] = field[6][41] = '0';
    field[7][23] = field[7][24] = field[7][25] = field[7][26] = field[7][27] = field[7][28] = field[7][29] =
        field[7][30] = field[7][31] = field[7][32] = field[7][39] = field[7][40] = field[7][41] = '0';

    field[8][32] = field[8][33] = field[8][34] = field[8][41] = field[8][42] = field[8][43] = '0';
    field[9][32] = field[9][33] = field[9][34] = field[9][41] = field[9][42] = field[9][43] = '0';
    field[10][32] = field[10][33] = field[10][34] = field[10][41] = field[10][42] = field[10][43] = '0';

    field[11][26] = field[11][27] = field[11][28] = field[11][29] = field[11][30] = field[11][31] =
        field[11][41] = field[11][42] = field[11][43] = '0';
    field[12][26] = field[12][27] = field[12][28] = field[12][29] = field[12][30] = field[12][31] =
        field[12][41] = field[12][42] = field[12][43] = '0';
    field[13][26] = field[13][27] = field[13][28] = field[13][29] = field[13][30] = field[13][31] =
        field[13][41] = field[13][42] = field[13][43] = '0';

    field[14][23] = field[14][24] = field[14][25] = field[14][41] = field[14][42] = field[14][43] = '0';
    field[15][23] = field[15][24] = field[15][25] = field[15][41] = field[15][42] = field[15][43] = '0';
    field[16][23] = field[16][24] = field[16][25] = field[16][41] = field[16][42] = field[16][43] = '0';

    field[17][26] = field[17][27] = field[17][28] = field[17][29] = field[17][30] = field[17][31] =
        field[17][32] = field[17][33] = field[17][34] = field[17][41] = field[17][42] = field[17][43] = '0';
    field[18][26] = field[18][27] = field[18][28] = field[18][29] = field[18][30] = field[18][31] =
        field[18][32] = field[18][33] = field[18][34] = field[18][41] = field[18][42] = field[18][43] = '0';
    field[19][26] = field[19][27] = field[19][28] = field[19][29] = field[19][30] = field[19][31] =
        field[19][32] = field[19][33] = field[19][34] = field[19][41] = field[19][42] = field[19][43] = '0';
}