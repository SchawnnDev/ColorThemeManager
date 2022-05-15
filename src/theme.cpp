#include <QFileDialog>
#include <QStandardPaths>
#include "include/theme.h"
#include "include/utils.h"
#include <QDebug>
#include <QSettings>


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
                dir.filePath(QString("%1.theme").arg(m_name)),
                "Fichiers thèmes (*.theme)");

        // Cancel => save failed
        if (fileName.isEmpty())
        {
            Utils::displayError(QWidget::tr("Le fichier sélectionné n'existe pas"), parent);
            return false;
        }

        if(!fileName.endsWith(".theme"))
            fileName += ".theme";

        QDir d = QFileInfo(fileName).absoluteDir();

        if(!d.exists())
        {
            Utils::displayError(QWidget::tr("Le dossier selectionné n'existe pas"), parent);
            return false;
        }

        m_path = fileName;
    }

    QFile file(m_path);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_uuid << m_name << m_iconPath << m_URL << m_colorPairs;
    file.close();

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    if(!files.contains(m_path))
    {
        files.insert(0, m_path);
    } else {
        files.removeOne(m_path);
        files.insert(0, m_path);
    }

    settings.setValue("recentFileList", files);

    m_saved = true;
    return true;
}

Theme::~Theme()
{
}
