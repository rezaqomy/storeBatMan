#include "animation.h"
#include "mainwindow.h"



Animation::Animation()
{

}


void Animation::moveFromRightToLeft(QPushButton *button, int movement){
    QPropertyAnimation *animation = new QPropertyAnimation(button, "pos");
    animation->setDuration(1000);
    animation->setStartValue(button->pos() + QPoint(movement,0));

    animation->setEndValue(button->pos());
    animation->start();


}

void Animation::moveFromTopToBottom(QPushButton *button, int movement)
{
    QPropertyAnimation *animation = new QPropertyAnimation(button, "pos");
    animation->setDuration(1000);
    animation->setStartValue(button->pos());
    animation->setEndValue(button->pos() + QPoint(0, movement));

    animation->start();

}

void Animation::moveFromTopToBottom(QWidget *widget, int movement)
{
    QPropertyAnimation *animation = new QPropertyAnimation(widget, "pos");
    animation->setDuration(1000);
    animation->setStartValue(widget->pos());
    animation->setEndValue(widget->pos() + QPoint(0, movement));

    animation->start();

}
