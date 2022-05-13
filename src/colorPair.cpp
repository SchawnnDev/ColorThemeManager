#include "../include/colorPair.h"

ColorPair::ColorPair() {
    m_id = QUuid::createUuid();
}

ColorPair::ColorPair(const QUuid& id) : m_id{id}
{
}

ColorPair::ColorPair(const QUuid& id, const QString& name, const QColor& source_color, const QColor& target_color)
        : m_id{id}
        , m_name{name}
        , m_source_color{source_color}
        , m_target_color{target_color}
{
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
    return colorPair1.id().toString().compare(colorPair2.id().toString()) < 0;
}

QDataStream& operator<<(QDataStream &out, const std::shared_ptr<ColorPair> &colorPair) {
    out << colorPair->id() << colorPair->name() << colorPair->sourceColor() << colorPair->targetColor();
    return out;
}

QDataStream &operator>>(QDataStream &in, std::shared_ptr<ColorPair> &colorPair) {
    colorPair = std::make_shared<ColorPair>();
    in >> colorPair->id() >> colorPair->name() >> colorPair->sourceColor() >> colorPair->targetColor();
    return in;
}