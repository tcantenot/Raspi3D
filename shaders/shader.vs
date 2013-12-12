attribute vec4 VertexPosition;

uniform mat4 MatModelView;
uniform mat4 MatProjection;
uniform float time;
uniform float random;
uniform float maxHeight;

varying vec4 color;

vec4 calc_color(float h)
{
    vec4 max_color(1, 0, 0);
    vec4 min_color(0, 0, 1);

    
    float red  = (maxHeigth - h) / (2 * maxHeight);
    float blue = (maxHeigth - h) / (2 * maxHeight);

    return vec4(red, 0, blue, 1);
}

void main()
{
    float h = VertexPosition.y * cos(time) * random;
    color = calc_color(h);
    vec4 cam_pos = MatModelView * vec4(VertexPosition.x, h, VertexPosition.zw);
    gl_Position  = MatProjection * cam_pos;
    /*gl_Position = VertexPosition;*/
}
