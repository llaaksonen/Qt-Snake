/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2022                                    #
# GUI-Project: snake_gui                                                    #
# File: mainwindow.hh                                                       #
# Description: A class file, which contains information about all the       #
#              variables, slots and methods used in the program to create   #
#              a GUI-version of a classic game called snake. This class     #
#              is based on 2 different classes: GameBoard and Point.        #
#                                                                           #
# Program author:                                                           #
#              * Name: Lauri Laaksonen                                      #
#############################################################################
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>

// A vector of strings which consist from the foods' filenames
const std::vector<QString> FOOD_FILENAMES = {
    "snake_food_a.png",
    "snake_food_b.png",
    "snake_food_c.png",
    "snake_food_d.png"
};

const int NORMAL_SPEED = 1500;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Obvious slots
    void on_set_pushButton_clicked();
    void on_play_pushButton_clicked();
    void on_up_pushButton_clicked();
    void on_right_pushButton_clicked();
    void on_down_pushButton_clicked();
    void on_left_pushButton_clicked();
    void seconds_tick();
    void move_tick();
    void on_reset_pushButton_clicked();
    void on_pause_pushButton_clicked();

private:
    /**
     * @brief ui_
     * A pointer to the user interface.
     */
    Ui::MainWindow *ui_ = nullptr;

    /**
     * @brief modify_buttons
     * A function that makes pushButtons enabled/disabled.
     * @param enabled
     * bool parameter, determines if buttons become enabled or disabled.
     */
    void modify_buttons(const bool &enabled);

    /**
     * @brief setup_timers
     * A function, which setups the timers on the screen.
     */
    void setup_timers();

    /**
     * @brief seconds_timer_
     * A pointer to the timer, which calculates the seconds played.
     */
    QTimer* seconds_timer_ = nullptr;

    /**
     * @brief time_
     * A variable, which indicates the time (seconds) spent.
     */
    int time_ = 0;

    /**
     * @brief move_timer_
     * A pointer to the timer, which calculates the time between automatic
     * moving of the snake.
     */
    QTimer* move_timer_ = nullptr;

    /**
     * @brief field_
     * A shared-pointer to the GameBoard class where the GUI is based on.
     * Shared-pointer will be used, because the normal pointer resulted in some
     * troublesome memory errors for this spesific variable and could not be
     * fixed without changing some const variables from the base codes.
     */
    std::shared_ptr<GameBoard> field_ = nullptr;

    /**
     * @brief setup_graphics
     * A function, which setups the used graphics on the screen.
     */
    void setup_graphics();

    /**
     * @brief make_grid
     * A function, which prints a grid to the gamescreen.
     */
    void make_grid() const;

    /**
     * @brief scene_
     * A Graphic Scene, where all the graphic items will be assigned to.
     */
    QGraphicsScene* scene_ = nullptr;

    /**
     * @brief square_
     * A pointer to the square QGraphicsItem (snake's body).
     */
    QGraphicsItem* square_ = nullptr;

    /**
     * @brief food_
     * A pointer to the ellipse QGraphicsEllipseItem (snake's food).
     */
    QGraphicsPixmapItem* food_ = nullptr;

    /**
     * @brief print_snake
     * A function that prints all the snakes occupied locations when the
     * move_timer_ ticks.
     */
    void print_snake();

    /**
     * @brief place_new_food
     * A function that places the food to a new random place on the gameboard.
     */
    void place_new_food();

    /**
     * @brief clear_screen
     * A function, which clears the screen from all the elements.
     */
    void clear_screen() const;

    /**
     * @brief modify_spinboxes
     * A function, which makes the spinboxes hidden/shown.
     * @param hidden
     * bool parameter, determines if buttons become hidden/shown.
     */
    void modify_spinboxes(const bool &hidden);

    /**
     * @brief check_hit
     * A function that checks if the snakes head is in the same spot as food.
     * @param food_x
     * Foods x location on the gameboard.
     * @param food_y
     * Foods y location on the gameboard.
     */
    void check_hit(const int &food_x, const int &food_y);

    /**
     * @brief increase_score
     * A function, which increases the current score.
     */
    void increase_score();

    /**
     * @brief game_over
     * A function, which changes the ui based on win/loss of the game.
     * @param text
     * QString parameter text given to the function, when calling it. This will
     * be displayed on the screen and it is based on win/loss.
     */
    void game_over(const QString &text);

    /**
     * @brief determine_death_cause
     * A function, which determines the snakes death cause (i.e did it hit the
     * wall or its own body).
     */
    void determine_death_cause() const;

    /**
     * @brief current_direction_
     * A variable, which indicates the last selected direction, where the snake
     * is going. In the start it is designated left, but will change over the
     * course of the game.
     */
    std::string current_direction_ = "d";

    /**
     * @brief SIZE
     * A constant variable, which indicates the size of one square in the game.
     */
    const int SIZE = 75; // square side size...

    /**
     * @brief STEP
     * A constant variable, which indicates the size of one step in the game.
     */
    const int STEP = 75;

    /**
     * @brief snake_length_
     * A variable, which is used to display the snakes total length. Will always
     * start as 1.
     */
    int snake_length_ = 1;

    /**
     * @brief paused_
     * A variable, which indicates if the game is currently paused or not.
     */
    bool paused_ = false;

    /**
     * @brief change_background_color
     * A function, which is used to change the background color over the course
     * of the game.
     */
    void change_background_color();

    /**
     * @brief reseted_
     * A variable, which indicates if the game has been reseted or not.
     */
    bool reseted_ = false;

    /**
     * @brief time_since_last_food_
     * A variable, which is used in the point-calculation. Indicates time since
     * spent after eating the latest food.
     */
    int time_since_last_food_ = 0;

    /**
     * @brief has_started_
     * A variable, which indicates if the game has started.
     */
    bool has_started_= false;

    /**
     * @brief FOOD_SIZE
     * A variable, which indicates the food's maximum size when creating it.
     */
    const int FOOD_SIZE = 75;

    /**
     * @brief get_random_food_filename
     * A function, which gets a random filename from the food filename vector
     * @return
     * A random filename, used to print a random food image
     */
    QString get_random_food_filename() const;

    /**
     * @brief snake_speed_
     * A variable to the snake's move speed. Will increase over the course of
     * the game.
     */
    int snake_speed_ = 1500;

    /**
     * @brief check_move
     * Checks if the given move direction is possible. If possible, assigns the
     * new direction, where the snake starts going.
     * @param forbidden
     * std::string forbidden direction symbol
     * @param allowed
     * std::string allowed direction symbol
     */
    void check_move(const std::string &forbidden, const std::string &allowed);
};
#endif // MAINWINDOW_HH
