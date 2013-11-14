#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "math.h"
#include "quicksort.c"
gint stroke=0;//variable to trigger stroke;
gint a=0,b=0;//used in expose_event function to size the rectangle
gint clear=0;//variable to trigger clear.
gint breadth=800,height=600;//drawing area dimentions
gint rec1=3,rec2=3;//this determines the size of rectangle
float red=0,green=0,blue=0;//They are colour proportions
int complete=0;//variable to trigger complete.
int line=0;//variable to trigger line.
  GtkWidget *butlabel;//global lable widgets to set text 
  GtkWidget *cullabel;//indicating which button's are in use.
struct {
  int count;//to count the point's selected for lines.
  double coordx[400];//stores the coordinates of points
  double coordy[400];//chose to make a line.
} glob;

//GM
double angle1;
double angle2;
double angle;
int center_x;
int center_y;
double radius;
int CUR_VISITED=0;
int check = 0;
gint pixels[10000][10000];
int visited[10000][10000];
int SPLINE =0;
int FILL=0;
int CENTER=0;
int RADIUS =0;
int SLINKY=0;
//AR
int CIRCLE=0;
int sp_x[10000];
int sp_y[10000];
int circle_x[10000];
int circle_y[10000];
int circle_centre;
int circle_radius;
float a1[10000];
float b1[10000];
float c[10000];
float h[10000];
gint count_sp=0;
gint count_circle=0;
float RAD;
float CENTRE_X;
float CENTRE_Y;
float R[10240][10000];
float B[10240][10000];
float G[10240][10000];
struct param_{
  gint x;
  gint y;
}; 

int ERASER=0;
cairo_t *cr;

GtkWidget *drawing_area;
struct param_ p;

//GM

// function to trigger lines.
void line_me (GtkWidget *widget, gpointer data);
// function to trigger complete.
void complete_me (GtkWidget *widget, gpointer data);
// function to trigger colours.
void colour_me (GtkWidget *widget,gpointer data);
// function to trigger normal mode.
void unstroke_me (GtkWidget *widget, gpointer data);
// function to trigger stroke mode.
void stroke_me (GtkWidget *widget, gpointer data);
// function call to increase thickness.
void thickness_increase(GtkWidget *widget, gpointer data);
// function call to decrease thickness.
void thickness_decrease(GtkWidget *widget, gpointer data);
// function call to reduce red content.
void red_decrease(GtkWidget *widget, gpointer data);
// function call to reduce green content.
void green_decrease(GtkWidget *widget, gpointer data);
// function call to reduce blue content.
void blue_decrease(GtkWidget *widget, gpointer data);
// function call to increase red content.
void red_increase(GtkWidget *widget, gpointer data);
// function call to increase green content.
void green_increase(GtkWidget *widget, gpointer data);
// function call to increase blue content.
void blue_increase(GtkWidget *widget, gpointer data);

//GM
void slinky_off( GtkWidget *widget, GdkEventButton *event );
void slinky( GtkWidget *widget, GdkEventButton *event );
void get_radius(GtkWidget *widget, GdkEventButton *event);
void get_center(GtkWidget *widget, GdkEventButton *event);
void button_press_event_circle_gm( GtkWidget *widget, GdkEventButton *event );
int check_floodfill(struct param_ p, int dir);		     
void floodfill(GtkWidget *widget, struct param_ p,int dir);		     
void floodfill_select( GtkWidget *widget, GdkEventButton *event);
static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event );
//GM
//AR
void get_points_spline(GtkWidget *widget, GdkEventButton *event);
void get_points_circle(GtkWidget *widget, GdkEventButton *event);
void aux_get_points_spline(GtkWidget * widget, GdkEventButton * event);
void aux_get_points_circle(GtkWidget * widget, GdkEventButton * event);
static gboolean button_press_event_spline(GtkWidget *widget, GdkEventButton *event);
static gboolean button_press_event_circle(GtkWidget * widget, GdkEventButton * event);
void draw_circle();
float distance (float x1,float y1,float x2,float y2);
float max_dist(int i);
int maxx_dist(int i);
int maxy_dist(int i);

//AR
// below horizontal box's are packed in newVericalbox.
GtkWidget *newVerticalbox (gint A, gint B,
		     gint C, gint D, gint E );
 /* 
  * newhorizontalbox(12345678) below functions 
  * represent the row of the button
  */
GtkWidget *newhorizontalbox1 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox2 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox3 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox4 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox5 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox6 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox7 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox8 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox9 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox10 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox11 (gint A, gint B, gint C, gint D, gint E );
// all colour boxes are packed in horizontal_box.
GtkWidget *horizontal_box (gint A, gint B, gint C, gint D, gint E,gint first);
