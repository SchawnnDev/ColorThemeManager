#include "ui_mainwindow.h"
#include "include/Widgets/mainwindow.h"
#include "include/Widgets/openthemeitem.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openThemesList,
            SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this,
            SLOT(onCurrentItemChanged(QListWidgetItem*, QListWidgetItem*)));

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
    auto theme = std::make_shared<Theme>();
    theme->iconPath() = "/mnt/c/Users/ipers/OneDrive/Images/braft.jpg";
    theme->name() = "Theme black/red";
    auto themeItem = new openThemeItem(theme, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);
    qDebug() << "Create theme with uuid " << theme->uuid().toString();

    // Connect signals between themeItem and MainWindow
    connect(themeItem, SIGNAL(emitThemeClosed(std::shared_ptr<Theme>)),
            this, SLOT(onThemeClosed(std::shared_ptr<Theme>)));
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

        qDebug() << "Deleting item " << theme->uuid().toString();

        delete ui->openThemesList->takeItem(ui->openThemesList->row(item));
    }
}

void MainWindow::onCurrentItemChanged(QListWidgetItem *current,
                                      QListWidgetItem *previous)
{
    if (current == nullptr) return;
    auto themeItem = qobject_cast<openThemeItem *>
            (ui->openThemesList->itemWidget(current));

    if (themeItem == nullptr) return;

    m_currentTheme = themeItem->theme();

    qDebug() << "New item selected: " << themeItem->theme()->uuid();
}
