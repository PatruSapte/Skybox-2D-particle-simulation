import QtQuick
import QtQuick.Controls

Window {
  id: root
  width: 640
  height: 480
  visible: true
  title: qsTr("Skybox")

  Rectangle {
    id: simArea
    anchors.fill: parent
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
