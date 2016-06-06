#ifndef CHOOSEUNITS_H
#define CHOOSEUNITS_H

#include <QDialog>
#include "configdata.h"
#include "studyqueue.h"
#include <utility>

namespace Ui {
class ChooseUnits;
}

class ChooseUnits : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseUnits(ConfigData* data, std::vector<std::pair<QString,QString>> units, QStringList*, QWidget *parent = 0);
    ~ChooseUnits();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ChooseUnits *ui;
    ConfigData* config;
    std::vector<std::pair<QString,QString>> unitName;
};

#endif // CHOOSEUNITS_H
