#include "ui_mainwindow.h"
#include "../../include/Widgets/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{}

MainWindow::~MainWindow()
{
	delete ui;
}
