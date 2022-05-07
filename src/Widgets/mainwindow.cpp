#include "ui_mainwindow.h"
#include "include/Widgets/mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionImportFile_triggered()
{
    qDebug() << "Trigger";
}

void MainWindow::on_actionCalculateFileTheme_triggered()
{

}

void MainWindow::on_actionChargeRecentThemes_triggered()
{

}

void MainWindow::on_actionCreateTheme_triggered()
{}

void MainWindow::on_actionImportThemeURL_triggered()
{}

void MainWindow::on_actionSaveAllThemes_triggered()
{

}