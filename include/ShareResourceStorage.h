/// \file ShareResourceStorage.h
/// \brief This Class is used to store ressources.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// The class store data to a file, to a deamon.
///

#include <QString>
#include <QtGlobal>
 
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
    /// This enumerate is used to define how storage has to be done.
    enum StorageMethod
    {
      DISK,  ///< The storage is done on the disk.
      DEAMON ///< The storage is done sending data to a deamon which store data on disk
    };
    
    
    /// \brief Set cache directory.
    /// \pre DISK mode. Else call is ignore and nothing change.
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
    
    /// \brief Set cache size.
    /// \pre DISK mode.
    /// \param[in] p_size the size allocated to disk cache.
    ///
    /// This function set the cache size if storage mode is DISK otherwise do nothing.
    static void setCacheSize(qint64 p_size);
    /// \brief Get cache free size.
    /// \pre DISK mode.
    /// \return Return the size in byte of the free cache.
    ///
    /// This function returns the free cache size. If \b precondition does not match, return must be ignored.
    static qint64 getCacheFree();
  private:
    static qint64 s_cacheSize;
    static qint64 s_cacheUsed;
    static qint64 s_cacheFree;
    static qint64 s_unitSize;
    static StorageMethod s_storage_method; 
  };
};
