#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QListWidgetItem>
#include "include/theme.h"
#include <QLabel>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

signals:
    void emitThemeSelected(const std::shared_ptr<Theme>& theme);
    void emitThemeClosed(const std::shared_ptr<Theme> &theme);

private slots:

    void on_actionImportFile_triggered();

    void on_actionCalculateFileTheme_triggered();

    void on_actionCreateTheme_triggered();

    void on_actionChargeRecentThemes_triggered();

    void on_actionSaveAllThemes_triggered();

    void onThemeClosed(const std::shared_ptr<Theme> &theme);

    void onStatusBarUpdate(const QString &message);

    void
    onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void onLanguageChanged(QAction *action);

    void createLanguageMenu();

    void on_actionQuitter_triggered();

private:
    Ui::MainWindow *ui;
    QTranslator m_translator;

    void addThemeItem(const std::shared_ptr<Theme> &theme);

    void dragEnterEvent(QDragEnterEvent *e) override;

    void dropEvent(QDropEvent *e) override;

    void changeEvent(QEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void loadLanguage(const QString &code);
};

#endif // MAINWINDOW_H
