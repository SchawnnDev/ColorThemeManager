#include "include/xmlReader.h"
#include "include/utils.h"

void XMLReader::importFile(const std::shared_ptr<Theme> &theme, const QString &path)
{
    QDomDocument doc;
    QFile xmlFile(path);

    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        Utils::displayError(QWidget::tr("Impossible d'ouvrir le fichier %1").arg(path));
        return;
    }

    doc.setContent(&xmlFile);
    xmlFile.close();

    import(theme, doc);

}

void XMLReader::import(const std::shared_ptr<Theme> &theme, const QDomDocument &doc)
{
    QDomElement root = doc.documentElement();
    QDomElement node = root.firstChildElement();

    while (!node.isNull())
    {
        auto colorPair = std::make_shared<ColorPair>();
        colorPair->name() = node.attribute("id");
        colorPair->targetColor() = ColorPair::fromRGBA(node.attribute("target"));
        colorPair->sourceColor() = ColorPair::fromRGBA(node.attribute("source"));

        theme->colorPairs().push_back(colorPair);
        // Go to next node
        node = node.nextSiblingElement();
    }
}
