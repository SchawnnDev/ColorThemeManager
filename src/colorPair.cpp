#include "../include/colorPair.h"

ColorPair::ColorPair(QString id) : m_id{std::move(id)}
{
}

ColorPair::ColorPair(QString id, QColor source_color, QColor target_color)
        : m_id{std::move(id)}
        , m_source_color{std::move(source_color)}
        , m_target_color{std::move(target_color)}
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
    return colorPair1.id().compare(colorPair2.id()) < 0;
}

QDataStream& operator<<(QDataStream &out, const std::shared_ptr<ColorPair> &colorPair) {
    out << colorPair->id() << colorPair->sourceColor() << colorPair->targetColor();
    return out;
}

QDataStream &operator>>(QDataStream &in, std::shared_ptr<ColorPair> &colorPair) {
    colorPair = std::make_shared<ColorPair>();
    in >> colorPair->id() >> colorPair->sourceColor() >> colorPair->targetColor();
    return in;
}