#include "productcard.h"

ProductCard::ProductCard(ProductInformation product, OrderInformation* order): product(product), order(order)
{
    int index = Order::findProductIndex(order, product.id);
    product_name = new QLabel("product name : " + product.productName);
    product_id->setText("id : " + QString::number(product.id));
    product_quantity->setText("quantity : " + QString::number(product.quantity));
    product_price->setText("price : " + QString::number(product.price));
    orderQuantitySpinBox->setMaximum(product.quantity);
    all_price->setText(QString::number(product.price * orderQuantitySpinBox->value()));
    connect(orderQuantitySpinBox,  static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ProductCard::onChangedSpinBox);
    if (index != -1){
        orderQuantitySpinBox->setValue(order->quantity[index]);
    }

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(product_name, 0, 0, 1, 4);
    layout->addWidget(product_id, 1, 0, 1, 2);
    layout->addWidget(product_quantity, 1, 2, 1, 2);
    layout->addWidget(product_price, 2, 0, 1, 4);
    layout->addWidget(all_price, 3, 0, 1, 2);
    layout->addWidget(orderQuantitySpinBox, 3, 2, 1, 2);

    setStyleSheet("background-color: rgb(220, 214, 247); border-radius:20px;");
    setMaximumHeight(250);
    setMaximumWidth(300);
    setLayout(layout);
}

void ProductCard::onChangedSpinBox(int newValue)
{
    int index = Order::findProductIndex(order, product.id);
    if(newValue == 0){
        if (order->products[index].id == product.id) {
            order->products.erase(order->products.begin() + index);
            order->quantity.erase(order->quantity.begin() + index);
        }
    } else {
        if (index == -1) {
            order->products.push_back(product);

            qDebug() << "ok" << index << newValue;
            order->quantity.push_back(newValue);

        } else {
            order->quantity[index] = newValue;
        }
    }
    all_price->setText(QString::number(product.price * newValue));

}
