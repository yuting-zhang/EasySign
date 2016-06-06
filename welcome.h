#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>

namespace Ui {
class Welcome;
}

class Welcome : public QDialog
{
    Q_OBJECT
    
private slots:
    void CloseWelcome();


public:
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();
    
private:
    Ui::Welcome *ui;
    const long maxNum=177; // mainwindows also has a maxNum
};

#endif // WELCOME_H
