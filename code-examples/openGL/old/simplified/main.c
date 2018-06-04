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

#define numparts 10000

int width,height;

Atom del_atom;
Display *Xdisplay;
GLXWindow glX_window_handle;

GLfloat verts[][8]={{-1.0,-1.0,1.0,0.0,0.0,1.0,0.0,0.0},{ 1.0,-1.0,1.0,0.0,0.0,1.0,1.0,0.0},{ 1.0,1.0,1.0,0.0,0.0,1.0,1.0,1.0},{-1.0,1.0,1.0,0.0,0.0,1.0,0.0,1.0},{ 1.0,-1.0,-1.0,0.0,0.0,-1.0,0.0,0.0},{-1.0,-1.0,-1.0,0.0,0.0,-1.0,1.0,0.0},{-1.0,1.0,-1.0,0.0,0.0,-1.0,1.0,1.0},{ 1.0,1.0,-1.0,0.0,0.0,-1.0,0.0,1.0},{-1.0,-1.0,-1.0,-1.0,0.0,0.0,0.0,0.0},{-1.0,-1.0,1.0,-1.0,0.0,0.0,1.0,0.0},{-1.0,1.0,1.0,-1.0,0.0,0.0,1.0,1.0},{-1.0,1.0,-1.0,-1.0,0.0,0.0,0.0,1.0},{ 1.0,-1.0,1.0,1.0,0.0,0.0,0.0,0.0},{ 1.0,-1.0,-1.0,1.0,0.0,0.0,1.0,0.0},{ 1.0,1.0,-1.0,1.0,0.0,0.0,1.0,1.0},{ 1.0,1.0,1.0,1.0,0.0,0.0,0.0,1.0},{-1.0,-1.0,-1.0,0.0,-1.0,0.0,0.0,0.0},{ 1.0,-1.0,-1.0,0.0,-1.0,0.0,1.0,0.0},{ 1.0,-1.0,1.0,0.0,-1.0,0.0,1.0,1.0},{-1.0,-1.0,1.0,0.0,-1.0,0.0,0.0,1.0},{-1.0,1.0,1.0,0.0,1.0,0.0,0.0,0.0},{ 1.0,1.0,1.0,0.0,1.0,0.0,1.0,0.0},{ 1.0,1.0,-1.0,0.0,1.0,0.0,1.0,1.0},{-1.0,1.0,-1.0,0.0,1.0,0.0,0.0,1.0},};

struct vector{
	double x,y,z;
};

struct obj{
	struct vector xyz;
	struct vector vel;
};

struct plane{
	struct vector xyz;
	struct vector dir;
};

struct planeSegment{
	struct plane p;
	struct vector xyz;
	double w;
	double d;
};

struct vector camPos;
struct vector camRot;
struct obj objectlist[numparts];

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

	XSetWMProperties(Xdisplay,window_handle,&textprop,&textprop,NULL,0,NULL,NULL,NULL);
	XMapWindow(Xdisplay,window_handle);
	XSetWMProtocols(Xdisplay,window_handle,&del_atom,1);
	GLXContext render_context=glXCreateNewContext(Xdisplay,fbconfig,GLX_RGBA_TYPE,0,True);
	glXMakeContextCurrent(Xdisplay,glX_window_handle,glX_window_handle,render_context);

	for(int i=0;i<numparts;i++){
		objectlist[i].xyz.x=(rand()%2000/50.-10)*1.;
		objectlist[i].xyz.y=(rand()%2000/50.-10)*1.;
		objectlist[i].xyz.z=(rand()%2000/50.-10)*1.;
		objectlist[i].vel.x=0;
		objectlist[i].vel.y=0;
		objectlist[i].vel.z=0;
	}
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
					case 'd':
						camRot.y+=20;
						break;
					case 'a':
						camRot.y-=20;
						break;
					case 'q':
						exit(0);
						break;
					default:
						printf("%d\n",key);
						break;
					case 65361:
						camPos.x+=20;
						break;
					case 65362:
						camPos.z+=20;
						break;
					case 65363:
						camPos.x-=20;
						break;
					case 65364:
						camPos.z-=20;
						break;
				}
				//printf("%d\n",key);
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

	glVertexPointer(3,GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][0]);
	glNormalPointer(GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][3]);
	glTexCoordPointer(2,GL_FLOAT,sizeof(GLfloat) * 8,&verts[0][6]);

	glDrawArrays(GL_TRIANGLES,0,3);
	//glColor4f(.5,.5,.5,.5);
	//glLineWidth(2.5);
	//glDrawArrays(GL_LINES,0,1);
}

void light(){
	float light0_dir[]={0,1,0,0};
	float light0_color[]={78./255.,80./255.,184./255.,1};
	float light1_dir[]={-1,1,1,0};
	float light1_color[]={255./255.,220./255.,97./255.,1};
	float light2_dir[]={0,-1,0,0};
	float light2_color[]={31./255.,75./255.,16./255.,1};
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

void draw(int i){
	glTranslatef(1.*objectlist[i].xyz.x,1.*objectlist[i].xyz.y,1.*objectlist[i].xyz.z);
	float scale=5;
	glScalef(1/scale,1/scale,1/scale);
	glCullFace(GL_FRONT);
	draw_vert_array();
	glCullFace(GL_BACK);
	draw_vert_array();
	glScalef(scale,scale,scale);
	glTranslatef(-1.*objectlist[i].xyz.x,-1.*objectlist[i].xyz.y,-1.*objectlist[i].xyz.z);
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

double absVec(struct vector v){
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

double dotVec(struct vector a,struct vector b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

struct vector scaleVec(struct vector v,double s){
	struct vector ret;
	ret.x=v.x*s;
	ret.y=v.y*s;
	ret.z=v.z*s;
	return ret;
}

struct vector normalize(struct vector v){
	double a=absVec(v);
	v.x=v.x/a;
	v.y=v.y/a;
	v.z=v.z/a;
	return v;
}

struct vector addVec(struct vector a, struct vector b){
	struct vector v;
	v.x=a.x+b.x;
	v.y=a.y+b.y;
	v.z=a.z+b.z;
	return v;
}

void printVec(struct vector v){
	printf("%f %f %f ",v.x,v.y,v.z);
}
//
void bounce(int i, struct planeSegment ps){
	struct plane p=ps.p;
	if(objectlist[i].xyz.x*p.dir.x+objectlist[i].xyz.y*p.dir.y+objectlist[i].xyz.z*p.dir.z<=p.xyz.y &&
			objectlist[i].xyz.x<=p.xyz.x+ps.w+ps.xyz.x &&
			objectlist[i].xyz.x>=p.xyz.x-ps.w-ps.xyz.x
	  ){
		struct vector d=objectlist[i].vel;
		struct vector n=normalize(p.dir);
		struct vector r;
		double ddotn=dotVec(d,n);
		//		//r=d-2(d.n)n
		r.x=d.x-2.*ddotn*n.x;
		r.y=d.y-2.*ddotn*n.y;
		r.z=d.z-2.*ddotn*n.z;
		r=scaleVec(r,.7);
		struct vector randomVec;
		//randomVec.x=rand();
		//randomVec.y=rand();
		//randomVec.z=rand();
		//r=addVec(r,scaleVec(normalize(randomVec),absVec(r)*.01));
		objectlist[i].vel=r;
		if(absVec(r)<.1){
			objectlist[i].vel.x=0;
			objectlist[i].vel.y=0;
			objectlist[i].vel.z=0;
		}
	}
}
//
void physics(){
	for(int i=0;i<numparts;i++){
		objectlist[i].xyz.x+=objectlist[i].vel.x;
		objectlist[i].xyz.y+=objectlist[i].vel.y;
		objectlist[i].vel.y-=.1;
		objectlist[i].xyz.z+=objectlist[i].vel.z;
		draw(i);

		struct planeSegment ps=(struct planeSegment){
			ps.p=(struct plane){
				(struct vector){0,-100,0},
					(struct vector){1,5,1}
			},
				ps.xyz=(struct vector){0,0,0},
				ps.w=3,
				ps.d=2,
		};

		bounce(i,ps);
		ps.p.xyz.y=-150;
		ps.p.dir.x=-1;
		ps.xyz.x=10;
		//ps.w=100000;
		bounce(i,ps);
	}
}
//
void redrawTheWindow(){
	glSettings();
	light();
	glTranslatef(0.,0.,-150.);//move the world 50 units away from the camera
	glTranslatef(camPos.x,camPos.y,camPos.z);
	glRotatef(camRot.x,1,0,0);
	glRotatef(camRot.y,0,1,0);
	glRotatef(camRot.z,0,0,1);
	//glRotatef(25.,1.,0.,0.);
	for(int i=0;i<1;i++)physics();
	//everything is done,show on screen
	glXSwapBuffers(Xdisplay,glX_window_handle);
}

int main(int argc,char *argv[]){
	createTheWindow();
	while (handleEvents())redrawTheWindow();
	return 0;
}
