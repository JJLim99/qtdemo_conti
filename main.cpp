#include <QApplication>   // Compatible for Qt QML library
#include <QQmlApplicationEngine>
#include "tGRPCPush.h"
#include "tGRPCPull.h"

int main(int a_argc, char *a_pargv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QApplication l_app(a_argc, a_pargv);

   // Set before resource file to prevent undefined error
   qmlRegisterType<tGRPCPush>("tGRPCPush", 1, 0, "PushNoti");
   qmlRegisterType<tGRPCPull>("tGRPCPull", 1, 0, "PullInfo");

   QQmlApplicationEngine l_engine;
   
   const QUrl l_url(QStringLiteral("main.qml"));

   QObject::connect(&l_engine, &QQmlApplicationEngine::objectCreated,&l_app, [l_url](QObject *obj, const QUrl &objUrl)
   {
   if(!obj && l_url == objUrl)
      QCoreApplication::exit(-1);
   },Qt::QueuedConnection);
   l_engine.load(l_url);

   return l_app.exec();
}
