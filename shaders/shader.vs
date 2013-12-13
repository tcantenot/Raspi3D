attribute vec4 VertexPosition;

uniform mat4 MatModelView;
uniform mat4 MatProjection;
uniform float time;
uniform float random;
uniform float maxHeight;
uniform float terrainWidth;
uniform float terrainHeight;

varying vec4 color;

vec4 calc_color(float h)
{
    vec4 max_color = vec4(1.0, 0.2, 0.5, 1.0);
    vec4 min_color = vec4(0.0, 0.0, 1.0, 1.0);

    vec4 outColor = min_color + (h - (-maxHeight)) * (max_color - min_color) / (2.0 * maxHeight);

    outColor = outColor * 1.2;

    return vec4(outColor.xyz, 1.0);
}

vec4 rainbow(float x, float y, float z)
{
    vec4 ambient = vec4(0.1, 0.1, 0.1, 0.0);
    return ambient + vec4(abs(1.5*x)/terrainWidth, abs(3.0*y)/terrainHeight,
        abs(2.0*z)/maxHeight, 1.0);
}

void main()
{
    float h = VertexPosition.y * cos(time) * random;
    /*color = calc_color(h);*/
    color = rainbow(VertexPosition.x, VertexPosition.y, VertexPosition.z);
    vec4 cam_pos = MatModelView * vec4(VertexPosition.x, h, VertexPosition.zw);
    gl_Position  = MatProjection * cam_pos;

    /*gl_Position = VertexPosition;*/
}
