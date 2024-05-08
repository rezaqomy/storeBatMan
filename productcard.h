#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H
#include "product.h"
#include "order.h"
#include "addprudoctviewer.h"
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>

class ProductCard: public QWidget
{
public:
    ProductCard(ProductInformation product,Product* productRepo , OrderInformation* order);
private slots:
    void onChangedSpinBox( int newValue);
    void productEdited(ProductInformation*);

private:
    OrderInformation* order;
    ProductInformation product;
    Product* productRepo;
    QLabel* product_id = new QLabel;
    QLabel* product_name = new QLabel;
    QLabel* product_quantity = new QLabel;
    QLabel* product_price = new QLabel;
    QLabel* all_price = new QLabel;
    QPushButton* edit_product = new QPushButton;
    QSpinBox* orderQuantitySpinBox = new QSpinBox;
    void on_edit_clidked();
    void updateTheScreen();



Q_SIGNALS:
    ProductInformation product_Edited(ProductInformation* productinfo);
};

#endif // PRODUCTCARD_H
