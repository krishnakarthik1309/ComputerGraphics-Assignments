varying vec3 normal;
void main()
{
    float intensity;
    vec4 color;
    vec3 n = normalize(normal);
    intensity = dot(vec3(gl_LightSource[0].position),n);
    if (intensity > 0.95)
    	color = vec4(204.0/255.0, 153.0/255.0, 102.0/255.0, 1.0);
    else if (intensity > 0.5)
    	color = vec4(0.5*204.0/255.0, 0.5*153.0/255.0, 0.5*102.0/255.0, 1.0);
    else if (intensity > 0.25)
    	color = vec4(0.25*204.0/255.0, 0.25*153.0/255.0, 0.25*102.0/255.0, 1.0);
    else
    	color = vec4(0.1*204.0/255.0, 0.1*153.0/255.0, 0.1*102.0/255.0, 1.0);
    gl_FragColor = color;
}