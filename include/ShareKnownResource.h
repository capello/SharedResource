/// \file
/// \brief This class define a cache of all known resources over network.
/// \author Anthony Jaguenaud
/// \version v0.1.0

#ifndef __SHARE_KNOWN_RESSOURCE_H
#define __SHARE_KNOWN_RESSOURCE_H

#include <qlist.h>

namespace Share
{
  /// \brief This class is a catalog of known resources over the network.
  class KnownResource
  {
  public:
    /// \brief Constructor.
    KnownResource();
    /// \brief Destructor.
    virtual ~KnownResource();
    
  private:
    static QList<KnownResource *> s_ql_known_resource;
    ResourceId resource_id;
  };
};

#endif
