#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include "product.h"
#include "QSqlDatabase"

class ProductRepository{
public:
    ProductRepository();
    virtual Product getProduct(int id);
    virtual Product getProducts();
    virtual Product getProducts(QString sortBy = "product_name", QString searchProduct = "");
    virtual int addProduct(Product* product);
    virtual bool editProduct(Product* product);
    virtual bool deleteProduct(Product* product);

protected:
    QSqlDatabase* db;
};


#endif // PRODUCTREPOSITORY_H
