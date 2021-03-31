// ConsoleApplication4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <GL/freeglut.h> 
#include "delaunay.h"
#include "windows.h" // for time statistics
std::vector<std::pair<float, float>> outData;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//���ñ�����ɫΪ��ɫ
	glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ
}
void myDisplay(void)
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);// ���������ΪԤ�ȵ�����ֵ,����ɫ
	//glTranslatef(0.8, 0.0, 0.0);//ƽ�ƺ�������ʱ���Բ���
// 	glBegin(GL_TRIANGLES);//��ʼ��������
// 	glColor3f(1.0, 0.0, 0.0);//���õ�һ������Ϊ��ɫ
// 	glVertex2f(-1.0, -1.0);//���õ�һ�����������
// 	glColor3f(0.0, 1.0, 0.0);//���õڶ�������Ϊ��ɫ
// 	glVertex2f(0.0, -1.0);//���õڶ������������
// 	glColor3f(0.0, 0.0, 1.0);//���õ���������Ϊ��ɫ
// 	glVertex2f(-0.5, 1.0);//���õ��������������
// 	glEnd();//�����ν���
	glPushMatrix();
	glScalef(100.0f, 100.0f, 100.0f);
	glBegin(GL_TRIANGLES);//��ʼ��������
	
	for (auto v: outData)
	{
		glVertex2f(v.first,v.second);//���õ�һ�����������
	}
	glEnd();
	glPopMatrix();
	glFlush();//ǿ��OpenGL����������ʱ��������
}
void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);//�����ӿ�
	glMatrixMode(GL_PROJECTION);//ָ����ǰ����ΪGL_PROJECTION
	glLoadIdentity();//����ǰ�����û�Ϊ��λ��
// 	if (w <= h)
// 		gluOrtho2D(-1.0, 1.5, -1.5, 1.5*(GLfloat)h / (GLfloat)w);//�����ά����ͶӰ����
// 	else		
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);//ָ����ǰ����ΪGL_MODELVIEW
}
int main(int argc, char ** argv)
{
	/*��ʼ��*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//�����塢RGBģʽ
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("������");//���ڱ���
	MESH mesh;
	double last_time, this_time;
	//int ver_num;
	//int tri_num;

	Input("F:/ѧϰ/3D���/ʵ��/��ҵ/Delaunay/ConsoleApplication4/input_points.txt", &mesh);

	last_time = GetTickCount();

	IncrementalDelaunay(&mesh);
	//Sleep(1000);
	this_time = GetTickCount();

	printf("Elapsed Time for Incremental Delaunay: %lg ms", this_time - last_time);
	Output("output_triangles.txt", &mesh, outData);
	

	init();
	/*��������ʾ*/
	glutReshapeFunc(myReshape);//���ڴ�С�����ı�ʱ��ȡ����Ϊ
	glutDisplayFunc(myDisplay);//��ʾ����ͼ��
	glutMainLoop();//ѭ��
	return(0);
}

