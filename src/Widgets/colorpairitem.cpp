#include "ui_colorpairitem.h"
#include "include/Widgets/colorpairitem.h"
#include <QDebug>
#include <QStyleOptionButton>

ColorPairItem::ColorPairItem(const std::shared_ptr<ColorPair>& colorPair, QWidget *parent) :
        QWidget(parent), ui(new Ui::ColorPairItem), m_colorPair{colorPair}
{
    ui->setupUi(this);
    auto height = ui->sourceColorHex->height();
    ui->sourceColor->setFixedSize(height, height);
    ui->targetColor->setFixedSize(height, height);
    //
    updateColorPairDisplay(true);
}

ColorPairItem::~ColorPairItem()
{
    delete ui;
}

void ColorPairItem::updateColorPairDisplay(bool updateHexText)
{
    ui->colorPairId->setText(m_colorPair->id());
    //$
    auto sourceColor = m_colorPair->sourceColor();
    auto targetColor = m_colorPair->targetColor();
    //
    if(updateHexText)
    {
        ui->sourceColorHex->setText(ColorPair::toRGBA(sourceColor).toUpper());
        ui->targetColorHex->setText(ColorPair::toRGBA(targetColor).toUpper());
    }

    QString sourceColorCss = QString("background-color: %1").arg(sourceColor.name());
    ui->sourceColor->setStyleSheet(sourceColorCss);

    QString targetColorCss = QString("background-color: %1").arg(targetColor.name());
    ui->targetColor->setStyleSheet(targetColorCss);

    // set close btn size
    auto closeBtn = ui->closeBtn;
    auto textSize = closeBtn->fontMetrics().size(Qt::TextShowMnemonic,
                                                 closeBtn->text()) * 2;
    QStyleOptionButton opt;
    opt.initFrom(ui->closeBtn);
    opt.rect.setSize(textSize);
    closeBtn->setMaximumSize(
            closeBtn->style()->sizeFromContents(QStyle::CT_PushButton,
                                                &opt,
                                                textSize,
                                                closeBtn));

}

void ColorPairItem::updateColorPair()
{

}


void ColorPairItem::on_sourceColor_clicked()
{
    qDebug() << "on_sourceColor_clicked";
}


void ColorPairItem::on_targetColor_clicked()
{
    qDebug() << "on_targetColor_clicked";
}


void ColorPairItem::on_closeBtn_clicked()
{

}


void ColorPairItem::on_sourceColorHex_textEdited(const QString &newColor)
{
    m_colorPair->sourceColor() = ColorPair::fromRGBA(newColor);
    updateColorPairDisplay(false);
    updateColorPair();
}

void ColorPairItem::on_targetColorHex_textEdited(const QString &newColor)
{
    m_colorPair->targetColor() = ColorPair::fromRGBA(newColor);
    updateColorPairDisplay(false);
    updateColorPair();
}

