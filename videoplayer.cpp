#include "videoplayer.h"
#include "ui_videoplayer.h"

VideoPlayer::VideoPlayer(ConfigData* data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer),
    player(0,QMediaPlayer::VideoSurface),
    Mirrored(false),
    config(data),
    dic(config)
{
    ui->setupUi(this);

    //Setup QMediaPlayer
    QVBoxLayout* layout= new QVBoxLayout;
    player.setVideoOutput(&videoWidget);
    layout->addWidget(&videoWidget);
    ui->PlayWidget->setLayout(layout);
    //SetupQMediaPlayer Ends
    ReloadConfig();
    //debugPlay();
}
VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::debugPlay()
{
    //player.setMedia(QUrl::fromLocalFile("D:/其他视频/格式工厂Bad Apple PV.mp4"));
    // player.play();
    dic.generatePlaylist(QString("琪露诺你是笨蛋！"),playList,false);
    player.setPlaylist(&playList);
    player.play();
}

void VideoPlayer::ResetVideoPlayer()
{
    if (config->get("SPEED")=="NORMAL")
    {
        ui->FastButton->setChecked(true);
        changeSpeed(1);
    }
    else
        if (config->get("SPEED")=="SLOW")
        {
            ui->SlowButton->setChecked(true);
            changeSpeed(0.5);
        }
        else
        {
            ui->VerySlowButton->setChecked(true);
            changeSpeed(0.25);
        }

    if (config->get("MIRRORED")=="TRUE")
    {
        ui->MirrorButton->setChecked(true);
        Mirrored=true;
    }
    else
    {
        ui->NormalButton->setChecked(true);
        Mirrored=false;
    }

    ui->SpeedControl->setEnabled(false);
    ui->MirrorControl->setEnabled(false);
    videoWidget.hide();
    player.stop();
    CurrentSentence="";

}

void VideoPlayer::EnableVideoPlayer()
{
    ui->SpeedControl->setEnabled(true);
    ui->MirrorControl->setEnabled(true);
    videoWidget.show();
}

void VideoPlayer::on_FastButton_clicked()
{
    changeSpeed(1);
}

void VideoPlayer::on_SlowButton_clicked()
{
    changeSpeed(0.5);
}

void VideoPlayer::on_VerySlowButton_clicked()
{
    changeSpeed(0.25);
}

void VideoPlayer::changeSpeed(qreal speed)
{
    player.setPlaybackRate(speed);
    if (speed==1)
        player.setMuted(false);
    else
        player.setMuted(true);
}

void VideoPlayer::TranslateSentence(QString sentence)
{
    CurrentSentence=sentence;
    Mirrored=ui->MirrorButton->isChecked();
    bool ok=dic.generatePlaylist(CurrentSentence,playList,Mirrored);
    if (!ok)
        return;
    player.setPlaylist(&playList);
    player.play();
}

void VideoPlayer::on_NormalButton_clicked()
{
    if (player.state()==QMediaPlayer::StoppedState || !Mirrored)
        return;
    Mirrored=false;
    JumpPlay();
}

void VideoPlayer::on_MirrorButton_clicked()
{
    if (player.state()==QMediaPlayer::StoppedState || Mirrored)
        return;
    Mirrored=true;
    JumpPlay();
}

void VideoPlayer::JumpPlay()
{
    int currIndex=playList.currentIndex();
    player.stop();
    dic.generatePlaylist(CurrentSentence,playList,Mirrored);
    playList.setCurrentIndex(currIndex);
    player.play();
}

void VideoPlayer::ReloadConfig()
{
    if (!(config->get("SPEED")=="NORMAL" || config->get("SPEED")=="SLOW" || config->get("SPEED")=="VERYSLOW"  ))
    {
        config->reportFileDamaged();
        ReloadConfig();
        return;
    }

    if (!(config->get("MIRRORED")=="TRUE" || config->get("MIRRORED")=="FALSE"))
    {
        config->reportFileDamaged();
        ReloadConfig();
        return;
    }
    dic.ReloadConfig();
    ResetVideoPlayer();
}
