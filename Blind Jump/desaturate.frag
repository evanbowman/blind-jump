uniform sampler2D texture;
uniform float amount;

void main() {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec3 color = vec3(pixel.r, pixel.g, pixel.b);
    vec3 gray = vec3(dot(vec3(0.2126,0.7152,0.0722), color));
    gl_FragColor = vec4(mix(color, gray, amount), pixel.a);
}
 