/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main Share::Configuration class.

#include "ShareConfiguration.h"
#include <ShareCommunicationNetwork.h>

#define debugName qDebug() << "Conf:" << __func__


#warning Not nominal configuration
const Share::Configuration::Config Share::Configuration::defaultSettings = {
  { false, 
    { Share::CommunicationNetwork::s_defaultAdminPortNumber,
      Share::Communication::DBUS,
      Share::CommunicationNetwork::s_defaultAdminPortNumber,
    },
    true,
    {
      false,
      Share::CommunicationNetwork::s_defaultUserPortNumber,
      Share::Communication::DBUS,
      Share::CommunicationNetwork::s_defaultUserPortNumber,
    },
  },
  {
    false, true,
    {
      Share::CommunicationNetwork::s_defaultUserPortNumber,
      Share::Communication::DBUS,
      Share::CommunicationNetwork::s_defaultUserPortNumber,
    },
  },
};

const Share::Configuration::ConfigNames Share::Configuration::configNames = {
  {
    QString("enableSystemDeamon"),
    {
      QString("systemDeamon"),
      QString("externalListenPort"),
      QString("internalCommunicationType"),
      QString("internalListenPort"),
    },
    QString("enableUserDeamon"),
    {
      QString("userDeamon"),
      QString("externalCommunicationViaSystemDeamon"),
      QString("externalListenPort"),
      QString("internalCommunicationType"),
      QString("internalListenPort"),
    }
  },
  {
    QString("useSystemConfig"),
    QString("enableUserDeamon"),
    {
      QString("userDeamon"),
      QString("externalListenPort"),
      QString("internalCommunicationType"),
      QString("internalListenPort"),
    },
  },
};

const QString Share::Configuration::organisationName = "CapProject";
const QString Share::Configuration::applicationName = "libShareResource";
Share::Configuration Share::Configuration::instance;

Share::Configuration::Configuration(QObject* parent)
{
  currentSettings = defaultSettings;
}

Share::Configuration::~Configuration()
{
}

Share::Configuration * Share::Configuration::getInstance()
{
  return &instance;
}

bool Share::Configuration::readConf()
{
  QSettings systemSettings(QSettings::SystemScope,organisationName,applicationName);
  QSettings userSettings(QSettings::UserScope,organisationName,applicationName);
  bool returnValue = false;
  qWarning()<< __func__ << " Not yet implemented\n";
    qDebug() << "Read systemConfig";
    currentSettings.systemConfig.useSystemDeamon = systemSettings.value(configNames.systemConfig.useSystemDeamon).toBool();
    systemSettings.beginGroup(configNames.systemConfig.systemDeamon.name);
    currentSettings.systemConfig.systemDeamon.externalListenPort = systemSettings.value(configNames.systemConfig.systemDeamon.externalListenPort).toInt();
    currentSettings.systemConfig.systemDeamon.internalCommunicationType = static_cast<Share::Communication::Type>(systemSettings.value(configNames.systemConfig.systemDeamon.internalCommunicationType).toInt());
    currentSettings.systemConfig.systemDeamon.internalListenPort = systemSettings.value(configNames.systemConfig.systemDeamon.internalListenPort).toInt();
    systemSettings.endGroup();
    currentSettings.systemConfig.useUserDeamon = systemSettings.value(configNames.systemConfig.useUserDeamon).toBool();
    systemSettings.beginGroup(configNames.systemConfig.userDeamon.name);
    currentSettings.systemConfig.userDeamon.externalCommunicationViaSystemDeamon = systemSettings.value(configNames.systemConfig.userDeamon.externalCommunicationViaSystemDeamon).toInt();
    currentSettings.systemConfig.userDeamon.externalListenPort = systemSettings.value(configNames.systemConfig.userDeamon.externalListenPort).toInt();
    currentSettings.systemConfig.userDeamon.internalCommunicationType = static_cast<Share::Communication::Type> (systemSettings.value(configNames.systemConfig.userDeamon.internalCommunicationType).toInt());
    currentSettings.systemConfig.userDeamon.internalListenPort = systemSettings.value(configNames.systemConfig.userDeamon.internalListenPort).toInt();
    systemSettings.endGroup();
    qDebug() << "Read userConfig.";
    currentSettings.userConfig.useSystemConfig = userSettings.value(configNames.userConfig.useSystemConfig).toBool();
    currentSettings.userConfig.useUserDeamon = userSettings.value(configNames.userConfig.useUserDeamon).toBool();
    userSettings.beginGroup(configNames.userConfig.userDeamon.name);
    currentSettings.userConfig.userDeamon.externalListenPort = userSettings.value(configNames.userConfig.userDeamon.externalListenPort).toInt();
    currentSettings.userConfig.userDeamon.internalCommunicationType = static_cast<Share::Communication::Type> (userSettings.value(configNames.userConfig.userDeamon.internalCommunicationType).toInt());
    currentSettings.userConfig.userDeamon.internalListenPort = userSettings.value(configNames.userConfig.userDeamon.internalListenPort).toInt();
    userSettings.endGroup();
    returnValue = true;
  return returnValue;
}

bool Share::Configuration::readConf(QString & p_fileName)
{
  qWarning()<< __func__ << " Not yet implemented\n";
  signalConfig();
  return true;
}


bool Share::Configuration::writeConf()
{
  QSettings systemSettings(QSettings::SystemScope,organisationName,applicationName);
  QSettings userSettings(QSettings::UserScope,organisationName,applicationName);
  bool returnValue = false;
  qWarning()<< __func__ << " Not yet implemented\n";
  if (systemSettings.isWritable())
  {
    qDebug() << "Write systemConfig";
    systemSettings.setValue(configNames.systemConfig.useSystemDeamon,currentSettings.systemConfig.useSystemDeamon);
    systemSettings.beginGroup(configNames.systemConfig.systemDeamon.name);
    systemSettings.setValue(configNames.systemConfig.systemDeamon.externalListenPort,currentSettings.systemConfig.systemDeamon.externalListenPort);
    systemSettings.setValue(configNames.systemConfig.systemDeamon.internalCommunicationType,currentSettings.systemConfig.systemDeamon.internalCommunicationType);
    systemSettings.setValue(configNames.systemConfig.systemDeamon.internalListenPort,currentSettings.systemConfig.systemDeamon.internalListenPort);
    systemSettings.endGroup();
    systemSettings.setValue(configNames.systemConfig.useUserDeamon,currentSettings.systemConfig.useUserDeamon);
    systemSettings.beginGroup(configNames.systemConfig.userDeamon.name);
    systemSettings.setValue(configNames.systemConfig.userDeamon.externalCommunicationViaSystemDeamon,currentSettings.systemConfig.userDeamon.externalCommunicationViaSystemDeamon);
    systemSettings.setValue(configNames.systemConfig.userDeamon.externalListenPort,currentSettings.systemConfig.userDeamon.externalListenPort);
    systemSettings.setValue(configNames.systemConfig.userDeamon.internalCommunicationType,currentSettings.systemConfig.userDeamon.internalCommunicationType);
    systemSettings.setValue(configNames.systemConfig.userDeamon.internalListenPort,currentSettings.systemConfig.userDeamon.internalListenPort);
    systemSettings.endGroup();
    returnValue = true;
  }
  else
  {
    qDebug() << "Write systemConfig not allowed.";
  }
  if (userSettings.isWritable())
  {
    qDebug() << "Write userConfig.";
    userSettings.setValue(configNames.userConfig.useSystemConfig,currentSettings.userConfig.useSystemConfig);
    userSettings.setValue(configNames.userConfig.useUserDeamon,currentSettings.userConfig.useUserDeamon);
    userSettings.beginGroup(configNames.userConfig.userDeamon.name);
    userSettings.setValue(configNames.userConfig.userDeamon.externalListenPort,currentSettings.userConfig.userDeamon.externalListenPort);
    userSettings.setValue(configNames.userConfig.userDeamon.internalCommunicationType,currentSettings.userConfig.userDeamon.internalCommunicationType);
    userSettings.setValue(configNames.userConfig.userDeamon.internalListenPort,currentSettings.userConfig.userDeamon.internalListenPort);
    userSettings.endGroup();
    returnValue = true;
  }
  else
  {
    qDebug() << "Write userConfig not allowed.";
  }
  return returnValue;
}

bool  Share::Configuration::writeConf(QString & p_fileName)
{
  qWarning()<< __func__ << " Not yet implemented\n";
  return true;
}


void Share::Configuration::setSystem_SystemDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.systemConfig.useSystemDeamon == p_activated)
     return;
  currentSettings.systemConfig.useSystemDeamon = p_activated;
  emit changeSystem_SystemDeamon(p_activated);
}

void Share::Configuration::setSystem_UserDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.systemConfig.useUserDeamon == p_activated)
     return;
  currentSettings.systemConfig.useUserDeamon = p_activated;
  emit changeSystem_UserDeamon(p_activated);
}

void Share::Configuration::setSystem_SystemListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.externalListenPort == p_listenPort)
     return;
  currentSettings.systemConfig.systemDeamon.externalListenPort = p_listenPort;
  emit changeSystem_SystemListenPort(p_listenPort);
}

void Share::Configuration::setSystem_SystemCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.internalCommunicationType == p_mode)
     return;
  currentSettings.systemConfig.systemDeamon.internalCommunicationType = p_mode;
  emit changeSystem_SystemCommunicationMode(p_mode);
}

void Share::Configuration::setSystem_SystemLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.internalListenPort == p_listenPort)
     return;
  currentSettings.systemConfig.systemDeamon.internalListenPort = p_listenPort;
  emit changeSystem_SystemLocalListenPort(p_listenPort);
}

void Share::Configuration::setSystem_UserListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.externalListenPort == p_listenPort)
     return;
  currentSettings.systemConfig.userDeamon.externalListenPort = p_listenPort;
  emit changeSystem_UserListenPort(p_listenPort);
}

void Share::Configuration::setSystem_UserCommViaSystemDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.externalCommunicationViaSystemDeamon == p_activated)
     return;
  currentSettings.systemConfig.userDeamon.externalCommunicationViaSystemDeamon = p_activated;
  emit changeSystem_UserCommViaSystemDeamon(p_activated);
}

void Share::Configuration::setSystem_UserCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.internalCommunicationType == p_mode)
     return;
  currentSettings.systemConfig.userDeamon.internalCommunicationType = p_mode;
  emit changeSystem_UserCommunicationMode(p_mode);
}

void Share::Configuration::setSystem_UserLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.internalListenPort == p_listenPort)
     return;
  currentSettings.systemConfig.userDeamon.internalListenPort = p_listenPort;
  emit changeSystem_UserLocalListenPort(p_listenPort);
}

  
void Share::Configuration::setUser_UseSystemSettings(bool p_activated)
{
  debugName;
  if (currentSettings.userConfig.useSystemConfig == p_activated)
     return;
  currentSettings.userConfig.useSystemConfig = p_activated;
  emit changeUser_UseSystemSettings(p_activated);
}

void Share::Configuration::setUser_UserDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.userConfig.useUserDeamon == p_activated)
     return;
  currentSettings.userConfig.useUserDeamon = p_activated;
  emit changeUser_UserDeamon(p_activated);
}

void Share::Configuration::setUser_UserListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.externalListenPort == p_listenPort)
     return;
  currentSettings.userConfig.userDeamon.externalListenPort = p_listenPort;
  emit changeUser_UserListenPort(p_listenPort);
}

void Share::Configuration::setUser_UserCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.internalCommunicationType == p_mode)
     return;
  currentSettings.userConfig.userDeamon.internalCommunicationType = p_mode;
  emit changeUser_UserCommunicationMode(p_mode);
}

void Share::Configuration::setUser_UserLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.internalListenPort == p_listenPort)
     return;
  currentSettings.userConfig.userDeamon.internalListenPort = p_listenPort;
  emit changeUser_UserLocalListenPort(p_listenPort);
}

  
void Share::Configuration::loadConfig()
{
  bool isConfReaded;
  isConfReaded = readConf();
  if (isConfReaded)
    emit signalConfig();
  emit configLoaded(isConfReaded);
}

void Share::Configuration::saveConfig()
{
  bool isConfSaved;
  isConfSaved = writeConf();
  emit configSaved(isConfSaved);
}

  
void Share::Configuration::loadFile(QString & p_fileName)
{
  bool isConfReaded;
  isConfReaded = readConf(p_fileName);
  emit configLoaded(isConfReaded);
}

void Share::Configuration::saveFile(QString & p_fileName)
{
  bool isConfSaved;
  isConfSaved = writeConf(p_fileName);
  emit configSaved(isConfSaved);
}

void Share::Configuration::getConfig()
{
  signalConfig();
}
  
void Share::Configuration::signalConfig()
{
  emit changeSystem_SystemDeamon(currentSettings.systemConfig.useSystemDeamon);
  emit changeSystem_UserDeamon(currentSettings.systemConfig.useUserDeamon);
  emit changeSystem_SystemListenPort(currentSettings.systemConfig.systemDeamon.externalListenPort);
  emit changeSystem_SystemCommunicationMode(currentSettings.systemConfig.systemDeamon.internalCommunicationType);
  emit changeSystem_SystemLocalListenPort(currentSettings.systemConfig.systemDeamon.internalListenPort);
  emit changeSystem_UserCommViaSystemDeamon(currentSettings.systemConfig.userDeamon.externalCommunicationViaSystemDeamon);
  emit changeSystem_UserListenPort(currentSettings.systemConfig.userDeamon.externalListenPort);
  emit changeSystem_UserCommunicationMode(currentSettings.systemConfig.userDeamon.internalCommunicationType);
  emit changeSystem_UserLocalListenPort(currentSettings.systemConfig.userDeamon.internalListenPort);
  emit changeUser_UseSystemSettings(currentSettings.userConfig.useSystemConfig);
  emit changeUser_UserListenPort(currentSettings.userConfig.userDeamon.externalListenPort);
  emit changeUser_UserDeamon(currentSettings.userConfig.useUserDeamon);
  emit changeUser_UserCommunicationMode(currentSettings.userConfig.userDeamon.internalCommunicationType);
  emit changeUser_UserLocalListenPort(currentSettings.userConfig.userDeamon.internalListenPort);
}
