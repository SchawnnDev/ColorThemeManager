#include "include/theme.h"


Theme::Theme(const QString& name, const QString& iconPath, const QString& path, bool URL)
{
    this->name = name;
    this->iconPath = iconPath;
    this->path = path;
    this->URL = URL;
}

Theme::Theme(const QString& themePath)
{

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
