#version 130

uniform sampler2D texture;
uniform vec2 center;
uniform float offset;
uniform float intensity;
uniform float Scanlines;
uniform float time;
uniform int colorLevels;

void main()
{
    vec2 texCoord = gl_TexCoord[0].xy;
    vec2 direction = texCoord - center;
    
    // Chromatic aberration: Sample each color channel with slight offset
    float r = texture2D(texture, texCoord + direction * offset).r;
    float g = texture2D(texture, texCoord).g;
    float b = texture2D(texture, texCoord - direction * offset).b;
    
    vec4 color = vec4(r, g, b, 1.0);
    
    // Interlacing/scanlines: Darken every other line
    float scanlinePos = gl_FragCoord.y + (time * 100.0);
    if (mod(floor(scanlinePos), Scanlines) == 0.0) {
        color.rgb *= intensity;
    }
    
    if (colorLevels > 0) {
        float levels = float(colorLevels);
        color.r = floor(color.r * levels) / levels;
        color.g = floor(color.g * levels) / levels;
        color.b = floor(color.b * levels) / levels;
    }

    gl_FragColor = color;
}