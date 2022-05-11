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

    void switchThemeDisplay();

private:
    Ui::ThemeEditor *ui;
    std::shared_ptr<Theme> m_currentTheme;
};


#endif //COLOR_THEME_MANAGER_THEMEEDITOR_H
