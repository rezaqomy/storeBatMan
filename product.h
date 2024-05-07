#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QSqlQuery>
#include "database.h"

struct ProductInformation {
    int id;
    QString productName;
    int price;
    int discount;
    int quantity;

};


class Product
{
private:
    QSqlDatabase* db_;
    QSqlQuery query;

    void queryToVector(QVector<ProductInformation>* allProduct);

public:
    bool deleteProduct(int id);
    int addProduct(ProductInformation* prinfo);
    ProductInformation getProduct(int id);
    bool updateValues(ProductInformation* prinfo);
    QVector<ProductInformation> getAllProduct();
    QVector<ProductInformation> getAllProduct(QString sortBy);
    QVector<ProductInformation> getAllProduct(QString sortBy, int limit);
    QVector<ProductInformation> getAllProduct(QString sortBy, int limit, int offset);
    QVector<ProductInformation> getAllProduct(QString where, QString sortBy);
    QVector<ProductInformation> getAllProduct(QString where, QString sortBy, int limit);
    QVector<ProductInformation> getAllProduct(QString where, QString sortBy, int limit, int offset);
    QVector<ProductInformation> getAllProduct(int limit, int offset);
    Product(QSqlDatabase* db);
};

#endif // PRODUCT_H
