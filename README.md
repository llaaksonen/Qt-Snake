# Qt-Snake
This project was a part of our university's C++ programming course. As a task for this project, we were instructed to create a GUI for a snake game.
As a template, we were given an ASCII-styled snake game (files: gameboard.hh, point.hh, gameboard.cpp and point.cpp).

Instructions for the game:

When you boot up the program for the first time, you are greeted with a
pink-ish screen full of various buttons. Some of these buttons can be pressed
and some can't be pressed ( yet ). First, the program wants you to input values
for the width, height and seed, which will be used to construct the gameboard
itself. You can do this by accessing the spinboxes above the huge white game-
screen. Width and height values can be set from 3 to 10 both and the seed can be
anything from -99 to 99. After selecting values of your liking, you need to
press the Set-button located next to these spinboxes. You can change these
settings before starting the game.

After you have set your setting values, the gameboard is constructed in the
program and it will become visible to your screen. There you can spot your snake
( the yellow square - which indicates its head ) and a randomly selected food.
Your goal is to eat the food with the snake, by moving the snake with the arrow
buttons <, ^, v, > shown on the right side of your screen. You cant make 180
degree turns after your size is greater than 1 !!! Each time you eat an apple,
your snakes length increases by 1, and the food will be placed to another random
place on the board. The parts of the snake also have differences. As said before
the yellow square indicates its head. The snakes middle body will consist of red
squares and it's tail is a blue square. So when you play, focus on the yellow
square: it leads all the other squares, which follow it. ***IMPORTANT : Eating
also increases your speed Eat so much food, that you fill the whole gameboard
and you win the game. Crash into a wall or accidentally eat yourself and you
lose the game!

Now that you understand the games rules, it's time to play. Start the game by
simply pressing the start button on the top right corner. After doing so, your
snake starts automatically moving to the right. The snake moves between every
1 seconds, so be ready to press those arrow buttons on the SCREEN!

When you play the game, your score, the elapsed time and your snakes length will
be shown near the top right corner. A little info about these:

- Score  : Your score will be calculated by increasing it with the value based
           on the time you have spent since you ate your last apple. The less
           time you spend on getting to the next food, the more points you will
           be given and vice versa. This means, that in the end you will get
           more points from the food, since the game is much harder to play
           then!

- Time   : Shows the elapsed time as seconds based on how much you have spent in
           the game.

- Length : Displays your snakes length. Will start as 1 and always increases by
           1 when you eat food. How long will you become!?

You can always Pause your __started__ game. This can be done by pressing the
Pause/Resume button. Click it once to pause the game and click it twice to
resume it.

You also can always reset your game. This can be done by pressing the Reset-
button on the screen. When you press the button, your gamescreen will be cleared
and you need to assign new setting values for the game to start playing again.

When you are done playing, you can close the game by pressing the Quit-button.
This closes the program completely and lets you move on with your life.
