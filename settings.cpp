#include "settings.h"

Settings::Settings(QObject *parent, QString applicationDirPath) : QObject(parent)
{
    qDebug() << "Settings | Constructing Settings class:" << this;
    m_filename = initializeSettingsFileName(applicationDirPath);
    initializeSetttings();
}

QString Settings::initializeSettingsFileName(QString applicationDirPath)
{
    qDebug() << "Initializing Settings file name...";
    QCoreApplication::setOrganizationName("Aymeric");
    QCoreApplication::setOrganizationDomain("aymeric.com");
    QCoreApplication::setApplicationName("A Boring Project");

    QString filename = applicationDirPath + "/settings.ini";

    qDebug() << "initializeSettingsFileName | filenamne:" << filename;

    return filename;
}

void Settings::initializeSetttings()
{
    QSettings settings(m_filename, QSettings::Format::IniFormat);

    if(settings.allKeys().empty())
    {
        qDebug() << "Initialzing settings in setting.ini file";
        settings.beginGroup("Organization");
        settings.setValue("Name", QCoreApplication::organizationName());
        settings.setValue("Domain", QCoreApplication::organizationDomain());
        settings.endGroup();

        settings.beginGroup("Application");
        settings.setValue("Name", QCoreApplication::applicationName());
        settings.endGroup();
    }
}

void Settings::writeSettings(QString group, QString key, QVariant value)
{
    QSettings settings(m_filename, QSettings::Format::IniFormat);
    writeSingleKey(&settings, group, key, value);

}

void Settings::writeSettings(QString group, QMap<QString, QVariant> value)
{
    QSettings settings(m_filename, QSettings::Format::IniFormat);
    writeManyKeys(&settings, group, value);
}

void Settings::writeSettings(QString filename, QString group, QString key, QVariant value)
{
    QSettings settings(filename, QSettings::Format::IniFormat);
    writeSingleKey(&settings, group, key, value);
}

void Settings::writeSettings(QString filename, QString group, QMap<QString, QVariant> value)
{
    QSettings settings(filename, QSettings::Format::IniFormat);
    writeManyKeys(&settings, group, value);

    settings.sync();
}

void Settings::readSettings(QString group, QString key, QVariant value)
{
    QSettings settings(m_filename, QSettings::Format::IniFormat);
    settings.beginGroup(group);
    settings.value(key, value);
    settings.endGroup();
}

void Settings::writeSingleKey(QSettings *settings, QString group, QString key, QVariant value)
{
    settings->beginGroup(group);
    settings->setValue(key, value);
    settings->endGroup();
}

void Settings::writeManyKeys(QSettings *settings, QString group, QMap<QString, QVariant> value)
{
    settings->beginGroup(group);

    foreach(QString key, value.keys())
    {
        settings->setValue(key, value.value(key));
    }

    settings->endGroup();

    settings->sync();
}
