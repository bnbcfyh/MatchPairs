/*
 * The class to create the "game cards" as push buttons that have the words
 * as "text" in their fields. Necassary connections to add the actions when
 * those are clicked are made under the MyGrid class.
 */
#include "wordbutton.h"

// The cards are initialized with a question mark that is sent with the "initialize" parameter
WordButton::WordButton(QString initialize ,const QString& text, QWidget* parent)
    : QPushButton(initialize, parent)
{
    this->text = text;
    this->is_open = false;
    this->is_matched = false;
    setFlat(true);
    setAutoFillBackground(true);
    update();
}

// when user opens a card, shows the text to the user, sets is_open to true
void WordButton::open(){
    this->setText(text);
    this->is_open = true;
    update();
}
