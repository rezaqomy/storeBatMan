#include "showordermoreinformation.h"
#include "ui_showordermoreinformation.h"

ShowOrderMoreInformation::ShowOrderMoreInformation(OrderInformation* order ,QWidget *parent) :
    order(order) ,QWidget(parent),
    ui(new Ui::ShowOrderMoreInformation)
{
    ui->setupUi(this);
    updateInformation();
}

ShowOrderMoreInformation::~ShowOrderMoreInformation()
{
    delete ui;
}

void ShowOrderMoreInformation::updateInformation()
{
    int price{};
    QGridLayout* gridLayout = new QGridLayout();
    for (int i{}; i < order->products.size(); i++) {
        QHBoxLayout* hlayout = new QHBoxLayout();
        price += order->quantity[i] * order->prices[i];

        QLabel* productid = new QLabel("id : " + QString::number(order->products[i].id));
        QLabel* productName = new QLabel("product name: "+ order->products[i].productName);
        QLabel* quantity = new QLabel("quantity : " + QString::number(order->quantity[i]));
        QLabel* price = new QLabel("price" + QString::number(order->prices[i]));


        hlayout->addWidget(productid);
        hlayout->addWidget(productName);
        hlayout->addWidget(quantity);
        hlayout->addWidget(price);

        QWidget* widget = new QWidget;
        widget->setLayout(hlayout);

        gridLayout->addWidget(widget);
    }
    QWidget* window = new QWidget();
    window->setLayout(gridLayout);
    ui->products_scrollArea->setWidget(window);

    ui->CustomerID_label->setText(QString::number(order->customer.id));
    ui->firstName_label->setText(order->customer.firs_name);
    ui->lastName_label->setText(order->customer.Last_name);
    ui->phoneNUmber_label->setText(order->customer.phone_number);


    ui->orderID_label->setText(QString::number(order->id_order));
    qDebug() << "set label" ;
    ui->date_label->setText(order->order_date);
    ui->price_label->setText(QString::number(price));
    ui->discount_label->setText(QString::number(order->discount));
    ui->finalPrice_label->setText(QString::number(price - order->discount));
}
