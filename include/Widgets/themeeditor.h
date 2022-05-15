#ifndef COLOR_THEME_MANAGER_THEMEEDITOR_H
#define COLOR_THEME_MANAGER_THEMEEDITOR_H

#include <QWidget>
#include "include/theme.h"
#include "include/filedownloader.h"
#include <memory>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class ThemeEditor; }
QT_END_NAMESPACE

class ThemeEditor : public QWidget
{
Q_OBJECT

public:
    explicit ThemeEditor(QWidget *parent);

    ~ThemeEditor() override;

    void updateThemeDisplay();

private:
    Ui::ThemeEditor *ui;
    std::shared_ptr<Theme> m_currentTheme;
    FileDownloader* m_fileDownloader;

    void addColorPairItem(const std::shared_ptr<ColorPair> &colorPair);
    static void setButtonIcon(QPushButton *btn, const QString &path);

signals:
    void emitThemeUpdated(const std::shared_ptr<Theme> &theme);
    void emitStatusBarUpdate(const QString& message);

private slots:
    void onThemeSelected(const std::shared_ptr<Theme>& theme);
    void onThemeClosed(const std::shared_ptr<Theme> &theme);
    void on_changeThemeNameBtn_clicked();
    void on_changeThemeIconBtn_clicked();
    void on_addColorPairBtn_clicked();
    void on_applyToFileBtn_clicked();
    void on_saveBtn_clicked();
    void updateTheme();
    void onColorPairRemoved(const std::shared_ptr<ColorPair> &colorPair);
    void on_importColorPairsBtn_clicked();
    void on_importColorPairsURLBtn_clicked();
    void onURLDownloaded();

};


#endif //COLOR_THEME_MANAGER_THEMEEDITOR_H
