#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
//neccessary for function save_me.
gint stroke=0;//to save.
gint clear=0;//in expose event to clear screen;
gint breadth=800,height=650;//drawing area dimentions
gint rec1=3,rec2=3;//this determines the size of rectangle
float red=0,green=0,blue=0;//They are colour proportions

//GM
int handler_id;
int CUR_VISITED=0;
int check = 0;
int pixels[10000][10000];
int visited[10000][10000];
//AR
int SPLINE =0;
int CIRCLE=0;
int FILL=0;
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
struct param_{
  gint x;
  gint y;
}; 
int ERASER=0;
cairo_t *cr;
GtkWidget *drawing_area;
struct param_ p;

//GM

void colour_me (GtkWidget *widget,gpointer data);
void unstroke_me (GtkWidget *widget, gpointer data);
void stroke_me (GtkWidget *widget, gpointer data);
void red_decrease(GtkWidget *widget, gpointer data);
void thickness_increase(GtkWidget *widget, gpointer data);
void thickness_decrease(GtkWidget *widget, gpointer data);
void red_decrease(GtkWidget *widget, gpointer data);
void green_decrease(GtkWidget *widget, gpointer data);
void blue_decrease(GtkWidget *widget, gpointer data);
void red_increase(GtkWidget *widget, gpointer data);
void green_increase(GtkWidget *widget, gpointer data);
void blue_increase(GtkWidget *widget, gpointer data);

//GM
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
//AR

GtkWidget *newVerticalbox (gint A, gint B,
		     gint C, gint D, gint E );
GtkWidget *newhorizontalbox1 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox2 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox3 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox4 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox5 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox6 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox7 (gint A, gint B, gint C, gint D, gint E );
GtkWidget *newhorizontalbox8 (gint A, gint B, gint C, gint D, gint E );

GtkWidget *horizontal_box (gint A, gint B,
		     gint C, gint D, gint E,gint first);
