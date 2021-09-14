// #version 430
// out vec4 fColor;

// struct Material {
//     sampler2D diffuse;
//     sampler2D specular;  
//     vec3 Ka; 
//     vec3 Kd; 
//     vec3 Ks; 
//     int shineness; 
// }; 
// struct Light{
// 	vec4 lightPos;
// 	vec4 AmbientColor;
// 	vec4 DiffColor;
// 	vec4 SpecColor;
// 	vec3 Spot_Direction;
// 	float spot_exp;
// 	float spot_cutoff;
// };

// uniform vec4 ObjectColor;


// uniform vec3 viewPos;
// uniform int ton;
// uniform sampler2D dtex;
// uniform sampler2D stex;


// uniform Material material;
// uniform Light light;

// in vec4 vColor;
// in vec3 Normal; 
// in vec4 FragPos;
// in vec2 TexCoords;
// in flat int l_type;
// in vec4 LIGHT;

// // void main () {
// // 	int n = material.shineness;
// // 	if(ton==0)
// // 	{	
// // 		// Fonte Pontual
// // 		vec3 lightDir = normalize(light.lightPos.rgb - FragPos.rgb);  
// // 	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
		
// // 		// diffuse 
// // 		vec3 norm = normalize(Normal);
// // 		float NL = max(dot(norm, lightDir), 0.0);
// // 		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb; 

// // 		// specular
// // 		vec3 viewDir = normalize(viewPos - FragPos.rgb);

// // 		vec3 reflectDir = 2*norm*NL - lightDir;
// // 		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// // 		vec3 specular = material.Ks * light.SpecColor.rgb* spec * (texture(material.specular, TexCoords.xy)).rgb;



// // 		vec3 result = vec3(Iamb + diffuse + specular);
// // 		fColor = vec4(result, 1.0);
// // 	}
// // 	if(ton==1)
// // 	{
// // 		// Fonte Direcional
// // 		vec3 lightDir = normalize(light.lightPos.xyz);  
// // 		// ambient
// // 	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
		
// // 		// diffuse 
// // 		vec3 norm = normalize(Normal);
// // 		float NL = max(dot(norm, lightDir), 0.0);
// // 		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

// // 		// specular
// // 		vec3 Ks = vec3(0.5,0.5,0.5);
// // 		vec3 viewDir = normalize(viewPos - FragPos.rgb);

// // 		vec3 reflectDir = 2*norm*NL - lightDir;
// // 		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// // 		vec3 specular = material.Ks * light.SpecColor.rgb* spec * (texture(material.specular, TexCoords.xy)).rgb;



// // 		vec3 result = (Iamb + diffuse + specular);
// // 		fColor = vec4(result, 1.0);
// // 	}
// // 	if(ton==2)
// // 	{ 
// // 		//SPOT
// // 		float cutoff = cos((light.spot_cutoff)*3.14/180.0);
// // 		vec3 lightDir = normalize(light.lightPos.xyz - FragPos.xyz);
// // 		float theta = dot(lightDir,normalize(-light.Spot_Direction));
// // 		if(theta > cutoff)
// // 		{
// // 			// ambient
// // 			vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;

// // 			// diffuse 
// // 			vec3 norm = normalize(Normal);
// // 			float NL = max(dot(norm, lightDir), 0.0);
// // 			vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

// // 			// specular
// // 			vec3 viewDir = normalize(viewPos - FragPos.rgb);

// // 			vec3 reflectDir = 2*norm*NL - lightDir;
// // 			float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// // 			vec3 specular = material.Ks * light.SpecColor.rgb* spec* (texture(material.specular, TexCoords.xy)).rgb ;



// // 			vec3 result = (Iamb + diffuse + specular);
// // 			fColor = vec4(result, 1.0f);
// // 		}
// // 		else
// // 		{ 
// // 			// ambient
// // 			vec3 Ka = vec3(0.1,0.1,0.1);
// // 			vec3 Iamb = Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
// // 			fColor = vec4(Iamb,1.0f);
// // 		}
// // 	}


	
// // }

// void main () {
// if(l_type==0)
// {
// 	int n = material.shineness;
// 	int n_t = 1;
// 	if(ton==0)
// 	{	
// 		// Fonte Pontual
// 		vec3 lightDir = normalize(light.lightPos.rgb - FragPos.rgb);  
// 	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
		
// 		// diffuse 
// 		vec3 norm = normalize(Normal);
// 		float NL = max(dot(norm, lightDir), 0.0);
// 		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb; 

// 		// specular
// 		vec3 viewDir = normalize(viewPos - FragPos.rgb);

// 		vec3 reflectDir = 2*norm*NL - lightDir;
// 		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// 		vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(material.diffuse, TexCoords.xy)).rgb ;



// 		vec3 result = vec3(Iamb + diffuse + specular);
// 		fColor = vec4(result, 1.0);
// 	}
// 	if(ton==1)
// 	{
// 		// Fonte Direcional
// 		vec3 lightDir = normalize(light.lightPos.xyz);  
// 		// ambient
// 	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
		
// 		// diffuse 
// 		vec3 norm = normalize(Normal);
// 		float NL = max(dot(norm, lightDir), 0.0);
// 		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

// 		// specular
// 		vec3 viewDir = normalize(viewPos - FragPos.rgb);

// 		vec3 reflectDir = 2*norm*NL - lightDir;
// 		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// 		vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(material.diffuse, TexCoords.xy)).rgb ;



// 		vec3 result = (Iamb + diffuse + specular);
// 		fColor = vec4(result, 1.0);
// 	}
// 	if(ton==2)
// 	{ 
// 		//SPOT
// 		float cutoff = cos((light.spot_cutoff)*3.14/180.0);

// 		vec3 lightDir = normalize(light.lightPos.xyz - FragPos.xyz);
// 		float theta = dot(lightDir,normalize(-light.Spot_Direction));
// 		if(theta > cutoff)
// 		{
// 			// ambient
// 			vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
// 			float attenuation = 1.0;
// 			attenuation*=pow(cutoff,light.spot_exp);
// 			// diffuse 
// 			vec3 norm = normalize(Normal);
// 			float NL = max(dot(norm, lightDir), 0.0);
// 			vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

// 			// specular
// 			vec3 viewDir = normalize(viewPos - FragPos.rgb);

// 			vec3 reflectDir = 2*norm*NL - lightDir;
// 			float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
// 			vec3 specular = material.Ks * light.SpecColor.rgb* spec*attenuation*(texture(material.diffuse, TexCoords.xy)).rgb;



// 			vec3 result = (Iamb + diffuse + specular);
// 			fColor = vec4(result, 1.0f);
// 		}
// 		else
// 		{ 
// 			// ambient
// 			// vec3 Ka = vec3(0.1,0.1,0.1);
// 			vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
// 			fColor = vec4(Iamb,1.0f);
// 		}
// 	}
// };		


// if(l_type==1)
// {		
// 		vec3 result = LIGHT.xyz*ObjectColor.xyz*(texture(material.diffuse, TexCoords.xy)).rgb;
// 		fColor = vec4(result,1.0f);
// };
// if(l_type==2)
// 	{
// 		fColor = vec4(texture(material.diffuse, TexCoords.xy).rgb,1.0f);
// 	};
// }

#version 430
out vec4 fColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;  
    vec3 Ka; 
    vec3 Kd; 
    vec3 Ks; 
    int shineness; 
}; 
struct Light{
	vec4 lightPos;
	vec4 AmbientColor;
	vec4 DiffColor;
	vec4 SpecColor;
	vec4 Spot_Direction;
	float spot_exp;
	float spot_cutoff;
};

uniform vec4 ObjectColor;

uniform vec3 viewPos;
uniform int ton;
uniform sampler2D dtex;
uniform sampler2D stex;


uniform Material material;
uniform Light light;

in vec4 vColor;
in vec3 Normal; 
in vec4 FragPos;
in flat int l_type;
in vec4 LIGHT;
flat in vec4 colorflat;
in vec4 light_post;
in vec4 spot_post;
in vec2 TexCoords;
void main () {
if(l_type==0)
{
	int n = material.shineness;
	int n_t = 1;
	if(ton==0)
	{	
		// Fonte Pontual
		vec3 lightDir = normalize(light_post.rgb - FragPos.rgb);  
	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(dtex, TexCoords.xy)).rgb;
		
		// diffuse 
		vec3 norm = normalize(Normal);
		float NL = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(dtex, TexCoords.xy)).rgb; 

		// specular
		vec3 viewDir = normalize(viewPos - FragPos.rgb);

		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
		vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(stex, TexCoords.xy)).rgb;



		vec3 result = vec3(Iamb + diffuse + specular);
		fColor = vec4(result, 1.0);
	}
	if(ton==1)
	{
		// Fonte Direcional
		vec3 lightDir = normalize((light.lightPos).xyz);  
		// ambient
	    vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(dtex, TexCoords.xy)).rgb;
		
		// diffuse 
		vec3 norm = normalize(Normal);
		float NL = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(dtex, TexCoords.xy)).rgb;

		// specular
		vec3 viewDir = normalize(viewPos - FragPos.rgb);

		vec3 reflectDir = 2*norm*NL - lightDir;
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
		vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(stex, TexCoords.xy)).rgb;



		vec3 result = (Iamb + diffuse + specular);
		fColor = vec4(result, 1.0);
	}
	if(ton==2)
	{ 
		//SPOT
		float cutoff = cos((light.spot_cutoff)*3.14/180.0);

		vec3 lightDir = normalize(light_post.xyz - FragPos.xyz);

		vec3 direction = spot_post.xyz - light_post.xyz;

		float theta = dot(-lightDir,normalize(direction));

		if(theta > cutoff)
		{
			// ambient
			vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(dtex, TexCoords.xy)).rgb;
			float attenuation = 1.0;
			attenuation*=pow(cutoff,light.spot_exp);
			// diffuse 
			vec3 norm = normalize(Normal);
			float NL = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(dtex, TexCoords.xy)).rgb;

			// specular
			vec3 viewDir = normalize(viewPos - FragPos.rgb);

			vec3 reflectDir = 2*norm*NL - lightDir;
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
			vec3 specular = material.Ks * light.SpecColor.rgb* spec*attenuation*(texture(stex, TexCoords.xy)).rgb;



			vec3 result = (Iamb + diffuse + specular);
			fColor = vec4(result, 1.0f);
		}
		else
		{ 
			// ambient
			// vec3 Ka = vec3(0.1,0.1,0.1);
			vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
			fColor = vec4(Iamb,1.0f);
		}
	}
};		
if(l_type==1)
{
		fColor = LIGHT;
};
if(l_type==2)
	{
		fColor = colorflat;
	};
}