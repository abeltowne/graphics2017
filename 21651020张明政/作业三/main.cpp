#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "GlAux.lib")
#pragma comment(lib, "glut.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "OPENGL32.LIB")

#define GLUT_DISABLE_ATEXIT_HACK 
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glut.h>
#include <GL/GLAux.h>
#include "camera.h"
#include "mushroom.h"
#include <string>
#include <ctime>
#include <math.h>
struct CAMERA camera;     
float DEG_TO_RAD = 0.017453f;
int Window_Width = 1366;
int Window_Height = 768;
struct mPOINT oldpt={Window_Width/2, Window_Height/2}; 

int timestate = 0;//��ʱ
///////////////////////////////�����ĳ���
int L = 1000;			//�����ĳ���
float W = 0.5;		
int H = 1618;			//�����Ŀ��
int WH = 1000;		//����ǽ�ĸ߶�
int SR = 2350;
///////////////�������λ�úͳ���/////////////
float eyePX = 0.0f;
float eyePY = 80.0f;
float eyePZ = 100.0f;

float viewDX = eyePX + 0.0f;
float viewDY = eyePY + 0.0f;
float viewDZ = eyePZ + (-1.0f);
////////////////////////////////////////////////////////////
//ȫ�ֻ�����
float lmodel_ambient[] = {0.0f, 0.0f, 1.0f, 1.0f};

//����������ݹ�Դ
GLfloat light_ambient[] = { 1.0f , 1.0f , 1.0f , 1.0f };
GLfloat light_diffuse[] = { 1.0f , 0.7f , 0.2f , 1.0f };
GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_position[] = { 0.0f, 140.0f , 0.0f, 1.0f };
GLfloat light_spot_direction[] = {0.0f,-1.0f , 0.0f};

//�ֵ�Ͳ��Դ
GLfloat light_ambienth[] = { 1.0f , 1.0f , 1.0f , 1.0f };
GLfloat light_diffuseh[] = { 1.0f , 1.0f , 1.0f , 1.0f };
GLfloat light_specularh[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat light_positionh[] = { 0.0f, 0.0f , 0.0f, 1.0f };
GLfloat light_spot_directionh[] = {0.0f,0.0f , -1.0f};

int SPOT_LIGHT_ON = 1;			//�ֵ�Ͳ�Ŀ���״̬
/////////////////////////////////////////////////
//һ������Ĳ���
GLfloat ambient[]   = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat diffuse[]   = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat shininess   = 0.0f;
//�����Ĳ���
GLfloat ambient1[]   = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat diffuse1[]   = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat specular1[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat emission1[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shininess1   = 10.0f;
//���ݵĲ���
GLfloat ambient2[]   = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse2[]   = {0.9f, 0.8f, 0.2f, 1.0f};
GLfloat specular2[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat emission2[] = {0.9f, 0.8f, 0.2f, 1.0f};
GLfloat shininess2   = 1.0f;
//�����Ĳ���
GLfloat ambient3[]   = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat diffuse3[]   = {0.3f, 0.7f, 0.6f, 1.0f};
GLfloat specular3[] = {0.2f, 0.1f, 0.1f, 1.0f};
GLfloat emission3[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat shininess3   = 0.0f;

GLfloat shadowMat[4][4];	//��Ӱ����

const GLfloat P[4] = {0.0f, 1.0f, 0.0f, -3.0f}; //��Ӱƽ������
////////////////////////////////////////////////////////////////////
GLuint ID[50];            //���������s 

GLUquadricObj *quadric;	// ���������������
/////////////////////////////////////////////////////////////////////
struct MUSHROOM
{
	float x, y, z;					//Ģ����λ��
	int texT, texM, texB;			//Ģ����ͬ���ֶ�Ӧ������
};
#define MAX_MUSHROOM_ORG 30			//���Ģ����
int MAX_MUSHROOM = 30;
MUSHROOM* mushroom;
//MUSHROOM mushroom[MAX_MUSHROOM];
/////////////////////////////////////////////////////////////////////
float dstx;
float dsty;
float dstz;
																		//���ӷ��е�Ŀ��λ��
typedef struct
{
	float	life;														// ��������
	float	fade;														// ����˥���ٶ�
	float	r,g,b;														// ���ӵ���ɫ
	float	x,y,z;														// ����λ��
	float	xSpeed,ySpeed,zSpeed;										// ���ӵ��ٶ�
	float	xg,yg,zg;													// ���ӵ��˶����ٶ�
} PARTICLES;
#define MAX_PARTICLES 5000    //�����������
PARTICLES particle[MAX_PARTICLES];										// ����ϵͳ����
float	speedFator = 0.05f;
float MaxSpeed = 50.0f;		//��������ٶ�
int timesection = 0;			
float PR = 0.9f;				//���Ӱ뾶
float LIFE = 4.0f;				//��������
typedef struct
{
	float r;
	float g;
	float b;
}COLORRGB;
#define COLORS 300 
COLORRGB flycolor[COLORS];
///////////////////////////////////////////////////////////////////////////
//const int TM = 20;
//const int TN = 20;
#define TM 20
#define TN 20
int TERRAIN_TRIANGLES = 50;
typedef struct TERRAIN_POINT_T
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
}TERRAIN_POINT;
//TERRAIN_POINT* terrain;
TERRAIN_POINT terrain[TM+1][TN+1];
TERRAIN_POINT wall1[TM+1][TN+1];
TERRAIN_POINT wall2[TM+1][TN+1];
///////////////////////////////////////////////////////////////////////////////////
void SetTexture()        //�趨����
{   
//////////////////////////////////////////////////////////////////////////////////////////
	glShadeModel(GL_SMOOTH);
	_AUX_RGBImageRec *Image;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(50,ID); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		//�����Ĭ�ϵ����á�
	
	glBindTexture( GL_TEXTURE_2D, ID[0]); 
	Image = auxDIBImageLoadA("mushtop2.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[49]);
	Image = auxDIBImageLoadA("ground2.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[48]);
	Image = auxDIBImageLoadA("wall.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);
///////////////////////////////
	glBindTexture( GL_TEXTURE_2D, ID[47]);
	Image = auxDIBImageLoadA("Particle.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[6]);
	Image = auxDIBImageLoadA("mushmiddle.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[7]);
	Image = auxDIBImageLoadA("mushbottom.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[1]);
	Image = auxDIBImageLoadA("mushtop4.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[2]);
	Image = auxDIBImageLoadA("mushtop6.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	glBindTexture( GL_TEXTURE_2D, ID[3]);
	Image = auxDIBImageLoadA("mushtop9.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);

	
	/*glBindTexture( GL_TEXTURE_2D, ID[10]);
	Image = auxDIBImageLoadA("sky4.bmp");
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);*/
	for (int i=0; i<10; i++)
	{
		glBindTexture( GL_TEXTURE_2D, ID[10+i]);
		//std::string name = "sky/IMG000";
		std::string name = "sky100/";
		name += ('0'+ ((i+1)/10));
		name += ('0'+ ((i+1)%10));
		name +=".bmp";
		Image = auxDIBImageLoadA(name.c_str());
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);
	}

	for (int i=10; i<20; i++)
	{
		glBindTexture( GL_TEXTURE_2D, ID[10+i]);
		//std::string name = "sky/IMG000";
		std::string name = "sky100/";
		name += ('0'+ ((i-9)/10));
		name += ('0'+ ((i-9)%10));
		name +=".bmp";
		Image = auxDIBImageLoadA(name.c_str());
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Image->sizeX,Image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,Image->data);
	}
/////////////////////////////////////////////////////////////////////////////////
}


void SetFog()
{
	glEnable(GL_FOG);
	GLfloat fogColor[4] = {0.9,0.8,0.5,1.0};
	GLint fogMode = GL_EXP;
	glFogi(GL_FOG_MODE, fogMode);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.0001);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END,5.0f);
	glClearColor(0.9f,0.8f,0.5f,1.0f);
}
void SetLight()
{
	//���ù�Դ����

   //glEnable(GL_CULL_FACE);

//glLightModelf(GL_LIGHT_MODEL_AMBIENT,1);
//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,FALSE);

//�ö���õĹ�Դ���Ը�ָ����ԴGL_LIGHT0��������
glLightfv(GL_LIGHT0 , GL_AMBIENT , light_ambient);
glLightfv(GL_LIGHT0 , GL_DIFFUSE , light_diffuse);
glLightfv(GL_LIGHT0 , GL_POSITION , light_position);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,45.0f);	
//�������õĹ�ԴGL_LIGHT0	
glEnable(GL_LIGHT0);
}
void SetLightH()
{
	//���ù�Դ����

   //glEnable(GL_CULL_FACE);

//glLightModelf(GL_LIGHT_MODEL_AMBIENT,1);
//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,FALSE);

//�ö���õĹ�Դ���Ը�ָ����ԴGL_LIGHT1��������
glLightfv(GL_LIGHT1 , GL_AMBIENT , light_ambienth);
glLightfv(GL_LIGHT1 , GL_DIFFUSE , light_diffuseh);
glLightfv(GL_LIGHT1 , GL_POSITION , light_positionh);
glLightfv(GL_LIGHT1, GL_SPECULAR, light_specularh);
glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_directionh);
glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,25.0f);
//����˥��
glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5f);
glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.001f);
glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.f);
//�������õĹ�ԴGL_LIGHT1	
glEnable(GL_LIGHT1);
}

GLfloat bPoints[3][3] = 
{
	{0.0f,-23.5f,0.0f},{1.0f,-23.5f,0.0f},{-2.0f,-23.5f,1.0f}
};

void MakeShadowMatrix(GLfloat points[3][3], GLfloat lightPos[4], GLfloat destMat[4][4])
{
	GLfloat planeCoeff[4] = {0,1,0,1};
	GLfloat dot;
	planeCoeff[3] = -
	(
		(planeCoeff[0] * points[2][0])
			+ (planeCoeff[1]*points[2][1])
			+ (planeCoeff[2]*points[2][2])
	);
	dot = planeCoeff[0]*lightPos[0]
		+ planeCoeff[1]*lightPos[1]
		+ planeCoeff[2]*lightPos[2]
		+ planeCoeff[3]*lightPos[3];
	destMat[0][0] = dot - lightPos[0]*planeCoeff[0];
	destMat[1][0] = 0.0f - lightPos[0]*planeCoeff[1];
	destMat[2][0] = 0.0f - lightPos[0]*planeCoeff[2];
	destMat[3][0] = 0.0f - lightPos[0]*planeCoeff[3];
	
	destMat[0][1] = 0.0f - lightPos[2]*planeCoeff[0];
	destMat[1][1] = dot - lightPos[1]*planeCoeff[1];
	destMat[2][1] = 0.0f - lightPos[1]*planeCoeff[2];
	destMat[3][1] = 0.0f - lightPos[1]*planeCoeff[3];
	
	destMat[0][2] = 0.0f - lightPos[2]*planeCoeff[0];
	destMat[1][2] = 0.0f - lightPos[2]*planeCoeff[1];
	destMat[2][2] = dot - lightPos[2]*planeCoeff[2];
	destMat[3][2] = 0.0f - lightPos[2]*planeCoeff[3];

	destMat[0][3] = 0.0f - lightPos[3]*planeCoeff[0];
	destMat[1][3] = 0.0f - lightPos[3]*planeCoeff[1];
	destMat[2][3] = 0.0f - lightPos[3]*planeCoeff[2];
	destMat[3][3] = dot - lightPos[3]*planeCoeff[3];
}
// ������Ӱ����
void generate_shadow_matrix(GLfloat matrix[4][4], const GLfloat ground[4], const GLfloat light[4])
{
	GLfloat dot = 0;
	int i, j;
	for(i = 0; i < 4; i++)
		dot += ground[i] * light[i];
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(i == j)
				matrix[i][j] = dot - ground[i] * light[j];
			else
				matrix[i][j] = - ground[i] * light[j];
}
void TerrainInit(TERRAIN_POINT data[TM+1][TN+1], int xLength, int yLength,int no, float step)                          //������᫵ĵ���
{
	//terrain = new TERRAIN_POINT[TERRAIN_TRIANGLES];
	float cellx = 2*xLength/TM;
	float cellz = 2*yLength/TN;
	float* p1, *p2, *p3;
	for (int i=0;i<TM+1;i++)
	{
		for (int j=0;j<TN+1;j++)
		{
			data[i][j].x = cellx*i;
			data[i][j].y = float(rand()%no)*step;
			data[i][j].z = cellz*j;
			data[i][j].nx = 0.0f;
			data[i][j].ny = 0.0f;
			data[i][j].nz = 0.0f;
		}
	}
	/*for (int i=0;i<TM;i++)
	{
		for (int j=0;j<TN;j++)
		{
			p1 = (GLfloat*)&terrain[i][j];
			p2 = (GLfloat*)&terrain[i][j+1];
			p3 = (GLfloat*)&terrain[i+1][j];
			

			glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i][j+1]);
			glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i+1][j]);
			glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i+1][j+1]);
		}
	}*/
}
void MushroomInit()
{
	mushroom = new MUSHROOM[MAX_MUSHROOM];
	for (int i=0;i<MAX_MUSHROOM;i++)
	{
		mushroom[i].x = rand()%(2*(L-50))-(L-50);
		mushroom[i].y = rand()%30+5;
		mushroom[i].z = rand()%(2*(H-50))-(H-50);
		while ((-120.0f < mushroom[i].x) && (mushroom[i].x <120.0f)
			&& (-120.0f < mushroom[i].z) && (-120.0f < mushroom[i].z))
		{
			mushroom[i].x = rand()%(2*(L-50))-(L-50);
			mushroom[i].z = rand()%(2*(H-50))-(H-50);
		}
		mushroom[i].texT = rand()%4;
		mushroom[i].texM = 6;
		mushroom[i].texB = 7;
	}
}
void ParticleInit(void)
{
	for (int i=0;i<COLORS;i++)
	{
		flycolor[i].r = float(138 + rand()%(255-138))/256;
		flycolor[i].g = float(222 + rand()%(253-222))/256;
		flycolor[i].b = float(70 + rand()%(90-70))/256;
	}
	dstx = mushroom[1].x;
	dsty = mushroom[1].y;
	dstz = mushroom[1].z;
	for (int loop=0; loop<MAX_PARTICLES; ++loop)
	{
		particle[loop].life = LIFE;										// ����ÿ��������������
		particle[loop].fade = float(rand()%1000000)/1000000.0f;//+0.003f;			// �������˥���ٶ�
		particle[loop].r = flycolor[rand()%COLORS].r;							// ������ɫ�ĺ�ɫ����
		particle[loop].g = flycolor[rand()%COLORS].g;								// ������ɫ����ɫ����
		particle[loop].b = flycolor[rand()%COLORS].b;								// ������ɫ����ɫ����
		
		float Speed = float((rand()%300)-150.0f);	
		particle[loop].xSpeed = float((rand()%80)-40.0f);				// ��x�������ٶ�(-150,150)
		particle[loop].ySpeed = float((rand()%80)-40.0f);				// ��y�������ٶ�(-150,150)
		particle[loop].zSpeed = float((rand()%80)-40.0f);				// ��z�������ٶ�(-150,150)
		particle[loop].xg = 3.2f;										// ��x��ļ��ٶ�
		particle[loop].yg = 3.2f;										// ��y��ļ��ٶ�
		particle[loop].zg = 3.2f;										// ��z��ļ��ٶ�
		particle[loop].x = float(rand()%(2*(L-50)))-(L-50);				// ���ӵ���ʼλ��
		particle[loop].y = float(rand()%(130)) - 24;						// 
		particle[loop].z = float(rand()%(2*(L-50)))-(L-50);				//
	}
	//////////////////////////////
	/////////////////////////////
}
void Init()                    
{
   glDepthFunc(GL_LEQUAL);	
   glEnable(GL_DEPTH_TEST);
									// �����������ƽ����ʽ
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_BLEND);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glShadeModel(GL_SMOOTH);		
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   srand((unsigned)time(NULL));
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);		//����ȫ�ֻ�����
   SetTexture();
   SetFog();
   TerrainInit(terrain,L,H,50,0.5f);
   TerrainInit(wall1,L,WH,50,1.0f);
   TerrainInit(wall2,H,WH,50,1.0f);
   //SetLight();
   MushroomInit();
   ParticleInit();
   //MakeShadowMatrix(points, light_position, shadowMat);
  
   quadric = gluNewQuadric();	
   gluQuadricTexture(quadric, GLU_TRUE);								// ������������
   gluQuadricDrawStyle(quadric, GLU_FILL);	
   gluQuadricNormals(quadric,GLU_SMOOTH);
   glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
   // �������
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);
}
void Reshape(int width, int height)                   
{
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));				// ���õ�ǰ�ӿڴ�С
	glMatrixMode(GL_PROJECTION);										// �л���ͶӰ����ģʽ
	glLoadIdentity();													// ����ͶӰ����
	gluPerspective(45,(float)width/(float)height,0.1,10080);			// ����͸��ͶӰ
	glMatrixMode(GL_MODELVIEW);											// �л���ģ����ͼ����
	glLoadIdentity();													// ����ģ����ͼ����
	//SetLight();//glLightfv(GL_LIGHT0 , GL_POSITION , light_position);
}

void DrawBottom()			//�������κ�ǽ��
{	
		 glClear(GL_DEPTH_BUFFER_BIT);
///////////////////////////////////////////////////////////////////////////////////	
	   glEnable(GL_TEXTURE_2D);
		 //glDisable(GL_TEXTURE_2D);
	   glBindTexture(GL_TEXTURE_2D, ID[49]);
	   /*glBegin(GL_QUADS);
			  glNormal3f(0.0f,1.0f,0.0f);
              glTexCoord2f(0.0f, 0.0f);glVertex3f(-L, W,-H);
              glTexCoord2f(1.0f, 0.0f);glVertex3f(-L, W, H);
              glTexCoord2f(1.0f, 1.0f);glVertex3f( L, W, H);
              glTexCoord2f(0.0f, 1.0f);glVertex3f( L, W,-H);
	   glEnd();*/
	   glTranslatef(-L,0.0f,-H);
	   glBegin(GL_TRIANGLES);
			  glNormal3f(0.0f,1.0f,0.0f);
			  for (int i=0;i<TM;i++)
			  {
				  for (int j=0;j<TN;j++)
				  {
					glTexCoord2f(i*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i][j]);
					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i+1][j]);

					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i+1][j]);
					glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&terrain[i+1][j+1]);
				  }
			  }
	   glEnd();
	  
	   glTranslatef(L,0.0f,H);
///////////////////////////////////////////////////////////////////////////////
	  //��ǽ��
	   glBindTexture(GL_TEXTURE_2D, ID[48]);
	   /*glBegin(GL_QUADS);
			  glNormal3f(0.0f,0.0f,-1.0f);
              glTexCoord2f(0, 0);glVertex3f(-L,-W, H);
              glTexCoord2f(0, 1);glVertex3f( L,-W, H);
              glTexCoord2f(1, 1);glVertex3f( L, W+WH, H);
              glTexCoord2f(1, 0);glVertex3f(-L, W+WH, H);
	  glEnd();*/
	   glNormal3f(0.0f,1.0f,-1.0f);
	   glPushMatrix();
	   glTranslatef(L,0.0f,H);
	   //glRotatef(-90.0f,1.0f,0.0f,0.0f);
	   glRotatef(-180.0f,0.0f,1.0f,0.0f);
	   glRotatef(90.0f,1.0f,0.0f,0.0f);
	   glTranslatef(0.0f,0.0f,-WH);
	   glBegin(GL_TRIANGLES);
			  for (int i=0;i<TM;i++)
			  {
				  for (int j=0;j<TN;j++)
				  {
					glTexCoord2f(i*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j]);
					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j]);

					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j]);
					glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j+1]);
				  }
			  }
	   glEnd();
	   glPopMatrix();

	   glNormal3f(0.0f,0.0f,1.0f);
	   glPushMatrix();
	   glTranslatef(-L,0.0f,-H);	   
	   glRotatef(90.0f,1.0f,0.0f,0.0f);
	   glTranslatef(0.0f,0.0f,-WH);
	   glBegin(GL_TRIANGLES);
			  for (int i=0;i<TM;i++)
			  {
				  for (int j=0;j<TN;j++)
				  {
					glTexCoord2f(i*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j]);
					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j]);

					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j]);
					glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall1[i+1][j+1]);
				  }
			  }
	   glEnd();
	   glPopMatrix();
	  /*glBegin(GL_QUADS);    
			  glNormal3f(0.0f,0.0f,1.0f);
              glTexCoord2f(0, 0);glVertex3f(-L,-W, -H);
              glTexCoord2f(0, 1);glVertex3f( L,-W, -H);
              glTexCoord2f(1, 1);glVertex3f( L, W+WH, -H);
              glTexCoord2f(1, 0);glVertex3f(-L, W+WH, -H);
	  glEnd();*/
	   glNormal3f(-1.0f,0.0f,0.0f);
	  glPushMatrix();
	   glTranslatef(L,0.0f,-H);	  
	   glRotatef(-90.0f,0.0f,1.0f,0.0f);
	   glRotatef(90.0f,1.0f,0.0f,0.0f);
	   glTranslatef(0.0f,0.0f,-WH);
	   glBegin(GL_TRIANGLES);
			  for (int i=0;i<TM;i++)
			  {
				  for (int j=0;j<TN;j++)
				  {
					glTexCoord2f(i*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j]);
					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j]);

					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j]);
					glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j+1]);
				  }
			  }
	   glEnd();
	   glPopMatrix();

	  /*glBegin(GL_QUADS);
			  glNormal3f(-1.0f,0.0f,0.0f);
              glTexCoord2f(0, 0);glVertex3f( L,-W, -H);
              glTexCoord2f(0, 1);glVertex3f( L,-W, H);
              glTexCoord2f(1, 1);glVertex3f( L, W+WH, H);
              glTexCoord2f(1, 0);glVertex3f( L, W+WH, -H);
	  glEnd();*/
	   glNormal3f(1.0f,0.0f,0.0f);
	   glPushMatrix();
	   glTranslatef(-L,0.0f,H);	  
	   glRotatef(90.0f,0.0f,1.0f,0.0f);
	   glRotatef(90.0f,1.0f,0.0f,0.0f);
	   glTranslatef(0.0f,0.0f,-WH);
	   glBegin(GL_TRIANGLES);
			  for (int i=0;i<TM;i++)
			  {
				  for (int j=0;j<TN;j++)
				  {
					glTexCoord2f(i*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j]);
					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j]);

					glTexCoord2f(i*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i][j+1]);
					glTexCoord2f((i+1)*1.0f/TM, j*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j]);
					glTexCoord2f((i+1)*1.0f/TM, (j+1)*1.0f/TN);glVertex3fv((GLfloat*)&wall2[i+1][j+1]);
				  }
			  }
	   glEnd();
	   glPopMatrix();
	  /*glBegin(GL_QUADS); 
			  glNormal3f(1.0f,0.0f,0.0f);
              glTexCoord2f(0, 0);glVertex3f( -L,-W, -H);
              glTexCoord2f(0, 1);glVertex3f( -L,-W, H);
              glTexCoord2f(1, 1);glVertex3f( -L, W+WH, H);
              glTexCoord2f(1, 0);glVertex3f( -L, W+WH, -H);
	  glEnd();*/
//////////////////////////////////////////////////////////////////////////
}
void DrawSky()
{
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	switch ((timestate/16)%20)
	{
	case 0:
		glBindTexture(GL_TEXTURE_2D,ID[10]);
	case 1:
		glBindTexture(GL_TEXTURE_2D,ID[11]);
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D,ID[12]);
		break;
	case 3:
		glBindTexture(GL_TEXTURE_2D,ID[13]);
		break;
	case 4:
		glBindTexture(GL_TEXTURE_2D,ID[14]);
		break;
	case 5:
		glBindTexture(GL_TEXTURE_2D,ID[15]);
		break;
	case 6:
		glBindTexture(GL_TEXTURE_2D,ID[16]);
		break;
	case 7:
		glBindTexture(GL_TEXTURE_2D,ID[17]);
		break;
	case 8:
		glBindTexture(GL_TEXTURE_2D,ID[18]);
		break;
	case 9:
		glBindTexture(GL_TEXTURE_2D,ID[19]);
		break;
	case 10:
		glBindTexture(GL_TEXTURE_2D,ID[20]);
		break;
	case 11:
		glBindTexture(GL_TEXTURE_2D,ID[21]);
		break;
		case 12:
		glBindTexture(GL_TEXTURE_2D,ID[22]);
		break;
		case 13:
		glBindTexture(GL_TEXTURE_2D,ID[23]);
		break;
		case 14:
		glBindTexture(GL_TEXTURE_2D,ID[24]);
		break;
		case 15:
		glBindTexture(GL_TEXTURE_2D,ID[25]);
		break;
		case 16:
		glBindTexture(GL_TEXTURE_2D,ID[26]);
		break;
		case 17:
		glBindTexture(GL_TEXTURE_2D,ID[27]);
		break;
		case 18:
		glBindTexture(GL_TEXTURE_2D,ID[28]);
		break;
		case 19:
		glBindTexture(GL_TEXTURE_2D,ID[29]);
		break;
	default:
		glBindTexture(GL_TEXTURE_2D,ID[10]);
		break;
	}
	glRotatef(180,1.0f,0.0f,0.0f);

	/*glBegin(GL_QUADS);
              glTexCoord2f(0, 0);glVertex3f(-L, W,-H);
              glTexCoord2f(35, 0);glVertex3f(-L, W, H);
              glTexCoord2f(35, 35);glVertex3f( L, W, H);
              glTexCoord2f(0, 35);glVertex3f( L, W,-H);
	  glEnd();*/
	gluSphere(quadric,SR,32,32);
	//glEnable(GL_LIGHTING);	
}
void DrawMoon()
{
	glDisable(GL_TEXTURE_2D);
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission1);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess1);
	glTranslatef(500.0f,2000.0f,50.0f);
	gluSphere(quadric,100.0f,32,32);
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);
}
void drawCube(float l, float w, float h)          //����һ��������
{
	glBegin(GL_QUADS);
	glVertex3f(-l*0.5,+0.5*w,+0.5*h);
	glVertex3f(-l*0.5,+0.5*w,-0.5*h);
	glVertex3f(-l*0.5,-0.5*w,-0.5*h);
	glVertex3f(-l*0.5,-0.5*w,+0.5*h);

	glVertex3f(-l*0.5,+0.5*w,-0.5*h);
	glVertex3f(+l*0.5,+0.5*w,-0.5*h);
	glVertex3f(+l*0.5,-0.5*w,-0.5*h);
	glVertex3f(-l*0.5,-0.5*w,-0.5*h);

	glVertex3f(+l*0.5,+0.5*w,-0.5*h);
	glVertex3f(+l*0.5,+0.5*w,+0.5*h);
	glVertex3f(+l*0.5,-0.5*w,+0.5*h);
	glVertex3f(+l*0.5,-0.5*w,-0.5*h);

	glVertex3f(+l*0.5,+0.5*w,+0.5*h);
	glVertex3f(-l*0.5,+0.5*w,+0.5*h);
	glVertex3f(-l*0.5,-0.5*w,+0.5*h);
	glVertex3f(+l*0.5,-0.5*w,+0.5*h);

	glVertex3f(+l*0.5,+0.5*w,-0.5*h);
	glVertex3f(-l*0.5,+0.5*w,-0.5*h);
	glVertex3f(-l*0.5,+0.5*w,+0.5*h);
	glVertex3f(+l*0.5,+0.5*w,+0.5*h);

	glVertex3f(+l*0.5,-0.5*w,+0.5*h);
	glVertex3f(+l*0.5,-0.5*w,-0.5*h);
	glVertex3f(-l*0.5,-0.5*w,-0.5*h);
	glVertex3f(-l*0.5,-0.5*w,+0.5*h);
	glEnd();
}
void DrawBubble()
{
	float br = 20.0f;
	float move = 10.0f;
	glDisable(GL_TEXTURE_2D);
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission1);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess1);
	glTranslatef(br+move,200.0f,br+move);
	gluSphere(quadric,br,32,32);
	glTranslatef(0.0f,0.0f,-2*(br+move));
	gluSphere(quadric,br,32,32);
	glTranslatef(-2*(br+move),0.0f,0.0f);
	gluSphere(quadric,br,32,32);
	glTranslatef(0.0f,0.0f,2*(br+move));
	gluSphere(quadric,br,32,32);
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular3);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission3);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess3);
	 glTranslatef(br+move,0.0f,-(br+move));
	 float q2 = sqrt(2.0f);
	 glPushMatrix();
	 glRotatef(45.0f,0.0f,1.0f,0.0f);
	 drawCube(2*q2*(br+move),6.0f,6.0f);
	 glRotatef(90.0f,0.0f,1.0f,0.0f);
	 drawCube(2*q2*(br+move),6.0f,6.0f);
	 glPopMatrix();
	 glTranslatef(0.0f,-100.0f,0.0f);
	 drawCube(12.0f,260.0f,12.0f);
     
	 glTranslatef(0.0f,-124.0f,0.0f);
	 glRotatef(-90.0f,1.0f,0.0f,0.0f);
     gluCylinder(quadric,100.0f,60.0f,40.0f,32,32);
	 glTranslatef(0.0f,0.0f,40.0f);
	 gluDisk(quadric,0.0f,60.0f,32,32);
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);
}
GLfloat		angle;
void DrawMushroom(float x, float y, float z, int iTexTop, int iTexMiddle, int iTexBottom)
{
	glTranslatef(0,-24,0);
	float factor = float(y+24)/20;
	glTranslatef(x,10*factor,z);

	//glRotatef(((rand()%1)-1)*4*timestate,0.0f,1.0f,0.0f);
	
	glScalef(factor,factor,factor);
	
	glBindTexture(GL_TEXTURE_2D, ID[iTexTop]);
	float q3 = 1.73205080;
	float r = 3*q3;
	float R = 4*q3+4/q3;
	float h = 3 + 4;
	float q5 = 2.23606798;
	glRotatef(-90,1.0f,0.0f,0.0f);
	gluCylinder(quadric, R, r, h, 32, 32);
	glTranslatef(0,0,4);
	gluSphere(quadric,6,32,32);
	
	glBindTexture(GL_TEXTURE_2D, ID[iTexMiddle]);
	glTranslatef(0,0,-4);
	gluQuadricOrientation(quadric,GLU_INSIDE);
	gluDisk(quadric,R - 2*q5-0.3,R,32,32);
	gluQuadricOrientation(quadric,GLU_OUTSIDE);

	glBindTexture(GL_TEXTURE_2D, ID[iTexBottom]);
	glTranslatef(0,0,-8);
	gluCylinder(quadric, 2*q5-0.5, 2*q5, 8,32,32);
	gluSphere(quadric,2*q5-0.5,32,32);
}

void DrawParticle()
{
	if (timestate/850 != timesection)
	{
		int i = rand()%MAX_MUSHROOM;
		dstx = mushroom[i].x;
		dsty = mushroom[i].y;
		dstz = mushroom[i].z;
		timesection = timestate/850;
	}
	glBindTexture(GL_TEXTURE_2D,ID[47]);
	glPointSize(5.5f);

	glDisable(GL_LIGHTING);	
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);					//���ư�͸�����壬����Ȼ�������Ϊֻ��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_ONE, GL_ONE);
							// ѡ���Ϸ�ʽ
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	float x,y,z;
	//glBegin(GL_POINTS);	
	for (int loop=0; loop<MAX_PARTICLES; ++loop)						// ѭ������
	{
		x = particle[loop].x;											// ������������
		y = particle[loop].y;
		z = particle[loop].z;

		// ��glColor4f�������ӵ���ɫ��͸����(����),��life��fade���ɵõ����ӵ������仯
		glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);
		/*emission2[0] = particle[loop].r;
		emission2[1] = particle[loop].g;
		emission2[2] = particle[loop].b;
		ambient2[0] = particle[loop].r;
		ambient2[1] = particle[loop].g;
		ambient2[2] = particle[loop].b;
		diffuse2[0] = particle[loop].r;
		diffuse2[1] = particle[loop].g;
		diffuse2[2] = particle[loop].b;
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission2);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess2);*/
		//glTranslatef(x,y,z);
		//gluSphere(quadric,0.5f,32,32);
		float theta = float(rand()%360)*180/3.1415926;
		float theta2 = float(rand()%360)*180/3.1415926;
					// ��������
			glBegin(GL_QUADS);
		    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + PR*cos(theta)*cos(theta2), y + PR*sin(theta)*cos(theta2), z+PR*sin(theta2));
			glTexCoord2d(0.0f, 1.0f); glVertex3f(x - PR*cos(theta)*cos(theta2), y + PR*sin(theta)*cos(theta2), z-PR*sin(theta2));
			glTexCoord2d(0.0f, 0.0f); glVertex3f(x + PR*cos(theta)*cos(theta2), y - PR*sin(theta)*cos(theta2), z-PR*sin(theta2));
			glTexCoord2d(1.0f, 0.0f); glVertex3f(x - PR*cos(theta)*cos(theta2), y - PR*sin(theta)*cos(theta2), z+PR*sin(theta2));
			glEnd();	
			/*glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f);glVertex3f(x-PR,y+PR,z+PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x-PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x-PR,y-PR,z-PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x-PR,y-PR,z+PR);

			glTexCoord2f(1.0f, 1.0f);glVertex3f(x-PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x+PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x+PR,y-PR,z-PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x-PR,y-PR,z-PR);
			
			glTexCoord2f(1.0f, 1.0f);glVertex3f(x+PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x+PR,y+PR,z+PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x+PR,y-PR,z+PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x+PR,y-PR,z-PR);

			glTexCoord2f(1.0f, 1.0f);glVertex3f(x+PR,y+PR,z+PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x-PR,y+PR,z+PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x-PR,y-PR,z+PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x+PR,y-PR,z+PR);

			glTexCoord2f(1.0f, 1.0f);glVertex3f(x+PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x-PR,y+PR,z-PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x-PR,y+PR,z+PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x+PR,y+PR,z+PR);

			glTexCoord2f(1.0f, 1.0f);glVertex3f(x+PR,y-PR,z+PR);
			glTexCoord2d(0.0f, 1.0f);glVertex3f(x+PR,y-PR,z-PR);
			glTexCoord2d(0.0f, 0.0f);glVertex3f(x-PR,y-PR,z-PR);
			glTexCoord2d(1.0f, 0.0f);glVertex3f(x-PR,y-PR,z+PR);
			glEnd();*/
		//glVertex3f(x,y,z);
		//glEnd();
		float dirx = dstx - particle[loop].x;
		float diry = dsty - particle[loop].y;
		float dirz = dstz - particle[loop].z;
		float r = sqrt(dirx*dirx + diry*diry + dirz*dirz);
		dirx = 5*dirx/r;
		diry = 5*diry/r;
		dirz = 5*dirz/r;

		bool nearx = ((-12.0<(dirx-x)) && ((dirx-x)<12.0f));
		bool neary = ((-12.0<(diry-y)) && ((diry-y)<12.0f));
		bool nearz = ((-12.0<(dirz-z)) && ((dirz-z)<12.0f));
		// ����λ�ø���
		if (nearx && neary && nearz)
		;
		else
		{
			/*if (rand()%32 == 0)
			{
				particle[loop].x +=  float(rand()%200)-100;
				particle[loop].y += float(rand()%200)-100;
				particle[loop].z += float(rand()%200)-100;
			}
			else*/
			{
				particle[loop].x += particle[loop].xSpeed/(speedFator*1000.0f);	// x���ϵ�λ��
				particle[loop].y += particle[loop].ySpeed/(speedFator*1000.0f);	// y���ϵ�λ��
				particle[loop].z += particle[loop].zSpeed/(speedFator*1000.0f);	// z���ϵ�λ��
			}
		}
		// �����ٶȸ���
		particle[loop].xSpeed += particle[loop].xg*dirx;
		particle[loop].ySpeed += particle[loop].yg*diry;
		particle[loop].zSpeed += particle[loop].zg*dirz;
		if (   (particle[loop].xSpeed > MaxSpeed) 
			|| (particle[loop].ySpeed > MaxSpeed) 
			|| (particle[loop].zSpeed > MaxSpeed) 
			|| (particle[loop].xSpeed < -MaxSpeed)
			|| (particle[loop].ySpeed < -MaxSpeed) 
			|| (particle[loop].zSpeed < -MaxSpeed))
		{
			particle[loop].xSpeed = MaxSpeed * dirx/5;
			particle[loop].ySpeed = MaxSpeed * diry/5;
			particle[loop].zSpeed = MaxSpeed * dirz/5;
		}
		particle[loop].life -= particle[loop].fade;						// ����������˥��

		if (particle[loop].life <= 0.0f)								// �������˥����0
		{
			particle[loop].life = LIFE;									// ����������
			particle[loop].fade = float(rand()%1000000)/1000000.0f;//+0.003f;		// ���˥���ٶ�
			particle[loop].x = float(rand()%(2*(L-50)))-(L-50);									// ��������(0.0f,0,0f,0.0f)��
			particle[loop].y = float(rand()%(130)) - 24;
			particle[loop].z = float(rand()%(2*(L-50)))-(L-50);
			float Speed = float((rand()%300)-150.0f);	
			particle[loop].xSpeed = float((rand()%80)-40.0f);			// x���ٶ��뷽��
			particle[loop].ySpeed = float((rand()%80)-40.0f);			// y���ٶ��뷽��
			particle[loop].zSpeed = float((rand()%80)-40.0f);		// z���ٶ��뷽��
			particle[loop].r = flycolor[rand()%COLORS].r;			// ѡ�������ɫ��(r,g,b)ֵ
			particle[loop].g = flycolor[rand()%COLORS].g;		
			particle[loop].b = flycolor[rand()%COLORS].b;	
		}
	}
		 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);
	//glEnd();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);	
}
void Display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// �����ɫ����Ȼ���
	glLoadIdentity();
	gluLookAt(eyePX, eyePY,eyePZ,viewDX, viewDY, viewDZ, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
/////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	/*light_position[] = { 0.0f, 50.0f , 0.0f, 1.0f };
	SetLight();
	light_position[] = { 0.0f, 50.0f , 0.0f, 1.0f };
	SetLight();
	light_position[] = { 0.0f, 50.0f , 0.0f, 1.0f };*/
	SetLight();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	if (SPOT_LIGHT_ON == 1)
	SetLightH();
	else
	glDisable(GL_LIGHT1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,-24,0);
	DrawBottom();          //�����ײ��ذ壻�����õģ���ע�͵����Ժ����á�
		 /*glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);*/
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D,ID[10]);
	glPushMatrix();
	DrawSky();
	glPopMatrix();

	glPushMatrix();
	/*glTranslatef(20.0f,0.0f,200.0f);
	DrawBubble();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-330.0f,0.0f,270.0f);
	DrawBubble();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(420.0f,0.0f,-200.0f);*/
	DrawBubble();
	glPopMatrix();

	glPushMatrix();
	DrawMoon();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_TEXTURE_2D);
	for (int i=0;i<MAX_MUSHROOM;i++)
	{
		glPushMatrix();
		//glScalef(1.0f,0.5f,0.5f);
		//glTranslatef(0.0f,5.0*cos(float(timestate*0.05)) + 5.0f,0.0f);
		DrawMushroom(mushroom[i].x, mushroom[i].y, mushroom[i].z, mushroom[i].texT,mushroom[i].texM,mushroom[i].texB);
		glPopMatrix();

			//glPushMatrix();
			//glMatrixMode(GL_MODELVIEW);
			////glLoadIdentity();
			//glDisable(GL_LIGHTING);										// �رչ�Դ
			//glDisable(GL_TEXTURE_2D);									// ��������
			//glColor3f(0.0f, 0.0f, 0.0f);								// ������Ӱ��ɫ
			//MakeShadowMatrix(bPoints,light_position,shadowMat);
			////generate_shadow_matrix(shadowMat,P,light_position);
			//glMultMatrixf((GLfloat*) shadowMat);
			////glTranslatef(0.0f,24.0f,0.0f);
			//DrawMushroom(mushroom[i].x, mushroom[i].y, mushroom[i].z, mushroom[i].texT,mushroom[i].texM,mushroom[i].texB);
			//glEnable(GL_LIGHTING);										// �رչ�Դ
			//glEnable(GL_TEXTURE_2D);
			//glPopMatrix();
	}
///////////////////////////////////////////////////////////////////////////////////////////
	glPushMatrix();
		 /*glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
         glMaterialfv(GL_FRONT, GL_EMISSION, emission);
         glMaterialf (GL_FRONT, GL_SHININESS, shininess);*/
	DrawParticle();
	glPopMatrix();
////////////////////////////////////////////////////////////////////////////////////////////
	timestate++;
	glutSwapBuffers();   

}
void Timer(int time)
{
	//timestate +=100;
	//Display2();
	//glutPostRedisplay();
	//glutTimerFunc(FRAME_MILLI_SECONDS,Timer,1);
}
void idle()
{
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);            
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);         
   glutInitWindowSize(Window_Width, Window_Height);             
   glutInitWindowPosition(0, 0);        
   glutCreateWindow(argv[0]);          
 
   Init();
   SetCursorPos(Window_Width/2, Window_Height/2);
   SetCamera(0,0);
   glutReshapeFunc(Reshape);
   //glutDisplayFunc(Display);
   glutDisplayFunc(Display2);
   
   glutIdleFunc(idle);
   
   glutKeyboardFunc(Keyboard);			//����
   glutKeyboardUpFunc(UpKeyboard);		//�ͷ�

   glutSpecialFunc(SpecialKeyboard);			//����
   glutSpecialUpFunc(SpecialUpKeyboard);		//�ͷ�
   glutMouseFunc(Mouse);						//��굥��

   glutPassiveMotionFunc(MouseMove);			//����ƶ�
   glutMotionFunc(OnMouseMove);					//��갴ס�ƶ�
   //PlaySoundA(LPCSTR("Data/music.wav"), NULL, SND_FILENAME|SND_ASYNC|SND_LOOP);//��������
   //glutTimerFunc(FRAME_MILLI_SECONDS,Timer,1);
   glutMainLoop();             
   return 0;
}