/// \file
/// \brief This class store authentification of a Ressource.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This class is linked with a Share::ResourceStorageUnit. And use this storage unit to store all authentification information.
/// This storage unit is call “Meta”. If resource is not public, all storage units are encrypted. The “Meta” unit known the key.
/// All viewers, including owner, have the key encrypted with is public key. For more security, Meta unit can be encrypted
/// too with a key knowed only from software, or team that need to share the key by other way.

#ifndef __SHARE_RESOURCE_STORAGE_AUTH_H
#define __SHARE_RESOURCE_STORAGE_AUTH_H


#include <ShareResourceStorageUnit.h>
#include <QtCrypto>

namespace Share
{
  /// \brief ResourceStorageUnit <-> Auth link
  class ResourceStorageAuth
  {
  public:
    /// \brief Rights that process using the library have on the resource.
    struct Rights
    {
      bool isOwner; ///< \b true: is the owner of resource.
      bool canWrite;///< \b true: can modify the resource.
      bool canRead; ///< \b true: can read containt of the resource.
    };

  public:
    /// \brief Constructor
    ResourceStorageAuth();
    /// \brief Destructor
    ~ResourceStorageAuth();

    /// \brief Associate the storage unit to use
    /// \param[in] p_storageUnit the storage unit to add to “Meta” storage.
    void addAMetaUnit(ResourceStorageUnit &p_storageUnit);

    /// \brief Add a unit part
    /// \param[in] p_storageUnit the storage unit to add to storage index.
    void add(ResourceStorageUnit &p_storageUnit);

    /// \brief Flush informations to Resource Unit
    void flush();

    /// \brief Set the main key.
    /// \param[in] p_mainKey the main key.
    ///
    /// The main key is the key use to encrypt the “Meta” unit. There is no way to retreive it.
    /// If the main key is bad, others functions will return errors.
    void setMainKey(QCA::SymmetricKey p_mainKey);

    /// \brief Get the units keys.
    /// \param[in] p_unitNumber The number of the unit to encrypt or decrypt.
    QCA::SymmetricKey getUnitKey(qint64 p_unitNumber);

  private:
    QList<ResourceStorageUnit *> m_resourceUnit;
    QCA::SymmetricKey m_mainKey;
  };
};

#endif
