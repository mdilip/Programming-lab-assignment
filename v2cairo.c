/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

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
  //cairo_t *cr;
  //  printf("Hello\n");
  cr = gdk_cairo_create(widget->window);
  pixels[p.x][p.y]=1;
  printf("%d %d\n",p.x,p.y);
  int i,j;
  //for(i=0;i<1000 ;i++){
  //for(j=0;j<1000;j++){
  //  if(pixels[i][j]==1){
  cairo_set_source_rgb(cr,1,0,0);
  cairo_paint(cr);
	cairo_set_source_rgb(cr,1,0.6,0.6);
	cairo_set_line_width(cr,1);
	cairo_rectangle(cr, p.x,p.y,3,3);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
	// }
	// }
	// }
  //cairo_show_text(cr, "Aditi");

//return FALSE;
/* gdk_draw_drawable (widget->window,
		     widget->style->fg_gc[gtk_widget_get_state (widget)],
		     pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);*/

  return FALSE;
}

/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y,gint x1)
{

int i, j;
/*for(i=0;i<10;i++){
  p.x=x-3i;
  p.y=y+i;
  
  }
  */
p.x=x;
p.y=y;
  gtk_widget_queue_draw_area(widget,x,y,3,3);
  /*
  GdkRectangle update_rect;
update_rect.x=x-1;
  update_rect.y = y - 1;
  update_rect.width = x2;
  update_rect.height = x2;
  int i;*/
	//printf("Hello\n");
  //  cairo_t *cr;
  //  printf("HelloDraw\n");
  //cr = gdk_cairo_create(widget->window);
  //  cairo_rectangle(cr,x,y,5,5);
//cairo_set_source_rgb(cr,0,0,0);
//cairo_paint(cr);
  //cairo_destroy(cr);
  //gtk_widget_queue_draw_area(widget,x,y,5,5);
  //pixels[x][y]=1;
  /*
  cairo_t *cr;
  cr=gdk_cairo_create(widget->window);
  cairo_move_to(cr, 50, 30);
  cairo_show_text(cr,"Aditi");
  gtk_widget_queue_draw(widget);
  */

  /*for(i=0;i<10;i++){
  gdk_draw_rectangle (pixmap,
		      widget->style->black_gc,
		      TRUE,
		      update_rect.x-3i, update_rect.y-i,
		      update_rect.width, update_rect.height);
		     
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x-3i, update_rect.y-i,
		              update_rect.width, update_rect.height);
		              }
		              */
		              
  
  /*
  gdk_draw_rectangle (pixmap,
		      widget->style->black_gc,
		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget, 
		              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
gdk_draw_rectangle (pixmap,
		      widget->style->black_gc,
		      TRUE,
		      185, 165,
		      update_rect.width, update_rect.height);
		      
		      gtk_widget_queue_draw_area (widget, 
		              185, 165,
		              update_rect.width, update_rect.height);
  */
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
for(i=0;i<200;i++){
	for(j=0;j<200;j++){
	pixels[i][j]=0;
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
  button = gtk_button_new_with_label ("Quit");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

  g_signal_connect_swapped (button, "clicked",
			    G_CALLBACK (gtk_widget_destroy),
			    window);
  gtk_widget_show (button);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
