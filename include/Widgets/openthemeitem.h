#ifndef COLOR_THEME_MANAGER_OPENTHEMEITEM_H
#define COLOR_THEME_MANAGER_OPENTHEMEITEM_H

#include <QWidget>
#include "include/theme.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class openThemeItem; }
QT_END_NAMESPACE

class openThemeItem : public QWidget
{
Q_OBJECT

public:
    explicit openThemeItem(const std::shared_ptr<Theme>& theme, QWidget *parent = nullptr);

    ~openThemeItem() override;

    std::shared_ptr<Theme> theme() { return m_theme; };

signals:
    void emitThemeClosed(std::shared_ptr<Theme> theme);

private slots:
    void on_themeClose_clicked();
    void onThemeUpdated(const std::shared_ptr<Theme> &theme);

private:
    Ui::openThemeItem *ui;
    std::shared_ptr<Theme> m_theme;

    void updateThemeElement();
};


#endif //COLOR_THEME_MANAGER_OPENTHEMEITEM_H
