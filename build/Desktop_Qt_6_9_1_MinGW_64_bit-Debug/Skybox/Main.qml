import QtQuick

Window {
  id: root
  width: 640
  height: 480
  visible: true
  title: qsTr("Skybox")

  MouseArea {
    id: mouseArea
    anchors.fill: parent
    hoverEnabled: true

    property real orbitRadius: 40
    property real orbitAngle: -90
    property real centerX: mouseX
    property real centerY: mouseY

    Image {
      id: toSpawnPlanet
      source: "assets/planet.png"
      width: 32
      height: 32
      x: parent.mouseX - width / 2
      y: parent.mouseY - height / 2
    }

    cursorShape: "BlankCursor"
    onWheel: wheel => {
               orbitAngle += wheel.angleDelta.y > 0 ? 10 : -10
             }

    Image {
      id: directionArrow
      source: "assets/arrow-up.png"

      property vector2d orbitPosition: Qt.vector2d(
                                         mouseArea.centerX + mouseArea.orbitRadius
                                         * orbitDirection.x - directionArrow.width / 2,
                                         mouseArea.centerY + mouseArea.orbitRadius
                                         * orbitDirection.y - directionArrow.height / 2)

      property vector2d orbitDirection: Qt.vector2d(
                                          Math.cos(
                                            mouseArea.orbitAngle * Math.PI / 180),
                                          Math.sin(
                                            mouseArea.orbitAngle * Math.PI / 180))
      width: 32
      height: 32

      x: orbitPosition.x
      y: orbitPosition.y

      transform: Rotation {
        origin.x: directionArrow.width / 2
        origin.y: directionArrow.height / 2
        angle: Math.atan2(
                 directionArrow.y + directionArrow.height / 2 - mouseArea.centerY,
                 directionArrow.x + directionArrow.width / 2
                 - mouseArea.centerX) * 180 / Math.PI + 90
      }

      antialiasing: enabled
    }

    onClicked: {
      simulationController.createPlanet(mouseArea, toSpawnPlanet.x,
                                        toSpawnPlanet.y)


      /*  mouse => {
        if (mouse.button === Qt.LeftButton) {
          var component = Qt.createComponent("Planet.qml")
          var planet = component.createObject(mouseArea)
          //simulationController.createPlanet(mouseArea, mouseX, mouseY)


            planet.width = 32
          planet.height = 32
          planet.x = mouseX - planet.width / 2
          planet.y = mouseY - planet.height / 2
        }
      }*/
    }
  }
}
