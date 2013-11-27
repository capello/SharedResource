/// \file ShareResourceStorage.h
/// \brief This Class is used to store ressources.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// The class store data to files, to a deamon.
/// The class manage storage units for a resource.
///

#ifndef __SHARE_RESOURCE_STORAGE_H
#define __SHARE_RESOURCE_STORAGE_H

#include <QString>
#include <QtGlobal>
#include <ShareAuth.h>
#include <ShareResourceStorageUnit.h>
#include <ShareResourceStorageMeta.h>
#include <QList>


namespace Share
{

  /// \brief Class which perform the storage.
  ///
  /// This class defines the storage. This means, mode of storage,
  /// parameters for storage (storage method, sizes available)
  class ResourceStorage
  {
  public:
    /// \brief Constructor.
    ResourceStorage();
    /// \brief Destructor.
    virtual ~ResourceStorage();


    /// \enum StorageMethod
    /// \brief How library must store resource
    ///
    /// This enumerate is used to define how storage has to be done. From the library point of view.
    /// Deamons can communicate by network or local communication to share informations.
    enum StorageMethod
    {
      UNKNOWN, ///< Not yet defined.
      LOCAL_CACHE, ///< The storage is done by library saving into a directory.
      SYSTEM_DEAMON, ///< The storage is done sending data to a system deamon which store data on disk
      USER_DEAMON, ///< The storage is done in user disk space, all instance of library use the same local deamon.
                   ///< If no user deamon started, the library start one.
      NETWORK ///< The storage is done over the network.
    };


    /// \pre LOCAL_CACHE mode. Else call is ignore and nothing change.
    /// \param[in] p_path path to use to store cache files.
    /// \return false if path could not be set.
    ///         true in others cases.
    ///
    /// This function set the path to use for store resource into files on the current computer.
    /// The function can only be called if storage method is DISK.
    static bool setCacheDirectory(QString p_path);

    /// \brief Set storage method.
    /// \param[in] p_storage_method Storage method to use.
    ///
    /// This function set the storage method. Others set methods behavior may be affected by
    /// the call of this function.
    static void setStorageMethod(StorageMethod p_storage_method);

    /// \brief Get storage method.
    /// \return Storage method in used
    static StorageMethod getStorageMethod();

    /// \brief Get an instance of a Share::ResourceStorage class in function of configuration.
    ///
    /// This static function returns an instance of a derived class of ResourceStorage.
    static ResourceStorage * getAnInstance();

    /// \brief Set cache size.
    /// \pre LOCAL_CACHE mode.
    /// \param[in] p_size the size allocated to disk cache.
    ///
    /// This function set the cache size if storage mode is DISK otherwise do nothing.
    static void setCacheSize(qint64 p_size);

    /// \brief Get cache free size.
    /// \pre LOCAL_CACHE mode.
    /// \return Return the size in byte of the free cache.
    ///
    /// This function returns the free cache size. If \b precondition does not match, return must be ignored.
    static qint64 getCacheFree();

    /// \brief Stores a resource.
    /// \param[in] p_resource The resource to share.
    /// This method store the resource into one or more Share::StorageUnit.
    /// All resource will be rewrite. If this is new resource, Id will be created.
    void store(QByteArray &p_resource);

    /// \brief Gets a resource.
    /// \param[out] p_resource Stored resource.
    /// This method gets a resource.
    void get(QByteArray &p_resource) const;

    /// \brief SetOwner of a resource.
    /// \param[in] p_auth Auth parameter.
    void setOwner(Share::Auth& p_auth);

    /// \brief Set public the resource.
    /// \param[in] p_setPublic \li \b true: Set the resource public.
    ///                        \li \b false: Set the resource private. A resource can be private only if the
    ///                        owner is set.
    void setPublic(bool p_setPublic);

    /// \brief Set the resource encrypted.
    /// \param[in] p_setEncrypted \li \b true: The resource will be encrypted.
    ///                           \li \b false: The resource will not be encrypted.
    void setEncrypted(bool p_setEncrypted);

    /// \brief Get public resource flag.
    /// \return \li \b true: The resource is public.
    ///         \li \b false: The resource is private.
    bool getPublic();

    /// \brief Get incrypted resource flag.
    /// \return \li \b true: The resource is encrypted.
    ///         \li \b false: The resource is encrypted.
    bool getEncrypted();

    /// \brief Flush all data to disk or storage system.
    /// This function returns only when work is done.
    void flush();

  private:
    /// \brief Add new storage unit to this storage unit.
    qint64 newStorageUnit();

  private:
    QList<ResourceStorageUnit *> m_units;
    ResourceStorageMeta m_meta;
    bool m_isPublic;
    bool m_isEncrypted;
    static const qint64 s_defaultUnitSize;
    static const StorageMethod s_defaultStorageMethod;
    static qint64 s_unitSize;
    static StorageMethod s_storageMethod;
    static QString s_cacheDirectory;
    static QList<ResourceStorage *> s_listOfinstances;
  };
};
#endif
