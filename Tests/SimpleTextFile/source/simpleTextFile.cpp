/// \file
/// \brief This file implements a simble text file test.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// The objective of this test is to create a share ressource with a simble text file.
/// And then, show that cache as been correctly updated.

#include <iostream>
#include "ShareResource.h"

void usage(char *p_name, std::ostream& p_stream = std::cout)
{
  p_stream << "Usage:\n";
  p_stream << "  - " << p_name << " <file>.\n";
  p_stream << std::endl << "Return 0 if no error, else return 1." << std::endl;
}


/// \brief main function of simpleTextFile.
int main(int nargs, char *argv[])
{
  std::cout << "simbleTextFile test start" << std::endl;
  
  // First parameter should be file name or -h for help.
  if (nargs != 2)
  {
    usage(argv[0],std::cerr);
    return 1;
  }
  QString l_argument(argv[1]);
  
  if (l_argument == "-h")
  {
    usage(argv[0]);
    return 0;
  }
  
  QFile l_file(l_argument);
  
  // Check if file exists.
  if (! l_file.exists())
  {
    std::cerr << "File " << l_file.fileName().toStdString() << " does not exists.\n";
    return 1;
  }
  
  
  return 0;
}