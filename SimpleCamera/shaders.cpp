 
const char * g_vertexShaderSource = "#version 150\n in vec2 position; void main(){ gl_Position = vec4( position, 0.0, 1.0 ); }";

const char * g_fragmentShaderSource = "#version 150\n out vec4 outColor; void main(){ outColor = vec4( 1.0, 1.0, 1.0, 1.0 ); }";


