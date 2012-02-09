/// \file
/// \brief This Class is used to configure all.
/// \author Anthony Jaguenaud
/// \version v..
///

#ifndef __SHARE_CONFIGURATION_H
#define __SHARE_CONFIGURATION_H

#include <QSettings>
#include "ShareCommunication.h"

namespace Share {
  class Configuration:public QObject
  {
    Q_OBJECT
  private:
    struct Config
    {
      struct 
      {
        bool useSystemDeamon;
        bool useUserDeamon;
        struct
        {
          int externalListenPort;
          Communication::Type internalCommunicationType;
          int internalListenPort;
        } systemDeamon;
        struct
        {
          bool externalCommunicationViaSystemDeamon;
          int externalListenPort;
          Communication::Type internalCommunicationType;
          int internalListenPort;
        } userDeamon;
      } systemConfig;
      struct
      {
        bool useSystemConfig;
        bool useUserDeamon;
        struct
        {
          int externalListenPort;
          Communication::Type internalCommunicationType;
          int internalListenPort;
        } userDeamon;
      } userConfig;
    };
    
  private:
    Configuration(QObject * parent = 0);
    
    ~Configuration();
    
  public:
    static Configuration *getInstance();
    
    bool readConf();
    bool readConf(QString & p_fileName);
    
    bool writeConf();
    bool writeConf(QString & p_fileName);
    
    /// \brief This method, send all signals like if all have been changed.
    void signalConfig();
    
  public slots:
    void setSystem_SystemDeamon(bool p_activated);
    void setSystem_UserDeamon(bool p_activated);
    void setSystem_SystemListenPort(int p_listenPort);
    void setSystem_SystemCommunicationMode(Share::Communication::Type p_mode);
    void setSystem_SystemLocalListenPort(int p_listenPort);
    void setSystem_UserListenPort(int p_listenPort);
    void setSystem_UserCommViaSystemDeamon(bool p_activated);
    void setSystem_UserCommunicationMode(Share::Communication::Type p_mode);
    void setSystem_UserLocalListenPort(int p_listenPort);
    
    void setUser_UseSystemSettings(bool p_activated);
    void setUser_UserDeamon(bool p_activated);
    void setUser_UserListenPort(int p_listenPort);
    void setUser_UserCommunicationMode(Share::Communication::Type p_mode);
    void setUser_UserLocalListenPort(int p_listenPort);
    
    /// \brief This slot resent all signals for change of all flags.
    void getConfig();

    void loadConfig();
    void saveConfig();

    void loadFile(QString & p_fileName);
    void saveFile(QString & p_fileName);
    
    
  signals:
    void configLoaded(bool);
    void configSaved(bool);
    
    void changeSystem_SystemDeamon(bool);
    void changeSystem_UserDeamon(bool);
    void changeSystem_SystemListenPort(int);
    void changeSystem_SystemCommunicationMode(Share::Communication::Type);
    void changeSystem_SystemLocalListenPort(int);
    void changeSystem_UserListenPort(int);
    void changeSystem_UserCommViaSystemDeamon(bool);
    void changeSystem_UserCommunicationMode(Share::Communication::Type);
    void changeSystem_UserLocalListenPort(int);
    void changeUser_UseSystemSettings(bool);
    void changeUser_UserDeamon(bool);
    void changeUser_UserListenPort(int);
    void changeUser_UserLocalListenPort(int);
    void changeUser_UserCommunicationMode(Share::Communication::Type);
    
  private:
    static Configuration instance;
    static const Config defaultSettings;
    QSettings settings;
    Config currentSettings;
  };
  
};

#endif
