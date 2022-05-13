#ifndef COLOR_THEME_MANAGER_COLORPAIRITEM_H
#define COLOR_THEME_MANAGER_COLORPAIRITEM_H

#include <QWidget>
#include <memory>
#include <QGraphicsScene>
#include "include/colorPair.h"
#include "include/theme.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ColorPairItem; }
QT_END_NAMESPACE

class ColorPairItem : public QWidget
{
Q_OBJECT

public:
    explicit ColorPairItem(const std::shared_ptr<ColorPair>& colorPair, QWidget *parent = nullptr);

    ~ColorPairItem() override;

    std::shared_ptr<ColorPair> const& colorPair() const { return m_colorPair; }

private slots:
    void on_sourceColor_clicked();

    void on_targetColor_clicked();

    void on_closeBtn_clicked();

    void on_sourceColorHex_textEdited(const QString &newColor);

    void on_targetColorHex_textEdited(const QString &newColor);

    void on_colorPairName_textEdited(const QString &newName);

signals:
    void emitColorPairUpdated();
    void emitColorPairRemoved(const std::shared_ptr<ColorPair>& colorPair);

private:
    Ui::ColorPairItem *ui;
    std::shared_ptr<ColorPair> m_colorPair;

    void updateColorPairDisplay(bool updateHexText);
    void updateColorPair();
};


#endif //COLOR_THEME_MANAGER_COLORPAIRITEM_H
