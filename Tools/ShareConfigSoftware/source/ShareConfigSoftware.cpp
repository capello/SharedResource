/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v..
///
/// This file implements the configuration software for share library. This can be use for configure system or user configuration files.

#include <iostream>
#include <QApplication>
#include "ShareConfigMainWindow.h"

int main(int arg_n, char * arg_v[])
{
  QApplication app(arg_n, arg_v);
  
  ShareConfigMainWindow  *window = new ShareConfigMainWindow;
  
  QObject::connect(window,SIGNAL(quitRequest()),&app,SLOT(quit()));
  
  window->show();
  return app.exec();
}
