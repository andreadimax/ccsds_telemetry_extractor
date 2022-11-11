#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>



//acquisizione comandi da passare a CTP

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
	FILE *tmp;
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	tmp=fopen("temp.txt","w");
	fprintf(tmp,"%s",entry_text);
	fclose(tmp);
}


//Scrittura su file ext.txt del comando premuto

static void comando1( GtkWidget *widget, gpointer data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"1");
	fclose(ext);
	//invio=1;
}

/*static void comando2( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"2");
	fclose(ext);
}

static void comando3( GtkWidget *widget,
                   gpointer   data )
{
	//GtkWidget *dialog;
	
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"3");
	fclose(ext);
}

static void comando4( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"4");
	fclose(ext);
}

static void comando5( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"5");
	fclose(ext);
}

static void comando6( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"6");
	fclose(ext);
}

static void comando7( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"7");
	fclose(ext);
}

static void comando8( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"8");
	fclose(ext);
}

static void comando9( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"9");
	fclose(ext);
}

static void comando10( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"10");
	fclose(ext);
}

static void comando11( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"11");
	fclose(ext);
}

static void comando12( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"12");
	fclose(ext);
}*/







int main(int argc, char *argv[]) {

  int P1=16,P2=12,B1=75,B2=73,T1=25,T2=23,T3=32;
  int serial_number;
  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *button;
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *window1;
  GtkWidget *vbox;
  GtkWidget *frame1;
  GtkWidget *frame2;
  GtkWidget *Hbox;
  GtkWidget *Hbox2;
  GtkWidget *Hbox3;
  GtkWidget *radioB;
  GtkWidget *entry1;
  GtkWidget *label1;
  


  GtkWidget *comm1;
  GtkWidget *comm2;
  GtkWidget *comm3;
  GtkWidget *comm4;
  GtkWidget *comm5;
  GtkWidget *comm6;
  GtkWidget *comm7;
  GtkWidget *comm8;
  GtkWidget *comm9;
  GtkWidget *comm0;


  GSList *group;

  gtk_init(&argc, &argv);


////----------------------------------inizializzazioni------------------------//
serial_number= serial_init();
if (serial_number<0){
	printf("Wrong opening HL\n");
	window1=gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_title (GTK_WINDOW (window1),"Error");
	gtk_container_set_border_width (GTK_CONTAINER (window1),10);
	table=gtk_table_new(2,1,TRUE);
	gtk_container_add (GTK_CONTAINER (window1), table);
	button=gtk_button_new_with_label("Exit");
	g_signal_connect_swapped (button, "clicked",G_CALLBACK (gtk_widget_destroy),window1);
	gtk_table_attach(GTK_TABLE(table),button,0,1,1,2,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show  (button);
	frame = gtk_frame_new (" Error ");
	label = gtk_label_new ("\n     Unable to open HL Serial Port    \n");
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_table_attach(GTK_TABLE(table),frame,0,1,0,1,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show_all (window1);
	gtk_main();
	return 0;
	sleep(1);
}


//---------------------------------------------------------------------------------//





  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 750, 450);
  gtk_window_set_title(GTK_WINDOW(window), "Interface");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  Hbox = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(window), Hbox);

  frame1 = gtk_frame_new("Command Window");
  gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(Hbox), frame1);
  
  frame2 = gtk_frame_new("Telemetry Data");
  gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_IN);
  gtk_container_add(GTK_CONTAINER(Hbox), frame2);

  vbox = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(frame1), vbox);

  Hbox2 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox), Hbox2);

  Hbox3 = gtk_hbox_new(TRUE, 1);

  
  
  radioB = gtk_radio_button_new_with_label (NULL, "Command via HL");
  comm1 = gtk_button_new_with_label("command1");
  comm2 = gtk_button_new_with_label("command2");
  comm3 = gtk_button_new_with_label("command3");
  comm4 = gtk_button_new_with_label("command4");
  comm5 = gtk_button_new_with_label("command5");
  comm6 = gtk_button_new_with_label("command6");
  comm7 = gtk_button_new_with_label("command7");
  comm8 = gtk_button_new_with_label("command8");
  comm9 = gtk_button_new_with_label("command9");
  comm0 = gtk_button_new_with_label("command0");

  gtk_box_pack_start(GTK_BOX(Hbox2), radioB, TRUE, TRUE, 0);
  group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radioB));
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radioB), TRUE);
  radioB = gtk_radio_button_new_with_label (group, "Command via TNC");
  gtk_box_pack_start(GTK_BOX(Hbox2), radioB, TRUE, TRUE, 0);

  label1 = gtk_label_new("Set new Time");
  entry1 = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(Hbox3), label1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox3), entry1, TRUE, TRUE, 0);

  
  
  gtk_box_pack_start(GTK_BOX(vbox), comm1, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm2, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm3, TRUE, TRUE, 0);
  
  gtk_box_pack_start(GTK_BOX(vbox), Hbox3, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), comm4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm5, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm6, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm7, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm8, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm9, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), comm0, TRUE, TRUE, 0);


//Connessione bottoni-segnali

g_signal_connect(comm1,"clicked",G_CALLBACK(comando1),NULL);
//gtk_table_attach(GTK_TABLE(table),button,1,2,0,1,GTK_FILL,GTK_FILL,10,10);
g_signal_connect (entry1, "activate",G_CALLBACK (enter_callback),entry1);







//lettura dati seriale




  

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

