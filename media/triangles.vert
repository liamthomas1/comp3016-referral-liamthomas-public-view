
#version 400 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec4 vColour;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 VNormal;
out vec3 LightIntensity;
uniform mat4 mvp;
uniform struct LightInfo{ //https://dle.plymouth.ac.uk/pluginfile.php/2497682/mod_resource/content/0/Lab3%20-%20Lighting%20and%20shading.pdf
vec4 Position;
vec3 LA;
vec3 L;
}lights[3];
uniform struct MateralInfo{
vec3 Ka;
vec3 Kd;
vec3 Ks;
float Shininess;
}Material; 
out vec3 color;
out vec4 fragColour;
out vec2 TexCoord;

//vec3 phongModel (int light, vec3 position, vec3 n){
//lights[light].LA
//vec3 ambient = vColour + lights[light].LA ;
//vec3 s = vcoler + lights[light].L;
//float sDotN = n - position;
//vec3 diffuse = mMaterial.Kd + 
//vec3 spec = vec3(0.0);
//if(sDotN > 0.0){
 //vec3 v = normalize(-position.xyz);
//vec3 r = reflect (-s,n);
//spec =  Materal.Ks * pow(max(dot(r,v), 0.0),Material.Shininess);

 // https://dle.plymouth.ac.uk/pluginfile.php/2497682/mod_resource/content/0/Lab3%20-%20Lighting%20and%20shading.pdf}
//return ambient + lights[light].L * (diffuse + spec);
//}
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP; 
void
main()
{
    gl_Position = mvp * vec4 (vPosition,1.0);
	fragColour = vec4(0.5, 0.4, 0.8, 1.0);
	fragColour = vColour;
	TexCoord = aTexCoord;
//vec 3 n = normalize(NormalMatrix * VertexNormal);
//vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);

}
