////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements the tGRPCPull to bind gRPC data (Pull Data) with Qt QML
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ____tGRPCPull_h___
#define ____tGRPCPull_h___

#include <QThread>
#include <QThreadPool>
#include <QObject>
#include <QRunnable>
#include "tAteCoreCntApiClientImpl.h"

class tGRPCPull : public QObject, public QRunnable
{
   Q_OBJECT
   Q_PROPERTY(int valRPM1 READ valRPM1 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valRPM2 READ valRPM2 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valRPM3 READ valRPM3 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valRPM4 READ valRPM4 WRITE setNumber NOTIFY numberChanged)

   Q_PROPERTY(int valAmp1 READ valAmp1 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valAmp2 READ valAmp2 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valAmp3 READ valAmp3 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valAmp4 READ valAmp4 WRITE setNumber NOTIFY numberChanged)

   Q_PROPERTY(int valVolt1 READ valVolt1 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valVolt2 READ valVolt2 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valVolt3 READ valVolt3 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valVolt4 READ valVolt4 WRITE setNumber NOTIFY numberChanged)

   Q_PROPERTY(int valTemp1 READ valTemp1 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valTemp2 READ valTemp2 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valTemp3 READ valTemp3 WRITE setNumber NOTIFY numberChanged)
   Q_PROPERTY(int valTemp4 READ valTemp4 WRITE setNumber NOTIFY numberChanged)

   Q_PROPERTY(QString nameFan1 READ nameFan1 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameFan2 READ nameFan2 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameFan3 READ nameFan3 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameFan4 READ nameFan4 WRITE setName NOTIFY nameChanged)

   Q_PROPERTY(QString nameAmp1 READ nameAmp1 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameAmp2 READ nameAmp2 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameAmp3 READ nameAmp3 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameAmp4 READ nameAmp4 WRITE setName NOTIFY nameChanged)

   Q_PROPERTY(QString nameVolt1 READ nameVolt1 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameVolt2 READ nameVolt2 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameVolt3 READ nameVolt3 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameVolt4 READ nameVolt4 WRITE setName NOTIFY nameChanged)

   Q_PROPERTY(QString nameTemp1 READ nameTemp1 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameTemp2 READ nameTemp2 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameTemp3 READ nameTemp3 WRITE setName NOTIFY nameChanged)
   Q_PROPERTY(QString nameTemp4 READ nameTemp4 WRITE setName NOTIFY nameChanged)

public:
   tGRPCPull(QObject *receiver = nullptr) : QObject(receiver)
   {
      m_isRunning = false;
   }

   ~tGRPCPull()
   {
      stop();
   }

   Q_INVOKABLE void start()
   {
      if (!isRunning())
         QThreadPool::globalInstance()->start(this);
   }

   void run() override
   {
      m_isRunning = true;
     
      while (m_isRunning)
      {
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_FanReadings[0]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_FanReadings[1]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_FanReadings[2]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_FanReadings[3]));

         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_VoltReadings[0]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_VoltReadings[1]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_VoltReadings[2]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_VoltReadings[3]));

         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_AmpReadings[0]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_AmpReadings[1]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_AmpReadings[2]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_AmpReadings[3]));

         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_TempReadings[0]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_TempReadings[1]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_TempReadings[2]));
         QMetaObject::invokeMethod(this, "setNumber", Qt::QueuedConnection, Q_ARG(int, g_TempReadings[3]));

         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_FanNames[0])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_FanNames[1])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_FanNames[2])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_FanNames[3])));

         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_AmpNames[0])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_AmpNames[1])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_AmpNames[2])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_AmpNames[3])));

         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_VoltNames[0])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_VoltNames[1])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_VoltNames[2])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_VoltNames[3])));

         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_TempNames[0])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_TempNames[1])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_TempNames[2])));
         QMetaObject::invokeMethod(this, "setName", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(g_TempNames[3])));

         QThread::msleep(2000);
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
   QString nameTemp1()
   {
      return QString::fromStdString(g_TempNames[0]);
   }

   QString nameTemp2()
   {
      return QString::fromStdString(g_TempNames[1]);
   }

   QString nameTemp3()
   {
      return QString::fromStdString(g_TempNames[2]);
   }

   QString nameTemp4()
   {
      return QString::fromStdString(g_TempNames[3]);
   }

   QString nameAmp1()
   {
      return QString::fromStdString(g_AmpNames[0]);
   }

   QString nameAmp2()
   {
      return QString::fromStdString(g_AmpNames[1]);
   }

   QString nameAmp3()
   {
      return QString::fromStdString(g_AmpNames[2]);
   }

   QString nameAmp4()
   {
      return QString::fromStdString(g_AmpNames[3]);
   }

   QString nameVolt1()
   {
      return QString::fromStdString(g_VoltNames[0]);
   }

   QString nameVolt2()
   {
      return QString::fromStdString(g_VoltNames[1]);
   }

   QString nameVolt3()
   {
      return QString::fromStdString(g_VoltNames[2]);
   }

   QString nameVolt4()
   {
      return QString::fromStdString(g_VoltNames[3]);
   }

   QString nameFan1()
   {
      return QString::fromStdString(g_FanNames[0]);
   }

   QString nameFan2()
   {
      return QString::fromStdString(g_FanNames[1]);
   }

   QString nameFan3()
   {
      return QString::fromStdString(g_FanNames[2]);
   }

   QString nameFan4()
   {
      return QString::fromStdString(g_FanNames[3]);
   }

   double valTemp1()
   {
      return g_TempReadings[0];
   }

   double valTemp2()
   {
      return g_TempReadings[1];
   }

   double valTemp3()
   {
      return g_TempReadings[2];
   }

   double valTemp4()
   {
      return g_TempReadings[3];
   }

   double valAmp1()
   {
      return g_AmpReadings[0];
   }

   double valAmp2()
   {
      return g_AmpReadings[1];
   }

   double valAmp3()
   {
      return g_AmpReadings[2];
   }

   double valAmp4()
   {
      return g_AmpReadings[3];
   }

   double valVolt1()
   {
      return g_VoltReadings[0];
   }

   double valVolt2()
   {
      return g_VoltReadings[1];
   }

   double valVolt3()
   {
      return g_VoltReadings[2];
   }

   double valVolt4()
   {
      return g_VoltReadings[3];
   }

   uint32_t valRPM1()
   {
      return g_FanReadings[0];
   }

   uint32_t valRPM2()
   {
      return g_FanReadings[1];
   }

   uint32_t valRPM3()
   {
      return g_FanReadings[2];
   }

   uint32_t valRPM4()
   {
      return g_FanReadings[3];
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
