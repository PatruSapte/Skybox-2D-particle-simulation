import QtQuick
import QtQuick.Controls

Window {
  id: root
  width: 640
  height: 480
  visible: true
  title: qsTr("Skybox")
  color: "grey"
  Rectangle {
    id: menuBar
    color: "grey"
    height: 35
    anchors.bottom: parent.bottom
  }
  Rectangle {
    id: simArea

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: menuBar.top

    clip: true

    color: "#49759c"
    ParticleSpawnHandler {
      id: spawnHandler
      anchors.fill: parent
      maxForce: 200
      step: 4
      onSpawnRequested: (x, y, direction, force) => {
                          simulationController.createPlanet(
                            simArea, x, y, direction.times(force))
                        }
    }
  }
}
