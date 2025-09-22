import QtQuick
import QtQuick.Effects
import "Utils.js" as Utils

Item {
  id: root
  property real force: 0
  property real maxForce: 100
  property real step: 2
  property bool increasing: true

  // Mouse-based orbit control
  property real orbitRadius: 40
  property real orbitAngle: -90

  property color noForceColor: "grey" //no force applied aka one-click color
  property color minForceColor: "yellow" //smallest force applied / smallest time recognized by keeping click pressed
  property color maxForceColor: "red" //highest force applied / longest time recognized by keeping click pressed

  property vector2d orbitDirection: Qt.vector2d(
                                      Math.cos(orbitAngle * Math.PI / 180),
                                      Math.sin(orbitAngle * Math.PI / 180))

  // Emits when user releases the press
  // position = where to spawn, direction = normalized vector, velocity = force
  signal spawnRequested(real x, real y, vector2d direction, real force)

  MouseArea {
    id: mouseArea
    hoverEnabled: true //otherwise
    anchors.fill: parent
    onPressed: holdTimer.start()
    onReleased: {
      holdTimer.stop()
      // On release, request a spawn
      root.spawnRequested(mouseX, mouseY, orbitDirection, root.force)
    }

    onWheel: wheel => {
               orbitAngle += wheel.angleDelta.y > 0 ? 10 : -10
             }
  }

  Timer {
    id: holdTimer
    interval: 16
    repeat: true
    running: false

    onTriggered: {
      if (root.increasing) {
        root.force += root.step
        if (root.force >= root.maxForce) {
          root.force = root.maxForce
          root.increasing = false
        }
      } else {
        root.force -= root.step
        if (root.force <= 0) {
          root.force = 0
          root.increasing = true
        }
      }
    }
  }

  // Visual aids (your previews)
  Image {
    id: spawnParticle
    source: "assets/planet.png"
    width: 32
    height: 32
    x: mouseArea.mouseX - width / 2
    y: mouseArea.mouseY - height / 2
  }


  /*MultiEffect {
    id: colorizedDirArrow
    source: directionArrow

    width: 32
    height: 32
    colorizationColor: "red"

    x: mouseArea.mouseX + orbitRadius * orbitDirection.x - height / 2
    y: mouseArea.mouseY + orbitRadius * orbitDirection.y - height / 2
    transform: Rotation {
      origin.x: colorizedDirArrow.width / 2
      origin.y: colorizedDirArrow.height / 2
      angle: Math.atan2(
               colorizedDirArrow.y + colorizedDirArrow.height / 2 - mouseArea.mouseY,
               colorizedDirArrow.x + colorizedDirArrow.width / 2
               - mouseArea.mouseX) * 180 / Math.PI + 90
    }
    antialiasing: true
  }
  Image {
    id: directionArrow
    source: "assets/white_arrow.png"
    visible: false // use only as source
    width: 32
    height: 32
  }

*/
  MultiEffect {
    id: colorizedDirArrow
    source: directionArrow
    anchors.fill: directionArrow
    transform: arrowRot

    colorizationColor: (holdTimer.running) ? Utils.lerpColor(
                                               minForceColor, maxForceColor,
                                               force / 100) : noForceColor
    colorization: 1
  }

  Image {
    id: directionArrow
    source: "assets/white_arrow.png"
    width: 32
    height: 32
    visible: false
    x: mouseArea.mouseX + orbitRadius * orbitDirection.x - height / 2
    y: mouseArea.mouseY + orbitRadius * orbitDirection.y - height / 2

    transform: Rotation {
      id: arrowRot
      origin.x: directionArrow.width / 2
      origin.y: directionArrow.height / 2
      angle: Math.atan2(
               directionArrow.y + directionArrow.height / 2 - mouseArea.mouseY,
               directionArrow.x + directionArrow.width / 2 - mouseArea.mouseX) * 180 / Math.PI + 90
    }
    antialiasing: true
  }
}
