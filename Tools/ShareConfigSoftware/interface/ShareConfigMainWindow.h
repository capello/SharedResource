/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file contains the definition of main widget for configuration software.
#include <qmainwindow.h>
#include <ShareConfiguration.h>

/// \brief The main window class for the ShareConfig software.
class ShareConfigMainWindow:public QMainWindow
{
  Q_OBJECT
  
public:
  /// \brief Constructor
  ShareConfigMainWindow();
  
  /// \brief Destructor
  virtual ~ShareConfigMainWindow();
  
signals:
  /// \brief Signal a quit request from the MainWidget
  void quitRequest();
  
protected:
  /// \brief Close event method.
  void closeEvent(QCloseEvent *event);
  
  
private slots:
  
public slots:
  /// \brief Slot write into status bar that we are saving.
  void startSaving();
  /// \brief Slot write into status bar that we are loading.
  void startLoading();
  /// \brief Slot write into status bar that save has be done or fail.
  void configSaved(bool p_isConfSaved);
  /// \brief Slot write into status bar that load has be done or fail.
  void configLoaded(bool p_isConfLoaded);

private:
  /// \brief A local pointer on the configuration instance.
  Share::Configuration *configuration;
};
