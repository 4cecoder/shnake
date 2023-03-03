#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // for usleep()

#define WIDTH 40
#define HEIGHT 20

typedef struct {
  int x, y;
} point;

point snake[100];
int snake_length = 1;
int direction = KEY_RIGHT;
point food;

void init() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  srand(time(NULL));

  snake[0].x = WIDTH / 2;
  snake[0].y = HEIGHT / 2;

  food.x = rand() % WIDTH;
  food.y = rand() % HEIGHT;

  refresh();
}

void draw() {
  clear();

  for (int i = 0; i < snake_length; i++) {
    mvprintw(snake[i].y, snake[i].x, "O");
  }

  mvprintw(food.y, food.x, "X");

  refresh();
}

void update() {
  for (int i = snake_length - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }

  switch (direction) {
  case KEY_UP:
    snake[0].y--;
    break;
  case KEY_DOWN:
    snake[0].y++;
    break;
  case KEY_LEFT:
    snake[0].x--;
    break;
  case KEY_RIGHT:
    snake[0].x++;
    break;
  }

  if (snake[0].x == food.x && snake[0].y == food.y) {
    snake_length++;
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
  }

  if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT) {
    endwin();
    exit(0);
  }

  for (int i = 1; i < snake_length; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      endwin();
      exit(0);
    }
  }
}

int main() {
  init();

  while (1) {
    draw();
    update();
    usleep(100000);
    int ch = getch();
    if (ch != ERR) {
      direction = ch;
    }
  }

  endwin();
  return 0;
}
