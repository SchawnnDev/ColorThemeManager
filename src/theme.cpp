#include <QFileDialog>
#include <QStandardPaths>
#include "include/theme.h"


Theme::Theme()
{
    this->m_uuid = QUuid::createUuid();
    this->m_saved = false;
}

Theme::Theme(const QString &name, const QString &iconPath, const QString &path,
             bool URL, bool alreadyExists) : m_name{name}, m_iconPath{iconPath},
                                             m_path{path},
                                             m_URL{URL}, m_saved{alreadyExists}
{
}

Theme::Theme(const QString &themePath)
{
}

void Theme::applyToFile(const QString &filePath)
{

}

bool Theme::save(bool newPath, QWidget *parent = Q_NULLPTR)
{
    if (m_path.isEmpty() || newPath)
    {

        QString dirPath;

        if (m_path.isEmpty())
        {
            dirPath = QStandardPaths::DocumentsLocation;
        } else
        {
            QDir d = QFileInfo(m_path).absoluteDir();
            dirPath = d.absolutePath();
        }

        QString fileName = QFileDialog::getSaveFileName(
                parent, "Sauvegarder le fichier", dirPath,
                "Fichiers thèmes (*.theme)");

        // Cancel => save failed
        if (fileName.isEmpty())
            return false;
    }

    //TODO: Save theme

    return true;
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
