attribute vec4 VertexPosition;

uniform mat4 MatModelView;
uniform mat4 MatProjection;
uniform float time;
uniform float random;

void main()
{
    vec4 cam_pos = MatModelView * vec4(VertexPosition.x, VertexPosition.y * cos(time) * random, VertexPosition.zw);
    gl_Position  = MatProjection * cam_pos;
    /*gl_Position = VertexPosition;*/
}
