#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>

int width,height;
float counter=0;

Atom del_atom;
Display *Xdisplay;
GLXWindow glX_window_handle;

GLfloat triangle[][8]={{-1.0,-1.0,1.0,0.0,0.0,1.0,0.0,0.0},{ 1.0,-1.0,1.0,0.0,0.0,1.0,1.0,0.0},{ 1.0,1.0,1.0,0.0,0.0,1.0,1.0,1.0}};

Bool WaitForMapNotify(Display *d,XEvent *e,char *arg){
	return d && e && arg && (e->type==MapNotify) && (e->xmap.window==*(Window*)arg);
}

void createTheWindow(){
	Window Xroot,window_handle;
	GLXFBConfig *fbconfigs,fbconfig;
	XRenderPictFormat *pict_format;
	XVisualInfo *visual;
	XSetWindowAttributes attr={0,};
	Xdisplay=XOpenDisplay(NULL);
	int Xscreen;
	Xscreen=DefaultScreen(Xdisplay);
	Xroot=RootWindow(Xdisplay,Xscreen);
	int numfbconfigs;

	fbconfigs=glXChooseFBConfig(Xdisplay,Xscreen,NULL,&numfbconfigs);
	for(int i=0; i<numfbconfigs; i++) {
		visual=(XVisualInfo*) glXGetVisualFromFBConfig(Xdisplay,fbconfigs[i]);
		pict_format=XRenderFindVisualFormat(Xdisplay,visual->visual);
		fbconfig=fbconfigs[i];
	}

	attr.colormap=XCreateColormap(Xdisplay,Xroot,visual->visual,AllocNone);
	attr.background_pixmap=None;
	attr.border_pixmap=None;
	attr.border_pixel=0;
	attr.event_mask=StructureNotifyMask|EnterWindowMask|LeaveWindowMask|ExposureMask|ButtonPressMask|ButtonReleaseMask|OwnerGrabButtonMask|KeyPressMask|KeyReleaseMask;
	int attr_mask=CWBackPixmap|CWColormap|CWBorderPixel|CWEventMask;
	window_handle=XCreateWindow(Xdisplay,Xroot,0,0,200,200,0,visual->depth,InputOutput,visual->visual,attr_mask,&attr);
	glX_window_handle=window_handle;

	char *title="TEST";
	XTextProperty textprop;
	textprop.value=(unsigned char*)title;
	textprop.encoding=XA_STRING;
	textprop.format=8;
	textprop.nitems=strlen(title);

	XSetWMProperties(Xdisplay,window_handle,&textprop,&textprop,NULL,0,NULL,NULL,NULL);
	XMapWindow(Xdisplay,window_handle);
	XSetWMProtocols(Xdisplay,window_handle,&del_atom,1);
	GLXContext render_context=glXCreateNewContext(Xdisplay,fbconfig,GLX_RGBA_TYPE,0,True);
	glXMakeContextCurrent(Xdisplay,glX_window_handle,glX_window_handle,render_context);
}

int handleEvents(){
	XEvent event;
	XConfigureEvent *xc;
	KeySym key;
	while (XPending(Xdisplay)){
		XNextEvent(Xdisplay,&event);
		switch (event.type){
			case MotionNotify:
				printf("%f",event.xmotion.x);
				break;
			case ClientMessage:
				if (event.xclient.data.l[0]==del_atom){
					return 0;
				}
				break;
			case ConfigureNotify:
				xc=&(event.xconfigure);
				width=xc->width;
				height=xc->height;
				break;
			case KeyPress:
				XLookupString((XKeyEvent *)&event,NULL,0,&key,NULL);
				switch (key){
					case 'q':
						exit(0);
						break;
					default:
						printf("%d\n",key);
						break;
				}
				break;
		}
	}
	return 1;
}

void draw_vert_array(){
	glColor4f(1.,1.,1.,.7);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3,GL_FLOAT,sizeof(GLfloat) * 8,&triangle[0][0]);
	glNormalPointer(GL_FLOAT,sizeof(GLfloat) * 8,&triangle[0][3]);
	glTexCoordPointer(2,GL_FLOAT,sizeof(GLfloat) * 8,&triangle[0][6]);

	glDrawArrays(GL_TRIANGLES,0,3);
}

void draw(float x, float y, float z, float scale){
	glTranslatef(x,y,z);
	glScalef(scale,scale,scale);
	glCullFace(GL_FRONT);
	draw_vert_array();
	glCullFace(GL_BACK);
	draw_vert_array();
	glScalef(1/scale,1/scale,1/scale);
	glTranslatef(-x,-y,-z);
}

void glSettings(){
	float aspect=(float)width / (float)height;

	glDrawBuffer(GL_BACK);

	glViewport(0,0,width,height);

	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-aspect,aspect,-1,1,2.5,200);//the 200 is the viewdistance

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
}
void init(){
}

void redrawTheWindow(){
	glSettings();
	counter++;
	glTranslatef(0,0,-5);
	glRotatef(counter,0,1,0);
	for(float x=0;x<1.;x+=.01){
		draw(rand()%100/100.,rand()%100/100.,rand()%100/100.,.01);
	}
	glXSwapBuffers(Xdisplay,glX_window_handle);
}

int main(int argc,char *argv[]){
	createTheWindow();
	init();
	while (handleEvents())redrawTheWindow();
	return 0;
}
