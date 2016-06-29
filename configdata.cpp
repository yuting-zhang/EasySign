#include "configdata.h"
#include <QDir>
#include <algorithm>
#include <QDebug>
#include <QMessagebox>
ConfigData::ConfigData()
{
    QDir Dir(DOCUMENTDIR);
    QFile file(DOCUMENTDIR+"/config.ini");
    if (!Dir.exists() || !file.exists())
        initFile();
    readConfig();
}

void ConfigData::readConfig()
{
    QFile file(DOCUMENTDIR+"/config.ini");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fin(&file);
    QString val;
    while (!fin.atEnd())
    {
        val=fin.readLine();
        config.insert(parse(val));
    }
}

std::pair<QString,QString> ConfigData::parse(const QString& val) const
{
    auto pos=std::find(val.begin(),val.end(),'=');
    auto head=val.begin(),rear=pos;
    while ((*head)==' ')
        ++head;
    while ((*(rear-1)==' '))
        --rear;
    std::pair<QString,QString> ret;
    ret.first=val.mid(head-val.begin(),rear-head);
    head=pos+1;
    rear=val.end();
    while ((*head)==' ')
        ++head;
    while ((*(rear-1)==' '))
        --rear;
    ret.second=val.mid(head-val.begin(),rear-head);
    return ret;
}

void ConfigData::initFile()
{
    QDir Dir;
    Dir.mkpath(DOCUMENTDIR);
    QFile file(DOCUMENTDIR+"/config.ini");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out<< "DICTIONARY=CHINA\n"
       << "LEARN=\n"
       << "MIRRORED=FALSE\n"
       << "SPEED=NORMAL\n"
       << "VERSION=0.4.0\n";
}

void ConfigData::reportFileDamaged()
{
    initFile();
    config.clear();
    readConfig();
    QMessageBox errorBox;
    errorBox.setText("配置文档损坏！系统已经自动初始化配置文档！");
    errorBox.exec();
}

QString ConfigData::get(QString key)
{
    return config[key];
}

void ConfigData::put(QString key, QString val)
{
    config[key]=val;
    QFile file(DOCUMENTDIR+"/config.ini");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for (const auto& it: config)
        out<< it.first<<"="<<it.second<< "\n";
}
