#include "ui_openthemeitem.h"
#include "include/Widgets/openthemeitem.h"
#include <QDebug>
#include <QStyleOptionButton>

openThemeItem::openThemeItem(const std::shared_ptr<Theme>& theme, QWidget *parent) :
        QWidget(parent), ui(new Ui::openThemeItem)
{
    ui->setupUi(this);
    ui->themeName->setText(theme->name());

    this->m_theme = theme;

    // Set close button size
    auto closeBtn = ui->themeClose;
    auto textSize = closeBtn->fontMetrics().size(Qt::TextShowMnemonic,
                                                 closeBtn->text())  * 2;
    QStyleOptionButton opt;
    opt.initFrom(ui->themeClose);
    opt.rect.setSize(textSize);
    closeBtn->setMaximumSize(
            closeBtn->style()->sizeFromContents(QStyle::CT_PushButton,
                                                &opt,
                                                textSize,
                                                closeBtn));

    // Load image
    if (theme->iconPath().isEmpty())
        return;

    QPixmap image(theme->iconPath());

    if (image.isNull())
        return;

    int w = ui->themeIcon->width();
    int h = ui->themeIcon->height();

    ui->themeIcon->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
}

openThemeItem::~openThemeItem()
{
    delete ui;
}

void openThemeItem::on_themeClose_clicked()
{
    emit emitThemeClosed(m_theme);
}
