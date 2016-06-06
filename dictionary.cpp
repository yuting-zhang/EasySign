#include "dictionary.h"
#include <set>
#include <QMessageBox>

Dictionary::Dictionary(ConfigData* data): config(data)
{
   ReloadConfig();
}

Dictionary::~Dictionary()
{
}

QString processSentence(QString sentence)
{
    static const std::set<QString> ChinesePunct={"$","￥","！","（","…","）","—","、","；","：",
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

bool Dictionary::generatePlaylist(QString sentence, QMediaPlaylist& PlayList, bool mirrored)
{
    long curr=0;
    PlayList.clear();
    sentence=processSentence(sentence);
    if (sentence.isEmpty())
        return false;
    while (curr!=sentence.size())
    {
        bool found=false;
        for (long it=sentence.size()-curr; it!=0; --it)
        {
            if (dic.find(sentence.mid(curr,it))!=dic.end())
            {
                if (dic[sentence.mid(curr,it)]!="0")
                {
                    if (!mirrored)
                        PlayList.addMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/data/video/"+dic[sentence.mid(curr,it)]+".avi"));
                    else
                        PlayList.addMedia(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/data/video/"+dic[sentence.mid(curr,it)]+"~1.avi"));
                }
                curr+=it;
                found=true;
                break;
            }
        }
        if (!found)
        {
            QMessageBox errorBox;
            errorBox.setText("对不起！\""+sentence.mid(curr,1)+"\"并未被收录！");
            errorBox.exec();
            return false;
        }
    }
    PlayList.setCurrentIndex(0);
    return true;
}


void Dictionary::ReloadConfig()
{
    if (!(config->get("DICTIONARY")=="CHINA" || config->get("DICTIONARY")=="ZHENJIANG"))
    {
        config->reportFileDamaged();
        ReloadConfig();
        return;
    }
    ResetDictionary();
}

void Dictionary::ResetDictionary()
{
    dic.clear();
    if (config->get("DICTIONARY")=="ZHENJIANG")
    {
        QFile fin(QCoreApplication::applicationDirPath()+"/data/video/Zhenjiang.es");
        fin.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fin);
        QString word, address;
        while (!in.atEnd())
        {
            in>>word>>address;
            dic[word]=address;
        }
    }

    // set the rest the same as China
    QFile fin(QCoreApplication::applicationDirPath()+"/data/video/dic.es");
    fin.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fin);
    QString word, address;
    while (!in.atEnd())
    {
        in>>word>>address;
        if (dic.find(word)==dic.end())
            dic[word]=address;
    }
}
