//
// Created by Paul on 24/02/2022.
//

#include "include/xmlReader.h"

void XMLReader::read(const QString &path) {
    QDomDocument doc;
    QFile xmlFile(path);

    if (!xmlFile.open(QIODevice::ReadOnly)) {
        qDebug() << "erreur";
        return;
    }

    doc.setContent(&xmlFile);
    xmlFile.close();

    QDomElement root = doc.documentElement();
    QDomElement node = root.firstChildElement();

    while (!node.isNull()) {
        QString id = node.attribute("id");
        QString target_color = node.attribute("target");
        QString source_color = node.attribute("source");
        colorPairs.insert(ColorPair(id, source_color, target_color));
        // Go to next node
        node = node.nextSiblingElement();
    }

}

void XMLReader::display() {
    for (const ColorPair& pair: this->colorPairs) {
        qDebug() << pair.id();
    }
}
