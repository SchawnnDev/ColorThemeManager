#include "include/theme.h"


Theme::Theme(const QString& name, const QString& iconPath, const QString& path, bool URL)
{
    this->m_name = name;
    this->m_iconPath = iconPath;
    this->m_path = path;
    this->m_URL = URL;
    this->m_uuid = QUuid::createUuid();
}

Theme::Theme(const QString& themePath)
{
    this->m_uuid = QUuid::createUuid();
}

void Theme::applyToFile(const QString &filePath)
{

}

void Theme::save()
{

}

Themes::Themes()
{

}

void Themes::addTheme(const Theme &theme)
{

}

void Themes::loadAddTheme(const QString &path)
{

}

bool Themes::themeExists(const Theme &theme)
{
    return false;
}
