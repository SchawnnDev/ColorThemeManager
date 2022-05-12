#include "ui_themeeditor.h"
#include <QInputDialog>
#include <QDir>
#include "include/Widgets/themeeditor.h"


ThemeEditor::ThemeEditor(QWidget *parent) :
        QWidget(parent), ui{new Ui::ThemeEditor}, m_currentTheme{}
{
    ui->setupUi(this);
    switchThemeDisplay();
}

ThemeEditor::~ThemeEditor()
{
    delete ui;
}

void ThemeEditor::switchThemeDisplay()
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

    ui->changeThemeURLBtn->setDisabled(!m_currentTheme->URL());
    ui->saveBtn->setDisabled(m_currentTheme->saved());

}

void ThemeEditor::onThemeSelected(const std::shared_ptr<Theme> &theme)
{
    m_currentTheme = theme;
    switchThemeDisplay();
}

void ThemeEditor::onThemeClosed(const std::shared_ptr<Theme> &theme)
{
    if (m_currentTheme == nullptr) return;
    if (theme->uuid() != m_currentTheme->uuid()) return;
    m_currentTheme = nullptr;
    switchThemeDisplay();
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

    if(m_currentTheme->name() == text)
        return;

    m_currentTheme->name() = text;
    ui->themeEditorTitle->setText(
            "Gestion du thème : " + m_currentTheme->name());
    updateTheme();
}


void ThemeEditor::on_changeThemeIconBtn_clicked()
{

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

}

void ThemeEditor::updateTheme()
{
    m_currentTheme->saved() = false;
    emitThemeUpdated(m_currentTheme);
}

