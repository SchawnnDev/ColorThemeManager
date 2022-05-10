#ifndef COLOR_THEME_MANAGER_THEME_H
#define COLOR_THEME_MANAGER_THEME_H


#include <set>
#include <QString>
#include <QWidget>
#include <QUuid>
#include "colorPair.h"

class Theme
{
private:
    QUuid m_uuid;
    QString m_name;
    QString m_iconPath;
    QString m_path; // Path or URL
    bool m_URL = false; // path is URL or not?
    std::set<ColorPair, CompareColorPair> m_colorPairs;
public:
    Theme();
    Theme(const QString& name, const QString& iconPath, const QString& path, bool URL);
    explicit Theme(const QString& themePath);
    ~Theme();
    void applyToFile(const QString &filePath);
    void save();

    // Getters and setters
    QUuid const& uuid() const { return m_uuid; };
    QUuid& uuid() { return m_uuid; };

    QString const& name() const { return m_name; };
    QString& name() { return m_name; };

    QString const& iconPath() const { return m_iconPath; };
    QString& iconPath() { return m_iconPath; };

    QString const& path() const { return m_path; };
    QString& path() { return m_path; };

    bool const& URL() const { return m_URL; };
    bool& URL() { return m_URL; };

    std::set<ColorPair, CompareColorPair> const& colorPairs() const { return m_colorPairs; };

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
