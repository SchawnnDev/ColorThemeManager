//
// Created by Paul on 24/02/2022.
//

#ifndef COLOR_THEME_MANAGER_XMLREADER_H
#define COLOR_THEME_MANAGER_XMLREADER_H

#include <QtXml>
#include "colorPair.h"

class XMLReader {
private:
    set<ColorPair> colorPairs;
public:
    void read(const QFile& file);

};

#endif //COLOR_THEME_MANAGER_XMLREADER_H
