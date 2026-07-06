#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 29

#define WIN_WIDTH 70

const int WIDTH = 140;
const int HEIGHT = 35;
enum class Direction 
{ STOP = 0, LEFT, RIGHT, UP, DOWN };
using namespace std;

void gotoxy(int x, int y)
 {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void drawGameBoyInterface()
 {

    for (int i = 1; i < WIDTH; ++i) 
	{
        cout << "-";
    }
    cout << endl;


    for (int i = 0; i < HEIGHT - 2; ++i)
	 {
        cout << "|";
        for (int j = 0; j < WIDTH - 12; ++j) 
		{
       
            if (j >= 7 && j <= WIDTH - 20 && i >= 3 && i <= HEIGHT - 6) 
			{
                cout << " ";
            } else {
                cout << "*"; 
            }
        }
        cout << "|";
        cout << endl;
    }

    
    for (int i = 0; i < WIDTH; ++i)
	 {
        cout << "-";
    }
    cout << endl;
}

void displayMenu() 
{
    gotoxy(45, 5);
    cout << "Welcome to 'Game Boy'";
    gotoxy(16, 9);
    cout << "1. Dodge The Car";
    gotoxy(16, 11);
    cout << "2. Dino Game";
    gotoxy(16, 13);
    cout << "3. Snake Game" << endl;
    gotoxy(16, 17);
    cout << "Enter your choice: ";
}
//CLASS
class CarGame {
private:
    HANDLE console;
    COORD cursorPosition;
    int enemyY[3];
    int enemyX[3];
    int enemyFlag[3];
    char plane[6][42];
    int carPos;
    int score;

public:
    CarGame() {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
        carPos = WIN_WIDTH / 2;
        score = 0;

        // Initialize plane design
        char defaultCar[6][42] = {
            {' ', ' ', ' ', ' ', ' ', ' ', '/', '/', '\\', '\\', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', '_', '_', '_', '/', '/', ' ', ' ', '\\', '\\', '_', '_', '_', ' ', ' '},
            {' ', '/', '_', '_', '_', '|', '|', '0', '1', '|', '|', '_', '_', '_', '\\', ' '},
            {' ', ' ', ' ', ' ', ' ', '|', '|', ' ', ' ', '|', '|', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', '_', '_', '|', '|', '_', '_', '|', '|', '_', '_', ' ', ' '},
            {' ', ' ', ' ', '\\', '-', '-', '-', '-', '-', '-', '-', '-', '/', ' ', ' ', ' '}
        };

     
        for (int i = 0; i < 6; ++i) 
		{
            for (int j = 0; j < 42; ++j)
			 {
                plane[i][j] = defaultCar[i][j];
            }
        }
    }

    void gotoxy(int x, int y) 
	{
        cursorPosition.X = x;
        cursorPosition.Y = y;
        SetConsoleCursorPosition(console, cursorPosition);
    }


//void drawBorder() {
//    for (int i = 0; i < SCREEN_HEIGHT; i++) {
//        for (int j = 0; j < 17; j++) {
//            gotoxy(0 + j, i); cout << "±";
//            gotoxy(WIN_WIDTH - j, i); cout << "*";
//        }
//    }
//    for (int i = 0; i < SCREEN_HEIGHT; i++) {
//        gotoxy(SCREEN_WIDTH, i); cout << "*";
//    }
//}

    void genEnemy(int ind) 
	{
        enemyX[ind] = 17 + rand() % (33);
    }

    void drawEnemy(int ind) 
	{
        if (enemyFlag[ind] == true) 
		{
            gotoxy(enemyX[ind], enemyY[ind]); cout << "    ";
            gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "****";
            gotoxy(enemyX[ind], enemyY[ind] + 2); cout << " ** ";
            gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "****";
            gotoxy(enemyX[ind], enemyY[ind] + 4); cout << " ** ";
        }
    }

    void eraseEnemy(int ind) 
	{
        if (enemyFlag[ind] == true) 
		{
            gotoxy(enemyX[ind], enemyY[ind]);
			 cout << "    ";
            gotoxy(enemyX[ind], enemyY[ind] + 1); 
			cout << "    ";
            gotoxy(enemyX[ind], enemyY[ind] + 2); 
			cout << "    ";
            gotoxy(enemyX[ind], enemyY[ind] + 3); 
			cout << "    ";
        }
    }

    void resetEnemy(int ind) 
	{
        eraseEnemy(ind);
        enemyY[ind] = 1;
        genEnemy(ind);
    }

    void drawCar()
	 {
        for (int i = 0; i < 6; i++) 
		{
            for (int j = 0; j < 42; j++) 
			{
                gotoxy(j + carPos, i + 22);
                cout << plane[i][j];
            }
        }
    }

    void eraseCar()
	 {
        for (int i = 0; i < 6; i++)
		 {
            for (int j = 0; j < 42; j++) 
			{
                gotoxy(j + carPos, i + 22);
                cout << " ";
            }
        }
    }

int collision()
{
if( enemyY[0]+4 >= 23 )
{

if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos< 35 )
{

return 1;
}
}
return 0;
}


    void gameover() 
	{
        system("cls");
        cout << "==============================" << endl;
        cout << "          Game Over           " << endl;
        cout << "==============================" << endl;
        cout << "   Your Score: " << score << endl;
        cout << "==============================" << endl;
        cout << "  Press any key to exit...   " << endl;
        cout << "==============================" << endl;
    
        getch();
    }

 void updateScore()
  {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}


//    void instructions() 
//	{
//        system("cls");
//        cout << "Instructions";
//        cout << "\n----------------";
//        cout << "\n Avoid Cars by moving left or right. ";
//        cout << "\n\n Press 'a' to move left";
//        cout << "\n Press 'd' to move right";
//        cout << "\n Press 'escape' to exit";
//        cout << "\n\nPress any key to go back to menu";
//        getch();
//    }
    void clearMessage() {
    for (int i = 18; i < 62; i++) 
	{
        for (int j = 5; j < 7; j++) 
		{
            gotoxy(i, j);
            cout << " ";
        }
    }
}

 void play()
 {
        carPos = -1 + WIN_WIDTH / 2;
        score = 0;
        enemyFlag[0] = 1;
        enemyFlag[1] = 0;
        enemyY[0] = enemyY[1] = 1;

        system("cls");
       // drawBorder();
        updateScore();
        genEnemy(0);
        genEnemy(1);
        gotoxy(77, 2);
        cout << "Dodge The Car";
        gotoxy(77, 4);
        cout << "----------";

        gotoxy(77, 6);
        cout << "----------";
        gotoxy(77, 12);
        cout << "Control ";
        gotoxy(77, 13);
        cout << "-------- ";
        gotoxy(77, 14);
        cout << " A Key - Left";
        gotoxy(77, 15);
        cout << " D Key - Right";

        gotoxy(18, 5);
        cout << "Press any key to start";
        getch();
 clearMessage();
        while (1)
		 {
            if (kbhit()) 
			{
                char ch = getch();
                if (ch == 'a' || ch == 'A')
				 {
                    if (carPos > 18)
                        carPos -= 4;
                }
                if (ch == 'd' || ch == 'D')
				 {
                    if (carPos < 50)
                        carPos += 4;
                }
                if (ch == 27) {
                    break;
                }
            }

            drawCar();
            drawEnemy(0);
            drawEnemy(1);
            if (collision() == 1) 
			{
                gameover();
                return;
            }
            Sleep(50);
            eraseCar();
            eraseEnemy(0);
            eraseEnemy(1);

            if (enemyY[0] == 10)
                if (enemyFlag[1] == 0)
                    enemyFlag[1] = 1;

            if (enemyFlag[0] == 1)
                enemyY[0] += 1;

            if (enemyFlag[1] == 1)
                enemyY[1] += 1;

            if (enemyY[0] > SCREEN_HEIGHT - 4)
			 {
                resetEnemy(0);
                score++;
                updateScore();
            }
            if (enemyY[1] > SCREEN_HEIGHT - 4) 
			{
                resetEnemy(1);
                score++;
                updateScore();
            }
        }
    }
};

//CLASS 2
 class DinoGame
  {
private:
    int t;
    int speed;
    int x;
    int score;

    void gotoxy(int x, int y)
	 {
        cout << "\033[" << y << ";" << x << "H"; // ANSI escape codes for console cursor positioning
    }

    void delay(unsigned int milliseconds)
	 {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }

    void getup() 
	{
        system("cls");
        gotoxy(10, 2);
        cout << "Press X to Exit, Press Space to Jump";
        gotoxy(62, 2);
        cout << "SCORE : ";
        gotoxy(1, 25);
        for (int i = 0; i < 90; i++)
            cout << "*";
    }

    void ds(int jump = 0) 
	{
        static int a = 1;

        if (jump == 0)
            t = 0;
        else if (jump == 2)
            t--;
        else
            t++;

        gotoxy(2, 17 - t);
       cout << "                ";
        gotoxy(2, 18 - t);
        cout << "        UUUUUBBB";
        gotoxy(2, 19 - t);
        cout << " U      UUUUUB   ";
        gotoxy(2, 20 - t);
        cout << " UUU  UUUUUUUUUU ";
        gotoxy(2, 21 - t);
        cout << " BUUUUUUUUUUU  C ";
        gotoxy(2, 22 - t);
        cout << "   BUUUUUUUB     ";
        gotoxy(2, 23 - t);
        if (jump == 1 || jump == 2) 
		{
            cout << "    UUB BU       ";
            gotoxy(2, 24 - t);
            cout << "    UU   UU      ";
        } else if (a == 1) 
		{
            cout << "    BUUB  BBB    ";
            gotoxy(2, 24 - t);
            cout << "      UU         ";
            a = 2;
        } else if (a == 2)
		 {
            cout << "     BUU BU      ";
            gotoxy(2, 24 - t);
            cout << "          UU     ";
            a = 1;
        }
        gotoxy(1, 25 - t);
        if (jump !=0)
		 {
            cout << "                ";
        } else {
            cout << "BBBBBBBBBBBBBBBB";
        }
        delay(speed);
    }

    void obj() {
        if (x == 56 && t < 4)
		 {
            score = 0;
            speed = 40;
            gotoxy(36, 13);
            cout << "Game Over";
            getch();
            getup();
            gotoxy(36, 13);
            cout << "         ";
        }
        gotoxy(74 - x, 20);
        cout << "U    U ";
        gotoxy(74 - x, 21);
        cout << "U    U ";
        gotoxy(74 - x, 22);
        cout << "UUUUUU ";
        gotoxy(74 - x, 23);
        cout << "  U    ";
        gotoxy(74 - x, 24);
        cout << "  U  ";
        x++;
        if (x == 73) 
		{
            x = 0;
            score++;
            gotoxy(70, 2);
            cout << "     ";
            gotoxy(70, 2);
            cout << score;
            if (speed > 20)
                speed--;
        }
    }

public:
    DinoGame() : t(0), speed(40), x(0), score(0) {}

    void play()
	 {
        system("mode con: lines=29 cols=82");
        char ch;
        int i;
        getup();
        while (true) 
		{
            while (!kbhit()) 
			{
                ds();
                obj();
            }
            ch = getch();
            if (ch == ' ') 
			{
                for (i = 0; i < 10; i++)
				 {
                    ds(1);
                    obj();
                }
                for (i = 0; i < 10; i++)
				 {
                    ds(2);
                    obj();
                }
            } else if (ch == 'x')
                return;
        }
    }
};
  

class SnakeGame
 {
private:
    bool gameOver;
    const int width;
    const int height;
    int x, y, fruitX, fruitY, score;
    int* tailX;
    int* tailY;
    int nTail;
    Direction dir;

public:
    SnakeGame(int w, int h) : gameOver(false), width(w), height(h), x(w / 2), y(h / 2),
                               fruitX(rand() % w), fruitY(rand() % h), score(0), nTail(0), dir(Direction::STOP) {
        tailX = new int[100];
        tailY = new int[100];
    }

//    ~SnakeGame() {
//        delete[] tailX;
//        delete[] tailY;
//    }

    void Setup() 
	{
        gameOver = false;
        dir = Direction::STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        nTail = 0;
    }

    void Draw()
	 {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) 
		{
            for (int j = 0; j < width; j++)
			 {
                if (j == 0)
                    cout << "#";
                if (i == y && j == x)
                    cout << "O"; // Snake head
                else if (i == fruitY && j == fruitX)
                    cout << "*"; // Fruit
                else {
                    bool printTail = false;
                    for (int k = 0; k < nTail; k++)
					 {
                        if (tailX[k] == j && tailY[k] == i)
						 {
                            cout << "o"; // Snake tail
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        cout << "Score:" << score << endl;
    }

    void Input()
	 {
        if (_kbhit()) 
		{
            switch (_getch()) 
			{
                case 'a':
                    dir = Direction::LEFT;
                    break;
                case 'd':
                    dir = Direction::RIGHT;
                    break;
                case 'w':
                    dir = Direction::UP;
                    break;
                case 's':
                    dir = Direction::DOWN;
                    break;
                case 'x':
                    gameOver = true;
                    break;
            }
        }
    }

    void Algorithm()
	 {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < nTail; i++) 
		{
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir) 
		{
            case Direction::LEFT:
                x--;
                break;
            case Direction::RIGHT:
                x++;
                break;
            case Direction::UP:
                y--;
                break;
            case Direction::DOWN:
                y++;
                break;
            default:
                break;
        }

        if (x >= width)
            x = 0;
        else if (x < 0)
            x = width - 1;

        if (y >= height)
            y = 0;
        else if (y < 0)
            y = height - 1;

        for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        if (x == fruitX && y == fruitY)
		 {
            score += 2;
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
    }

  void Run() {
    while (!gameOver) 
	{
        Draw();
        Input();
        Algorithm();

        // Move the getch() outside the loop to wait for user input
        if (_kbhit()) 
		{
            char ch = _getch();
            if (ch == 'x')
                gameOver = true;
        }
    }
    getch(); 
}

};

  
void playDodgeTheCar(){
	CarGame game;
 game.play();
    

//    do {
////        game.gotoxy(10, 5); cout << " -------------------------- ";
////        game.gotoxy(10, 6); cout << " | plane Game | ";
////        game.gotoxy(10, 7); cout << " --------------------------";
////        game.gotoxy(10, 9); cout << "1. Start Game";
////        game.gotoxy(10, 10); cout << "2. Instructions";
////        game.gotoxy(10, 11); cout << "3. Quit";
////        game.gotoxy(10, 13); cout << "Select option: ";
//        char op = _getch();
//
//        if (op == '1') game.play();
////        else if (op == '2') game.instructions();
////        else if (op == '3') exit(0);
//
//    } while (1);
//
}

void playDinoGame() {
    system("mode con: lines=29 cols=90");  // Set console size to match the interface

    DinoGame dinoGame;
    dinoGame.play();
}



void playSnakeGame() {
     SnakeGame snakeGame(20,10);

    snakeGame.Setup();
    snakeGame.Run();
}

int main() {
    int choice;

    do {
        drawGameBoyInterface();
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                playDodgeTheCar();
                break;
            case 2:
                system("cls");
                playDinoGame();
              system("cls");
              system("cls");
                drawGameBoyInterface();
                break;
            case 3:
                system("cls");
                playSnakeGame();
                break;
            case 4:
                system("cls");
                drawGameBoyInterface();
                gotoxy(45, 10);
                cout << "===============================" << endl;
                gotoxy(45, 12);
                cout << " Exiting the game. Goodbye! " << endl;
                gotoxy(45, 14);
                cout << "===============================" << endl;
                getch(); // Wait for a key press before exiting
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 4) {
            cout << "\nPress any key to continue...";
            getch();
            system("cls");
        } else {
            // Additional clearing after returning from games
            system("cls");
        }

    } while (choice != 4);

    return 0;
}


