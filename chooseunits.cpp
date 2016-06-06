#include "chooseunits.h"
#include "ui_chooseunits.h"
#include <vector>

ChooseUnits::ChooseUnits(ConfigData* data, std::vector<std::pair<QString,QString>> units, QStringList* learning, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUnits),
    config(data),
    unitName(units)
{
    ui->setupUi(this);
    for (auto const& it :units)
    {
        QListWidgetItem* item=new QListWidgetItem(it.second,ui->listWidget);
        for (auto const& j: *learning)
            if (it.first==j)
            {
                item->setSelected(true);
                break;
            }
        ui->listWidget->addItem(item);
    }
}

ChooseUnits::~ChooseUnits()
{
    delete ui;
}

void ChooseUnits::on_buttonBox_accepted()
{
    QString val;
    auto list=ui->listWidget->selectedItems();
    for (const auto& it: list)
        for (const auto& j: unitName)
           if (j.second==(*it).text())
                    val+=j.first+" ";
    config->put("LEARN",val);
}
