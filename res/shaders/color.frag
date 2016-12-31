uniform sampler2D texture;
uniform float data[4];

void main() {
	// lookup the pixel in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	
	if (pixel.a != 0.0) {
		vec3 originalColor = vec3(pixel.r, pixel.g, pixel.b);
		vec3 targetColor = vec3(data[0], data[1], data[2]);
		gl_FragColor = vec4(mix(originalColor, targetColor, data[3]), pixel.a);
	} else {
		gl_FragColor = pixel;
	}
}