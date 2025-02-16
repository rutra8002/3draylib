#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

void main()
{
    float gradient = 1.0 - fragTexCoord.y;
    vec4 skyBottom = vec4(0.2, 0.5, 0.8, 1.0); // Light blue
    vec4 skyTop = vec4(0.0, 0.0, 0.5, 1.0);    // Dark blue
    finalColor = mix(skyTop, skyBottom, gradient);
}