/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v..
///
/// This file implements the main Share::Configuration class.

#include "ShareConfiguration.h"
#include <ShareCommunicationNetwork.h>

#define debugName qDebug() << "Conf:" << __func__


#if 0
const Share::Configuration::Config Share::Configuration::defaultSettings = {
  .systemConfig = {
    .useSystemDeamon = false,
    .useUserDeamon = false,
    .systemDeamon = {
      .externalListenPort = Share::CommunicationNetwork::s_defaultAdminPortNumber,
      .internalCommunicationType = Share::Communication::DBUS,
      .internalListenPort = Share::CommunicationNetwork::s_defaultAdminPortNumber,
    },
    .userDeamon = {
      .externalCommunicationViaSystemDeamon = false,
      .externalListenPort = Share::CommunicationNetwork::s_defaultUserPortNumber,
      .internalCommunicationType = Share::Communication::DBUS,
      .internalListenPort = Share::CommunicationNetwork::s_defaultUserPortNumber,
    },
  },
  .userConfig = {
    .useSystemConfig = false,
    .useUserDeamon = true,
    .userDeamon = {
      .externalListenPort = Share::CommunicationNetwork::s_defaultUserPortNumber,
      .internalCommunicationType = Share::Communication::DBUS,
      .internalListenPort = Share::CommunicationNetwork::s_defaultUserPortNumber,
    },
  },
};
#else
#warning Not nominal configuration
const Share::Configuration::Config Share::Configuration::defaultSettings = {
  { false, false,
    { Share::CommunicationNetwork::s_defaultAdminPortNumber+1,
      Share::Communication::SHARE_MEM,
      Share::CommunicationNetwork::s_defaultAdminPortNumber-1,
    },
    {
      false,
      Share::CommunicationNetwork::s_defaultUserPortNumber+1,
      Share::Communication::NETWORK,
      Share::CommunicationNetwork::s_defaultUserPortNumber-1,
    },
  },
  {
    false, true,
    {
      Share::CommunicationNetwork::s_defaultUserPortNumber+2,
      Share::Communication::SHARE_MEM,
      Share::CommunicationNetwork::s_defaultUserPortNumber-2,
    },
  },
};
#endif

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
  qWarning()<< __func__ << " Not yet implemented\n";
  signalConfig();
  return true;
}

bool Share::Configuration::readConf(QString & p_fileName)
{
  qWarning()<< __func__ << " Not yet implemented\n";
  signalConfig();
  return true;
}


bool Share::Configuration::writeConf()
{
  qWarning()<< __func__ << " Not yet implemented\n";
  return true;
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
