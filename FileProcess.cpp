#include <QStandardPaths>
#include "FileProcess.h"
#include <QDir>
#include <QtWidgets>
#include <QString>

const QString loc(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/EasySign");

void FileProcess()
{
    if (firstUse())
    {
        createUserData();
    }
    else
        return;

}

bool firstUse()
{
    QDir Dir(loc);
    if (Dir.exists())
        return false;
    else
        return true;
}

void createUserData()
{
    QDir Dir;
    Dir.mkpath(loc);
}

void addExtension(long maxNum)
{
    QDir Dir;
    QString loc=QCoreApplication::applicationDirPath()+"/data/video/";
    for (int i=1;i!=maxNum;++i)
    {
        Dir.rename(loc+QString::number(i),loc+QString::number(i)+".avi");
        Dir.rename(loc+QString::number(i)+"~1",loc+QString::number(i)+"~1.avi");
    }
}

void cutExtension(long maxNum)
{
    QDir Dir;
    QString loc=QCoreApplication::applicationDirPath()+"/data/video/";
    for (int i=1;i!=maxNum;++i)
    {
        Dir.rename(loc+QString::number(i)+".avi",loc+QString::number(i));
        Dir.rename(loc+QString::number(i)+"~1.avi",loc+QString::number(i)+"~1");
    }
}
