#ifndef COLOR_THEME_MANAGER_THEMEEDITOR_H
#define COLOR_THEME_MANAGER_THEMEEDITOR_H

#include <QWidget>
#include "include/theme.h"
#include <memory>

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

signals:
    void emitThemeUpdated(const std::shared_ptr<Theme> &theme);

private slots:
    void onThemeSelected(const std::shared_ptr<Theme>& theme);
    void onThemeClosed(const std::shared_ptr<Theme> &theme);
    void on_changeThemeNameBtn_clicked();
    void on_changeThemeIconBtn_clicked();
    void on_changeThemeURLBtn_clicked();
    void on_addColorPairBtn_clicked();
    void on_applyToFileBtn_clicked();
    void on_saveBtn_clicked();

    void updateTheme();
};


#endif //COLOR_THEME_MANAGER_THEMEEDITOR_H
