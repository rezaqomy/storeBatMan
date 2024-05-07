#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::updateProductInCart(){
    QVector<ProductInformation> prsInfo = order->products;

    int theAllPrice{};
    QGridLayout* gridLayout = new QGridLayout();

    QWidget* window = new QWidget();

    window->setWindowTitle("Product List");
    for (int i = 0; i < prsInfo.size(); ++i) {
        theAllPrice += order->products[i].price * order->quantity[i];
        ProductCard* productCard = new ProductCard(prsInfo[i], order);
        productCard->setStyleSheet("background-color: rgb(244, 238, 255);");
        //connect(productCard ,&ProductCard::updateTheScreen, this, &MainWindow::updateProductInCart);
        gridLayout->addWidget(productCard, i / 3, i % 3);

    }
    window->setLayout(gridLayout);
    qDebug() << theAllPrice;

    //ui->price_All_label->setText("price : " + QString::number(theAllPrice));



    ui->productInCartScrollArea->setWidget(window);
    qDebug()<< "update cart";
}

void MainWindow::on_CartMenuPushButton_clicked()
{
    QPushButton *button = ui->CartMenuPushButton;
    Animation::moveFromRightToLeft(button, 25);

    updateProductInCart();
    ui->stackedWidget->setCurrentIndex(1);
}

bool MainWindow::isValidIranianPhoneNumber(const QString &phoneNumber)
{
    QRegularExpression phoneRegex(R"(09\d{9})");

    return phoneRegex.match(phoneNumber).hasMatch();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug() << arg1;
    if (arg1 == 2){
        ui->customerIdWidget->hide();
        ui->customerInformationWidget->show();
    } else{
        ui->customerIdWidget->show();
        ui->customerInformationWidget->hide();
    }
}

bool MainWindow::isValidCustomerId(QString idText)
{
    bool isValid = true;
    QVariant variant(idText);
    if (variant.canConvert(QVariant::Int)){
        int id = idText.toInt();
        /* TODO ADD CONNECTION TO DATABASE */
    } else{
        isValid = false;
    }
    return isValid;
}

void MainWindow::on_pushButton_clicked()
{

    bool isValid = true;
    if(ui->checkBox->isChecked()) {
        if (ui->customer_firs_name_lineEdit->text().size() >= 3) {
            order->customer.firs_name = ui->customer_firs_name_lineEdit->text();
            ui->cusotmer_firstName_label->setStyleSheet("color: rgb(0,0,0)");
        } else {
            isValid = false;
            ui->cusotmer_firstName_label->setStyleSheet("color: rgb(255,0,0);");
        }
        if (ui->costomer_lastName_lineEdit->text().size() >= 3 ) {
            order->customer.Last_name = ui->costomer_lastName_lineEdit->text();
            ui->customer_lastName_label->setStyleSheet("color: rgb(0,0,0)");
        } else {
            isValid = false;
            ui->customer_lastName_label->setStyleSheet("color: rgb(255,0,0);");
            qDebug() << "lo";
        }
        if (isValidIranianPhoneNumber(ui->customer_phoneNumber_lineEdit->text())) {
            order->customer.phone_number = ui->customer_phoneNumber_lineEdit->text();
            ui->custoemr_phoneNumber_label->setStyleSheet("color: rgb(0,0,0);");
        } else {
            isValid = false;
            ui->custoemr_phoneNumber_label->setStyleSheet("color: rgb(255,0,0);");
        }
    } else {
        if (isValidCustomerId(ui->customer_id_lineEdit->text())) {
            ui->customer_id_label->setStyleSheet("color: rgb(0,0,0)");
            order->customer.id = ui->customer_id_lineEdit->text().toInt();
        } else {
            isValid = false;
            ui->customer_id_label->setStyleSheet("color: rgb(255,0,0)");
        }
    }
    int price{};
    int discount{};
    for (int i{}; i < order->products.size(); i++) {
        price += order->products[i].price * order->quantity[i];
    }
    ui->price_All_label->setText("price : " + QString::number(price));
    if (ui->discount_lineEdit->text().toInt() < price) {
        ui->discount_label->setStyleSheet("color: rgb(0,0,0);");
        discount = ui->discount_lineEdit->text().toInt();
    } else {
        isValid = false;
        ui->discount_label->setStyleSheet("color: rgb(255,0,0);");
    }
    ui->discount_Label->setText("- discount : " + QString::number(discount));
    ui->discounted_price_label->setText("final price : "+ QString::number(price - discount));


    if (isValid) {
        QMessageBox msgBox;

        msgBox.setText("Do you confirm the following information?");
        msgBox.layout()->addWidget(ui->price_All_label);
        msgBox.layout()->addWidget(ui->discount_Label);
        msgBox.layout()->addWidget(ui->discounted_price_label);

        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        int result = msgBox.exec();
        if (result == QMessageBox::Yes){
            order->discount = discount;
            order->order_date = "2024-1-1";
            if (order->customer.id == -1){
                order->customer.id = custmerRepoitory->addCustomer(&order->customer);
            }
            orderRepository->addOrder(order);
            for (int i{}; i < order->products.size(); i++) {
                order->products[i].quantity -= order->quantity[i];
                product->updateValues(&order->products[i]);
            }
            order = new OrderInformation;


            ui->customer_firs_name_lineEdit->setText("");
            ui->costomer_lastName_lineEdit->setText("");
            ui->customer_phoneNumber_lineEdit->setText("");
            ui->customer_id_lineEdit->setText("");
            ui->discount_lineEdit->setText("");

        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    updateProductInCart();
}
