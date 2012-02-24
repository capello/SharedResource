/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main Share::Configuration class.

#include "ShareConfiguration.h"
#include <ShareCommunicationNetwork.h>
#include <ShareDebug.h>
#include <QtCore>


#define debugName WHERE


const QString Share::Configuration::organisationName = "CapProject";
const QString Share::Configuration::applicationName = "libShareResource";
const Share::Configuration::Config Share::Configuration::defaultSettings = {
  /* .systemConfig */ {
    { QString("enableSystemDeamon"),false },
    { QString("systemCachePath"),QString("/var/cache/") + organisationName + QString("/") + applicationName },
    { QString("systemCacheMaxSize"),2},
    { QString("systemDeamon"), {
      { QString("externalListenPort"),Share::CommunicationNetwork::s_defaultAdminPortNumber },
      { QString("internalCommunicationType"),Share::Communication::DBUS },
      { QString("internalListenPort"),Share::CommunicationNetwork::s_defaultAdminPortNumber },
    } },
    { QString("enableUserDeamon"),true },
    { QString("userCachePath"),QString("~/.local/share/") + organisationName + QString("/") + applicationName },
    { QString("userCacheMaxSize"),1},
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
    { QString("userCachePath"),QString("~/.local/share/") + organisationName + QString("/") + applicationName },
    { QString("userCacheMaxSize"),1},
    { QString("userDeamon"),{
      { QString("externalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
      { QString("internalCommunicationType"),Share::Communication::DBUS },
      { QString("internalListenPort"),Share::CommunicationNetwork::s_defaultUserPortNumber },
    } },
  },
};

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
  WHERE;
  QSettings l_systemSettings(QSettings::SystemScope,organisationName,applicationName);
  QSettings l_userSettings(QSettings::UserScope,organisationName,applicationName);
  bool l_returnValue = false;
    qDebug() << "Read systemConfig";
    currentSettings.systemConfig.useSystemDeamon.value = l_systemSettings.value(currentSettings.systemConfig.useSystemDeamon.name).toBool();
    currentSettings.systemConfig.systemCachePath.value = l_systemSettings.value(currentSettings.systemConfig.systemCachePath.name).toString();
    currentSettings.systemConfig.systemCacheQuota.value = l_systemSettings.value(currentSettings.systemConfig.systemCacheQuota.name).toInt();
    l_systemSettings.beginGroup(currentSettings.systemConfig.systemDeamon.name);
    currentSettings.systemConfig.systemDeamon.value.externalListenPort.value = l_systemSettings.value(currentSettings.systemConfig.systemDeamon.value.externalListenPort.name).toInt();
    currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type>(l_systemSettings.value(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.systemConfig.systemDeamon.value.internalListenPort.value = l_systemSettings.value(currentSettings.systemConfig.systemDeamon.value.internalListenPort.name).toInt();
    l_systemSettings.endGroup();
    currentSettings.systemConfig.useUserDeamon.value = l_systemSettings.value(currentSettings.systemConfig.useUserDeamon.name).toBool();
    currentSettings.systemConfig.userCachePath.value = l_systemSettings.value(currentSettings.systemConfig.userCachePath.name).toString();
    currentSettings.systemConfig.userCacheQuota.value = l_systemSettings.value(currentSettings.systemConfig.userCacheQuota.name).toInt();
    l_systemSettings.beginGroup(currentSettings.systemConfig.userDeamon.name);
    currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value = l_systemSettings.value(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.name).toInt();
    currentSettings.systemConfig.userDeamon.value.externalListenPort.value = l_systemSettings.value(currentSettings.systemConfig.userDeamon.value.externalListenPort.name).toInt();
    currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type> (l_systemSettings.value(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.systemConfig.userDeamon.value.internalListenPort.value = l_systemSettings.value(currentSettings.systemConfig.userDeamon.value.internalListenPort.name).toInt();
    l_systemSettings.endGroup();
    qDebug() << "Read userConfig.";
    currentSettings.userConfig.useSystemConfig.value = l_userSettings.value(currentSettings.userConfig.useSystemConfig.name).toBool();
    currentSettings.userConfig.useUserDeamon.value = l_userSettings.value(currentSettings.userConfig.useUserDeamon.name).toBool();
    currentSettings.userConfig.userCachePath.value = l_userSettings.value(currentSettings.userConfig.userCachePath.name).toString();
    currentSettings.userConfig.userCacheQuota.value = l_userSettings.value(currentSettings.userConfig.userCacheQuota.name).toInt();
    l_userSettings.beginGroup(currentSettings.userConfig.userDeamon.name);
    currentSettings.userConfig.userDeamon.value.externalListenPort.value = l_userSettings.value(currentSettings.userConfig.userDeamon.value.externalListenPort.name).toInt();
    currentSettings.userConfig.userDeamon.value.internalCommunicationType.value = static_cast<Share::Communication::Type> (l_userSettings.value(currentSettings.userConfig.userDeamon.value.internalCommunicationType.name).toInt());
    currentSettings.userConfig.userDeamon.value.internalListenPort.value = l_userSettings.value(currentSettings.userConfig.userDeamon.value.internalListenPort.name).toInt();
    l_userSettings.endGroup();
    l_returnValue = true;
  return l_returnValue;
}

bool Share::Configuration::readConf(QString & p_fileName)
{
  WHERE;
  NOT_IMPLEMENTED;
  return true;
}


bool Share::Configuration::writeConf()
{
  WHERE;
  QSettings l_systemSettings(QSettings::SystemScope,organisationName,applicationName);
  QSettings l_userSettings(QSettings::UserScope,organisationName,applicationName);
  bool l_returnValue = false;
  if (l_systemSettings.isWritable())
  {
    qDebug() << "Write systemConfig";
    l_systemSettings.setValue(currentSettings.systemConfig.useSystemDeamon.name,currentSettings.systemConfig.useSystemDeamon.value);
    l_systemSettings.setValue(currentSettings.systemConfig.systemCachePath.name,currentSettings.systemConfig.systemCachePath.value);
    l_systemSettings.setValue(currentSettings.systemConfig.systemCacheQuota.name,currentSettings.systemConfig.systemCacheQuota.value);
    l_systemSettings.beginGroup(currentSettings.systemConfig.systemDeamon.name);
    l_systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.externalListenPort.name,currentSettings.systemConfig.systemDeamon.value.externalListenPort.value);
    l_systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.name,currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value);
    l_systemSettings.setValue(currentSettings.systemConfig.systemDeamon.value.internalListenPort.name,currentSettings.systemConfig.systemDeamon.value.internalListenPort.value);
    l_systemSettings.endGroup();
    l_systemSettings.setValue(currentSettings.systemConfig.useUserDeamon.name,currentSettings.systemConfig.useUserDeamon.value);
    l_systemSettings.setValue(currentSettings.systemConfig.userCachePath.name,currentSettings.systemConfig.userCachePath.value);
    l_systemSettings.setValue(currentSettings.systemConfig.userCacheQuota.name,currentSettings.systemConfig.userCacheQuota.value);
    l_systemSettings.beginGroup(currentSettings.systemConfig.userDeamon.name);
    l_systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.name,currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value);
    l_systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.externalListenPort.name,currentSettings.systemConfig.userDeamon.value.externalListenPort.value);
    l_systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.name,currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value);
    l_systemSettings.setValue(currentSettings.systemConfig.userDeamon.value.internalListenPort.name,currentSettings.systemConfig.userDeamon.value.internalListenPort.value);
    l_systemSettings.endGroup();
    l_returnValue = true;
  }
  else
  {
    qDebug() << "Write systemConfig not allowed.";
  }
  if (l_userSettings.isWritable())
  {
    qDebug() << "Write userConfig.";
    l_userSettings.setValue(currentSettings.userConfig.useSystemConfig.name,currentSettings.userConfig.useSystemConfig.value);
    l_userSettings.setValue(currentSettings.userConfig.useUserDeamon.name,currentSettings.userConfig.useUserDeamon.value);
    l_userSettings.setValue(currentSettings.userConfig.userCachePath.name,currentSettings.userConfig.userCachePath.value);
    l_userSettings.setValue(currentSettings.userConfig.userCacheQuota.name,currentSettings.userConfig.userCacheQuota.value);
    l_userSettings.beginGroup(currentSettings.userConfig.userDeamon.name);
    l_userSettings.setValue(currentSettings.userConfig.userDeamon.value.externalListenPort.name,currentSettings.userConfig.userDeamon.value.externalListenPort.value);
    l_userSettings.setValue(currentSettings.userConfig.userDeamon.value.internalCommunicationType.name,currentSettings.userConfig.userDeamon.value.internalCommunicationType.value);
    l_userSettings.setValue(currentSettings.userConfig.userDeamon.value.internalListenPort.name,currentSettings.userConfig.userDeamon.value.internalListenPort.value);
    l_userSettings.endGroup();
    l_returnValue = true;
  }
  else
  {
    qDebug() << "Write userConfig not allowed.";
  }
  return l_returnValue;
}

bool  Share::Configuration::writeConf(QString & p_fileName)
{
  WHERE;
  NOT_IMPLEMENTED;
  return true;
}

Share::Communication::Type Share::Configuration::getSystem_SystemCommunicationMode()
{
  return currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value;
}


bool Share::Configuration::getUser_UseSystemConfig()
{
  return currentSettings.userConfig.useSystemConfig.value;
}

Share::Communication::Type Share::Configuration::getSystem_UserCommunicationMode()
{
  return currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value;
}

Share::Communication::Type Share::Configuration::getUser_UserCommunicationMode()
{
  return currentSettings.userConfig.userDeamon.value.internalCommunicationType.value;
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

void Share::Configuration::setSystem_SystemCacheQuota(int p_maxSize)
{
  WHERE;
  if (currentSettings.systemConfig.systemCacheQuota.value == p_maxSize)
    return;
  currentSettings.systemConfig.systemCacheQuota.value = p_maxSize;
  emit changeSystem_SystemCacheQuota(p_maxSize);
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

void Share::Configuration::setSystem_UserCacheQuota(int p_maxSize)
{
  WHERE;
  if (currentSettings.systemConfig.userCacheQuota.value == p_maxSize)
    return;
  currentSettings.systemConfig.userCacheQuota.value = p_maxSize;
  emit changeSystem_UserCacheQuota(p_maxSize);
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

void Share::Configuration::setUser_UserCachePath(QString p_localCache)
{
  debugName;
  bool l_isRelativeToHome = false;
  if (currentSettings.userConfig.userCachePath.value == p_localCache)
    return;
  // If path is home relative, remove the home part.
  if (p_localCache.indexOf(QDir::homePath()) == 0)
  {
    p_localCache.replace(0,QDir::homePath().length()+1,"");
    l_isRelativeToHome = true;
  }
  currentSettings.userConfig.userCachePath.value = p_localCache;
  if (l_isRelativeToHome)
    emit changeUser_UserCachePath(QDir::homePath() + QString("/") + p_localCache);
  else
    emit changeUser_UserCachePath(p_localCache);
}

void Share::Configuration::setSystem_SystemCachePath(QString p_localCache)
{
  debugName;
  if (currentSettings.systemConfig.systemCachePath.value == p_localCache)
    return;
  currentSettings.systemConfig.systemCachePath.value = p_localCache;
  emit changeSystem_SystemCachePath(p_localCache);
}

void Share::Configuration::setSystem_UserCachePath(QString p_localCache)
{
  debugName;
  bool l_isRelativeToHome = false;
  if (currentSettings.systemConfig.userCachePath.value == p_localCache)
    return;
  // If path is home relative, remove the home part.
  if (p_localCache.indexOf(QDir::homePath()) == 0)
  {
    p_localCache.replace(0,QDir::homePath().length()+1,"");
    l_isRelativeToHome = true;
  }
  currentSettings.systemConfig.userCachePath.value = p_localCache;
  if (l_isRelativeToHome)
    emit changeSystem_UserCachePath(QDir::homePath() + QString("/") + p_localCache);
  else
    emit changeSystem_UserCachePath(p_localCache);
}

void Share::Configuration::setUser_UserCacheQuota(int p_maxSize)
{
  WHERE;
  if (currentSettings.userConfig.userCacheQuota.value == p_maxSize)
    return;
  currentSettings.userConfig.userCacheQuota.value = p_maxSize;
  emit changeUser_UserCacheQuota(p_maxSize);
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
  WHERE;
  emit changeSystem_SystemDeamon(currentSettings.systemConfig.useSystemDeamon.value);
  emit changeSystem_UserDeamon(currentSettings.systemConfig.useUserDeamon.value);
  emit changeSystem_SystemListenPort(currentSettings.systemConfig.systemDeamon.value.externalListenPort.value);
  emit changeSystem_SystemCommunicationMode(currentSettings.systemConfig.systemDeamon.value.internalCommunicationType.value);
  emit changeSystem_SystemLocalListenPort(currentSettings.systemConfig.systemDeamon.value.internalListenPort.value);
  emit changeSystem_SystemCachePath(currentSettings.systemConfig.systemCachePath.value);
  emit changeSystem_SystemCacheQuota(currentSettings.systemConfig.systemCacheQuota.value);
  emit changeSystem_UserCommViaSystemDeamon(currentSettings.systemConfig.userDeamon.value.externalCommunicationViaSystemDeamon.value);
  emit changeSystem_UserListenPort(currentSettings.systemConfig.userDeamon.value.externalListenPort.value);
  emit changeSystem_UserCommunicationMode(currentSettings.systemConfig.userDeamon.value.internalCommunicationType.value);
  emit changeSystem_UserLocalListenPort(currentSettings.systemConfig.userDeamon.value.internalListenPort.value);
  emit changeSystem_UserCachePath(currentSettings.systemConfig.userCachePath.value);
  emit changeSystem_UserCacheQuota(currentSettings.systemConfig.userCacheQuota.value);
  emit changeUser_UseSystemSettings(currentSettings.userConfig.useSystemConfig.value);
  emit changeUser_UserListenPort(currentSettings.userConfig.userDeamon.value.externalListenPort.value);
  emit changeUser_UserDeamon(currentSettings.userConfig.useUserDeamon.value);
  emit changeUser_UserCommunicationMode(currentSettings.userConfig.userDeamon.value.internalCommunicationType.value);
  emit changeUser_UserLocalListenPort(currentSettings.userConfig.userDeamon.value.internalListenPort.value);
  emit changeUser_UserCachePath(currentSettings.userConfig.userCachePath.value);
  emit changeUser_UserCacheQuota(currentSettings.userConfig.userCacheQuota.value);
}

QString Share::Configuration::getCachePath()
{
  QString l_path;
  if (currentSettings.userConfig.useSystemConfig.value)
    l_path = currentSettings.systemConfig.userCachePath.value;
  l_path = currentSettings.userConfig.userCachePath.value;
  QDir l_dir(l_path);
  // If is a relative path, add home path.
  if (!l_dir.isAbsolute())
    l_path = QDir::homePath() + QString("/") + l_path;
  return l_path;
}

QString Share::Configuration::getSystemCachePath()
{
  return currentSettings.systemConfig.systemCachePath.value;
}
