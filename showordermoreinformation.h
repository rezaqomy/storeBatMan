#ifndef SHOWORDERMOREINFORMATION_H
#define SHOWORDERMOREINFORMATION_H

#include <QWidget>
#include "order.h"
#include "product.h"
#include "customer.h"

namespace Ui {
class ShowOrderMoreInformation;
}

class ShowOrderMoreInformation : public QWidget
{
    Q_OBJECT

public:
    explicit ShowOrderMoreInformation(OrderInformation* order ,QWidget *parent = nullptr);
    ~ShowOrderMoreInformation();

private:
    Ui::ShowOrderMoreInformation *ui;
    OrderInformation* order = new OrderInformation;
    void updateInformation();

};

#endif // SHOWORDERMOREINFORMATION_H
