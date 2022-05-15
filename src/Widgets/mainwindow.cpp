#include "ui_mainwindow.h"
#include "include/Widgets/mainwindow.h"
#include "include/Widgets/openthemeitem.h"
#include "include/utils.h"

#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QInputDialog>
#include <QSettings>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createLanguageMenu();

    ui->openThemesList->setDragDropMode(QAbstractItemView::InternalMove);

    // Drag and drop
    setAcceptDrops(true);

    setWindowIcon(QIcon(":/img/favicon.ico"));

    connect(ui->openThemesList,
            SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem * )),
            this,
            SLOT(onCurrentItemChanged(QListWidgetItem * , QListWidgetItem * )));

    connect(this,
            SIGNAL(emitThemeSelected(const std::shared_ptr<Theme>&)),
            ui->themeEditor,
            SLOT(onThemeSelected(const std::shared_ptr<Theme>&)));

    connect(this,
            SIGNAL(emitThemeClosed(const std::shared_ptr<Theme>&)),
            ui->themeEditor,
            SLOT(onThemeClosed(const std::shared_ptr<Theme>&)));

    connect(ui->themeEditor,
            SIGNAL(emitStatusBarUpdate(const QString &)),
            this,
            SLOT(onStatusBarUpdate(const QString &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createLanguageMenu()
{
    QActionGroup *langGroup = new QActionGroup(ui->menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL(triggered(QAction * )),
            this, SLOT(onLanguageChanged(QAction * )));

    QSettings settings;
    QString currentLocale = settings.value("currentLocale", "fr").toString();

    QStringList languages;
    languages << "Francais" <<"Anglais";

    QStringList languageCodes;
    languageCodes << "fr" << "en";

    for (int i = 0; i < languages.size(); ++i)
    {
        const auto &language = languages.at(i);
        const auto &code = languageCodes.at(i);

        QIcon icon(QString(":/img/lang/%1.png").arg(code));
        QAction *action = new QAction(icon, tr(qPrintable(language)), this);
        action->setCheckable(true);
        action->setData(code);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        if (currentLocale != code)
            continue;

        action->setChecked(true);
    }

    loadLanguage(currentLocale);

}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (!e->mimeData()->hasUrls())
        return;
    e->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    int imported = 0;

            foreach (const QUrl &url, e->mimeData()->urls())
        {
            QString fileName = url.toLocalFile();

            if (!fileName.endsWith(".theme"))
                continue;

            QFile file(fileName);

            if (!file.exists())
            {
                Utils::displayError(tr("Le fichier sélectionné n'existe pas"),
                                    this);
                continue;
            }

            onStatusBarUpdate(
                    tr("Importation du fichier drag-and-drop ") + fileName);

            file.open(QIODevice::ReadOnly);
            QDataStream in(&file);

            auto theme = std::make_shared<Theme>();
            in >> theme->uuid() >> theme->name() >> theme->iconPath()
               >> theme->URL()
               >> theme->colorPairs();
            // Close file
            file.close();

            theme->saved() = true;
            theme->path() = fileName;

            addThemeItem(theme);
            ++imported;
        }

    QString msg = tr("%1 thèmes ont bien été chargés.").arg(imported);
    QMessageBox::information(this, "Success!", msg);
    onStatusBarUpdate(msg);
}

void MainWindow::on_actionImportFile_triggered()
{

    QDir dir = QDir((QString) QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Importer un thème"),
            dir.filePath("theme.theme"),
            tr("Fichiers thème (*.theme)"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.exists())
    {
        Utils::displayError(tr("Le fichier sélectionné n'existe pas"), this);
        return;
    }

    onStatusBarUpdate(tr("Importation du thème ") + fileName);

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    auto theme = std::make_shared<Theme>();
    in >> theme->uuid() >> theme->name() >> theme->iconPath() >> theme->URL()
       >> theme->colorPairs();
    // Close file
    file.close();

    theme->saved() = true;
    theme->path() = fileName;

    addThemeItem(theme);
    onStatusBarUpdate(tr("Le thème %1 a bien été importé.").arg(theme->name()));
}

void MainWindow::on_actionCalculateFileTheme_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Ouvrir un fichier"),
            (QString) QStandardPaths::DocumentsLocation);

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.exists())
    {
        Utils::displayError(tr("Le fichier sélectionné n'existe pas"), this);
        return;
    }

    onStatusBarUpdate(tr("Calcul du thème d'un fichier pour ") + fileName);

    file.open(QIODevice::ReadWrite);
    QByteArray content = file.readAll();
    QString contentStr(content);

    auto theme = std::make_shared<Theme>();
    theme->iconPath() = ":/img/new.png";
    theme->name() = tr("Nouveau thème importé");

    // HEX
    QRegularExpression regex(
            R"(#?([\da-fA-F]{2})([\da-fA-F]{2})([\da-fA-F]{2}([\da-fA-F]{2})))");
    QRegularExpressionMatchIterator i = regex.globalMatch(contentStr);
    int j = 0;

    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (!match.hasMatch()) continue;
        QString captured = match.captured();

        auto colorPair = std::make_shared<ColorPair>();
        colorPair->name() = tr("Couleur %1").arg(j++);
        colorPair->sourceColor() = ColorPair::fromRGBA(captured);
        colorPair->targetColor() = QColor(0, 0, 0, 255);

        theme->colorPairs().push_back(colorPair);
        ++j;
    }

    addThemeItem(theme);

    QString msg = tr("%1 couleurs ont bien été trouvées").arg(j);
    QMessageBox::information(this, tr("Success!"), msg);
    onStatusBarUpdate(msg);
}

void MainWindow::on_actionChargeRecentThemes_triggered()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    QStringList filesCopy = files;
    int loaded = 0;

    onStatusBarUpdate(
            tr("Chargement de %1 thèmes récents.").arg(files.length()));

            foreach(QString filePath, filesCopy)
        {
            QFileInfo info(filePath);

            if (!info.exists() || !info.isFile())
            {
                files.removeOne(filePath);
                continue;
            }

            QFile file(filePath);

            file.open(QIODevice::ReadOnly);
            QDataStream in(&file);

            auto theme = std::make_shared<Theme>();
            in >> theme->uuid() >> theme->name() >> theme->iconPath()
               >> theme->URL() >> theme->colorPairs();
            // Close file
            file.close();

            theme->saved() = true;
            theme->path() = filePath;

            addThemeItem(theme);

            // import theme
            ++loaded;
        }

    // update files
    settings.setValue("recentFileList", files);

    QString msg = tr("%1 thèmes ont bien été chargés.").arg(loaded);

    QMessageBox::information(this, tr("Success!"), msg);
    onStatusBarUpdate(msg);
}

void MainWindow::on_actionCreateTheme_triggered()
{
    auto theme = std::make_shared<Theme>();
    theme->iconPath() = ":/img/new.png";
    theme->name() = tr("Nouveau thème");
    addThemeItem(theme);
}

void MainWindow::addThemeItem(const std::shared_ptr<Theme> &theme)
{
    auto widget = ui->openThemesList;
    auto item = new QListWidgetItem(widget);
    auto themeItem = new openThemeItem(theme, widget);
    item->setSizeHint(themeItem->minimumSizeHint());
    widget->addItem(item);
    widget->setItemWidget(item, themeItem);

    // Connect signals between themeItem and MainWindow
    connect(themeItem, SIGNAL(emitThemeClosed(std::shared_ptr<Theme>)),
            this, SLOT(onThemeClosed(std::shared_ptr<Theme>)));

    connect(ui->themeEditor,
            SIGNAL(emitThemeUpdated(const std::shared_ptr<Theme>&)),
            themeItem,
            SLOT(onThemeUpdated(const std::shared_ptr<Theme>&)));

    widget->setCurrentItem(item);
}

void MainWindow::on_actionSaveAllThemes_triggered()
{
    int saved = 0;

    onStatusBarUpdate(
            tr("Sauvegarde de %1 thèmes").arg(ui->openThemesList->count()));

    for (auto i = 0; i < ui->openThemesList->count(); ++i)
    {
        auto item = ui->openThemesList->item(i);
        auto themeItem = qobject_cast<openThemeItem *>
                (ui->openThemesList->itemWidget(item));
        auto theme = themeItem->theme();

        if (theme->saved()) continue;

        if (!theme->save(false, this)) continue;

        ++saved;
    }

    QString msg = tr("%1 thèmes ont bien été sauvegardés.").arg(saved);

    QMessageBox::information(this, tr("Success!"), msg);
    onStatusBarUpdate(msg);
}

void MainWindow::onThemeClosed(const std::shared_ptr<Theme> &theme)
{
    for (auto i = 0; i < ui->openThemesList->count(); ++i)
    {
        auto item = ui->openThemesList->item(i);
        auto themeItem = qobject_cast<openThemeItem *>
                (ui->openThemesList->itemWidget(item));

        if (themeItem->theme()->uuid() != theme->uuid())
            continue;

        emitThemeClosed(themeItem->theme());
        delete ui->openThemesList->takeItem(ui->openThemesList->row(item));
        break;
    }
}

void MainWindow::onCurrentItemChanged(QListWidgetItem *current,
                                      QListWidgetItem *previous)
{
    if (current == nullptr) return;
    auto themeItem = qobject_cast<openThemeItem *>
            (ui->openThemesList->itemWidget(current));

    if (themeItem == nullptr) return;

    emitThemeSelected(themeItem->theme());
}

void MainWindow::onStatusBarUpdate(const QString &message)
{
    ui->statusBar->showMessage(message, 2000);
}

void MainWindow::loadLanguage(const QString& code)
{
    QSettings settings;
    // fr or en

    // remove the old translator
    qApp->removeTranslator(&m_translator);

    if(code == "fr")
    {
        settings.setValue("currentLocale", "fr");
        return;
    }

    // load the new translator
    bool result = m_translator.load(QString(":/lang/color_theme_manager_%1.qm").arg(code));

    if(!result) {
        Utils::displayError(tr("Impossible de charger le langage %1").arg(code));
        return;
    }

    settings.setValue("currentLocale", code);
    qApp->installTranslator(&m_translator);
}

void MainWindow::onLanguageChanged(QAction *action)
{
    if (action == Q_NULLPTR) return;

    QString code = action->data().toString();
    loadLanguage(code);
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event != Q_NULLPTR && event->type() == QEvent::LanguageChange)
        ui->retranslateUi(this);
    QMainWindow::changeEvent(event);
}

void MainWindow::on_actionQuitter_triggered()
{

}

