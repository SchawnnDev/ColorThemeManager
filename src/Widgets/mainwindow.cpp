#include "ui_mainwindow.h"
#include "include/Widgets/mainwindow.h"
#include "include/Widgets/openthemeitem.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init signals
    connect(ui->openThemesList, SIGNAL(emitThemeClosed),
            this, SLOT(onThemeClosed));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImportFile_triggered()
{
    qDebug() << "Trigger";
    // test
    auto widget = ui->openThemesList;
    auto item = new QListWidgetItem(widget);
    Theme theme{};
    theme.iconPath() = "/mnt/c/Users/ipers/OneDrive/Images/braft.jpg";
    theme.name() = "Theme black/red";
    auto themeItem = new openThemeItem(theme, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);
    qDebug() << "setitemwidget";

    // Connect signals between themeItem and MainWindow
    connect(themeItem, SIGNAL(emitThemeClosed(Theme)),
            this, SLOT(onThemeClosed(Theme)));
}

void MainWindow::on_actionCalculateFileTheme_triggered()
{}

void MainWindow::on_actionChargeRecentThemes_triggered()
{}

void MainWindow::on_actionCreateTheme_triggered()
{}

void MainWindow::on_actionImportThemeURL_triggered()
{}

void MainWindow::on_actionSaveAllThemes_triggered()
{}

void MainWindow::onThemeClosed(const Theme &theme)
{
    qDebug() << "OnThemeClosed: " << theme.name();

    for (auto i = 0; i < ui->openThemesList->count(); ++i)
    {
        auto item = ui->openThemesList->item(i);
        auto themeItem = qobject_cast<openThemeItem *>
                (ui->openThemesList->itemWidget(item));

        qDebug() << "Comparing " << themeItem->theme().name() << " and "
                 << theme.name();

        if (themeItem->theme().uuid() != theme.uuid())
            continue;

        qDebug() << "Found item";

        delete ui->openThemesList->takeItem(ui->openThemesList->row(item));
    }
}



