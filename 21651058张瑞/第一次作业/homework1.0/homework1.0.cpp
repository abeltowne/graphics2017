#include<stdio.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include<gl/GLUT.H>


static float year = 0, day = 0;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//�趨��ɫģʽ��ʹ��ͼԪ��ĳ���������ɫ����Ⱦ����ͼԪ��
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glPushMatrix();
	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


	//����̫��
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glutWireSphere(0.8, 20, 20);



	//���Ƶ���
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glutWireSphere(0.2, 20, 20);


	//��������
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glutWireSphere(0.1, 15, 15);

	//glutWireCube(2.0);
	glPopMatrix();
	glutSwapBuffers();


}


void spinDisplay(void)
{
	year = year + 0.003;
	if (year > 360.0)
	{
		year = year - 360.0;
	}
	day = day + 0.006;
	if (day > 360.0)
	{
		day = day - 360.0;
	}


	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//�������ã���һ���Ӿ����ȡͼ��


											 //glFrustum(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_PROJECTION);//mode ָ����һ�������ջ����һ�����������Ŀ��,������ʾ������Ҫ����ͶӰ��صĲ���


	glLoadIdentity();//���õ�ǰ�仯����Ϊ��λ���󣻵�λ������ǶԽ����϶���1������Ԫ�ؽ�Ϊ0�ľ���Ȼ��λ


					 //glOrtho(-3.0,3.0,-3.0,3.0,-3.0,3.0);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	glMatrixMode(GL_MODELVIEW);//�����Ӿ���صĲ���


							   //glLoadIdentity();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Homework 01");
	glutInitWindowPosition(50, 50);
	//glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
	return 0;
}