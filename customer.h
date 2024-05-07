#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


struct CustomerInformation{
    int id = -1;
    QString firs_name = "";
    QString Last_name = "";
    QString phone_number = "";
};






class Customer
{
private:
    QSqlDatabase* db;
    QSqlQuery query;

public:
    Customer(QSqlDatabase* db);
    int addCustomer(CustomerInformation* cusInfo);
    CustomerInformation getCustomer(int id);

};

#endif // CUSTOMER_H
