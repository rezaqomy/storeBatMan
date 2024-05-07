#include "customer.h"

Customer::Customer(QSqlDatabase* db): db(db)
{
    query = QSqlQuery(*db);
    if (!db) {
        qWarning() << "Product: Database connection not provided!";
    }
}


int Customer::addCustomer(CustomerInformation* cusInfo){
    QString insertQuery = "INSERT INTO customer (first_name, last_name, phone_number) "
                          "VALUES ( :first_name, :last_name, :phone_number)";

    query.prepare(insertQuery);
    query.bindValue(":first_name", cusInfo->firs_name);
    qDebug() << cusInfo->firs_name;
    query.bindValue(":last_name", cusInfo->Last_name);
    query.bindValue(":phone_number", cusInfo->phone_number);




    if (!query.exec()) {
        qCritical() << "Customer: Error adding customer to database:" << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();;
}




CustomerInformation Customer::getCustomer(int id) {
    CustomerInformation cusInfo;
    qDebug() << "ok";
    QString selectQuery = "SELECT * FROM customer WHERE id_customer = %1";
    query.exec(selectQuery.arg(id));

    query.next();

    cusInfo.id = id;
    cusInfo.firs_name = query.value(1).toString();
    cusInfo.Last_name = query.value(2).toString();
    cusInfo.phone_number = query.value(3).toString();


    if (!query.exec()) {
        qCritical() << "Product: Error adding product to database:" << query.lastError().text();
        return cusInfo;
    }


    return cusInfo;

}
