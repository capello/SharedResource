/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v..
///
/// This file contains the definition of main widget for configuration software.
#include <qmainwindow.h>
#include <ShareConfiguration.h>

class ShareConfigMainWindow:public QMainWindow
{
  Q_OBJECT
  
public:
  ShareConfigMainWindow();
  
  virtual ~ShareConfigMainWindow();
  
signals:
  void quitRequest();
  
protected:
  void closeEvent(QCloseEvent *event);
  
  
private slots:
  
public slots:
  void startSaving();
  void startLoading();
  void configSaved(bool p_isConfSaved);
  void configLoaded(bool p_isConfLoaded);

private:
  Share::Configuration *configuration;
};
