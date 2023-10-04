/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: point.hh                                                   #
# Description: Declares a class representing a point in            #
# the gameboard. This was the other one of the given base-classes  #
# and here I implemented 2 new public methods for the class:       #
# return_x() and return_y(). These were used to provide me access  #
# to different Point-variables' coordinates and it really helped   #
# when creating the GUI with the snake and food moving inside it.  #
#                                                                  #
# Code template given by Tampere University,                       #
# modified by Lauri Laaksonen#                                     #
####################################################################
*/

#ifndef POINT_HH
#define POINT_HH

#include <string>

// Constants for directions
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';

class Point
{
public:
    // Default constructor, creates a new point at (0, 0).
    Point();

    // Constructor, creates a new point at the given coordinates.
    Point(int x, int y);

    // Destructor
    ~Point();

    // Comparison operators
    bool operator==(const Point& rhs) const;
    bool operator!=(const Point& rhs) const;

    // Sets a new position for the point
    void setPosition(int x, int y);

    // Moves the point into the given direction, direction can be one of
    // constants above.
    void move(const std::string& dir);

    // Tells if the point is inside the square specified by the given
    // parameters.
    bool isInside(int left_top_x, int left_top_y,
                  int right_bottom_x, int right_bottom_y) const;

    // Returns the point's x-location.
    int return_x() const;

    // Returns the point's y-location.
    int return_y() const;

private:
    // Coordinates of the point
    int x_;
    int y_;
};

#endif // POINT_HH
