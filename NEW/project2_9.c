#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <math.h>
#include "quicksort.c"
gint x2=5;
gfloat red=0,green=0,blue=0,rec1=3,rec2=3;
int handler_id;
int sp_x[1000];
int sp_y[1000];
float a[1000];
float b[1000];
float c[1000];
float h[1000];
gint count =0;
void colour_me (GtkWidget *widget,gpointer data);
void colour_me (GtkWidget *widget,gpointer data){
char buf[1];
sprintf(buf,"%s\n",(char* )data);
  switch (buf[0]){
     case '0':
       red=0;green=0;blue=0;
       rec1=5;rec2=5;
       break;
     case '1':
       red=1;green=0;blue=1;rec1=5;rec2=5;
       break;
     case '2':
       red=0.7;green=1;blue=0;rec1=5;rec2=5;
       break;
     case '3':
       red=0;green=0;blue=1;rec1=5;rec2=5;
       break;
     case '4':
       red=1;green=1;blue=1;
       rec1=5;rec2=5;
       break;
     case '5':
       red=1;green=0;blue=0;rec1=5;rec2=5;
       break;
     case '6':
       red=1;green=1;blue=0;rec1=5;rec2=5;
       break;
     case '7':
       red=1;green=0;blue=1;
       }
}
GtkWidget *horizontal_box (gint A, gint B, gint C, gint D, gint E, gint first);

struct param_{
  GtkWidget* widget;
  gint x;
  gint y;
};

cairo_t *cr;

struct param_ p;
int check = 0;

gint pixels[10000][10000];
int visited[10000][10000];


static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  cr = gdk_cairo_create(widget->window);
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,3);
  cairo_rectangle(cr, p.x,p.y,rec1,rec2);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  return FALSE;
}



void floodfill(GtkWidget *widget, struct param_ p);
void floodfill(GtkWidget *widget, struct param_ p)
{

	if(pixels[p.x][p.y]==1||visited[p.x][p.y]==1||p.x>200||p.y>200||p.x<1||p.y<1)
		return ;
	
	else
	{
		struct param_ p1, p2, p3, p4;
		//printf("flood called\n");
		visited[p.x][p.y]=1;
		cr = gdk_cairo_create(widget->window);
		cairo_set_source_rgb(cr,red,green,blue);
  		cairo_set_line_width(cr,1);
  		printf("%d %d\n",p.x,p.y);
  		cairo_rectangle(cr,p.x,p.y,5,5);
 		cairo_stroke_preserve(cr);
  		cairo_fill(cr);
  		//gtk_widget_queue_draw_area(widget,p.x,p.y,3,3);

  		
  		p1.x = p.x+1; p2.x = p.x-1; p3.x = p.x; p4.x = p.x;
  		p1.y = p.y; p2.y = p.y; p3.y = p.y+1; p4.y = p.y-1; 
  		
  		floodfill(widget, p3);
  		floodfill(widget, p4);
  		floodfill(widget, p1);
  		floodfill(widget, p2);
  		return;
  	}
}


void floodfill_select( GtkWidget *widget, GdkEventButton *event);
void floodfill_select( GtkWidget *widget, GdkEventButton *event) 
{
	p.x = event->x;
	p.y = event->y;
	floodfill(widget, p);
	g_signal_handler_unblock(widget, handler_id);
}


static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event )
{
  g_signal_handler_block(widget, handler_id);
  g_signal_connect(widget, "button_press_event", G_CALLBACK (floodfill_select),GINT_TO_POINTER(10));
  return TRUE;
}
void get_points(GtkWidget * widget, GdkEventButton * event);
void aux_get_points( GtkWidget * widget, GdkEventButton *event)
{
  count=0;
   g_signal_handler_block(widget, handler_id);
  g_signal_connect(widget,"button_press_event",G_CALLBACK(get_points),NULL);
  //  return TRUE;
}


void get_points(GtkWidget *widget, GdkEventButton *event)
{
  printf("Get points called\n");
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  //printf("%d %d\n",p.x,p.y);
  cairo_rectangle(cr,event->x,event->y,1,1);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  sp_x[count]=event->x;
  sp_y[count]=event->y;
  count ++;
}



static gboolean button_press_event_spline(GtkWidget *widget, GdkEventButton *event)
{
  int i,j;
  printf("Entered spline\n");
  printf("Count : %d\n",count);
  quicksort(count, sp_x,sp_y);
  for(i=0;i<count-1;i++){
    h[i]=sqrt(pow((sp_x[i+1]-sp_x[i]),2)+pow((sp_y[i+1]-sp_y[i]),2));
    printf("%f\n",h[i]);
  }
  c[0]=1/(2*pow(h[0],2))*(sp_y[0]-2*sp_y[1]+sp_y[2]);
  for(i=1;i<count-1;i++){
      c[i]=-h[i-1]*c[i-1]/h[i] + (h[i]*sp_y[i-1]-(h[i-1]+h[i])*sp_y[i]+h[i-1]*sp_y[i+1])/(h[i-1]*pow(h[i],2));
    }
  for(i=0;i<count-1;i++){
    a[i]=sp_y[i];
    b[i]=1/h[i]*(sp_y[i+1]-sp_y[i])-h[i]*c[i];
  }
  for(i=0;i<count-1;i++){
    for(j=sp_x[i];j<=sp_x[i+1];j++){
      int y= a[i]+b[i]*(j-sp_x[i])+c[i]*pow((j-sp_x[i]),2);
      printf("%d\n",y);
      cr=gdk_cairo_create(widget->window);
      cairo_set_source_rgb(cr,red, green, blue);
      cairo_set_line_width(cr,1);
      cairo_rectangle(cr,j, y,1,1);
      cairo_stroke_preserve(cr);
      cairo_fill(cr);
    }
  }
  g_signal_handler_unblock(widget, handler_id);
}
/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget, gdouble x, gdouble y, gint x1)
{
	int i, j;
	p.x=x;
	p.y=y;
 	gtk_widget_queue_draw_area(widget,x,y,rec1,rec2);
}

static gboolean button_press_event( GtkWidget *widget, GdkEventButton *event ,gint x1)
{
	
	printf("%f %f\n",event->x,event->y);
	if (event->button == 1)
    	draw_brush (widget, event->x, event->y,x1);
  	return TRUE;
  	
}

static gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event,gpointer data,gint x1)
{
  int x, y;
  GdkModifierType state;


  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      state = event->state;
       if(p.x>0 && p.y>0)
  	pixels[p.x][p.y]=1;
    }
    
  if (state & GDK_BUTTON1_MASK /*&& pixmap != NULL*/)
    draw_brush (widget, x, y,x1);
  
  return TRUE;
}

void quit ()
{
  exit (0);
}

int main( int   argc, char *argv[] )
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{
			pixels[i][j]=0;
			visited[i][j]=0;
		}
	}
	
  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *vbox;
  GtkWidget *button;
  
  
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "pencil_project");

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  g_signal_connect (GTK_WINDOW(window), "destroy", G_CALLBACK (quit), NULL);

  /* Create the drawing area */

  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 200, 200);
  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_show (drawing_area);

  g_signal_connect (drawing_area, "expose_event", G_CALLBACK (expose_event),NULL);


  g_signal_connect (drawing_area, "motion_notify_event", G_CALLBACK (motion_notify_event), GINT_TO_POINTER(10));
  handler_id = g_signal_connect (drawing_area, "button_press_event", G_CALLBACK (button_press_event), GINT_TO_POINTER(10));

  gtk_widget_set_events (drawing_area, /*GDK_EXPOSURE_MASK
			 |*/ /*GDK_LEAVE_NOTIFY_MASK
			 |*/ GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			/* | GDK_POINTER_MOTION_HINT_MASK*/);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, TRUE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, FALSE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  
  //Paint bucket button	 

  button = gtk_button_new_with_label ("Fill");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (button_press_event_fill), drawing_area);

  //Give points for function

  button=gtk_button_new_with_label("Select Points");
  gtk_box_pack_start(GTK_BOX(vbox),button,FALSE, FALSE, 0);
  g_signal_connect_swapped(button, "clicked",G_CALLBACK( aux_get_points),drawing_area);

  //Get function

  button=gtk_button_new_with_label("Get Function");
  gtk_box_pack_start(GTK_BOX(vbox),button,FALSE, FALSE, 0);
  g_signal_connect_swapped(button,"clicked",G_CALLBACK(button_press_event_spline), drawing_area);
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
GtkWidget *horizontal_box (gint A, gint B,
		     gint C, gint D, gint E,gint first)
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label (first?"black":"eraser");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"0":"4"));
  
  button = gtk_button_new_with_label (first?"purple":"Red");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"1":"5"));
  
  button = gtk_button_new_with_label (first?"green":"Yellow");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"2":"6"));
  
  button = gtk_button_new_with_label (first?"blue":"Pink");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"3":"7"));
  
  return Hbox;
}
