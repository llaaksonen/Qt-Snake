/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2022                                    #
# GUI-Project: snake_gui                                                    #
# File: mainwindow.cpp                                                      #
# Description: This is the .cpp file of the GameBoard class. Here is        #
#              written all the methods used in the GUI-program and their    #
#              functionality is also commented here.                        #
#                                                                           #
# Program author:                                                           #
#              * Name: Lauri Laaksonen                                      #
#############################################################################
*/

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <QGraphicsView>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // Assigning the graphics scene to its designated location on the UI
    scene_ = new QGraphicsScene(this);

    // Disabling unusable pushButtons from the ui.
    modify_buttons(false);

    // Disablign the play button
    ui_->play_pushButton->setDisabled(true);

    // Disabling the pause button
    ui_->pause_pushButton->setDisabled(true);

    // Setting up the default background color.
    this->setStyleSheet("background-color: rgb(255, 151, 255);");
    ui_->graphicsView->setBackgroundBrush(Qt::white);

    ui_->info_textBrowser->setText("Welcome to snake_gui ! Please adjust the "
                                   "game's settings from the spinboxes above "
                                   "and assign them by pressing the "
                                   "Set-button.");

    // Setting up the timers used in the program.
    setup_timers();
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete scene_;
    delete seconds_timer_;
    delete move_timer_;
}

void MainWindow::on_set_pushButton_clicked()
{
    // Defining the gameboard with the user given settings
    field_ = std::make_shared<GameBoard>(ui_->width_spinBox->value(),
                                         ui_->height_spinBox->value(),
                                         ui_->seed_spinBox->value());

    make_grid();

    // Printing a short info on the programs functionality with some instructio-
    // ns to a designated spot (info_textBrowser)
    QString info_text = "Your aim is to guide the snake to the food around the "
                        "field while avoiding the walls and the ever-growing "
                        "snake itself. The snake can't make 180 degree turns, "
                        "which means that it can't go directly back to the "
                        "square it came from, unless the snake occupies only "
                        "one square in total. When you're ready to play, press "
                        "the Play-button from the top right corner and start "
                        "playing by moving the snake with the buttons next to "
                        "the gameboard!";
    ui_->info_textBrowser->setText(info_text);

    // Making the play_pushButton enabled so the game can be started by pressing
    // it
    ui_->play_pushButton->setEnabled(true);

    // Setting up the first look on the gameboard, if the screen is empty
    if ( ui_->graphicsView->items().empty() )
    {
        setup_graphics();
    }
    // Otherwise, clearing the screen and filling it with new items
    else
    {
        clear_screen();
        setup_graphics();
    }
}

void MainWindow::on_play_pushButton_clicked()
{
    // Making the direction pushButtons enabled so the game can be played by
    // pressing them separately
    modify_buttons(false);

    ui_->play_pushButton->setDisabled(true);

    // Hiding the width-, height- and seed-spinboxes until they are needed again
    modify_spinboxes(true);

    // Clearing the info text, so it doesn't bother the player, when they start
    // the game
    ui_->info_textBrowser->clear();

    // Making the play-button disabled (you can't start a game when it's already
    // started)
    ui_->play_pushButton->setDisabled(true);

    // Starting the timers
    seconds_timer_->start(1000);
    move_timer_->start(snake_speed_);

    has_started_ = true;
}

void MainWindow::on_up_pushButton_clicked()
{
    // Checking move directions
    check_move("s", "w");
}

void MainWindow::on_right_pushButton_clicked()
{
    // Checking move directions
    check_move("a", "d");
}

void MainWindow::on_down_pushButton_clicked()
{
    // Checking move directions
    check_move("w", "s");
}

void MainWindow::on_left_pushButton_clicked()
{
    // Checking move directions
    check_move("d", "a");
}

void MainWindow::seconds_tick()
{
    // When the timer ticks, add 1 to the seconds-time_ -counter
    time_ += 1;
    ui_->time_lcdNumber->display(time_);

    // Also increase the time gone since the last food eaten.
    time_since_last_food_ += 1;
}

void MainWindow::move_tick()
{
    // Defining the locations of the snake's head and the food.
    int snake_x = field_->get_snake_head_x();
    int snake_y = field_->get_snake_head_y();
    int food_x = field_->get_food_x();
    int food_y = field_->get_food_y();

    if ( current_direction_ == "w" )
    {
        field_->moveSnake(current_direction_);
        square_->setPos(snake_x * SIZE, snake_y * SIZE);
    }
    else if ( current_direction_ == "d" )
    {
        field_->moveSnake(current_direction_);
        square_->setPos(snake_x * SIZE, snake_y * SIZE);
    }
    else if ( current_direction_ == "s" )
    {
        field_->moveSnake(current_direction_);
        square_->setPos(snake_x * SIZE, snake_y * SIZE);
    }
    else
    {
        field_->moveSnake(current_direction_);
        square_->setPos(snake_x * SIZE, snake_y * SIZE);
    }

    // Checking if the snake ate the food after moving it.
    check_hit(food_x, food_y);
}

void MainWindow::on_reset_pushButton_clicked()
{
    has_started_ = false;

    // The game has been reseted, returning the game to the set-state.
    seconds_timer_->stop();
    time_ = 0;
    move_timer_->stop();

    // Current direction is set to default (right)
    current_direction_ = "d";

    reseted_ = true;
    change_background_color();

    // Making the spinboxes visible again
    modify_spinboxes(false);

    // Disabling the buttons
    modify_buttons(true);
    ui_->pause_pushButton->setDisabled(true);
    ui_->play_pushButton->setDisabled(true);

    // Making all the lcdNumber values 0
    ui_->time_lcdNumber->display(0);
    ui_->score_lcdNumber->display(0);
    ui_->length_lcdNumber->display(1);

    // Clearing the GraphicsScene
    scene_->clear();

    ui_->info_textBrowser->setText("Your game has been reseted. Please select "
                                   "new settings from the spinboxes above and "
                                   "press the Set-button to start playing.");

    snake_speed_ = NORMAL_SPEED;

    // The reset-operation has ending, making the reseted variable false again
    reseted_ = false;
}

void MainWindow::on_pause_pushButton_clicked()
{
    if ( paused_ == false )
    {
        // Pausing the game
        paused_ = true;
        seconds_timer_->stop();
        move_timer_->stop();
        ui_->info_textBrowser->setText("The game is currently paused. Continue "
                                       "it by pressing the Pause-button once "
                                       "again.");

        // Disabling the arrow-buttons
        modify_buttons(true);
    }
    else
    {
        // Resuming the game
        paused_ = false;
        seconds_timer_->start(1000);
        move_timer_->start(snake_speed_);
        ui_->info_textBrowser->clear();

        // Enabling the arrow-buttons
        modify_buttons(false);
    }

    // Putting the snake speed back to normal
    snake_speed_ = NORMAL_SPEED;
}

void MainWindow::modify_buttons(const bool &enabled)
{
    // Disabling/enabling following pushButtons based on the parameter value.
    ui_->up_pushButton->setDisabled(enabled);
    ui_->right_pushButton->setDisabled(enabled);
    ui_->down_pushButton->setDisabled(enabled);
    ui_->left_pushButton->setDisabled(enabled);

    if ( not paused_ )
    {
        ui_->pause_pushButton->setDisabled(enabled);
    }
}

void MainWindow::setup_timers()
{
    // Setting up the seconds-timer used in the program.
    ui_->time_lcdNumber->display(time_);
    seconds_timer_ = new QTimer(this);
    // Connecting the timer to a slot dealing with it every time it ticks.
    connect(seconds_timer_, SIGNAL(timeout()), this, SLOT(seconds_tick()));

    // Doing the same to the move-timer used in the program.
    ui_->length_lcdNumber->display(snake_length_);
    move_timer_ = new QTimer(this);
    connect(move_timer_, SIGNAL(timeout()), this, SLOT(move_tick()));
}

void MainWindow::setup_graphics()
{
    // Setting up the graphics used on the game screen
    scene_->setSceneRect(0, 0, SIZE*ui_->width_spinBox->value(),
                         SIZE*ui_->height_spinBox->value());

    ui_->graphicsView->setFixedSize(SIZE * ui_->width_spinBox->value(), SIZE *
                                    ui_->height_spinBox->value());

    ui_->graphicsView->setScene(scene_);

    ui_->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui_->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    // Creating the snake
    print_snake();

    // Creating the food
    place_new_food();
}

void MainWindow::make_grid() const
{
    // Going trough a loop with the range of the width spinBox value
    for ( int loop_width = 0; loop_width < ui_->width_spinBox->value();
          loop_width++)
    {
        // Printing a line vertically
        scene_->addLine(loop_width * SIZE, 0, loop_width * SIZE,
                        ui_->height_spinBox->value() * SIZE, QPen(Qt::black));
    }
    // Going trough a loop with the range of the height spinBox value
    for ( int loop_height = 0; loop_height < ui_->height_spinBox->value();
          loop_height++)
    {
        // Printing a line horizontally
        scene_->addLine(0, loop_height * SIZE,
                        ui_->width_spinBox->value() * SIZE, loop_height * SIZE,
                        QPen(Qt::black));
    }
}

void MainWindow::print_snake()
{
    // Deleting all the previous items displaying the snake and the food except
    // for the snakes head from the ui (if the game has already started)
    if ( has_started_ )
    {
        for ( auto & item : ui_->graphicsView->items() )
            if ( item != food_)
            {
                scene_->removeItem(item);
                delete item;
            }
    }

    // Printing the grid
    make_grid();

    // Getting new snake coordinates from the snake's Point-deque.
    std::deque<Point> snake_coordinates;
    snake_coordinates = field_->return_snake();

    // Initializing the colors used to draw the snake and its different parts.
    QPen blackPen(Qt::black);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush blueBrush(Qt::blue);
    blackPen.setWidth(2);

    // Initializing the variables used in the loop
    int snake_point_x = 0;
    int snake_point_y = 0;

    // Creating all the new snake locations to the screen
    for ( auto& snake_point : snake_coordinates )
    {
        snake_point_x = snake_point.return_x();
        snake_point_y = snake_point.return_y();

        // Checking if the current loop-Point is the snakes head.
        if ( snake_point == snake_coordinates.back() )
        {
            // Creating the head.
            square_ = scene_->addRect(0, 0, STEP, STEP, blackPen,
                                      yellowBrush);
            square_->setPos(snake_point_x * SIZE, snake_point_y * SIZE);
        }
        // Checking if the current loop-Point is the snakes tail.
        else if ( snake_point == snake_coordinates.front() )
        {
            // Creating the tail.
            square_ = scene_->addRect(0, 0, STEP, STEP, blackPen, blueBrush);
            square_->setPos(snake_point_x * SIZE, snake_point_y * SIZE);
        }
        // Otherwise we are dealing with the snake's middle body.
        else
        {
            // Printing the middle body
            square_ = scene_->addRect(0, 0, STEP, STEP, blackPen, redBrush);
            square_->setPos(snake_point_x * SIZE, snake_point_y * SIZE);
        }
    }
}

void MainWindow::place_new_food()
{
    int new_food_x = 0;
    int new_food_y = 0;

    // Getting the new food x- and y_coords
    new_food_x = field_->get_food_x();
    new_food_y = field_->get_food_y();

    // Removing the previous food from the screen (if game has started)
    if ( has_started_ )
    {
        scene_->removeItem(food_);
        delete food_;
    }

    QString random_filename = "";

    // Getting a random food's filename
    random_filename = get_random_food_filename();

    // Creating a QPixmap image
    QPixmap image = (random_filename);
    image = image.scaled(FOOD_SIZE, FOOD_SIZE, Qt::KeepAspectRatio);

    // Adding the created image to it's designated spot on the screen
    food_ = scene_->addPixmap(image);
    food_->setPos(new_food_x * SIZE, new_food_y*SIZE);
}

void MainWindow::clear_screen() const
{
    // Going trough all gui-items in the graphicsView window and deleting them
    for ( auto& gui_item : ui_->graphicsView->items() )
    {
        delete gui_item;
    }
}

void MainWindow::modify_spinboxes(const bool &hidden)
{
    if ( hidden )
    {
        // Hiding all the spinboxes
        ui_->width_label->hide();
        ui_->width_spinBox->hide();
        ui_->height_label->hide();
        ui_->height_spinBox->hide();
        ui_->seed_label->hide();
        ui_->seed_spinBox->hide();
        ui_->set_pushButton->hide();
    }
    else
    {
        // Showing all the spinboxes
        ui_->width_label->show();
        ui_->width_spinBox->show();
        ui_->height_label->show();
        ui_->height_spinBox->show();
        ui_->seed_label->show();
        ui_->seed_spinBox->show();
        ui_->set_pushButton->show();
    }
}

void MainWindow::check_hit(const int &food_x, const int &food_y)
{
    print_snake();

    // Checking if the game has not been lost.
    if ( not field_->gameLost() )
    {
        int snake_head_x, snake_head_y = 0;
        snake_head_x = field_->get_snake_head_x();
        snake_head_y = field_->get_snake_head_y();

        // Game has not been lost, checking if the snake's head location is in
        // the same place as the food.
        if ( snake_head_x == food_x and snake_head_y == food_y )
        {
            // Snake eats the food, increasing the score.
            increase_score();

            // Increasing the length lcdNumber value with 1
            int prev_length = ui_->length_lcdNumber->value();
            ui_->length_lcdNumber->display(prev_length + 1);

            // Checking if the game is over (i.e no possible moves left )
            if ( field_->gameWon() )
            {
                // Player won the game
                game_over("You won the game, congratulations!");
                ui_->pause_pushButton->setDisabled(true);
                return;
            }

            // Player did not win yet, placing new food on the board
            place_new_food();
        }
    }
    else
    {
        // Game has been lost
        game_over("");
        // Determining the death cause of the snake
        determine_death_cause();
    }
}

void MainWindow::increase_score()
{
    int prev_score = ui_->score_lcdNumber->value();

    /* Defining the points earned by a simple formula: If time since the last
     * food has been eaten are below 3, the player gets 5 points. If time since
     * the last food eaten are over or equal to 3 and under or equal to 5, the
     * player gets 3 points. */

    if (time_since_last_food_ < 3 )
    {
        prev_score += 5;
    }
    else if (time_since_last_food_ >= 3 and time_since_last_food_ <= 5)
    {
        prev_score += 3;
    }
    else
    {
        prev_score += 1;
    }

    ui_->score_lcdNumber->display(prev_score);

    // Reassigning time since the last food eaten to 0.
    time_since_last_food_ = 0;

    // Eating food also increases the snakes speed
    snake_speed_ -= 15;
}

void MainWindow::game_over(const QString &text)
{
    // Displaying the parameter given text.
    ui_->info_textBrowser->setText(text);

    // Stopping the timers
    seconds_timer_->stop();
    move_timer_->stop();

    // Changing the background color
    change_background_color();
}

void MainWindow::determine_death_cause() const
{
    if ( field_->collision_with_self(current_direction_) )
    {
        // The snake died, because it collided with itself. Displaying a text.
        ui_->info_textBrowser->setText("Game over, you lost ! Cause of death: "
                                       "The snake ate itself :(");
    }
    else
    {
        ui_->info_textBrowser->setText("Game over, you lost ! Cause of death: "
                                       "The snake crashed to a wall :(");
    }
}

void MainWindow::change_background_color()
{
    // Checking if the game has been reseted
    if ( reseted_ )
    {
        this->setStyleSheet("background-color: rgb(255, 151, 255);");
    }
    // Checking if the game has been lost
    else if ( field_->gameLost() )
    {
        this->setStyleSheet("background-color: rgb(79, 13, 33);");
    }
    // The game has been won
    else
    {
        this->setStyleSheet("background-color: rgb(102, 255, 102);");
    }
}

QString MainWindow::get_random_food_filename() const
{
    // Getting a random number between 0-3
    int random_number = (rand() % 4);

    // Getting the random number responding foods filename and returning it.
    QString filename = "";
    filename = FOOD_FILENAMES.at(random_number);

    return filename;
}

void MainWindow::check_move(const std::string &forbidden, const
                            std::string &allowed)
{
    // The snake can be moved to the designated direction if, the direction
    // is not the parameter given forbidden direction or if snake length is 1
    if ( current_direction_ != forbidden or snake_length_ == 1 )
    {
        current_direction_ = allowed;
    }
}
