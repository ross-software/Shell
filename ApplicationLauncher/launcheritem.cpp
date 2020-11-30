#include "launcheritem.h"

#include <QProcess>

LauncherItem::LauncherItem(QWidget *parent)
    : QWidget(parent)
    , verticalLayout(new QVBoxLayout(this))
    , iconLabel(new QLabel)
    , titleLabel(new QLabel)
{
    setFixedSize(fixedSize);
    setLayout(verticalLayout);
    iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    verticalLayout->addWidget(iconLabel);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    verticalLayout->addWidget(titleLabel);
}

void LauncherItem::execute()
{
    if (!m_exec.empty()) {
        QString program = m_exec.first();
        QStringList arguments = m_exec;
        arguments.removeFirst();
        QProcess::startDetached(program, arguments);
        window()->hide();
    }
}

QStringList LauncherItem::getExec() const
{
    return m_exec;
}

QPixmap LauncherItem::getIcon() const
{
    return iconLabel->pixmap(Qt::ReturnByValue);
}

QString LauncherItem::getTitle() const
{
    return titleLabel->text();
}

void LauncherItem::setExec(const QStringList &exec)
{
    m_exec = exec;
}

void LauncherItem::setIcon(const QPixmap &icon)
{
    iconLabel->setPixmap(icon);
}

void LauncherItem::setTitle(const QString &title)
{
    QFontMetrics metrics(titleLabel->font());
    titleLabel->setText(metrics.elidedText(title, Qt::ElideRight, width() - 10));
}
