/// \file
/// \brief Implements the unit storage main class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#include <ShareResourceStorageUnit.h>
#include <QtCore>

Share::ResourceStorageUnit::ResourceStorageUnit(Mode p_mode)
{
  m_currentMode = p_mode;
  m_sizeOfData = 0;
}


Share::ResourceStorageUnit::~ResourceStorageUnit()
{
}

bool Share::ResourceStorageUnit::isSafe()
{
  qWarning() << __func__ << "Not yet implemented.";
}


qint64 Share::ResourceStorageUnit::getPartNumber()
{
  qWarning() << __func__ << "Not yet implemented.";
}

void Share::ResourceStorageUnit::setMeta(bool p_isMeta)
{
  if (p_isMeta)
  {
    m_currentMode = META;
  }
  else
  {
    if (m_currentMode == META)
    {
      m_currentMode = UNKNOWN;
    }
  }
}

void Share::ResourceStorageUnit::setData(bool p_isData)
{
  if (p_isData)
  {
    m_currentMode = DATA;
  }
  else
  {
    if (m_currentMode == DATA)
    {
      m_currentMode = UNKNOWN;
    }
  }
}

Share::ResourceStorageUnit::Mode Share::ResourceStorageUnit::getMode()
{
  return m_currentMode;
}
