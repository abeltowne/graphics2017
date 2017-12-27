#include <windows.h>
#include "Utility.h"
#include <gl/glut.h>

GLuint textureID[3];

void loadTextures(){

	glGenTextures(3, textureID);//ò��Ҫ�������ʱɾ��

	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	LoadTGA("sunmap.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	LoadTGA("earthmap.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	LoadTGA("moonmap.tga", GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void Initial(){

	GLfloat light0_diffuse[]={1.0f,1.0f,1.0f,1.0f};//light0������������
	GLfloat light0_position[]={10.0f,20.0f,-150.0f,1.0f};//light0������λ��
	GLfloat light0_direction[]={0.0f,0.0f,-1.0f};//light0�ľ۹�Ʒ����

	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);//light0��̫������
	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light0_direction);

	glEnable(GL_DEPTH_TEST);// ������Ȳ���
	glEnable(GL_LIGHTING);// ���ù�Դ
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);//������ɫ����ģʽ
	glFrontFace(GL_CCW);// ָ����ʱ���Ʒ���ʾ���������

	glClearColor(0.75f, 0.75f,0.75f, 1.0f );//����

	loadTextures();
}

void ChangeSize(int w, int h){

	if(h==0)h=1;      

	glViewport(0,0,w,h);// ���������ߴ�

	glMatrixMode(GL_PROJECTION);//ָ����ǰ����ͶӰ�����ջ

	glLoadIdentity();//����ͶӰ����

	gluPerspective(35.0,(float)w/(float)h,1.0,500.0);//ָ��͸��ͶӰ�Ĺ۲�ռ�

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void Display(void){

	static float angle1=0.0f, angle2=0.0f;

	//angle1������̫����ת�ĽǶȣ�angle2�����Ƶ�����ת�ĽǶ�

	GLfloat sun_emission[]={0.6f,0.0f,0.0f,1.0f};//̫����ɫ
	GLfloat earth_emission[]={0.0f,0.0f,0.8f,1.0f};//������ɫ
	GLfloat moon_emission[]={0.98f,0.625f,0.12f,1.0f};//������ɫ

	GLfloat light1_diffuse[]={1.0f,1.0f,1.0f,1.0f};//��Դlight1������������
	GLfloat light1_position[]={50.0f,100.0f,100.0f,1.0f};//��Դlight1������λ��
	GLfloat light1_direction[]={0.0f,0.0f,-1.0f};//��Դlight1�ľ۹�Ʒ����

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ�����

	glMatrixMode(GL_MODELVIEW);//ָ����ǰ����ģ����ͼ�����ջ

	glLoadIdentity();//����ģ����ͼ����

	glTranslatef(0.0f,0.0f,-150.0f);//��ͼ����z�Ḻ���ƶ�150.0f

	//����̫��
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light1_direction);

	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,sun_emission);

	//glutSolidSphere(12.0f,30,30);//����̫��
	glRotatef(angle1, 0.0f, 10.0f, 1.0f);
	gltDrawSphere(12.0f,30,30);

	glDisable(GL_LIGHT1);

	//���Ƶ���

	glPushMatrix();//���浱ǰ�ľ�����ͼģ��

	glRotatef(angle1,0.0f,10.0f,1.0f);//��תһ���Ƕ�
	glTranslatef(40.0f,0.0f,0.0f);//��x�������ƶ�40.0f

	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,earth_emission);	

	//glutSolidSphere(6.0f,20,20);//���Ƶ���
	glRotatef(angle2,0.0f,10.0f,1.0f);
	gltDrawSphere(6.0f,20,20);

	//��������

	glRotatef(angle2,0.0f,1.0f,0.0f);
	glTranslatef(15.0f,0.0f,0.0f);//��x�᷽���ƶ�15.0f

	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,moon_emission);	

	//glutSolidSphere(3.0f,20,20);//��������
	glRotatef(angle2,0.0f,10.0f,1.0f);
	gltDrawSphere(3.0f,20,20);


	glPopMatrix();//�ָ�������ͼģ��

	angle1-=2.0f;//������ת��������������Ч��
	if(angle1==360.0f)
		angle1=0.0f;

	angle2-=20.0f;
	if(angle2==360.0f)
		angle2=0.0f;

	glutSwapBuffers();
}

void TimerFunc(int x){

	glutPostRedisplay();
	glutTimerFunc(100,TimerFunc,1);
}

int main(int argc, char* argv[]){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(640,480);
	glutInitWindowPosition(400,200);

	glutCreateWindow("̫����������");

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);

	glutTimerFunc(500,TimerFunc,1);

	Initial();

	glutMainLoop();

	return 0;
}