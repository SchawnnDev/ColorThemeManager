#include "ui_colorpairitem.h"
#include "include/Widgets/colorpairitem.h"
#include <QDebug>
#include <QStyleOptionButton>
#include <QColorDialog>
#include <QMessageBox>

ColorPairItem::ColorPairItem(const std::shared_ptr<ColorPair> &colorPair,
                             QWidget *parent) :
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
    ui->colorPairName->setText(m_colorPair->name());
    //$
    auto sourceColor = m_colorPair->sourceColor();
    auto targetColor = m_colorPair->targetColor();
    //
    if (updateHexText)
    {
        ui->sourceColorHex->setText(ColorPair::toRGBA(sourceColor).toUpper());
        ui->targetColorHex->setText(ColorPair::toRGBA(targetColor).toUpper());
    }

    QString sourceColorCss = QString("background-color: %1").arg(
            sourceColor.name());
    ui->sourceColor->setStyleSheet(sourceColorCss);

    QString targetColorCss = QString("background-color: %1").arg(
            targetColor.name());
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
    emit emitColorPairUpdated();
}


void ColorPairItem::on_sourceColor_clicked()
{
    QColor color = QColorDialog::getColor(m_colorPair->sourceColor(), this);
    if(!color.isValid()) return;
    m_colorPair->sourceColor() = color;
    updateColorPairDisplay(true);
    updateColorPair();
}


void ColorPairItem::on_targetColor_clicked()
{
    QColor color = QColorDialog::getColor(m_colorPair->targetColor(), this);
    if(!color.isValid()) return;
    m_colorPair->targetColor() = color;
    updateColorPairDisplay(true);
    updateColorPair();
}


void ColorPairItem::on_closeBtn_clicked()
{

    QMessageBox msgBox(QMessageBox::NoIcon, "Suppresion paire de couleurs",
                       "Etes-vous sûr de vouloir supprimer cette paire de couleurs ?",
                       QMessageBox::Yes | QMessageBox::Cancel,this);
    int ret = msgBox.exec();

    if(ret != QMessageBox::Yes)
        return;

    emit emitColorPairRemoved(m_colorPair);
}


void ColorPairItem::on_sourceColorHex_textEdited(const QString &newColor)
{
    if (newColor.length() != 9) return;
    auto color = ColorPair::fromRGBA(newColor);
    if(!color.isValid()) return;
    m_colorPair->sourceColor() = color;
    updateColorPairDisplay(false);
    updateColorPair();
}

void ColorPairItem::on_targetColorHex_textEdited(const QString &newColor)
{
    if (newColor.length() != 9) return;
    auto color = ColorPair::fromRGBA(newColor);
    if(!color.isValid()) return;
    m_colorPair->targetColor() = color;
    updateColorPairDisplay(false);
    updateColorPair();
}


void ColorPairItem::on_colorPairName_textEdited(const QString &newName)
{
    if (newName.length() < 3) return;
    m_colorPair->name() = newName;
    updateColorPairDisplay(false);
    updateColorPair();
}

