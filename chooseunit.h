#ifndef CHOOSEUNIT_H
#define CHOOSEUNIT_H

#include <QDialog>
#include <vector>
using std::vector;

namespace Ui {
class ChooseUnit;
}

class ChooseUnit : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChooseUnit(unsigned *index,const vector<vector<QString>>& book,QWidget *parent = 0);
    ~ChooseUnit();
    
private slots:


    void on_ChooseUnitCancel_clicked();

    void on_ChooseUnitOK_clicked();

private:
    Ui::ChooseUnit *ui;
    unsigned* bookIndex;
};

#endif // CHOOSEUNIT_H
