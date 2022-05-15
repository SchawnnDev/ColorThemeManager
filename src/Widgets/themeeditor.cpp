#include "ui_themeeditor.h"
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include "include/Widgets/themeeditor.h"
#include "include/Widgets/colorpairitem.h"
#include "include/xmlReader.h"
#include "include/utils.h"
#include <QDebug>
#include <QMessageBox>

ThemeEditor::ThemeEditor(QWidget *parent) :
        QWidget(parent), ui{new Ui::ThemeEditor}, m_currentTheme{} {
    ui->setupUi(this);
    updateThemeDisplay();
}

ThemeEditor::~ThemeEditor() {
    delete ui;
}

void ThemeEditor::updateThemeDisplay() {
    bool display = m_currentTheme != nullptr;
    ui->actionsGroupBox->setVisible(display);
    ui->colorPairList->setVisible(display);
    ui->themeEditorTitle->setVisible(display);
    //
    ui->noProjectLabel->setVisible(!display);

    if (!display) return;
    // display => set new infos
    ui->themeEditorTitle->setText(
            "Gestion du thème : " + m_currentTheme->name());

    ui->saveBtn->setDisabled(m_currentTheme->saved());
}

void ThemeEditor::onThemeSelected(const std::shared_ptr<Theme> &theme) {
    m_currentTheme = theme;

    const int count = ui->colorPairList->count();

    for (int i = 0; i < count; ++i) {
        auto item = ui->colorPairList->item(0);
        delete ui->colorPairList->takeItem(ui->colorPairList->row(item));
    }

            foreach(const std::shared_ptr<ColorPair> &colorPair,
                    theme->colorPairs()) {
            addColorPairItem(colorPair);
        }

    updateThemeDisplay();
}

void ThemeEditor::onThemeClosed(const std::shared_ptr<Theme> &theme) {
    if (m_currentTheme == nullptr) return;
    if (theme->uuid() != m_currentTheme->uuid()) return;
    m_currentTheme = nullptr;
    updateThemeDisplay();
}


void ThemeEditor::on_changeThemeNameBtn_clicked() {
    if (m_currentTheme == nullptr) return;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Editer le nom"),
                                         tr("Nom du thème:"),
                                         QLineEdit::Normal,
                                         m_currentTheme->name(), &ok);
    if (!ok) return;

    if (text.isEmpty() || text.length() > 32) {
        Utils::displayError(tr("Le nouveau nom du thème n'est pas valide"), this);
        return;
    }

    if (m_currentTheme->name() == text)
        return;

    m_currentTheme->name() = text;
    ui->themeEditorTitle->setText(
            "Gestion du thème : " + m_currentTheme->name());
    updateTheme();
}

void ThemeEditor::on_changeThemeIconBtn_clicked() {
    QString dirPath = m_currentTheme->iconPath();

    if (dirPath.isEmpty()) {
        dirPath = QStandardPaths::PicturesLocation;
    } else {
        dirPath = QFileInfo(dirPath).absoluteDir().absolutePath();
    }

    QString fileName = QFileDialog::getOpenFileName(
            this, "Ouvrir un fichier",
            dirPath, "Fichiers png (*.png)");

    if (fileName.isEmpty())
        return;

    m_currentTheme->iconPath() = fileName;
    updateTheme();
}

void ThemeEditor::on_addColorPairBtn_clicked() {
    auto colorPair = std::make_shared<ColorPair>();
    colorPair->name() = "Nouvelle couleur";
    colorPair->sourceColor() = QColor(0, 0, 0, 255);
    colorPair->targetColor() = QColor(0, 0, 0, 255);

    m_currentTheme->colorPairs().push_front(colorPair);

    addColorPairItem(colorPair);
    updateTheme();

    ui->colorPairList->scrollToBottom();
}

void ThemeEditor::on_importColorPairsURLBtn_clicked() {
    if (m_currentTheme == nullptr) return;
    bool ok;
    QString url = QInputDialog::getText(this, tr("Importer des paires de couleur par URL"),
                                        tr("URL:"),
                                        QLineEdit::Normal,
                                        m_currentTheme->URL(), &ok);
    if (!ok)
        return;

    QUrl xmlUrl(url);

    if (!xmlUrl.isValid()) {
        Utils::displayError(tr("L'URL n'est pas valide"), this);
        return;
    }

    emit emitStatusBarUpdate(tr("Démarrage du téléchargement de ") + url);

    m_currentTheme->URL() = url;

    delete m_fileDownloader;

    m_fileDownloader = new FileDownloader(xmlUrl, this);
    connect(m_fileDownloader, SIGNAL (downloaded()), this, SLOT (onURLDownloaded()));
}

void ThemeEditor::addColorPairItem(const std::shared_ptr<ColorPair> &colorPair) {
    auto widget = ui->colorPairList;
    auto item = new QListWidgetItem(widget);
    auto themeItem = new ColorPairItem(colorPair, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);
    item->setSelected(true);

    connect(themeItem, SIGNAL(emitColorPairUpdated()),
            this, SLOT(updateTheme()));

    connect(themeItem,
            SIGNAL(emitColorPairRemoved(const std::shared_ptr<ColorPair> &)),
            this,
            SLOT(onColorPairRemoved(const std::shared_ptr<ColorPair> &)));
}

void ThemeEditor::on_applyToFileBtn_clicked() {
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Ouvrir un fichier a convertir"),
            (QString) QStandardPaths::DocumentsLocation);

    if (fileName.isEmpty())
        return;

    emit emitStatusBarUpdate(tr("Application du thème au fichier..."));

    QFile file(fileName);

    if (!file.exists()) {
        Utils::displayError(tr("Le fichier sélectionné n'existe pas"), this);
        return;
    }

    file.open(QIODevice::ReadWrite);
    QByteArray content = file.readAll();
    QString contentStr(content);

    int found = 0;

            foreach(const std::shared_ptr<ColorPair> &colorPair,
                    m_currentTheme->colorPairs()) {
            QString source = ColorPair::toRGBA(colorPair->sourceColor());
            QString target = ColorPair::toRGBA(colorPair->targetColor());
            found += contentStr.count(source, Qt::CaseInsensitive);
            contentStr.replace(source, target, Qt::CaseInsensitive);
        }

    file.seek(0);
    file.write(contentStr.toUtf8());
    file.close();

    QMessageBox::information(this, "Success!",
                             QString("Le thème a bien été appliqué au fichier " +
                                     fileName + ".\n%1 couleurs ont été remplacées.").arg(found));
    emit emitStatusBarUpdate(QString("%1 " + tr("couleurs ont été remplacées.")).arg(found));

}

void ThemeEditor::on_saveBtn_clicked() {
    if (m_currentTheme == Q_NULLPTR) return;
    ui->saveBtn->setDisabled(true);

    if (m_currentTheme->save(false, this))
        return;
    // Save not succeed
    ui->saveBtn->setDisabled(false);
}

void
ThemeEditor::onColorPairRemoved(const std::shared_ptr<ColorPair> &colorPair) {
    for (auto i = 0; i < ui->colorPairList->count(); ++i) {
        auto item = ui->colorPairList->item(i);
        auto themeItem = qobject_cast<ColorPairItem *>
                (ui->colorPairList->itemWidget(item));

        if (themeItem->colorPair()->id() != colorPair->id())
            continue;

        m_currentTheme->colorPairs().removeOne(themeItem->colorPair());
        delete ui->colorPairList->takeItem(ui->colorPairList->row(item));
        updateTheme();
        break;
    }
}

void ThemeEditor::updateTheme() {
    m_currentTheme->saved() = false;
    updateThemeDisplay();
    emitThemeUpdated(m_currentTheme);
}

void ThemeEditor::on_importColorPairsBtn_clicked() {
    QString dirPath = QFileInfo((QString)
                                        QStandardPaths::DocumentsLocation)
            .absoluteDir().absolutePath();

    QString fileName = QFileDialog::getOpenFileName(
            this, "Importer des paires de couleurs",
            dirPath, "Fichiers xml (*.xml)");

    if (fileName.isEmpty())
        return;

    emit emitStatusBarUpdate(tr("Démarrage de l'importation pour ")+ fileName);

    XMLReader::importFile(m_currentTheme, fileName);

    // Reload colorPairs
    onThemeSelected(m_currentTheme);

    emit emitStatusBarUpdate(tr("Importation terminée"));

    updateTheme();
}

void ThemeEditor::onURLDownloaded() {
    if (m_currentTheme == Q_NULLPTR) return;
    auto data = m_fileDownloader->downloadedData();

    emit emitStatusBarUpdate(tr("Téléchargement effectué."));

    if (data.isEmpty()) {
        Utils::displayError(tr("Les données XML téléchargées sont vides."), this);
        return;
    }

    QDomDocument doc;

    if (!doc.setContent(QString(data).trimmed())) {
        Utils::displayError(tr("Impossible de traiter le XML"), this);
        return;
    }

    emit emitStatusBarUpdate(tr("Traitement des éléments téléchargés."));

    XMLReader::import(m_currentTheme, doc);

    const int count = ui->colorPairList->count();

    for (int i = 0; i < count; ++i) {
        auto item = ui->colorPairList->item(0);
        delete ui->colorPairList->takeItem(ui->colorPairList->row(item));
    }

            foreach(const std::shared_ptr<ColorPair> &colorPair,
                    m_currentTheme->colorPairs()) {
            addColorPairItem(colorPair);
        }

    updateTheme();

    emit emitStatusBarUpdate(tr("Importation des elements téléchargés terminée"));
}
