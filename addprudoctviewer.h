#ifndef ADDPRUDOCTVIEWER_H
#define ADDPRUDOCTVIEWER_H

#include <QWidget>
#include <QVariant>
#include "product.h"
#include "mainwindow.h"


namespace Ui {
class AddPrudoctViewer;
}

class AddPrudoctViewer : public QWidget
{
    Q_OBJECT

public:
    explicit AddPrudoctViewer(ProductInformation product,QWidget *parent = nullptr);
    ~AddPrudoctViewer();

private slots:
    void on_ConfrimPushButton_clicked();

private:
    Ui::AddPrudoctViewer *ui;
    ProductInformation product;

Q_SIGNALS:
    ProductInformation sendProductAded(ProductInformation* productInfo);
};

#endif // ADDPRUDOCTVIEWER_H
