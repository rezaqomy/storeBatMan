#include "order.h"

Order::Order(QSqlDatabase* db): db(db)
{
    query = QSqlQuery(*db);
    if (!db) {
        qWarning() << "Product: Database connection not provided!";
    }
}

int Order::addOrder(OrderInformation* ordInfo) {
    QString InsertOrder = "INSERT INTO orders(ids_product, quantity, prices, discount, order_date , id_customer)"
            "VALUES(:ids_product, :quantity, :prices, :discount, :order_date , :id_customer)";
    query.prepare(InsertOrder);
    query.bindValue(":ids_product", vectorToQString(ordInfo->products));
    query.bindValue(":quantity", vectorToQString(ordInfo->quantity));
    query.bindValue(":prices", vectorToQStringPrice(ordInfo->products));
    query.bindValue(":discount", QString::number(ordInfo->discount));
    query.bindValue(":order_date", ordInfo->order_date);
    query.bindValue(":id_customer", ordInfo->customer.id);


    if (!query.exec()) {
        qCritical() << "Order: Error adding order to database:" << query.lastError().text();
        return -1;
    }
    ordInfo->id_order = query.lastInsertId().toInt();

    return ordInfo->id_order;
}

int Order::findProductIndex(OrderInformation *order, int id)
{
    for (int i{}; i < order->products.size(); i++) {
        if (id == order->products[i].id){
            return i;
        }
    }
    return -1;
}

QVector<OrderInformation> Order::getOredersByTime(QString first, QString seccond)
{
    query.exec(QString("SELECT * FROM orders WHERE order_date >= '%1' AND order_date <= '%2'").arg(first).arg(seccond));

    QVector<OrderInformation> orders = getOrders();
    return orders;
}

QVector<OrderInformation> Order::getOrders()
{
    QVector<OrderInformation> allOrder;

    Customer customer(db);
    while (query.next()) {
        OrderInformation orderInfo;
        orderInfo.id_order = query.value(0).toInt();
        QString productJson = query.value(1).toString();
        QString quantityJson = query.value(2).toString();
        QString PricesJson = query.value(3).toString();
        int discount = query.value(4).toInt();
        QString date = query.value(5).toString();
        int customerId = query.value(6).toInt();
        orderInfo.products = productIdJsonToVector(productJson);
        orderInfo.quantity = quantityJsonToVector(&quantityJson);
        orderInfo.prices = pricesJsonToVector(&PricesJson);
        orderInfo.discount = discount;
        orderInfo.order_date = date;
        orderInfo.customer = customer.getCustomer(customerId);


        allOrder.push_back(orderInfo);


    }

    if (!query.exec()) {
        qCritical() << "Orders: Error get orders to database:" << query.lastError().text();
    }
    return allOrder;
}

QVector<OrderInformation> Order::getAllOrders()
{

    QString selectQuery = QString("SELECT * FROM orders");
    query.exec(selectQuery);

    QVector<OrderInformation> allOrder = getOrders();

    return allOrder;
}


QString Order::vectorToQString(QVector<int> vec) noexcept{
    QString json = "{";
    for(int i{}; i < vec.size(); i++){
        if (!(i == 0)){
            json += ", " + QString::number(vec[i]);
        }
        else
            json += QString::number(vec[i]);
    }
    json += "}";
    return json;
}

QString Order::vectorToQString(QVector<ProductInformation> vec) noexcept
{
    QString json = "{ ";
    for(int i{}; i < vec.size(); i++){
        if (!(i == 0)){
            json += ", " + QString::number(vec[i].id);
        }
        else
            json += QString::number(vec[i].id);
    }
    json += "}";
    return json;
}

QString Order::vectorToQStringPrice(QVector<ProductInformation> vec) noexcept
{
    QString json = "{ ";
    for(int i{}; i < vec.size(); i++){
        if (!(i == 0)){
            json += ", " + QString::number(vec[i].price);
        }
        else
            json += QString::number(vec[i].price);
    }
    json += "}";
    return json;
}

QVector<ProductInformation> Order::productIdJsonToVector(QString json)
{
    Product product(db);
    QVector<ProductInformation> allOrder;
    QStringList numbers;
    QRegularExpression pattern("\\d+");

    QRegularExpressionMatchIterator it = pattern.globalMatch(json);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        numbers.append(match.captured(0));
    }

    for (int i{}; i < numbers.size(); i++) {
        allOrder.push_back(product.getProduct(numbers[i].toInt()));
    }

    return allOrder;
}

QVector<int> Order::quantityJsonToVector(QString *json)
{
    QVector<int> allQuantity;
    QStringList numbers;
    QRegularExpression pattern("\\d+");

    QRegularExpressionMatchIterator it = pattern.globalMatch(json);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        numbers.append(match.captured(0));
    }

    for (int i{}; i < numbers.size(); i++){
        allQuantity.push_back(numbers[i].toInt());
    }
    return allQuantity;
}

QVector<int> Order::pricesJsonToVector(QString *json)
{
    QVector<int> allPrice;
    QStringList numbers;
    QRegularExpression pattern("\\d+");

    QRegularExpressionMatchIterator it = pattern.globalMatch(json);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        numbers.append(match.captured(0));
    }
    for(int i{}; i < numbers.size(); i++){
        allPrice.push_back(numbers[i].toInt());
    }
    return allPrice;
}




