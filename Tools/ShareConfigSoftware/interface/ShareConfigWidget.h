/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file contains the definition of main widget for configuration software.

#include <QtGui>
#include <ShareCommunication.h>

/// \brief The main widget class for the Share config software.
class ShareConfigWidget: public QWidget
{
  Q_OBJECT

public:
  /// \brief Constructor
  ShareConfigWidget(QWidget* parent = 0);

  /// \brief Destructor
  virtual ~ShareConfigWidget();

signals:
  /// \brief Signal a change of the System deamon value of the system configuration file.
  void changeSystemSystemDeamon(bool p_isActivated);
  /// \brief Signal a change of the User deamon value of the system configuration file.
  void changeSystemUserDeamon(bool p_isActivated);
  /// \brief Signal a change of the value of the listen port of the System deamon of the system configuration file.
  void changeSystemSystemListenPort(int p_listenPort);
  /// \brief Signal a change of the internal communication mode for library or user deamon to the system deamon.
  void changeSystemSystemCommunicationMode(Share::Communication::Type p_commType);
  /// \brief Signal a change of the internal communication mode for library or user deamon to the system deamon.
  void changeSystemSystemCommunicationMode(int p_commType);
  /// \brief Signal a change of the local listen port for System deamon of the system configuration file.
  void changeSystemSystemLocalListenPort(int p_listenPort);
  /// \brief Signal a change of the system cache path of the system configuration file.
  void changeSystemSystemCachePath(QString p_path);
  /// \brief Signal a change of the max system cache size of the system configuration file (in GB).
  void changeSystemSystemCacheQuota(int p_size);
  /// \brief Signal a change of the user deamon external listen port of the system configuration file.
  void changeSystemUserListenPort(int p_listenPort);
  /// \brief Signal a change of the flag that define the way to connect with external peers of the system configuration file.
  void changeSystemUserCommViaSystemDeamon(bool p_activated);
  /// \brief Set the internal communication mode for library to user deamon.
  void changeSystemUserCommunicationMode(Share::Communication::Type p_commType);
  /// \brief Set the internal communication mode for library to user deamon.
  void changeSystemUserCommunicationMode(int p_commType);
  /// \brief Signal a change of the local listen port for User deamon of the system configuration file.
  void changeSystemUserLocalListenPort(int p_listenPort);
  /// \brief Signal a change of the user cache path of the system configuration file.
  void changeSystemUserCachePath(QString p_path);
  /// \brief Signal a change of the max user cache size of the system configuration file (in GB).
  void changeSystemUserCacheQuota(int p_size);

  /// \brief Signal a change of the user flag which define if the process use the System configuration or an overwrite configuration.
  void changeUserUseSystemSettings(bool b_useSystemSettings);
  /// \brief Signal a change of the user deamon flag of the user configuration file.
  void changeUserUserDeamon(bool p_isActivated);
  /// \brief Signal a change of the external listen port for the user deamon.
  void changeUserUserListenPort(int p_listenPort);
  /// \brief Signal a change of the internal communication mode for library to user deamon.
  void changeUserUserCommunicationMode(Share::Communication::Type p_commType);
  /// \brief Signal a change of the internal communication mode for library to user deamon.
  void changeUserUserCommunicationMode(int p_commType);
  /// \brief Signal a change of the local listen port for User deamon of the system configuration file.
  void changeUserUserLocalListenPort(int p_listenPort);
  /// \brief Signal a change of the user cache path of the user configuration file.
  void changeUserUserCachePath(QString p_path);
  /// \brief Signal a change of the max user cache size of the user configuration file (in GB).
  void changeUserUserCacheQuota(int p_size);

  void activateSystemSystemPortBox(bool p_activate);
  void activateSystemUserListenPortBox(bool p_activate);
  void activateSystemUserPortBox(bool p_activate);
  void activateUserUserPortBox(bool p_activate);
  void activateUserUserListenPortBox(bool p_activate);
  void activateApplyButton(bool p_activate);

  /// \brief Signal that the configuration is valid and should be saved.
  void validateConfig();

  /// \brief Signal that user want to quit software.
  void quitRequest();

public slots:
  /// \brief Set the System deamon value of the system configuration file.
  void setSystemSystemDeamon(bool p_isActivated);
  /// \brief Set the User deamon value of the system configuration file.
  void setSystemUserDeamon(bool p_isActivated);
  /// \brief Set the value of the listen port of the System deamon of the system configuration file.
  void setSystemSystemListenPort(int p_listenPort);
  /// \brief Set the internal communication mode for library or user deamon to the system deamon.
  void setSystemSystemCommunicationMode(Share::Communication::Type p_mode);
  /// \brief Set the local listen port for System deamon of the system configuration file.
  void setSystemSystemCommunicationMode(int p_commType);
  /// \brief Set the local listen port for System deamon of the system configuration file.
  void setSystemSystemLocalListenPort(int p_listenPort);
  /// \brief Set the System cache path of the system configuration file.
  void setSystemSystemCachePath(QString p_path);
  /// \brief Set the System max cache size of the system configuration file (in GB).
  void setSystemSystemCacheQuota(int p_maxSize);
  /// \brief Set the user deamon external listen port of the system configuration file.
  void setSystemUserListenPort(int p_listenPort);
  /// \brief Set the flag that define the way to connect with external peers of the system configuration file.
  void setSystemUserCommViaSystemDeamon(bool p_activate);
  /// \brief Set the internal communication mode for library to user deamon.
  void setSystemUserCommunicationMode(Share::Communication::Type p_commType);
  /// \brief Set the internal communication mode for library to user deamon.
  void setSystemUserCommunicationMode(int p_commType);
  /// \brief Set the local listen port for User deamon of the system configuration file.
  void setSystemUserLocalListenPort(int p_listenPort);
  /// \brief Set the User cache path of the system configuration file.
  void setSystemUserCachePath(QString p_path);
  /// \brief Set the System max cache size of the system configuration file (in GB).
  void setSystemUserCacheQuota(int p_maxSize);

  /// \brief Set the user flag which define if the process use the System configuration or an overwrite configuration.
  void setUserUseSystemSettings(bool b_useSystemSettings);
  /// \brief Set the user deamon flag of the user configuration file.
  void setUserUserDeamon(bool p_isActivated);
  /// \brief Set the external listen port for the user deamon.
  void setUserUserListenPort(int p_listenPort);
  /// \brief Set the internal communication mode for library to user deamon.
  void setUserUserCommunicationMode(Share::Communication::Type p_commType);
  /// \brief Set the internal communication mode for library to user deamon.
  void setUserUserCommunicationMode(int p_commType);
  /// \brief Set the local listen port for User deamon of the system configuration file.
  void setUserUserLocalListenPort(int p_listenPort);
  /// \brief Set the User cache path of the user configuration file.
  void setUserUserCachePath(QString p_path);
  /// \brief Set the User max cache size of the user configuration file (in GB).
  void setUserUserCacheQuota(int p_maxSize);

  /// \brief The slot inform widget if the config has been saved.
  void configSaved(bool p_isConfSaved);
  /// \brief The slot inform widget if the config has been loaded.
  void configLoaded(bool p_isConfLoaded);
private slots:
  /// \brief Slot for click on Ok button.
  void okButton();
  /// \brief Slot for click on Cancel button.
  void cancelButton();
  /// \brief Slot for click on Apply button.
  void applyButton();
  /// \brief Slot for click on system select directory button of system tab.
  void selectSystemSystemCachePath();
  /// \brief Slot for click on user select directory button of system tab.
  void selectSystemUserCachePath();
  /// \brief Slot for click on user select directory button of user tab.
  void selectUserUserCachePath();

private:
  /// \brief Method that create the widget in “system” tab.
  QWidget * createSystemWidget();
  /// \brief Method that create the widget in “user” tab.
  QWidget * createUserWidget();

  /// \brief The tab widget.
  QTabWidget *m_tab;
  /// \brief Cache of Configuration path.
  QString m_systemSystemPath;
  /// \brief Cache of Configuration path.
  QString m_systemUserPath;
  /// \brief Cache of Configuration path.
  QString m_userUserPath;
};
