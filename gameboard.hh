/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: gameboard.hh                                               #
# Description: Declares a class representing the gameboard. This   #
#              class is given as a part of the base code, but I    #
#              personally have altered it by creating a few public #
#              functions ( get_food_x(), get_food_y(),             #
#              get_snake_head_x(), get_snake_head_y(),             #
#              return_snake() and collision_with_self(). These     #
#              were methods I simply needed to create the project, #
#              since they provide me access to required data.      #
#                                                                  #
# Code template given by Tampere University,                       #
# modified by Lauri Laaksonen#                                     #
####################################################################
*/

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "point.hh"
#include <random>
#include <string>
#include <deque> // Better than vector, since we need erase front elements

// Constants for printing the gameboard
const std::string BODY = "~";
const std::string DEAD = "X";
const std::string FOOD = "*";
const std::string HEAD = "@";
const std::string TAIL = "-";
const std::string WALL = "#";
const std::string EMPTY = " ";

const int DEFAULT_WIDTH = 5;
const int DEFAULT_HEIGTH = 6;
const int DEFAULT_SEED = 1;

class GameBoard {
public:
    // Default constructor.
    // Calls the other constructor with default width, height, and seed.
    GameBoard();

    // Constructs a gameboard based the given width and height,
    // rng is used to generate random locations for the food.
    GameBoard(int width, int height, int seed_value);

    // Destructor
    ~GameBoard();

    // Checks if the game is over.
    // Returns false until the game has been either lost or won.
    bool gameOver() const;

    // Checks if the game has been lost.
    // Returns true if the snake is dead.
    bool gameLost() const;

    // Checks if the game has been won.
    // Returns true if the snake has filled the field.
    bool gameWon() const;

    // Moves the snake to the given direction, if possible.
    // Moving is not possible, if game is over, or if the snake would move
    // against a wall.
    // If moving is possible, calls the private method moveSnakeAndFood.
    // Returns true, if moving was possible.
    bool moveSnake(const std::string& direction);

    // Prints the gameboard and the snake in it.
    void print() const;

    // Returns the snake's foods x-location on the gameboard.
    int get_food_x() const;

    // Returns the snake's foods y-location on the gameboard.
    int get_food_y() const;

    // Returns the snake's heads x-location on the gameboard.
    int get_snake_head_x() const;

    // Returns the snake's heads y-location on the gameboard.
    int get_snake_head_y() const;

    // Returns the snake_ deque to inspect all the snake's locations in the
    // mainwindow.cpp file
    std::deque<Point> return_snake() const;

    // Inspects the death cause. Returns true if collision with itself, other-
    // wise returns false (collision with a wall).
    bool collision_with_self(std::string prev_direction) const;

private:
    // Returns true if the given point is a part of the snake.
    bool isSnakePoint(const Point& point) const;

    // Returns the point of the snake's head.
    const Point& getHead() const;

    // Returns the point of the snake's tail.
    const Point& getTail() const;

    // Relocates food to a random, snakeless location.
    // Hides the food if the snake has completely filled the gameboard.
    void moveFood();

    // Moves the snake unless the new head would be the body of the snake.
    // If the new head is the neck of the snake, nothing happens.
    // If the new head is other body part of the snake, the snake dies.
    // Otherwise the snake moves, whereupon the method returns true.
    // If, in addition, the food got eaten a new one is placed somewhere,
    // and the snake grows a bit.
    bool moveSnakeAndFood(const Point& new_head);

    // Prints the top or bottom wall of the gameboard.
    void printHorizontalWall() const;

    // Tells if the snake is alive and able to move.
    bool dead_ = false;

    // Specifies the width and height of the gameboard.
    const int width_ = 0;
    const int height_ = 0;

    // Generates random numbers used to move the food item to random locations.
    std::default_random_engine rng_;

    // Points currently occupied by the snake, head being the last one.
    std::deque<Point> snake_;

    // The food item's position in the gameboard.
    Point food_;
};  // class GameBoard


#endif  // GAMEBOARD_HH
