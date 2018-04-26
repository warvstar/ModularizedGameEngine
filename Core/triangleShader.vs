in vec3 vp;
uniform vec2 p;
void main() {
  vec4 pos = vec4(vp, 1.0); pos.xy += p;
  gl_Position = pos;
}