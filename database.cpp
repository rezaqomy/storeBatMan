#include "database.h"

DataBase::DataBase(QSqlDatabase* db){
    this->db = db;
    if (!openConnection()) {
        throw std::runtime_error("Failed to open database connection");
    }
    createTables();
}

DataBase::~DataBase() {
    db->close();
}

bool DataBase::openConnection() {
    if (!db->open()) {

        return false;
    }
    return true;
}

void DataBase::createTables() {
    query.exec("CREATE TABLE customer (id_customer INTEGER PRIMARY KEY AUTOINCREMENT, first_name VARCHAR(30), last_name VARCHAR(40) , phone_number VARCHAR(11))");
    query.exec("CREATE TABLE product (id_product INTEGER PRIMARY KEY AUTOINCREMENT, product_name VARCHAR(40) NOT NULL, price INTEGER NOT NULL, quantity INTEGER NOT NULL)");
    query.exec("CREATE TABLE orders (id_order INTEGER PRIMARY KEY AUTOINCREMENT, ids_product JSON NOT NULL, quantity JSON NOT NULL, prices JSON NOT NULL, discount INTEGER NOT NULL, order_date TEXT NOT NULL, id_customer INTEGER NOT NULL, FOREIGN KEY (id_customer) REFERENCES customer(id_customer))");
    // ... Add more table definitions if needed
}
