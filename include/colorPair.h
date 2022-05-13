#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H


#include <QString>
#include <QColor>
#include <memory>

class ColorPair {
private:
    QString m_id;
    QColor m_source_color;
    QColor m_target_color;
public:
    ColorPair() = default; //constructeur vide
    ColorPair(QString id, QColor source_color, QColor target_color);
    explicit ColorPair(QString id); //con. initialisant uniquement l'identifiant

    static QString toRGBA(const QColor &color);

    static QColor fromRGBA(const QString &colorStr);

    QString const& id() const { return m_id; };
    QString& id() { return m_id; };

    QColor const& sourceColor() const { return m_source_color; }
    QColor& sourceColor() { return m_source_color;}

    QColor const& targetColor() const { return m_target_color; }
    QColor& targetColor() { return m_target_color; }

};

class CompareColorPair {
public:
    bool operator()(const ColorPair &colorPair1, const ColorPair &colorPair2) const;
};

QDataStream& operator<<(QDataStream &out, const std::shared_ptr<ColorPair> &colorPair);

QDataStream &operator>>(QDataStream &in, std::shared_ptr<ColorPair> &colorPair);

inline uint qHash(const std::shared_ptr<ColorPair> &colorPair) {
    return qHash(colorPair->id(), 0xa03f); // arbitrary value
}

#endif //COLOR_THEME_MANAGER_COLORPAIR_H
