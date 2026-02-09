#version 130

uniform sampler2D texture;
uniform float offset;
uniform float intensity;
uniform float Scanlines;

void main()
{
    vec2 texCoord = gl_TexCoord[0].xy;
    vec2 center = vec2(0.5, 0.5);
    vec2 direction = texCoord - center;
    
    // Chromatic aberration: Sample each color channel with slight offset
    float r = texture2D(texture, texCoord + direction * offset).r;
    float g = texture2D(texture, texCoord).g;
    float b = texture2D(texture, texCoord - direction * offset).b;
    
    vec4 color = vec4(r, g, b, 1.0);
    
    // Interlacing/scanlines: Darken every other line
    if (mod(floor(gl_FragCoord.y), Scanlines) == 0.0) {
        color.rgb *= intensity;
    }
    
    gl_FragColor = color;
}