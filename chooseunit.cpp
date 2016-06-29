#include "chooseunit.h"
#include "ui_chooseunit.h"
#include <QDesktopWidget>
#include <vector>
using std::vector;

ChooseUnit::ChooseUnit(unsigned* index,const vector<vector<QString>>& book,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseUnit),
    bookIndex(index)
{
    ui->setupUi(this);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                    size(),qApp->desktop()->availableGeometry()));
    for (decltype(book.size()) i=0;i!=book.size();++i)
    {
        ui->ChooseUnitBox->addItem(book[i][0]);
    }
}

ChooseUnit::~ChooseUnit()
{
    delete ui;
}



void ChooseUnit::on_ChooseUnitCancel_clicked()
{
    close();
}

void ChooseUnit::on_ChooseUnitOK_clicked()
{
    *bookIndex=ui->ChooseUnitBox->currentIndex();
    close();
}
