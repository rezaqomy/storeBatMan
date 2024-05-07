#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <exception>
#include <QDebug>

class DataBase {
public:
    explicit DataBase(QSqlDatabase* db);
    ~DataBase();



private:
    QSqlDatabase* db;
    QSqlQuery query;

    bool openConnection();
    void createTables();
};

#endif // DATABASE_H
