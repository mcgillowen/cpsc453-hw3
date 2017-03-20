#version 410

out vec4 FragmentColour;

in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 T;
} fs_in;

uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;

uniform sampler2D image;

void main() {

  // Normalize the incoming N, L, and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each
    // fragment
    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
    diffuse = diffuse * texture(image, fs_in.T).rgb;
    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) *
                    specular_albedo;

    // Write final color to the framebuffer
    FragmentColour = vec4(diffuse + specular, 1.0);
}
