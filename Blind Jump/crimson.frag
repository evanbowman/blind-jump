uniform sampler2D texture;

void main() {
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if (pixel.a == 1.0) {
        gl_FragColor = vec4(0.94, 0.09, 0.34, pixel.a);
	} else {
		gl_FragColor = pixel;
	}
}
