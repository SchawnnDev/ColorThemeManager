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

ColorPair::ColorPair(const QString &id, const QColor &source_color, const QColor &target_color) {
    this->m_id = id;
    this->source_color = source_color;
    this->target_color = target_color;
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

bool CompareColorPair::operator()(const ColorPair &colorPair1, const ColorPair &colorPair2) const {
    return colorPair1.get_m_id().compare(colorPair2.get_m_id()) < 0;
}
