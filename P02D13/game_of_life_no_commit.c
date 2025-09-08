#include <stdio.h>
#include <unistd.h>

#define W 80
#define H 25

void print_field(int field[H][W]);
int count_neighbors(int f[H][W], int r, int c);
void step(int f[H][W], int next[H][W]);
void copy_field(int dst[H][W], int src[H][W]);

int main() {
    int field[H][W] = {0}, next[H][W] = {0};

    field[5][23] = field[5][24] = field[5][25] = field[5][26] = field[5][27] = field[5][28] = field[5][29] =
        field[5][30] = field[5][31] = field[5][32] = field[5][39] = field[5][40] = field[5][41] = 1;
    field[6][23] = field[6][24] = field[6][25] = field[6][26] = field[6][27] = field[6][28] = field[6][29] =
        field[6][30] = field[6][31] = field[6][32] = field[6][39] = field[6][40] = field[6][41] = 1;
    field[7][23] = field[7][24] = field[7][25] = field[7][26] = field[7][27] = field[7][28] = field[7][29] =
        field[7][30] = field[7][31] = field[7][32] = field[7][39] = field[7][40] = field[7][41] = 1;

    field[8][32] = field[8][33] = field[8][34] = field[8][41] = field[8][42] = field[8][43] = 1;
    field[9][32] = field[9][33] = field[9][34] = field[9][41] = field[9][42] = field[9][43] = 1;
    field[10][32] = field[10][33] = field[10][34] = field[10][41] = field[10][42] = field[10][43] = 1;

    field[11][26] = field[11][27] = field[11][28] = field[11][29] = field[11][30] = field[11][31] =
        field[11][41] = field[11][42] = field[11][43] = 1;
    field[12][26] = field[12][27] = field[12][28] = field[12][29] = field[12][30] = field[12][31] =
        field[12][41] = field[12][42] = field[12][43] = 1;
    field[13][26] = field[13][27] = field[13][28] = field[13][29] = field[13][30] = field[13][31] =
        field[13][41] = field[13][42] = field[13][43] = 1;

    field[14][23] = field[14][24] = field[14][25] = field[14][41] = field[14][42] = field[14][43] = 1;
    field[15][23] = field[15][24] = field[15][25] = field[15][41] = field[15][42] = field[15][43] = 1;
    field[16][23] = field[16][24] = field[16][25] = field[16][41] = field[16][42] = field[16][43] = 1;

    field[17][26] = field[17][27] = field[17][28] = field[17][29] = field[17][30] = field[17][31] =
        field[17][32] = field[17][33] = field[17][34] = field[17][41] = field[17][42] = field[17][43] = 1;
    field[18][26] = field[18][27] = field[18][28] = field[18][29] = field[18][30] = field[18][31] =
        field[18][32] = field[18][33] = field[18][34] = field[18][41] = field[18][42] = field[18][43] = 1;
    field[19][26] = field[19][27] = field[19][28] = field[19][29] = field[19][30] = field[19][31] =
        field[19][32] = field[19][33] = field[19][34] = field[19][41] = field[19][42] = field[19][43] = 1;

    while (1) {
        print_field(field);
        usleep(300000);
        step(field, next);
        copy_field(field, next);
    }

    return 0;
}

void print_field(int field[H][W]) {
    printf("\033[H\033[J");
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            printf("%c", field[r][c] ? 'o' : ' ');
        }
        printf("\n");
    }
}

int count_neighbors(int f[H][W], int r, int c) {
    int n = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int rr = r + dr, cc = c + dc;
            if (rr >= 0 && rr < H && cc >= 0 && cc < W) {
                n += f[rr][cc];
            }
        }
    }
    return n;
}

void step(int f[H][W], int next[H][W]) {
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            int alive = f[r][c];
            int n = count_neighbors(f, r, c);
            next[r][c] = (alive && (n == 2 || n == 3)) || (!alive && n == 3);
        }
    }
}

void copy_field(int dst[H][W], int src[H][W]) {
    for (int r = 0; r < H; r++)
        for (int c = 0; c < W; c++)
            dst[r][c] = src[r][c];
}