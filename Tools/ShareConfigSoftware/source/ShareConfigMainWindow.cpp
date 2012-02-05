/// \file
/// \brief Config software implementation.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the main window of configuration software for share library. This can be use for configure system or user configuration files.
#include <ShareConfigMainWindow.h>
#include <QtGui>

ShareConfigMainWindow::ShareConfigMainWindow()
{
  // Create de main window.
  
  QPushButton *button = new QPushButton;
  
  QMainWindow::setCentralWidget(button);
  
  statusBar()->showMessage(tr("Loading..."));
}

ShareConfigMainWindow::~ShareConfigMainWindow()
{
}

void ShareConfigMainWindow::closeEvent(QCloseEvent *event)
{
}
