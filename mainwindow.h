#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include <QChart>
#include <QDateTime>

#include <QLineSeries>
#include <QDateTimeAxis>
#include <QMainWindow>
#include <QThread>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QVariant>
#include <QDate>
#include "animation.h"
#include "product.h"
#include "productcard.h"
#include "addprudoctviewer.h"
#include "ordercard.h"

//-----------------------------------

#include <QtCharts/QValueAxis>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

//--------------------------------------


using namespace QtCharts;

//-------------------------------------------------

typedef QPair<QPoint, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

//-------------------------------------------------

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

    void on_dateEdit_2_dateChanged(const QDate &date);

    void on_dateEdit_dateChanged(const QDate &date);


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
    QDate firstDate;
    QDate secondDate;
    void updateTurnover();
    //-------------------------------------------------------
    QChart *createBarChart(int valueCount) const;
    int m_listCount = 1;
    int m_valueMax = 1000;
    int m_valueCount = 7;
    int TOTAL_PRICE;
    int TOTAL_DISCOUNT;
    int TOTAL_FINAL_PRICE;
    DataTable m_dataTable;
    DataTable configureDate(QVector<OrderInformation> orders);
};
#endif // MAINWINDOW_H
