// ConsoleApplication4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL/freeglut.h> 
#include "delaunay.h"
#include "windows.h" // for time statistics
std::vector<std::pair<float, float>> outData;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色为黑色
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式
}
void myDisplay(void)
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	glClear(GL_COLOR_BUFFER_BIT);// 将缓存清除为预先的设置值,即黑色
	//glTranslatef(0.8, 0.0, 0.0);//平移函数，暂时可以不用
// 	glBegin(GL_TRIANGLES);//开始画三角形
// 	glColor3f(1.0, 0.0, 0.0);//设置第一个顶点为红色
// 	glVertex2f(-1.0, -1.0);//设置第一个顶点的坐标
// 	glColor3f(0.0, 1.0, 0.0);//设置第二个顶点为绿色
// 	glVertex2f(0.0, -1.0);//设置第二个顶点的坐标
// 	glColor3f(0.0, 0.0, 1.0);//设置第三个顶点为蓝色
// 	glVertex2f(-0.5, 1.0);//设置第三个顶点的坐标
// 	glEnd();//三角形结束
	glPushMatrix();
	glScalef(100.0f, 100.0f, 100.0f);
	glBegin(GL_TRIANGLES);//开始画三角形
	
	for (auto v: outData)
	{
		glVertex2f(v.first,v.second);//设置第一个顶点的坐标
	}
	glEnd();
	glPopMatrix();
	glFlush();//强制OpenGL函数在有限时间内运行
}
void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);//设置视口
	glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
	glLoadIdentity();//将当前矩阵置换为单位阵
// 	if (w <= h)
// 		gluOrtho2D(-1.0, 1.5, -1.5, 1.5*(GLfloat)h / (GLfloat)w);//定义二维正视投影矩阵
// 	else		
	gluOrtho2D(-w/2, w/2, -h/2, h/2);
	glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW
}
int main(int argc, char ** argv)
{
	/*初始化*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//单缓冲、RGB模式
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("三角形");//窗口标题
	MESH mesh;
	double last_time, this_time;
	//int ver_num;
	//int tri_num;

	Input("F:/学习/3D编程/实验/作业/Delaunay/ConsoleApplication4/input_points.txt", &mesh);

	last_time = GetTickCount();

	IncrementalDelaunay(&mesh);
	//Sleep(1000);
	this_time = GetTickCount();

	printf("Elapsed Time for Incremental Delaunay: %lg ms", this_time - last_time);
	Output("output_triangles.txt", &mesh, outData);
	

	init();
	/*绘制与显示*/
	glutReshapeFunc(myReshape);//窗口大小发生改变时采取的行为
	glutDisplayFunc(myDisplay);//显示绘制图形
	glutMainLoop();//循环
	return(0);
}

