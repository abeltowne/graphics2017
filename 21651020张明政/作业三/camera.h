#ifndef CAMERA_H
#define CAMERA_H
/////////////////////////////////////////////////////////////////////
///////////�趨��ת������������ɹ���꽻��ʽ���.///////////////////
struct mPOINT                     
{
       int x;
       int y;
};
 
struct CAMERA                  
{
       GLfloat xeye;
       GLfloat yeye;
       GLfloat zeye;
};
 
struct POLAR              
{
       float r;                  
       float alpha;                   
       float fy;                
};
void OnMouseMove(int x, int y);
void SetCamera(GLfloat x, GLfloat y);
void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);

void Keyboard(unsigned char key,int x,int y);
void Keyboard(unsigned char key, int x, int y);
void UpKeyboard(unsigned char key, int x ,int y);

void SpecialKeyboard(int key,int x,int y);
void SpecialUpKeyboard(int key,int x,int y);
////////////////////////////////////////////////////////////////////////////////////
#endif