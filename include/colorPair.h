//
// Created by Paul on 10/02/2022.
//

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H


#include <QString>
#include <QColor>

class ColorPair {
private:
    QString m_id;
    QColor m_source_color;
    QColor m_target_color;
public:
    ColorPair() = default; //constructeur vide
    ColorPair(QString id, QColor source_color, QColor target_color);
    ColorPair(QString id); //con. initialisant uniquement l'identifiant

    static QString toRGBA(const QColor &color);

    static QColor fromRGBA(const QString &colorStr);

    QString const& id() const { return m_id; };
    QString& id() { return m_id; };

};

class CompareColorPair {
public:
    bool operator()(const ColorPair &colorPair1, const ColorPair &colorPair2) const;
};

#endif //COLOR_THEME_MANAGER_COLORPAIR_H
