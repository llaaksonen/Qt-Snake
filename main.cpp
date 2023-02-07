/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2022                                    #
# GUI-Project: snake_gui                                                    #
# File: main.cpp                                                            #
# Description: This file executes the game window for the user to see.      #
#                                                                           #
# Program author:                                                           #
#              * Name: Lauri Laaksonen                                      #
#############################################################################
*/

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
