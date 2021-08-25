#include "applicationlauncher.h"

#include <QGuiApplication>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QProcess>
#include <QScreen>
#include <QtMath>

ApplicationLauncher::ApplicationLauncher(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    initializeSettings();
    centerCirclePosition = -centerCircleSize / 2;
    iconOffset = iconSize / 2;
    menuOffset = menuSize / 2;
    iconDistance = centerCircleSize / 2 + (menuSize - centerCircleSize) / 4;
    sliceLength = 2 * M_PI / sliceCount;
    menu.setEnvironments(QStringList() << qgetenv("XDG_CURRENT_DESKTOP"));
    QString menuFile = XdgMenu::getMenuFileName();
    if (!menu.read(menuFile)) {
        return;
    }
}

ApplicationLauncher::~ApplicationLauncher()
{
}

void ApplicationLauncher::toggle()
{
    if (isVisible()) {
        hide();
    } else {
        sliceSelected = -1;
        items.clear();
        currentPage.clear();
        items << menu.xml().documentElement();
        currentPage.append(0);
        navigate(0);
        showFullScreen();
        QCursor::setPos(screen()->size().width() / 2, screen()->size().height() / 2);
    }
}

void ApplicationLauncher::initializeSettings()
{
    if (settings.allKeys().isEmpty()) {
        settings.beginGroup("settings");
        settings.setValue("sliceCount", sliceCount);
        settings.endGroup();
        settings.beginGroup("size");
        settings.setValue("centerCircle", centerCircleSize);
        settings.setValue("icons", iconSize);
        settings.setValue("menu", menuSize);
        settings.endGroup();
    }
    settings.beginGroup("settings");
    sliceCount = settings.value("sliceCount", centerCircleSize).toInt();
    settings.endGroup();
    settings.beginGroup("size");
    centerCircleSize = settings.value("centerCircle", centerCircleSize).toInt();
    iconSize = settings.value("icons", iconSize).toInt();
    menuSize = settings.value("menu", menuSize).toInt();
    settings.endGroup();
}

void ApplicationLauncher::navigate(int i)
{
    QDomElement e;
    if (i == -1) {
        QDomNode n = items[0].parentNode().parentNode();
        if (n.isDocument()) {
            hide();
            return;
        } else {
            currentPage.removeLast();
            e = n.firstChildElement();
        }
    } else {
        if(items[i + currentPage.last() * sliceCount].attribute("exec").isNull()) {
            e = items[i + currentPage.last() * sliceCount].firstChildElement();
            currentPage.append(0);
        } else {
            QProcess::startDetached(items[i + currentPage.last() * sliceCount].attribute("exec").split(" ")[0], {});
            hide();
        }
    }
    items.clear();
    while (!e.isNull()) {
        if (e.tagName() == "Menu" || e.tagName() == "AppLink") {
            items << e;
        }
        e = e.nextSiblingElement();
    }
    pageCount = (items.count() - 1) / sliceCount + 1;
    update();
}

void ApplicationLauncher::closeEvent(QCloseEvent *event)
{
    event->ignore();
    hide();
}

void ApplicationLauncher::mouseMoveEvent(QMouseEvent *event)
{
    int menuPosX = event->x() - screen()->size().width() / 2;
    int menuPosY = event->y() - screen()->size().height() / 2;
    int distance = pow(menuPosX, 2) + pow(menuPosY, 2);
    sliceSelected = -1;
    if (distance >= pow(centerCircleSize / 2, 2)) {
        for (int i = 0; i + currentPage.last() * sliceCount < items.count() && i < sliceCount; i++) {
            float angle = M_PI - atan2(menuPosX, menuPosY);
            float startangle = i * sliceLength - sliceLength / 2;
            float endangle = startangle + sliceLength;
            if (startangle < 0) {
                startangle += 2 * M_PI;
            }
            if ((startangle <= angle && angle <= endangle) || (endangle < startangle && (startangle <= angle || angle <= endangle))) {
                sliceSelected = i;
            }
        }
        if (distance >= pow(menuSize / 2, 2)) {
            if (!lock && sliceSelected != -1 && QGuiApplication::mouseButtons() == Qt::LeftButton) {
                navigate(sliceSelected);
            }
            lock = true;
        } else {
            lock = false;
        }
    } else {
        lock = false;
    }
    update();
}

void ApplicationLauncher::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        navigate(-1);
    } else if (event->button() == Qt::RightButton) {
        if (++currentPage.last() >= pageCount) {
            currentPage.last() = 0;
        }
        update();
    }
}

void ApplicationLauncher::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(rect().center());
    for (int i = 0; i < sliceCount; i++) {
        if (sliceSelected == i) {
            painter.setBrush(Qt::darkGray);
        } else {
            painter.setBrush(Qt::SolidPattern);
        }
        float sliceLengthDegrees = qRadiansToDegrees(sliceLength);
        painter.drawPie(-menuOffset, -menuOffset, menuSize, menuSize, (90 - i * sliceLengthDegrees + qRadiansToDegrees(sliceLength) / 2) * 16, -sliceLengthDegrees * 16);
    }
    for (int i = 0; i + currentPage.last() * sliceCount < items.count() && i < sliceCount; i++) {
        QPixmap icon = QIcon::fromTheme(items[i + currentPage.last() * sliceCount].attribute("icon")).pixmap(iconSize);
        painter.drawPixmap(iconDistance * sin(i * sliceLength) - iconOffset, iconDistance * -cos(i * sliceLength) - iconOffset, icon);
    }
    painter.setBrush(Qt::SolidPattern);
    painter.drawEllipse(centerCirclePosition, centerCirclePosition, centerCircleSize, centerCircleSize);
    QString circleText;
    if (sliceSelected + currentPage.last() * sliceCount < items.count() && sliceSelected != -1) {
        circleText = items[sliceSelected + currentPage.last() * sliceCount].attribute("title");
    } else {
        circleText = "[Left Click Drag] Navigate\n[Middle Click] Back\n[Right Click] Next Page\n(" + QString::number(currentPage.last() + 1) + "/" + QString::number(pageCount) + ")";
    }
    painter.setPen(Qt::white);
    painter.drawText(centerCirclePosition, centerCirclePosition, centerCircleSize, centerCircleSize, Qt::AlignCenter, circleText);
}
