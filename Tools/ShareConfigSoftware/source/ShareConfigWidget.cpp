/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main Widget of the application.
#include <ShareConfigWidget.h>
#include <iostream>
#include <ShareCommunicationNetwork.h>
#include <typeinfo>

#define returnIfUnchange(value) static bool isStarted; \
  static __typeof__(value) oldValue;\
  if (isStarted && (oldValue == value)) \
    return; \
  oldValue = value; \
  isStarted = true
  
  
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
  
  // Connections for buttons.
  connect(okButton,SIGNAL(clicked(bool)),this,SLOT(okButton()));
  connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButton()));
  connect(applyButton,SIGNAL(clicked(bool)),this,SLOT(applyButton()));
  connect(this,SIGNAL(activateApplyButton(bool)),applyButton,SLOT(setEnabled(bool)));
  
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
  
  systemInternalCommunicationBox->addItem(tr("Dbus"),Share::Communication::DBUS);
  systemInternalCommunicationBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
  systemInternalCommunicationBox->addItem(tr("Network"),Share::Communication::NETWORK);
  QSpinBox *systemInternalCommunicationPortBox = new QSpinBox();
  //systemInternalCommunicationPortBox->setDisabled(true);
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
  listenUserPortNumber->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  listenUserPortNumber->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  listenUserPortNumber->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  
  userInternalCommunicationBox->addItem(tr("Dbus"),Share::Communication::DBUS);
  userInternalCommunicationBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
  userInternalCommunicationBox->addItem(tr("Network"),Share::Communication::NETWORK);
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
  connect(userInternalCommunicationPortBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemUserLocalListenPort(int)));
  connect(this,SIGNAL(activateSystemUserPortBox(bool)),userInternalCommunicationPortBox,SLOT(setEnabled(bool)));
  
  // Change interface via external changes.
  // Connect signals of Config Widget to interface elements.
  // Tab<System>:System part
  connect(this,SIGNAL(changeSystemSystemDeamon(bool)),systemDeamonGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemSystemListenPort(int)),listenSystemPortNumber,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemSystemCommunicationMode(int)),systemInternalCommunicationBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeSystemSystemLocalListenPort(int)),systemInternalCommunicationPortBox,SLOT(setValue(int)));
  // Tab<System>:user part
  connect(this,SIGNAL(changeSystemUserDeamon(bool)),userDeamonGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemUserCommViaSystemDeamon(bool)),userExternalCommunicationViaSystem,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemUserListenPort(int)),listenUserPortNumber,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemUserCommunicationMode(int)),userInternalCommunicationBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeSystemUserLocalListenPort(int)),userInternalCommunicationPortBox,SLOT(setValue(int)));
  
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
  listenUserPortNumber->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
  listenUserPortNumber->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
  listenUserPortNumber->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
  
  userInternalCommunicationBox->addItem(tr("Dbus"),Share::Communication::DBUS);
  userInternalCommunicationBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
  userInternalCommunicationBox->addItem(tr("Network"),Share::Communication::NETWORK);
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
  connect(userDeamonGroupBox,SIGNAL(clicked(bool)),this,SLOT(setUserUserDeamon(bool)));
  connect(listenUserPortNumber,SIGNAL(valueChanged(int)),this,SLOT(setUserUserListenPort(int)));
  connect(userInternalCommunicationBox,SIGNAL(activated(int)),this,SLOT(setUserUserCommunicationMode(int)));
  connect(userInternalCommunicationPortBox,SIGNAL(valueChanged(int)),this,SLOT(setUserUserLocalListenPort(int)));
  connect(this,SIGNAL(activateUserUserPortBox(bool)),userInternalCommunicationPortBox,SLOT(setEnabled(bool)));
  
  // Connect changes to Widget.
  connect(this,SIGNAL(changeUserUseSystemSettings(bool)),useSystemSettings,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeUserUserCommunicationMode(int)),userInternalCommunicationBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeUserUserDeamon(bool)),userDeamonGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeUserUserListenPort(int)),listenUserPortNumber,SLOT(setValue(int)));
  connect(this,SIGNAL(changeUserUserLocalListenPort(int)),userInternalCommunicationPortBox,SLOT(setValue(int)));
  // Set final widget
  mainGroup->setLayout(mainLayout);
 return mainGroup;
}

void ShareConfigWidget::setSystemSystemDeamon(bool p_isActivated)
{
  returnIfUnchange(p_isActivated);
  qDebug() << "In: " << __func__ << "(" << p_isActivated << ")";
  emit changeSystemSystemDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserDeamon(bool p_isActivated)
{
  returnIfUnchange(p_isActivated);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeSystemSystemListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCommunicationMode(Share::Communication::Type p_commType)
{
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int> (p_commType);
  qDebug() << "In: " << __func__ << "(Share::Communication::Type)" ;
  
  emit changeSystemSystemCommunicationMode(p_commType);
  emit changeSystemSystemCommunicationMode(l_commType);
  emit activateSystemSystemPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCommunicationMode(int p_commType)
{
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type>(p_commType);
  
  qDebug() << "In: " << __func__ << "(int)" ;
  emit changeSystemSystemCommunicationMode(p_commType);
  emit changeSystemSystemCommunicationMode(l_commType);
  emit activateSystemSystemPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemLocalListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeSystemSystemLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommViaSystemDeamon(bool p_activate)
{
  returnIfUnchange(p_activate);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserCommViaSystemDeamon(p_activate);
  emit activateSystemUserListenPortBox(!p_activate);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommunicationMode(Share::Communication::Type p_commType)
{
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int>(p_commType);
  qDebug() << "In: " << __func__ << "(Share::Communication::Type)";
  emit changeSystemUserCommunicationMode(p_commType);
  emit changeSystemUserCommunicationMode(l_commType);
  emit activateSystemUserPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommunicationMode(int p_commType)
{
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type>(p_commType);
  qDebug() << "In: " << __func__ << "(int)";
  emit changeSystemUserCommunicationMode(p_commType);
  emit changeSystemUserCommunicationMode(l_commType);
  emit activateSystemUserPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserLocalListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUseSystemSettings(bool p_useSystemSettings)
{
  returnIfUnchange(p_useSystemSettings);
  qDebug() << "In: " << __func__ ;
  emit changeUserUseSystemSettings(p_useSystemSettings);
  emit activateUserUserListenPortBox(!p_useSystemSettings);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserDeamon(bool p_isActivated)
{
  returnIfUnchange(p_isActivated);
  qDebug() << "In: " << __func__ ;
  emit changeUserUserDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeUserUserListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCommunicationMode(Share::Communication::Type p_commType)
{
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int> (p_commType);
  qDebug() << "In: " << __func__ << "(Share::Communication::Type)";
  emit changeUserUserCommunicationMode(p_commType);
  emit changeUserUserCommunicationMode(l_commType);
  emit activateUserUserPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCommunicationMode(int p_commType)
{
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type> (p_commType);
  qDebug() << "In: " << __func__ << "(int)";
  emit changeUserUserCommunicationMode(p_commType);
  emit changeUserUserCommunicationMode(l_commType);
  emit activateUserUserPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserLocalListenPort(int p_listenPort)
{
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeUserUserLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::okButton()
{
  qDebug() << "In:" << __func__;
  emit validateConfig();
  emit quitRequest();
}

void ShareConfigWidget::cancelButton()
{
  qDebug() << "In:" << __func__;
  emit quitRequest();
}

void ShareConfigWidget::applyButton()
{
  qDebug() << "In:" << __func__;
  emit validateConfig();
}


void ShareConfigWidget::configSaved(bool p_isConfSaved)
{
  qDebug() << "In:" << typeid(*this).name() << "::" << __func__ << "(" << p_isConfSaved << ")";
  emit activateApplyButton(!p_isConfSaved);
}

void ShareConfigWidget::configLoaded(bool p_isConfLoaded)
{
  qDebug() << "In:" << __func__;
  emit activateApplyButton(!p_isConfLoaded);
}
