#include "ui_themeeditor.h"
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include "include/Widgets/themeeditor.h"


ThemeEditor::ThemeEditor(QWidget *parent) :
        QWidget(parent), ui{new Ui::ThemeEditor}, m_currentTheme{}
{
    ui->setupUi(this);
    updateThemeDisplay();
}

ThemeEditor::~ThemeEditor()
{
    delete ui;
}

void ThemeEditor::updateThemeDisplay()
{
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

    ui->changeThemeURLBtn->setDisabled(m_currentTheme->URL().isEmpty());
    ui->saveBtn->setDisabled(m_currentTheme->saved());

}

void ThemeEditor::onThemeSelected(const std::shared_ptr<Theme> &theme)
{
    m_currentTheme = theme;
    updateThemeDisplay();
}

void ThemeEditor::onThemeClosed(const std::shared_ptr<Theme> &theme)
{
    if (m_currentTheme == nullptr) return;
    if (theme->uuid() != m_currentTheme->uuid()) return;
    m_currentTheme = nullptr;
    updateThemeDisplay();
}


void ThemeEditor::on_changeThemeNameBtn_clicked()
{
    if (m_currentTheme == nullptr) return;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Editer le nom"),
                                         tr("Nom du thème:"),
                                         QLineEdit::Normal,
                                         m_currentTheme->name(), &ok);
    if (!ok || text.isEmpty())
        return;

    if (m_currentTheme->name() == text)
        return;

    m_currentTheme->name() = text;
    ui->themeEditorTitle->setText(
            "Gestion du thème : " + m_currentTheme->name());
    updateTheme();
}


void ThemeEditor::on_changeThemeIconBtn_clicked()
{
    QString dirPath = m_currentTheme->iconPath();

    if (dirPath.isEmpty())
    {
        dirPath = QStandardPaths::PicturesLocation;
    } else
    {
        dirPath = QFileInfo(dirPath).absoluteDir().absolutePath();
    }

    QString fileName = QFileDialog::getOpenFileName(
            this, "Ouvrir un fichier",
            dirPath, "Fichiers png (*.png)");

    // TODO: info box?
    if (fileName.isEmpty())
        return;

    m_currentTheme->iconPath() = fileName;
    updateTheme();
}


void ThemeEditor::on_changeThemeURLBtn_clicked()
{

}


void ThemeEditor::on_addColorPairBtn_clicked()
{

}


void ThemeEditor::on_applyToFileBtn_clicked()
{
}


void ThemeEditor::on_saveBtn_clicked()
{
    if (m_currentTheme == Q_NULLPTR) return;
    ui->saveBtn->setDisabled(true);

    if (m_currentTheme->save(false, this))
        return;
    // Save not succeed
    ui->saveBtn->setDisabled(false);
}

void ThemeEditor::updateTheme()
{
    m_currentTheme->saved() = false;
    updateThemeDisplay();
    emitThemeUpdated(m_currentTheme);
}

