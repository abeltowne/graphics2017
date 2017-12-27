#include "stdafx.h"
#include <gl/glut.h>
#include <stdio.h>
#include <Windows.h>
// ̫�������������   
// ����ÿ���¶���12��   
// һ��12���£�����360��   
static int day = 200; // day�ı仯����0��359

void myDisplay(void)
{
	//glEnable����д��glBegin��glEnd���������м䡣
	glEnable(GL_DEPTH_TEST);//������Ȳ��ԡ����������Զ���Զ����ر���ס��ͼ�Σ����ϣ�
	glDepthFunc(GL_EQUAL);//ָ����Ȼ���Ƚ�ֵ�������������ֵ���ڲο�ֵ����ͨ��
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�����Լ���Ȼ���

	glMatrixMode(GL_PROJECTION);//��ͶӰ����Ӧ�����ľ������
	glLoadIdentity();//����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
	gluPerspective(75, 1, 1, 400000000);//ָ���˹۲���Ӿ��壬����Ϊ����Ұ�ĽǶȣ��Ӿ���Ŀ�߱ȣ���ƽ�棬Զƽ��
	glMatrixMode(GL_MODELVIEW);//��ģ���Ӿ������ջӦ�����ľ������
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);//����һ����ͼ���󣬲���Ϊ��
	//��һ��eyex, eyey,eyez ��������������λ��
	//�ڶ���centerx,centery,centerz �����ͷ��׼�����������������λ��
	//������upx,upy,upz ������ϵķ��������������еķ���

	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

	// ���ƺ�ɫ�ġ�̫����
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotated(a, 0, 0, -1);//����������Ϊʲô��const���������Կ�����ת��
	glutSolidSphere(69600000, 20, 20);//��Ⱦһ�����塣��������λ��ԭ�㡣����Ϊ���뾶����Z�����߶�Ϊֱ���ֲ���Բ���ߵ�������Χ����Z����Χ���ߵ�����
	glPopMatrix();

	// ������ɫ�ġ�����
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);//��ת�������ֹ���
	glTranslatef(150000000, 0.0f, 0.0f);//ƽ�ƾ���ע�ⲻ�����壬���ǻ�������ϵ��glTranslatef��glRotatef���ǡ�
	glRotated(a, 0, 0, -1);
	glutSolidSphere(15945000, 20, 20);
	
	// ���ƻ�ɫ�ġ�������
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	glRotated(a, 0, 0, -1);
	glutSolidSphere(4345000, 20, 20);
	glPopMatrix();

	glFlush();//ǿ��ˢ�»��壬��֤��ͼ�����ִ�У������Ǵ洢�ڻ�����
	glutSwapBuffers();//˫���������ƣ�����������
}  

void myIdle(void)
{
	++day;
	Sleep(50);
	if( day >= 360 )
		day = 0;
	myDisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char *argv[])
{  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//���ó�ʼ��ʾģʽ�� RGB ��ɫģʽ��˫����Ĵ���
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("̫�������������");

	glutDisplayFunc(&myDisplay);//ע��һ����ͼ����
	glutIdleFunc(&myIdle);//����ȫ�ֵĻص���������û�д����¼�����ʱ��GLUT�����ܿ���ִ�к�̨�������������������

	glEnable(GL_CULL_FACE);//�ڵ�
    glCullFace(GL_BACK);//�����޳�

    glEnable(GL_LIGHT0);//��Դ0
    glEnable(GL_COLOR_MATERIAL);//�������
    glEnable(GL_LIGHTING);//����

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);//������
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);//ɢ���
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);//���淴���
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//��Դλ��

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);//���ʵĻ�����ɫ
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);//���ʵ�ɢ����ɫ
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);//���ʵľ��淴����ɫ
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);//���淴��ָ��

	glutMainLoop();//����GLUT�¼�����ѭ���������е��롰�¼����йصĺ�����������ѭ����

	return 0;
}