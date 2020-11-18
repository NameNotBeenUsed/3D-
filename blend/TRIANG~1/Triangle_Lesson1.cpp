// Triangle_Lesson1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
enum VAO_IDs { Square, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;
GLuint flag = 1;

void init(void) {

	GLfloat vertices[] = {
		// positions              // colors
		0.0, 1.0, 0.0,            1.0, 0.0, 0.0,  // bottom right
		1.0, -sqrt(3) / 3,  0.0,  0.0, 1.0, 0.0,  // bottom left
		-1.0, -sqrt(3) / 3, 0.0,  0.0f, 0.0, 1.0,   // top

		-1.0, sqrt(3) / 3, 0.0,   0.0, 0.0, 1.0,  // bottom right
		1.0, sqrt(3) / 3, 0.0,    0.0, 1.0, 0.0,  // bottom left
		0.0,-1.0, 0.0,            1.0, 0.0, 0.0   // top

	};
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Square]);

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	ShaderInfo shader[] = {
		{ GL_VERTEX_SHADER, "triangle.vert" },
		{ GL_FRAGMENT_SHADER, "triangle.frag" },
		{ GL_NONE, NULL },
	};
	GLuint program = LoadShaders(shader);
	glUseProgram(program);
}

void keyborad_callback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		flag = 1;
		//glutPostRedisplay();
		break;
	case '2':
		flag = 2;
		//glutPostRedisplay();
		break;
	case '3':
		flag = 3;
		//glutPostRedisplay();
		break;
	case '4':
		flag = 4;
		//glutPostRedisplay();
		break;
	case '5':
		flag = 5;
		//glutPostRedisplay();
		break;
	case '6':
		flag = 6;
		//glutPostRedisplay();
		break;
	default:
		break;
	}
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[VAO_IDs::Square]);

	glEnable(GL_BLEND);

	switch (flag)
	{
	case 1:
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_ZERO);
		glBlendEquation(GL_FUNC_ADD);
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角
		break;
	case 2:
		glBlendFunc(GL_ONE, GL_ZERO);//下三角在上 参数前为源颜色 后为目标颜色
		glBlendEquation(GL_FUNC_ADD);
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角
		break;
	case 3:
		//glBlendFunc(GL_ZERO, GL_ONE);//什么都不显示
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角
		break;
	case 4:
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
		glBlendEquation(GL_MAX);
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角
		break;
	case 5:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_SUBTRACT);
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角
		break;
	case 6:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
		glDrawArrays(GL_TRIANGLES, 0, 3);//上三角 目标颜色 先在颜色缓冲中
		glDrawArrays(GL_TRIANGLES, 3, 3);//下三角
	default:
		break;
	}
	//glBlendFuncSeparate(GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ZERO);//下三角在上 参数前为源颜色 后为目标颜色
	//glBlendFunc(GL_ZERO, GL_ONE);//只显示上三角 源颜色即下三角的参数被设置为0
	//glDrawArrays(GL_TRIANGLES, 0, 3);//上三角 目标颜色 先在颜色缓冲中
	//glDrawArrays(GL_TRIANGLES, 3, 3);//下三角
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Triangle Windows");
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		cerr << "Unable to Initialize GLEW" << endl;
	}
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyborad_callback);
	glutMainLoop();
	return 0;
}

