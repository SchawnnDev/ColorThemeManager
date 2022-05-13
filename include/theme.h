#ifndef COLOR_THEME_MANAGER_THEME_H
#define COLOR_THEME_MANAGER_THEME_H


#include <set>
#include <QString>
#include <QWidget>
#include <QUuid>
#include <memory>
#include "colorPair.h"

class Theme
{
private:
    QUuid m_uuid;
    QString m_name;
    QString m_iconPath;
    QString m_path; // Path
    QString m_URL;// if URL is empty => no URL
    bool m_saved = false;
    std::set<ColorPair, CompareColorPair> m_colorPairs;
public:
    Theme();
    Theme(const QString& name, const QString& iconPath, const QString& path, bool URL, bool alreadyExists);
    explicit Theme(const QString& themePath);
    ~Theme();
    void applyToFile(const QString &filePath);
    bool save(bool newPath, QWidget *parent);

    // Getters and setters
    QUuid const& uuid() const { return m_uuid; };
    QUuid& uuid() { return m_uuid; };

    QString const& name() const { return m_name; };
    QString& name() { return m_name; };

    QString const& iconPath() const { return m_iconPath; };
    QString& iconPath() { return m_iconPath; };

    QString const& path() const { return m_path; };
    QString& path() { return m_path; };

    QString const& URL() const { return m_URL; };
    QString& URL() { return m_URL; };

    bool const& saved() const { return m_saved; };
    bool& saved() { return m_saved; };

    std::set<ColorPair, CompareColorPair> const& colorPairs() const { return m_colorPairs; };

};

#endif //COLOR_THEME_MANAGER_THEME_H
