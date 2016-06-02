uniform sampler2D 	texture;
uniform vec2 		blurRadius;
uniform vec2        textureSize;

void main() {
	vec2 textureCoordinates = gl_TexCoord[0].xy;
	vec4 color = vec4(0.0);
    float dist = sqrt(pow(textureSize[0] - textureCoordinates[0], 2.0) - pow(textureSize[1] - textureCoordinates[1], 2.0));
    vec2 factors = vec2(dist / textureSize[0], dist / textureSize[1]);
    vec2 finalBlurAmount = blurRadius * factors;
	color += texture2D(texture, textureCoordinates - 4.0 * finalBlurAmount) * 0.0162162162;
	color += texture2D(texture, textureCoordinates - 3.0 * finalBlurAmount) * 0.0540540541;
	color += texture2D(texture, textureCoordinates - 2.0 * finalBlurAmount) * 0.1216216216;
	color += texture2D(texture, textureCoordinates - finalBlurAmount) * 0.1945945946;
	color += texture2D(texture, textureCoordinates) * 0.2270270270;
	color += texture2D(texture, textureCoordinates + finalBlurAmount) * 0.1945945946;
	color += texture2D(texture, textureCoordinates + 2.0 * finalBlurAmount) * 0.1216216216;
	color += texture2D(texture, textureCoordinates + 3.0 * finalBlurAmount) * 0.0540540541;
	color += texture2D(texture, textureCoordinates + 4.0 * finalBlurAmount) * 0.0162162162;
    gl_FragColor = color;
}
