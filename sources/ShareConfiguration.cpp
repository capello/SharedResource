/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main Share::Configuration class.

#include "ShareConfiguration.h"
#include <ShareCommunicationNetwork.h>

#define debugName qDebug() << "Conf:" << __func__


const Share::Configuration::Config Share::Configuration::defaultSettings = {
  /* .systemConfig */ { 
    { QString("enableSystemDeamon"),false }, 
    { QString("systemDeamon"), {
      { QString("externalListenPort"),Share::CommunicationNetwork::s_defaultAdminPortNumber },
      { QString("internalCommunicationType"),Share::Communication::DBUS },
      { QString("internalListenPort"),Share::CommunicationNetwork::s_defaultAdminPortNumber },
    } },
    { QString("enableUserDeamon"),true },
    { QString("userDeamon"),{
      { QString("externalCommunicationViaSystemDeamon"),false},
      { QString("externalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
      { QString("internalCommunicationType"),Share::Communication::DBUS },
      { QString("internalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
    } },
  },
  /* .userConfig */ {
    { QString("useSystemConfig"),false }, 
    { QString("enableUserDeamon"),true },
    { QString("userDeamon"),{
      { QString("externalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
      { QString("internalCommunicationType"),Share::Communication::DBUS },
      { QString("internalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
    } },
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
    qDebug() << "Read systemConfig";
    currentSettings.systemConfig.useSystemDeamon.value = systemSettings.value(currentSettings.systemConfig.useSystemDeamon.name).toBool();
    systemSettings.beginGroup(currentSettings.systemConfig.systemDeamon.name);
    currentSettings.systemConfig.systemDeamon.value.externalListenPort.value = systemSettings.value(currentSettings.systemConfig.systemDeamon.value.externalListenPort.name).toInt();
    currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type>(systemSettings.value(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.systemConfig.systemDeamon.value.internalListenPort.value = systemSettings.value(currentSettings.systemConfig.systemDeamon.value.internalListenPort.name).toInt();
    systemSettings.endGroup();
    currentSettings.systemConfig.useUserDeamon.value = systemSettings.value(currentSettings.systemConfig.useUserDeamon.name).toBool();
    systemSettings.beginGroup(currentSettings.systemConfig.userDeamon.name);
    currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value = systemSettings.value(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.name).toInt();
    currentSettings.systemConfig.userDeamon.value.externalListenPort.value = systemSettings.value(currentSettings.systemConfig.userDeamon.value.externalListenPort.name).toInt();
    currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type> (systemSettings.value(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.systemConfig.userDeamon.value.internalListenPort.value = systemSettings.value(currentSettings.systemConfig.userDeamon.value.internalListenPort.name).toInt();
    systemSettings.endGroup();
    qDebug() << "Read userConfig.";
    currentSettings.userConfig.useSystemConfig.value = userSettings.value(currentSettings.userConfig.useSystemConfig.name).toBool();
    currentSettings.userConfig.useUserDeamon.value = userSettings.value(currentSettings.userConfig.useUserDeamon.name).toBool();
    userSettings.beginGroup(currentSettings.userConfig.userDeamon.name);
    currentSettings.userConfig.userDeamon.value.externalListenPort.value = userSettings.value(currentSettings.userConfig.userDeamon.value.externalListenPort.name).toInt();
    currentSettings.userConfig.userDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type> (userSettings.value(currentSettings.userConfig.userDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.userConfig.userDeamon.value.internalListenPort.value = userSettings.value(currentSettings.userConfig.userDeamon.value.internalListenPort.name).toInt();
    userSettings.endGroup();
    returnValue = true;
  return returnValue;
}

bool Share::Configuration::readConf(QString & p_fileName)
{
  qWarning()<< __func__ << " Not yet implemented\n";
  return true;
}


bool Share::Configuration::writeConf()
{
  QSettings systemSettings(QSettings::SystemScope,organisationName,applicationName);
  QSettings userSettings(QSettings::UserScope,organisationName,applicationName);
  bool returnValue = false;
  if (systemSettings.isWritable())
  {
    qDebug() << "Write systemConfig";
    systemSettings.setValue(currentSettings.systemConfig.useSystemDeamon.name,currentSettings.systemConfig.useSystemDeamon.value);
    systemSettings.beginGroup(currentSettings.systemConfig.systemDeamon.name);
    systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.externalListenPort.name,currentSettings.systemConfig.systemDeamon.value.externalListenPort.value);
    systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.name,currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value);
    systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.internalListenPort.name,currentSettings.systemConfig.systemDeamon.value.internalListenPort.value);
    systemSettings.endGroup();
    systemSettings.setValue(currentSettings.systemConfig.useUserDeamon.name,currentSettings.systemConfig.useUserDeamon.value);
    systemSettings.beginGroup(currentSettings.systemConfig.userDeamon.name);
    systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.name,currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value);
    systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.externalListenPort.name,currentSettings.systemConfig.userDeamon.value.externalListenPort.value);
    systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.name,currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value);
    systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.internalListenPort.name,currentSettings.systemConfig.userDeamon.value.internalListenPort.value);
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
    userSettings.setValue(currentSettings.userConfig.useSystemConfig.name,currentSettings.userConfig.useSystemConfig.value);
    userSettings.setValue(currentSettings.userConfig.useUserDeamon.name,currentSettings.userConfig.useUserDeamon.value);
    userSettings.beginGroup(currentSettings.userConfig.userDeamon.name);
    userSettings.setValue(currentSettings.userConfig.userDeamon.value.externalListenPort.name,currentSettings.userConfig.userDeamon.value.externalListenPort.value);
    userSettings.setValue(currentSettings.userConfig.userDeamon.value.internalCommunicationType.name,currentSettings.userConfig.userDeamon.value.internalCommunicationType.value);
    userSettings.setValue(currentSettings.userConfig.userDeamon.value.internalListenPort.name,currentSettings.userConfig.userDeamon.value.internalListenPort.value);
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
  if (currentSettings.systemConfig.useSystemDeamon.value == p_activated)
     return;
  currentSettings.systemConfig.useSystemDeamon.value = p_activated;
  emit changeSystem_SystemDeamon(p_activated);
}

void Share::Configuration::setSystem_UserDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.systemConfig.useUserDeamon.value == p_activated)
     return;
  currentSettings.systemConfig.useUserDeamon.value = p_activated;
  emit changeSystem_UserDeamon(p_activated);
}

void Share::Configuration::setSystem_SystemListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.value.externalListenPort.value == p_listenPort)
     return;
  currentSettings.systemConfig.systemDeamon.value.externalListenPort.value = p_listenPort;
  emit changeSystem_SystemListenPort(p_listenPort);
}

void Share::Configuration::setSystem_SystemCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value == p_mode)
     return;
  currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value = p_mode;
  emit changeSystem_SystemCommunicationMode(p_mode);
}

void Share::Configuration::setSystem_SystemLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.systemDeamon.value.internalListenPort.value == p_listenPort)
     return;
  currentSettings.systemConfig.systemDeamon.value.internalListenPort.value = p_listenPort;
  emit changeSystem_SystemLocalListenPort(p_listenPort);
}

void Share::Configuration::setSystem_UserListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.value.externalListenPort.value == p_listenPort)
     return;
  currentSettings.systemConfig.userDeamon.value.externalListenPort.value = p_listenPort;
  emit changeSystem_UserListenPort(p_listenPort);
}

void Share::Configuration::setSystem_UserCommViaSystemDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value == p_activated)
     return;
  currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value = p_activated;
  emit changeSystem_UserCommViaSystemDeamon(p_activated);
}

void Share::Configuration::setSystem_UserCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value == p_mode)
     return;
  currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value = p_mode;
  emit changeSystem_UserCommunicationMode(p_mode);
}

void Share::Configuration::setSystem_UserLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.systemConfig.userDeamon.value.internalListenPort.value == p_listenPort)
     return;
  currentSettings.systemConfig.userDeamon.value.internalListenPort.value = p_listenPort;
  emit changeSystem_UserLocalListenPort(p_listenPort);
}

  
void Share::Configuration::setUser_UseSystemSettings(bool p_activated)
{
  debugName;
  if (currentSettings.userConfig.useSystemConfig.value == p_activated)
     return;
  currentSettings.userConfig.useSystemConfig.value = p_activated;
  emit changeUser_UseSystemSettings(p_activated);
}

void Share::Configuration::setUser_UserDeamon(bool p_activated)
{
  debugName;
  if (currentSettings.userConfig.useUserDeamon.value == p_activated)
     return;
  currentSettings.userConfig.useUserDeamon.value = p_activated;
  emit changeUser_UserDeamon(p_activated);
}

void Share::Configuration::setUser_UserListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.value.externalListenPort.value == p_listenPort)
     return;
  currentSettings.userConfig.userDeamon.value.externalListenPort.value = p_listenPort;
  emit changeUser_UserListenPort(p_listenPort);
}

void Share::Configuration::setUser_UserCommunicationMode(Share::Communication::Type p_mode)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.value.internalCommunicationType.value == p_mode)
     return;
  currentSettings.userConfig.userDeamon.value.internalCommunicationType.value = p_mode;
  emit changeUser_UserCommunicationMode(p_mode);
}

void Share::Configuration::setUser_UserLocalListenPort(int p_listenPort)
{
  debugName;
  if (currentSettings.userConfig.userDeamon.value.internalListenPort.value == p_listenPort)
     return;
  currentSettings.userConfig.userDeamon.value.internalListenPort.value = p_listenPort;
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
  if (isConfReaded)
    emit signalConfig();
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
  emit changeSystem_SystemDeamon(currentSettings.systemConfig.useSystemDeamon.value);
  emit changeSystem_UserDeamon(currentSettings.systemConfig.useUserDeamon.value);
  emit changeSystem_SystemListenPort(currentSettings.systemConfig.systemDeamon.value.externalListenPort.value);
  emit changeSystem_SystemCommunicationMode(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value);
  emit changeSystem_SystemLocalListenPort(currentSettings.systemConfig.systemDeamon.value.internalListenPort.value);
  emit changeSystem_UserCommViaSystemDeamon(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value);
  emit changeSystem_UserListenPort(currentSettings.systemConfig.userDeamon.value.externalListenPort.value);
  emit changeSystem_UserCommunicationMode(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value);
  emit changeSystem_UserLocalListenPort(currentSettings.systemConfig.userDeamon.value.internalListenPort.value);
  emit changeUser_UseSystemSettings(currentSettings.userConfig.useSystemConfig.value);
  emit changeUser_UserListenPort(currentSettings.userConfig.userDeamon.value.externalListenPort.value);
  emit changeUser_UserDeamon(currentSettings.userConfig.useUserDeamon.value);
  emit changeUser_UserCommunicationMode(currentSettings.userConfig.userDeamon.value.internalCommunicationType.value);
  emit changeUser_UserLocalListenPort(currentSettings.userConfig.userDeamon.value.internalListenPort.value);
}
