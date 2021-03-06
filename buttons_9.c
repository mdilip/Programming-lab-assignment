#include "buttons.h"

void line_me (GtkWidget *widget, gpointer data)
{
 if(LINE == 0)
   LINE = 1;
 else
   LINE = 0;
}

void complete_me (GtkWidget *widget, gpointer data)
{
 if(COMPLETE == 0)
   COMPLETE = 1;
 else
   COMPLETE = 0;
}

void stroke_me (GtkWidget *widget, gpointer data)
{
 stroke = 1;
}

void unstroke_me (GtkWidget *widget, gpointer data)
{
 stroke = 0;
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
   //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_PENCIL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
      //change end
  sprintf(buf,"%s\n",(char* )data);
  switch (buf[0]){
     case '0':
       red=0;green=0;blue=0;clear=0;
       break;
     case '1':
       red=0;green=1;blue=1;clear=0;
       break;
     case '2':
       red=0;green=1;blue=0;clear=0;
       break;
     case '3':
       red=0;green=0;blue=1;clear=0;
       break;
     case '4':
       red=1;green=0;blue=0;clear=0;
       break;
     case '5':
       red=1;green=1;blue=1;clear=1;
       break;
     case '7':
       red=0.6;green=0.4;blue=0.1;clear=0;
       break;
     case '8':
       red=0.4;green=0.4;blue=0.4;clear=0;
       break;
     case '9':
       red=1;green=1;blue=0;clear=0;
       break;
     case 'a':
       red=0.7;green=0;blue=1;clear=0;
       break;
     case 'b':
       red=1;green=0;blue=1;clear=0;
       break;
     case 'c':
       red=1;green=1;blue=1;clear=0;
       //rec1=10;rec2=10;
   //Changing cursor
   GdkWindow *win = gtk_widget_get_window( GTK_WIDGET( widget ) );
   GdkCursor *cur;
   cur = gdk_cursor_new( GDK_BOX_SPIRAL );
   gdk_window_set_cursor( win, cur );
   gdk_cursor_unref( cur );
   while( gtk_events_pending() )
      gtk_main_iteration();
      //change end       
       }
}

GtkWidget *newVerticalbox (gint A, gint B,
		     gint C, gint D, gint E )
{
  GtkWidget *Vbox;
  GtkWidget *Hbox;
  GtkWidget *label;
  Vbox = gtk_vbox_new (A, B);
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
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (stroke_me), NULL);
  
  button = gtk_button_new_with_label ("Full");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show (button);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (unstroke_me), NULL); 
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
  g_signal_connect_swapped (button, "clicked", G_CALLBACK(button_press_event_fill),drawing_area); 
  
  button = gtk_button_new_with_label ("Line");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (line_me), NULL);
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
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (complete_me), NULL);
  gtk_widget_show (button);
  
  button = gtk_button_new_with_label ("Save");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  //gboolean gdk_pixbuf_save (GdkPixbuf *pixbuf, "project","png",NULL);
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
  g_signal_connect_swapped(button,"clicked",G_CALLBACK(aux_get_points),drawing_area);
 
  button = gtk_button_new_with_label ("Get Function");
  gtk_box_pack_start (GTK_BOX (Hbox), button, C, D, E);
  gtk_widget_show(button);
   g_signal_connect_swapped(button,"clicked",G_CALLBACK(button_press_event_spline),drawing_area);
 
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


