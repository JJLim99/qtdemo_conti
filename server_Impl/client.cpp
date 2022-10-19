////////////////////////////////////////////////////////////////////////////////
//
// Purpose:
//   Implements gRPC client which is used for testing purpose in server_Impl
//   
////////////////////////////////////////////////////////////////////////////////

#include "tAteCoreCntApiClientImpl.h"

int main()
{
   for(;;)
   {
      g_runClient();
      std::cout << "Status code: " << g_statusCode << std::endl;
      std::cout << "Fan 0: " << g_FanReadings[0] << std::endl;
      std::cout << "Fan 1: " << g_FanReadings[1] << std::endl;
   }
}
