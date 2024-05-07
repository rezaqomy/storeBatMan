#include "mainwindow.h"
#include "database.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("store.db");
    DataBase dataBase(&db);


    QApplication a(argc, argv);
    MainWindow w(&db);
    w.show();
    return a.exec();
}
