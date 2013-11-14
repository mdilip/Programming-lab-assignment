/*All global variables are declared in buttons.h
 * My other functions and button are also declared in buttons.h
n *Changes I have made 'drawing area size declared globally'.
 *Edits to be made to this :
--The fill part change has to be made.
--Dilip's line code has to be integrated into this
--Gayathri's circle also has to be a part of the project
 */
#include "buttons.c"
#include "quicksort.c"
#include "math.h"
//#include "icon.c"//to be included;
//#include "floodfill.c"
//#include "splines.c"

gint a=0,b=0;//this will remove the spot in top corner.


/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event )
{
  cr = gdk_cairo_create(widget->window);
  
  int i,j;
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  cairo_set_source_rgb(cr,red,green,blue);
  //cairo_set_line_width(cr,3);
  cairo_rectangle(cr, p.x,p.y,rec1,rec2);
  //cairo_stroke_preserve(cr);
  // cairo_fill(cr);
  if(stroke == 0)
	cairo_fill(cr);
  else
	cairo_stroke(cr);
  //  cairo_surface_finish(cr);
  return FALSE;//return value don't have significance.
  
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
  printf("Inside button press\n");
  if (( event->button == 1)&&SPLINE==0&&FILL==0 ){
    draw_brush (widget, event->x, event->y);
    printf("Function 1 called\n");
      return TRUE;
  }
  if(SPLINE==1){
    get_points_spline(widget, event);
    return TRUE;
  }
  if(FILL==1){
    floodfill_select(widget, event);
    return TRUE;
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
    if(SPLINE!=1&&FILL!=1){
      x = event->x;
      y = event->y;
      state = event->state;
      if(p.x>0 && p.y>0){
  	  	pixels[p.x][p.y]=1;
		printf("%d %d\n",p.x,p.y);
		printf("Pixels updated\n");
		if(CIRCLE==1){
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
	//	count_sp--;
		      }
		      count_circle--;
		    }
		  }
		}
    //}
    
  if ( state & GDK_BUTTON1_MASK ){
    draw_brush (widget, x, y);
    //draw_brush (widget, x-1,y-1);
    // draw_brush(widget,x+1,y);
  }
  
  return TRUE;
      }
    }
}



void aux_get_points_spline( GtkWidget * widget, GdkEventButton *event)
{
  count_sp=0;
  printf("Aux points\n");
  SPLINE=1;
  printf("Handler id : %d\n",handler_id);
  //  g_signal_handler_block(widget, 29);
  g_signal_connect(widget,"button_press_event",G_CALLBACK(get_points_spline),NULL);
  //  SPLINE=0;
  //  return TRUE;
}

void aux_get_points_circle(GtkWidget* widget, GdkEventButton *event)
{
  //  printf("Aux called \n");
  count_circle=0;
  CIRCLE=1;
  //  g_signal_connect(widget, "button_press_event",G_CALLBACK(get_points_circle),NULL);
}



void get_points_spline(GtkWidget *widget, GdkEventButton *event)
{
  printf("Get points called\n");
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  //printf("%d %d\n",p.x,p.y);
  cairo_rectangle(cr,event->x,event->y,rec1,rec2);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  if(ERASER!=1){
  sp_x[count_sp]=event->x;
  sp_y[count_sp]=event->y;
  count_sp ++;
  }
  else {
    int i;
    for(i=0;i<count_sp;i++){
      if(sp_x[i]==event->x && sp_y[i]==event->y){
	int j;
	for(j=i;j<count_sp-1;j++){
	  sp_x[j]=sp_x[j+1];
	  sp_y[j]=sp_y[j+1];
	}
	//	count_sp--;
      }
      count_sp--;
    }
  }
}




  //  cairo_destroy(cr);

//def 1
void get_points_circle(GtkWidget *widget, GdkEventButton *event)
{
  cr=gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr, red, green, blue);
  cairo_set_line_width(cr,1);
  cairo_rectangle(cr, event->x,event->y,rec1, rec2);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  if(ERASER!=1)
    {
      circle_x[count_circle]=event->x;
      circle_y[count_circle]=event->y;
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
	//	count_sp--;
      }
      count_circle--;
    }
  }
}

float distance (float x1,float y1,float x2,float y2){
  return sqrt(pow((x1-x2),2)+ pow((y1-y2),2));
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
      //      cairo_destroy(cr);
    }
  }
  //  cairo_surface_finish(cr);
  //  g_signal_handler_unblock(widget, handler_id);
  SPLINE=0;
}

static gboolean button_press_event_circle(GtkWidget *widget,GdkEventButton *event)
{
  printf("%d\n",count_circle);
  int i,j,k;
  int no_of_points= 15;
  for(i=0;i<count_circle;i+=no_of_points){
    for(j=i+count_circle/no_of_points;j<count_circle;j+=no_of_points){
      float min = 100000;
      for(k=j+count_circle/no_of_points;k<count_circle;k+=no_of_points){
	//generating all the circle possible for 3 points chosen
	float yDelta_a=circle_y[j]-circle_y[i];
	float xDelta_a=circle_x[j]-circle_x[i];
	float yDelta_b=circle_y[k]-circle_y[j];
	float xDelta_b=circle_x[k]-circle_x[j];
	float aSlope = yDelta_a/xDelta_a;
	float bSlope = yDelta_b/xDelta_b;
	float centre_x=aSlope*bSlope*(circle_y[i]-circle_y[k]) + bSlope * (circle_x[i] + circle_x[j]) - aSlope*(circle_x[j]+circle_x[k])/2*(bSlope-aSlope);
	float centre_y= -1 * (centre_x - (circle_x[i] + circle_x[j])/2)/aSlope + (circle_y[i] + circle_y[j])/2;
	float rad = distance(circle_x[i],circle_y[i],centre_x,centre_y);
	int l;
	float sum=0;
      	for(l=0;l<count_circle;l+=no_of_points){
	  sum+=fabs(rad-distance(circle_x[l],circle_y[l],centre_x,centre_y));
	}
	if(sum<min){
	  min=sum;
	  CENTRE_X=centre_x;
	  CENTRE_Y=centre_y;
	  RAD=rad;
	}
      }
    }
  }
  
  CIRCLE=0;
  for(i=0;i<count_circle;i++){
  cr=gdk_cairo_create(widget->window);
  cairo_set_line_width(cr, 1);
  cairo_set_source_rgb(cr, 1, 1, 1);
  pixels[circle_x[i]][circle_y[i]]=0;
  cairo_rectangle(cr, circle_x[i],circle_y[i],rec1, rec2);
  cairo_set_source_rgb(cr, 1,1, 1);
  cairo_fill(cr);
  }
  cairo_arc(cr, CENTRE_X,CENTRE_Y,RAD,0,2 * M_PI);
  cairo_stroke_preserve(cr);
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
  printf("Helo\n");
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

  g_signal_connect (drawing_area, "expose_event",
		    G_CALLBACK (expose_event),NULL);
 /* g_signal_connect (drawing_area, "configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (drawing_area, "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);//made them null as it don't have significance.
  handler_id = g_signal_connect (drawing_area, "button_press_event",
		    G_CALLBACK (button_press_event), NULL);

  gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
			 |GDK_LEAVE_NOTIFY_MASK
			 | GDK_BUTTON_PRESS_MASK
			 |GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, TRUE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  button = horizontal_box ( FALSE, 0, TRUE, TRUE, 0, FALSE );
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);   
  
   button = gtk_button_new_with_label ("Fill");
  gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (button_press_event_fill), drawing_area);
 
                           
  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}









  //  cairo_destroy(cr);

//def 1




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
  //  printf("%d\n",check_floodfill(p,dir));
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
		//		cairo_destroy(cr);

  		p1.x = p.x+3; p2.x = p.x-3; p3.x = p.x; p4.x = p.x;
  		p1.y = p.y; p2.y = p.y; p3.y = p.y+3; p4.y = p.y-3; 
  		
  		floodfill(widget, p1,0);
  		floodfill(widget, p2,1);
  		floodfill(widget, p3,2);
  		floodfill(widget, p4,3);
  		return;
  	}
	//	cairo_surface_finish(cr);
  FILL=0;
}


void floodfill_select( GtkWidget *widget, GdkEventButton *event) 
{
	
	printf("Floodfill_select called\n");
	p.x = event->x;
	p.y = event->y;
	CUR_VISITED=visited[p.x][p.y];
	floodfill(widget, p,0);
	//	g_signal_handler_unblock(widget, handler_id);

}

static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event )
{
	printf("HI");
	
	//Changing cursor
    GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
    GdkCursor *cur;
    cur = gdk_cursor_new( GDK_TARGET );
    gdk_window_set_cursor( win, cur );
    gdk_cursor_unref( cur );
    while( gtk_events_pending() )
       gtk_main_iteration();
	
	//	printf("Handler id : %d\n",handler_id);
	//	g_signal_handler_block(widget, handler_id);
  //	FILL=1;
  //	g_signal_connect(widget, "button_press_event", G_CALLBACK (floodfill_select), GINT_TO_POINTER(10));
  return TRUE;
}

