#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixVal;

void main() {
  // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  // FragColor = color;
  // FragColor = texture(texture1, TexCoord);
  FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixVal);
}