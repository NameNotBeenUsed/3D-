#version 430 core
in vec4 color;
out vec4 fColor;
void main()
{
	//float b = 3.1f;
	//fColor = abs(vec4(1.0, 1.0, 1.0, 0.0)*color)*b;
	//mat4 m = mat4(1);
	//vec4 v = m[0];
	//fColor = vec4(1.0, 1.0, 1.0, 1.0)*v;
	fColor = color;
}