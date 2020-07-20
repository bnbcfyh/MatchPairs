#ifndef WORDBUTTON_H
#define WORDBUTTON_H
#include <QPushButton>


class WordButton : public QPushButton
{
    Q_OBJECT

public:

    /*
     * Creates the button objects with their texts that are simply written "under
     * the card", keeps it in the "text" field but initializes the objects with
     * just a question mark thanks to "initialize" parameter.
     */
    WordButton(const QString initialize, const QString& text, QWidget* parent = 0);

    QString text; // the words that are written under the cards
    bool is_open; // true if this card is open right now
    bool is_matched; // true if this card has been matched with its pair before

public slots:
    void open(); // simulates opening a card
};


#endif // WORDBUTTON_H





