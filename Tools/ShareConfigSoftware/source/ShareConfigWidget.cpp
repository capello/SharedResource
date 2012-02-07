/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main Widget of the application.
#include <ShareConfigWidget.h>
#include <iostream>
#include <ShareCommunicationNetwork.h>


ShareConfigWidget::ShareConfigWidget(QWidget *parent ):QWidget(parent)
{
  tab = new QTabWidget;
  tab->addTab(createSystemWidget(),tr("System"));
  tab->addTab(createUserWidget(),tr("User"));
  
  QPushButton *okButton = new QPushButton;
  QPushButton *applyButton = new QPushButton;
  QPushButton *cancelButton = new QPushButton;
  okButton->setText(tr("Ok"));
  applyButton->setText(tr("Apply"));
  applyButton->setDisabled(true);
  cancelButton->setText(tr("Cancel"));
  
  
  QHBoxLayout * buttons = new QHBoxLayout;
  buttons->addStretch();
  buttons->addWidget(okButton);
  buttons->addWidget(applyButton);
  buttons->addWidget(cancelButton);
  
  QVBoxLayout * main = new QVBoxLayout;
  main->addWidget(tab);
  main->addLayout(buttons);
  
  setLayout(main);
}

ShareConfigWidget::~ShareConfigWidget()
{
}

QWidget * ShareConfigWidget::createSystemWidget()
{
  QVBoxLayout *mainLayout = new QVBoxLayout;
  
  // System deamon part.
  QLabel *listenSystemPortLabel = new QLabel(tr("External listen Port"));
  QSpinBox *listenSystemPortNumber = new QSpinBox();
  listenSystemPortNumber->setMinimum(Share::CommunicationNetwork::s_minAdminPortNumber);
  listenSystemPortNumber->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  listenSystemPortNumber->setValue(Share::CommunicationNetwork::s_defaultAdminPortNumber);
  
  QLabel *systemInternalCommunicationLabel = new QLabel(tr("Internal communication"));
  QComboBox *systemInternalCommunicationBox = new QComboBox;
  
  systemInternalCommunicationBox->addItem(tr("Dbus"),DBUS);
  systemInternalCommunicationBox->addItem(tr("Share memory"),SHARE_MEM);
  systemInternalCommunicationBox->addItem(tr("Network"),NETWORK);
  QSpinBox *systemInternalCommunicationPortBox = new QSpinBox();
  systemInternalCommunicationPortBox->setDisabled(true);
  systemInternalCommunicationPortBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  systemInternalCommunicationPortBox->setMinimum(Share::CommunicationNetwork::s_minAdminPortNumber);
  systemInternalCommunicationPortBox->setValue(Share::CommunicationNetwork::s_defaultAdminPortNumber);
  
  QGridLayout *systemDeamonLayout = new QGridLayout;
  systemDeamonLayout->addWidget(listenSystemPortLabel,0,0);
  systemDeamonLayout->addWidget(listenSystemPortNumber,0,1);
  systemDeamonLayout->addWidget(systemInternalCommunicationLabel,1,0);
  systemDeamonLayout->addWidget(systemInternalCommunicationBox,1,1);
  systemDeamonLayout->addWidget(systemInternalCommunicationPortBox,1,2);
  
  QGroupBox *systemDeamonGroupBox = new QGroupBox (tr("System deamon"));
  systemDeamonGroupBox->setLayout(systemDeamonLayout);
  systemDeamonGroupBox->setCheckable(true);
  
  mainLayout->addWidget(systemDeamonGroupBox);
  
  // User deamon part
  QCheckBox *userExternalCommunicationViaSystem = new QCheckBox(tr("External communication via system deamon"));
  QLabel *userInternalCommunicationLabel = new QLabel(tr("Internal communication"));
  QComboBox *userInternalCommunicationBox = new QComboBox;
  userExternalCommunicationViaSystem->setChecked(true);
  
  QLabel *listenUserPortLabel = new QLabel(tr("External listen Port"));
  QSpinBox *listenUserPortNumber = new QSpinBox();
  listenUserPortLabel->setDisabled(true);
  listenUserPortNumber->setDisabled(true);
  listenUserPortNumber->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  listenUserPortNumber->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  listenUserPortNumber->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  
  userInternalCommunicationBox->addItem(tr("Dbus"),DBUS);
  userInternalCommunicationBox->addItem(tr("Share memory"),SHARE_MEM);
  userInternalCommunicationBox->addItem(tr("Network"),NETWORK);
  QSpinBox *userInternalCommunicationPortBox = new QSpinBox();
  userInternalCommunicationPortBox->setDisabled(true);
  userInternalCommunicationPortBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  userInternalCommunicationPortBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  userInternalCommunicationPortBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  
  QGridLayout *userInternalCommunicationLayout = new QGridLayout;
  userInternalCommunicationLayout->addWidget(listenUserPortLabel,0,0);
  userInternalCommunicationLayout->addWidget(listenUserPortNumber,0,1);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationLabel,1,0);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationBox,1,1);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationPortBox,1,2);
  
  QVBoxLayout * userDeamonLayout = new QVBoxLayout;
  userDeamonLayout->addWidget(userExternalCommunicationViaSystem);
  userDeamonLayout->addLayout(userInternalCommunicationLayout);
  
  QGroupBox *userDeamonGroupBox = new QGroupBox (tr("User deamon"));
  userDeamonGroupBox->setLayout(userDeamonLayout);
  userDeamonGroupBox->setCheckable(true);
  
  mainLayout->addWidget(userDeamonGroupBox);
  mainLayout->addStretch();
  
  
  // Connections
  // System deamon
  connect(systemDeamonGroupBox,SIGNAL(clicked(bool)),this,SLOT(setSystemSystemDeamon(bool)));
  connect(listenSystemPortNumber,SIGNAL(valueChanged(int)),this,SLOT(setSystemSystemListenPort(int)));
  connect(systemInternalCommunicationBox,SIGNAL(activated(int)),this,SLOT(setSystemSystemCommunicationMode(int)));
  connect(this,SIGNAL(activateSystemSystemPortBox(bool)),systemInternalCommunicationPortBox,SLOT(setEnabled(bool)));
  connect(systemInternalCommunicationPortBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemSystemLocalListenPort(int)));
  
  // User deamon
  connect(userDeamonGroupBox,SIGNAL(clicked(bool)),this,SLOT(setSystemUserDeamon(bool)));
  connect(userExternalCommunicationViaSystem,SIGNAL(clicked(bool)),this,SLOT(setSystemUserCommViaSystemDeamon(bool)));
  connect(listenUserPortNumber,SIGNAL(valueChanged(int)),this,SLOT(setSystemUserListenPort(int)));
  connect(userInternalCommunicationBox,SIGNAL(activated(int)),this,SLOT(setSystemUserCommunicationMode(int)));
  connect(this,SIGNAL(activateSystemUserListenPortBox(bool)),listenUserPortNumber,SLOT(setEnabled(bool)));
  connect(this,SIGNAL(activateSystemUserListenPortBox(bool)),listenUserPortLabel,SLOT(setEnabled(bool)));
  connect(this,SIGNAL(activateSystemUserPortBox(bool)),userInternalCommunicationPortBox,SLOT(setEnabled(bool)));
  // Set final widget
  QGroupBox *returnWidget = new QGroupBox;
  returnWidget->setLayout(mainLayout);
  return returnWidget;
  
}


QWidget * ShareConfigWidget::createUserWidget()
{
  QGroupBox * mainGroup = new QGroupBox();
  
  QCheckBox *useSystemSettings = new QCheckBox(tr("Use system configuration"));
  useSystemSettings->setChecked(true);
  
  // User deamon part
  QLabel *userInternalCommunicationLabel = new QLabel(tr("Internal communication"));
  QComboBox *userInternalCommunicationBox = new QComboBox;
  
  QLabel *listenUserPortLabel = new QLabel(tr("External listen Port"));
  QSpinBox *listenUserPortNumber = new QSpinBox();
  listenUserPortLabel->setDisabled(true);
  listenUserPortNumber->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  listenUserPortNumber->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  listenUserPortNumber->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  listenUserPortNumber->setDisabled(true);
  
  userInternalCommunicationBox->addItem(tr("Dbus"),DBUS);
  userInternalCommunicationBox->addItem(tr("Share memory"),SHARE_MEM);
  userInternalCommunicationBox->addItem(tr("Network"),NETWORK);
  QSpinBox *userInternalCommunicationPortBox = new QSpinBox();
  userInternalCommunicationPortBox->setDisabled(true);
  userInternalCommunicationPortBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  userInternalCommunicationPortBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  userInternalCommunicationPortBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  
  QGridLayout *userInternalCommunicationLayout = new QGridLayout;
  userInternalCommunicationLayout->addWidget(listenUserPortLabel,0,0);
  userInternalCommunicationLayout->addWidget(listenUserPortNumber,0,1);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationLabel,1,0);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationBox,1,1);
  userInternalCommunicationLayout->addWidget(userInternalCommunicationPortBox,1,2);
  
  QVBoxLayout * userDeamonLayout = new QVBoxLayout;
  userDeamonLayout->addLayout(userInternalCommunicationLayout);
  
  QGroupBox *userDeamonGroupBox = new QGroupBox (tr("User deamon"));
  userDeamonGroupBox->setLayout(userDeamonLayout);
  userDeamonGroupBox->setCheckable(true);
  userDeamonGroupBox->setChecked(false);
  
  
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(useSystemSettings);
  mainLayout->addWidget(userDeamonGroupBox);
  mainLayout->addStretch();
  
  // Create connections.
  connect(useSystemSettings,SIGNAL(clicked(bool)),this,SLOT(setUserUseSystemSettings(bool)));
  connect(listenUserPortNumber,SIGNAL(valueChanged(int)),this,SLOT(setUserUserListenPort(int)));
  connect(userInternalCommunicationBox,SIGNAL(activated(int)),this,SLOT(setUserUserCommunicationMode(int)));
  connect(userInternalCommunicationPortBox,SIGNAL(valueChanged(int)),this,SLOT(setUserUserLocalListenPort(int)));
  connect(this,SIGNAL(activateUserUserPortBox(bool)),userInternalCommunicationPortBox,SLOT(setEnabled(bool)));
  connect(this,SIGNAL(activateUserUserListenPortBox(bool)),listenUserPortNumber,SLOT(setEnabled(bool)));
  connect(this,SIGNAL(activateUserUserListenPortBox(bool)),listenUserPortLabel,SLOT(setEnabled(bool)));
  
  // Set final widget
  mainGroup->setLayout(mainLayout);
 return mainGroup;
}

void ShareConfigWidget::setSystemSystemDeamon(bool p_isActivated)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemSystemDeamon(p_isActivated);
}

void ShareConfigWidget::setSystemUserDeamon(bool p_isActivated)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserDeamon(p_isActivated);
}

void ShareConfigWidget::setSystemSystemListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemSystemListenPort(p_listenPort);
}

void ShareConfigWidget::setSystemSystemCommunicationMode(int p_commType)
{
  communicationType l_commType = static_cast<communicationType>(p_commType);
  
  qDebug() << "In: " << __func__  ;
  emit changeSystemSystemCommunicationMode(l_commType);
  switch (l_commType)
  {
    case NETWORK:
      emit activateSystemSystemPortBox(true);
      break;
    default:
      emit activateSystemSystemPortBox(false);
      break;
  }
}

void ShareConfigWidget::setSystemSystemLocalListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemSystemLocalListenPort(p_listenPort);
}

void ShareConfigWidget::setSystemUserListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserListenPort(p_listenPort);
}

void ShareConfigWidget::setSystemUserCommViaSystemDeamon(bool p_activate)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserCommViaSystemDeamon(p_activate);
  emit activateSystemUserListenPortBox(!p_activate);
}

void ShareConfigWidget::setSystemUserCommunicationMode(int p_commType)
{
  communicationType l_commType = static_cast<communicationType>(p_commType);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserCommunicationMode(l_commType);
  switch (l_commType)
  {
    case NETWORK:
      emit activateSystemUserPortBox(true);
      break;
    default:
      emit activateSystemUserPortBox(false);
      break;
  }
}

void ShareConfigWidget::setSystemUserLocalListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserLocalListenPort(p_listenPort);
}

void ShareConfigWidget::setUserUseSystemSettings(bool p_useSystemSettings)
{
  qDebug() << "In: " << __func__ ;
  emit changeUserUseSystemSettings(p_useSystemSettings);
  emit activateUserUserListenPortBox(!p_useSystemSettings);
}

void ShareConfigWidget::setUserUserDeamon(bool p_isActivated)
{
  qDebug() << "In: " << __func__ ;
  emit changeUserUserDeamon(p_isActivated);
}

void ShareConfigWidget::setUserUserListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeUserUserListenPort(p_listenPort);
}

void ShareConfigWidget::setUserUserCommunicationMode(int p_commType)
{
  communicationType l_commType = static_cast<communicationType> (p_commType);
  qDebug() << "In: " << __func__ ;
  emit changeUserUserCommunicationMode(l_commType);
  switch (l_commType)
  {
    case NETWORK:
      emit activateUserUserPortBox(true);
      break;
    default:
      emit activateUserUserPortBox(false);
      break;
  }
}

void ShareConfigWidget::setUserUserLocalListenPort(int p_listenPort)
{
  qDebug() << "In: " << __func__ ;
  emit changeUserUserLocalListenPort(p_listenPort);
}

