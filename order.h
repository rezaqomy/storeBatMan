#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include "customer.h"
#include <sstream>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QStringList>
#include <QVector>
#include <regex>
#include <QString>
#include <QStringList>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

struct OrderInformation {
  int id_order;
  QVector<ProductInformation> products;
  QVector<int> quantity;
  QVector<int> prices;
  int discount;
  QString order_date;
  CustomerInformation customer;
};






class Order
{
private:
    QSqlDatabase* db;
    QSqlQuery query;
    QString vectorToQString(QVector<int> vec) noexcept;
    QString vectorToQString(QVector<ProductInformation> vec) noexcept;
    QString vectorToQStringPrice(QVector<ProductInformation> vec) noexcept;
    QVector<ProductInformation> productIdJsonToVector(QString json);
    QVector<int> quantityJsonToVector(QString* json);
    QVector<int> pricesJsonToVector(QString* json);
    
public:
    Order(QSqlDatabase* db);
    int addOrder(OrderInformation* ordInfo);
    static int findProductIndex(OrderInformation* order, int id);
    QVector<OrderInformation> getCustomerOrders(int customer_id);
    QVector<OrderInformation> getOredersLastMonth();
    QVector<OrderInformation> getAllOrders();
};

#endif // ORDER_H
