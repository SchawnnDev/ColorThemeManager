#ifndef COLOR_THEME_MANAGER_UTILS_H
#define COLOR_THEME_MANAGER_UTILS_H

#include <QString>
#include <QWidget>
#include <QMessageBox>

class Utils {

public:
    static void displayError(const QString& message, QWidget *parent = Q_NULLPTR)
    {
        QMessageBox::critical(parent, "Erreur", message);
    }

};

#endif //COLOR_THEME_MANAGER_UTILS_H
