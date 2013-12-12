attribute vec4 VertexPosition;

uniform mat4 MatModelView;
uniform mat4 MatProjection;
uniform float time;

void main()
{
    /*gl_PointSize = 10;*/
    vec4 cam_pos = MatModelView * vec4(VertexPosition.x, VertexPosition.y * cos(time), VertexPosition.zw);
    gl_Position  = MatProjection * cam_pos;
    /*gl_Position = VertexPosition;*/
}
