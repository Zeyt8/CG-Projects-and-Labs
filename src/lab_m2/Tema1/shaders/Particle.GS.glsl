#version 430

// Input and output topologies
layout(points) in;
layout(triangle_strip, max_vertices = 100) out;

// Uniform properties
uniform mat4 Projection;
uniform mat4 viewMatrices[6];
uniform mat4 Model;
uniform vec3 eye_position;
uniform int type;

in float vert_lifetime[1];
in float vert_iLifetime[1];

// Output
layout(location = 0) out vec2 texture_coord;
layout(location = 1) out float geom_lifetime;
layout(location = 2) out float geom_iLifetime;


// Local variables
vec3 vpos = gl_in[0].gl_Position.xyz;
vec3 forward = normalize(eye_position - vpos);
vec3 right = normalize(cross(forward, vec3(0, 1, 0)));
vec3 up = normalize(cross(forward, right));


void EmitPoint(vec2 offset, int layer)
{
    geom_lifetime = vert_lifetime[0];
    geom_iLifetime = vert_iLifetime[0];
    vec3 pos = right * offset.x + up * offset.y + vpos;
    gl_Position = Projection * viewMatrices[layer] * Model * vec4(pos, 1.0);
    EmitVertex();
}


void main()
{
    if (type != 2) return;
    float ds = 0.05f;
    for (int layer = 0; layer < 6; layer++) {
        gl_Layer = layer;
        texture_coord = vec2(0, 0);
        EmitPoint(vec2(-ds, -ds), layer);
        texture_coord = vec2(0, 1);
        EmitPoint(vec2(-ds, ds), layer);
        texture_coord = vec2(1, 0);
        EmitPoint(vec2(ds, -ds), layer);
        texture_coord = vec2(1, 1);
        EmitPoint(vec2(ds, ds), layer);
	    EndPrimitive();
    }
}
