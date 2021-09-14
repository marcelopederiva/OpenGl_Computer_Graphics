// #version 430 core

// layout (location = 0) in vec4  vertex;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 atexCoords;
// uniform vec4  ObjectColor; 

//  uniform mat4 u_projMatrix;
//  uniform mat4 u_modelViewMatrix;
//  uniform vec4 u_modelquaternion;
//  uniform mat4 model;
// out vec4 vColor; // Outgoing varying data sent to the fragment shader
// out vec4 FragPos;
// out vec3 Normal;
// out vec4 LIGHT;
// out vec2 TexCoords;
// out flat int l_type;

// uniform int light_type;

// struct Material {
//     sampler2D diffuse;
//     sampler2D specular;  
//     vec3 Ka; 
//     vec3 Kd; 
//     vec3 Ks; 
//     int shineness; 
// }; 
// struct Light{
//     vec4 lightPos;
//     vec4 AmbientColor;
//     vec4 DiffColor;
//     vec4 SpecColor;
//     vec3 Spot_Direction;
//     float spot_exp;
//     float spot_cutoff;
// };


// uniform vec3 viewPos;
// uniform int ton;
// uniform sampler2D dtex;
// uniform sampler2D stex;


// uniform Material material;
// uniform Light light;
// void main() {
// // FLAT
// if(light_type == 0){

//         vColor = ObjectColor; 
//         LIGHT = vec4(1.0);
//         vec4 xVertex = u_modelViewMatrix * vertex;
//         gl_Position = u_projMatrix * xVertex;
//         FragPos =xVertex;
//         vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
//         Normal = N.xyz;
//         TexCoords = atexCoords;
//         l_type = 0;
// };
// //goraut
// if(light_type==1){

//         // vColor = ObjectColor; 
//         vec4 xVertex = u_modelViewMatrix * vertex;
//         gl_Position = u_projMatrix * xVertex;
//         FragPos =xVertex;
//         vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
//         Normal = N.xyz;
//         TexCoords = atexCoords;
        
//         int n = material.shineness;
//         int n_t = 1;
//         l_type = 1;
//         if(ton==0)
//         {   
//             // Fonte Pontual
//             vec3 lightDir = normalize(light.lightPos.rgb - FragPos.rgb);  
//             vec3 Iamb = material.Ka * light.AmbientColor.rgb;
            
//             // diffuse 
//             vec3 norm = normalize(Normal);
//             float NL = max(dot(norm, lightDir), 0.0);
//             vec3 diffuse = material.Kd *light.DiffColor.rgb*NL; 

//             // specular
//             vec3 viewDir = normalize(viewPos - FragPos.rgb);

//             vec3 reflectDir = 2*norm*NL - lightDir;
//             float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
//             vec3 specular = material.Ks * light.SpecColor.rgb* spec ;



//             vec3 result = vec3(Iamb + diffuse + specular)*ObjectColor.rgb;
//             LIGHT = vec4(result, 1.0);
//         }
//         if(ton==1)
//         {
//             // Fonte Direcional
//             vec3 lightDir = normalize(light.lightPos.xyz);  
//             // ambient
//             vec3 Iamb = material.Ka * light.AmbientColor.rgb;
            
//             // diffuse 
//             vec3 norm = normalize(Normal);
//             float NL = max(dot(norm, lightDir), 0.0);
//             vec3 diffuse = material.Kd *light.DiffColor.rgb*NL;

//             // specular
//             vec3 viewDir = normalize(viewPos - FragPos.rgb);

//             vec3 reflectDir = 2*norm*NL - lightDir;
//             float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
//             vec3 specular = material.Ks * light.SpecColor.rgb* spec ;



//             vec3 result = (Iamb + diffuse + specular)*ObjectColor.rgb;
//             LIGHT = vec4(result, 1.0);
//         }
//         if(ton==2)
//         { 
//             //SPOT
//             float cutoff = cos((light.spot_cutoff)*3.14/180.0);
//             vec3 lightDir = normalize(light.lightPos.xyz - FragPos.xyz);
//             float theta = dot(lightDir,normalize(-light.Spot_Direction));
//             if(theta > cutoff)
//             {
//                 // ambient
//                 vec3 Iamb = material.Ka * light.AmbientColor.rgb;

//                 // diffuse 
//                 vec3 norm = normalize(Normal);
//                 float NL = max(dot(norm, lightDir), 0.0);
//                 vec3 diffuse = material.Kd *light.DiffColor.rgb*NL;

//                 // specular
//                 vec3 viewDir = normalize(viewPos - FragPos.rgb);

//                 vec3 reflectDir = 2*norm*NL - lightDir;
//                 float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
//                 vec3 specular = material.Ks * light.SpecColor.rgb* spec;



//                 vec3 result = (Iamb + diffuse + specular)*ObjectColor.rgb;
//                 LIGHT = vec4(result, 1.0f);
//             }
//             else
//             { 
//                 // ambient
//                 // vec3 Ka = vec3(0.1,0.1,0.1);
//                 vec3 Iamb = material.Ka * light.AmbientColor.rgb;
//                 LIGHT = vec4(Iamb,1.0f);
//             }
//         }


//         }
// if(light_type==2){
//     LIGHT = vec4(1.0);
//     vColor = ObjectColor; 
//     vec4 xVertex = u_modelViewMatrix * vertex;
//     gl_Position = u_projMatrix * xVertex;
//     FragPos =xVertex;
//     vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
//     Normal = N.xyz;
//     l_type = 2;
//     TexCoords = atexCoords;
// };
// }


#version 430 core

layout (location = 0) in vec4  vertex;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 atexCoords;
in vec4 vertexcolor;
uniform vec4  ObjectColor; 

uniform mat4 u_projMatrix;
uniform mat4 u_modelViewMatrix;
uniform vec4 u_modelquaternion;
uniform mat4 viewerMatrix;
uniform mat4 model;
uniform int light_type;
out vec4 vColor; // Outgoing varying data sent to the fragment shader
out vec4 FragPos;
out vec3 Normal;
out vec4 LIGHT;
out vec2 TexCoords;
out flat int l_type;
out vec4 light_post;
flat out vec4 colorflat;
out vec4 spot_post;

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

uniform vec3 viewPos;
uniform int ton;
uniform sampler2D dtex;
uniform sampler2D stex;


uniform Material material;
uniform Light light;
void main() {
if(light_type == 0){
        light_post = vec4(viewerMatrix * light.lightPos);
        spot_post = viewerMatrix*light.Spot_Direction;
        // vec4 s = light.Spot_Direction;
        // spot_post = (viewerMatrix*s).xyz;
        vColor = ObjectColor; 
        LIGHT = vec4(1.0);
        vec4 xVertex = u_modelViewMatrix * vertex;
        gl_Position = u_projMatrix * xVertex;
        FragPos = xVertex;
        vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
        Normal = N.xyz;
        TexCoords = atexCoords;
        l_type = 0;
};
//goraut
if(light_type==1){
        light_post = vec4(viewerMatrix * light.lightPos);
        spot_post = viewerMatrix*light.Spot_Direction;
        vec4 xVertex = u_modelViewMatrix * vertex;
        gl_Position = u_projMatrix * xVertex;
        FragPos =xVertex;
        vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
        Normal = N.xyz;
        TexCoords = atexCoords;
        int n = material.shineness;
        int n_t = 1;
        l_type = 1;
        if(ton==0)
        {   
            // Fonte Pontual
            vec3 lightDir = normalize(light_post.rgb - FragPos.rgb);  
            vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
            
            // diffuse 
            vec3 norm = normalize(Normal);
            float NL = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb; 

            // specular
            vec3 viewDir = normalize(viewPos - FragPos.rgb);

            vec3 reflectDir = 2*norm*NL - lightDir;
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
            vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(material.diffuse, TexCoords.xy)).rgb ;



            vec3 result = vec3(Iamb + diffuse + specular);
            LIGHT = vec4(result, 1.0);
        }
        if(ton==1)
        {
            // Fonte Direcional
            vec3 lightDir = normalize((light.lightPos).xyz);  
            // ambient
            vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
            
            // diffuse 
            vec3 norm = normalize(Normal);
            float NL = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

            // specular
            vec3 viewDir = normalize(viewPos - FragPos.rgb);

            vec3 reflectDir = 2*norm*NL - lightDir;
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
            vec3 specular = material.Ks * light.SpecColor.rgb* spec *(texture(material.diffuse, TexCoords.xy)).rgb;



            vec3 result = (Iamb + diffuse + specular);
            LIGHT = vec4(result, 1.0);
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
                vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
                float attenuation = 1.0;
                attenuation*=pow(cutoff,light.spot_exp);
                // diffuse 
                vec3 norm = normalize(Normal);
                float NL = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

                // specular
                vec3 viewDir = normalize(viewPos - FragPos.rgb);

                vec3 reflectDir = 2*norm*NL - lightDir;
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
                vec3 specular = material.Ks * light.SpecColor.rgb* spec*attenuation*(texture(material.diffuse, TexCoords.xy)).rgb;



                vec3 result = (Iamb + diffuse + specular);
                LIGHT = vec4(result, 1.0f);
            }
            else
            { 
                // ambient
                // vec3 Ka = vec3(0.1,0.1,0.1);
                vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
                LIGHT = vec4(Iamb,1.0f);
            }
        }


        }
if(light_type==2){
    LIGHT = vec4(1.0);
    vColor = ObjectColor;
    spot_post = viewerMatrix*light.Spot_Direction;
    vec4 xVertex = u_modelViewMatrix * vertex;
    gl_Position = u_projMatrix * xVertex;
    FragPos =xVertex;
    vec4 N = vec4(   mat4(transpose(inverse(model)))   *    vec4(aNormal,1.0) );
    Normal = N.xyz;
    l_type = 2;
    light_post = viewerMatrix * light.lightPos;
    TexCoords = atexCoords;
    int n = material.shineness;
    int n_t = 1;
    if(ton==0)
    {   
        // Fonte Pontual
        vec3 lightDir = normalize( light_post.rgb - FragPos.rgb);  
        vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float NL = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb; 

        // specular
        vec3 viewDir = normalize(viewPos - FragPos.rgb);

        vec3 reflectDir = 2*norm*NL - lightDir;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
        vec3 specular = material.Ks * light.SpecColor.rgb* spec *(texture(material.diffuse, TexCoords.xy)).rgb;

        vec3 result = vec3(Iamb + diffuse + specular);
        colorflat = vec4(result, 1.0);
    }
    if(ton==1)
    {
        // Fonte Direcional
        vec3 lightDir = normalize((light.lightPos).xyz);  
        // ambient
        vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float NL = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos.rgb);

        vec3 reflectDir = 2*norm*NL - lightDir;
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
        vec3 specular = material.Ks * light.SpecColor.rgb* spec*(texture(material.diffuse, TexCoords.xy)).rgb;



        vec3 result = (Iamb + diffuse + specular);
        colorflat = vec4(result, 1.0);
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
            vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
            float attenuation = 1.0;
            attenuation*=pow(cutoff,light.spot_exp);
            // diffuse 
            vec3 norm = normalize(Normal);
            float NL = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = material.Kd *light.DiffColor.rgb*NL*(texture(material.diffuse, TexCoords.xy)).rgb;

            // specular
            vec3 viewDir = normalize(viewPos - FragPos.rgb);

            vec3 reflectDir = 2*norm*NL - lightDir;
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), n);
            vec3 specular = material.Ks * light.SpecColor.rgb* spec*attenuation*(texture(material.diffuse, TexCoords.xy)).rgb;



            vec3 result = (Iamb + diffuse + specular);
            colorflat = vec4(result, 1.0f);
        }
        else
        { 
            // ambient
            // vec3 Ka = vec3(0.1,0.1,0.1);
            vec3 Iamb = material.Ka * light.AmbientColor.rgb*(texture(material.diffuse, TexCoords.xy)).rgb;
            colorflat = vec4(Iamb,1.0f);
        }
    }
};
}


