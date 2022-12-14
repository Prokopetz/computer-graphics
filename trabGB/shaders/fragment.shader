#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float FogDepth;

out vec4 color;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

uniform vec4 fogColor;
uniform float fogNear;
uniform float fogFar;

uniform sampler2D texture1;

void main() {
	vec4 objectColor = texture(texture1, TexCoord);

    vec3 ambient = lightColor * materialAmbient;
  	
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * materialDiffuse;
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = spec * lightColor * materialSpecular;  

    float fogAmount = smoothstep(fogNear, fogFar, FogDepth);
    vec3 result = ambient + diffuse + specular;
	color = mix(vec4(result, 1.0) * objectColor, fogColor, fogAmount);
}
