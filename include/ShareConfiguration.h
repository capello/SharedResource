/// \file
/// \brief This Class is used to configure all.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
#include <QString>

namespace Share {
  class Configuration
  {
  private:
    Configuration();
    
    ~Configuration();
  public:
    static void readConf();
  private:
    static Configuration instance;
    static QSettings settings;
  };
  
};