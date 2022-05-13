#ifndef COLOR_THEME_MANAGER_XMLREADER_H
#define COLOR_THEME_MANAGER_XMLREADER_H

#include <QtXml>
#include <set>
#include <QFile>
#include "colorPair.h"
#include "theme.h"

class XMLReader {
public:
    static void import(const std::shared_ptr<Theme>& theme, const QString &path);
};

#endif //COLOR_THEME_MANAGER_XMLREADER_H
