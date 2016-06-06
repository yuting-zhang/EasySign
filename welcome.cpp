#include "welcome.h"
#include "ui_welcome.h"
#include <QTimer>
#include <QDesktopWidget>
#include "FileProcess.h"

Welcome::Welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,
                                    size(),qApp->desktop()->availableGeometry()));
    addExtension(maxNum);
    QTimer::singleShot(1500, this, SLOT(CloseWelcome()));
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::CloseWelcome()
{
    close();
}
