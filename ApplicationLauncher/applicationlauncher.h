#ifndef APPLICATIONLAUNCHER_H
#define APPLICATIONLAUNCHER_H

#include "launcheritem.h"

#include <QGridLayout>
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
    const int maxColumns = 4;
    QLabel *nextPageLabel;
    const int maxRows = 2;
    XdgMenu menu;
    QStringList path = {"Applications"};
    QVBoxLayout *verticalLayout;

    void clearGridLayout();
    void initializeMenu();
    void loadLauncherItems(const QString &tagName);
    void showApplications();

    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *);
    void keyPressEvent(QKeyEvent *event);

};
#endif // APPLICATIONLAUNCHER_H
