#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include <QThread>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QVariant>
#include "animation.h"
#include "product.h"
#include "productcard.h"
#include "addprudoctviewer.h"
#include "ordercard.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSqlDatabase* db, QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_CartMenuPushButton_clicked();

    void on_showProductMenuPushButton_clicked();

    void on_AllOrdersMenuPushButton_clicked();

    void on_TurnoversMenuPushButton_clicked();

    void on_addProduct_clicked();

    void handelAddProduct(ProductInformation* productInfo);

    void on_searchPushButton_clicked();

    void on_selectSortComboBox_currentIndexChanged(int index);


    void on_comboBox_2_currentIndexChanged(int index);

    void on_addToCartPushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    void updateProductInCart();
    Ui::MainWindow *ui;
    Product *product;
    Order* orderRepository;
    Customer* custmerRepoitory;
    QSqlDatabase* db;
    QString sortByProduct = "product_name";
    QString orderBy = " DESC ";
    void updateProductShow();
    OrderInformation* order = new OrderInformation;
    bool isValidIranianPhoneNumber(const QString& phoneNumber);
    bool isValidCustomerId(QString idText);

};
#endif // MAINWINDOW_H
