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
  class Resource:public QObject
  {
    Q_OBJECT
  public:
    /// \brief Version of resource class
    /// This class is used to know wich version of a resource it is. And then upgrade the resource when a
    /// new version is available.
    class Version
    {
    public:
      /// \brief Constructor
      Version();

      /// \brief Destructor
      ~Version();
    };

    /// \brief Resource Id class
    /// This class manage an Id for a Resource. The ID is uniq and will not change during all life of resource.
    class Id
    {
    public:
      /// \brief Constructor
      Id();

      /// \brief Destructor
      ~Id();
    };

    /// \brief Share resource configuration class.
    class Config
    {
    private:
      /// \brief Constructor.
      Config();
      /// \brief Destructor.
      virtual ~Config();

    public:
      /// \brief Set user StorageMethod.
      /// \param[in] p_isUserMethod boolean set if storageMethod is for user or global.
      /// \li \b true user mode. Storage is local to user account.
      /// \li \b false global mode. Storage is managed by a deamon that store in is own disk space.
      void setLocalStorage(bool p_isUserMethod);

      /// \brief Get StorageMethod.
      /// \return \li \b true user mode. Storage is local to user account.
      /// \li \b false global mode. Storage is managed by a deamon that store in is own disk space.
      bool isLocalStorage() const;

      /// \brief Get Storage Method
      /// \return \b Share::ResourceStorage::StorageMethod configured.
      ResourceStorage::StorageMethod getStorageMethod();

      /// \brief Load configuration file.
      /// \return \li \b true if configuration has been loaded.
      /// \li \b false if configuration cannot be read.
      bool loadConfigFile();

      /// \brief Save configuration file.
      /// \return \li \b true if configuration has been saved.
      /// \li \b false if configuration cannot be save.
      bool saveConfigFile() const;

      /// \brief Set default public flag.
      /// \param[in] p_isPublic value to set.
      void setPublicByDefault(bool p_isPublic);

      /// \brief Get default public flag.
      /// \return \li \b true: The public default flag is true.
      ///         \li \b false: The public default flag is false.
      bool getPublicByDefault();

      /// \brief Set default encrypt flag.
      /// \param[in] p_isEncrypted value to set.
      void setEncryptedByDefault(bool p_isEncrypted);

      /// \brief Get default encrypt flag.
      /// \return \li \b true: The encrypt default flag is true.
      ///         \li \b false: The encryt default flag is false.
      bool getEncryptedByDefault();

      /// \brief Set default owner.
      /// \param[in] p_owner Set the default owner.
      void setOwnerByDefault(Auth * p_owner);

      /// \brief Get default owner.
      /// \return Pointer on default owner.
      Auth * getOwnerByDefault();

      /// \brief Get instance method.
      /// \return A pointer on instance.
      static Config * getInstance();

    private:
      ResourceStorage::StorageMethod m_storageMethod;
      bool m_isAdminMode;
      bool m_isPublicByDefault;
      bool m_isEncryptedByDefault;
      Auth *m_defaultOwner;
      static Config s_instance;

    };

    /// \brief Enumerated to define states available for a resource.
    /// The safe states are AVAILABLE, PARTIALY_AVAILABLE, GETTING. In those states the resource has been saved somewhere.
    enum State {
      UNKNOWN, ///< Resource has not be created.
      AVAILABLE, ///< Resource is localy available and complete.
      PARTIALY_AVAILABLE, ///< Resource is partialy available localy.
      GETTING, ///< Resource has been requested localy and download from peers is progressing.
      PARTIAL, ///< Resource is partial, we cannot retreive all parts.
      CONFLICT, ///< The resource has been modify by two users and the modifications need to be merged.
      CREATING, ///< First version of resource is currently in creation (need resource, owner).
      MODIFYING, ///< The resource is in modification.
    };

    /// \brief Constructor.
    Resource();

    /// \brief Constructor.
    /// \param[in] p_resource The raw resource.
    /// \param[in] p_owner The owner of the resource.
    ///
    /// This constructor is used to create a new resource with data
    /// yet initialized. The constructor returns when resource is safe.
    Resource(QByteArray &p_resource, Auth &p_owner = Auth::Undefine);

    /// \brief Constructor
    /// \param[in] p_resourceId The resource will be retreive by resourceId.
    Resource(Share::Resource::Id p_resourceId);

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

    /// \brief Get the resource.
    /// This method is synchronious, so if need download, will wait all download.
    /// \return The resource has a byte array.
    QByteArray get();

    /// \brief Get the state of the resource
    /// This method returns the state of the resource. The resource start unknown and became available.
    State getState();

    /// \brief Modify a resource.
    /// This method modify the resource. If is the first version of the resource it is created.
    /// The function return only when the entire resource has been copied to the first relay.
    /// \param[in] p_resource The raw resource.
    void modify(QByteArray &p_resource);

    /// \brief Get the ResourceId of the resource.
    /// \return The resourceId of resource.
    Share::Resource::Id getId();

    /// \brief Get the version of the current resource.
    /// \return Version of the resource.
    Share::Resource::Version getVersion();

    /// \brief To knew if resource is localy available.
    /// This can be use to improve CPU time. And wait for get method.
    /// \return \li \b true: The resource is in local cache.
    ///         \li \b false: The resource is not all in local cache.
    bool isLocalyAvailable();

    /// \brief Set owner of a resource.
    /// This method set the owner of a resource.
    /// \param[in] p_owner Owner to set.
    void setOwner(Auth &p_owner);

    /// \brief Add a viewer
    /// This method add a viewer to the resource.
    /// \param[in] p_viewer Viewer to add.
    /// \param[in] p_canModify Set to \b true to authorized viewer to modify this resource. (default: \b false)
    void addViewer(Auth &p_viewer, bool p_canModify = false);

  signals:
    /// \brief Signal resource state changes.
    /// \param[in] p_newState The new resource state.
    void changeState(State p_newState);

  private:
    ResourceStorage *resource;
    Id           resourceId;
    State        state;
    Unit<qint64> min_peers;
    Unit<qint64> max_peers;
    Auth owner;
    QList<Auth> viewers;
    QList<Auth> modifiers;
  };
};

#endif
