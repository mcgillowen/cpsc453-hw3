#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 color;

uniform mat4x4 M;
uniform mat4x4 V;
uniform mat4x4 P;

uniform float time;

void main() {

    // Define a light direction in eye space
    vec3 L = normalize(vec3(0.5,0.5,1));
    
    // intensity of the light
    vec3 I = vec3(0.2,0.2,1.0);
    
  vec3 normal_eye = normalize((V * M * vec4(normal, 0)).xyz);
    
  vec3 ambient = vec3(0.1,0.1,0.1);
  vec3 diffuse = I * clamp( dot(normal_eye, L), 0, 1 );
  color = ambient + diffuse;
    

  gl_Position = P*V*M*vec4(position, 1.0);
}
