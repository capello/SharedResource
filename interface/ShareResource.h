/// \file
/// \brief Shared resource interface.
/// \author Anthony Jaguenaud
/// \version v0.0
///
/// This file is the entry point of libSharedResource.

#include <QtCore>
#include "ShareAuth.h"
#include <ShareUnit.h>

/// \namespace Share
/// \brief Namespace for Share library
namespace Share {
  /// \brief Share ressource object.
  class Resource
  {
  public:
    /// \brief Constructor.
    Resource();
    
    /// \brief Constructor.
    /// \param[in] p_resource The raw ressource.
    ///
    /// This constructor is used to create a new resource with data
    /// yet initialized.
    Resource(QByteArray &p_resource);

    /// \brief Return a configuration widget.
    static QWidget & config();
    
    /// \brief Destructor.
    virtual ~Resource();

    /// \brief Set replication of resource parameters
    /// \param[in] p_min_peers Set the minimum number of peers.
    /// \param[in] p_max_peers Set the maximum number of peers.
    void setDuplication(Unit<qint64> p_min_peers, Unit<qint64> p_max_peers);
    
    /// \brief Get the number of replication of the resource now.
    /// \return The absolute number of known replication of the ressource.
    /// If the resource is trunkated in 3 parts, the result is the less duplication of parts.
    qint64 getDuplicationInstant();
    
  private:
    QByteArray resource;
    Unit<qint64> min_peers;
    Unit<qint64> max_peers;
    Auth owner;
    QList<Auth> viewers;
    QList<Auth> modifiers;
  };
};

