#ifndef COLOR_THEME_MANAGER_THEME_H
#define COLOR_THEME_MANAGER_THEME_H


#include <set>
#include <QString>
#include "colorPair.h"

class Theme
{
private:
    QString name;
    QString iconPath;
    QString path; // Path or URL
    bool URL = false; // path is URL or not?
    std::set<ColorPair, CompareColorPair> colorPairs;
public:
    Theme() = default;
    Theme(const QString& name, const QString& iconPath, const QString& path, bool URL);
    Theme(const QString& themePath);

    void applyToFile(const QString &filePath);
    void save();


};

class Themes
{
private:
    std::set<Theme> openThemes;
public:
    Themes();

    void addTheme(const Theme &theme);
    void loadAddTheme(const QString& path);
    bool themeExists(const Theme &theme);
};

#endif //COLOR_THEME_MANAGER_THEME_H
