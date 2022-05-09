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
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

private slots:
    void on_actionImportFile_triggered();
    void on_actionCalculateFileTheme_triggered();
    void on_actionCreateTheme_triggered();
    void on_actionImportThemeURL_triggered();
    void on_actionChargeRecentThemes_triggered();
    void on_actionSaveAllThemes_triggered();

    void onThemeClosed(const Theme& theme);

private:
	Ui::MainWindow *ui;
    Theme currentTheme;
};
#endif // MAINWINDOW_H
