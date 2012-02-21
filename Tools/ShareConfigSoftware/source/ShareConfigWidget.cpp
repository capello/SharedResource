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
#include <ShareDebug.h>

#define returnIfUnchange(value) static bool isStarted; \
  static __typeof__(value) oldValue;\
  if (isStarted && (oldValue == value)) \
    return; \
  oldValue = value; \
  isStarted = true


ShareConfigWidget::ShareConfigWidget(QWidget *parent ):QWidget(parent)
{
  m_tab = new QTabWidget;
  m_tab->addTab(createSystemWidget(),tr("System"));
  m_tab->addTab(createUserWidget(),tr("User"));

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
  main->addWidget(m_tab);
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
  QGroupBox *l_systemDeamon_QGroupBox = new QGroupBox (tr("System deamon"));
  l_systemDeamon_QGroupBox->setCheckable(true);
    // System listen port
      QLabel *l_systemListenPort_QLabel = new QLabel(tr("External listen Port"));
      QSpinBox *l_systemListenPortNumber_QSpinBox = new QSpinBox();
        l_systemListenPortNumber_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minAdminPortNumber);
        l_systemListenPortNumber_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
        l_systemListenPortNumber_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultAdminPortNumber);
    // System communication mode
      QLabel *l_systemInternalCommunication_QLabel = new QLabel(tr("Internal communication"));
      QComboBox *l_systemInternalCommunication_QComboBox = new QComboBox;
        l_systemInternalCommunication_QComboBox->addItem(tr("Dbus"),Share::Communication::DBUS);
        l_systemInternalCommunication_QComboBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
        l_systemInternalCommunication_QComboBox->addItem(tr("Network"),Share::Communication::NETWORK);
      QSpinBox *l_systemInternalCommunicationPort_QSpinBox = new QSpinBox();
        l_systemInternalCommunicationPort_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
        l_systemInternalCommunicationPort_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minAdminPortNumber);
        l_systemInternalCommunicationPort_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultAdminPortNumber);
      // System cache path
      QLabel *l_systemCachePath_QLabel = new QLabel(tr("Cache Path"));
      QPushButton *l_systemCachePath_QPushButton = new QPushButton(tr("..."));
      QLineEdit *l_systemCachePath_QLineEdit = new QLineEdit();
      // System cache quota.
      QLabel *l_systemCacheQuota_QLabel = new QLabel(tr("Max cache size"));
      QSpinBox *l_systemCacheQuota_QSpinBox = new QSpinBox();
        l_systemCacheQuota_QSpinBox->setSuffix(tr(" GByte"));

    QGridLayout *l_systemDeamonLayout = new QGridLayout;
      l_systemDeamonLayout->addWidget(l_systemListenPort_QLabel,0,0,1,2);
      l_systemDeamonLayout->addWidget(l_systemListenPortNumber_QSpinBox,0,2,1,2);
      l_systemDeamonLayout->addWidget(l_systemInternalCommunication_QLabel,1,0,1,2);
      l_systemDeamonLayout->addWidget(l_systemInternalCommunication_QComboBox,1,2);
      l_systemDeamonLayout->addWidget(l_systemInternalCommunicationPort_QSpinBox,1,3);
      l_systemDeamonLayout->addWidget(l_systemCachePath_QLabel,2,0);
      l_systemDeamonLayout->addWidget(l_systemCachePath_QPushButton,2,1);
      l_systemDeamonLayout->addWidget(l_systemCachePath_QLineEdit,2,2,1,2);
      l_systemDeamonLayout->addWidget(l_systemCacheQuota_QLabel,3,0,1,2);
      l_systemDeamonLayout->addWidget(l_systemCacheQuota_QSpinBox,3,2,1,2);

  l_systemDeamon_QGroupBox->setLayout(l_systemDeamonLayout);

  mainLayout->addWidget(l_systemDeamon_QGroupBox);

  // User deamon part
  QGroupBox *l_userDeamon_QGroupBox = new QGroupBox (tr("User deamon"));
  l_userDeamon_QGroupBox->setCheckable(true);

    QCheckBox *l_userExternalCommunicationViaSystem_QCheckBox = new QCheckBox(tr("External communication via system deamon"));
      l_userExternalCommunicationViaSystem_QCheckBox->setChecked(true);

    QLabel *l_userListenPortNumber_QLabel = new QLabel(tr("External listen Port"));
    QSpinBox *l_userListenPortNumber_QSpinBox = new QSpinBox();
      l_userListenPortNumber_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
      l_userListenPortNumber_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
      l_userListenPortNumber_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);

    QLabel *l_userInternalCommunication_QLabel = new QLabel(tr("Internal communication"));
    QComboBox *l_userInternalCommunication_QComboBox = new QComboBox;
      l_userInternalCommunication_QComboBox->addItem(tr("Dbus"),Share::Communication::DBUS);
      l_userInternalCommunication_QComboBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
      l_userInternalCommunication_QComboBox->addItem(tr("Network"),Share::Communication::NETWORK);

    QSpinBox *l_userInternalCommunicationListenPort_QSpinBox = new QSpinBox();
      l_userInternalCommunicationListenPort_QSpinBox->setDisabled(true);
      l_userInternalCommunicationListenPort_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
      l_userInternalCommunicationListenPort_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
      l_userInternalCommunicationListenPort_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
      l_systemInternalCommunicationPort_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultAdminPortNumber);
      // System cache path
      QLabel *l_userCachePath_QLabel = new QLabel(tr("Cache Path"));
      QPushButton *l_userCachePath_QPushButton = new QPushButton(tr("..."));
      QLineEdit *l_userCachePath_QLineEdit = new QLineEdit();
      // System cache quota.
      QLabel *l_userCacheQuota_QLabel = new QLabel(tr("Max cache size"));
      QSpinBox *l_userCacheQuota_QSpinBox = new QSpinBox();
        l_userCacheQuota_QSpinBox->setSuffix(tr(" GByte"));

    QGridLayout *userInternalCommunicationLayout = new QGridLayout;
      userInternalCommunicationLayout->addWidget(l_userListenPortNumber_QLabel,0,0,1,2);
      userInternalCommunicationLayout->addWidget(l_userListenPortNumber_QSpinBox,0,2,1,2);
      userInternalCommunicationLayout->addWidget(l_userInternalCommunication_QLabel,1,0,1,2);
      userInternalCommunicationLayout->addWidget(l_userInternalCommunication_QComboBox,1,2);
      userInternalCommunicationLayout->addWidget(l_userInternalCommunicationListenPort_QSpinBox,1,3);
      userInternalCommunicationLayout->addWidget(l_userCachePath_QLabel,2,0);
      userInternalCommunicationLayout->addWidget(l_userCachePath_QPushButton,2,1);
      userInternalCommunicationLayout->addWidget(l_userCachePath_QLineEdit,2,2,1,2);
      userInternalCommunicationLayout->addWidget(l_userCacheQuota_QLabel,3,0,1,2);
      userInternalCommunicationLayout->addWidget(l_userCacheQuota_QSpinBox,3,2,1,2);

  QVBoxLayout * userDeamonLayout = new QVBoxLayout;
    userDeamonLayout->addWidget(l_userExternalCommunicationViaSystem_QCheckBox);
    userDeamonLayout->addLayout(userInternalCommunicationLayout);

  l_userDeamon_QGroupBox->setLayout(userDeamonLayout);

  mainLayout->addWidget(l_userDeamon_QGroupBox);
  mainLayout->addStretch();


  // Connections
  // System deamon
  connect(l_systemDeamon_QGroupBox,SIGNAL(clicked(bool)),this,SLOT(setSystemSystemDeamon(bool)));
  connect(l_systemListenPortNumber_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemSystemListenPort(int)));
  connect(l_systemInternalCommunication_QComboBox,SIGNAL(activated(int)),this,SLOT(setSystemSystemCommunicationMode(int)));
  connect(this,SIGNAL(activateSystemSystemPortBox(bool)),l_systemInternalCommunicationPort_QSpinBox,SLOT(setEnabled(bool)));
  connect(l_systemInternalCommunicationPort_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemSystemLocalListenPort(int)));
  connect(l_systemCachePath_QLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setSystemSystemCachePath(QString)));
  connect(l_systemCachePath_QPushButton,SIGNAL(clicked(bool)),this,SLOT(selectSystemSystemCachePath()));
  connect(l_systemCacheQuota_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemSystemCacheQuota(int)));

  // User deamon
  connect(l_userDeamon_QGroupBox,SIGNAL(clicked(bool)),this,SLOT(setSystemUserDeamon(bool)));
  connect(l_userExternalCommunicationViaSystem_QCheckBox,SIGNAL(clicked(bool)),this,SLOT(setSystemUserCommViaSystemDeamon(bool)));
  connect(l_userListenPortNumber_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemUserListenPort(int)));
  connect(l_userInternalCommunication_QComboBox,SIGNAL(activated(int)),this,SLOT(setSystemUserCommunicationMode(int)));
  connect(l_userInternalCommunicationListenPort_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemUserLocalListenPort(int)));
  connect(this,SIGNAL(activateSystemUserPortBox(bool)),l_userInternalCommunicationListenPort_QSpinBox,SLOT(setEnabled(bool)));
  connect(l_userCachePath_QLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setSystemUserCachePath(QString)));
  connect(l_userCachePath_QPushButton,SIGNAL(clicked(bool)),this,SLOT(selectSystemUserCachePath()));
  connect(l_userCacheQuota_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSystemUserCacheQuota(int)));

  // Change interface via external changes.
  // Connect signals of Config Widget to interface elements.
  // Tab<System>:System part
  connect(this,SIGNAL(changeSystemSystemDeamon(bool)),l_systemDeamon_QGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemSystemListenPort(int)),l_systemListenPortNumber_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemSystemCommunicationMode(int)),l_systemInternalCommunication_QComboBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeSystemSystemLocalListenPort(int)),l_systemInternalCommunicationPort_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemSystemCachePath(QString)),l_systemCachePath_QLineEdit,SLOT(setText(QString)));
  connect(this,SIGNAL(changeSystemSystemCacheQuota(int)),l_systemCacheQuota_QSpinBox,SLOT(setValue(int)));
  // Tab<System>:user part
  connect(this,SIGNAL(changeSystemUserDeamon(bool)),l_userDeamon_QGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemUserCommViaSystemDeamon(bool)),l_userExternalCommunicationViaSystem_QCheckBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeSystemUserListenPort(int)),l_userListenPortNumber_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemUserCommunicationMode(int)),l_userInternalCommunication_QComboBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeSystemUserLocalListenPort(int)),l_userInternalCommunicationListenPort_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeSystemUserCachePath(QString)),l_userCachePath_QLineEdit,SLOT(setText(QString)));
  connect(this,SIGNAL(changeSystemUserCacheQuota(int)),l_userCacheQuota_QSpinBox,SLOT(setValue(int)));

  // Set final widget
  QGroupBox *returnWidget = new QGroupBox;
  returnWidget->setLayout(mainLayout);
  return returnWidget;

}


QWidget * ShareConfigWidget::createUserWidget()
{
  QVBoxLayout *l_mainLayout = new QVBoxLayout;
  QGroupBox * l_mainGroup_QGroupBox = new QGroupBox();


  QCheckBox *l_useSystemSettings_QCheckBox = new QCheckBox(tr("Use system configuration"));
    l_useSystemSettings_QCheckBox->setChecked(true);

  QGroupBox *l_userDeamon_QGroupBox = new QGroupBox (tr("User deamon"));
    l_userDeamon_QGroupBox->setCheckable(true);
    l_userDeamon_QGroupBox->setChecked(false);
    QLabel *l_userListenPortNumber_QLabel = new QLabel(tr("External listen Port"));
    QSpinBox *l_userListenPortNumber_QSpinBox = new QSpinBox();
      l_userListenPortNumber_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
      l_userListenPortNumber_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
      l_userListenPortNumber_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);


  // User deamon part
    QLabel *l_userInternalCommunication_QLabel = new QLabel(tr("Internal communication"));
    QComboBox *l_userInternalCommunication_QComboBox = new QComboBox;
      l_userInternalCommunication_QComboBox->addItem(tr("Dbus"),Share::Communication::DBUS);
      l_userInternalCommunication_QComboBox->addItem(tr("Share memory"),Share::Communication::SHARE_MEM);
      l_userInternalCommunication_QComboBox->addItem(tr("Network"),Share::Communication::NETWORK);
    QSpinBox *l_userInternalCommunicationPortNumber_QSpinBox = new QSpinBox();
      l_userInternalCommunicationPortNumber_QSpinBox->setDisabled(true);
      l_userInternalCommunicationPortNumber_QSpinBox->setMaximum(Share::CommunicationNetwork::s_maxPortNumber);
      l_userInternalCommunicationPortNumber_QSpinBox->setMinimum(Share::CommunicationNetwork::s_minUserPortNumber);
      l_userInternalCommunicationPortNumber_QSpinBox->setValue(Share::CommunicationNetwork::s_defaultUserPortNumber);
      // User cache path
      QLabel *l_userCachePath_QLabel = new QLabel(tr("Cache Path"));
      QPushButton *l_userCachePath_QPushButton = new QPushButton(tr("..."));
      QLineEdit *l_userCachePath_QLineEdit = new QLineEdit();
      // System cache quota.
      QLabel *l_userCacheQuota_QLabel = new QLabel(tr("Max cache size"));
      QSpinBox *l_userCacheQuota_QSpinBox = new QSpinBox();
      l_userCacheQuota_QSpinBox->setSuffix(tr(" GByte"));


    QGridLayout *l_userInternalCommunicationLayout = new QGridLayout;
      l_userInternalCommunicationLayout->addWidget(l_userListenPortNumber_QLabel,0,0,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userListenPortNumber_QSpinBox,0,2,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userInternalCommunication_QLabel,1,0,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userInternalCommunication_QComboBox,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userInternalCommunicationPortNumber_QSpinBox,1,3);
      l_userInternalCommunicationLayout->addWidget(l_userCachePath_QLabel,2,0);
      l_userInternalCommunicationLayout->addWidget(l_userCachePath_QPushButton,2,1);
      l_userInternalCommunicationLayout->addWidget(l_userCachePath_QLineEdit,2,2,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userCacheQuota_QLabel,3,0,1,2);
      l_userInternalCommunicationLayout->addWidget(l_userCacheQuota_QSpinBox,3,2,1,2);

  QVBoxLayout * l_userDeamonLayout = new QVBoxLayout;
    l_userDeamonLayout->addLayout(l_userInternalCommunicationLayout);

    l_userDeamon_QGroupBox->setLayout(l_userDeamonLayout);


  l_mainLayout->addWidget(l_useSystemSettings_QCheckBox);
  l_mainLayout->addWidget(l_userDeamon_QGroupBox);
  l_mainLayout->addStretch();

  // Create connections.
  connect(l_useSystemSettings_QCheckBox,SIGNAL(clicked(bool)),this,SLOT(setUserUseSystemSettings(bool)));
  connect(l_userDeamon_QGroupBox,SIGNAL(clicked(bool)),this,SLOT(setUserUserDeamon(bool)));
  connect(l_userListenPortNumber_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setUserUserListenPort(int)));
  connect(l_userInternalCommunication_QComboBox,SIGNAL(activated(int)),this,SLOT(setUserUserCommunicationMode(int)));
  connect(l_userInternalCommunicationPortNumber_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setUserUserLocalListenPort(int)));
  connect(this,SIGNAL(activateUserUserPortBox(bool)),l_userInternalCommunicationPortNumber_QSpinBox,SLOT(setEnabled(bool)));
  connect(l_userCachePath_QLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setUserUserCachePath(QString)));
  connect(l_userCachePath_QPushButton,SIGNAL(clicked(bool)),this,SLOT(selectUserUserCachePath()));
  connect(l_userCacheQuota_QSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setUserUserCacheQuota(int)));

  // Connect changes to Widget.
  connect(this,SIGNAL(changeUserUseSystemSettings(bool)),l_useSystemSettings_QCheckBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeUserUserCommunicationMode(int)),l_userInternalCommunication_QComboBox,SLOT(setCurrentIndex(int)));
  connect(this,SIGNAL(changeUserUserDeamon(bool)),l_userDeamon_QGroupBox,SLOT(setChecked(bool)));
  connect(this,SIGNAL(changeUserUserListenPort(int)),l_userListenPortNumber_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeUserUserLocalListenPort(int)),l_userInternalCommunicationPortNumber_QSpinBox,SLOT(setValue(int)));
  connect(this,SIGNAL(changeUserUserCachePath(QString)),l_userCachePath_QLineEdit,SLOT(setText(QString)));
  connect(this,SIGNAL(changeUserUserCacheQuota(int)),l_userCacheQuota_QSpinBox,SLOT(setValue(int)));

  // Set final widget
  l_mainGroup_QGroupBox->setLayout(l_mainLayout);
 return l_mainGroup_QGroupBox;
}

void ShareConfigWidget::setSystemSystemDeamon(bool p_isActivated)
{
  WHERE;
  returnIfUnchange(p_isActivated);
  emit changeSystemSystemDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserDeamon(bool p_isActivated)
{
  WHERE;
  returnIfUnchange(p_isActivated);
  emit changeSystemUserDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  emit changeSystemSystemListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCommunicationMode(Share::Communication::Type p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int> (p_commType);

  emit changeSystemSystemCommunicationMode(p_commType);
  emit changeSystemSystemCommunicationMode(l_commType);
  emit activateSystemSystemPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCommunicationMode(int p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type>(p_commType);

  emit changeSystemSystemCommunicationMode(p_commType);
  emit changeSystemSystemCommunicationMode(l_commType);
  emit activateSystemSystemPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemLocalListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  emit changeSystemSystemLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCachePath(QString p_path)
{
  WHERE;
  returnIfUnchange(p_path);
  m_systemSystemPath = p_path;
  emit changeSystemSystemCachePath(p_path);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemSystemCacheQuota(int p_maxSize)
{
  WHERE;
  returnIfUnchange(p_maxSize);
  emit changeSystemSystemCacheQuota(p_maxSize);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  emit changeSystemUserListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommViaSystemDeamon(bool p_activate)
{
  WHERE;
  returnIfUnchange(p_activate);
  emit changeSystemUserCommViaSystemDeamon(p_activate);
  emit activateSystemUserListenPortBox(!p_activate);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommunicationMode(Share::Communication::Type p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int>(p_commType);
  emit changeSystemUserCommunicationMode(p_commType);
  emit changeSystemUserCommunicationMode(l_commType);
  emit activateSystemUserPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCommunicationMode(int p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type>(p_commType);
  emit changeSystemUserCommunicationMode(p_commType);
  emit changeSystemUserCommunicationMode(l_commType);
  emit activateSystemUserPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserLocalListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  qDebug() << "In: " << __func__ ;
  emit changeSystemUserLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}


void ShareConfigWidget::setSystemUserCachePath(QString p_path)
{
  WHERE;
  returnIfUnchange(p_path);
  m_systemUserPath = p_path;
  emit changeSystemUserCachePath(p_path);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setSystemUserCacheQuota(int p_maxSize)
{
  WHERE;
  returnIfUnchange(p_maxSize);
  emit changeSystemUserCacheQuota(p_maxSize);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUseSystemSettings(bool p_useSystemSettings)
{
  WHERE;
  returnIfUnchange(p_useSystemSettings);
  emit changeUserUseSystemSettings(p_useSystemSettings);
  emit activateUserUserListenPortBox(!p_useSystemSettings);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserDeamon(bool p_isActivated)
{
  WHERE;
  returnIfUnchange(p_isActivated);
  emit changeUserUserDeamon(p_isActivated);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  emit changeUserUserListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCommunicationMode(Share::Communication::Type p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  int l_commType = static_cast<int> (p_commType);
  emit changeUserUserCommunicationMode(p_commType);
  emit changeUserUserCommunicationMode(l_commType);
  emit activateUserUserPortBox(p_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCommunicationMode(int p_commType)
{
  WHERE;
  returnIfUnchange(p_commType);
  Share::Communication::Type l_commType = static_cast<Share::Communication::Type> (p_commType);
  emit changeUserUserCommunicationMode(p_commType);
  emit changeUserUserCommunicationMode(l_commType);
  emit activateUserUserPortBox(l_commType == Share::Communication::NETWORK);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserLocalListenPort(int p_listenPort)
{
  WHERE;
  returnIfUnchange(p_listenPort);
  emit changeUserUserLocalListenPort(p_listenPort);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCachePath(QString p_path)
{
  WHERE;
  returnIfUnchange(p_path);
  m_userUserPath = p_path;
  emit changeUserUserCachePath(p_path);
  emit activateApplyButton(true);
}

void ShareConfigWidget::setUserUserCacheQuota(int p_maxSize)
{
  WHERE;
  returnIfUnchange(p_maxSize);
  emit changeUserUserCacheQuota(p_maxSize);
  emit activateApplyButton(true);
}

void ShareConfigWidget::okButton()
{
  WHERE;
  emit validateConfig();
  emit quitRequest();
}

void ShareConfigWidget::cancelButton()
{
  WHERE;
  emit quitRequest();
}

void ShareConfigWidget::applyButton()
{
  WHERE;
  emit validateConfig();
}

void ShareConfigWidget::selectSystemSystemCachePath()
{
  WHERE;
  QDir l_dir;
  if (!l_dir.exists(m_systemSystemPath))
    m_systemSystemPath = QDir::homePath();
  qDebug() << "l_dir[0] =" << l_dir[0];
  QString l_path = QFileDialog::getExistingDirectory(this, tr("Select a directory"),m_systemSystemPath,QFileDialog::ShowDirsOnly);
  if ( l_path.isNull() == false )
  {
    setSystemSystemCachePath(l_path);
  }
}

void ShareConfigWidget::selectSystemUserCachePath()
{
  WHERE;
  QDir l_dir;
  if (!l_dir.exists(m_systemUserPath))
    m_systemUserPath = QDir::homePath();
  qDebug() << "l_dir[0] =" << l_dir[0];
  QString l_path = QFileDialog::getExistingDirectory(this, tr("Directory"),m_systemUserPath,QFileDialog::ShowDirsOnly);
  qDebug() << "l_path = " << l_path;
  if ( l_path.isNull() == false )
  {
    setSystemUserCachePath(l_path);
  }
}

void ShareConfigWidget::selectUserUserCachePath()
{
  WHERE;
  QDir l_dir;
  if (!l_dir.exists(m_userUserPath))
    m_userUserPath = QDir::homePath();
  QString l_path = QFileDialog::getExistingDirectory(this, tr("Directory"),m_userUserPath,QFileDialog::ShowDirsOnly);
  qDebug() << "l_path = " << l_path;
  if ( l_path.isNull() == false )
  {
    setUserUserCachePath(l_path);
  }
}

void ShareConfigWidget::configSaved(bool p_isConfSaved)
{
  WHERE;
  emit activateApplyButton(!p_isConfSaved);
}

void ShareConfigWidget::configLoaded(bool p_isConfLoaded)
{
  WHERE;
  emit activateApplyButton(!p_isConfLoaded);
}
