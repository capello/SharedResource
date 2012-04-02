/// \file
/// \brief This class store a unit of a Ressource.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// A unit is a piece of.
/// For example is you have a unit size equal to 64MB, a ressource of 264MB will be
/// separate into 5 units. Each unit will be replicated over the network.
/// This class can exists only if Share::ShareResourceStorage::s_storage_method == Share::StorageMethod::DISK

#ifndef __SHARE_RESSOURCE_STORAGE_UNIT_H
#define __SHARE_RESSOURCE_STORAGE_UNIT_H

#include <qfile.h>

namespace Share
{
  /// \brief Unit Storage class
  class ResourceStorageUnit
  {
  public:
    enum Mode
    {
      UNKNOWN,
      META,
      DATA
    };
  public:
    /// \brief Constructor.
    /// \param[in] p_mode Mode of the resource. \b default is DATA.
    ResourceStorageUnit(Mode p_mode = DATA);
    /// \brief Destructor.
    virtual ~ResourceStorageUnit();

    /// \brief Don't remember usage
    /// \todo Complete doxygen brief description.
    bool isSafe();

    /// \brief Return the part number.
    /// \return Return the number of the part of the resource.
    qint64 getPartNumber();

    /// \brief Set the mode of the unit to meta.
    /// \param[in] p_isMeta \li \b true: Set the mode to META.
    ///                     \li \b false: If mode is not META: unchange, else set the mode to unknown.
    void setMeta(bool p_isMeta);

    /// \brief Set the mode of the unit to meta.
    /// \param[in] p_isData \li \b true: Set the mode to DATA.
    ///                     \li \b false: If mode is not DATA: unchange, else set the mode to unknown.
    void setData(bool p_isData);

    /// \brief Get the current mode of the unit.
    /// \return \b Mode The current mode.
    Mode getMode();

    /// \brief Flush data of the Storage Unit.
    /// \warning This of unit must be called after storage or meta information created.
    /// This flush storage unit.
    void flush();

    /// \brief Add data to storage unit.
    /// \param[in] p_data Data to add.
    virtual void storeData(QByteArray p_data) = 0;

  private:
    qint64 m_sizeOfData;
    Mode m_currentMode;
  };
};
#endif
