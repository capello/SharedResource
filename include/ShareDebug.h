/// \file
/// \brief This file have some debug.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///


#ifndef __SHARE_DEBUG_H
#define __SHARE_DEBUG_H

#include <typeinfo>
#include <QtGlobal>
#include <QString>
#include <qdebug.h>

#define WHERE Where<typeof(*this)> __where_var(__func__)

#define NOT_IMPLEMENTED qWarning() << typeid(*this).name() << "::" << __func__ << "Not yet implemented."

extern int g_numberIndent_Where;

template <class T> class Where
{
public:
  Where(const char * p_str):m_str(p_str)
  {
    QString l_indentStr;
    for(int cp = 0; cp < g_numberIndent_Where; cp++)
      l_indentStr += QString("| ");
    qDebug() << l_indentStr.toStdString().c_str() << "Enter: " << typeid(T).name() << "::" << m_str;
    g_numberIndent_Where++;
  };

  ~Where()
  {
    QString l_indentStr;
    g_numberIndent_Where--;
    for(int cp = 0; cp < g_numberIndent_Where; cp++)
      l_indentStr += QString("| ");
    qDebug() << l_indentStr.toStdString().c_str() << "Exit : " << typeid(T).name() << "::" << m_str;
  }
private:
  const char *m_str;
};

#endif
