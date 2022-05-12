#ifndef COLOR_THEME_MANAGER_COLORPAIRITEM_H
#define COLOR_THEME_MANAGER_COLORPAIRITEM_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class ColorPairItem; }
QT_END_NAMESPACE

class ColorPairItem : public QWidget
{
Q_OBJECT

public:
    explicit ColorPairItem(QWidget *parent = nullptr);

    ~ColorPairItem() override;

private:
    Ui::ColorPairItem *ui;
};


#endif //COLOR_THEME_MANAGER_COLORPAIRITEM_H
