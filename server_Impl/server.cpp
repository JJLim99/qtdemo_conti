////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements gRPC server which is used for LCD Application in grpcLCD and 
//   testing purpose in server_Impl
//   
////////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <condition_variable>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "rcu-service.grpc.pb.h"
#include <functional>
#include <memory>
#include <vector>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
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

class tAteCoreCntApiServiceImpl final : public AteCoreCntApi::Service
{
public:

   Status PushNoti(ServerContext* l_context, ServerReaderWriter <Info, Info>* stream) override
   {
      Info l_info;
      double l_tempOffset = 60;
      int32_t l_status;
      double l_test;

      for(;;)
      {
         std::this_thread::sleep_for(std::chrono::seconds(2));
         l_test = rand() % 100;

         if (l_test >= l_tempOffset)
         {
            std::string n = "Chassis fault";
            l_status = -1;
            l_info.set_message(n.data(),n.size());
            l_info.set_status(l_status);
            stream->Write(l_info);
         }
         else
         {
            std::string n = "No Error";
            l_status = 0;
            l_info.set_message(n.data(),n.size());
            l_info.set_status(l_status);
            stream->Write(l_info);
         }

         if (l_context->IsCancelled())
         {
            std::cout<<"Channel 1 is unsubscribed" << std::endl << std::endl;
            return Status::CANCELLED;
         }
         std::cout<<std::endl;
         return Status::OK;
      }
	}

   Status SetAttribute(ServerContext* a_pContext, const SetAttrRequest* a_pRequest, StatusResponse* a_pResponse) override
   {
       return Status::OK;
   }

   Status GetAttribute(ServerContext* a_pContext, const GetAttrRequest* a_pRequest, GetAttrResponse* a_pResponse) override
   {
      try
      {
         switch (a_pRequest->attr())
         {
            case rcuservice::Attribute::Attr_UTF8_TempName_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_tempNames : m_tempNames)
                  {
                     a_pResponse->mutable_value()->mutable_utf8arr()->add_d(l_tempNames.data(), l_tempNames.size());
                  }
               }
               else
               {
                  std::string l_displayName = m_tempNames.at(a_pRequest->index());
                  a_pResponse->mutable_value()->set_utf8(l_displayName);
               }
               break;
            }
            case rcuservice::Attribute::Attr_UTF8_AmpName_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_ampNames : m_ampNames)
                  {
                     a_pResponse->mutable_value()->mutable_utf8arr()->add_d(l_ampNames.data(), l_ampNames.size());
                  }
               }
               else
               {
                  std::string l_displayName = m_ampNames.at(a_pRequest->index());
                  a_pResponse->mutable_value()->set_utf8(l_displayName);
               }
               break;
            }
            case rcuservice::Attribute::Attr_U32_FanRpm_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_fanNames : m_fanNames)
                  {
                     double l_fanReading = rand() % 100;
                     a_pResponse->mutable_value()->mutable_dblarr()->add_d(l_fanReading);
                     std::cout << "check after case: " << l_fanReading << std::endl;
                  }
               }
               else
               {
                  double l_fanReading = rand() % 50;
                  a_pResponse->mutable_value()->set_dbl(l_fanReading);
               }
               break;
            }
            case rcuservice::Attribute::Attr_U32_FanCount:
            {
               a_pResponse->mutable_value()->set_u32(m_fanNames.size());
               break;
            }
            case rcuservice::Attribute::Attr_UTF8_FanName_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_fanNames : m_fanNames)
                  {
                     a_pResponse->mutable_value()->mutable_utf8arr()->add_d(l_fanNames.data(), l_fanNames.size());
                  }
               }
               else
               {
                  std::string l_displayName = m_fanNames.at(a_pRequest->index());
                  a_pResponse->mutable_value()->set_utf8(l_displayName);
               }
               break;
            }
            case rcuservice::Attribute::Attr_U32_FanDomainIndex_N:
            case rcuservice::Attribute::Attr_U32_FanDomain_N:
            case rcuservice::Attribute::Attr_U32_FanDomainMode_N:
            case rcuservice::Attribute::Attr_U32_FanDomainCount:
            {
               break;
            }
            case rcuservice::Attribute::Attr_U32_TempCount:
            {
               a_pResponse->mutable_value()->set_u32(m_tempNames.size());
               break;
            }
            case rcuservice::Attribute::Attr_U32_VoltCount: // (Unsupported at this moment, low level function not yet implemented)
            {
               a_pResponse->mutable_value()->set_u32(m_voltNames.size());
               break;
            }
            case rcuservice::Attribute::Attr_U32_AmpCount:
            {
               a_pResponse->mutable_value()->set_u32(m_ampNames.size());
               break;
            }
            case rcuservice::Attribute::Attr_DBL_VoltReading_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_voltNames : m_voltNames)
                  {
                     double l_voltReading = rand() % 25;
                     a_pResponse->mutable_value()->mutable_dblarr()->add_d(l_voltReading);
                  }
               }
               else
               {
                  double l_voltReading = rand() % 25;
                  a_pResponse->mutable_value()->set_dbl(l_voltReading);
               }
               break;
            }
            case rcuservice::Attribute::Attr_DBL_TempReadingC_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_tempNames : m_tempNames)
                  {
                     double l_tempReading = rand() % 56 + 25;
                     a_pResponse->mutable_value()->mutable_dblarr()->add_d(l_tempReading);
                  }
               }
               else
               {
                  double l_tempReading = rand() % 8 + 25;
                  a_pResponse->mutable_value()->set_dbl(l_tempReading);
               }
               break;
            }
            case rcuservice::Attribute::Attr_DBL_AmpReading_N:
            {
               if (a_pRequest->index() == rcuservice::constants::Ndx_All_Available_Indices)
               {
                  for (const auto& l_ampNames : m_ampNames)
                  {
                     double l_ampReading = rand() % 25;
                     a_pResponse->mutable_value()->mutable_dblarr()->add_d(l_ampReading);
                  }
               }
               else
               {
                  double l_ampReading = rand() % 25;
                  a_pResponse->mutable_value()->set_dbl(l_ampReading);
               }
               break;
            }
         }
      }
      catch (std::exception& e)
      {
         printf("%s\n", e.what());
      }

      return Status::OK;
   }

private:
   // Helper method so we can get all indices
   // template<typename VALUE_DATATYPE>
   // void _getAllIndices (uint32_t a_Attribute, const std::function<void(VALUE_DATATYPE&)>& a_addFunc);

   std::unique_ptr<grpc::Server> m_server;

   std::vector <std::string> m_tempNames = {"Temp 1", "Temp 2", "Temp 3", "Temp 4"};
   std::vector <std::string> m_ampNames = {"Current 1", "Current 2", "Current 3", "Current 4"};
   std::vector <std::string> m_fanNames = {"Fan 1", "Fan 2", "Fan 3", "Fan 4"};
   std::vector <std::string> m_voltNames = {"Voltage 1", "Voltage 2", "Voltage 3", "Voltage 4"};
};

void l_RunServer()
{
   std::string l_serverAddr("0.0.0.0:50051");
   tAteCoreCntApiServiceImpl l_service;
   grpc::EnableDefaultHealthCheckService(true);
   grpc::reflection::InitProtoReflectionServerBuilderPlugin();
   ServerBuilder l_builder;
   l_builder.AddListeningPort(l_serverAddr, grpc::InsecureServerCredentials());
   l_builder.RegisterService(&l_service);
   std::unique_ptr<Server> server(l_builder.BuildAndStart());
   std::cout << "Server listening on " << l_serverAddr << std::endl;
   server->Wait();
}

int main(int argc, char** argv)
{
   l_RunServer();
   return 0;
}
