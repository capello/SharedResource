/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file contains the definition of main widget for configuration software.
#include <qmainwindow.h>

class ShareConfigMainWindow:public QMainWindow
{
  Q_OBJECT
  
public:
  ShareConfigMainWindow();
  
  virtual ~ShareConfigMainWindow();
  
protected:
  void closeEvent(QCloseEvent *event);
  
private slots:
  
};
