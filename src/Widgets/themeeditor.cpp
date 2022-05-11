#include "ui_themeeditor.h"
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
}

