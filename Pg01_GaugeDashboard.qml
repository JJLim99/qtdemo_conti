import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import "GUI"
import tGRPCPush 1.0
import tGRPCPull 1.0

Item {
   objectName: "win"
   id: win
   width: 1080
   height: 720
   property int windowStatus: 0
   property bool powerOn: false
   property int pState: 0
   property int sliderOn: 0
   property int maxH: Screen.height - 50
   property int maxW: Screen.width - 50

   PushNoti {
      id: qmlPush
   }

   PullInfo {
      id: qmlPull
   }

   MouseArea {
      width: parent.width
      height: parent.height
      anchors.centerIn: parent

      onClicked: {
         powerOn = !powerOn
         qmlPush.start()
         qmlPull.start()
      }

      onDoubleClicked: {
         if (pState == 0) {
            winChild.width = parent.height
            winChild.height = parent.width
            pState = !pState
            winChild.rotation = 90
            rotation = 90
         }
         else {
            winChild.width = parent.width
            winChild.height = parent.height
            winChild.rotation = 0
            pState = !pState
            rotation = 0
         }
      }
   }

   /* Circular Gauge */
   Item {
      objectName: "winChild"
      id: winChild
      width: parent.width
      height: parent.height
      anchors.horizontalCenter : parent.horizontalCenter
      anchors.verticalCenter : parent.verticalCenter

      Grid {
         id: viewGauge
         width: parent.width * 0.45
         height: parent.height * (1 - 0.02)
         anchors.top: parent.top
         anchors.topMargin: parent.height * 0.02
         anchors.left: parent.left
         columns: 2
         rows: 2
         spacing: parent.height * 0.02

         Item {
            width: viewGauge.width * 0.5
            height: viewGauge.height * 0.5

            CircularGauge {
               id: gaugeRPM1
               objectName: "gaugeRPM1"
               value: sliderOn == 1? control.value : qmlPull.valRPM1
               maximumValue: 100
               anchors.top: parent.top
               anchors.horizontalCenter: parent.horizontalCenter
               width: parent.width * 0.9
               height: parent.height * 0.75
               property bool accelerating: false

               Keys.onSpacePressed: accelerating = true
               Keys.onReleased: {
                  if (event.key === Qt.Key_Space) {
                     accelerating = false;
                     event.accepted = true;
                  }
               }

               Component.onCompleted: forceActiveFocus()

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: DashboardGaugeStyle {}
            }

            DropShadow {
               id: shadow1
               objectName: "shadow1"
               anchors.fill: gaugeRPM1
               horizontalOffset: 3
               verticalOffset: 3
               radius: 100
               samples: 100
               color: gaugeRPM1.value >= 80 ? "red" : gaugeRPM1.value >= 50 && gaugeRPM1.value < 80 ? "#ff8400" : gaugeRPM1.value > 0 && gaugeRPM1.value < 50 ? "#39ff14" : "transparent"
               source: gaugeRPM1

               SequentialAnimation on color {
                  id: aniShadow1
                  running: (powerOn == true) && (gaugeRPM1.value >= 90) ? true : false
                  loops: Animation.Infinite
                  ColorAnimation {from: "red"; to: "transparent"; duration: 500}
               }
            }

            Item {
               width: parent.width * 0.8
               height: parent.height * 0.125
               anchors.top: gaugeRPM1.bottom
               anchors.topMargin: parent.width * 0.025
               anchors.horizontalCenter: parent.horizontalCenter

               StatusIndicator {
                  id: indicator
                  color: gaugeRPM1.value === 0 ? "red" : "#39ff14"
                  height: parent.height * 0.9
                  width: parent.width * 0.2
                  anchors.left: parent.left
                  anchors.leftMargin: parent.width * 0.10
                  anchors.top: parent.top
                  active: true
               }

               Text {
                  id: txtGaugeRPM1
                  height: parent.height * 0.9
                  width: parent.width * 0.4
                  anchors.centerIn: parent
                  text: qsTr(" ") + qmlPull.nameFan1
                  color: gaugeRPM1.value === 0 ? "red" : "#39ff14"
                  font.bold: true
                  font.pointSize: 60
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            width: viewGauge.width * 0.5
            height: viewGauge.height * 0.5

            CircularGauge {
               id: gaugeRPM2
               objectName: "gaugeRPM2"
               value: sliderOn == 1? control.value : qmlPull.valRPM2
               maximumValue: 100
               anchors.top: parent.top
               anchors.horizontalCenter: parent.horizontalCenter
               width: parent.width * 0.9
               height: parent.height * 0.75
               property bool accelerating: false

               Keys.onSpacePressed: accelerating = true
               Keys.onReleased: {
                  if (event.key === Qt.Key_Space) {
                     accelerating = false;
                     event.accepted = true;
                  }
               }

               Component.onCompleted: forceActiveFocus()

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: DashboardGaugeStyle {}
            }

            DropShadow {
               id: shadow2
               objectName: "shadow2"
               anchors.fill: gaugeRPM2
               horizontalOffset: 3
               verticalOffset: 3
               radius: 100
               samples: 100
               color: gaugeRPM2.value >= 80 ? "red" : gaugeRPM2.value >= 50 && gaugeRPM2.value < 80 ? "#ff8400" : gaugeRPM2.value > 0 && gaugeRPM2.value < 50 ? "#39ff14" : "transparent"
               source: gaugeRPM2

               SequentialAnimation on color {
                  id: aniShadow2
                  running: (powerOn == true) && (gaugeRPM2.value >= 90) ? true : false
                  loops: Animation.Infinite
                  ColorAnimation {from: "red"; to: "transparent"; duration: 500}
               }
            }

            Item {
               width: parent.width * 0.8
               height: parent.height * 0.125
               anchors.top: gaugeRPM2.bottom
               anchors.topMargin: parent.width * 0.025
               anchors.horizontalCenter: parent.horizontalCenter

               StatusIndicator {
                  id: indicator2
                  color: gaugeRPM2.value === 0 ? "red" : "#39ff14"
                  height: parent.height * 0.9
                  width: parent.width * 0.2
                  anchors.left: parent.left
                  anchors.leftMargin: parent.width * 0.10
                  anchors.top: parent.top
                  active: true
               }

               Text {
                  id: txtGaugeRPM2
                  height: parent.height * 0.9
                  width: parent.width * 0.4
                  anchors.centerIn: parent
                  text: qsTr(" ") + qmlPull.nameFan2
                  color: gaugeRPM2.value === 0 ? "red" : "#39ff14"
                  font.bold: true
                  font.pointSize: 60
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            width: viewGauge.width * 0.5
            height: viewGauge.height * 0.5

            CircularGauge {
               id: gaugeRPM3
               objectName: "gaugeRPM3"
               value: sliderOn == 1? control.value : qmlPull.valRPM3
               maximumValue: 100
               anchors.top: parent.top
               anchors.horizontalCenter: parent.horizontalCenter
               width: parent.width * 0.9
               height: parent.height * 0.75
               property bool accelerating: false

               Keys.onSpacePressed: accelerating = true
               Keys.onReleased: {
                  if (event.key === Qt.Key_Space) {
                     accelerating = false;
                     event.accepted = true;
                  }
               }

               Component.onCompleted: forceActiveFocus()

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: DashboardGaugeStyle {}
            }

            DropShadow {
               id: shadow3
               objectName: "shadow3"
               anchors.fill: gaugeRPM3
               horizontalOffset: 3
               verticalOffset: 3
               radius: 100
               samples: 100
               color: gaugeRPM4.value >= 90 ? "red" : gaugeRPM3.value >= 50 && gaugeRPM3.value < 80 ? "#ff8400" : gaugeRPM3.value > 0 && gaugeRPM3.value < 50 ? "#39ff14" : "transparent"
               source: gaugeRPM3

               SequentialAnimation on color {
                  id: aniShadow3
                  running: (powerOn == true) && (gaugeRPM4.value >= 90) ? true : false
                  loops: Animation.Infinite
                  ColorAnimation {from: "red"; to: "transparent"; duration: 500}
               }
            }

            Item {
               width: parent.width * 0.8
               height: parent.height * 0.125
               anchors.top: gaugeRPM3.bottom
               anchors.topMargin: parent.width * 0.025
               anchors.horizontalCenter: parent.horizontalCenter

               StatusIndicator {
                  id: indicator3
                  color: gaugeRPM3.value === 0 ? "red" : "#39ff14"
                  height: parent.height * 0.9
                  width: parent.width * 0.2
                  anchors.left: parent.left
                  anchors.leftMargin: parent.width * 0.10
                  anchors.top: parent.top
                  active: true
               }

               Text {
                  id: txtGaugeRPM3
                  height: parent.height * 0.9
                  width: parent.width * 0.4
                  anchors.centerIn: parent
                  text: qsTr(" ") + qmlPull.nameFan3
                  color: gaugeRPM3.value === 0 ? "red" : "#39ff14"
                  font.bold: true
                  font.pointSize: 60
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            width: viewGauge.width * 0.5
            height: viewGauge.height * 0.5

            CircularGauge {
               id: gaugeRPM4
               objectName: "gaugeRPM"
               value: sliderOn == 1? control.value : qmlPull.valRPM4
               maximumValue: 100
               anchors.top: parent.top
               anchors.horizontalCenter: parent.horizontalCenter
               width: parent.width * 0.9
               height: parent.height * 0.75
               property bool accelerating: false

               Keys.onSpacePressed: accelerating = true
               Keys.onReleased: {
                  if (event.key === Qt.Key_Space) {
                     accelerating = false;
                     event.accepted = true;
                  }
               }

               Component.onCompleted: forceActiveFocus()

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: DashboardGaugeStyle {}
            }

            DropShadow {
               id: shadow4
               objectName: "shadow4"
               anchors.fill: gaugeRPM4
               horizontalOffset: 3
               verticalOffset: 3
               radius: 100
               samples: 100
               color: gaugeRPM4.value >= 80 ? "red" : gaugeRPM4.value >= 50 && gaugeRPM4.value < 80? "#ff8400" : gaugeRPM4.value > 0 && gaugeRPM4.value < 50 ? "#39ff14" : "transparent"
               source: gaugeRPM4

               SequentialAnimation on color {
                  id: aniShadow4
                  running: (powerOn == true) && (gaugeRPM4.value >= 90) ? true : false
                  loops: Animation.Infinite
                  ColorAnimation {from: "red"; to: "transparent"; duration: 500}
               }
            }

            Item {
               width: parent.width * 0.8
               height: parent.height * 0.125
               anchors.top: gaugeRPM4.bottom
               anchors.topMargin: parent.width * 0.025
               anchors.horizontalCenter: parent.horizontalCenter

               StatusIndicator {
                  id: indicator4
                  color: gaugeRPM4.value === 0 ? "red" : "#39ff14"
                  height: parent.height * 0.9
                  width: parent.width * 0.2
                  anchors.left: parent.left
                  anchors.leftMargin: parent.width * 0.10
                  anchors.top: parent.top
                  active: true
               }

               Text {
                  id: txtGaugeRPM4
                  height: parent.height * 0.9
                  width: parent.width * 0.4
                  anchors.centerIn: parent
                  text: qsTr(" ") + qmlPull.nameFan4
                  color: gaugeRPM4.value === 0 ? "red" : "#39ff14"
                  font.bold: true
                  font.pointSize: 60
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }
      }

      /* Vertical Gauge */
      Grid {
         id: viewTempIV
         width: parent.width * 0.25
         height: parent.height
         anchors.top: parent.top
         anchors.topMargin: parent.height * 0.01
         anchors.left: viewGauge.right
         anchors.leftMargin: parent.width * 0.04
         columns: 2
         rows: 2

         Item {
            width: viewTempIV.width * 0.5
            height: viewTempIV.height * 0.5

            Gauge {
               id: gauge1
               width: parent.width * 0.75
               height: parent.height * 0.8
               minimumValue: 0
               value: qmlPull.valTemp1
               maximumValue: 100
               anchors.horizontalCenter : parent.horizontalCenter
               font.pointSize: 10
               font.bold: true
               minorTickmarkCount : 4

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: GaugeStyle {
                  valueBar: Rectangle {
                  implicitWidth: 16
                  color: gauge1.value >= 80 ? "red" : gauge1.value >= 50 && gauge1.value < 80 ? "orange" : "#33FF57"
                  }
               }
            }

            Text {
               id: textArea
               width: gauge1.width
               height: parent.height * 0.2
               anchors.top: gauge1.bottom
               anchors.topMargin: parent.height * 0.01
               text: qsTr(" ") + qmlPull.nameTemp1
               color: gauge1.value >= 80 ? "red" : gauge1.value >= 50 && gauge1.value < 80 ? "#FFBD33" : "#33FF57"
               font.bold: true
               font.pointSize: 11
               minimumPointSize: 10
               anchors.horizontalCenter: parent.horizontalCenter
            }
         }

         Item {
            width: viewTempIV.width * 0.5
            height: viewTempIV.height * 0.5

            Gauge {
               id: gauge2
               width: parent.width * 0.75
               height: parent.height * 0.8
               minimumValue: 0
               value: qmlPull.valTemp2
               maximumValue: 100
               anchors.horizontalCenter : parent.horizontalCenter
               font.pointSize: 10
               font.bold: true
               minorTickmarkCount : 4

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: GaugeStyle {
                  valueBar: Rectangle {
                  implicitWidth: 16
                  color: gauge2.value >= 80 ? "red" : gauge2.value >= 50 && gauge2.value < 80 ? "orange" : "#33FF57"
                  }
               }
            }

            Text {
               id: textArea2
               width: gauge2.width
               height: parent.height * 0.2
               anchors.top: gauge2.bottom
               anchors.topMargin: parent.height * 0.01
               text: qsTr(" ") + qmlPull.nameTemp2
               color: gauge2.value >= 80 ? "red" : gauge2.value >= 50 && gauge2.value < 80 ? "#FFBD33" : "#33FF57"
               font.bold: true
               font.pointSize: 11
               minimumPointSize: 10
               anchors.horizontalCenter: parent.horizontalCenter
            }
         }

         Item {
            width: viewTempIV.width * 0.5
            height: viewTempIV.height * 0.5

            Gauge {
               id: gauge3
               width: parent.width * 0.75
               height: parent.height * 0.8
               minimumValue: 0
               value: qmlPull.valTemp3
               maximumValue: 100
               anchors.horizontalCenter : parent.horizontalCenter
               font.pointSize: 10
               font.bold: true
               minorTickmarkCount : 4

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: GaugeStyle {
                  valueBar: Rectangle {
                  implicitWidth: 16
                  color: gauge3.value >= 80 ? "red" : gauge3.value >= 50 && gauge3.value < 80 ? "orange" : "#33FF57"
                  }
               }
            }

            Text {
               id: textArea3
               width: gauge3.width
               height: parent.height * 0.2
               anchors.top: gauge3.bottom
               anchors.topMargin: parent.height * 0.01
               text: qsTr(" ") + qmlPull.nameTemp3
               color: gauge3.value >= 80 ? "red" : gauge3.value >= 50 && gauge3.value < 80 ? "orange" : "#33FF57"
               font.bold: true
               font.pointSize: 11
               minimumPointSize: 10
               anchors.horizontalCenter: parent.horizontalCenter
            }
         }

         Item {
            width: viewTempIV.width * 0.5
            height: viewTempIV.height * 0.5

            Gauge {
               id: gauge4
               width: parent.width * 0.75
               height: parent.height * 0.8
               minimumValue: 0
               value: qmlPull.valTemp4
               maximumValue: 100
               anchors.horizontalCenter : parent.horizontalCenter
               font.pointSize: 10
               font.bold: true
               minorTickmarkCount : 4

               Behavior on value {
                  NumberAnimation {
                     duration: 250
                  }
               }

               style: GaugeStyle {
                  valueBar: Rectangle {
                  implicitWidth: 16
                  color: gauge4.value >= 80 ? "red" : gauge4.value >= 50 && gauge4.value < 80 ? "orange" : "#33FF57"
                  }
               }
            }

            Text {
               id: textArea4
               width: gauge4.width
               height: parent.height * 0.2
               anchors.top: gauge4.bottom
               anchors.topMargin: parent.height * 0.01
               text: qsTr(" ") + qmlPull.nameTemp4
               color: gauge4.value >= 80 ? "red" : gauge4.value >= 50 && gauge4.value < 80? "orange" : "#33FF57"
               font.bold: true
               font.pointSize: 11
               minimumPointSize: 10
               anchors.horizontalCenter: parent.horizontalCenter
            }
         }
      }

      /* Text Information */
      Column {
         id: colIV
         width: parent.width * 0.2
         height: parent.height * (1 - 0.5)
         anchors.top: parent.top
         anchors.left: viewTempIV.right
         Item {
            id : itemIV1
            width: parent.width
            height: parent.height * 0.25
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.02

            Rectangle {
               id: rect1
               width: parent.width * 0.3
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               color: "transparent"

               Text {
                  id: txtComponent1
                  height: parent.height * 0.4
                  anchors.horizontalCenter : parent.horizontalCenter
                  anchors.verticalCenter : parent.verticalCenter
                  text: qsTr(" ") + qmlPull.nameFan1
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }

            Rectangle {
               width: parent.width * 0.7
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               anchors.right: parent.right
               color: "transparent"

               Text {
                  id: txtI1
                  height: parent.height * 0.5
                  anchors.top: parent.top
                  anchors.left: rect1.right
                  width: parent.width
                  text: qsTr("Current (A): ") + qmlPull.valAmp1
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }

               Text {
                  id: txtV1
                  height: parent.height * 0.5
                  width: parent.width
                  anchors.top: txtI1.bottom
                  anchors.left: rect1.right
                  text: qsTr("Voltage (V): ") + qmlPull.valVolt1
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            id : itemIV2
            width: parent.width
            height: parent.height * 0.25
            anchors.top: itemIV1.bottom
            anchors.topMargin: parent.height * 0.02

            Rectangle {
               id: rect2
               width: parent.width * 0.3
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               color: "transparent"

               Text {
                  id: txtComponent2
                  height: parent.height * 0.4
                  anchors.horizontalCenter : parent.horizontalCenter
                  anchors.verticalCenter : parent.verticalCenter
                  text: qsTr(" ") + qmlPull.nameFan2
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }

            Rectangle {
               width: parent.width * 0.7
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               anchors.right: parent.right
               color: "transparent"

               Text {
                  id: txtI2
                  height: parent.height * 0.5
                  anchors.top: parent.top
                  anchors.left: rect2.right
                  width: parent.width
                  text: qsTr("Current (A): ") + qmlPull.valAmp2
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }

               Text {
                  id: txtV2
                  height: parent.height * 0.5
                  width: parent.width
                  anchors.top: txtI2.bottom
                  anchors.left: rect2.right
                  text: qsTr("Voltage (V): ") + + qmlPull.valVolt2
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            id : itemIV3
            width: parent.width
            height: parent.height * 0.25
            anchors.top: itemIV2.bottom
            anchors.topMargin: parent.height * 0.02

            Rectangle {
               id: rect3
               width: parent.width * 0.3
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               color: "transparent"

               Text {
                  id: txtComponent3
                  height: parent.height * 0.4
                  anchors.horizontalCenter : parent.horizontalCenter
                  anchors.verticalCenter : parent.verticalCenter
                  text: qsTr(" ") + qmlPull.nameFan3
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }

            }

            Rectangle {
               width: parent.width * 0.7
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               anchors.right: parent.right
               color: "transparent"

               Text {
                  id: txtI3
                  height: parent.height * 0.5
                  anchors.top: parent.top
                  anchors.left: rect3.right
                  width: parent.width
                  text: qsTr("Current (A): ") + qmlPull.valAmp3
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }

               Text {
                  id: txtV3
                  height: parent.height * 0.5
                  width: parent.width
                  anchors.top: txtI3.bottom
                  anchors.left: rect3.right
                  text: qsTr("Voltage (V): ") + qmlPull.valVolt3
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }

         Item {
            id : itemIV4
            width: parent.width
            height: parent.height * 0.25
            anchors.top: itemIV3.bottom
            anchors.topMargin: parent.height * 0.02

            Rectangle {
               id: rect4
               width: parent.width * 0.3
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               color: "transparent"

               Text {
                  id: txtComponent4
                  height: parent.height * 0.4
                  anchors.horizontalCenter : parent.horizontalCenter
                  anchors.verticalCenter : parent.verticalCenter
                  text: qsTr(" ") + qmlPull.nameFan4
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }

            Rectangle {
               width: parent.width * 0.7
               height: parent.height
               anchors.top: parent.top
               anchors.topMargin: parent.height * 0.02
               anchors.right: parent.right
               color: "transparent"

               Text {
                  id: txtI4
                  height: parent.height * 0.5
                  anchors.top: parent.top
                  anchors.left: rect4.right
                  width: parent.width
                  text: qsTr("Current (A): ") + qmlPull.valAmp4
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }

               Text {
                  id: txtV4
                  height: parent.height * 0.5
                  width: parent.width
                  anchors.top: txtI4.bottom
                  anchors.left: rect4.right
                  text: qsTr("Voltage (V): ") + qmlPull.valVolt4
                  color: "white"
                  font.bold: true
                  font.pointSize: 12
                  minimumPointSize: 10
                  fontSizeMode: Text.Fit
               }
            }
         }
      }

      /* Status Box */
      Rectangle {
            id: rectStatus
            width: parent.width * 0.2
            height: parent.height * 0.2
            anchors.top: colIV.bottom
            anchors.topMargin: parent.height * 0.05
            anchors.left: viewTempIV.right
            radius: 20
            color: "#CCDCC8"

            Column {
               id: colStatus
               width: parent.width * 0.16
               height: parent.height
               anchors.left: parent.left
               anchors.leftMargin: parent.width * 0.04

               Item {
                  width: parent.width
                  height: parent.height * 0.5

                  StatusIndicator {
                      id: indicatorStatus
                      color: powerOn === true ? "#39ff14" : "red"
                      height: rectStatus.height * 0.12
                      anchors.horizontalCenter : parent.horizontalCenter
                      anchors.top: parent.top
                      anchors.topMargin: parent.height * 0.23
                      active: true
                  }

                  Text {
                     color: "#044123"
                     font.bold: true
                     font.pointSize: 10
                     anchors.horizontalCenter : parent.horizontalCenter
                     anchors.top: indicatorStatus.bottom
                     anchors.topMargin: parent.height * 0.02
                     text: qsTr("Power")
                  }

                  StatusIndicator {
                     id: indicatorStatusError
                     color: "red"
                     height: rectStatus.height * 0.12
                     anchors.horizontalCenter : parent.horizontalCenter
                     anchors.top: indicatorStatus.bottom
                     anchors.topMargin: parent.height * 0.5
                     active: true

                     SequentialAnimation on color {
                        id: aniRunning
                        running: (powerOn == true) && (aniStatus.running == true) ? true : false
                        loops: Animation.Infinite

                        ColorAnimation { from: "red"; to: "transparent"; duration: 500 }
                     }
                  }

                  Text {
                     color: "#044123"
                     font.bold: true
                     font.pointSize: 10
                     anchors.horizontalCenter: parent.horizontalCenter
                     anchors.top: indicatorStatusError.bottom
                     anchors.topMargin: parent.height * 0.02
                     text: qsTr("Error")
                  }
               }
            }

            Rectangle {
               id: status
               width: parent.width * 0.725
               height: parent.height * 0.9
               radius: 20
               color: (powerOn == true) && (aniStatus.running == true) ? "red" : "#7FFF00"
               anchors.left: colStatus.right
               anchors.leftMargin: parent.width * 0.05
               anchors.top: parent.top
               anchors.topMargin: rectStatus.height * 0.05

               SequentialAnimation on color {
                  id: aniStatus
                  running: (powerOn == true) && (qmlPush.number == -1) ? true : false
                  loops: Animation.Infinite
                  ColorAnimation {from: "red"; to: "yellow"; duration: 250}  
               }

               Text {
                  id: statusTxt
                  objectName: "statusTxt"
                  width: parent.width * 0.9
                  height: parent.height * 0.8
                  anchors.centerIn: parent
                  font.pixelSize: 12
                  text: (powerOn == true) && (aniStatus.running == true) ? qmlPush.pushError: qmlPush.pushError
               }
            }
      }

      /* Slider and Progress Bar */
      Column {
         id: colControl
         anchors.left: viewTempIV.right
         anchors.top: rectStatus.bottom
         width: parent.width * 0.2
         height: parent.height * 0.25

         Slider {
            id: control
            value: 50
            from: 0
            to: 100
            stepSize: 1
            width: colControl.width*0.9
            anchors.top: colControl.top
            anchors.topMargin: colControl.height*0.12

            background: Rectangle {
               x: control.leftPadding
               y: control.topPadding + control.availableHeight / 2 - height / 2
               implicitWidth: 150
               implicitHeight: 4
               width: control.availableWidth
               height: implicitHeight
               radius: 2
               color: "#CCDCC8"

               Rectangle {
                  width: control.visualPosition * parent.width
                  height: parent.height
                  color: "#03B585"
                  radius: 2
               }
            }

            handle: Rectangle {
               x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
               y: control.topPadding + control.availableHeight / 2 - height / 2
               implicitWidth: 40
               implicitHeight: 40
               radius: 20
               color: control.pressed ? "#CCDCC8" : "#03B585"
               border.color: "#f6f6f6"

               Text {
                  anchors.centerIn: parent
                  color: control.pressed ? "#03B585" : "#CCDCC8"
                  font.pixelSize: 20
                  text: control.value
               }
            }
         }

         ProgressBar {
            id: progressBar
            width: colControl.width*0.9
            anchors.top: control.bottom
            anchors.topMargin: colControl.height*0.1

            MouseArea {
               anchors.fill: parent

               onClicked: {
                  sliderOn = 1;
               }

               onDoubleClicked: {
                  sliderOn = 0;
               }
            }

            background: Rectangle {
               implicitWidth: 150
               implicitHeight: 30
               color: "#F6F6F6"
               radius: 20
            }

            contentItem: Item {
               implicitWidth: 150
               implicitHeight: 30

               Rectangle {
                  width: control.visualPosition * parent.width
                  height: parent.height
                  radius: 20

                  gradient: Gradient {
                      GradientStop {
                          position: 0.5
                          color: "#CCDCC8"
                      }

                      GradientStop {
                         position: 1
                         color: "#03B585"
                      }
                  }
               }

               Text {
                  textFormat: Text.RichText
                  anchors.centerIn: parent
                  color: control.pressed ? "#03B585" : "#044123"
                  font.pixelSize: 18
                  text: control.value + " x10<sup>2</sup> RPM"
               }
            }
         }
      }
   }
}
