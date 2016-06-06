#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoplayer.h"
#include "configdata.h"
#include "studyqueue.h"
#include "chooseunits.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ReloadConfig();
    void ResetMainWindow();
    void NextWord();

private slots:
    void on_ToTransButton_clicked();

    void on_TransPageReturnButton_clicked();

    void on_TransPagePlayButton_clicked();

    void on_ToSettingsButton_clicked();

    void on_SettingsPageReturnButton_clicked();

    void on_DefaultNormal_clicked();

    void on_DefaultMirrored_clicked();

    void on_DefaultFast_clicked();

    void on_DefaultSlow_clicked();

    void on_DefaultVerySlow_clicked();

    void on_DefaultChina_clicked();

    void on_DefaultZhenjiang_clicked();

    void on_ToLearnButton_clicked();

    void on_LearnSame_clicked();

    void on_LearnInc_clicked();

    void on_LearnDec_clicked();

    void on_LearnReturn_clicked();

    void on_LearnUnit_clicked();

    void on_LearnPlay_clicked();

private:
    Ui::MainWindow *ui;
    ConfigData configData;
    VideoPlayer player;
    StudyQueue queue;
    StudyItem* currItem;
    bool viewed;

    bool checkViewed();
};

#endif // MAINWINDOW_H
