attribute vec4 a_position;
attribute vec4 a_color;
 
out vec4 out_color;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
	out_color = a_color;
}