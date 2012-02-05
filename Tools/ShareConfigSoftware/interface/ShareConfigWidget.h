/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file contains the definition of main widget for configuration software.

#include <QtGui>

class ShareConfigWidget: public QWidget
{
  Q_OBJECT
  
public:
    explicit ShareConfigWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    ShareConfigWidget(const QWidget& );
    
    virtual ~ShareConfigWidget();
    
private:
  QTabWidget *tab;
  ShareConfigSystemSettings *sysSettings;
  ShareConfigUserSettings *userSettings;
};
