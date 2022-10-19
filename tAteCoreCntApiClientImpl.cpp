#include "tAteCoreCntApiClientImpl.h"

// Function definition of push notification using bidirectional RPC
void tAteCoreCntApiClientImpl::pushNoti()
{
   ClientContext l_context;
 	Info l_info;
	std::shared_ptr<ClientReaderWriter<Info,Info>>stream(stub_->PushNoti(&l_context));
   std::string l_statusMessage = "No error";
   while (stream->Read(&l_info))
   {
      g_statusCode = l_info.status();
      g_statusMessage = l_info.message();
   }
}

// Function definition of pull data using unary RPC
uint32_t tAteCoreCntApiClientImpl::getTempCount()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_U32_TempCount);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);
   if (l_status.ok())
   {
      return l_reply.value().u32();
   }
   else 
   {
      return 0;
   }
}

uint32_t tAteCoreCntApiClientImpl::getAmpCount()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_U32_AmpCount);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);
   if (l_status.ok())
   {
      return l_reply.value().u32();
   }
   else 
   {
      return 0;
   }
}

uint32_t tAteCoreCntApiClientImpl::getVoltCount()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_U32_VoltCount);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);
   if (l_status.ok())
   {
      return l_reply.value().u32();
   }
   else 
   {
      return 0;
   }
}

uint32_t tAteCoreCntApiClientImpl::getFanCount()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_U32_FanCount);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);
   if (l_status.ok())
   {
      return l_reply.value().u32();
   }
   else 
   {
      return 0;
   }
}

std::vector <std::string> tAteCoreCntApiClientImpl::getTempNames()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_UTF8_TempName_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <std::string> l_tempNames;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().utf8arr().d_size();i ++)
      {
         std::string l_displayNames = l_reply.value().utf8arr().d(i);
         l_tempNames.push_back(l_displayNames);
      }
      return l_tempNames;
   }
}

std::vector <std::string> tAteCoreCntApiClientImpl::getAmpNames()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_UTF8_AmpName_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <std::string> l_AmpNames;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().utf8arr().d_size();i ++)
      {
         std::string l_displayNames = l_reply.value().utf8arr().d(i);
         l_AmpNames.push_back(l_displayNames);
      }
      return l_AmpNames;
   }
}

std::vector <std::string> tAteCoreCntApiClientImpl::getVoltNames()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_UTF8_VoltName_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <std::string> l_VoltName;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().utf8arr().d_size();i ++)
      {
         std::string l_displayName = l_reply.value().utf8arr().d(i);
         l_VoltName.push_back(l_displayName);
      }
      return l_VoltName;
   }
}

std::vector <std::string> tAteCoreCntApiClientImpl::getFanNames()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_UTF8_FanName_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <std::string> l_FanName;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().utf8arr().d_size();i ++)
      {
         std::string l_displayName = l_reply.value().utf8arr().d(i);
         l_FanName.push_back(l_displayName);
      }
      return l_FanName;
   }
}

std::vector <double> tAteCoreCntApiClientImpl::getTempReadings()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_DBL_TempReadingC_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <double> l_TempReadings;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().dblarr().d_size();i ++)
      {
         double l_displayReadings = l_reply.value().dblarr().d(i);
         l_TempReadings.push_back(l_displayReadings);
      }
      return l_TempReadings;
   }
}

std::vector <double> tAteCoreCntApiClientImpl::getAmpReadings()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_DBL_AmpReading_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <double> l_AmpReadings;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().dblarr().d_size();i ++)
      {
         double l_displayReadings = l_reply.value().dblarr().d(i);
         l_AmpReadings.push_back(l_displayReadings);
      }
      return l_AmpReadings;
   }
}

std::vector <double> tAteCoreCntApiClientImpl::getVoltReadings()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_DBL_VoltReading_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <double> l_VoltReadings;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().dblarr().d_size();i ++)
      {
         double l_displayReadings = l_reply.value().dblarr().d(i);
         l_VoltReadings.push_back(l_displayReadings);
      }
      return l_VoltReadings;
   }
}

std::vector <uint32_t> tAteCoreCntApiClientImpl::getFanReadings()
{
   GetAttrRequest l_request;
   l_request.set_attr(rcuservice::Attribute::Attr_U32_FanRpm_N);
   l_request.set_index(rcuservice::constants::Ndx_All_Available_Indices);

   GetAttrResponse l_reply;
   ClientContext l_context;

   Status l_status = stub_->GetAttribute(&l_context, l_request, &l_reply);

   std::vector <uint32_t> l_FanReadings;

   if (l_status.ok())
   {
      for (int i = 0;i < l_reply.value().dblarr().d_size();i ++)
      {
         uint32_t l_displayReadings = l_reply.value().dblarr().d(i);
         l_FanReadings.push_back(l_displayReadings);
      }
      return l_FanReadings;
   }
}

// Global variable initialization
uint32_t g_tempCount = 0;
uint32_t g_ampCount = 0;
uint32_t g_voltCount = 0;
uint32_t g_fanCount = 0;

std::vector <std::string> g_TempNames = {"a","b","c","d"};
std::vector <std::string> g_AmpNames = {"a","b","c","d"};
std::vector <std::string> g_VoltNames = {"a","b","c","d"};
std::vector <std::string> g_FanNames = {"a","b","c","d"};

std::vector <double> g_TempReadings = {0};
std::vector <double> g_AmpReadings = {0};
std::vector <double> g_VoltReadings = {0};
std::vector <uint32_t> g_FanReadings = {0};

int32_t g_statusCode = 0;
std::string g_statusMessage = "No Error";

// gRPC Client definition
void g_runClient()
{
   std::string l_targetAddr = "localhost:50051";
   tAteCoreCntApiClientImpl l_client(grpc::CreateChannel(l_targetAddr, grpc::InsecureChannelCredentials()));

   std::thread l_pullThread(
      [&]()
      {
         tMockClient l_mockClient;

         EXPECT_CALL(l_mockClient, getTempCount()).Times(AnyNumber()).WillRepeatedly(Return(4));
         EXPECT_CALL(l_mockClient, getAmpCount()).Times(AnyNumber()).WillRepeatedly(Return(4));
         EXPECT_CALL(l_mockClient, getVoltCount()).Times(AnyNumber()).WillRepeatedly(Return(4));
         EXPECT_CALL(l_mockClient, getFanCount()).Times(AnyNumber()).WillRepeatedly(Return(4));

         EXPECT_CALL(l_mockClient, getTempNames()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <std::string> ({"Temp 1", "Temp 2", "Temp 3", "Temp 4"})));
         EXPECT_CALL(l_mockClient, getAmpNames()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <std::string> ({"Amp 1", "Amp 2", "Amp 3", "Amp 4"})));
         EXPECT_CALL(l_mockClient, getVoltNames()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <std::string> ({"Volt 1", "Volt 2", "Volt 3", "Volt 4"})));
         EXPECT_CALL(l_mockClient, getFanNames()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <std::string> ({"Fan 1", "Fan 2", "Fan 3", "Fan 4"})));
         
         EXPECT_CALL(l_mockClient, getTempReadings()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <double> ({rand() % 25, rand() % 25, rand() % 25, rand() % 25})));
         EXPECT_CALL(l_mockClient, getAmpReadings()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <double> ({rand() % 25, rand() % 25, rand() % 25, rand() % 25})));
         EXPECT_CALL(l_mockClient, getVoltReadings()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <double> ({rand() % 25, rand() % 25, rand() % 25, rand() % 25})));
         EXPECT_CALL(l_mockClient, getFanReadings()).Times(AnyNumber()).WillRepeatedly(Return(std::vector <uint32_t> ({rand() % 25, rand() % 25, rand() % 25, rand() % 25})));

         std::vector <std::string> l_TempNames;
         std::vector <std::string> l_AmpNames;
         std::vector <std::string> l_VoltNames;
         std::vector <std::string> l_FanNames;
        
         std::vector <double> l_TempReadings;
         std::vector <double> l_AmpReadings;
         std::vector <double> l_VoltReadings;
         std::vector <uint32_t> l_FanReadings;

         if (l_client.getTempCount() != 0)
         {
            g_tempCount = l_client.getTempCount();
         }
         else
         {
            g_tempCount = l_mockClient.getTempCount();
         }

         if (l_client.getAmpCount() != 0)
         {
            g_ampCount = l_client.getAmpCount();
         }
         else
         {
            g_ampCount = l_mockClient.getAmpCount();
         }

         if (l_client.getVoltCount() != 0)
         {
            g_voltCount = l_client.getVoltCount();
         }
         else
         {
            g_voltCount = l_mockClient.getVoltCount();
         }

         if (l_client.getFanCount() != 0)
         {
            g_fanCount = l_client.getFanCount();
         }
         else
         {
            g_fanCount = l_mockClient.getFanCount();
         }

         if (l_client.getTempNames().size() != 0)
         {
            for (int i = 0;i < l_client.getTempNames().size();i ++)
            {
               l_TempNames.push_back(l_client.getTempNames()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getTempNames().size();i ++)
            {
               l_TempNames.push_back(l_mockClient.getTempNames()[i]);
            }
         }

         if (l_client.getAmpNames().size() != 0)
         {
            for (int i = 0;i < l_client.getAmpNames().size();i ++)
            {
               l_AmpNames.push_back(l_client.getAmpNames()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getAmpNames().size();i ++)
            {
               l_AmpNames.push_back(l_mockClient.getAmpNames()[i]);
            }
         }

         // Volt Names not available

         if (l_client.getFanNames().size() != 0)
         {
            for (int i = 0;i < l_client.getFanNames().size();i ++)
            {
               l_FanNames.push_back(l_client.getFanNames()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getFanNames().size();i ++)
            {
               l_FanNames.push_back(l_mockClient.getFanNames()[i]);
            }
         }

         if (l_client.getFanReadings().size() != 0)
         {
            for (int i = 0;i < l_client.getTempReadings().size();i ++)
            {
               l_TempReadings.push_back(l_client.getTempReadings()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getTempNames().size();i ++)
            {
               l_TempReadings.push_back(l_mockClient.getTempReadings()[i]);
            }
         }

         if (l_client.getAmpReadings().size() != 0)
         {
            for (int i = 0;i < l_client.getAmpReadings().size();i ++)
            {
               l_AmpReadings.push_back(l_client.getAmpReadings()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getAmpNames().size();i ++)
            {
               l_AmpReadings.push_back(l_mockClient.getAmpReadings()[i]);
            }
         }

         if (l_client.getVoltReadings().size() != 0)
         {
            for (int i = 0;i < l_client.getVoltReadings().size();i ++)
            {
               l_VoltReadings.push_back(l_client.getVoltReadings()[i]);
             }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getVoltNames().size();i ++)
            {
                l_VoltReadings.push_back(l_mockClient.getVoltReadings()[i]);
            }
         }

         if (l_client.getFanReadings().size() != 0)
         {
            for (int i = 0;i < l_client.getFanReadings().size();i ++)
            {
               l_FanReadings.push_back(l_client.getFanReadings()[i]);
            }
         }
         else
         {
            for (int i = 0;i < l_mockClient.getFanNames().size();i ++)
            {
               l_FanReadings.push_back(l_mockClient.getFanReadings()[i]);
            }
         }

         g_TempNames = l_TempNames;
         g_AmpNames = l_AmpNames;
         g_VoltNames = l_VoltNames;
         g_FanNames = l_FanNames;

         g_TempReadings = l_TempReadings;
         g_AmpReadings = l_AmpReadings;
         g_VoltReadings = l_VoltReadings;
         g_FanReadings = l_FanReadings;
      }
   );

   std::thread l_pushThread(
      [&]()
      {
         l_client.pushNoti();
      }
   );

   if (l_pullThread.joinable())
   {
      l_pullThread.join();
   }

   if (l_pushThread.joinable())
   {
      l_pushThread.join();
   }
}
