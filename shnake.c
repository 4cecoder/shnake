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
int score = 0;

void init() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  srand(time(NULL));

  snake[0].x = WIDTH / 2;
  snake[0].y = HEIGHT / 2;

  food.x = rand() % (WIDTH - 2) + 1;
  food.y = rand() % (HEIGHT - 2) + 1;

  refresh();
}

void draw() {
  clear();

  // Draw border
  for (int i = 0; i < WIDTH; i++) {
      mvprintw(0, i, "#");
      mvprintw(HEIGHT - 1, i, "#");
    }

    for (int i = 0; i < HEIGHT; i++) {
      mvprintw(i, 0, "#");
      mvprintw(i, WIDTH - 1, "#");
    }

    // Draw snake
    for (int i = 0; i < snake_length; i++) {
      if (i == 0) {
        mvprintw(snake[i].y, snake[i].x, "@");
      } else {
        mvprintw(snake[i].y, snake[i].x, "o");
      }
    }

    // Draw food
    mvprintw(food.y, food.x, "*");

    // Draw score
    mvprintw(0, (WIDTH / 2) - 4, "Score: %d", score);

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
    score += 10;
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
  }

  if (snake[0].x < 1 || snake[0].x >= WIDTH - 1 || snake[0].y < 1 || snake[0].y >= HEIGHT - 1) {
    endwin();
    printf("Game Over! Your final score is %d.\n", score);
    exit(0);
  }

  for (int i = 1; i < snake_length; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      endwin();
      printf("Game Over! Your final score is %d.\n", score);
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
          switch (ch) {
            case KEY_UP:
              if (direction != KEY_DOWN) {
                direction = KEY_UP;
              }
              break;
            case KEY_DOWN:
              if (direction != KEY_UP) {
                direction = KEY_DOWN;
              }
              break;
            case KEY_LEFT:
              if (direction != KEY_RIGHT) {
                direction = KEY_LEFT;
              }
              break;
            case KEY_RIGHT:
              if (direction != KEY_LEFT) {
                direction = KEY_RIGHT;
              }
              break;
          }
        }
      }

      endwin();
      return 0;
    }