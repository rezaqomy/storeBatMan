#include "ordercard.h"

OrderCard::OrderCard(OrderInformation *order)
{
    id->setText("order id: " + QString::number(order->id_order));
    id->setStyleSheet("background-color: rgb(120, 140, 102);");
    int price {};
    for (int i{}; i < order->products.size(); i++) {
        price += order->prices[i] * order->quantity[i];
    }
    priceLabel->setText("price: " + QString::number(price) + " - " + QString::number(order->discount) + " = " + QString::number(price - order->discount));
    priceLabel->setStyleSheet("background-color: rgb(220, 2, 214);");
    dateLabel->setText("date: " + order->order_date);
    dateLabel->setStyleSheet("background-color: rgb(220, 214, 2);");
    customerName->setText("customer name : " + order->customer.firs_name + "    " + order->customer.Last_name);
    customerName->setStyleSheet("background-color: rgb(20, 214, 220);");
    moreInforamtionPushButton->setText("...");
    moreInforamtionPushButton->setMaximumWidth(50);


    qHBoxLayout->addWidget(id);
    qHBoxLayout->addWidget(priceLabel);
    qHBoxLayout->addWidget(dateLabel);
    qHBoxLayout->addWidget(customerName);
    qHBoxLayout->addWidget(moreInforamtionPushButton);


    //setStyleSheet("background-color: rgb(220, 214, 247);");
    setMinimumHeight(50);
    setMaximumHeight(50);
    setLayout(qHBoxLayout);

}
