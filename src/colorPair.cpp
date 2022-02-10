//
// Created by Paul on 10/02/2022.
//

#include "../include/colorPair.h"


ColorPair::ColorPair() = default;

ColorPair::ColorPair(const QString &id) {
    this->m_id = id;
}

ColorPair::ColorPair(const ColorPair &color) {

}

ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2) {
    this->m_id = id;
}

//bool ColorPair::CompareColorPair()(const ColorPair &color1, const ColorPair &color2) {
//    return &color1 == &color2;
//}

QString ColorPair::toRGBA(const QColor &color) {
    return color.name().append(QString::number(color.alpha(), 16));
}

QColor ColorPair::fromRGBA(const QString &colorStr) {
    QColor color = QColor(colorStr.left(7));
    color.setAlpha(colorStr.rightRef(2).toInt(Q_NULLPTR, 16));
    return {color};
}

bool ColorPair::operator()(const ColorPair &color1, const ColorPair &color2) const {
    return false;
}

