#include "applicationlauncher.h"

#include <QApplication>
#include <QDBusConnectionInterface>
#include <QObject>
#include <QTextStream>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    translator.load(QLocale::system().name());
    app.installTranslator(&translator);
    QDBusConnection dbus = QDBusConnection::sessionBus();
    if(!dbus.registerService("org.ROSS.ApplicationLauncher")) {
        QTextStream(stderr) << "ApplicationLauncher is already running!";
        exit(EXIT_FAILURE);
    }
    ApplicationLauncher applicationLauncher;
    QObject::connect(&app, &QApplication::applicationStateChanged, [&applicationLauncher](Qt::ApplicationState state) {
        if (state == Qt::ApplicationInactive) {
            applicationLauncher.hide();
        }
    });
    dbus.registerObject("/App", &applicationLauncher, QDBusConnection::ExportScriptableSlots);
    return app.exec();
}
