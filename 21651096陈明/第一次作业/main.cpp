#include <iostream>
#include <GL/glut.h>
static double year = 0, day = 0, startYear = 0;
static double moonDay = 0, moonMonth = 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //�������
	/*�滭̫��*/
	glPushMatrix();
	glColor3f(237 / 255.0, 200 / 255.0, 0.0); // ������ɫ
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//̫����ת
	glutWireSphere(1.01, 40, 16);     // ����������
	glPopMatrix(); // ��ջ��ȡ��ԭʼ״̬
	/*���Ƶ�����*/
	glPushMatrix();  // �����֡λ�ú�״̬
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	glutSolidTorus(0.005, 3.0, 10, 64);
	glPopMatrix();
	/*���Ƶ���*/
	glPushMatrix();
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);//���ǹ�ת
	glTranslatef(3.0, 0.0, 0.0);
	glColor3f(180 / 255.0, 100 / 255.0, 15 / 255.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);//������ת
	glutWireSphere(0.3, 20, 8);
	/*�������ǹ��*/
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	//glRotatef(45.0f, 0.0, 0.0, 1.0);
	glutSolidTorus(0.005, 1.0, 10, 64);
	glPopMatrix();
	/*�滭����*/
	glPushMatrix();
	glRotatef((GLfloat)moonMonth, 0.0, 1.0, 0.0);
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)moonDay, 0.0, 1.0, 0.0);
	glColor3f(255 / 255.0, 255 / 255.0, 20 / 255.0);
	glutWireSphere(0.2, 20, 8);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers(); // ����˫������ָ��

}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // ���ô��������ɫ
	glShadeModel(GL_FLAT);  //������ɫģʽ
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0);
}

void idle()
{
	moonDay = moonDay + 0.04;
	if (moonDay >= 360)
	{
		moonDay -= 360;
	}
	moonMonth = moonMonth + 0.03;
	if (moonMonth >= 360)
	{
		moonMonth -= 360;
	}
	day = day + 0.02;
	if (day >= 360)
	{
		day -= 360;
	}
	//    �ɿ��Ƶ���ת�����ٶ�
	year = year + 0.04;
	if (day >= 360)
	{
		year -= 360;
	}
	startYear = startYear + 0.002;
	if (startYear >= 360)
	{
		startYear -= 360;
	}

	glutPostRedisplay();
}


int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ָ��ʹ��RGBAģʽ��˫���崰��
	glutInitWindowSize(1000, 700);  // ��ʼ�����ڴ�С
	glutInitWindowPosition(300, 100); // ��ʼ��λ��
	glutCreateWindow("��һ����ҵ-̫��ϵ");  // ����
	init();
	glutDisplayFunc(display); // ���ƴ���
	glutReshapeFunc(reshape); // �ı䴰��ʱ���»���
	glutIdleFunc(idle); // 
	glutMainLoop();    // glut��������¼�ѭ��
	return 0;
}