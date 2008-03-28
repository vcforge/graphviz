/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#ifndef SMYRNADEFS_H
#define SMYRNADEFS_H

#ifdef WIN32
#include "windows.h"
//#define       SMYRNA_GLADE "C:/Projects/graphviz2/share/gui/smyrna.glade"
#define	SMYRNA_ATTRS "c:/Projects/graphviz2/share/gui/attrs.txt"
#endif
#ifdef _WIN32
#define SMYRNA_GLADE "c:\\Projects\\ATT\\GTK\\gtktopview\\lib\\GUI\\smyrna.glade"
#define GTKTOPVIEW_ATTRS "c:\\Projects\\ATT\\GTK\\GTKTest2\\attrs.txt"
#define DEFAULT_ATTRIBUTES_TEMPLATE_DOT_FILE	"C:\\GTK\\2.0\\bin\\attr_template.dot"
// #else
// using -DGTKTOPVIEW_GLADE from Makefile.am and configure.ac
// using -DGTKTOPVIEW_ATTRS from Makefile.am and configure.ac
#endif
#ifdef	WIN32			//this  is needed on WIN32 to get libglade see the callback
#define _BB  __declspec(dllexport)
#else
#define _BB
#endif

#include <gtk/gtk.h>
#include "cgraph.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <gtk/gtkgl.h>
#include "glcompset.h"
#include "hierarchy.h"

#define IS_TEST_MODE_ON							0
#define	DEFAULT_MAGNIFIER_WIDTH					300
#define	DEFAULT_MAGNIFIER_HEIGHT				225
#define DEFAULT_MAGNIFIER_KTS					3	//x3
#define DEFAULT_FISHEYE_MAGNIFIER_RADIUS		250
#define TOP_VIEW_USER_ADVANCED_MODE				0
#define TOP_VIEW_USER_NOVICE_MODE				1

//mouse modes
#define MM_PAN					0
#define MM_ZOOM					1
#define MM_ROTATE				2
#define MM_SINGLE_SELECT		3
#define MM_RECTANGULAR_SELECT	4
#define MM_RECTANGULAR_X_SELECT	5
#define MM_MOVE					10
#define MM_MAGNIFIER			20
#define MM_FISHEYE_MAGNIFIER	21

#define MAX_ZOOM	-1.000033
#define MIN_ZOOM	-89.00000
#define ZOOM_STEP	5
#define DEG2RAD  G_PI/180

#define UNHIGHLIGHTED_ALPHA	0.3
#define Z_FORWARD_PLANE -0.00201
#define Z_MIDDLE_PLANE 0.0000
#define Z_BACK_PLANE -0.00199

#define NODE_ZOOM_LIMIT	-25.3
#define NODE_CIRCLE_LIMIT	-7.3

typedef enum { nodshapedot,nodeshapecircle} node_shape;

typedef struct {
    float R;
    float G;
    float B;
    float A;			//Alpha
} RGBColor;

typedef struct {
    GtkButton **gtkhostbtn;
    int gtkhostbtncount;
    GtkColorButton **gtkhostcolor;
    int hostactive[50];		//temporary static, convert to dynamic,realloc
    char **hostregex;
} topviewdata;
typedef struct {
    Agnode_t *Node;
    /*original coordinates */
    float x;
    float y;
    float z;
    /*coordinates to draw */
    float distorted_x;
    float distorted_y;
    float distorted_z;
    float zoom_factor;
    int in_fish_eye;		//boolean value if to apply fisheye
    RGBColor Color;
    RGBColor GroupColor;
    int GroupIndex;		//default -1;
    int update_required;
    char *Label;
    char *Label2;
    int degree;
    float node_alpha;
    int valid;
} topview_node;

typedef struct {
    Agnode_t *Tnode;		//Tail node
    Agnode_t *Hnode;		//Tail node
    Agedge_t *Edge;		//edge itself
    float x1;
    float y1;
    float z1;
    float x2;
    float y2;
    float z2;
    topview_node *Node1;
    topview_node *Node2;
    RGBColor Color;
    int update_required;
} topview_edge;

typedef struct {
    topview_node *Nodes;
    topview_edge *Edges;
    int Nodecount;
    int Edgecount;
    int limits[4];
    glCompSet *topviewmenu;	//for novice user open gl menu
    topviewdata *TopviewData;
    void *customptr;
    Hierarchy *h;
} topview;

enum {
    COL_NAME = 0,
    COL_FILENAME,
    NUM_COLS
};
//atributes
typedef struct _mouse_attr {
    int mouse_down;
    int mouse_mode;
    int mouse_X;
    int mouse_Y;
} mouse_attr;


typedef struct _attribute {
    char Type;
    char *Name;
    char *Default;
    char ApplyTo[4];
    char Engine[5];
    char **ComboValues;
    int ComboValuesCount;
    GtkWidget *attrWidget;

} attribute;

//bind this to cgraph g
typedef struct _custom_graph_data {
    Agrec_t h;
    char *GraphName;
    char *GraphFileName;
    int AlwaysShow;		//active or not draw it 
    int TopView;		//default 0, 1 for topview data, dots and lines
    int Locked;
    int Engine;			//enum GVEngine{DOT,NEATO,TWOPI,CIRCO,FDP};
    //graph's location, change these to move the whole graph
    int Modified;		//if graph has been modified after loading
    float offsetx;
    float offsety;
    float offsetz;

    Agraph_t **selectedGraphs;	//clusters , subgraphs indeed
    Agnode_t **selectedNodes;
    Agedge_t **selectedEdges;

    int selectedGraphsCount;
    int selectedNodesCount;
    int selectedEdgesCount;
} custom_graph_data;



enum GEunit { GEpixels, GEinches, GEmm };


typedef struct _custom_object_data	//has to be attached to every Node, Edge, Graph and cluster
{
    Agrec_t h;
    int ID;
    char *ObjName;
    int ObjType;
    int Layer;
    int Visible;
    int Locked;
    int Highlighted;
    int Selected;
    int Preselected;
    int NumDataCount;
    float *NumData;
    int StrDataCount;
    char **StrData;
    int selectionflag;
    int param;			//generic purpose param
    int TVRef;			//Topview reference

} custom_object_data;

#define OD_id(p) (((custom_object_data*)AGDATA(p))->TVRef)
#define OD_Selected(p) (((custom_object_data*)AGDATA(p))->Selected)
#define OD_Preselected(p) (((custom_object_data*)AGDATA(p))->Preselected)
#define OD_SelFlag(p) (((custom_object_data*)AGDATA(p))->selectionflag)

typedef struct _selection {
    int Active;			//0 there is no selection need to be applied
    char Type;			//0     single selection , 1 rectangle , 2 rectangleX 
    float X, Y, W, H;		//selection boundries
    int Anti;			//subtract selections if 1
    int AlreadySelected;	//for single selections to avoid selecting more than one object
    RGBColor SelectionColor;

} selection;
typedef struct _magnifier {
    float x, y;
    float kts;			//zoom X
    float GLwidth, GLheight;
    int width, height;		//how big is the magnifier referenced from windows
    int active;
} magnifier;

typedef struct _fisheye_magnifier {
    float x, y;			//center coords of active circle
    float distortion_factor;	//distortion factor ,default 1
    int R;			//radius of  the magnifier 
	int constantR;	//radius of  the magnifier referenced from windows
    int active;
    int fisheye_distortion_fac;
} fisheye_magnifier;

typedef struct _ViewInfo
{
	/*view variables*/
	float panx;
	float pany;
	float panz;
	float prevpanx;
	float prevpany;
	float prevpanz;
	float zoom;

	/*clipping coordinates, to avoid unnecesarry rendering*/
	float clipX1,clipX2,clipY1,clipY2,clipZ1,clipZ2;

	/*background color*/
	RGBColor bgColor;
	/*default pen color*/
	RGBColor penColor;
	/*default fill color*/
	RGBColor fillColor;
	/*highlighted Node Color*/
	RGBColor highlightedNodeColor;
	/*highlighted Edge Color*/
	RGBColor highlightedEdgeColor;
	/*grid color*/
	RGBColor gridColor;	//grid color
	/*border color*/
	RGBColor borderColor;
	/*selected node color*/
	RGBColor selectedNodeColor;
	/*selected edge color*/
	RGBColor selectedEdgeColor;

	/*default line width*/
	float LineWidth;
	
	/*grid is drawn if this variable is 1*/
	int gridVisible;	
	/*grid cell size in gl coords system*/
	float gridSize;	//grid cell size

	/*draws a border in border colors if it is 1*/
	int bdVisible;	//if borders are visible (boundries of the drawing,
	/*border coordinates, needs to be calculated for each graph*/

	/*randomize node colors or use default node color*/
	int rndNodeColor;

	/*randomize edge colors or use default edge color*/
	int rndEdgeColor;
	/*Font Size*/
	int FontSize;


	float bdxLeft,bdyTop,bdzTop;	
	float bdxRight,bdyBottom,bdzBottom; 

	/*reserved , not being used yet*/
	enum GEunit unit;	//default pixels :0  

	/*variable to hold mouse coordinates temporarily*/
	float GLx,GLy,GLz;		
	/*this is second  set of mouse coordinates holder for, it is needed to draw a rectangle with mouse*/
	float GLx2,GLy2,GLz2;		

	/*screen window size in 2d*/	
	int w,h;
	/*graph pointer to hold loaded graphs*/
	Agraph_t** g;
	/*number of graphs loaded*/
	int graphCount;		
	/*active graph*/
	int activeGraph; 

	/*texture data*/
	int texture;	/*1 texturing enabled, 0 disabled*/	
	/*opengl depth value to convert mouse to GL coords*/
	float GLDepth;		

	/*stores the info about status of mouse,pressed? what button ? where?*/
	mouse_attr mouse;

	/*selection object,refer to smyrnadefs.h for more info*/
	selection Selection;

	/*rectangular magnifier object*/
	magnifier mg;
	/*fisheye magnifier object*/
	fisheye_magnifier fmg;

	/*data attributes are read from graph's attributes DataAttribute1 and DataAttribute2*/
	char* node_data_attribute1;	/*for topview graphs this is the node data attribute to put as label*/
	char* node_data_attribute2;	/*for topview graphs this is the node data attribute to be stored and used for something else*/

	/*0 advanced users with editing options 1 nonice users just navigate (glmenu system)*/
	int topviewusermode;	
	/*this should not be confused with graphviz node shapes, it can be dot or circles (dots are rendered mych faster, circle looks handsome, if graph is ulta large go with dot*/
//	node_shape nodeshape;
	/*if true and nodeshape is nodeshapecircle , radius of nodes changes with degree*/
	int nodesizewithdegree;

	/*open gl canvas, used to be a globa variable before looks better wrapped in viewinfo*/
	GtkWidget *drawing_area; 

	/*some boolean variable for variety hacks used in the software*/
	int SignalBlock;

	/*Topview data structure, refer topview.h for more info*/
	topview* Topview;
	/*listed default visual graph attributes are stored in this graph
	bgcolor;
	bordercolor;
	gridcolor;
	highlightednodecolor;
	selectednodecolor;
	selectededgecolor;
	bdvisible;
	gridvisible; */
	Agraph_t* default_attributes;
}ViewInfo;

extern ViewInfo *view;
extern GtkMessageDialog *Dlg;
extern int respond;
extern char* smyrnaPath (char* suffix);
extern char* smyrnaGlade;

extern void glexpose();


#endif
