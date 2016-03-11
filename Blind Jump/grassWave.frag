//
//  grassWave.frag
//  Blind Jump
//
//  Created by Evan Bowman on 2/29/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

uniform float time;
uniform sampler2D texture;

void main() {
    float t = time;
    vec2 aux = gl_TexCoord[0].xy;
    float height = 1.0 - aux.y;
    float offset = pow(height, 1.5);
    // This would also make waving/deform the texture
    offset *= (sin(time * 0.5) * 0.2);
    float alpha = texture2D(texture, fract(vec2(aux.x + offset, aux.y))).a;
    vec3 normalColor = texture2D(texture, fract(vec2(aux.x + offset, aux.y))).rgb;
    gl_FragColor = vec4(normalColor, alpha);
}