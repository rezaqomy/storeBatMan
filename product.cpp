#include "product.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Product::Product(QSqlDatabase* db) : db_(db) {
    query = QSqlQuery(*db_);
    if (!db_) {
        qWarning() << "Product: Database connection not provided!";
    }
}



void Product::queryToVector(QVector<ProductInformation>* allProduct)
{
    while (query.next()) {
        ProductInformation prinfo;

        prinfo.id = query.value(0).toInt();
        prinfo.productName = query.value(1).toString();
        prinfo.price = query.value(2).toInt();
        prinfo.quantity = query.value(3).toInt();



        allProduct->push_back(prinfo);
    }
}

bool Product::deleteProduct(int id)
{
    QString deleteQuery = "DELETE FROM product WHERE id = %1";
    query.exec(deleteQuery.arg(id));

}

QVector<ProductInformation> Product::getAllProduct() {
    QVector<ProductInformation> allProduct;


    query.exec("SELECT * FROM product");

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString sortBy)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product ORDER BY %1").arg(sortBy);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString sortBy, int limit)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product ORDER BY %1 LIMIT %2").arg(sortBy).arg(limit);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString sortBy, int limit, int offset)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product ORDER BY %1 LIMIT %2 OFFSET %3").arg(sortBy).arg(limit).arg(offset);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString where, QString sortBy)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product WHERE %1 ORDER BY %2").arg(where).arg(sortBy);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString where, QString sortBy, int limit)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product WHERE %1 ORDER BY %2 LIMIT %3").arg(where).arg(sortBy).arg(limit);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(QString where, QString sortBy, int limit, int offset)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product WHERE %1 ORDER BY %2 LIMIT %3 OFFSET %4").arg(where).arg(sortBy).arg(limit).arg(offset);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

QVector<ProductInformation> Product::getAllProduct(int limit, int offset)
{
    QVector<ProductInformation> allProduct;
    QString selectQuery = QString("SELECT * FROM product LIMIT %1 OFFSET %2").arg(limit).arg(offset);


    query.exec(selectQuery);

    queryToVector(&allProduct);


    return allProduct;
}

ProductInformation Product::getProduct(int id){
    ProductInformation prinfo;



    QString insertQuery = "SELECT * FROM product WHERE id_product = %1";

    query.exec(insertQuery.arg(id));
    query.next();

    prinfo.id = query.value(0).toInt();
    prinfo.productName = query.value(1).toString();
    prinfo.price = query.value(2).toInt();
    prinfo.quantity = query.value(3).toInt();


    return prinfo;
}

bool Product::updateValues(ProductInformation* prinfo){

    QString insertQuery = "UPDATE product SET product_name = :Nproduct_name, price = :Nprice, quantity = :Nquantity WHERE id_product = %1 ";
    qDebug() << "ok";

    query.prepare(insertQuery.arg(prinfo->id));
    query.bindValue(":Nproduct_name", prinfo->productName);
    query.bindValue(":Nprice", prinfo->price);
    query.bindValue(":Nquantity", prinfo->quantity);


    if (!query.exec()) {
        qCritical() << "Product: Error updating product to database:" << query.lastError().text();
        return -1;
    }

    prinfo->id = query.lastInsertId().toInt();
    return true;

}




int Product::addProduct(ProductInformation* prinfo) {


    QString insertQuery = "INSERT INTO product (product_name, price, quantity) "
                          "VALUES (:product_name, :price, :quantity)";

    query.prepare(insertQuery);
    query.bindValue(":product_name", prinfo->productName);
    query.bindValue(":price", prinfo->price);
    query.bindValue(":quantity", prinfo->quantity);




    if (!query.exec()) {
        qCritical() << "Product: Error adding product to database:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();
}
