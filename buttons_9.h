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
int COMPLETE=0;
int LINE=0;
//GM
int handler_id_pencil;
//int handler_id_fill;
//int handler_id_spline;
//int handler_id_get_points;
int CUR_VISITED=0;
int check = 0;
gint pixels[10000][10000];
int visited[10000][10000];
int SPLINE =0;
int FILL=0;
//AR
int sp_x[10000];
int sp_y[10000];
float a1[10000];
float b1[10000];
float c[10000];
float h[10000];
gint count_sp=0;
struct param_{
  gint x;
  gint y;
}; 

struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;

cairo_t *cr;
cairo_t *cr1;
GtkWidget *drawing_area;
struct param_ p;

//GM
void line_me (GtkWidget *widget, gpointer data);
void complete_me (GtkWidget *widget, gpointer data);
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
void line_get(GtkWidget *widget, GdkEventButton *event);

//GM
int check_floodfill(struct param_ p, int dir);		     
void floodfill(GtkWidget *widget, struct param_ p,int dir);		     
void floodfill_select( GtkWidget *widget, GdkEventButton *event);
static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event );
//GM
//AR
void get_points(GtkWidget *widget, GdkEventButton *event);
void aux_get_points(GtkWidget * widget, GdkEventButton * event);
static gboolean button_press_event_spline(GtkWidget *widget, GdkEventButton *event);
static gboolean button_press_event_spline(GtkWidget * widget, GdkEventButton * event);
//void draw_circle();
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
