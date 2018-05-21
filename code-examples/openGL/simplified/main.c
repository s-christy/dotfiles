#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xutil.h>

int Xscreen;
int numfbconfigs;
int width,height;

Atom del_atom;
Display *Xdisplay;
GLXFBConfig *fbconfigs,fbconfig;
GLXWindow glX_window_handle;
Window Xroot,window_handle;
XEvent event;
XRenderPictFormat *pict_format;
XVisualInfo *visual;

float light0_dir[]={0,1,0,0};
float light0_color[]={78./255.,80./255.,184./255.,1};
float light1_dir[]={-1,1,1,0};
float light1_color[]={255./255.,220./255.,97./255.,1};
float light2_dir[]={0,-1,0,0};
float light2_color[]={31./255.,75./255.,16./255.,1};

float worldRot=0;
float worldRotVel=0;

GLfloat verts[][8]={{-1.0,-1.0,1.0,0.0,0.0,1.0,0.0,0.0},{ 1.0,-1.0,1.0,0.0,0.0,1.0,1.0,0.0},{ 1.0,1.0,1.0,0.0,0.0,1.0,1.0,1.0},{-1.0,1.0,1.0,0.0,0.0,1.0,0.0,1.0},{ 1.0,-1.0,-1.0,0.0,0.0,-1.0,0.0,0.0},{-1.0,-1.0,-1.0,0.0,0.0,-1.0,1.0,0.0},{-1.0,1.0,-1.0,0.0,0.0,-1.0,1.0,1.0},{ 1.0,1.0,-1.0,0.0,0.0,-1.0,0.0,1.0},{-1.0,-1.0,-1.0,-1.0,0.0,0.0,0.0,0.0},{-1.0,-1.0,1.0,-1.0,0.0,0.0,1.0,0.0},{-1.0,1.0,1.0,-1.0,0.0,0.0,1.0,1.0},{-1.0,1.0,-1.0,-1.0,0.0,0.0,0.0,1.0},{ 1.0,-1.0,1.0,1.0,0.0,0.0,0.0,0.0},{ 1.0,-1.0,-1.0,1.0,0.0,0.0,1.0,0.0},{ 1.0,1.0,-1.0,1.0,0.0,0.0,1.0,1.0},{ 1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0},{-1.0,-1.0,-1.0,0.0,-1.0,0.0,0.0,0.0},{ 1.0,-1.0,-1.0,0.0,-1.0,0.0,1.0,0.0},{ 1.0,-1.0,1.0,0.0,-1.0,0.0,1.0,1.0},{-1.0,-1.0,1.0,0.0,-1.0,0.0,0.0,1.0},{-1.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0},{ 1.0,1.0,1.0,0.0,1.0,0.0,1.0,0.0},{ 1.0,1.0,-1.0,0.0,1.0,0.0,1.0,1.0},{-1.0,1.0,-1.0,0.0,1.0,0.0,0.0,1.0},};

Bool WaitForMapNotify(Display *d,XEvent *e,char *arg){
	return d && e && arg && (e->type==MapNotify) && (e->xmap.window==*(Window*)arg);
}

void createTheWindow(){
	XSetWindowAttributes attr={0,};
	Xdisplay=XOpenDisplay(NULL);
	Xscreen=DefaultScreen(Xdisplay);
	Xroot=RootWindow(Xdisplay,Xscreen);

	fbconfigs=glXChooseFBConfig(Xdisplay,Xscreen,NULL,&numfbconfigs);
	for(int i=0; i<numfbconfigs; i++) {
		visual=(XVisualInfo*) glXGetVisualFromFBConfig(Xdisplay,fbconfigs[i]);
		pict_format=XRenderFindVisualFormat(Xdisplay,visual->visual);
		fbconfig=fbconfigs[i];

		//this is why the background is transparent
		//if(pict_format->direct.alphaMask > 0)break;
	}

	attr.colormap=XCreateColormap(Xdisplay,Xroot,visual->visual,AllocNone);
	attr.background_pixmap=None;
	attr.border_pixmap=None;
	attr.border_pixel=0;
	attr.event_mask=
		StructureNotifyMask |
		EnterWindowMask |
		LeaveWindowMask |
		ExposureMask |
		ButtonPressMask |
		ButtonReleaseMask |
		OwnerGrabButtonMask |
		KeyPressMask |
		KeyReleaseMask;

	int attr_mask=
		CWBackPixmap|
		CWColormap|
		CWBorderPixel|
		CWEventMask;

	window_handle=XCreateWindow(Xdisplay,
			Xroot,
			0,0,200,200,
			0,
			visual->depth,
			InputOutput,
			visual->visual,
			attr_mask,&attr);

	glX_window_handle=window_handle;

	char *title="TEST";
	XTextProperty textprop;
	textprop.value=(unsigned char*)title;
	textprop.encoding=XA_STRING;
	textprop.format=8;
	textprop.nitems=strlen(title);

	XSetWMProperties(Xdisplay,window_handle,&textprop,&textprop,NULL,0,	NULL,NULL,NULL);
	XMapWindow(Xdisplay,window_handle);
	XIfEvent(Xdisplay,&event,WaitForMapNotify,(char*)&window_handle);
	if ((del_atom=XInternAtom(Xdisplay,"WM_DELETE_WINDOW",0)) !=None) {
		XSetWMProtocols(Xdisplay,window_handle,&del_atom,1);
	}
	GLXContext render_context=glXCreateNewContext(Xdisplay,fbconfig,GLX_RGBA_TYPE,0,True);
	glXMakeContextCurrent(Xdisplay,glX_window_handle,glX_window_handle,render_context);
}

int handleEvents(){
	XConfigureEvent *xc;
	KeySym key;
	while (XPending(Xdisplay)){
		XNextEvent(Xdisplay,&event);
		switch (event.type){
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
					case 'a':
						worldRotVel++;
						break;
					case 'q':
						exit(0);
						break;
					default:
						printf("%d\n",key);
						break;
					case 65361:
						worldRotVel--;
						break;
					case 65362:
						worldRotVel++;
						break;
					case 65363:
						worldRotVel++;
						break;
					case 65364:
						worldRotVel--;
						break;
				}
				//printf("%d\n",key);
				break;
		}
	}
	return 1;
}

void draw_cube(){
	glColor4f(1.,1.,1.,1.);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3,GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][0]);
	glNormalPointer(GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][3]);
	glTexCoordPointer(2,GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][6]);

	glDrawArrays(GL_QUADS,0,24);
}

void light(){
	glLightfv(GL_LIGHT0,GL_POSITION,light0_dir);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_color);

	glLightfv(GL_LIGHT1,GL_POSITION,light1_dir);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_color);

	glLightfv(GL_LIGHT2,GL_POSITION,light2_dir);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_color);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void redrawTheWindow(){
	float aspect=(float)width / (float)height;

	glDrawBuffer(GL_BACK);

	glViewport(0,0,width,height);

	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-aspect,aspect,-1,1,2.5,20);//the 20 is the viewdistance

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	light();

	glTranslatef(0.,0.,-10.);//move the world 10 units away from the camera
	glRotatef(worldRot,0,1,0);//rotate along the y axis
	worldRot+=worldRotVel;

	//draw cube,translate,then draw another cube
	glCullFace(GL_FRONT);
	draw_cube();
	glCullFace(GL_BACK);
	draw_cube();

	glTranslatef(0.,0.,-3.);

	glCullFace(GL_FRONT);
	draw_cube();
	glCullFace(GL_BACK);
	draw_cube();

	//everything is done,show on screen
	glXSwapBuffers(Xdisplay,glX_window_handle);
}

int main(int argc,char *argv[]){
	createTheWindow();
	while (handleEvents()) {
		redrawTheWindow();
	}
	return 0;
}
