#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QStyle>
#include <QDesktopWidget>

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT
    
public:
    explicit Info(QWidget *parent = 0);
    ~Info();
    
private:
    Ui::Info *ui;
};

#endif // INFO_H
