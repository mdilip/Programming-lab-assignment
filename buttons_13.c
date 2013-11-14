#include "buttons_13.h"

void line_me (GtkWidget *widget, gpointer data)
{
 if(line == 0)
  {
   line = 1;
   //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
     //change end 
   complete = 0;
    SPLINE=0;
    FILL=0;
    ERASER=0;
    CENTER=0; 
    gtk_label_set_text (GTK_LABEL(butlabel),"Line");
 }
 else
 {
   line = 0;
    gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
 }
 glob.count = 0;
}

void complete_me (GtkWidget *widget, gpointer data)
{
 if(complete == 0)
 {  
 	complete = 1;
 	//Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
      //change end
    line = 0;
    SPLINE=0;
    FILL=0;
    ERASER=0;
    CENTER=0;
    gtk_label_set_text (GTK_LABEL(butlabel),"Complete");
  } 
 else
 {
   complete = 0;
  gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
 }
 glob.count = 0;
}

void stroke_me (GtkWidget *widget, gpointer data)
{
 stroke = 1;
 gtk_label_set_text (GTK_LABEL(butlabel),"Stroke");
}

void unstroke_me (GtkWidget *widget, gpointer data)
{
 stroke = 0;
 line = 0;
   complete = 0;
    SPLINE=0;
    FILL=0;
    CENTER=0;
    SLINKY=0;
 gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
}

void red_decrease(GtkWidget *widget, gpointer data)
{
 if( red >=0 && red <= 1 )
  red = red - 0.1;
 return;
}

void green_decrease(GtkWidget *widget, gpointer data)
{
 if( green >=0 && green <= 1 )
  green = green - 0.1;
 return;
}

void blue_decrease(GtkWidget *widget, gpointer data)
{
 if( blue >=0 && blue <= 1 )
  blue = blue - 0.1;
 return;
}

void red_increase(GtkWidget *widget, gpointer data)
{
 if( red >=0 && red <= 1 )
  red = red + 0.1;
 return;
}

void green_increase(GtkWidget *widget, gpointer data)
{
 if( green >=0 && green <= 1 )
  green = green + 0.1;
 return;
}

void blue_increase(GtkWidget *widget, gpointer data)
{
 if( blue >=0 && blue <= 1 )
  blue = blue + 0.1;
 return;
}

void thickness_decrease(GtkWidget *widget, gpointer data)
{   if( rec1 > 0 && rec2 > 0 ) 
	rec1=rec1-1; rec2=rec2-1;
	return;
}

void thickness_increase(GtkWidget *widget, gpointer data)
{
    if( rec1 < height && rec2 < height )
	rec1=rec1+1; rec2=rec2+1;
	return;
}

void colour_me (GtkWidget *widget,gpointer data)
{
  char buf[1];
  
  if(FILL==0)
  {
   //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
   		gtk_main_iteration();
   //change end
  }
  sprintf(buf,"%s\n",(char* )data);
  switch (buf[0]){
     case '0':
       red=0;green=0;blue=0;clear=0;
       ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Black");
       break;
     case '1':
       red=0;green=1;blue=1;clear=0;
       ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Aqua");
       break;
     case '2':
       red=0;green=1;blue=0;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Green");
       break;
     case '3':
       red=0;green=0;blue=1;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Blue");
       break;
     case '4':
       red=1;green=0;blue=0;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Red");
       break;
     case '5':
       clear=1;
       ERASER=0;
       int i,j;
      
       for(i=0;i<breadth;i++){
	 for(j=0;j<height;j++){
	   pixels[i][j]=0;
	   visited[i][j]=0;
	   R[i][j]=1;
	   B[i][j]=1;
	   G[i][j]=1;
	 }
       }
        gtk_widget_queue_draw_area(drawing_area,0,0,breadth, height);
       gtk_label_set_text (GTK_LABEL(cullabel),"Clear All");
       break;
     case '7':
       red=0.6;green=0.4;blue=0.1;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"brown");
       break;
     case '8':
       red=0.4;green=0.4;blue=0.4;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"Grey");
       break;
     case '9':
       red=1;green=1;blue=0;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"yellow");
       break;
     case 'a':
       red=0.7;green=0;blue=1;clear=0;
              ERASER=0;
       gtk_label_set_text (GTK_LABEL(cullabel),"purple");
       break;
     case 'b':
       red=1;green=0;blue=1;clear=0;ERASER=1;
       gtk_label_set_text (GTK_LABEL(cullabel),"pink");
       break;
     case 'c':
       red=1;green=1;blue=1;clear=0;
       ERASER=1;
       gtk_label_set_text (GTK_LABEL(cullabel),"Eraser");
       
       //rec1=10;rec2=10;
   //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur2;
   cur2 = gdk_cursor_new( GDK_BOX_SPIRAL );
   gdk_window_set_cursor( win, cur2 );
   gdk_cursor_unref( cur2 );
   while( gtk_events_pending() )
      gtk_main_iteration();
      //change end  
      break;     
       }
}

GtkWidget *newVerticalbox (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Vbox;
  GtkWidget *Hbox;
  GtkWidget *label;
  Vbox = gtk_vbox_new (A, B);
  
  cullabel = gtk_label_new ("Black");
  gtk_misc_set_alignment (GTK_MISC (cullabel), 0, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), cullabel, FALSE, FALSE, 0);
  gtk_widget_show (cullabel);
  
  butlabel = gtk_label_new ("Normal");
  gtk_misc_set_alignment (GTK_MISC (butlabel), 0, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), butlabel, FALSE, FALSE, 0);
  gtk_widget_show (butlabel);
  
  label = gtk_label_new ("Thickness");//gtk_widget_set_usize (label, 110, 20);
  gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), label, FALSE, FALSE, 0);
  gtk_widget_show (label);  
  Hbox = newhorizontalbox1 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  label = gtk_label_new ("Colour_proportion");
  gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), label, FALSE, FALSE, 0);
  gtk_widget_show (label);
  Hbox = newhorizontalbox2 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox3 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox4 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  label = gtk_label_new ("E_V_E_N_T_S");
  gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), label, FALSE, FALSE, 0);
  gtk_widget_show (label);
  Hbox = newhorizontalbox5 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox6 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox7 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox8 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox9 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  Hbox = newhorizontalbox10 (FALSE, 0, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (Vbox), Hbox, C, D, E);
  gtk_widget_show (Hbox);
  return Vbox;
}
/* newhorizontalbox(12345678) below functions 
 * represent the row of the button
 * keep the call back of button you want on
 * respective button
 */
GtkWidget *newhorizontalbox1 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("-");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (thickness_decrease), NULL);
  
  button = gtk_button_new_with_label ("+");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (thickness_increase), NULL); 
  return Hbox;
}

GtkWidget *newhorizontalbox2 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Red-");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (red_decrease), NULL);
  
  button = gtk_button_new_with_label ("Red+");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (red_increase), NULL); 
  return Hbox;
}

GtkWidget *newhorizontalbox3 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);

  button = gtk_button_new_with_label ("Green-");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (green_decrease), NULL);

  button = gtk_button_new_with_label ("Green+");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button); 
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (green_increase), NULL);
  return Hbox;
}

GtkWidget *newhorizontalbox4 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);

  button = gtk_button_new_with_label ("Blue-");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (blue_decrease), NULL);
  button = gtk_button_new_with_label ("Blue+");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (blue_increase), NULL); 
  return Hbox;
}



GtkWidget *newhorizontalbox5 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Stroke");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect(button, "clicked", G_CALLBACK (stroke_me), NULL);
  
  button = gtk_button_new_with_label ("Normal");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect(button, "clicked", G_CALLBACK (unstroke_me), NULL); 
  return Hbox;
}

GtkWidget *newhorizontalbox6 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Fill");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", G_CALLBACK(button_press_event_fill),drawing_area); 
  
  button = gtk_button_new_with_label ("Line");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  g_signal_connect(button, "clicked", G_CALLBACK (line_me), NULL);
  gtk_widget_show (button); 
  return Hbox;
}
GtkWidget *newhorizontalbox7 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Complete");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  g_signal_connect(button, "clicked", G_CALLBACK (complete_me), NULL);
  gtk_widget_show (button);
  
  button = gtk_button_new_with_label ("Circle");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  g_signal_connect(button, "clicked", G_CALLBACK (button_press_event_circle_gm), drawing_area);
  gtk_widget_show (button); 
  
  return Hbox;
}

GtkWidget *newhorizontalbox8 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  button = gtk_button_new_with_label ("Select Points");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect_swapped(button,"clicked",G_CALLBACK(aux_get_points_spline),drawing_area);
  button = gtk_button_new_with_label ("Get Function");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect(button,"clicked",G_CALLBACK(button_press_event_spline),drawing_area);
  return Hbox;
}

GtkWidget *newhorizontalbox9 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Slinky On");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect(button,"clicked",G_CALLBACK(slinky),drawing_area);
 
  button = gtk_button_new_with_label ("Slinky Off");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect(button,"clicked",G_CALLBACK(slinky_off),drawing_area);
 
  return Hbox;
}

GtkWidget *newhorizontalbox10 (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  
  button = gtk_button_new_with_label ("Approx Circle");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect(button,"clicked",G_CALLBACK(aux_get_points_circle),drawing_area);
 
  button = gtk_button_new_with_label ("Get circle");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
  g_signal_connect(button,"clicked",G_CALLBACK(button_press_event_circle),drawing_area);
 
  return Hbox;
}


GtkWidget *horizontal_box (gint A, gint B,
		     gint C, gint D, gint E,gint first)
{
  GtkWidget *Hbox;
  GtkWidget *button;
  Hbox = gtk_hbox_new (A, B);
  button = gtk_button_new_with_label (first?"Pencil":"Brown");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"0":"7"));
  button = gtk_button_new_with_label (first?"Aqua":"Grey");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"1":"8"));
  button = gtk_button_new_with_label (first?"Green":"Yellow");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"2":"9"));
  button = gtk_button_new_with_label (first?"Blue":"Purple");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"3":"a"));
  button = gtk_button_new_with_label (first?"Red":"Pink");
  gtk_box_pack_start ( GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"4":"b"));
  button = gtk_button_new_with_label (first?"Clearall":"Eraser");
  gtk_box_pack_start ( GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect (button, "clicked", 
      G_CALLBACK(colour_me), (gpointer) (first?"5":"c"));
  return Hbox;
}




/*****************************CIRCLE**********************************/

void slinky( GtkWidget *widget, GdkEventButton *event )
{
	//Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
      //change end
	SLINKY = 1;
	CENTER = 0;
  line=0;
  complete=0;
  stroke=0;
  SPLINE=0;
  FILL=0;
	gtk_label_set_text (GTK_LABEL(butlabel),"Slinky");
	return ;
}

void slinky_off( GtkWidget *widget, GdkEventButton *event )
{
	SLINKY = 0;
	stroke=0;
		gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
	return ;
}

void button_press_event_circle_gm( GtkWidget *widget, GdkEventButton *event )
{
  //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
     //change end 
  CENTER = 1;
  line=0;
  complete=0;
  stroke=0;
  SPLINE=0;
  FILL=0;
  SLINKY=0;	
  gtk_label_set_text (GTK_LABEL(butlabel),"Circle");
  
  //  printf("%d",CENTER);
  return ;
}


void get_center(GtkWidget *widget, GdkEventButton *event)
{
  //  printf("Get center called\n");
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  int X=event->x;
  int Y=event->y;
  cairo_rectangle(cr,event->x,event->y,1,1);
  //cairo_stroke_preserve(cr);
  cairo_fill(cr);
  center_x = event->x;
  center_y = event->y;
  CENTER=0;
  RADIUS=1;
  return;
}

void get_radius(GtkWidget *widget, GdkEventButton *event)
{
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  cairo_rectangle(cr,event->x,event->y,1,1);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  
  radius = sqrt(pow((center_x - event->x),2) + pow((center_y - event->y),2));
   
  cr = gdk_cairo_create(widget->window);
  angle1 = 0.0  * (M_PI/180.0);  
  angle2 = 360.0 * (M_PI/180.0);  
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  cairo_arc (cr, center_x, center_y, radius, angle1, angle2);
  cairo_stroke (cr);
  cairo_set_source_rgb(cr,R[center_x][center_y],G[center_x][center_y],B[center_x][center_y]);
  cairo_set_line_width(cr,1);
  cairo_rectangle(cr,center_x,center_y,1,1);
  cairo_rectangle(cr,center_x,center_y+1,1,1);
  cairo_rectangle(cr,center_x,center_y-1,1,1);
  cairo_rectangle(cr,center_x+1,center_y,1,1);
  cairo_rectangle(cr,center_x-1,center_y,1,1);
  cairo_stroke_preserve(cr);
  cairo_set_source_rgb(cr,R[center_x][center_y],G[center_x][center_y],B[center_x][center_y]);
  cairo_fill(cr);
  
  angle = (double)(0.001/radius);
  int x,y,i;
  int max=(2* M_PI) / angle;
  for(i=0;i<max;i++)
  {
  	x = radius*cos((i*angle)+angle) + center_x;
  	y = radius*sin((i*angle)+angle) + center_y;
  	pixels[x][y]=1;
	R[x][y]=red;
	B[x][y]=blue;
	G[x][y]=green;

  
  }

  
  center_x = 0;
  center_y = 0;
  RADIUS = 0;
  		gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
	
  return;
}


/******************************FLOOD FILL**********************************/


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
	if(check_floodfill(p,dir)==1||visited[p.x][p.y]==CUR_VISITED+1||p.x>800||p.y>800||p.x<4||p.y<4)
		return ;
	
	else
	{
		struct param_ p1, p2, p3, p4;
		//printf("floodfill called\n");
		visited[p.x][p.y]++;
		cr = gdk_cairo_create(widget->window);
		cairo_set_source_rgb(cr,red,green,blue);
		R[p.x+2][p.y+2]=red;
		G[p.x+2][p.y+2]=green;
		B[p.x+2][p.y+2]=blue;
		R[p.x][p.y]=R[p.x+1][p.y+1]=red;
		R[p.x+2][p.y+2]=R[p.x][p.y+1]=red;
		R[p.x][p.y+2]=R[p.x+1][p.y]=red;
		R[p.x+1][p.y+2]=R[p.x+2][p.y]=R[p.x+2][p.y+1]=red;
		G[p.x][p.y]=G[p.x+1][p.y+1]=green;
		G[p.x+2][p.y+2]=G[p.x][p.y+1]=green;
		G[p.x][p.y+2]=G[p.x+1][p.y]=green;
		G[p.x+1][p.y+2]=G[p.x+2][p.y]=G[p.x+2][p.y+1]=green;
		B[p.x][p.y]=B[p.x+1][p.y+1]=blue;
		B[p.x+2][p.y+2]=B[p.x][p.y+1]=blue;
		B[p.x][p.y+2]=B[p.x+1][p.y]=B[p.x+1][p.y+2]=B[p.x+2][p.y]=B[p.x+2][p.y+1]=blue;
		//		printf("%f\n",R[p.x][p.y]);
  		cairo_set_line_width(cr,1);
  		//printf("%d %d\n",p.x,p.y);
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
	p.x = event->x;
	p.y = event->y;
	CUR_VISITED=visited[p.x][p.y];
	floodfill(widget, p,0);
	//FILL=0;
	gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
}


static gboolean button_press_event_fill( GtkWidget *widget, GdkEventButton *event )
{
	FILL=1;
	CIRCLE=0;
	SPLINE=0;
	SLINKY=0;
	GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_TARGET );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
	gtk_label_set_text (GTK_LABEL(butlabel),"Fill");
  return TRUE;
}


/*******************************SPLINES*****************************************/

void aux_get_points_spline( GtkWidget * widget, GdkEventButton *event)
{
  count_sp=0;
  SPLINE=1;
  //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
     //change end 
  gtk_label_set_text (GTK_LABEL(butlabel),"Spline");
  CENTER=0;
  line=0;
  complete=0;
  stroke=0;
  FILL=0;
  SLINKY=0;
  CIRCLE=0;
  g_signal_connect(widget,"button_press_event",G_CALLBACK(get_points_spline),NULL);
 
}

void aux_get_points_circle(GtkWidget* widget, GdkEventButton *event)
{
   count_circle=0;
  CIRCLE=1;
  gtk_label_set_text (GTK_LABEL(butlabel),"Approx circle");
  SPLINE=0;
  CENTER=0;
  line=0;
  complete=0;
  stroke=0;
  FILL=0;
  SLINKY=0;
}



void get_points_spline(GtkWidget *widget, GdkEventButton *event)
{
  cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_set_line_width(cr,1);
  cairo_rectangle(cr,event->x,event->y,rec1,rec2);
  int X=event->x;
  int Y=event->y;
  R[X][Y]=red;
  B[X][Y]=blue;
  G[X][Y]=green;
  //  cairo_stroke_preserve(cr);
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
      }
      count_sp--;
    }
  }
}





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
      }
      count_circle--;
    }
  }
}

float distance (float x1,float y1,float x2,float y2){
  float dist = sqrt((x1-x2)*(x1-x2)+ (y1-y2)*(y1-y2));
  return dist;
}



static gboolean button_press_event_spline(GtkWidget *widget, GdkEventButton *event)
{
  //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
     //change end 
  
  int i,j;
  if(SPLINE==0)
  	return FALSE;
  //  printf("Entered spline\n");
  //  printf("Count : %d\n",count_sp);
  quicksort(count_sp, sp_x,sp_y);
  for(i=0;i<count_sp-1;i++){
    h[i]=sqrt(pow((sp_x[i+1]-sp_x[i]),2)+pow((sp_y[i+1]-sp_y[i]),2));
    //    printf("%f\n",h[i]);
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
      cairo_set_source_rgb(cr,red, green, blue);
      cairo_set_line_width(cr,1);
      cairo_rectangle(cr,j, y,1,1);
      cairo_fill(cr);

    }
  }
  SPLINE=0;
  gtk_label_set_text (GTK_LABEL(butlabel),"Pencil");
  cairo_set_line_width(cr, 1);
  cairo_set_source_rgb(cr,red,green,blue);
  cairo_translate(cr, CENTRE_X,CENTRE_Y);
  cairo_stroke_preserve(cr);
  cairo_set_source_rgb(cr,0,0,0);
  cairo_fill(cr);
  CIRCLE=0;

}


//Function that returns the largest distance of a point from the point at ith position

float max_dist(int i){
  int j;
  float dist = distance(circle_x[i],circle_y[i],circle_x[0],circle_y[0]);
  //  printf("%f\n",dist);
  for(j=0;j<count_circle;j++){
    if( distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j])>dist)
      dist= distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j]);
  }
  return dist;
}

//Function that returns the x coordinate of the point at largest distance
int maxx_dist(int i){
  int j;
  int maxX=circle_x[0];
  float dist = distance(circle_x[i],circle_y[i],circle_x[0],circle_y[0]);
  for(j=0;j<count_circle;j++){
    if( distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j])>dist){
      dist= distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j]);
      maxX=circle_x[j];
    }
  }
  return maxX;
}


//Function that returns the y coordinate of the point which is at larget distance

int maxy_dist(int i){
  int j;
  int maxY=circle_y[0];
  float dist = distance(circle_x[i],circle_y[i],circle_x[0],circle_y[0]);
  for(j=0;j<count_circle;j++){
    if( distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j])>dist){
      dist= distance(circle_x[i],circle_y[i],circle_x[j],circle_y[j]);
      maxY=circle_y[j];
    }
  }
  return maxY;
}


static gboolean button_press_event_circle(GtkWidget *widget,GdkEventButton *event)
{
  //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
     //change end 
  if(CIRCLE==0)
    return;
  if(count_circle<=0)
    return;
  float centre_x=0, centre_y=0;
  float radius;
  //printf("%d\n",count_circle);
  int i,j,k;
 
    //To erase the old circle
  for(i=0;i<count_circle;i++){
  cairo_set_line_width(cr, 2);
  if(circle_x[i]>0&&circle_y[i]>0){
  cairo_set_source_rgb(cr,R[circle_x[i]][circle_y[i]],G[circle_x[i]][circle_y[i]],B[circle_x[i]][circle_y[i]]);
  pixels[circle_x[i]][circle_y[i]]=0;
  }
  //  printf("PIXELS : %f\n",R[circle_x[i]][circle_y[i]]);
  cairo_rectangle(cr, circle_x[i],circle_y[i],rec1, rec2);
  cairo_set_source_rgb(cr,R[circle_x[i]][circle_y[i]],G[circle_x[i]][circle_y[i]],B[circle_x[i]][circle_y[i]]);
    cairo_stroke_preserve(cr);
  cairo_fill(cr);
  }
     
  //New algo to compute the centre of the random circle -- Go Aditi ! :D
  radius = max_dist(0)/2;
    //  printf("Radius :%f\n",radius);
  i=0;
  while(i<count_circle){
    radius=  (radius + max_dist(i)/2)/2;
    i+=10;
  }
  //  printf("Radius : %f\n",radius);
  i=0;
   centre_x = (circle_x[0]+maxx_dist(0))/2;
  while(i<count_circle){
    centre_x = (centre_x + (circle_x[i]+ maxx_dist(i))/2)/2; 
    i+=10;
  }
   centre_y = (circle_y[0]+maxy_dist(0))/2;
  while(i<count_circle){
    centre_y = (centre_y + (circle_y[i]+ maxy_dist(i))/2)/2; 
    i+=10;
  }

  cairo_set_line_width(cr, rec1);
  cairo_set_source_rgb(cr,red,green,blue);

  cairo_arc(cr,centre_x,centre_y,radius,0,2 * M_PI);

  cairo_stroke_preserve(cr);
  cairo_set_source_rgb(cr,0,0,0);

  //CIRCLE=0;
  count_circle=0;
   double angle = (double)(0.001/radius);
  int m=(2* M_PI) / angle;
  int x1,y1;
  
  for(i=0;i<m;i++)
  {
  	x1 = radius*cos((i*angle)+angle) + centre_x;
  	y1 = radius*sin((i*angle)+angle) + centre_y;
  	pixels[x1][y1]=1;
	R[x1][y1]=red;
	B[x1][y1]=blue;
	G[x1][y1]=green;
	
  
  }
  

}


