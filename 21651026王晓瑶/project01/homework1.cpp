// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include <GL/glut.h>
static int day = 0;

void Display()
{    
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//�����ɫ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ʹ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	//����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
	glLoadIdentity();

	//����һ����׶��
	gluPerspective(85, 1, 1, 500000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//��һ������Ϊ�Դ�λ�ã��ڶ�������Ϊ�۾����������λ�ã���������ͷ������ķ���
	gluLookAt(0, -200000, 200000, 0, 0, 0, 0, 0, 1);

	//����̫��
	glColor3f(1, 0, 0);
	glutSolidSphere(69600, 20, 20);

	//���Ƶ���
	glColor3f(0, 0, 1);
	glRotatef(day, 0, 0, -1);
	glTranslatef(150000, 0, 0);
	glutSolidSphere(15945, 20, 20);

	//��������
	glColor3f(1, 1, 0);
	glRotatef(day / 30.0 * 360 - day, 0, 0, -1);
	glTranslatef(38000, 0, 0);
	glutSolidSphere(4345, 20, 20);

	//ִ��˫���彻��
	glutSwapBuffers();

}


//��value�������ĸ���ʱ�����ں�����ı��λ���йصı���������glutPostRedisplay()�����ػ�
//����ٴε���glutTimerFunc����Ϊglut�Ķ�ʱ���ǵ���һ�βŲ���һ�ζ�ʱ
void Timer(int value)
{
	day++;
	if (day > 365)
	{
		day = 0;
	}
	
	//��ǵ�ǰ������Ҫ���»���
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

int main(int argc, char **argv)
{   
	//��GLUT���г�ʼ�������������������в���
	glutInit(&argc, argv);

	//ָ��ʹ��RGBAģʽ��˫���崰��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	//���ô��ڴ���ʱ�Ŀ��
	glutInitWindowSize(800, 800);
	//����һ������
	glutCreateWindow("test");
	
	//�ص�������������������Ҫ������ʾʱ��ע��Ļص������ᱻִ��
	glutDisplayFunc(Display);
	//��ʱ��
	glutTimerFunc(50, Timer, 0);
	glutMainLoop();
	return 0;
}