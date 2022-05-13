#include "ui_openthemeitem.h"
#include "include/Widgets/openthemeitem.h"
#include <QDebug>
#include <QStyleOptionButton>
#include <QMessageBox>

openThemeItem::openThemeItem(const std::shared_ptr<Theme> &theme,
                             QWidget *parent) :
        QWidget(parent), ui{new Ui::openThemeItem}, m_theme{theme}
{
    ui->setupUi(this);
    updateThemeElement();
}

openThemeItem::~openThemeItem()
{
    delete ui;
}

void openThemeItem::on_themeClose_clicked()
{

    if (!m_theme->saved())
    {
        QMessageBox msgBox(QMessageBox::NoIcon, "Sauvegarder et quitter",
                           "Etes-vous sûr de vouloir fermer ce thème sans le sauvegarder?",
                           QMessageBox::Save | QMessageBox::Discard |
                           QMessageBox::Cancel,
                           this);
        int ret = msgBox.exec();

        switch (ret)
        {
            case QMessageBox::Save:
                if(!m_theme->save(false, this))
                    return;
                break;
            case QMessageBox::Discard:
                break;
            default:
                return;
        }

    }

    emit emitThemeClosed(m_theme);
}

void openThemeItem::onThemeUpdated(const std::shared_ptr<Theme> &theme)
{
    if (theme->uuid() != m_theme->uuid()) return;
    updateThemeElement();
}

void openThemeItem::updateThemeElement()
{
    ui->themeName->setText(m_theme->name());

    // Set close button size
    auto closeBtn = ui->themeClose;
    auto textSize = closeBtn->fontMetrics().size(Qt::TextShowMnemonic,
                                                 closeBtn->text()) * 2;
    QStyleOptionButton opt;
    opt.initFrom(ui->themeClose);
    opt.rect.setSize(textSize);
    closeBtn->setMaximumSize(
            closeBtn->style()->sizeFromContents(QStyle::CT_PushButton,
                                                &opt,
                                                textSize,
                                                closeBtn));

    // Load image
    if (m_theme->iconPath().isEmpty())
        return;

    QPixmap image(m_theme->iconPath());

    if (image.isNull())
        return;

    int w = ui->themeIcon->width();
    int h = ui->themeIcon->height();

    ui->themeIcon->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
}
