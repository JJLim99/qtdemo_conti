////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements the tGRPCPush to bind gRPC data (Push Notification) with Qt QML
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ____tGRPCPush_h___
#define ____tGRPCPush_h___

#include <QThread>
#include <QThreadPool>
#include <QObject>
#include <QRunnable>
#include "tAteCoreCntApiClientImpl.h"

class tGRPCPush : public QObject, public QRunnable
{
   Q_OBJECT
   Q_PROPERTY(int number READ number WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(QString pushError READ pushError WRITE setName NOTIFY nameChanged)

public:
   tGRPCPush(QObject *receiver = nullptr) : QObject(receiver)
   {
      m_isRunning = false;
   }

   ~tGRPCPush()
   {
      stop();
   }

   Q_INVOKABLE void start()
   {
      if (!isRunning())
         QThreadPool::globalInstance()->start(this);
   }

   void run()
   {
      m_isRunning = true;
      while (m_isRunning)
      {
         g_runClient();
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_statusCode));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_statusMessage)));
         QThread::msleep(1);
      }
   }

   bool isRunning() const
   {
      return m_isRunning;
   }

   void stop()
   {
      m_isRunning = false;
   }

   // Return Qt QML value
   int number() const
   {
      return g_statusCode;
   }

   QString pushError()
   {
      return QString::fromStdString(g_statusMessage);
   }

/* *************************************************************************** */
/* public slots and signals are used to pass the type of variable              */
/* functions of public slots and signals are not releted with the Qt QML value */
/* *************************************************************************** */
public slots:
   void setNumber(int a_number)
   {
      if (a_number == m_number)
      {
         return;
      }
      m_number = a_number;
      emit numberChanged(m_number);
   }

   void setName(QString a_name)
   {
      if (a_name == m_name)
      {
         return;
      }
      m_name = a_name;
      emit nameChanged(m_name);
   }

signals:
   void numberChanged(int);
   void nameChanged(QString);

private:
   int m_number;
   QString m_name;
   bool m_isRunning;
};

#endif
