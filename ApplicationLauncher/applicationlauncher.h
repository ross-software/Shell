#ifndef APPLICATIONLAUNCHER_H
#define APPLICATIONLAUNCHER_H

#include <QSettings>
#include <QWidget>
#include <XdgMenu>

class ApplicationLauncher : public QWidget
{
    Q_CLASSINFO("D-Bus Interface", "org.ROSS.ApplicationLauncher")
    Q_OBJECT

public:
    ApplicationLauncher(QWidget *parent = nullptr);
    ~ApplicationLauncher();

public slots:
    Q_SCRIPTABLE void toggle();

private:
    int centerCircleSize = 250;
    int iconSize = 64;
    int menuSize = 500;
    int sliceCount = 8;
    QSettings settings;

    int centerCirclePosition;
    QList<int> currentPage;
    int iconDistance;
    int iconOffset;
    QList<QDomElement> items;
    bool leftClicking;
    bool lock;
    int menuOffset;
    int pageCount;
    float sliceLength;
    int sliceSelected;
    XdgMenu menu;

    void initializeSettings();
    void navigate(int i);

    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};
#endif // APPLICATIONLAUNCHER_H
