// g++ main.cpp float2.cpp -lGL -lGLU -lglut -std=c++11

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// Needed on MsWindows
#include <windows.h>
#endif // Win32 platform
 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "float2.h" 
#include "BezierCurve.h" 
#include "LagrangeCurve.h" 
#include "Polyline.h" 
#include "CatmullRomSpline.h" 


using namespace std;

int windowWidth = 640;
int windowHeight = 480;

float2 mouseV = float2();

const char NONE = -1;
const char POLYLINE = 'p';
const char LAGRANGE = 'l';
const char BEZIER = 'b';
const char CATMULLROM = 'r';
const char APPEND = 'a';
const char MOVE = -2;

bool F = false;

string MODES ("plbr");

char mode = NONE;

Freeform *sf;

vector<Freeform *> freeforms;

//--------------------------------------------------------
// Display callback that is responsible for updating the screen
//--------------------------------------------------------
void onDisplay( ) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);        	// clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen

	for(Freeform* &f : freeforms){
		f->drawFreeform(f==sf, F&f==sf);
		f->drawControlPoints(f==sf);
	}
	glutSwapBuffers(); // Swap buffers for double buffering
	glutPostRedisplay();
}

void onReshape(int winWidth0, int winHeight0)
{
	glViewport(0, 0, winWidth0, winHeight0);
	
	glLoadIdentity();
	
	// Reset the window coordinates to match pixels so that the mouse 
	// coordinates map directly to the screen.
	gluOrtho2D(0, windowWidth, 0, windowHeight); 
} 

void onKeyboard(unsigned char c, int x, int y)
{
	if(MODES.find(c)+1>0){
		mode = c;
		sf = NULL;
	}
	else if(sf != NULL && mode == NONE && c == APPEND) {
		mode = APPEND;
	} 
	else if(c=='f'){
		F = true;
	} 
	else if(c==27){
		// Quit the program when the escape key is pressed
		exit(0);
	}
}

void onKeyboardUp(unsigned char c, int x, int y)
{
	if(mode==c){
		mode = NONE;
	}
	if(c=='f'){
		F = false;
	}
}

// I chose to implement OpenGL selection mode to find out which object the cursor is pointing at
int getSelected(int x, int y){
	const int BUFSIZE = 512;
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    glGetIntegerv (GL_VIEWPORT, viewport);

    glSelectBuffer(BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(0);
    int c = 0;

    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix ((GLdouble) x, (GLdouble) (windowHeight - y), 
                  5.0, 5.0, viewport);
	gluOrtho2D(0, windowWidth, 0, windowHeight);
 	for(Freeform* &f : freeforms){
		glLoadName(c);
		c++;
		f->drawFreeform(f==sf, F);
		f->drawControlPoints(f==sf);
	}
	glPopMatrix();
	glFlush();
    hits = glRenderMode(GL_RENDER);

   	if(mode == NONE){
 	   	sf = NULL;
   	}
    glutPostRedisplay();

    if(hits > 0 && mode == NONE){
	   	GLuint *ptr = (GLuint *) selectBuf+3;
	   	return *ptr;
    }
    return -1;
}

void onMouse(int button, int state, int x, int y)
{
	mouseV = float2(x, windowHeight - y);

	if(state == GLUT_DOWN){
		if(button == GLUT_LEFT_BUTTON) {
			if(mode == NONE){
				sf = NULL;
				int selected = getSelected(x, y);
		    	if(selected>-1){
			    	sf = freeforms[selected];
			    	mode = MOVE;
			    }
			} else {
				if(sf == NULL){
					Freeform *f;
					switch(mode){
					case POLYLINE:
						f = new Polyline();
						break;
					case LAGRANGE:
						f = new LagrangeCurve();
						break;
					case BEZIER:
						f = new BezierCurve();
						break;
					case CATMULLROM:
						f = new CatmullRomSpline();
						break;
					default:
						break;
					}
					freeforms.push_back(f);
					sf = f;
				}
				sf->addControlPoint(mouseV);
			}
		}
	} else if (state == GLUT_UP) {
		if(button == GLUT_LEFT_BUTTON) {
			if(mode == MOVE){
				mode = NONE;
			}
		}
	}
}

void onMouseMotion(int x, int y)
{
	float2 newMouseV = float2(x,windowHeight-y);

	if(sf && mode == MOVE){
		sf->offset+=(newMouseV-mouseV);
	}

	mouseV = newMouseV;
}

//--------------------------------------------------------
// The entry point of the application 
//--------------------------------------------------------
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);                 		// GLUT initialization
    glutInitWindowSize(windowWidth, windowHeight);				// Initial resolution of the MsWindows Window is 600x600 pixels 
    glutInitWindowPosition(100, 100);           // Initial location of the MsWindows window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);    // Image = 8 bit R,G,B + double buffer + depth buffer
 
    glutCreateWindow("Curve Editor");        	// Window is born
  
    glutDisplayFunc(onDisplay);                	// Register event handlers
    
	glutReshapeFunc(onReshape);
    
	glutKeyboardFunc(onKeyboard);
	glutKeyboardUpFunc(onKeyboardUp);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // Disables automatic key repeat on Linux

	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMotion);

    glutMainLoop();                    			// Event loop  
    return 0;
}
