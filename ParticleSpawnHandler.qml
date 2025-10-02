import QtQuick
import QtQuick.Effects
import "Utils.js" as Utils

Item {
  id: root
  property real force: 0
  property real maxForce: 100
  property real highForceThreshold: 85 //minimum force threshold before step value get halfed
  property real step: 5
  property bool increasing: true

  // Mouse-based orbit control
  property real orbitAngle: -90
  property real orbitRadius: 40
  property real radiusOffset: Utils.lerpNumber(
                                10, 40,
                                force / maxForce) //increase orbit radius based on applied force

  property color noForceColor: "grey" //no force applied aka one-click color
  property color minForceColor: "yellow" //smallest force applied / smallest time recognized by keeping click pressed
  property color maxForceColor: "red" //highest force applied / longest time recognized by keeping click pressed

  property real arrowHeight: Utils.lerpNumber(minArrowHeight, maxArrowHeight,
                                              force / maxForce)
  property real minArrowHeight: 48 //how short direction arrow can be based on applied force
  property real maxArrowHeight: 96 //how long direction arrow can be based on applied force

  property real arrowWidth: Utils.lerpNumber(minArrowWidth, maxArrowWidth,
                                             force / maxForce)
  property real minArrowWidth: 48 //how short direction arrow can be based on applied force
  property real maxArrowWidth: 64 //how long direction arrow can be based on applied force

  property vector2d orbitDirection: Qt.vector2d(
                                      Math.cos(orbitAngle * Math.PI / 180),
                                      Math.sin(orbitAngle * Math.PI / 180))

  // Emits when user releases the press
  // position = where to spawn, direction = normalized vector, velocity = force
  signal spawnRequested(real x, real y, vector2d direction, real force)

  MouseArea {
    id: mouseArea
    hoverEnabled: true
    anchors.fill: parent
    onPressed: {
      force = 0
      holdTimer.start()
    }
    onReleased: {
      holdTimer.stop()
      // On release, request a spawn
      root.spawnRequested(mouseX, mouseY, orbitDirection, root.force)
      force = 0
    }

    onWheel: wheel => {
               orbitAngle += wheel.angleDelta.y > 0 ? 10 : -10
             }

    onEntered: {
      colorizedDirArrow.visible = true
      spawnParticle.visible = true
    }
    onExited: {
      colorizedDirArrow.visible = false
      spawnParticle.visible = false
    }
  }

  Timer {
    id: holdTimer
    interval: 10
    repeat: true
    running: false

    onTriggered: {
      var stepVal = root.step
      if (root.force > highForceThreshold) {
        stepVal /= 2
      }

      if (root.increasing) {
        root.force += stepVal
        if (root.force >= root.maxForce) {
          root.force = root.maxForce
          root.increasing = false
        }
      } else {
        root.force -= stepVal
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

  MultiEffect {
    id: colorizedDirArrow
    source: directionArrow
    anchors.fill: directionArrow
    transform: arrowRot

    colorizationColor: (holdTimer.running) ? Utils.lerpColor(
                                               minForceColor, maxForceColor,
                                               force / 100) : noForceColor
    colorization: 1

    transformOrigin: Item.Center

    SequentialAnimation on rotation {
      id: arrowShakeAnimation
      running: force >= highForceThreshold ? true : false
      loops: Animation.Infinite
      property double intensity: Utils.lerpNumber(
                                   1, 5,
                                   (force - highForceThreshold) / (maxForce - highForceThreshold))
      NumberAnimation {
        from: -arrowShakeAnimation.intensity
        to: arrowShakeAnimation.intensity
        duration: 50
        easing.type: Easing.Linear
      }
      NumberAnimation {
        from: arrowShakeAnimation.intensity
        to: -arrowShakeAnimation.intensity
        duration: 50
        easing.type: Easing.Linear
      }
    }
  }

  Image {
    id: directionArrow
    source: "assets/white_arrow.png"
    width: arrowWidth
    height: arrowHeight
    visible: false

    x: mouseArea.mouseX + (orbitRadius + radiusOffset) * orbitDirection.x - width / 2
    y: mouseArea.mouseY + (orbitRadius + radiusOffset) * orbitDirection.y - height / 2

    transform: Rotation {
      id: arrowRot
      origin.x: directionArrow.width / 2
      origin.y: directionArrow.height / 2

      angle: Math.atan2(orbitDirection.y, orbitDirection.x) * 180 / Math.PI + 90
    }

    antialiasing: true
  }
}
