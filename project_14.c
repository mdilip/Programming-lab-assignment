/*
 *All global variables are declared in buttons.h
 *Other functions and button are also declared in buttons.h
 */
#include "buttons_14.c"

/*This function is to add icon to the app*/
GdkPixbuf *create_pixbuf(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error); //create an icon for app
   if(!pixbuf) 
   {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }     
   return pixbuf;
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  
  cr = gdk_cairo_create(widget->window);
  
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);    //paint the drawing area with white colour
  if(clear==1)
  {
  	cairo_set_source_rgb(cr,1,1,1);
    clear=0;
    return;
  }
  else
  	cairo_set_source_rgb(cr,red,green,blue);   	// set the colour of drawing with global variables red,green,blue.
  	cairo_set_line_width(cr,3);
  	cairo_rectangle(cr, p.x,p.y,a,b);   //p.x,p.y is position of cursor and a,b global variables(size fo rectangle)
  	R[p.x][p.y]=red;
  	G[p.x][p.y]=green;
  	B[p.x][p.y]=blue;

  if(stroke == 0)
	cairo_fill(cr);  //fills normally.
  else
	cairo_stroke(cr);  //stroke will be active when ever stroke is ON.
	
  return TRUE; 
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


/*Function executes only if there is button press event*/
static gboolean button_press_event( GtkWidget      *widget,
                                    GdkEventButton *event )
{	
	int i;
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
  
  	if( complete == 1 )
  	{
    	if (event->button == 1 ) 
    	{
        	glob.coordx[glob.count] = event->x;         //stores the coordinates of present point
        	glob.coordy[glob.count] = event->y;
        	draw_brush (widget, event->x, event->y);
        	if(glob.count>0)
        	{
          		cr = gdk_cairo_create(widget->window);
	      		cairo_set_source_rgb(cr,red,green,blue);
          		cairo_set_line_width(cr, rec1);  
          			//moves to present point  
          			for( i = 0; i<=glob.count-1; i++ )                     
          			{ 
					   cairo_move_to(cr, glob.coordx[glob.count], glob.coordy[glob.count]);
         			   //line is made to previous point.
          			   cairo_line_to(cr, glob.coordx[i], glob.coordy[i]);
					   int end_x = glob.coordx[glob.count];
					   //present point coordinates stored in end_x.
					   int end_y = glob.coordy[glob.count];
					   int start_x = glob.coordx[i];
					   //coordinates of previously selected points.
					   int start_y = glob.coordy[i]; 
					   pixels[start_x][start_y]=1;
					   R[start_x][start_y]=red;
					   G[start_x][start_y]=green;
					   B[start_x][start_y]=blue;
					   int distance = sqrt(pow((end_x - start_x),2) + pow((end_y - start_y),2)); 
					   double slope = ((double)(end_y-start_y)/(double)(end_x-start_x));
					   int i,j;
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
					  cairo_stroke(cr); 
          			}
          		} glob.count++;
          }
     }

  if( line == 1 )
  {
    if (event->button == 1 ) 
    {
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count] = event->y;
        int end_x = event->x;
        // coordinates of present points
        int end_y = event->y;
        pixels[end_x][end_y]=1;
        R[end_x][end_y]=1;
		G[end_x][end_y]=1;
		B[end_x][end_y]=1;
        // this function shows the presently selected point.
        draw_brush (widget, event->x, event->y);
        if(glob.count>0)
        {
          cr = gdk_cairo_create(widget->window);
	      cairo_set_source_rgb(cr,red,green,blue);
	      //line colour is set
          cairo_set_line_width(cr, rec1);
          // line width is set rec1 is global variable
          // moved to present point
          cairo_move_to(cr, glob.coordx[glob.count], glob.coordy[glob.count]);
          // line is made to previous point
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
    if(SPLINE!=1&&FILL!=1)
    {
      x = event->x;
      y = event->y;
      state = event->state;
      if(p.x>0 && p.y>0)
  	  	pixels[p.x][p.y]=1;
	if(state & GDK_BUTTON1_MASK && CIRCLE==1)
	{
		  if(ERASER!=1)
		  {
		  	circle_x[count_circle]=x;
		  	circle_y[count_circle]=y;
		  	count_circle++;
		  }
	       
		  else 
		  {
		    int i;
		    for(i=0;i<count_circle;i++)
		    {
		      if(sp_x[i]==event->x && sp_y[i]==event->y)
		      {
				int j;
				for(j=i;j<count_circle-1;j++)
				{
				  circle_x[j]=circle_x[j+1];
				  circle_y[j]=circle_y[j+1];
	  			}
			  }count_circle--;	  
		    }
		  }
 	cr=gdk_cairo_create(widget->window);
 	cairo_set_line_width(cr,1);
 	cairo_set_source_rgb(cr, red, green, blue);
	cairo_rectangle(cr, event->x,event->y, rec1, rec2);
	int X=event->x;
  	int Y=event->y;
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
	return TRUE;
	}
    }
    
    if ( state & GDK_BUTTON1_MASK && CIRCLE!=1 )
    {
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
  gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("dilip.jpg"));
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
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area), breadth, height);
  //breadth,height global variables in buttons.h
  gtk_box_pack_start (GTK_BOX (hbox), drawing_area, TRUE, TRUE, 0);
  gtk_widget_show (drawing_area);

  /* Signals used to handle backing pixmap */

  g_signal_connect (drawing_area, "expose_event",
		    G_CALLBACK (expose_event),NULL);

  /* Event signals */

  g_signal_connect (drawing_area, "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);
  g_signal_connect (drawing_area, "button_press_event",
		    G_CALLBACK (button_press_event), NULL);

  gtk_widget_set_events (drawing_area, GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK );
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, TRUE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, FALSE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);   
  
  
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}







