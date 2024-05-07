#ifndef ANIMATION_H
#define ANIMATION_H

#include <QPropertyAnimation>
#include <QPushButton>


class Animation
{
public:
    Animation();
    static void moveFromRightToLeft(QPushButton* button, int movement = 50);
    static void moveFromTopToBottom(QPushButton* button, int movement = 50);
    static void moveFromTopToBottom(QWidget* button, int movement = 50);
};

#endif // ANIMATION_H
