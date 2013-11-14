/*All global variables are declared in buttons.h
 * My other functions and button are also declared in buttons.h
 *Changes I have made 'drawing area size declared globally'.
 */
#include "buttons.c"
#include "quicksort.c"
#include "math.h"
#include <gdk-pixbuf/gdk-pixbuf.h>


//#include "icon.c"//to be included;
//#include "floodfill.c"
//#include "splines.c"

gint a=0,b=0;//this will remove the spot in top corner.

static gboolean draw_circle( GtkWidget *widget, GdkEventButton *event );


/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  cr = gdk_cairo_create(widget->window);
  
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  cairo_set_source_rgb(cr,red,green,blue);
   if( COMPLETE == 1 || LINE == 1 )
   { 
     cairo_save(cr);
     cr1 = gdk_cairo_create(widget->window);
     cairo_set_line_width(cr1, 1);
     int i, j;
     if( COMPLETE == 1 && LINE != 1 )
     {
     	for (i = 0; i <= glob.count - 1; i++ ) 
     	{
     		for (j = 0; j <= glob.count - 1; j++ ) 
     		{
            	cairo_move_to(cr1, glob.coordx[i], glob.coordy[i]);
          		cairo_line_to(cr1, glob.coordx[j], glob.coordy[j]);
          	}
        }
     }
     else
     {
     	i = 0;
     	while(i < glob.count-1 )
     	{
        	cairo_move_to(cr1, glob.coordx[i], glob.coordy[i]);
        	i++;
      		cairo_line_to(cr1, glob.coordx[i], glob.coordy[i]);
      	}
     }
     glob.count = 0;
     cairo_stroke(cr1); 
     cairo_restore(cr);
   }
   else
   {
      cairo_rectangle(cr, p.x, p.y, a, b);
  	  if(stroke == 0)
      	 cairo_fill(cr);
  	  else
		 cairo_stroke(cr);
   }
  
}

/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
	if( clear == 1 )
	{
   		a=breadth;b=height;p.x=0;p.y=0;
   		gtk_widget_queue_draw_area(widget,0,0,breadth,height);
 	}
 	else
 	{
 		p.x=x;a=rec1;b=rec2;
 		p.y=y;
  		gtk_widget_queue_draw_area(widget,x,y,rec1,rec2);
  	}
}

static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event )
{	
  if (( event->button == 1) && SPLINE==0 && FILL==0 && LINE!=1 && COMPLETE!=1)
  {
    draw_brush (widget, event->x, event->y); 
    return TRUE;
  }
  
  if(SPLINE==1)
  {
    get_points(widget,event);
    return TRUE;
  }
  
  if(FILL==1)
  {
    floodfill_select(widget,event);
    return TRUE;
  }
  
  if( COMPLETE == 1 )
  {
    if (event->button == 1 ) 
    {
        cr = gdk_cairo_create(widget->window);
  		cairo_set_source_rgb(cr,red,green,blue);
  		cairo_set_line_width(cr,1);
  		cairo_rectangle(cr,event->x,event->y,1,1);
  		cairo_stroke_preserve(cr);
  		cairo_fill(cr);
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count++] = event->y;
    }
    if (event->button == 3) 
        gtk_widget_queue_draw(widget);
  }
  
  if( LINE == 1 )
  {
   cairo_save(cr);
    if (event->button == 1 ) 
    {
    	cr = gdk_cairo_create(widget->window);
  		cairo_set_source_rgb(cr,red,green,blue);
  		cairo_set_line_width(cr,1);
  		cairo_rectangle(cr,event->x,event->y,1,1);
  		cairo_stroke_preserve(cr);
  		cairo_fill(cr);
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count++] = event->y;
    }
    if (event->button == 3) 
        gtk_widget_queue_draw(widget);
    cairo_restore(cr);
  } 

}

static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event,gpointer data)
{
  int x, y;
  GdkModifierType state;

  /*if ( event->is_hint )//I didn't understand its significance.
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {*/
      x = event->x;
      y = event->y;
      state = event->state;
      if(p.x>0 && p.y>0)
  	  	pixels[p.x][p.y]=1;
    //}
    
  if ( state & GDK_BUTTON1_MASK )
    draw_brush (widget, x, y);
  
  return TRUE;
}




void aux_get_points( GtkWidget * widget, GdkEventButton *event)
{
  count_sp=0;
 // printf("Aux points\n");
  SPLINE=1;
  g_signal_connect(widget,"button_press_event",G_CALLBACK(get_points),NULL);
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
  sp_x[count_sp]=event->x;
  sp_y[count_sp]=event->y;
  count_sp ++;
}


static gboolean button_press_event_spline(GtkWidget *widget, GdkEventButton *event)
{
  int i,j;
  printf("Entered spline\n");
  printf("Count : %d\n",count_sp);
  quicksort(count_sp, sp_x,sp_y);
  for(i=0;i<count_sp-1;i++){
    h[i]=sqrt(pow((sp_x[i+1]-sp_x[i]),2)+pow((sp_y[i+1]-sp_y[i]),2));
    printf("%f\n",h[i]);
  }
  c[0]=1/(2*pow(h[0],2))*(sp_y[0]-2*sp_y[1]+sp_y[2]);
  for(i=1;i<count_sp-1;i++){
      c[i]=-h[i-1]*c[i-1]/h[i] + (h[i]*sp_y[i-1]-(h[i-1]+h[i])*sp_y[i]+h[i-1]*sp_y[i+1])/(h[i-1]*pow(h[i],2));
    }
  for(i=0;i<count_sp-1;i++){
    a1[i]=sp_y[i];
    b1[i]=1/h[i]*(sp_y[i+1]-sp_y[i])-h[i]*c[i];
  }
  for(i=0;i<count_sp-1;i++){
    for(j=sp_x[i];j<=sp_x[i+1];j++){
      float y= a1[i]+b1[i]*(j-sp_x[i])+c[i]*pow((j-sp_x[i]),2);
      printf("Debug2\n");
      //      printf("%d\n",y);
      //      cr=gdk_cairo_create(widget->window);
      printf("Debug 1\n");
      cairo_set_source_rgb(cr,red, green, blue);
      cairo_set_line_width(cr,1);
      cairo_rectangle(cr,j, y,1,1);
      //cairo_stroke_preserve(cr);
      cairo_fill(cr);
    }
  }
  //  cairo_surface_finish(cr);
 // g_signal_handler_unblock(widget, handler_id_pencil);
  SPLINE=0;
}


static gboolean draw_circle( GtkWidget *widget, GdkEventButton *event )
{
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,1,1,1);
   cairo_set_line_width(cr,1);


  cairo_arc(cr, 330, 60, 40, 0, 2*M_PI);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);

  return TRUE;

}




void quit ()
{
  exit (0);
}

int main( int   argc, 
          char *argv[] )
{
  GtkWidget *window;
  GtkWidget *drawing_area;
  GtkWidget *vbox;
  GtkWidget *v1box;
  GtkWidget *hbox;
  GtkWidget *button;
  
  gtk_init (&argc, &argv);
  
  int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{
			pixels[i][j]=0;
			visited[i][j]=0;
		}
	}
	

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "pencil_project");

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  g_signal_connect (GTK_WINDOW(window), "destroy",
                    G_CALLBACK (quit), NULL);

  hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);
  v1box = newVerticalbox ( FALSE, 0, TRUE, TRUE, 0 );
  gtk_box_pack_start (GTK_BOX (hbox), v1box, FALSE, FALSE, 0);
  gtk_widget_show (v1box);
  
    /* Create the drawing area */
    
  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), breadth, height);//breadth,height global variables in buttons.h
  //cr = gdk_cairo_create(drawing_area->window);
  gtk_box_pack_start (GTK_BOX (hbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_show (drawing_area);

  /* Signals used to handle backing pixmap */

  g_signal_connect (drawing_area, "expose_event",
		    G_CALLBACK (expose_event),NULL);
 /* g_signal_connect (drawing_area, "configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (drawing_area, "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);//made them null as it don't have significance.
  handler_id_pencil = g_signal_connect (drawing_area, "button_press_event",
		    G_CALLBACK (button_press_event), NULL);

  gtk_widget_set_events (drawing_area, /*GDK_EXPOSURE_MASK
			 |*/ /*GDK_LEAVE_NOTIFY_MASK
			 |*/ GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			/* | GDK_POINTER_MOTION_HINT_MASK*/);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, TRUE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, FALSE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);   
  
  button = gtk_button_new_with_label ("Circle");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (draw_circle), drawing_area);
 
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}

int check_floodfill(struct param_ p, int dir)
{
	switch(dir)
	{
		case 0: 
		if(pixels[p.x][p.y]==1||pixels[p.x-1][p.y]==1||pixels[p.x-2][p.y]==1)
			return 1;
			else return 0;
			break;
		case 1: 
		if(pixels[p.x][p.y]==1||pixels[p.x+1][p.y]==1||pixels[p.x+2][p.y]==1)
			return 1;
			else return 0;
			break;
		case 2: 
		if(pixels[p.x][p.y]==1||pixels[p.x][p.y-1]==1||pixels[p.x][p.y-2]==1)
			return 1;
			else return 0;
			break;
		case 3: 
		if(pixels[p.x][p.y]==1||pixels[p.x][p.y+1]==1||pixels[p.x][p.y+2]==1)
			return 1;
			else return 0;
			break;
		default : return 0;	
	}
}


void floodfill(GtkWidget *widget, struct param_ p,int dir)
{
	if(check_floodfill(p,dir)==1||visited[p.x][p.y]==CUR_VISITED+1||p.x>800||p.y>800||p.x<3||p.y<3)
		return ;
	
	else
	{
		struct param_ p1, p2, p3, p4;
		//printf("floodfill called\n");
		visited[p.x][p.y]++;
		cr = gdk_cairo_create(widget->window);
		cairo_set_source_rgb(cr,red,green,blue);
  		cairo_set_line_width(cr,1);
  		printf("%d %d\n",p.x,p.y);
  		cairo_rectangle(cr,p.x,p.y,3,3);
 		cairo_stroke_preserve(cr);
  		cairo_fill(cr);

  		p1.x = p.x+3; p2.x = p.x-3; p3.x = p.x; p4.x = p.x;
  		p1.y = p.y; p2.y = p.y; p3.y = p.y+3; p4.y = p.y-3; 
  		
  		floodfill(widget, p1,0);
  		floodfill(widget, p2,1);
  		floodfill(widget, p3,2);
  		floodfill(widget, p4,3);
  		return;
  	}
}



void floodfill_select( GtkWidget *widget, GdkEventButton *event) 
{
	//Changing cursor
  /* GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_TARGET );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
    */  //change end     
	//printf("Floodfill_select called\n");
	p.x = event->x;
	p.y = event->y;
	CUR_VISITED=visited[p.x][p.y];
	floodfill(widget, p,0);
	FILL=0;
}


static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event )
{
	FILL=1;
  return TRUE;
}





