#include <QFileDialog>
#include <QStandardPaths>
#include "include/theme.h"
#include <QDebug>


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

        QDir dir;

        if (m_path.isEmpty())
        {
            dir = QDir((QString)QStandardPaths::DocumentsLocation);
        } else
        {
            dir = QFileInfo(m_path).absoluteDir();
        }

        QString fileName = QFileDialog::getSaveFileName(
                parent, "Sauvegarder le fichier",
                dir.filePath("new_theme.theme"),
                "Fichiers thèmes (*.theme)");

        // Cancel => save failed
        if (fileName.isEmpty())
            return false;

        if(!fileName.endsWith(".theme"))
            fileName += ".theme";

        QDir d = QFileInfo(fileName).absoluteDir();

        // TODO: Maybe add info box dir not exists
        if(!d.exists())
            return false;

        m_path = fileName;
    }

    QFile file(m_path);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_uuid << m_name << m_iconPath << m_URL;
    file.close();

    m_saved = true;

    return true;
}

Theme::~Theme()
{
}