import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Shapes 1.12
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3

Window {
    objectName: "win"
    id: win
    width: 800   // set Screen.width to make it full screen
    height: 480   // set Screen.height - 50 to make it full screen
    visible: true
    color:"black"
    // visibility: Window.FullScreen   // uncomment this to make it full screen

    property int windowStatus: 0
    property int pState: 0
    property int maxH: Screen.height - 50
    property int maxW: Screen.width - 50
    property int swp: 0

    SwipeView {
        width: parent.width
        height: parent.height
        id: swpV
        currentIndex: 0
        anchors.fill: parent

        Pg01_GaugeDashboard {}
        //Pg02_Chart {}   // Add more slides by uncommenting this
    }

   // Switch button to control swiping slide condition
   // Uncomment the section below to enable the swiping control function
   /* Item {
       width: parent.width
       height: parent.height
       anchors.centerIn: parent
       Switch {
          id: sw
          anchors.right: parent.right
          anchors.top: parent.top

          onClicked: {
              if (swp == 1) {
                 swpV.interactive = true;
                 timer.restart()
                 swp = 0;
              }
              else {
                 swpV.interactive = false;
                 timer.stop()
                 swp = 1;
              }
          }
       }
    }*/

    PageIndicator {
        id: indicator

        count: swpV.count
        currentIndex: swpV.currentIndex

        anchors.bottom: swpV.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Timer {
       id: timer
       running: true
       repeat: true
       interval: 10000

       onTriggered: {
          if (swpV.currentIndex == 1) {
             swpV.currentIndex = -1;
          }

          swpV.currentIndex = swpV.currentIndex + 1
       }
    }
}
