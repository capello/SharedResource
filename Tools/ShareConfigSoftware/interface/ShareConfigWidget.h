/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file contains the definition of main widget for configuration software.

#include <QtGui>

enum communicationType 
{
  DBUS,
  SHARE_MEM,
  NETWORK
};

class ShareConfigWidget: public QWidget
{
  Q_OBJECT
  
public:
  ShareConfigWidget(QWidget* parent = 0);
    
  virtual ~ShareConfigWidget();
    
signals:
  void changeSystemSystemDeamon(bool p_isActivated);
  void changeSystemUserDeamon(bool p_isActivated);
  void changeSystemSystemListenPort(int p_listenPort);
  void changeSystemSystemCommunicationMode(communicationType p_commType);
  void changeSystemSystemLocalListenPort(int p_listenPort);
  void changeSystemUserListenPort(int p_listenPort);
  void changeSystemUserCommViaSystemDeamon(bool b_activate);
  void changeSystemUserCommunicationMode(communicationType p_commType);
  void changeSystemUserLocalListenPort(int p_listenPort);
  
  void changeUserUseSystemSettings(bool b_useSystemSettings);
  void changeUserUserDeamon(bool p_isActivated);
  void changeUserUserListenPort(int p_listenPort);
  void changeUserUserCommunicationMode(communicationType p_commType);
  void changeUserUserLocalListenPort(int p_listenPort);
  
  void activateSystemSystemPortBox(bool p_activate);
  void activateSystemUserListenPortBox(bool p_activate);
  void activateSystemUserPortBox(bool p_activate);
  void activateUserUserPortBox(bool p_activate);
  void activateUserUserListenPortBox(bool p_activate);
  
private slots:
  void setSystemSystemDeamon(bool p_isActivated);
  void setSystemUserDeamon(bool p_isActivated);
  void setSystemSystemListenPort(int p_listenPort);
  void setSystemSystemCommunicationMode(int p_commType);
  void setSystemSystemLocalListenPort(int p_listenPort);
  void setSystemUserListenPort(int p_listenPort);
  void setSystemUserCommViaSystemDeamon(bool p_activate);
  void setSystemUserCommunicationMode(int p_commType);
  void setSystemUserLocalListenPort(int p_listenPort);
  
  void setUserUseSystemSettings(bool b_useSystemSettings);
  void setUserUserDeamon(bool p_isActivated);
  void setUserUserListenPort(int p_listenPort);
  void setUserUserCommunicationMode(int p_commType);
  void setUserUserLocalListenPort(int p_listenPort);
                           
private:
  QWidget * createSystemWidget();
  QWidget * createUserWidget();
  
  QTabWidget *tab;
};
