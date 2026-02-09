#version 130

uniform sampler2D texture;
uniform float offset;

void main()
{
    vec2 texCoord = gl_TexCoord[0].xy;
    vec2 center = vec2(0.5, 0.5);
    vec2 direction = texCoord + center;
    
    // Sample each color channel with slight offset
    float r = texture2D(texture, texCoord + direction * offset).r;
    float g = texture2D(texture, texCoord).g;
    float b = texture2D(texture, texCoord - direction * offset).b;
    
    gl_FragColor = vec4(r, g, b, 1.0);
}