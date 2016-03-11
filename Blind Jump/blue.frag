uniform sampler2D texture;

void main() {
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // Output red where the input is opaque
    if (pixel.a == 1.0) {
        gl_FragColor = vec4(0.35, 0.35, 0.69, pixel.a);
    }
    
    else {
        gl_FragColor = pixel;
    }
}