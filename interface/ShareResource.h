/// \file
/// \brief Shared resource interface.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file is the entry point of libSharedResource.

#ifndef __SHARE_RESOURCE_H
#define __SHARE_RESOURCE_H

#include <QtCore>
#include "ShareAuth.h"
#include <ShareUnit.h>
#include <ShareResourceStorage.h>

/// \namespace Share
/// \brief Namespace for Share library
namespace Share {
/// \brief Share resource object.
class Resource
{
public:
  /// \brief Share resource configuration class.
    class Config
    {
    public:
      /// \brief Constructor.
      Config();
      /// \brief Destructor.
      virtual ~Config();
      
        /// \brief Return a configuration widget.
        static QWidget & getWidget();
        
        /// \brief Set user StorageMethod.
        /// \param[in] p_isUserMethod boolean set if storageMethod is for user or global.
        /// \li \b true user mode. Storage is local to user account.
        /// \li \b false global mode. Storage is managed by a deamon that store in is own disk space.
        void setUserStorage(bool p_isUserMethod);
        
        /// \brief Get StorageMethod.
        /// \return \li \b true user mode. Storage is local to user account.
        /// \li \b false global mode. Storage is managed by a deamon that store in is own disk space.
        bool isUserStorage() const;
        
        /// \brief Load configuration file.
        /// \return \li \b true if configuration has been loaded.
        /// \li \b false if configuration cannot be read.
        bool loadConfigFile();
        
        /// \brief Save configuration file.
        /// \return \li \b true if configuration has been saved.
        /// \li \b false if configuration cannot be save.
        bool saveConfigFile() const;
        
    private:
      ResourceStorage storageMethod;
      bool canManuallyModify;

    };
    /// \brief Constructor.
    Resource();

    /// \brief Constructor.
    /// \param[in] p_resource The raw ressource.
    ///
    /// This constructor is used to create a new resource with data
    /// yet initialized.
    Resource(QByteArray &p_resource);

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

#endif
