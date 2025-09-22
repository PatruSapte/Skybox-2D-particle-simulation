//Create a new color by interpolating between 2 colors
function lerpColor(c1, c2, factor) {
  factor = Math.min(1.0, Math.max(0.0, factor)) // clamp to [0,1]

  var r = c1.r + (c2.r - c1.r) * factor
  var g = c1.g + (c2.g - c1.g) * factor
  var b = c1.b + (c2.b - c1.b) * factor
  var a = c1.a + (c2.a - c1.a) * factor

  return Qt.rgba(r, g, b, a)
}
