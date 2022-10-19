////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements the tMockClient to mock the gRPC Client Behaviour in server_Impl
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ___tMockClient_h___
#define ___tMockClient_h___

#include "iGRPCClient.h"

class tMockClient : public iGRPCClient
{
public:
   MOCK_METHOD0(getTempCount,uint32_t());
   MOCK_METHOD0(getAmpCount,uint32_t());
   MOCK_METHOD0(getVoltCount,uint32_t());
   MOCK_METHOD0(getFanCount,uint32_t());

   MOCK_METHOD0(getTempNames, std::vector <std::string> ());
   MOCK_METHOD0(getAmpNames, std::vector <std::string> ());
   MOCK_METHOD0(getVoltNames, std::vector <std::string> ());
   MOCK_METHOD0(getFanNames, std::vector <std::string> ());

   MOCK_METHOD0(getTempReadings, std::vector <double> ());
   MOCK_METHOD0(getAmpReadings, std::vector <double> ());
   MOCK_METHOD0(getVoltReadings, std::vector <double> ());
   MOCK_METHOD0(getFanReadings, std::vector <uint32_t> ());
};

#endif
