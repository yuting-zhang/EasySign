#ifndef VEDIOPLAYER_H
#define VEDIOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include "dictionary.h"
#include "configdata.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(ConfigData*, QWidget *parent = 0);
    ~VideoPlayer();
    void ResetVideoPlayer();
    void ReloadConfig();
    void EnableVideoPlayer();
    void TranslateSentence(QString);

private slots:

    void on_FastButton_clicked();

    void on_SlowButton_clicked();

    void on_VerySlowButton_clicked();

    void on_NormalButton_clicked();

    void on_MirrorButton_clicked();

private:
    void debugPlay();
    void changeSpeed(qreal speed);
    void JumpPlay();

    Ui::VideoPlayer *ui;
    QMediaPlayer player;
    QMediaPlaylist playList;
    QVideoWidget videoWidget; 
    QString CurrentSentence;
    bool Mirrored;
    ConfigData* config;
    Dictionary dic;
};

#endif // VEDIOPLAYER_H
