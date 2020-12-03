#include "applicationlauncher.h"

#include <QIcon>
#include <QKeyEvent>
#include <QKeySequence>
#if HAVE_X11
#include <QtX11Extras/QX11Info>
#include <X11/XKBlib.h>
#endif
#include <cmath>

ApplicationLauncher::ApplicationLauncher(QWidget *parent)
    : QWidget(parent)
    , escapeLabel(new QLabel(tr("[Esc] Back/Close")))
    , gridLayout(new QGridLayout)
    , nextPageLabel(new QLabel(tr("[Tab] Switch Page")))
    , settings(new QSettings)
    , verticalLayout(new QVBoxLayout(this))
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    verticalLayout->addWidget(escapeLabel);
    verticalLayout->addLayout(gridLayout);
    gridLayout->setAlignment(Qt::AlignLeft);
    verticalLayout->addStretch();
    verticalLayout->addWidget(nextPageLabel);
    nextPageLabel->setAlignment(Qt::AlignHCenter);
}

void ApplicationLauncher::toggle()
{
    if (!isVisible()) {
        while (path.size() > 1) {
            path.removeLast();
        }
        currentPage = 0;
        initializeMenu();
        showApplications();
        show();
    } else {
        hide();
    }
}

void ApplicationLauncher::clearGridLayout()
{
    while (QLayoutItem *item = gridLayout->takeAt(0)) {
        item->widget()->setParent(nullptr);
        delete item;
    }
}

void ApplicationLauncher::initializeMenu()
{
    settings.sync();
    settings.beginGroup("Layout");
    maxColumns = settings.value("MaxColumns", 4).toInt();
    maxRows = settings.value("MaxRows", 2).toInt();
    settings.endGroup();
    menu.setEnvironments(QStringList() << qgetenv("XDG_CURRENT_DESKTOP"));
    if (!menu.read(XdgMenu::getMenuFileName())) {
        return;
    }
    launcherItems.clear();
    loadLauncherItems("Menu");
    loadLauncherItems("AppLink");
    QHashIterator<QString, QVarLengthArray<LauncherItem *>> it(launcherItems);
    while (it.hasNext()) {
        it.next();
        std::sort(launcherItems[it.key()].begin(), launcherItems[it.key()].end(), [](LauncherItem *a, LauncherItem *b) {
            return a->getTitle() < b->getTitle();
        });
    }
}

void ApplicationLauncher::loadLauncherItems(const QString &tagName) {
    QDomNodeList nodes = menu.xml().elementsByTagName(tagName);
    for (int i = 0; i < nodes.size(); i++) {
        QDomNode node = nodes.at(i);
        if (node.parentNode().isElement()) {
            LauncherItem *launcherItem = new LauncherItem;
            launcherItem->setIcon(QIcon::fromTheme(node.toElement().attribute("icon")).pixmap(32));
            launcherItem->setTitle(node.toElement().attribute("title"));
            if (tagName == "Menu") {
                launcherItem->isCategory = true;
                launcherItem->setExec({ node.toElement().attribute("name") });
            } else if (tagName == "AppLink") {
                launcherItem->setExec(node.toElement().attribute("exec").remove("\"").remove(QRegExp(" %.")).split(" "));
            }
            launcherItems[node.parentNode().toElement().attribute("name")] << launcherItem;
        }
    }
}

void ApplicationLauncher::showApplications()
{
    clearGridLayout();
    int maxPages = std::ceil(launcherItems[path.last()].size() / (double)(maxRows * maxColumns));
    if (currentPage >= maxPages) {
        currentPage = 0;
    } else if (currentPage < 0) {
        currentPage = maxPages - 1;
    }
    nextPageLabel->setVisible(maxPages > 1);
    for (int row = 0; row < maxRows; row++) {
        for (int column = 0; column < maxColumns; column++) {
            int i = currentPage * maxRows * maxColumns + row * maxColumns + column;
            if (i < launcherItems[path.last()].size()) {
#if HAVE_X11
                if (QX11Info::isPlatformX11()) {
                    QString keyPrefix = "[" + QKeySequence(XkbKeycodeToKeysym(QX11Info::display(), 24 + 14 * row + column, 0, 0)).toString() + "] ";
                    if (!launcherItems[path.last()].at(i)->getTitle().startsWith(keyPrefix)) {
                        launcherItems[path.last()].at(i)->setTitle(keyPrefix + launcherItems[path.last()].at(i)->getTitle());
                    }
                }
#endif
                gridLayout->addWidget(launcherItems[path.last()].at(i), row, column);
            }
        }
    }
}

void ApplicationLauncher::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void ApplicationLauncher::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    int nativeKey = event->nativeScanCode();
    for (int row = 0; row < maxRows; row++) {
        int i = 24 + row * 14;
        if (nativeKey >= i && nativeKey < i + maxColumns) {
            i = nativeKey - i + row * maxColumns;
            if (i < gridLayout->count()) {
                LauncherItem *launcherItem = qobject_cast<LauncherItem *>(gridLayout->itemAt(i)->widget());
                if (launcherItem->isCategory) {
                    path << launcherItem->getExec().at(0);
                    showApplications();
                } else {
                    launcherItem->execute();
                }
            }
        }
    }
    if (event->key() == Qt::Key_Tab) {
        currentPage++;
        showApplications();
    } else if (event->key() == Qt::Key_Backtab) {
        currentPage--;
        showApplications();
    }
    if (event->key() == Qt::Key_Escape) {
        if (path.size() > 1) {
            path.removeLast();
            currentPage = 0;
        } else {
            hide();
        }
        showApplications();
    }
}
