#include "ui_themeeditor.h"
#include "include/Widgets/themeeditor.h"


ThemeEditor::ThemeEditor(QWidget *parent) :
        QWidget(parent), ui(new Ui::ThemeEditor)
{
    ui->setupUi(this);
}

ThemeEditor::~ThemeEditor()
{
    delete ui;
}

