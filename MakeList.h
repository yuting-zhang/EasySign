#ifndef MAKELIST_H
#define MAKELIST_H

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

map<QString,long> generateDic();

QString processSentence(QString sentence);

bool MakeList(QString sentence,map<QString,long>& dic, QMediaPlaylist& PlayList, bool mirror);

vector<vector<QString>> generateBook();

#endif // MAKELIST_H
