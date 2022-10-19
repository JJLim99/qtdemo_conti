# LCDAppPrototype
This project is the LCD Application Prototype. It is the combination of Qt GUI, gRPC and Google Mock. Use any code editor (e.g. Visual Studio Code) to view and edit the code.
## Demo
Coming soon...
## Project Rquirement
* cmake version >= 3.14<br/>
* Qt version >= 5.12<br/>
* gRPC<br/>
* Google Test/Mock<br/><br/>

*Remark:*<br/>
* *Ubuntu 18.04 provides qt-5.9.5 as default*<br/>
* *Ubuntu 20.04 provides qt-5.12.8 as default*<br/>
* *Change the default qt path if necessary to make sure the qt version is compatible with the project requirement*

## Project Configuration
### Using Linux Terminal
1. Install the necessary Qt libraries by using the following command
```
sudo apt update
sudo apt-get install libxcb-xinerama0
sudo apt-get install mesa-common-dev libglu1-mesa-dev

sudo apt-get install qt5-default
sudo apt-get install qmlscene
sudo apt-get install qtdeclarative5-dev
sudo apt-get install qml-module-qtquick-controls
sudo apt-get install qml-module-qtquick-dialogs
sudo apt-get install -y qml-module-qtquick-controls2
sudo apt-get install -y qml-module-qtquick-extras
sudo apt-get install qml-module-qtquick2
sudo apt-get install libqt5charts5-dev
sudo apt-get install qttools5-dev
sudo apt-get install qml-module-qtcharts
sudo apt-get install qml-module-qtquick-particles2
sudo apt-get install libqt5concurrent5
sudo apt-get install -y qml-module-qtquick-shapes
```
2. Install gRPC C++ based on the instructions in https://grpc.io/docs/languages/cpp/quickstart/ <br/>
## Usage
1. Git clone the project repository into your preferable path.<br/>
2. Open the project to view the code by choosing your preferable code editor (e.g. Visual Studio Code).<br/>
### Run server
3. Open Terminal, switch to the server_Impl directory which contains CMakeLists.txt. Compile the project by using the following commands
```
cmake .
make -j
```
4. Run binary executable file of gRPC server
```
./<bin file>
```
### Run Qt Application
5. Open Terminal, switch to the main directory which contains CMakeLists.txt. Compile the project by using the following commands<br/>
```
cmake .
make -j
```
6. Run binary executable file of Qt Application<br/>
```
./<bin file>
```
## Output</br>
Qt Application will be updated by gRPC server which is executed in server_Impl. It will be updated by Google Mock if the gRPC server is closed.<br/>
## Project Structure
<pre>
grpcLCD
├── CMakeLists.txt
├── GUI
│   └── DashboardGaugeStyle.qml
├── iGRPCClient.h
├── main.cpp
├── main.qml
├── Pg01_GaugeDashboard.qml
├── Pg02_Chart.qml
├── qml.qrc
├── rcu-service.proto
├── README.md
├── server_Impl
│   ├── client.cpp
│   ├── CMakeLists.txt
│   ├── iGRPCClient.h
│   ├── rcu-service.proto
│   ├── server.cpp
│   ├── tAteCoreCntApiClientImpl.cpp
│   ├── tAteCoreCntApiClientImpl.h
│   └── tMockClient.h
├── tAteCoreCntApiClientImpl.cpp
├── tAteCoreCntApiClientImpl.h
├── tGRPCPull.cpp
├── tGRPCPush.h
└── tMockClient.h
</pre>
## Reference
1. https://doc.qt.io/qt-5/qtexamplesandtutorials.html (Qt Documentation)
2. https://grpc.io/docs/languages/cpp/quickstart/
3. https://github.com/google/googletest.git
## License
1. Copyright (C) 2018 The Qt Company Ltd. (https://doc.qt.io/qt-5/examples-license.html)
2. Apache License 2.0 (https://github.com/grpc/grpc/blob/master/LICENSE)
3. BSD 3-Clause (https://github.com/google/googletest/blob/master/LICENSE)
