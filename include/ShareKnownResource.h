/// \file
/// \brief This class define a cache of all known resources over network.
/// \author Anthony Jaguenaud
/// \version v0.0

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