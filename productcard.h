#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H
#include "product.h"
#include "order.h"
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>

class ProductCard: public QWidget
{
public:
    ProductCard(ProductInformation product, OrderInformation* order);
private slots:
    void onChangedSpinBox( int newValue);

private:
    OrderInformation* order;
    ProductInformation product;
    QLabel* product_id = new QLabel;
    QLabel* product_name = new QLabel;
    QLabel* product_quantity = new QLabel;
    QLabel* product_price = new QLabel;
    QLabel* all_price = new QLabel;
    QSpinBox* orderQuantitySpinBox = new QSpinBox;


    void updateTheScreen();
};

#endif // PRODUCTCARD_H
