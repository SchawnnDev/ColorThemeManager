#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/theme.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
    void on_actionImportFile_triggered();
    void on_actionCalculateFileTheme_triggered();
    void on_actionCreateTheme_triggered();
    void on_actionImportThemeURL_triggered();
    void on_actionChargeRecentThemes_triggered();
    void on_actionSaveAllThemes_triggered();

private:
	Ui::MainWindow *ui;
    Themes themes;
};
#endif // MAINWINDOW_H
