#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
struct Material	{
vec3 ambient;
sampler2D diffuse;
sampler2D specular;
float shiness;
};
struct Light {
vec3 ambient;
vec3 diffuse;
vec3 specular;
vec3 position;
};
//uniform vec3 lightPos; 
uniform vec3 lightColor;
//uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform Material newMaterial;
uniform Light newLight;
void main()
{

    // ambient
    //float ambientStrength = 0.1;
    vec3 ambient =  newLight.ambient * vec3(texture(newMaterial.diffuse,TexCoords)).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(newLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = newLight.diffuse * diff * vec3(texture(newMaterial.diffuse,TexCoords));
    // specular
	//float specularStr = 0.5;
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float specularEff = pow(max(dot(viewDir,reflectDir),0.0),newMaterial.shiness);
	vec3 specular = newLight.specular * specularEff * vec3(texture(newMaterial.specular,TexCoords));
    // result
	
    FragColor = vec4(ambient + diffuse + specular,1.0);
} 