# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

//float Diffuse(const in vec3 surfaceNorm, const in vec3 lightdirection);
//float Specular(const in vec3 surfaceNorm, const in vec3 halfVector, const in float shininess);

float Diffuse(const in vec3 surfaceNorm, const in vec3 lightdirection)
{
    return max(dot(surfaceNorm, lightdirection), 0.0);
}

float Specular(const in vec3 surfaceNorm, const in vec3 halfVector, const in float shininess)
{
    return pow(max(dot(surfaceNorm, halfVector), 0.0), shininess);
}


void main (void) 
{       
    if (enablelighting) {       
        vec3 eyePos = vec3(0.0f);
        vec3 viewDir = normalize(eyePos - (myvertex.xyz / myvertex.w));
        vec3 lightPos;
        vec3 lightDir;
        vec3 halfvec;
        vec4 finalcolor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        vec3 norm = normalize(mat3(transpose(inverse(modelview))) * mynormal);
        bool pointLight;

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader
        for (int i=0; i < numLights; i++)
        {
            pointLight = bool(lightposn[i].w);
            lightPos = pointLight ? lightposn[i].xyz / lightposn[i].w : lightposn[i].xyz;
            lightDir = pointLight ? normalize(lightPos- vec3(myvertex)) : normalize(lightPos);
            halfvec = normalize(lightDir + viewDir);
            finalcolor += lightcolor[i] * (diffuse * Diffuse(norm, lightDir) + specular * Specular(norm, halfvec, shininess));  
        }
        fragColor = ambient + emission + finalcolor;
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}
