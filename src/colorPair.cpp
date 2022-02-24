//
// Created by Paul on 10/02/2022.
//

#include "../include/colorPair.h"

ColorPair::ColorPair(const QString &id) {
    this->m_id = id;
}

ColorPair::ColorPair(const ColorPair &color) {
    this->source_color = color.source_color;
    this->target_color = color.target_color;
}

ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2) {
    this->m_id = id;
    this->source_color = color1;
    this->target_color = color2;
}

//bool ColorPair::CompareColorPair()(const ColorPair &source_color, const ColorPair &target_color) {
//    return &source_color == &target_color;
//} #rrggbbaa

QString ColorPair::toRGBA(const QColor &color) {
    return color.name().append(QString::number(color.alpha(), 16));
}

QColor ColorPair::fromRGBA(const QString &colorStr) {
    QColor color = QColor(colorStr.left(7));
    color.setAlpha(colorStr.rightRef(2).toInt(Q_NULLPTR, 16));
    return {color};
}

bool ColorPair::operator()(const ColorPair &colorPair) const {
    return get_m_id().compare(colorPair.get_m_id()) < 0;
}
