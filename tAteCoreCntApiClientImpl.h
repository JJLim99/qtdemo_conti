////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements tAteCoreCntApiClientImpl to declare the function of gRPC Client 
//   API
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ___tAteCoreCntApiClientImpl_h___
#define ___tAteCoreCntApiClientImpl_h___

#include <thread>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "rcu-service.grpc.pb.h"

#include "iGRPCClient.h"
#include "tMockClient.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using rcuservice::AteCoreCntApi;
using rcuservice::StatusResponse;
using rcuservice::VariantData;
using rcuservice::SetAttrRequest;
using rcuservice::GetAttrRequest;
using rcuservice::GetAttrResponse;
using rcuservice::I2CRequest;
using rcuservice::I2CResponse;
using rcuservice::GPIODirectionRequest;
using rcuservice::GPIOLevelSetRequest;
using rcuservice::GPIOLevelGetRequest;
using rcuservice::GPIOLevelGetResponse;
using rcuservice::WriteSerialRequest;
using rcuservice::ReadSerialRequest;
using rcuservice::ReadSerialResponse;
using rcuservice::Info;

class tAteCoreCntApiClientImpl : public iGRPCClient
{
public:
   tAteCoreCntApiClientImpl (std::shared_ptr<Channel> channel) : stub_(AteCoreCntApi::NewStub(channel)) {}

   virtual uint32_t getTempCount();
   virtual uint32_t getAmpCount();
   virtual uint32_t getVoltCount();
   virtual uint32_t getFanCount();

   virtual std::vector <std::string> getTempNames();
   virtual std::vector <std::string> getAmpNames();
   virtual std::vector <std::string> getVoltNames();
   virtual std::vector <std::string> getFanNames();

   virtual std::vector <double> getTempReadings();
   virtual std::vector <double> getAmpReadings();
   virtual std::vector <double> getVoltReadings();
   virtual std::vector <uint32_t> getFanReadings();

   virtual void pushNoti();

private:
   std::unique_ptr<AteCoreCntApi::Stub> stub_;
};

// Declare the global variable and function which are used to bind Qt with gRPC
extern uint32_t g_tempCount;
extern uint32_t g_ampCount;
extern uint32_t g_voltCount;
extern uint32_t g_fanCount;

extern std::vector <std::string> g_TempNames;
extern std::vector <std::string> g_AmpNames;
extern std::vector <std::string> g_VoltNames;
extern std::vector <std::string> g_FanNames;

extern std::vector <double> g_TempReadings;
extern std::vector <double> g_AmpReadings;
extern std::vector <double> g_VoltReadings;
extern std::vector <uint32_t> g_FanReadings;
extern double g_pushFanReadings;
extern std::string g_statusMessage;
extern int32_t g_statusCode;

void g_runClient();

#endif
