#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_showProductMenuPushButton_clicked()
{
    QPushButton *button = ui->showProductMenuPushButton;
    Animation::moveFromRightToLeft(button, 25);



    updateProductShow();

    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::updateProductShow()
{
    QVector<ProductInformation> prsInfo = product->getAllProduct(QString(" product_name LIKE '%%1%' ").arg(ui->searchProductLineEdit->text()), sortByProduct + orderBy);

    QGridLayout* gridLayout = new QGridLayout();

    QWidget* window = new QWidget();

    window->setWindowTitle("Product List");
    for (int i = 0; i < prsInfo.size(); ++i) {
        ProductCard* productCard = new ProductCard(prsInfo[i], order);
        productCard->setStyleSheet("background-color: rgb(244, 238, 255);");

        gridLayout->addWidget(productCard, i / 3, i % 3);

    }
    window->setLayout(gridLayout);
    ui->ShowProductsScrollArea->setWidget(window);
}

void MainWindow::on_addProduct_clicked()
{
    ProductInformation product;
    product.id = -1;
    AddPrudoctViewer* window = new AddPrudoctViewer(product);
    QObject::connect(window , &AddPrudoctViewer::sendProductAded, this, &MainWindow::handelAddProduct);
    window->show();
}

void MainWindow::handelAddProduct(ProductInformation *productInfo)
{
    product->addProduct(productInfo);
}

void MainWindow::on_selectSortComboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    switch (index) {
    case 0: {
        sortByProduct = "product_name";
        updateProductShow();
        break;
    } case 1: {
        sortByProduct = "price";
        updateProductShow();
        break;
    } case 2: {
        sortByProduct = "quantity";
        updateProductShow();
        break;
    }
    }
}

void MainWindow::on_searchPushButton_clicked()
{
    updateProductShow();
}

void MainWindow::on_addToCartPushButton_clicked()
{
    if (order->products.size() != 0)
        updateProductInCart();
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index) {
    case 0: {
        orderBy = " ASC ";
        updateProductShow();
        break;
    } case 1:
        orderBy = " DESC ";
        updateProductShow();
        break;
    }
}
