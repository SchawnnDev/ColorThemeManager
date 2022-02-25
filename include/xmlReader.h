//
// Created by Paul on 24/02/2022.
//

#ifndef COLOR_THEME_MANAGER_XMLREADER_H
#define COLOR_THEME_MANAGER_XMLREADER_H

#include <QtXml>
#include <set>
#include <QFile>
#include "colorPair.h"

class XMLReader {
private:
    set<ColorPair, CompareColorPair> colorPairs;
public:
    void read(const QString &path);
    void display();

};

#endif //COLOR_THEME_MANAGER_XMLREADER_H
