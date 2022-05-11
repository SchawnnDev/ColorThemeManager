#include "include/theme.h"


Theme::Theme()
{
    this->m_uuid = QUuid::createUuid();
}

Theme::Theme(const QString &name, const QString &iconPath, const QString &path,
             bool URL) : m_name{name}, m_iconPath{iconPath}, m_path{path},
             m_URL{URL}
{
}

Theme::Theme(const QString &themePath)
{
}

void Theme::applyToFile(const QString &filePath)
{

}

void Theme::save()
{

}

Theme::~Theme()
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
