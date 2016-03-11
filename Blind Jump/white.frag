uniform sampler2D texture;

void main() {
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // Color the image white
    gl_FragColor = vec4(1.0, 1.0, 1.0, pixel.a);
}