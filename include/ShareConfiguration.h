/// \file
/// \brief This Class is used to configure all.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#ifndef __SHARE_CONFIGURATION_H
#define __SHARE_CONFIGURATION_H

#include <QSettings>
#include "ShareCommunication.h"

namespace Share {
  /// \brief Configuration class.
  /// The configuration is separate into two parts:
  /// \li \b System: the system part configured by the computer administrator. 
  /// Contains use of a system deamon, and a user configuration part.
  /// \li \b User: the user part configured by user can overwrite the system configuration for the user part.
  class Configuration:public QObject
  {
    Q_OBJECT
  private:
    /// \brief This class is used to config structure for have keys and values in the same structure.
    template <class T> struct PairValueName
    {
      QString name; ///< Name of the field.
      T value; ///< Value of the field.
    };
    
    /// \brief Internal structure for store current settings.
    struct Config
    {
      struct SystemSystemDeamon
      {
        PairValueName<int> externalListenPort; ///< Network port use to communicate with external peers.
        PairValueName<Communication::Type> internalCommunicationType; ///< Define the internal mode of communication (from user deamon or library).
        PairValueName<int> internalListenPort; ///< Network port use to internal communication.
      };
      struct SystemUserDeamon
      {
        PairValueName<bool> externalCommunicationViaSystemDeamon; ///< User deamon have to send requests through system deamon.
        PairValueName<int> externalListenPort; ///< If user deamon do not connect to external peers through system deamon, set the network port to use.
        PairValueName<Communication::Type> internalCommunicationType; ///< How the library have to connect to the user deamon.
        PairValueName<int> internalListenPort; ///< If the internal communication mode is NETWORK, the user deamon listen this port for communication.
      }; 
      struct UserUserDeamon
      {
        PairValueName<int> externalListenPort; ///< If there is no system deamon, the user deamon listen on this port.
        PairValueName<Communication::Type> internalCommunicationType; ///< How the library connect to the user deamon.
        PairValueName<int> internalListenPort; ///< If the internal communication mode is NETWORK, the user deamen listen this port.
      };
      struct SystemConfig
      {
        PairValueName<bool> useSystemDeamon; ///< Use the system deamon to communicate with peers.
        PairValueName<QString> systemCachePath; ///< System cache file path.
        PairValueName<SystemSystemDeamon> systemDeamon; ///< System deamon configuration.
        PairValueName<bool> useUserDeamon; ///< Use the user deamon to communicate.
        PairValueName<QString> userCachePath; ///< User cache file path.
        PairValueName<SystemUserDeamon> userDeamon; ///< User deamon configuration.
      };
      struct UserConfig
      {
        PairValueName<bool> useSystemConfig; ///< The library or user deamon must use the system configuration. If this value is true, all other are not used.
        PairValueName<bool> useUserDeamon; ///< Use the local deamon.
        PairValueName<QString> userCachePath; ///< User cache file path.
        PairValueName<UserUserDeamon> userDeamon; ///< User deamon configuration.
      };
      
      SystemConfig systemConfig; ///< System part of the configuration.
      UserConfig userConfig; ///< User part of the configuration.
    };
    
  private:
    /// \brief Constructor
    Configuration(QObject * parent = 0);
    
    /// \brief Destructor
    ~Configuration();
    
  public:
    /// \brief Get the uniq instance of the class.
    static Configuration *getInstance();
    
    /// \brief Read the config from standard config files
    bool readConf();
    
    /// \brief Read the config from a user file.
    /// \param[in] p_fileName File name of the file to load.
    bool readConf(QString & p_fileName);
    
    /// \brief Write the config to standard config files
    bool writeConf();
    
    /// \brief Write the config to a user file.
    /// \param[in] p_fileName File name of the file where save config.
    bool writeConf(QString & p_fileName);
    
    /// \brief This method, send all signals like if all have been changed.
    void signalConfig();
    
    /// \brief This method returns the local path cache.
    /// \return \b QString: string containing the path to local cache.
    QString getCachePath();
    
    /// \brief This method returns the system cache path.
    /// \return \b QString: string containing the path to system cache.
    QString getSystemCachePath();
    
    /// \brief This method get the system communication mode of system settings.
    /// \return \b Share::Communication::Type type of current communication.
    Share::Communication::Type getSystem_SystemCommunicationMode();
    
    /// \brief This method get the “use” system config flag of user settings.
    /// \return \b bool the flag.
    bool getUser_UseSystemConfig();
    
    /// \brief This method get the user communication mode of system settings.
    /// \return \b Share::Communication::Type type of current communication.
    Share::Communication::Type getSystem_UserCommunicationMode();
    
    /// \brief This method get the user communication mode of user settings.
    /// \return \b Share::Communication::Type type of current communication.
    Share::Communication::Type getUser_UserCommunicationMode();
    
    
  public slots:
    /// \brief Set the System deamon value of the system configuration file.
    /// \param[in] p_activated \li \b true: System deamon is activated.
    ///                        \li \b false: System deamon is not activated.
    void setSystem_SystemDeamon(bool p_activated);
    /// \brief Set the User deamon value of the system configuration file.
    /// \param[in] p_activated \li \b true: User deamon is activated.
    ///                        \li \b false: User deamon is not activated.
    void setSystem_UserDeamon(bool p_activated);
    /// \brief Set the value of the listen port of the System deamon of the system configuration file.
    /// \param[in] p_listenPort The port to listen.
    void setSystem_SystemListenPort(int p_listenPort);
    /// \brief Set the internal communication mode for library or user deamon to the system deamon.
    /// \param[in] p_mode The mode of communication. See Share::Communication::Type to known values.
    void setSystem_SystemCommunicationMode(Share::Communication::Type p_mode);
    /// \brief Set the local listen port for System deamon of the system configuration file.
    /// \pre Only usefull when the internal communication type is Share::Communication::NETWORK.
    /// \param[in] p_listenPort The port to listen.
    void setSystem_SystemLocalListenPort(int p_listenPort);
    /// \brief Set the user deamon external listen port of the system configuration file.
    /// \pre This value is usefull if the flag “user comm via system deamon” is false.
    /// \param[in] p_listenPort The port to listen.
    void setSystem_UserListenPort(int p_listenPort);
    /// \brief Set the flag that define the way to connect with external peers of the system configuration file.
    /// \param[in] p_activated \li \b true: the user library or deamon must use the system deamon.
    ///                        \li \b false: the user deamon have to connect itself with others peers.
    void setSystem_UserCommViaSystemDeamon(bool p_activated);
    /// \brief Set the internal communication mode for library to user deamon.
    /// \param[in] p_mode The mode of communication. See Share::Communication::Type to known values.
    void setSystem_UserCommunicationMode(Share::Communication::Type p_mode);
    /// \brief Set the local listen port for User deamon of the system configuration file.
    /// \pre Only usefull when the internal communication type is Share::Communication::NETWORK.
    /// \param[in] p_listenPort The port to listen.
    void setSystem_UserLocalListenPort(int p_listenPort);
    /// \brief Set the system cache path of the system configuration file.
    /// \param[in] p_localCachePath The path to set.
    void setSystem_SystemCachePath(QString p_localCachePath);
    
    /// \brief Set the system cache path of the system configuration file.
    /// \param[in] p_localCachePath The path to set.
    void setSystem_UserCachePath(QString p_localCachePath);
    
    
    /// \brief Set the user flag which define if the process use the System configuration or an overwrite configuration.
    /// \param[in] p_activated \li \b true: Use the system configuration.
    ///                        \li \b false: Use the user configuration.
    void setUser_UseSystemSettings(bool p_activated);
    /// \brief Set the user deamon flag of the user configuration file.
    /// \param[in] p_activated \li \b true: Unable user deamon.
    ///                        \li \b false: Disable user deamon.
    void setUser_UserDeamon(bool p_activated);
    /// \brief Set the external listen port for the user deamon.
    /// \param[in] p_listenPort The port to listen.
    void setUser_UserListenPort(int p_listenPort);
    /// \brief Set the internal communication mode for library to user deamon.
    /// \param[in] p_mode The mode of communication. See Share::Communication::Type to known values.
    void setUser_UserCommunicationMode(Share::Communication::Type p_mode);
    /// \brief Set the local listen port for User deamon of the system configuration file.
    /// \pre Only usefull when the internal communication type is Share::Communication::NETWORK.
    /// \param[in] p_listenPort The port to listen.
    void setUser_UserLocalListenPort(int p_listenPort);
    
    /// \brief Set the user cache path of the user configuration file.
    /// \param[in] p_localCachePath The path to set.
    void setUser_UserCachePath(QString p_localCachePath);
    
    
    /// \brief This slot resent all signals for change of all flags.
    void getConfig();

    /// \brief This slot requests to load configuration 
    void loadConfig();
    
    /// \brief This slot requests to save configuration
    void saveConfig();

    /// \brief This slot requests to load configuration from a file.
    /// \param[in] p_fileName File to load
    void loadFile(QString & p_fileName);
    /// \brief This slot requests to save configuration to a file.
    /// \param[in] p_fileName File into save.
    void saveFile(QString & p_fileName);
    
    
  signals:
    /// \brief Signal config has been loaded.
    /// \param[in] p_isLoaded \li \b true: load succesfull.
    ///                       \li \b false: load fail.
    void configLoaded(bool);
    /// \brief Signal config has been saved.
    /// \param[in] p_isLoaded \li \b true: save succesfull.
    ///                       \li \b false: save fail.
    void configSaved(bool);
    
    /// \brief Signal a change of the system deamon flag of the system settings.
    void changeSystem_SystemDeamon(bool);
    /// \brief Signal a change of the user deamon flag of the system settings.
    void changeSystem_UserDeamon(bool);
    /// \brief Signal a change of the listen port of the system deamon in system settings.
    void changeSystem_SystemListenPort(int);
    /// \brief Signal a change of internal communication mode of the system deamon in system settings.
    void changeSystem_SystemCommunicationMode(Share::Communication::Type);
    /// \brief Signal a change of the local listen port of the system deamon in system settings.
    void changeSystem_SystemLocalListenPort(int);
    /// \brief Signal a change of the external listen port use by the user deamon in system settings.
    void changeSystem_UserListenPort(int);
    /// \brief Signal a change of the flag defining if system deamon have to be used in system settings.
    void changeSystem_UserCommViaSystemDeamon(bool);
    /// \brief Signal a change in local communication mode of the user deamon in system settings.
    void changeSystem_UserCommunicationMode(Share::Communication::Type);
    /// \brief Signal a change of the local listen port of the user deamon in system settings.
    void changeSystem_UserLocalListenPort(int);
    /// \brief Signal a change in the user cache of system settings.
    void changeSystem_UserCachePath(QString p_localCachePath);
    /// \brief Signal a change in the system cache of system settings.
    void changeSystem_SystemCachePath(QString p_localCachePath);
    /// \brief Signal a change of the “use system settings“ in the user settings.
    void changeUser_UseSystemSettings(bool);
    /// \brief Signal a change of the user deamon flag of the user settings.
    void changeUser_UserDeamon(bool);
    /// \brief Signal a change of the external listen port use by the user deamon in user settings.
    void changeUser_UserListenPort(int);
    /// \brief Signal a change of the local listen port of the user deamon in user settings.
    void changeUser_UserLocalListenPort(int);
    /// \brief Signal a change in local communication mode of the user deamon in user settings.
    void changeUser_UserCommunicationMode(Share::Communication::Type);
    /// \brief Signal a change in the user cache of user settings.
    void changeUser_UserCachePath(QString p_localCachePath);
    
  private:
    /// \brief Static instance of the configuration class.
    static Configuration instance;
    /// \brief Default settings.
    static const Config defaultSettings;
    /// \brief The organisation name.
    static const QString organisationName;
    /// \brief The application name.
    static const QString applicationName;
    /// \brief The current settings.
    Config currentSettings;
  };
  
};

#endif
