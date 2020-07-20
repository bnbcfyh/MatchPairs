#ifndef MYTIMER_H
#define MYTIMER_H
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

class MyTimer : public QObject
{
    Q_OBJECT

public:
    MyTimer();
    QTimer *timer; // QTimer object for counting time
    QLabel *label; // Time (secs): "counter"
    int counter; // Number of seconds past

public slots:
    void reset(); // sets the counter to zero
                   //and starts the timer again
};

#endif // MYTIMER_H







