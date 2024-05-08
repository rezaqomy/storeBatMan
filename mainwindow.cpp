#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QSqlDatabase* db,QWidget *parent):
    db(db), QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    product = new Product(db);
    orderRepository = new Order(db);
    custmerRepoitory = new Customer(db);
    ui->customerInformationWidget->hide();
    updateProductShow();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AllOrdersMenuPushButton_clicked()
{
    QPushButton *button = ui->AllOrdersMenuPushButton;
    Animation::moveFromRightToLeft(button, 25);
    QVector<OrderInformation> orders = orderRepository->getAllOrders();


    QGridLayout* gridLayout = new QGridLayout();

    QWidget* window = new QWidget();

    for (int i{}; i < orders.size(); i++) {
        OrderCard* orderCard = new OrderCard(&orders[i]);
        gridLayout->addWidget(orderCard, i, 0);
    }
    window->setLayout(gridLayout);
    ui->showOrdersScrollArea->setWidget(window);



    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::updateTurnover()
{
    QVector<OrderInformation> orders = orderRepository->getOredersByTime( firstDate.toString("yyyy-MM-dd") , secondDate.toString("yyyy-MM-dd"));
    qDebug() << orders.size();

    QGridLayout* gridLayout = new QGridLayout();

    QWidget* window = new QWidget();

    for (int i{}; i < orders.size(); i++) {
        OrderCard* orderCard = new OrderCard(&orders[i]);
        gridLayout->addWidget(orderCard, i, 0);
    }
    window->setLayout(gridLayout);
    ui->timeOrder_scrollArea->setWidget(window);

    //----------------------------------------------------------------------

    QChartView *chartView;
    m_dataTable = configureDate(orders);

    chartView = new QChartView(createBarChart(10));
    ui->gridLayout->addWidget(chartView, 0,0);
    ui->allPrce_label->setText(QString::number(TOTAL_PRICE));
    ui->theAllDiscount_label->setText(QString::number(TOTAL_DISCOUNT));
    ui->theAllFinal_label->setText(QString::number(TOTAL_FINAL_PRICE));


}


QChart *MainWindow::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("sell chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("sell set " + QString::number(i));
        for (const Data &data : m_dataTable[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, m_valueMax * 2);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%1i  toman");

    // Create a category axis for the X-axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    // Set the categories (labels) for the X-axis
    QStringList categories;
    for (const DataList &dataList : m_dataTable) {
        for (const Data &data : dataList) {
            categories << data.second; // Assuming data.second contains the label
        }
    }
    axisX->append(categories);

    // Set the X-axis on the chart
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    return chart;
}

DataTable MainWindow::configureDate(QVector<OrderInformation> orders)
{
    DataTable dataTable;

    QMap<QDate, int> dailySales;
    TOTAL_PRICE = 0;
    TOTAL_DISCOUNT = 0;
    TOTAL_FINAL_PRICE = 0;

    for (const OrderInformation& order : orders) {
        QDate orderDate = QDate::fromString(order.order_date, "yyyy-MM-dd");
        int orderTotal = 0;
        for (int i = 0; i < order.products.size(); ++i) {
            orderTotal += order.prices[i] * order.quantity[i];
        }
        dailySales[orderDate] += orderTotal - order.discount;
        TOTAL_PRICE += orderTotal;
        TOTAL_DISCOUNT += order.discount;
        TOTAL_FINAL_PRICE += orderTotal - order.discount;
    }


    DataList dataList;
    for (QDate date = firstDate; date < secondDate; date = date.addDays(1)) {
        int price = dailySales.value(date, 0);
        if (m_valueMax < price){
            m_valueMax = price;
        }
        QPoint point(date.toJulianDay(), price);
        dataList << Data(point, date.toString("MM-dd"));
    }

    dataTable << dataList;
    return dataTable;
}



void MainWindow::on_TurnoversMenuPushButton_clicked()
{
    QPushButton *button = ui->TurnoversMenuPushButton;
    Animation::moveFromRightToLeft(button, 25);

    firstDate = QDate::currentDate().addMonths(-1);
    secondDate = QDate::currentDate();

    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit->setDate(firstDate);
    ui->dateEdit->setMaximumDate(secondDate);

    ui->dateEdit_2->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_2->setDate(secondDate);
    ui->dateEdit_2->setMaximumDate(QDate::currentDate());



    updateTurnover();

    ui->stackedWidget->setCurrentIndex(3);
}




void MainWindow::on_dateEdit_2_dateChanged(const QDate &date)
{
    ui->dateEdit->setMaximumDate(date);
    secondDate = date;
    updateTurnover();
}


void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    firstDate = date;
    updateTurnover();
}


