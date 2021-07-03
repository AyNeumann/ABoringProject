#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QCoreApplication>
#include <QSettings>
#include <QVariant>
#include <QDebug>

class Settings : public QObject
{
    Q_OBJECT
private:
    QString m_filename;
public:
    explicit Settings(QObject *parent = nullptr, QString applicationDirPath = NULL);

    QString initializeSettingsFileName(QString applicationDirPath);
    void initializeSetttings();
    void writeSettings(QString group, QString key, QVariant value);
    void writeSettings(QString group, QMap<QString, QVariant> value);
    void writeSettings(QString filename, QString group, QString key, QVariant value);
    void writeSettings(QString filename, QString group, QMap<QString, QVariant> value);
    void readSettings(QString group, QString key, QVariant value);

    void writeSingleKey(QSettings *settings, QString group, QString key, QVariant value);
    void writeManyKeys(QSettings *settings, QString group, QMap<QString, QVariant> value);

signals:

};

#endif // SETTINGS_H
