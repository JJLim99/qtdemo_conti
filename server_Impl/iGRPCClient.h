////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements the iGRPCClient to define the interface of tMockClient.h in
//   server_Impl
////////////////////////////////////////////////////////////////////////////////

#ifndef ___iGRPCClient_h___
#define ___iGRPCClient_h___

#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::AnyNumber;

class iGRPCClient
{
public:
   virtual uint32_t getTempCount() = 0;
   virtual uint32_t getAmpCount() = 0;
   virtual uint32_t getVoltCount() = 0;
   virtual uint32_t getFanCount() = 0;

   virtual std::vector <std::string> getTempNames() = 0;
   virtual std::vector <std::string> getAmpNames() = 0;
   virtual std::vector <std::string> getVoltNames() = 0;
   virtual std::vector <std::string> getFanNames() = 0;

   virtual std::vector <double> getTempReadings() = 0;
   virtual std::vector <double> getAmpReadings() = 0;
   virtual std::vector <double> getVoltReadings() = 0;
   virtual std::vector <uint32_t> getFanReadings() = 0;
};

#endif
