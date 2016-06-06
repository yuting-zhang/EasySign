#include <fstream>
using std::ifstream;
using std::ofstream;

#include <map>
using std::map;

#include <set>
using std::set;

#include <vector>
using std::vector;

#include <QTextStream>
#include <QMediaPlaylist>
#include "mainwindow.h"
#include <QMainWindow>
#include <QtGui/QMovie>
#include <QtWidgets/QWidget>
#include <QtWidgets>

map<QString,long> generateDic()
{
    QFile fin(QCoreApplication::applicationDirPath()+"/data/video/dic.es");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    map<QString,long> dic;
    QString word;
    long val;
    while (!in.atEnd())
    {
        in>>word>>val;
        dic[word]=val;
    }
    return dic;
}

QString processSentence(QString sentence)
{
    static const set<QString>ChinesePunct={"$","￥","！","（","…","）","—","、","；","：",
                                           "“","‘","？","，","。","《","》","·","\n"," "};
    QString processed;
    for (auto ch: sentence)
        if (!ch.isPunct()&& ChinesePunct.find(ch)==ChinesePunct.end())
        {
            if (ch.isLetter())
                processed+=ch.toLower();
            else
                processed+=ch;
        }
    return processed;
}

bool MakeList(QString sentence,map<QString,long>& dic, QMediaPlaylist& PlayList, bool mirror)
{
    long curr=0;
    PlayList.clear();
    sentence=processSentence(sentence);
    while (curr!=sentence.size())
    {
        bool found=false;
        for (long it=sentence.size()-curr; it!=0; --it)
        {
            if (dic.find(sentence.mid(curr,it))!=dic.end())
            {
                if (!mirror)
                    PlayList.addMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()
                        +"/data/video/"+QString::number(dic[sentence.mid(curr,it)])+".avi"));
                else
                    PlayList.addMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()
                        +"/data/video/"+QString::number(dic[sentence.mid(curr,it)])+"~1.avi"));
                curr+=it;
                found=true;
                break;
            }
        }
        if (!found)
        {
            QMessageBox errorBox;
            errorBox.setText("对不起，您的输入中有未收入单词，请输入已经学习过的单词。");
            errorBox.exec();
            return false;
        }
    }
    return true;
}

vector<vector<QString>> generateBook()
{
    //book number
    const int bookNo=3;
    const vector<QString> bookName={"Unit1.es","Unit2.es","Unit3.es"};
    vector<vector<QString>> book;
    for (int i=0;i!=bookNo;++i)
    {
        book.push_back(vector<QString>());
        QFile fin(QCoreApplication::applicationDirPath()+"/data/units/"+bookName[i]);
        fin.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fin);
        QString sentence;
        while (!in.atEnd())
        {
            in>>sentence;
            book[i].push_back(sentence);
        }
    }
    return book;
}
