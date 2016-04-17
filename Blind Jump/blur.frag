uniform sampler2D texture;
uniform vec2 blur_radius;

void main() {
    vec2 textureCoordinates = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    color += texture2D(texture, textureCoordinates - 11.0 * blur_radius) * 0.0108;
    color += texture2D(texture, textureCoordinates - 10.0 * blur_radius) * 0.0158;
    color += texture2D(texture, textureCoordinates - 9.0 * blur_radius) * 0.0175;
    color += texture2D(texture, textureCoordinates - 8.0 * blur_radius) * 0.0222;
    color += texture2D(texture, textureCoordinates - 7.0 * blur_radius) * 0.0299;
    color += texture2D(texture, textureCoordinates - 6.0 * blur_radius) * 0.0388;
    color += texture2D(texture, textureCoordinates - 5.0 * blur_radius) * 0.0484;
    color += texture2D(texture, textureCoordinates - 4.0 * blur_radius) * 0.0579;
    color += texture2D(texture, textureCoordinates - 3.0 * blur_radius) * 0.0666;
    color += texture2D(texture, textureCoordinates - 2.0 * blur_radius) * 0.0737;
    color += texture2D(texture, textureCoordinates - blur_radius) * 0.0782;
    color += texture2D(texture, textureCoordinates) * 0.0798;
    color += texture2D(texture, textureCoordinates + blur_radius) * 0.0782;
    color += texture2D(texture, textureCoordinates + 2.0 * blur_radius) * 0.0737;
    color += texture2D(texture, textureCoordinates + 3.0 * blur_radius) * 0.0666;
    color += texture2D(texture, textureCoordinates + 4.0 * blur_radius) * 0.0579;
    color += texture2D(texture, textureCoordinates + 5.0 * blur_radius) * 0.0484;
    color += texture2D(texture, textureCoordinates + 6.0 * blur_radius) * 0.0388;
    color += texture2D(texture, textureCoordinates + 7.0 * blur_radius) * 0.0299;
    color += texture2D(texture, textureCoordinates + 8.0 * blur_radius) * 0.0222;
    color += texture2D(texture, textureCoordinates + 9.0 * blur_radius) * 0.0175;
    color += texture2D(texture, textureCoordinates + 10.0 * blur_radius) * 0.0158;
    color += texture2D(texture, textureCoordinates + 11.0 * blur_radius) * 0.0108;
    gl_FragColor = color;
}