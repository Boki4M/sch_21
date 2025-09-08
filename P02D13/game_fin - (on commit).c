#include <ncurses.h>  //библиотека для создания текстового интерфейса
#include <stdio.h>    //стандартная библиотека ввода и вывода
#include <unistd.h>   //библиотека для задержки выполнения (функция usleep)

// Определяем константы для размера игрового поля
#define WIDTH 80   // деректива задающая размер ШИРИНЫ поля - 80 символов
#define HEIGHT 25  // деректива задающая размер ВЫСОТЫ поля - 25 символов

// объявление функций (прототипы)
int count_live_neighbors(char field[HEIGHT][WIDTH], int row, int col);
void update_field(char current[HEIGHT][WIDTH], char next[HEIGHT][WIDTH]);
void print_field(char field[HEIGHT][WIDTH], int delay);
void initialize_field(char field[HEIGHT][WIDTH]);

// главная функция программы
int main() {
    initscr();  // инициализация экрана из библиотеки <ncurses>
    cbreak();   // отключение буферизации ввода (не нужно писать команду и запускать ее, символы сразу
                // доступны)
    noecho();   // отключение вывода нажатых клавиш
    nodelay(stdscr, TRUE);  // отмена ожидания нажатия клавиш
    curs_set(0);            // скрытие курсора
    keypad(stdscr, TRUE);   // Включить расширенные клавиши (на всякий случай)

    // создание и инициализация игровых полей
    char current[HEIGHT][WIDTH] = {0};  // текущее состояние поля
    char next[HEIGHT][WIDTH] = {0};     // следующее состояние поля (буфер)

    // заполнение полей начальными значениями
    initialize_field(current);  // инициализация текущего поля
    initialize_field(next);     // инициализация буферного поля

    // настройка параметров скорости анимации
    int delay = 300000;             // Начальная задержка в микросекундах (0.3 сек)
    const int min_delay = 50000;    // Минимальная задержка (0.05 сек)
    const int max_delay = 1000000;  // Максимальная задержка (1.0 сек)
    const int step = 50000;         // Шаг изменения скорости

    // основной игровой цикл
    while (1) {
        // отображение текущего состояния поля
        print_field(current, delay);

        // обработка пользовательского ввода
        int ch = getch();                                  // получение символов из входного буфера
        if (ch == '\x20') {                                // если нажать пробел (ascii 32 = 0х20)
            break;                                         // выход из цикла
        } else if (ch == 'a' || ch == 'A') {               // если нажать 'А' (ускорить)
            if (delay > min_delay) {                       // проверка, не достигнут ли минимум
                delay -= step;                             // уменьшение задержки (ускорение)
                if (delay < min_delay) delay = min_delay;  // защита от превышения минимума
            }
        } else if (ch == 'z' || ch == 'Z') {               // если нажать 'Z' (замедлить)
            if (delay < max_delay) {                       // проверка не достигнут-ли максимум
                delay += step;                             // увеличение задержки (замедление)
                if (delay > max_delay) delay = max_delay;  // защита от превышения максимума
            }
        }

        // обновление состояния игры
        update_field(current, next);  // расчет следующего состояния

        // копирование следующего состояния в текущее (next -> current)
        for (int i = 0; i < HEIGHT; i++) {     // для каждой строки
            for (int j = 0; j < WIDTH; j++) {  // для каждого столбца
                current[i][j] = next[i][j];    // копирование значения
            }
        }

        usleep(delay);  // Задержка с учётом управления
    }

    // завершение работы с ncurses
    endwin();  // востановление терминала в исходное состояние
    return 0;  // успешное завершение программы
}

// функция подсчета живых соседей
int count_live_neighbors(char field[HEIGHT][WIDTH], int row, int col) {
    int count = 0;  // счетчик живых соседей
    // проверка всех 8-ми соседних клеток
    for (int i = -1; i <= 1; i++) {          // для смещения по вертикали (-1, 0, 1)
        for (int j = -1; j <= 1; j++) {      // для смещения по горизонтали (-1, 0, 1)
            if (i == 0 && j == 0) continue;  // пропуск самой клетки
            int r = row + i;                 // вычисление СТРОКИ соседа
            int c = col + j;                 // вычисление СТОЛБЦА соседа
            // проверка, что соседи в пределах поля
            if (r >= 0 && r < HEIGHT && c >= 0 && c < WIDTH) {
                if (field[r][c] == '0') {  // если сосед живой
                    count++;               // увеличить счетчик
                }
            }
        }
    }
    return count;  // возврат живых соседей
}

// функция обновления состояния игрового поля
void update_field(char current[HEIGHT][WIDTH], char next[HEIGHT][WIDTH]) {
    // обход всех клеток поля
    for (int i = 0; i < HEIGHT; i++) {                                 // для каждой строки
        for (int j = 0; j < WIDTH; j++) {                              // для каждого столбца
            int live_neighbors = count_live_neighbors(current, i, j);  // подсчет соседей

            // применение правил игры "Жизнь"
            if (current[i][j] == '0') {  // если клетка живая
                if (live_neighbors < 2 ||
                    live_neighbors > 3) {  // если соседей меньше 2 или больше 2 (правило 1 и 2)
                    next[i][j] = ' ';      // клетка умирает
                } else {
                    next[i][j] = '0';  // иначе остается живой
                }
            } else {
                if (live_neighbors == 3) {  // если живых соседей вокруг мертвой равно 3 (правило 4)
                    next[i][j] = '0';       // клетка рождается
                } else {
                    next[i][j] = ' ';  // клетка остается мертвой
                }
            }
        }
    }
}

// функция отображения игрового поля
void print_field(char field[HEIGHT][WIDTH], int delay) {
    clear();  // очиства экрана

    // рисуем игровое поле
    for (int i = 0; i < HEIGHT; i++) {     // для каждой строки
        for (int j = 0; j < WIDTH; j++) {  // для каждого столбца
            mvaddch(i, j, field[i][j]);  // функция из библиотеки ncurses, выводящая символы в позицию (i, j)
        }
    }

    // строка статуса внизу (информационная строка)
    int fps = (delay > 0) ? 1000000 / delay : 0;                     // подсчет скорости
    mvprintw(HEIGHT, 0, "A (faster), Z (slower), Spacebar (exit)");  // подсказка управления
    mvprintw(HEIGHT + 1, 0, "Speed: %d mks (%d fps)", delay, fps);   // текущая скорость

    refresh();  // обновление экрана
}

// функция инициализации начального состояния поля
void initialize_field(char field[HEIGHT][WIDTH]) {

    // заполнение всего поля пробелами (мертвые клетки)
    for (int i = 0; i < HEIGHT; i++) { // для каждой строки
        for (int j = 0; j < WIDTH; j++) { // для каждого столбца
            field[i][j] = ' '; // мертва клетка
        }
    }

    // Создание начальной конфигурации (живых клеток)
    // Установка живых клеток ('0') в определенных позициях
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