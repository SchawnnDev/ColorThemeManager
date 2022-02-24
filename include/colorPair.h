//
// Created by Paul on 10/02/2022.
//

#ifndef COLOR_THEME_MANAGER_COLORPAIR_H
#define COLOR_THEME_MANAGER_COLORPAIR_H


#include <QString>
#include <QColor>
#include <set>
#include <QFile>

using namespace std;

class ColorPair {
private:
    QString m_id;
    QColor source_color;
    QColor target_color;
public:
    ColorPair() = default; //constructeur vide
    ColorPair(const ColorPair &color); //con. par copie
    ColorPair(const QString &id, const QColor &color1, const QColor &color2);

    ColorPair(const QString &id); //con. initialisant uniquement l'identifiant

    static QString toRGBA(const QColor &color);

    static QColor fromRGBA(const QString &colorStr);

    bool operator()(const ColorPair &colorPair) const;

    const QString &get_m_id() const {
        return m_id;
    }

};

#endif //COLOR_THEME_MANAGER_COLORPAIR_H
