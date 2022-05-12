#include "ui_colorpairitem.h"
#include "include/Widgets/colorpairitem.h"


ColorPairItem::ColorPairItem(QWidget *parent) :
        QWidget(parent), ui(new Ui::ColorPairItem)
{
    ui->setupUi(this);
}

ColorPairItem::~ColorPairItem()
{
    delete ui;
}

