# Console Game Boy (C++)

A console-based **Game Boy** built in **C++** that includes three classic mini-games in a single application. The project demonstrates object-oriented programming, console graphics, keyboard input handling, and basic game development concepts using the Windows Console API.

## Overview

This project contains three playable console games:

- Dodge The Car
- Dino Game
- Snake Game

The application provides a menu-driven interface that allows users to select and play any of the available games.

## Games Included

### Dodge The Car

- Move left and right to avoid incoming obstacles.
- Score increases as you survive.
- Collision detection and game over screen.

### Dino Game

- Jump over obstacles.
- Increasing difficulty as the score increases.
- Endless runner gameplay.

### Snake Game

- Classic Snake gameplay.
- Collect food to grow the snake.
- Game ends when the snake collides with itself.

## Features

- Console-based graphical interface
- Menu-driven game selection
- Object-Oriented Programming (OOP)
- Keyboard controls
- Score tracking
- Collision detection
- Windows Console API (`windows.h`)
- ANSI cursor positioning
- Multiple mini-games in one application

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- Windows Console API
- `windows.h`
- `conio.h`
- `chrono`
- `thread`

## Controls

### Dodge The Car

| Key | Action |
|------|--------|
| A | Move Left |
| D | Move Right |
| ESC | Exit Game |

### Dino Game

| Key | Action |
|------|--------|
| Space | Jump |
| X | Exit |

### Snake Game

| Key | Action |
|------|--------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| X | Exit |

## Project Structure

```
GameBoy/
│── main.cpp
│── README.md
```

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/your-username/your-repository-name.git
```

2. Open the project in a C++ IDE such as Visual Studio, Code::Blocks, or Dev-C++.

3. Compile the project using a Windows C++ compiler (MSVC or MinGW).

4. Run the executable.

## Requirements

- Windows Operating System
- C++ Compiler (MSVC or MinGW)
- Windows Console

## Concepts Demonstrated

- Object-Oriented Programming
- Classes and Objects
- Arrays
- Enums
- Game Loop
- Collision Detection
- Random Number Generation
- Keyboard Event Handling
- Console Cursor Manipulation

## Author

Developed as a C++ console application to demonstrate object-oriented programming concepts and basic game development using the Windows Console API.
