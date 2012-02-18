/// \file
/// \brief This file implements a simble text file test.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// The objective of this test is to create a share ressource with a simble text file.
/// And then, show that cache as been correctly updated.
/// \li First scenario is with local storage (no deamon launches) is direct saving file, no peers. (Use Resource_Disk)
/// \li Second scenario is with local user deamon (no system deamon lanched) try communication with all possible protocols.
/// \li Third scenario is with system deamon, try communication with all possible protocols.

#include <iostream>
#include "ShareResource.h"

void usage(char *p_name, std::ostream& p_stream = std::cout)
{
  p_stream << "Usage:\n";
  p_stream << "  - " << p_name << " <file>.\n";
  p_stream << std::endl << "Return 0 if no error, else return 1." << std::endl;
}

Share::Resource::Id shareFile(QFile &p_file, Share::Auth & p_auth)
{
  Share::Resource::Id l_resourceId;
  // Open file cannot fail.
  p_file.open(QIODevice::ReadOnly);
  QByteArray l_file_in_byte_array = p_file.readAll();
  p_file.close();
  std::cout << "File size: " << p_file.size() << ", bytearray size: " << l_file_in_byte_array.size() << std::endl;
  // Create Resource. It is directly push to ResourceStorage.
  Share::Resource l_resource(l_file_in_byte_array,p_auth);

  l_resourceId = l_resource.getId();

  return l_resourceId;
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

  Share::Resource::Config::getInstance()->setLocalStorage(true);

  Share::Auth l_auth;
  Share::Resource::Id l_id = shareFile(l_file,l_auth);

  //md5Resource();

  // Compare md5sum and size of l_file and resource


  return 0;
}