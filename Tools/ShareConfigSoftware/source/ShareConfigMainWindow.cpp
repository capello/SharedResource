/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v..
///
/// This file implements the main window of configuration software for share library. This can be use for configure system or user configuration files.
#include <ShareConfigMainWindow.h>
#include <QtGui>
#include <ShareConfigWidget.h>
#include <typeinfo>


ShareConfigMainWindow::ShareConfigMainWindow()
{
  configuration = Share::Configuration::getInstance();
  
  // Create de main window.
  ShareConfigWidget *mainWidget = new ShareConfigWidget;
  
  QMainWindow::setCentralWidget(mainWidget);
  
  statusBar()->showMessage(tr("Loading..."));
  connect(mainWidget,SIGNAL(quitRequest()),this,SIGNAL(quitRequest()));
  
  // connect mainWidget with configuration instance
  // Tab<System>.system
  connect(configuration,SIGNAL(changeSystem_SystemDeamon(bool)),mainWidget,SLOT(setSystemSystemDeamon(bool)));
  connect(configuration,SIGNAL(changeSystem_SystemCommunicationMode(Share::Communication::Type)),mainWidget,SLOT(setSystemSystemCommunicationMode(Share::Communication::Type)));
  connect(configuration,SIGNAL(changeSystem_SystemListenPort(int)),mainWidget,SLOT(setSystemSystemListenPort(int)));
  connect(configuration,SIGNAL(changeSystem_SystemLocalListenPort(int)),mainWidget,SLOT(setSystemSystemLocalListenPort(int)));
  // Tab<System>.User
  connect(configuration,SIGNAL(changeSystem_UserDeamon(bool)),mainWidget,SLOT(setSystemUserDeamon(bool)));
  connect(configuration,SIGNAL(changeSystem_UserCommViaSystemDeamon(bool)),mainWidget,SLOT(setSystemUserCommViaSystemDeamon(bool)));
  connect(configuration,SIGNAL(changeSystem_UserListenPort(int)),mainWidget,SLOT(setSystemUserListenPort(int)));
  connect(configuration,SIGNAL(changeSystem_UserCommunicationMode(Share::Communication::Type)),mainWidget,SLOT(setSystemUserCommunicationMode(Share::Communication::Type)));
  connect(configuration,SIGNAL(changeSystem_UserLocalListenPort(int)),mainWidget,SLOT(setSystemUserLocalListenPort(int)));
  // Tab<User>
  connect(configuration,SIGNAL(changeUser_UseSystemSettings(bool)),mainWidget,SLOT(setUserUseSystemSettings(bool)));
  connect(configuration,SIGNAL(changeUser_UserDeamon(bool)),mainWidget,SLOT(setUserUserDeamon(bool)));
  connect(configuration,SIGNAL(changeUser_UserCommunicationMode(Share::Communication::Type)),mainWidget,SLOT(setUserUserCommunicationMode(Share::Communication::Type)));
  connect(configuration,SIGNAL(changeUser_UserListenPort(int)),mainWidget,SLOT(setUserUserListenPort(int)));
  connect(configuration,SIGNAL(changeUser_UserLocalListenPort(int)),mainWidget,SLOT(setUserUserLocalListenPort(int)));
  
  // Inform configuration class
  connect(mainWidget,SIGNAL(validateConfig()),this,SLOT(startSaving()));
  connect(mainWidget,SIGNAL(validateConfig()),configuration,SLOT(saveConfig()));
  
  // Connect events saving...
  connect(configuration,SIGNAL(configLoaded(bool)),this,SLOT(configLoaded(bool)));
  connect(configuration,SIGNAL(configLoaded(bool)),mainWidget,SLOT(configLoaded(bool)));
  connect(configuration,SIGNAL(configSaved(bool)),this,SLOT(configSaved(bool)));
  connect(configuration,SIGNAL(configSaved(bool)),mainWidget,SLOT(configSaved(bool)));
  
  // Connect changes on interface to the configuration class
  connect(mainWidget,SIGNAL(changeSystemSystemDeamon(bool)),configuration,SLOT(setSystem_SystemDeamon(bool)));
  connect(mainWidget,SIGNAL(changeSystemSystemListenPort(int)),configuration,SLOT(setSystem_SystemListenPort(int)));
  connect(mainWidget,SIGNAL(changeSystemSystemCommunicationMode(Share::Communication::Type)),configuration,SLOT(setSystem_SystemCommunicationMode(Share::Communication::Type)));
  connect(mainWidget,SIGNAL(changeSystemSystemLocalListenPort(int)),configuration,SLOT(setSystem_SystemLocalListenPort(int)));
  
  connect(mainWidget,SIGNAL(changeSystemUserDeamon(bool)),configuration,SLOT(setSystem_UserDeamon(bool)));
  connect(mainWidget,SIGNAL(changeSystemUserCommViaSystemDeamon(bool)),configuration,SLOT(setSystem_UserCommViaSystemDeamon(bool)));
  connect(mainWidget,SIGNAL(changeSystemUserListenPort(int)),configuration,SLOT(setSystem_UserListenPort(int)));
  connect(mainWidget,SIGNAL(changeSystemUserCommunicationMode(Share::Communication::Type)),configuration,SLOT(setSystem_UserCommunicationMode(Share::Communication::Type)));
  connect(mainWidget,SIGNAL(changeSystemUserLocalListenPort(int)),configuration,SLOT(setSystem_UserLocalListenPort(int)));
  
  connect(mainWidget,SIGNAL(changeUserUseSystemSettings(bool)),configuration,SLOT(setUser_UseSystemSettings(bool)));
  connect(mainWidget,SIGNAL(changeUserUserDeamon(bool)),configuration,SLOT(setUser_UserDeamon(bool)));
  connect(mainWidget,SIGNAL(changeUserUserCommunicationMode(Share::Communication::Type)),configuration,SLOT(setUser_UserCommunicationMode(Share::Communication::Type)));
  connect(mainWidget,SIGNAL(changeUserUserListenPort(int)),configuration,SLOT(setUser_UserListenPort(int)));
  connect(mainWidget,SIGNAL(changeUserUserLocalListenPort(int)),configuration,SLOT(setUser_UserLocalListenPort(int)));
  // Send configuration
  configuration->loadConfig();
}

ShareConfigMainWindow::~ShareConfigMainWindow()
{
}

void ShareConfigMainWindow::closeEvent(QCloseEvent *event)
{
  qDebug() << "In:" << __func__;
}

void ShareConfigMainWindow::configSaved(bool p_isConfSaved)
{
  qDebug() << "In:" << typeid(*this).name() << "::" << __func__;
  statusBar()->showMessage(tr("Saved."));
}

void ShareConfigMainWindow::configLoaded(bool p_isConfLoaded)
{
  qDebug() << "In:" << __func__;
  statusBar()->showMessage(tr("Loaded."));
}

void ShareConfigMainWindow::startSaving()
{
  qDebug() << "In:" << __func__;
  statusBar()->showMessage(tr("Saving..."));
}

void ShareConfigMainWindow::startLoading()
{
  qDebug() << "In:" << __func__;
  statusBar()->showMessage(tr("Loading..."));
}

