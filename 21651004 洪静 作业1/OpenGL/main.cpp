#include <GL/glut.h>
static int day = 0;

void MyDisplay(){    
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//����һ����׶��
	gluPerspective(75, 1, 1, 400000);

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


void OnTimer(int value){
	day++;
	if (day > 365){
		day = 0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(30, OnTimer, 0);
}

int main(int argc, char **argv){   
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(400, 400);
	glutCreateWindow("homework");
	
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(30, OnTimer, 0);
	glutMainLoop();
	return 0;
}
