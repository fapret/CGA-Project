#version 400 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 ambientColor; // Ambient light color

void main()
{    
    // Sample the texture
    vec4 texColor = texture(texture_diffuse1, TexCoords);
    
    // Apply ambient light
    vec3 ambient = ambientColor * texColor.rgb;
    
    // Output final color
    FragColor = vec4(ambient, texColor.a);
}