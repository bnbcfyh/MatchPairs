/*
 * Point class is used in order to hold the value of the
 * points gained and prepare a label for it to show in
 * the main window.
 */

#include "point.h"

// default constructor constructs a point object with 0 value
Point::Point()
{
    this->value = 0;
    QString str = "Point: " + QString::number(value);
    this->label = new QLabel(str);
}
