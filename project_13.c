/*All global variables are declared in buttons.h
 * My other functions and button are also declared in buttons.h
 *Changes I have made 'drawing area size declared globally'.
 */
#include "buttons_13.c"
//#include "quicksort.c"
#include "math.h"
#include <gdk-pixbuf/gdk-pixbuf.h>


//#include "icon.c"//to be included;
//#include "flood_fill.c"
//#include "splines.c"

gint a=0,b=0;//this will remove the spot in top corner.



/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  
  cr = gdk_cairo_create(widget->window);
  
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  if(clear==1)
  {
  	cairo_set_source_rgb(cr,1,1,1);
    clear=0;
    return;
    //gtk_label_set_text (GTK_LABEL(cullabel),"White");
  }
  else
  	cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,3);
  cairo_rectangle(cr, p.x,p.y,a,b);
  R[p.x][p.y]=red;
  G[p.x][p.y]=green;
  B[p.x][p.y]=blue;

  if(stroke == 0)
	cairo_fill(cr);
  else
	cairo_stroke(cr);
	
  return TRUE;//return value don't have significance.
  
}
/* Draw a rectangle on the screen */
static void draw_brush( GtkWidget *widget,
                        gdouble    x,
                        gdouble    y)
{
 	if(SLINKY==1)
	{
		p.x=x;a=rec1;b=rec2;
 		p.y=y;
  		//gtk_widget_queue_draw_area(widget,x,y,1,1);
		cr = gdk_cairo_create(widget->window);
  		angle1 = 0.0  * (M_PI/180.0);  
  		angle2 = 360.0 * (M_PI/180.0);  
  		cairo_set_source_rgb(cr,red,green,blue);
  		cairo_set_line_width(cr,1);
  		radius = 50;
  		cairo_arc (cr, x, y, radius, angle1, angle2);
  		cairo_stroke (cr);
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
{	int i;
  if (( event->button == 1) && SPLINE==0 && FILL==0 && line==0 && complete==0 && CENTER!=1 && RADIUS!=1&&CIRCLE==0)
  {
    draw_brush (widget, event->x, event->y); 
    return TRUE;
  }
  
  if(SPLINE==1)
  {
    get_points_spline(widget, event);
    return TRUE;
  }
  
  if(CENTER==1)
  {
  	get_center(widget,event);
  	return TRUE;
  }
  
  if(RADIUS==1)
  {
  	get_radius(widget,event);
  	return TRUE;
  }
  
  if(FILL==1)
  {
    floodfill_select(widget,event);
    return TRUE;
  }
  
  if( complete == 1 ){
    if (event->button == 1 ) {
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count] = event->y;
        draw_brush (widget, event->x, event->y);
        if(glob.count>0){
          cr = gdk_cairo_create(widget->window);
	      cairo_set_source_rgb(cr,red,green,blue);
          cairo_set_line_width(cr, rec1);
          
          for( i = 0; i<=glob.count-1; i++ )
          {          
          cairo_move_to(cr, glob.coordx[glob.count], glob.coordy[glob.count]);
          cairo_line_to(cr, glob.coordx[i], glob.coordy[i]);
          int end_x = glob.coordx[glob.count];
          int end_y = glob.coordy[glob.count];
          int start_x = glob.coordx[i];
          int start_y = glob.coordy[i]; 
		  pixels[start_x][start_y]=1;
          R[start_x][start_y]=red;
		  G[start_x][start_y]=green;
		  B[start_x][start_y]=blue;
		  int distance = sqrt(pow((end_x - start_x),2) + pow((end_y - start_y),2)); 
		  double slope = ((double)(end_y-start_y)/(double)(end_x-start_x));
		  int i,j;
		  //printf("%d %d to %d %d\n",start_x,start_y,end_x,end_y);
		  for(i=start_x;i<=end_x;i++)
		  {
		  	j=(slope*i)-(slope*start_x)+(start_y);
		  	pixels[i][j]=1;
		  	pixels[i+1][j]=1;
		  	pixels[i-1][j]=1;
		  	pixels[i][j+1]=1;
		  	pixels[i][j-1]=1;
		  	pixels[i+2][j]=1;
		  	pixels[i-2][j]=1;
		  	pixels[i][j+2]=1;
		  	pixels[i][j-2]=1;
		  	/*pixels[i+3][j]=1;
		  	pixels[i-3][j]=1;
		  	pixels[i][j+3]=1;
		  	pixels[i][j-3]=1;*/
		  	R[i][j]=red;
		  	G[i][j]=green;
		  	B[i][j]=blue;
		  }
          cairo_stroke(cr); 
          
          
          
          }
          
          }
     glob.count++;
     }}
  if( line == 1 )
  {
    if (event->button == 1 ) 
    {
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count] = event->y;
        int end_x = event->x;
        int end_y = event->y;
        pixels[end_x][end_y]=1;
        R[end_x][end_y]=1;
		G[end_x][end_y]=1;
		B[end_x][end_y]=1;
        
        draw_brush (widget, event->x, event->y);
        if(glob.count>0)
        {
          cr = gdk_cairo_create(widget->window);
	      cairo_set_source_rgb(cr,red,green,blue);
          cairo_set_line_width(cr, rec1);
          cairo_move_to(cr, glob.coordx[glob.count], glob.coordy[glob.count]);
          cairo_line_to(cr, glob.coordx[glob.count-1], glob.coordy[glob.count-1]);
          line=0;
              gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
          int start_x = glob.coordx[glob.count-1];
          int start_y = glob.coordy[glob.count-1]; 
		  pixels[start_x][start_y]=1;
          R[start_x][start_y]=red;
		  G[start_x][start_y]=green;
		  B[start_x][start_y]=blue;
		  int distance = sqrt(pow((end_x - start_x),2) + pow((end_y - start_y),2)); 
		  double slope = ((double)(end_y-start_y)/(double)(end_x-start_x));
		  int i,j;
		 // printf("%d %d to %d %d\n",start_x,start_y,end_x,end_y);
		  for(i=start_x;i<=end_x;i++)
		  {
		  	j=(slope*i)-(slope*start_x)+(start_y);
		  	pixels[i][j]=1;
		  	pixels[i+1][j]=1;
		  	pixels[i-1][j]=1;
		  	pixels[i][j+1]=1;
		  	pixels[i][j-1]=1;
		  	pixels[i+2][j]=1;
		  	pixels[i-2][j]=1;
		  	pixels[i][j+2]=1;
		  	pixels[i][j-2]=1;
		  	R[i][j]=red;
		  	G[i][j]=green;
		  	B[i][j]=blue;
		  }
		  cairo_stroke_preserve(cr);
          cairo_stroke(cr);
        }
        glob.count++;   
     }
     
    }
    if(CIRCLE==1)
    {
    cr=gdk_cairo_create(widget->window);
    cairo_set_source_rgb(cr, red, green, blue);
    cairo_set_line_width(cr,1);
    cairo_rectangle(cr, event->x,event->y, rec1, rec2);
    int X=event->x;
    int Y=event->y;
    R[X][Y]=red;
    B[X][Y]=blue;
    G[X][Y]=green;
    cairo_stroke_preserve(cr);
    cairo_fill(cr);
    return TRUE;
    }
    
}

static gboolean motion_notify_event( GtkWidget *widget,
                                     GdkEventMotion *event,gpointer data)
{
  int x, y;
  GdkModifierType state;
  //  printf("Inside motion notify event\n");
  /*if ( event->is_hint )//I didn't understand its significance.
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {*/
    if(SPLINE!=1&&FILL!=1){
      x = event->x;
      y = event->y;
      state = event->state;
      if(p.x>0 && p.y>0){
  	  	pixels[p.x][p.y]=1;
		//printf("%d %d\n",p.x,p.y);
      }
		//		printf("Pixels updated\n");
      //      printf("Circle %d\n",CIRCLE);
		if(state & GDK_BUTTON1_MASK && CIRCLE==1){
		  //		  printf("Inside circle motion\n");
		  if(ERASER!=1){
		  circle_x[count_circle]=x;
		  circle_y[count_circle]=y;
		  count_circle++;
		  }
	       
		  else {
		    int i;
		    for(i=0;i<count_circle;i++){
		      if(sp_x[i]==event->x && sp_y[i]==event->y){
			int j;
			for(j=i;j<count_circle-1;j++){
			  circle_x[j]=circle_x[j+1];
			  circle_y[j]=circle_y[j+1];
  			}
		      }
		      count_circle--;
		    }
		  }
		  cr=gdk_cairo_create(widget->window);
		  cairo_set_line_width(cr,1);
		  cairo_set_source_rgb(cr, red, green, blue);

		  cairo_rectangle(cr, event->x,event->y, rec1, rec2);
		  int X=event->x;
  		  int Y=event->y;
		  //		  R[X][Y]=red;
		  //		  B[X][Y]=blue;
		  //		  G[X][Y]=green;
		  cairo_stroke_preserve(cr);
		  cairo_fill(cr);
		  return TRUE;
		}
    }
    if ( state & GDK_BUTTON1_MASK && CIRCLE!=1 ){
      draw_brush (widget, x, y);
      
    }
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
  //GtkWidget *drawing_area;
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
			R[i][j]=1;
			B[i][j]=1;
			G[i][j]=1;
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
  g_signal_connect (drawing_area, "button_press_event",
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
  
  
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}







