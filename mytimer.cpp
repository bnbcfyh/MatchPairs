/*
 * This class is used in order to follow the time passed during the
 * game and show it in a proper format on the main window. Also, it is
 * reasonable to note that MyGrid class' constructor also takes a MyTimer
 * object pointer as parameter to be able to stop when the game ends or
 * reset the time when a new game starts.
 */

#include "mytimer.h"
#include <QTime>
#include <QCoreApplication>

/*
 * Default constructor initializes the MyTimer object by setting the
 * counter to zero, preparing the label to show in the main window, and
 * starting the timer to count.
 */
MyTimer::MyTimer()
{
    timer = new QTimer(this);
    label = new QLabel("Time (secs): 0");
    counter = 0;
    timer->start(1000);
}

/*
 * Used for setting the count to zero and starting the counter that
 * has been stopped for a while again.
 *
 * "counter" is set to -1 in the method in order to create a one second
 * delay and show the user "Time (secs): 0" as text, meaning like a
 * wait just before starting the new game.
 */
void MyTimer::reset(){
    counter = -1;
    timer->start(1000);
}

