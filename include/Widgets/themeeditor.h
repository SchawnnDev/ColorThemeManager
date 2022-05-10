#ifndef COLOR_THEME_MANAGER_THEMEEDITOR_H
#define COLOR_THEME_MANAGER_THEMEEDITOR_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ThemeEditor; }
QT_END_NAMESPACE

class ThemeEditor : public QWidget
{
Q_OBJECT

public:
    explicit ThemeEditor(QWidget *parent = nullptr);

    ~ThemeEditor() override;

private:
    Ui::ThemeEditor *ui;
};


#endif //COLOR_THEME_MANAGER_THEMEEDITOR_H
