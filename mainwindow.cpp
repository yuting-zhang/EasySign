#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    player(&configData),
    queue(&configData),
    viewed(false)
{
    ui->setupUi(this);
    QVBoxLayout *layout= new QVBoxLayout;
    layout->addWidget(&player);
    ui->videoFrame->setLayout(layout);
    ui->stackedWidget->setCurrentIndex(0);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,size(),qApp->desktop()->availableGeometry()));
    ReloadConfig();
}

void MainWindow::ReloadConfig()
{
    player.ReloadConfig();
    queue.ReloadConfig();
    ResetMainWindow();
}

void MainWindow::ResetMainWindow()
{
    if (configData.get("SPEED")=="NORMAL")
        ui->DefaultFast->setChecked(true);
    else
        if (configData.get("SPEED")=="SLOW")
            ui->DefaultSlow->setChecked(true);
        else
            ui->DefaultVerySlow->setChecked(true);
    if (configData.get("MIRRORED")=="TRUE")
        ui->DefaultMirrored->setChecked(true);
    else
        ui->DefaultNormal->setChecked(true);
    if (configData.get("DICTIONARY")=="CHINA")
        ui->DefaultChina->setChecked(true);
    else
        ui->DefaultZhenjiang->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ToTransButton_clicked()
{
    player.EnableVideoPlayer();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_TransPageReturnButton_clicked()
{
    player.ResetVideoPlayer();
    ui->TransPageInput->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_TransPagePlayButton_clicked()
{
    player.TranslateSentence(ui->TransPageInput->toPlainText());
}

void MainWindow::on_ToSettingsButton_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_SettingsPageReturnButton_clicked()
{
    ReloadConfig();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_DefaultNormal_clicked()
{
    configData.put("MIRRORED","FALSE");
}

void MainWindow::on_DefaultMirrored_clicked()
{
    configData.put("MIRRORED","TRUE");
}

void MainWindow::on_DefaultFast_clicked()
{
    configData.put("SPEED","NORMAL");
}

void MainWindow::on_DefaultSlow_clicked()
{
    configData.put("SPEED","SLOW");
}

void MainWindow::on_DefaultVerySlow_clicked()
{
    configData.put("SPEED","VERYSLOW");
}

void MainWindow::on_DefaultChina_clicked()
{
    configData.put("DICTIONARY","CHINA");
}

void MainWindow::on_DefaultZhenjiang_clicked()
{
    configData.put("DICTIONARY","ZHENJIANG");
}

void MainWindow::on_ToLearnButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    player.EnableVideoPlayer();
    NextWord();
}

bool MainWindow::checkViewed()
{
    if (viewed)
        return true;
    QMessageBox message;
    message.setText("尚未查看标准翻译，确认继续?");
    message.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int ret=message.exec();
    if (ret==QMessageBox::Yes)
        return true;
    else
        return false;
}

void MainWindow::on_LearnInc_clicked()
{
    if (!checkViewed())
        return;
    currItem->incLevel();
    queue.sort();
    NextWord();
}

void MainWindow::on_LearnSame_clicked()
{
    if (!checkViewed())
        return;
    currItem->unchange();
    queue.sort();
    NextWord();
}

void MainWindow::on_LearnDec_clicked()
{
    if (!checkViewed())
        return;
    currItem->decLevel();
    queue.sort();
    NextWord();
}

void MainWindow::NextWord()
{
    viewed=false;
    queue.updateFiles();
    currItem=queue.getNext();
    player.ResetVideoPlayer();
    player.EnableVideoPlayer();
    if (currItem!=nullptr)
    {
        ui->LearnWord->setText(currItem->getWord());
        ui->LearnControl->setEnabled(true);
    }
    else
    {
        if (queue.learningEmpty())
            ui->LearnWord->setText("尚未选择课程！");
        else
        {
            ui->LearnWord->setText("你已经完成了本轮学习！");
            QMessageBox msg;
            msg.setText("你已经完成了本轮学习！请稍后回来继续学习！");
            msg.exec();
        }
        ui->LearnControl->setEnabled(false);
        player.ResetVideoPlayer();
    }
}

void MainWindow::on_LearnReturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    player.ResetVideoPlayer();
    ui->LearnControl->setEnabled(false);
}

void MainWindow::on_LearnUnit_clicked()
{
    ChooseUnits* unit= new ChooseUnits(&configData, queue.getUnits(),queue.getLearning());
    unit->exec();
    delete unit;
    ReloadConfig();
    player.EnableVideoPlayer();
    NextWord();
}

void MainWindow::on_LearnPlay_clicked()
{
    viewed=true;
    player.TranslateSentence(currItem->getWord());
}
