#include "addprudoctviewer.h"
#include "ui_addprudoctviewer.h"

AddPrudoctViewer::AddPrudoctViewer(ProductInformation product, QWidget *parent) :
    product(product) ,QWidget(parent),
    ui(new Ui::AddPrudoctViewer)
{

    ui->setupUi(this);
    if (product.id == -1) {
        ui->TitleProductLabel->setText("ADD PRODUCT");
    } else {
        ui->TitleProductLabel->setText("EDIT PRODUCT");
        ui->ProductNameLineEdit->setText(product.productName);
        ui->ProductPriceLineEdit->setText(QString::number(product.price));
        ui->ProductQuantityLineEdit->setText(QString::number(product.quantity));
    }
}

AddPrudoctViewer::~AddPrudoctViewer()
{
    delete ui;
}

void AddPrudoctViewer::on_ConfrimPushButton_clicked()
{
    bool isValide = true;
    QString name = ui->ProductNameLineEdit->text();
    if (name.size() < 3 || name == "   "){
        isValide = false ;
        ui->name_label->setStyleSheet("color: rgb(255,0,0)");
    } else {
        product.productName = ui->ProductNameLineEdit->text();
        ui->name_label->setStyleSheet("color: rgb(0,0,0)");
    }
    QString price = ui->ProductPriceLineEdit->text();
    QVariant priceVariant(price);
    if ((priceVariant.canConvert(QVariant::Int) && price.toInt() != 0 )|| price.toInt() > 0) {
        product.price = price.toInt();
        ui->price_label->setStyleSheet("color: rgb(0,0,0)");
    } else {
        isValide = false;

        ui->price_label->setStyleSheet("color: rgb(255,0,0)");
    }
    QString quantity = ui->ProductQuantityLineEdit->text();
    QVariant quantityVar(quantity);
    if ((quantityVar.canConvert(QVariant::Int) && quantity.toInt() != 0) || quantity.toInt() > 0){
        product.quantity = quantity.toInt();

        ui->quantity_label->setStyleSheet("color: rgb(0,0,0)");
    } else {
        isValide = false;
        ui->quantity_label->setStyleSheet("color: rgb(255,0,0)");
    }
    if (isValide) {
        ui->ProductNameLineEdit->setText("");
        ui->ProductPriceLineEdit->setText("");
        ui->ProductQuantityLineEdit->setText("");

    if (product.id == -1) {
        emit sendProductAded(&product);
    }
    }
}

