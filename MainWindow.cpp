/*
 * CMPE 230 - Assignment 3
 * Match Pairs Game
 * Author: Can Atakan Ugur - 2017400057
 *
 */

/*
 * This is the class that all process about main window are made. MyGrid,
 * Point, and MyTimer objects are created here as well. The main method is
 * located under this class.
 *
 * Main window is prepared after all these steps, and then shown at the
 * end of the main method, here under this class.
 *
 */


#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QMainWindow>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QSize>
#include "mytimer.h"
#include "mygrid.h"
#include "wordbutton.h"
#include "point.h"

// main method
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow *mw = new QMainWindow;
    QWidget *cw = new QWidget;

    QVBoxLayout *vb = new QVBoxLayout(cw);


    MyTimer *mt = new MyTimer(); // timer object to count time
    Point *p = new Point(); // point object for points during the game

    // MyGrid object to host WordButtons also those are initialized in MyGrid class
    MyGrid *lay = new MyGrid(mt, p);

    // Horizontal box for "New Game" and "Quit Game" buttons and Time, and Point
    QHBoxLayout *hb = new QHBoxLayout;

    const QSize size = QSize(200,50); // fix a size for the widgets in the horizontal box


    p->label->setFixedSize(size);
    hb->addWidget(p->label);


    mt->label->setFixedSize(size);
    hb->addWidget(mt->label);


    QPushButton *ng = new QPushButton("New Game"); // new game button
    QObject::connect(ng, SIGNAL(clicked()), lay, SLOT(new_game()));
    ng->setFixedSize(size);

    QPushButton *qg = new QPushButton("Quit Game"); // quit game button
    QObject::connect(qg, SIGNAL(clicked()), mw, SLOT(close()));
    qg->setFixedSize(size);

    hb->addWidget(ng);
    hb->addWidget(qg);
    vb->addLayout(hb);
    vb->addLayout(lay);

    mw->setCentralWidget(cw);
    mw->setWindowTitle("Memory Game");
    mw->show();

    return app.exec();
}
