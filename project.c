#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
gint x2=5;

struct param_{
  gint x;
  gint y;
};

cairo_t *cr;

struct param_ p;

gint pixels[10000][10000];
/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;

/* Create a new backing pixmap of the appropriate size */
static gboolean configure_event( GtkWidget         *widget,
                                 GdkEventConfigure *event )
{
  if (pixmap)
    g_object_unref (pixmap);

  pixmap = gdk_pixmap_new (widget->window,
			   widget->allocation.width,
			   widget->allocation.height,
			   -1);
  gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);

  return TRUE;
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget      *widget,
			      GdkEventExpose *event )
{
  cr = gdk_cairo_create(widget->window);
  pixels[p.x][p.y]=1;
  printf("%d %d\n",p.x,p.y);
  int i,j;
  cairo_set_source_rgb(cr,1,0,0);
  cairo_paint(cr);
	cairo_set_source_rgb(cr,1,0.6,0.6);
	cairo_set_line_width(cr,1);
	cairo_rectangle(cr, p.x,p.y,3,3);
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
  gtk_widget_queue_draw_area(widget,x,y,3,3);
}

static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event ,gint x1)
{
printf("%f %f\n",event->x,event->y);
if (event->button == 1 && pixmap != NULL)
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
    
  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
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

  GtkWidget *green;
  
  
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "pencil_project");

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  g_signal_connect (window, "destroy",
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
  g_signal_connect (drawing_area, "configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (drawing_area, "motion_notify_event",
		    G_CALLBACK (motion_notify_event), GINT_TO_POINTER(10));
  g_signal_connect (drawing_area, "button_press_event",
		    G_CALLBACK (button_press_event), GINT_TO_POINTER(10));

  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK);

  /* .. And a quit button */
  green = gtk_button_new_with_label ("green");
  gtk_box_pack_start (GTK_BOX (vbox), green, FALSE, FALSE, 0);
  green = gtk_button_new_with_label ("blue");
  gtk_box_pack_start (GTK_BOX (vbox), green, FALSE, FALSE, 0);
  g_signal_connect_swapped (green, "clicked",
			    G_CALLBACK (gtk_widget_destroy),
			    window);
  //gtk_widget_show (green);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
