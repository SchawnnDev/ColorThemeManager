#ifndef COLOR_THEME_MANAGER_OPENTHEMEITEM_H
#define COLOR_THEME_MANAGER_OPENTHEMEITEM_H

#include <QWidget>
#include "include/theme.h"


QT_BEGIN_NAMESPACE
namespace Ui { class openThemeItem; }
QT_END_NAMESPACE

class openThemeItem : public QWidget
{
Q_OBJECT

public:
    explicit openThemeItem(const Theme &theme, QWidget *parent = nullptr);

    ~openThemeItem() override;

    Theme const& theme() const { return m_theme; };
    Theme& theme() { return m_theme; };

signals:
    void emitThemeClosed(const Theme& theme);

private slots:
    void on_themeClose_clicked();

private:
    Ui::openThemeItem *ui;
    Theme m_theme;
};


#endif //COLOR_THEME_MANAGER_OPENTHEMEITEM_H
