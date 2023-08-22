#version 330 core

out vec4 FragColor;
in vec4 gl_FragCoord;



const int TILE_MAP_SIZE = 256;
uniform float time = 0.;
uniform vec2 resolution = vec2(800,600);

uniform sampler2D tileTexture;
uniform sampler2D tileData;

//uniform int tiles[TILE_MAP_SIZE*TILE_MAP_SIZE];

uniform vec2 pos = vec2(0,0);
uniform vec2 size = vec2(256.0,256.0);

uniform float tileSizePx = 48.0;
uniform float cameraFact = 1.;

uniform vec2 dir = normalize(vec2(0,1));
uniform mat2 dirMtx;

uniform float planeRad = 67.88225;

//-----------------------------
vec4 renderPlane(vec2 centeredPos);
int getTileAt(vec2 pos);
vec2 getTileUv(int id);
//-----------------------------



void main()
{
    vec2 uv = gl_FragCoord.xy/resolution.xy;
    vec2 centered = gl_FragCoord.xy-0.5*resolution.xy;
    centered.y*=-1;
    
    /*
    vec4 color = vec4(0);
        //color = texture(tileData, uv);
    
    
    if(uv.y<0.5){
        color = texture(tileTexture, uv);
    } else{
        color = vec4(0);
        color = texture(tileData, uv);
    }
    FragColor = color;
    return;//*/
    
    if (length(centered) <= planeRad){
        vec4 planeColor = renderPlane(centered);
        if(planeColor!=vec4(0)){
            FragColor = planeColor;
            return;
        }
    }

    vec2 pxPos = pos+centered;

    vec2 sizeInPx = size*tileSizePx;

    vec2 mapUV = mod(pxPos,sizeInPx)/sizeInPx;
    vec2 tileInnerUv = mod(pxPos,tileSizePx)/(8*tileSizePx);

    int id = getTileAt(mapUV);
    vec2 tileUv = getTileUv(id);

    FragColor = texture(tileTexture, tileUv+tileInnerUv);
    //FragColor = texture(tileTexture, vec2(0.1,0.1));

    //FragColor = vec4(abs(sin(time)), 0.6f, 0.9f, 1.0f);
}


vec4 renderPlane(vec2 centeredPos){
    //return vec4(0.5,0.3,1,1);
    vec2 norm = centeredPos/planeRad*sqrt(2.0);
    
    mat2 dirTrMtx = mat2(dir.x ,-dir.y,
                         dir.y, -dir.x);
                 
    vec2 trs = norm*dirMtx;
    
    if(abs(trs.x)>1. || abs(trs.y) >1.) return vec4(0);
    
    vec2 offset = getTileUv(63);
    vec2 txtCoord = offset+trs/8.0;
    return texture(tileTexture,txtCoord);
}

int getTileAt(vec2 pos){
    //return 0;
     //int(mod(tilePos.x,4))
    //*
    float asFloat = texture(tileData, pos).x;
    return int(asFloat*255);//*/
}

vec2 getTileUv(int id){
    vec2 uv = vec2( mod(id,8.0)/8.0, (id/8)/8.0 );
    return uv;
}