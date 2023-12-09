#version 400 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;  // Add a new texture uniform
uniform sampler2D texture_height;   // New height map texture
uniform vec3 ambientColor; // Ambient light color
uniform vec3 lightDirection; // Direction of the sunlight
uniform vec3 lightColor; // Color of the sunlight

void main()
{    
    // Sample the textures
    vec4 texColor1 = texture(texture_diffuse1, TexCoords);
    vec4 texColor2 = texture(texture_diffuse2, TexCoords);

    // Combine textures as needed (for example, you can blend them using mix)
    vec4 texColor = mix(texColor1, texColor2, 0.5);

    // Sample the height map texture
    float heightValue = texture(texture_height, TexCoords).r;

    // Calculate the normal from the height map
    vec3 normalFromHeightMap = normalize(vec3(dFdx(heightValue), dFdy(heightValue), 1.0));

    // Combine the normal from the height map with the original normal
    vec3 finalNormal = normalize(Normal + normalFromHeightMap);

    // Apply ambient light
    vec3 ambient = ambientColor * texColor.rgb;

    // Directional light calculations
    float diff = max(dot(finalNormal, -lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Combine ambient and diffuse lighting
    vec3 result = ambient + diffuse * texColor.rgb;

    // Output final color
    FragColor = vec4(result, texColor.a);
}