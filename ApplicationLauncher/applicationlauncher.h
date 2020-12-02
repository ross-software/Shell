#ifndef APPLICATIONLAUNCHER_H
#define APPLICATIONLAUNCHER_H

#include "launcheritem.h"

#include <QGridLayout>
#include <QSettings>
#include <qt5xdg/XdgMenu>

class ApplicationLauncher : public QWidget
{
    Q_CLASSINFO("D-Bus Interface", "org.ROSS.ApplicationLauncher")
    Q_OBJECT

public:
    ApplicationLauncher(QWidget *parent = nullptr);

public slots:
    Q_SCRIPTABLE void toggle();

private:
    int currentPage = 0;
    QLabel *escapeLabel;
    QGridLayout *gridLayout;
    QHash<QString, QVarLengthArray<LauncherItem *>> launcherItems;
    int maxColumns;
    int maxRows;
    XdgMenu menu;
    QLabel *nextPageLabel;
    QStringList path = {"Applications"};
    QSettings settings;
    QVBoxLayout *verticalLayout;

    void clearGridLayout();
    void initializeMenu();
    void loadLauncherItems(const QString &tagName);
    void showApplications();

    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

};
#endif // APPLICATIONLAUNCHER_H
