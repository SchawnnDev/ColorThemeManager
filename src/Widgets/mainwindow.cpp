#include "ui_mainwindow.h"
#include "include/Widgets/mainwindow.h"
#include "include/Widgets/openthemeitem.h"

#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/favicon.ico"));

    connect(ui->openThemesList,
            SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem * )),
            this,
            SLOT(onCurrentItemChanged(QListWidgetItem * , QListWidgetItem * )));

    connect(this,
            SIGNAL(emitThemeSelected(const std::shared_ptr<Theme>&)),
            ui->themeEditor,
            SLOT(onThemeSelected(const std::shared_ptr<Theme>&)));

    connect(this,
            SIGNAL(emitThemeClosed(const std::shared_ptr<Theme>&)),
            ui->themeEditor,
            SLOT(onThemeClosed(const std::shared_ptr<Theme>&)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImportFile_triggered()
{

    QDir dir = QDir((QString)QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getOpenFileName(
            this, "Importer un thème",
            dir.filePath("theme.theme"),
            "Fichiers thème (*.theme)");

    // TODO: info box?
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    // TODO: info box?
    if (!file.exists())
        return;

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    auto theme = std::make_shared<Theme>();
    in >> theme->uuid() >> theme->name() >> theme->iconPath() >> theme->URL() >> theme->colorPairs();
    // Close file
    file.close();

    theme->saved() = true;
    theme->path() = fileName;

    auto widget = ui->openThemesList;
    auto item = new QListWidgetItem(widget);
    auto themeItem = new openThemeItem(theme, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);

    // Connect signals between themeItem and MainWindow
    connect(themeItem, SIGNAL(emitThemeClosed(std::shared_ptr<Theme>)),
            this, SLOT(onThemeClosed(std::shared_ptr<Theme>)));

    connect(ui->themeEditor,
            SIGNAL(emitThemeUpdated(const std::shared_ptr<Theme>&)),
            themeItem,
            SLOT(onThemeUpdated(const std::shared_ptr<Theme>&)));

    widget->setCurrentItem(item);
}

void MainWindow::on_actionCalculateFileTheme_triggered()
{}

void MainWindow::on_actionChargeRecentThemes_triggered()
{}

void MainWindow::on_actionCreateTheme_triggered()
{
    // test
    auto widget = ui->openThemesList;
    auto item = new QListWidgetItem(widget);
    auto theme = std::make_shared<Theme>();
    theme->iconPath() = ":/img/new.png";
    theme->name() = "Nouveau thème";
    auto themeItem = new openThemeItem(theme, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);

    // Connect signals between themeItem and MainWindow
    connect(themeItem, SIGNAL(emitThemeClosed(std::shared_ptr<Theme>)),
            this, SLOT(onThemeClosed(std::shared_ptr<Theme>)));

    connect(ui->themeEditor,
            SIGNAL(emitThemeUpdated(const std::shared_ptr<Theme>&)),
            themeItem,
            SLOT(onThemeUpdated(const std::shared_ptr<Theme>&)));

    widget->setCurrentItem(item);
}

void MainWindow::on_actionImportThemeURL_triggered()
{}

void MainWindow::on_actionSaveAllThemes_triggered()
{}

void MainWindow::onThemeClosed(const std::shared_ptr<Theme> &theme)
{
    qDebug() << "OnThemeClosed: " << theme->name();

    for (auto i = 0; i < ui->openThemesList->count(); ++i)
    {
        auto item = ui->openThemesList->item(i);
        auto themeItem = qobject_cast<openThemeItem *>
                (ui->openThemesList->itemWidget(item));

        if (themeItem->theme()->uuid() != theme->uuid())
            continue;

        emitThemeClosed(themeItem->theme());
        delete ui->openThemesList->takeItem(ui->openThemesList->row(item));
        break;
    }
}

void MainWindow::onCurrentItemChanged(QListWidgetItem *current,
                                      QListWidgetItem *previous)
{
    if (current == nullptr) return;
    auto themeItem = qobject_cast<openThemeItem *>
            (ui->openThemesList->itemWidget(current));

    if (themeItem == nullptr) return;

    emitThemeSelected(themeItem->theme());

    qDebug() << "New item selected: " << themeItem->theme()->uuid();
}
