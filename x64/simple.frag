#version 400 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientColor; // Ambient light color
uniform vec3 lightDirection; // Direction of the sunlight
uniform vec3 lightColor; // Color of the sunlight

void main()
{    
    // Sample the texture
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    
    // Apply ambient light
    vec3 ambient = ambientColor * texColor.rgb;

    // Directional light calculations
    float diff = max(dot(normalize(Normal), -lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine ambient and diffuse lighting
    vec3 result = ambient + diffuse * texColor.rgb;

    // Output final color
    FragColor = vec4(result, texColor.a);
}
