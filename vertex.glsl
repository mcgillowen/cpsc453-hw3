#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 T;
} vs_out;

uniform mat4x4 M;
uniform mat4x4 V;
uniform mat4x4 P;

uniform vec3 light = vec3(1,1,1);

void main() {

    vec4 Pos = V * M * vec4(position, 1.0);

    vs_out.N = mat3(M) * normal;

    vs_out.L = light - Pos.xyz;

    vs_out.V = -Pos.xyz;

    vs_out.T = texture;

    gl_Position = P * Pos;
}
