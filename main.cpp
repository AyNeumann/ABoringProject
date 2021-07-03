#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "settings.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    Settings appSettings(&app, app.applicationDirPath());

    QString filename = app.applicationDirPath() + "/settings2.ini";
    QMap<QString, QVariant> value;
    value.insert("TestKey1", "TestValue1");
    value.insert("TestKey2", "TestValue2");
    appSettings.writeSettings(filename, "TestGroup", value);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("AppSetting", &appSettings);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
