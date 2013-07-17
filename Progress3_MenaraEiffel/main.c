#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#define ESCAPE 27
#include "eiffel.txt"
#include "lampu.txt"
#include "pohon.txt"
#include "tanggataman.txt"
#include "pagar.txt"
#include "bonekasalju.txt"

/* Here we will put variables which we wish to be global */
GLint window;           /* The number of our GLUT window */
GLint Xsize=400;
GLint Ysize=400;

GLfloat xt=0.0,yt=0.0,zt=0.0;   /* x,y,z translation */
GLfloat xs=1.0,ys=1.0,zs=1.0;   /* x,y,z scale */
GLfloat xangle=0.0,yangle=0.0,zangle=0.0;   /* axis angles */

//Kamera Mouse Move
double camera_angle_h = 0;
double camera_angle_v = 0;
int drag_x_origin;
int drag_y_origin;
int dragging = 0;

GLfloat sizes[2];       /* Store supported point size range */
GLfloat step;           /* Store supported point size increments */

GLvoid Transform(GLfloat Width, GLfloat Height)
{
  glViewport(0, 0, Width, Height);              /* Set the viewport */
  glMatrixMode(GL_PROJECTION);                  /* Select the projection matrix */
  glLoadIdentity();				/* Reset The Projection Matrix */
  gluPerspective(45.0,Width/Height,0.1,100.0);  /* Calculate The Aspect Ratio Of The Window */
  glMatrixMode(GL_MODELVIEW);                   /* Switch back to the modelview matrix */
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLfloat Width, GLfloat Height)	
{
  glClearColor(0.75, 0.75, 0.75, 0.0);		/* This Will Clear The Background Colour To Black */
  glPointSize(4.0);                             /* Add point size, to make it clear */
  glLineWidth(2.0);                             /* Add line width,   ditto */
  glShadeModel(GL_SMOOTH);                      /* Set the color model */
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  Transform( Width, Height );                   /* Perform the transformation */
}

/* The function called when our window is resized  */
GLvoid ReSizeGLScene(GLint Width, GLint Height)
{
  if (Height==0)    Height=1;                   /* Sanity checks */
  if (Width ==0)    Width=1;
  Transform( Width , Height );                   /* Perform the transformation */
}

//Fungsi untuk menampilkan pada layar
GLvoid DrawGLScene()
{
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	/* Clear screen, depth Buffer */
  /*koding eiffel*/
  glLoadIdentity();
  //set Kamera 
  gluLookAt(0.0, 35.0, 35.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glRotated(camera_angle_v, 1.0, 0.0, 0.0);
  glRotated(camera_angle_h, 0.0, 1.0, 0.0);
  // garis bantu koordinat
  glColor3f(0.0,1.0,0.0); 
  /*glBegin(GL_LINES);
   glVertex3f(0.0,-10.0,0.0);
   glVertex3f(0.0,10.0,0.0);
   glVertex3f(-10.0,0.0,0.0);
   glVertex3f(10.0,0.0,0.0);
   glVertex3f(0.0,0.0,-10.0);
   glVertex3f(0.0,0.0,10.0);
  glEnd();*/
  //Memanggil fugsi eiffel
  glPushMatrix();
   eiffel();
  glPopMatrix();  
  glPushMatrix();
   glTranslatef(-5.0,0.0,0.0);
   lampujalan();
  glPopMatrix();
  glPushMatrix();
   glTranslatef(-7.0,0.0,0.0);
   lamputaman();
  glPopMatrix();
  glPushMatrix();
   glTranslatef(7.0,0.0,0.0);
   pohon();
  glPopMatrix();
  glPushMatrix();
   glTranslatef(0.0,0.0,5.0);
   glScalef(0.25,0.25,0.25);
   pagartanggataman();
   tanggataman();
  glPopMatrix();
  glPushMatrix();
   glTranslatef(0.0,0.0,-5.0);
   glScalef(0.15,0.15,0.15);
   pagar();
  glPopMatrix();
  glPushMatrix();
   glTranslatef(13.0,0.0,0.0);
   glScalef(2.0,2.0,2.0);
   bonekasalju();
  glPopMatrix();
  glFlush(); 
  printf("drawing called\n");
}

void NormalKey(GLubyte key, GLint x, GLint y) 
{
    switch ( key )    { 
     case ESCAPE :
        printf("escape pressed. exit.\n");
	    glutDestroyWindow(window);	/* Kill our window */
	    exit(0); 			/* Very dirty exit */                  
        break;
      case 'b':
        glEnable(GL_BLEND);
        glutPostRedisplay();
        break;
     case 'B':
        glDisable(GL_BLEND);
        glutPostRedisplay();
        break;				/* Do we need this??? */
     case 'P':
     case 'p':
        glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
        glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
        printf("Point size ranges from %f to %f at %f steps.\n",
               sizes[0],sizes[1],step);
        break;
     case 'W':
     case 'w':                          /* Tell us about the window */
        printf("Current window size is %d x %d pixels in %s mode\n",
               glutGet(GLUT_WINDOW_WIDTH),
               glutGet(GLUT_WINDOW_HEIGHT),
               glutGet(GLUT_WINDOW_DOUBLEBUFFER) ? "double buffer" :
                                                   "single buffer");
        break;
     case 'x':                          /* Move to right */
        xt += 0.2;
        glutPostRedisplay();
        break;
     case 'X':
        xt -= 0.2;                      /* Move to left */
        glutPostRedisplay();
        break;

      case 'y':                          /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;
     case 'Y':
        yt -= 0.2;                      /* Move down */
        glutPostRedisplay();
        break;
      case 'z':                          /* Move forward */
        zt += 0.2;
        glutPostRedisplay();
        break;
     case 'Z':
        zt -= 0.2;                      /* Move away */
        glutPostRedisplay();
        break;
     case 'j':                          /* scale x up */
        xs += 0.2;
        glutPostRedisplay();
        break;
     case 'J':
        xs -= 0.2;                      /* scale x down */
        glutPostRedisplay();
        break;
      case 'k':                          /* scale y up */
        ys += 0.2;
        glutPostRedisplay();
        break;
     case 'K':
        ys -= 0.2;                      /* scale y down */
        glutPostRedisplay();
        break;
      case 'l':                          /* scale z up */
        zs += 0.2;
        glutPostRedisplay();
        break;
     case 'L':
        zs -= 0.2;                      /* scale z down */
        glutPostRedisplay();
        break;
     case 'u':
        xangle += 5.0;
        glutPostRedisplay();
        break;
     case 'U':
        xangle -= 5.0;
        glutPostRedisplay();
        break;
     case 'i':
        yangle += 5.0;
        glutPostRedisplay();
        break;
     case 'I':
        yangle -= 5.0;
        glutPostRedisplay();
        break;
     case 'o':
        zangle += 5.0;
        glutPostRedisplay();
        break;
     case 'O':
        zangle -= 5.0;
        glutPostRedisplay();
        break;
     default:
	    break;
    }
}

void mouse_click(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            dragging = 1;
            drag_x_origin = x;
            drag_y_origin = y;
        }
        else
            dragging = 0;
    }
}

void mouse_move(int x, int y) {
    if(dragging) {
        camera_angle_v += (y - drag_y_origin)*0.3;
        camera_angle_h += (x - drag_x_origin)*0.3;
        drag_x_origin = x;
        drag_y_origin = y;
    }
}

int main(int argc, char *argv[])
{
  /* Initialisation and window creation */
  glutInit(&argc, argv);               /* Initialize GLUT state. */

  glutInitDisplayMode(GLUT_RGBA |      /* RGB and Alpha */
                      GLUT_SINGLE|     /* Single buffer */
                      GLUT_DEPTH);     /* Z buffer (depth) */

  glutInitWindowSize(400,400);         /* set initial window size. */
  glutInitWindowPosition(0,0);         /* upper left corner of the screen. */
  window = glutCreateWindow("Grafika Komputer-Kelompok 8-IF 8");     /* Open a window with a title. */ 
  InitGL(400,400);                     /* Initialize our window. */
/* Now register the various callback functions */
  glutDisplayFunc(DrawGLScene);        /* Function to do all our OpenGL drawing. */
  glutReshapeFunc(ReSizeGLScene);
  glutIdleFunc(DrawGLScene);
  glutMouseFunc(mouse_click);
  glutMotionFunc(mouse_move);
  glutKeyboardFunc(NormalKey);         /*Normal key is pressed */
  
  glEnable(GL_DEPTH_TEST);
/* Now drop into the event loop from which we never return */
  glutMainLoop();                      /* Start Event Processing Engine. */ 
   return 1;
   
   
  /*system("PAUSE");	
  return 0;*/
}
