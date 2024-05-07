#ifndef ORDERCARD_H
#define ORDERCARD_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "order.h"
#include "customer.h"
#include "product.h"
#include "showordermoreinformation.h"

class OrderCard: public QWidget
{
public:
    OrderCard(OrderInformation* order);
private:
    OrderInformation order;
    QHBoxLayout* qHBoxLayout = new QHBoxLayout();
    QLabel* id = new QLabel;
    QLabel* priceLabel = new QLabel;
    QLabel* dateLabel = new QLabel;
    QLabel* customerName = new QLabel;
    QPushButton* moreInforamtionPushButton = new QPushButton();

private slots:
    void on_moreInformationclicked();
};

#endif // ORDERCARD_H
