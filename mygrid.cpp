/*
 * After each click of the user, necessary checks are made, initialization
 * of the WordButton objects are made, new game is started, and time is
 * counted in this class.
 *
 * Holds a Point object to print it in the pop up when the game ends to show
 * the user the points that he/she collected, and a MyTimer object to be able
 * to know the time during the game and stop it when the game ends and reset
 * it when a new game request comes.
 */

#include "mygrid.h"
#include "wordbutton.h"
#include <QTime>
#include <QCoreApplication>
#include <QMessageBox>
#include "mytimer.h"

// MyTimer and Point objects are assigned to the variables here and necessary connection is made.
MyGrid::MyGrid(MyTimer *timer, Point *p) : QGridLayout(){
    this->my_timer = timer;

    // change the count after each second
    connect(my_timer->timer, SIGNAL(timeout()),
            this, SLOT(count_time()));

    this->p = p;
    initialize(); // create WordButton objects to store in the grid
}


// checks the board after each click of the user on the
// buttons and takes action accordingly
void MyGrid::check(){

    int open_card_count = 0; // count the open cards
    QWidgetList *open_widgets = new QWidgetList; // store open cards here


    for (int i = 0; i < this->count(); i++) // scan all cards
    {
        WordButton *widget = qobject_cast<WordButton*>
                (this->itemAt(i)->widget());


        if(widget->is_open != 0){ // if card is open,
            open_card_count++; // increase the number of open cards
            open_widgets->append(widget); // and add the card to the
                                            // list of open cards
        }

    }

    if(open_card_count == 2){ // if two cards are open, then an action is needed

        WordButton *word1 = qobject_cast<WordButton*>(open_widgets->at(0));
        WordButton *word2 = qobject_cast<WordButton*>(open_widgets->at(1));


        if(QString::compare(word1->text, word2->text) == 0){ // the cards have the same word

            // disable other cards except the open ones
            for (int i = 0; i < this->count(); i++)
            {
                WordButton *widget = qobject_cast<WordButton*>
                        (this->itemAt(i)->widget());

                if(QString::compare(word1->text, widget->text) != 0)
                    widget->setDisabled(true);

            }

            // wait a second
            QTime waitTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < waitTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            // set disability of other cards false again
            for (int i = 0; i < this->count(); i++)
            {
                WordButton *widget = qobject_cast<WordButton*>
                        (this->itemAt(i)->widget());

                if(QString::compare(word1->text, widget->text) != 0)
                    widget->setDisabled(false);

            }

            // change the fields of the cards accordingly
            word1->is_open = false;
            word1->is_matched = true;
            word1->close();
            word2->is_open = false;
            word2->is_matched = true;
            word2->close();

            // give 50 points for the match
            p->value += 50;
            p->label->setText("Point: " + QString::number(p->value));

            // check whether the game is finished or not after each match
            bool is_finished = false;
            for (int i = 0; i < this->count(); i++)
            {
                WordButton *widget = qobject_cast<WordButton*>
                        (this->itemAt(i)->widget());

                if(widget->is_matched == 0){
                    is_finished = false;
                    break;
                }

                is_finished = true;
            }


            if(is_finished != 0){ // the game is completed before time's up

                this->my_timer->timer->stop(); // stop the timer

                QMessageBox *box = new QMessageBox;
                box->setWindowTitle("Congratulations!");
                box->setText("You won! Do you want to play again?");

                QAbstractButton* play_again = box->addButton(tr("Play again!"), QMessageBox::YesRole);
                QAbstractButton* cancel = box->addButton(tr("No, thanks"), QMessageBox::NoRole);

                box->exec();

                if (box->clickedButton()== play_again) { // if the user wants to play again
                    new_game(); // start a new game
                } else if(box->clickedButton() == cancel){
                    my_timer->reset();
                    my_timer->timer->stop();
                }

            }


        } else { //no match

            // disable other cards except the open ones
            for (int i = 0; i < this->count(); i++)
            {
                WordButton *widget = qobject_cast<WordButton*>
                        (this->itemAt(i)->widget());

                if(widget != word1 && widget != word2)
                    widget->setDisabled(true);

            }

            // wait a second
            QTime waitTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < waitTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);


            // set disability of other cards false again
            for (int i = 0; i < this->count(); i++)
            {
                WordButton *widget = qobject_cast<WordButton*>
                        (this->itemAt(i)->widget());

                if(widget != word1 && widget != word2)
                    widget->setDisabled(false);

            }

            // close the cards again because it's not a match
            word1->setText("?");
            word1->is_open = false;
            word2->setText("?");
            word2->is_open = false;
        }
    }
}

// a private method to create WordButton objects randomly
void MyGrid::initialize(){

    // the list of pairs of words to be written under the cards
    QStringList words = {"bitcoin", "bitcoin", "ethereum", "ethereum", "ripple", "ripple",
                         "stellar", "stellar", "moon", "moon", "dump", "dump", "pump",
                         "pump", "tether", "tether", "verge","verge", "doge", "doge", "link",
                         "link", "mining", "mining", "cosmos", "cosmos", "theta",
                         "theta", "crypto", "crypto"};

    int maximum_index = 30; // amount of words left to be picked in other words

    // 5 x 6 table full of WordButton objects
    for(int row=0; row<5; row++){
        for(int col=0; col<6; col++){

            // generate a random number and pick the word at that index
            int random = QRandomGenerator::global()->bounded(maximum_index);
            QString word = words[random];

            // create the button with ? written "upside" and the actual word downside
            WordButton *wb = new WordButton("?", word);

            words.removeAt(random); // remove the word form the list
            maximum_index--; // decrease the amount of words left

            // set a sizePolicy so that cards won't change their place after a match
            QSizePolicy sp_retain = wb->sizePolicy();
            sp_retain.setRetainSizeWhenHidden(true);
            wb->setSizePolicy(sp_retain);

            // when a card is clicked, open it, and check every card to decide whether
            // the game ended or there is a match or not
            QObject::connect(wb, SIGNAL(clicked()), wb, SLOT(open()));
            QObject::connect(wb, SIGNAL(clicked()), this, SLOT(check()));

            // add the card
            this->addWidget(wb, row, col, 1, 1);

        }
    }
}

// starts a new game whenever the user wants to play again or start
// the current game from the beginning
void MyGrid::new_game(){

    this->my_timer->reset(); // reset the timer

    // wait a second
    QTime waitTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < waitTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    // set the point collected to zero
    this->p->value = 0;
    this->p->label->setText("Point: " + QString::number(this->p->value));

    // close old hidden widgets from the previous game
    for (int i = 0; i < this->count(); i++)
    {
        WordButton *widget = qobject_cast<WordButton*>
                (this->itemAt(i)->widget());

        widget->close();
    }

    // create WordButton objects again randomly to start new game
    initialize();
}

/*
 * Checks if the player still has time or the time is up and shows
 * a window asking the player whether he/she wants to play again
 * and shows the point earned during the game. Invokes new_game() if
 * the user wants retry after his/her time is up before he/she was
 * able to complete the game.
 */
void MyGrid::count_time(){

    my_timer->counter += 1;
    my_timer->label->setText("Time (secs): "+
                             QString::number(my_timer->counter));

    if(my_timer->counter>=120){ // time is up (the time is set to 120 by default, can be changed)
        my_timer->timer->stop(); // stop the timer

        // disable all cards
        for (int i = 0; i < this->count(); i++)
        {
            WordButton *widget = qobject_cast<WordButton*>
                    (this->itemAt(i)->widget());

            widget->setDisabled(true);
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Time's up!");

        // show the amount of points the player collected
        msgBox.setText("You collected " + QString::number(p->value)
                       + " points. You can try again to get more points.");

        QAbstractButton* retry = msgBox.addButton(tr("Retry"), QMessageBox::YesRole);
        QAbstractButton* cancel = msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()== retry) {
            new_game(); // start a new game if the player wants to try again
        } else if(msgBox.clickedButton() == cancel){
            my_timer->reset();
            my_timer->timer->stop();
        }
    }
}



