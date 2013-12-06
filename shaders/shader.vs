attribute vec4 VertexPosition;

uniform mat4 MatModelView;
uniform mat4 MatProjection;

void main()
{
    vec4 cam_pos = MatModelView * VertexPosition;
    gl_Position  = MatProjection * cam_pos;
    /*gl_Position = VertexPosition;*/
}
