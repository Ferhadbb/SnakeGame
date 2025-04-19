#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
//Board dimesnions
#define WIDTH 40
#define HEIGHT 20

// Creating Snake(Limited to 100)
int snakeX[100];
int snakeY[100];
int length = 1;

int foodX;
int foodY;
int direction = 0;
int gameOver = 0;
int score = 0;

void setup();
void draw();
void move();
void checkInput();

int main() {
    setup();

    // Game loop itself
    while (gameOver == 0) {
        draw();
        checkInput();
        move();
        Sleep(150);
    }
    printf("\nGame Over! Score: %d\n", score);
    return 0;
}

// Game Setup
void setup() {
    srand(time(NULL)); // Using this to make sure Random is different each time

    snakeX[0] = 5;  // Snakes start position
    snakeY[0] = 5;
    length = 1; //Snakes start lenght

    // Placing first food
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

//Creatung the board
void draw() {
    system("cls");

    //First line
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    //Middle parts
    for (int y = 0; y < HEIGHT; y++) {
        printf("#");
        for (int x = 0; x < WIDTH; x++) {
            // Upon drawing board checking if snake is existing in this square
            int isSnake= 0;
            for (int i = 0; i < length; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    printf("*"); // Draws snakes body if coordinates are equal
                    isSnake = 1;
                    break;
                }
            }
            // If didnt encnter snake then check for food
            if (isSnake == 0 && x == foodX && y == foodY) {
                printf("@"); // Draw food using same logic
            }
            // if there are no objects place space
            else if (isSnake == 0) {
                printf(" ");
            }
        }
        printf("#\n");
    }

    // Bottom of boaerd
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\nScore: %d\n", score);
} // Added this missing closing brace

// Keyboard input (Used gpt for explanation and interpretation)
void checkInput() {
    if (_kbhit()) { // If a key is pressed
        char key = _getch(); // Recording the key press
        if (key == 'w' && direction != 1) direction = 3; // If not goin down go up
        if (key == 's' && direction != 3) direction = 1; // if not going up go down
        if (key == 'a' && direction != 0) direction = 2; // if not going right  go left
        if (key == 'd' && direction != 2) direction = 0; // if not going left go right
    }
}

// Snake movement
void move() {
    // Moving the body
    for (int i = length - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Move the head based on direction
    if (direction == 0) snakeX[0]++; // Right
    if (direction == 1) snakeY[0]++; // Down
    if (direction == 2) snakeX[0]--; // Left
    if (direction == 3) snakeY[0]--; // Up

    // Check if snake hits food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        score = score + 1;
        length = length + 1;
        // Spawn food(random)
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }

    // Check if snake hits walls
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        gameOver = 1;
    }

    // Check if snake hits itself
    for (int i = 1; i < length; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
        }
    }
}
