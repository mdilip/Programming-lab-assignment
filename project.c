#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
gint x2=5;
gint red=0,green=0,blue=0,rec1=3,rec2=3;
void colour_me (GtkWidget *widget,gpointer data);
void colour_me (GtkWidget *widget,gpointer data)
{
  char buf[1];
  sprintf(buf,"%s\n",(char* )data);
  //printf("%c,%c",buf[0],buf[1]);
  switch (buf[0]){
     case '0':
       red=0;green=0;blue=0;
       rec1=3;rec2=3;
       break;
     case '1':
       red=0;green=1;blue=1;rec1=3;rec2=3;
       break;
     case '2':
       red=0;green=1;blue=0;rec1=3;rec2=3;
       break;
     case '3':
       red=0;green=0;blue=1;rec1=3;rec2=3;
       break;
     case '4':
       red=1;green=1;blue=1;
       rec1=10;rec2=10;
       break;
     case '5':
       red=1;green=0;blue=0;rec1=3;rec2=3;
       break;
     case '6':
       red=1;green=1;blue=0;rec1=3;rec2=3;
       break;
     case '7':
       red=1;green=0;blue=1;
       }
}
GtkWidget *horizontal_box (gint A, gint B,
		     gint C, gint D, gint E,gint first);

struct param_{
  gint x;
  gint y;
};

cairo_t *cr;

struct param_ p;

gint pixels[10000][10000];
/* Backing pixmap for drawing area */

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget      *widget,
			      GdkEventExpose *event )
{
  cr = gdk_cairo_create(widget->window);
  pixels[p.x][p.y]=1;
  printf("%d %d\n",p.x,p.y);
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
	cairo_set_source_rgb(cr,red,green,blue);
	cairo_set_line_width(cr,1);
	cairo_rectangle(cr, p.x,p.y,rec1,rec2);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
  return FALSE;
}

/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y,gint x1)
{
 int i, j;
 p.x=x;
 p.y=y;
  gtk_widget_queue_draw_area(widget,x,y,rec1,rec2);
}

static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event ,gint x1)
{
printf("%f %f\n",event->x,event->y);
if (event->button == 1/* && pixmap != NULL*/)
    draw_brush (widget, event->x, event->y,x1);

  return TRUE;
}

static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event,gpointer data,gint x1)
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
    }
    
  if (state & GDK_BUTTON1_MASK /*&& pixmap != NULL*/)
    draw_brush (widget, x, y,x1);
  
  return TRUE;
}

void quit ()
{
  exit (0);
}

int main( int   argc, 
          char *argv[] )
{
int i,j;
for(i=0;i<200;i++)
	for(j=0;j<200;j++)
	pixels[i][j]=0;
	
	
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

  g_signal_connect (GTK_WINDOW(window), "destroy",
                    G_CALLBACK (quit), NULL);

  /* Create the drawing area */

  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), 200, 200);
  //cr = gdk_cairo_create(drawing_area->window);
  gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_show (drawing_area);

  /* Signals used to handle backing pixmap */

  g_signal_connect (drawing_area, "expose_event",
		    G_CALLBACK (expose_event),NULL);
 /* g_signal_connect (drawing_area, "configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (drawing_area, "motion_notify_event",
		    G_CALLBACK (motion_notify_event), GINT_TO_POINTER(10));
  g_signal_connect (drawing_area, "button_press_event",
		    G_CALLBACK (button_press_event), GINT_TO_POINTER(10));

  gtk_widget_set_events (drawing_area, /*GDK_EXPOSURE_MASK
			 |*/ /*GDK_LEAVE_NOTIFY_MASK
			 |*/ GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			/* | GDK_POINTER_MOTION_HINT_MASK*/);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, TRUE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, FALSE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);                             
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
