#version 410

out vec4 FragmentColour;
in vec3 color;

uniform float time;

void main() {
  //FragmentColour = vec4(color*(sin(time)+1),1);
    FragmentColour = vec4(color,1);
}
