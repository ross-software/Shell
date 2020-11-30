#ifndef LAUNCHERITEM_H
#define LAUNCHERITEM_H

#include <QLabel>
#include <QVBoxLayout>

class LauncherItem : public QWidget
{
    Q_OBJECT

public:
    LauncherItem(QWidget *parent = nullptr);

    inline static const QSize fixedSize = QSize(250, 100);
    bool isCategory = false;
    QVBoxLayout *verticalLayout;

    void execute();
    QStringList getExec() const;
    QPixmap getIcon() const;
    QString getTitle() const;
    void setExec(const QStringList &exec);
    void setIcon(const QPixmap &icon);
    void setTitle(const QString &title);

private:
    QLabel *iconLabel, *titleLabel;
    QStringList m_exec;

};

#endif // LAUNCHERITEM_H
