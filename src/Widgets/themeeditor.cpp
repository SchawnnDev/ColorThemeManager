#include "ui_themeeditor.h"
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include "include/Widgets/themeeditor.h"
#include "include/Widgets/colorpairitem.h"


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
    auto widget = ui->colorPairList;
    auto item = new QListWidgetItem(widget);
    auto colorPair = std::make_shared<ColorPair>();
    colorPair->id() = "#1";
    colorPair->sourceColor() = QColor(0, 0, 0);
    colorPair->targetColor() = QColor(0, 0, 0);
    m_currentTheme->colorPairs().insert(colorPair);
    auto themeItem = new ColorPairItem(colorPair, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);

    connect(themeItem, SIGNAL(emitColorPairUpdated()),
            this, SLOT(updateTheme()));

    connect(themeItem,
            SIGNAL(emitColorPairRemoved(const std::shared_ptr<ColorPair> &)),
            this,
            SLOT(onColorPairRemoved(const std::shared_ptr<ColorPair> &)));

    updateTheme();
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

void
ThemeEditor::onColorPairRemoved(const std::shared_ptr<ColorPair> &colorPair)
{
    for (auto i = 0; i < ui->colorPairList->count(); ++i)
    {
        auto item = ui->colorPairList->item(i);
        auto themeItem = qobject_cast<ColorPairItem *>
                (ui->colorPairList->itemWidget(item));

        if (themeItem->colorPair()->id() != colorPair->id())
            continue;

        m_currentTheme->colorPairs().remove(themeItem->colorPair());
        delete ui->colorPairList->takeItem(ui->colorPairList->row(item));
        updateTheme();
        break;
    }
}

void ThemeEditor::updateTheme()
{
    m_currentTheme->saved() = false;
    updateThemeDisplay();
    emitThemeUpdated(m_currentTheme);
}



void ThemeEditor::on_importColorPairsBtn_clicked()
{

}

