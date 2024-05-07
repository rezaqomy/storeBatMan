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
        qDebug() << "ok";
        gridLayout->addWidget(orderCard, i, 0);
    }
    window->setLayout(gridLayout);
    ui->showOrdersScrollArea->setWidget(window);



    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_TurnoversMenuPushButton_clicked()
{
    QPushButton *button = ui->TurnoversMenuPushButton;
    Animation::moveFromRightToLeft(button, 25);
    ui->stackedWidget->setCurrentIndex(3);
}

