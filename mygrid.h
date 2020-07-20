#ifndef MYGRID_H
#define MYGRID_H
#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTimer>
#include <QStringList>
#include "point.h"
#include "mytimer.h"

class MyGrid : public QGridLayout
{
    Q_OBJECT

public:
    MyGrid(MyTimer* my_timer, Point *p);
    MyTimer* my_timer; // holds the MyTimer object in the field to
                        // reset, start, etc. when necessary
    Point *p;

public slots:
    void check(); // checks the game board after each click
    void new_game(); // starts a new game by creating new WordButtons
    void count_time(); // keeps track of time during the game

private:
    void initialize(); // creates the WordButtons randomly
};


#endif // MYGRID_H







