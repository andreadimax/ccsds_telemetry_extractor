#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <unistd.h>

#define PI 3.1415





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

//acquisizione linea da cui passare i comandi

static void set_HL( GtkWidget *widget,
                            GtkWidget *entry )
{
	FILE *port;
	port=fopen("port.txt","w");
	fprintf(port,"0");
	fclose(port);
}

static void set_TNC( GtkWidget *widget,
                            GtkWidget *entry )
{
	FILE *port;
	port=fopen("port.txt","w");
	fprintf(port,"1");
	fclose(port);
}

//Scrittura su file ext.txt del comando premuto

static void comando1( GtkWidget *widget, gpointer data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"1");
	fclose(ext);
}

static void comando2( GtkWidget *widget,
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
}

static void comando13( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"13");
	fclose(ext);
}

static void comando14( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"14");
	fclose(ext);
}

static void comando15( GtkWidget *widget,
                   gpointer   data )
{
	FILE *ext;
	ext=fopen("ext.txt","w");
	fprintf(ext,"15");
	fclose(ext);
}







int main(int argc, char *argv[]) {


FILE *inv;
FILE *tmp;
FILE *seriale;

//definizione variabili
  
	int serial_number,serial_number1;
	int pid;
	int r1=0,r2=0,r3=0,r4=0,r5=0;
	int invio=0, port=0;
	int i,j,g=0,nn=0;

//definizione variabili pacchetti

	char pack_out_HL[23]={0,}; //command HL
	char pack_out_TNC[38]={0,}; //command TNC
	
	char set[18]={0,};		//setting option


unsigned char tnc_init_part[6]={0x1B,0x40,0x4B,0xFF,0xC0,0x0D}; //setting for TNC for KISS AX.25 protocol
unsigned char tnc_init_part1[6]={0x1B,0x54,0x32,0x30,0x30,0x0D};
unsigned char tnc_init_part2[4]={0x1B,0x40,0x4B,0x0D};

	char receive_HL_start[3]={'C','2','G'}; //header HL received packets
	char command_HL_start[3]={'G','2','C'}; //header HL commands

unsigned char command_ax25_start[18]={0xC0,0x00,'C','T','P','C','T','P',0xE0,'G','S','S','G','S','S',0x26,0x03,0xF0}; //header TNC commands






//-------------------------------------------------------------------------//



//definizione oggetti gtk
  
	GtkWidget *eWin1;
	GtkWidget *ebut1;
  	GtkWidget *eFrame1;
	GtkWidget *eLabel1;
	GtkWidget *eTab1;

	GtkWidget *window;
	GtkWidget *window_int;
	GtkWidget *button;
	GtkWidget *combut;
	GtkWidget *radio;
	GtkWidget *radio1;
	GtkWidget *radio2;
	GtkWidget *radio3;
	GtkWidget *radio4;
	GtkWidget *radio5;
	GtkWidget *radio6;
	GtkWidget *radio7;
	GtkWidget *radio8;
	GtkWidget *radio9;
	GtkWidget *label;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *vbox1;
	GtkWidget *hbox1;
	GtkWidget *entry;
	GtkWidget *entry1;

	GSList *group;
	GSList *group1;
	GSList *group2;
	GSList *group3;
	GSList *group4;


//--------------------------------------------------------------------------// 

  gtk_init(&argc, &argv);


////----------------------------------inizializzazioni------------------------//

serial_number= serial_init();			//apertura seriale
if (serial_number<0){
	printf("Wrong opening HL\n");
	eWin1=gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_title (GTK_WINDOW (eWin1),"Error");
	gtk_container_set_border_width (GTK_CONTAINER (eWin1),10);
	eTab1=gtk_table_new(2,1,TRUE);
	gtk_container_add (GTK_CONTAINER (eWin1), eTab1);
	ebut1=gtk_button_new_with_label("Exit");
	g_signal_connect_swapped (ebut1, "clicked",G_CALLBACK (gtk_widget_destroy),eWin1);
	gtk_table_attach(GTK_TABLE(eTab1),ebut1,0,1,1,2,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show  (ebut1);
	eFrame1 = gtk_frame_new (" Error ");
	eLabel1 = gtk_label_new ("\n     Unable to open HL Serial Port    \n");
	gtk_container_add (GTK_CONTAINER (eFrame1), eLabel1);
	gtk_table_attach(GTK_TABLE(eTab1),eFrame1,0,1,0,1,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show_all (eWin1);
	gtk_main();
	return 0;
	sleep(1);
}

serial_number1= serial_init2();			//apertura seriale
if (serial_number1<0){
	printf("Wrong opening TNC\n");
	eWin1=gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_title (GTK_WINDOW (eWin1),"Error");
	gtk_container_set_border_width (GTK_CONTAINER (eWin1),10);
	eTab1=gtk_table_new(2,1,TRUE);
	gtk_container_add (GTK_CONTAINER (eWin1), eTab1);
	ebut1=gtk_button_new_with_label("Exit");
	g_signal_connect_swapped (ebut1, "clicked",G_CALLBACK (gtk_widget_destroy),eWin1);
	gtk_table_attach(GTK_TABLE(eTab1),ebut1,0,1,1,2,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show  (ebut1);
	eFrame1 = gtk_frame_new (" Error ");
	eLabel1 = gtk_label_new ("\n     Unable to open TNC Serial Port    \n");
	gtk_container_add (GTK_CONTAINER (eFrame1), eLabel1);
	gtk_table_attach(GTK_TABLE(eTab1),eFrame1,0,1,0,1,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show_all (eWin1);
	gtk_main();
	return 0;
	sleep(1);
}

//inizializzazione protocollo ax25

nn=write(serial_number1,tnc_init_part,6);
printf("nn= %d",nn);
nn=write(serial_number1,tnc_init_part1,6);
printf("nn= %d",nn);
nn=write(serial_number1,tnc_init_part2,4);
printf("nn= %d",nn);




	seriale=fopen("port.txt","w");		//azzeramento file seriale
	fprintf(seriale,"0");
	fclose(seriale);

	inv=fopen("ext.txt","w");		//azzeramento file comando
	fprintf(inv,"0");
	fclose(inv);

	tmp=fopen("temp.txt","w");		//azzeramento file dati invio
	fprintf(tmp,"");
	fclose(tmp);

	for (i=0;i<3;i++)			//header HL command
	{
		pack_out_HL[i] = command_HL_start[i];
	}
	
	for (i=0;i<18;i++)			//header TNC command
	{
		pack_out_TNC[i] = command_ax25_start[i];
	}


//---------------------------------------------------------------------------------//

printf("il comando con solo header è : %c %c %c", pack_out_HL[0],pack_out_HL[1],pack_out_HL[2] );

//creazione processi padre/figlio
pid=fork();

if (pid==0)
{
	//creation of the interface window
/*	window_int = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window_int), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window_int), 750, 450);
	gtk_window_set_title(GTK_WINDOW(window_int), "Ground station");
	gtk_container_set_border_width(GTK_CONTAINER(window_int), 10);
	combut = gtk_button_new_with_label("COMMAND WINDOW");
	*/
	//creation of the command window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 750, 450);
	gtk_window_set_title(GTK_WINDOW(window), "Command Window");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_widget_show(window);

	hbox1 = gtk_hbox_new(TRUE, 1);
	gtk_container_add(GTK_CONTAINER(window), hbox1);

	vbox = gtk_vbox_new(TRUE, 1);
	gtk_container_add(GTK_CONTAINER(hbox1), vbox);

	vbox1 = gtk_vbox_new(TRUE, 1);
	gtk_container_add(GTK_CONTAINER(hbox1), vbox1);

	hbox = gtk_hbox_new(TRUE, 1);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);
	radio8 = gtk_radio_button_new_with_label (NULL, "Command via HL");
	gtk_box_pack_start(GTK_BOX(hbox), radio8, TRUE, TRUE, 0);
  	group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio8));
  	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio8), TRUE);
  	radio9 = gtk_radio_button_new_with_label (group, "Command via RF");
  	gtk_box_pack_start(GTK_BOX(hbox), radio9, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	g_signal_connect(radio8,"toggled",G_CALLBACK(set_HL),NULL);
	g_signal_connect(radio9,"toggled",G_CALLBACK(set_TNC),NULL);

	button = gtk_button_new_with_label("STOP");
	g_signal_connect(button,"clicked",G_CALLBACK(comando1),NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show  (button);

	button = gtk_button_new_with_label("RESTART");
	g_signal_connect(button,"clicked",G_CALLBACK(comando2),NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show  (button);

	button = gtk_button_new_with_label("RECOVERY");
	g_signal_connect(button,"clicked",G_CALLBACK(comando3),NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show  (button);

	button = gtk_button_new_with_label("FUNCTIONAL TEST");
	g_signal_connect(button,"clicked",G_CALLBACK(comando4),NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show  (button);

	button = gtk_button_new_with_label("NOMINAL");
	g_signal_connect(button,"clicked",G_CALLBACK(comando5),NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show  (button);

	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	radio = gtk_radio_button_new_with_label (NULL, "Propulsion OFF");
	gtk_box_pack_start(GTK_BOX(hbox), radio, TRUE, TRUE, 0);
  	group1 = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio));
  	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio), TRUE);
  	radio1 = gtk_radio_button_new_with_label (group1, "Propulsion ON");
  	gtk_box_pack_start(GTK_BOX(hbox), radio1, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	g_signal_connect(radio,"toggled",G_CALLBACK(comando8),NULL);
	g_signal_connect(radio1,"toggled",G_CALLBACK(comando9),NULL);
	
	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	radio2 = gtk_radio_button_new_with_label (NULL, "Burst OFF");
	gtk_box_pack_start(GTK_BOX(hbox), radio2, TRUE, TRUE, 0);
  	group2 = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio2));
  	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio2), TRUE);
  	radio3 = gtk_radio_button_new_with_label (group2, "Burst ON");
  	gtk_box_pack_start(GTK_BOX(hbox), radio3, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	g_signal_connect(radio2,"toggled",G_CALLBACK(comando10),NULL);
	g_signal_connect(radio3,"toggled",G_CALLBACK(comando11),NULL);

	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	radio4 = gtk_radio_button_new_with_label (NULL, "HL Enabled");
	gtk_box_pack_start(GTK_BOX(hbox), radio4, TRUE, TRUE, 0);
  	group3 = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio4));
  	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio4), TRUE);
  	radio5 = gtk_radio_button_new_with_label (group3, "HL Disabled");
  	gtk_box_pack_start(GTK_BOX(hbox), radio5, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	g_signal_connect(radio4,"toggled",G_CALLBACK(comando12),NULL);
	g_signal_connect(radio5,"toggled",G_CALLBACK(comando13),NULL);

	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	radio6 = gtk_radio_button_new_with_label (NULL, "RF Enabled");
	gtk_box_pack_start(GTK_BOX(hbox), radio6, TRUE, TRUE, 0);
  	group4 = gtk_radio_button_get_group (GTK_RADIO_BUTTON (radio6));
  	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio6), TRUE);
  	radio7 = gtk_radio_button_new_with_label (group4, "RF Disabled");
  	gtk_box_pack_start(GTK_BOX(hbox), radio7, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	g_signal_connect(radio6,"toggled",G_CALLBACK(comando14),NULL);
	g_signal_connect(radio7,"toggled",G_CALLBACK(comando15),NULL);

	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	button = gtk_button_new_with_label("Change log file");
	g_signal_connect(button,"clicked",G_CALLBACK(comando6),NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
	g_signal_connect (entry, "activate",G_CALLBACK (enter_callback),entry);
	gtk_widget_show(hbox);

	hbox = gtk_hbox_new(TRUE, 1);				
	gtk_container_add(GTK_CONTAINER(vbox1), hbox);
	button = gtk_button_new_with_label("Change Time");
	g_signal_connect(button,"clicked",G_CALLBACK(comando7),NULL);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	entry1 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), entry1, TRUE, TRUE, 0);
	g_signal_connect (entry1, "activate",G_CALLBACK (enter_callback),entry1);
	gtk_widget_show(hbox);


	
	g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	gtk_widget_show_all (window);
	gtk_main();


}
else if (pid >0)
{
	while(1)
	{
		printf("\ninizio ciclo while\n");


		inv=fopen("ext.txt","r");		//apertura e lettura del comando
		fscanf(inv,"%d",&invio);
		fclose(inv);
		printf("\naperto file inv - valore : %d\n",invio);
		seriale=fopen("port.txt","r");		//apertura e lettura del comando
		fscanf(seriale,"%d",&port);
		fclose(seriale);



	if (port==0)		//comunicazione via HL
	{
	printf("\ninvio comandi HL abilitato\n");
		if (invio == 1)
		{
			printf("entrato caso 1");
			pack_out_HL[3] = 'S';
			pack_out_HL[4] = 'T';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 2)
		{
			printf("entrato caso 2");
			pack_out_HL[3] = 'R';
			pack_out_HL[4] = 'S';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 3)
		{
			printf("entrato caso 3");
			pack_out_HL[3] = 'R';
			pack_out_HL[4] = 'E';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 4)
		{
			printf("entrato caso 4");
			pack_out_HL[3] = 'F';
			pack_out_HL[4] = 'T';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 5)
		{
			printf("entrato caso 5");
			pack_out_HL[3] = 'N';
			pack_out_HL[4] = 'L';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s\n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 6)
		{
			printf("entrato caso 6");
			pack_out_HL[3] = 'C';
			pack_out_HL[4] = 'L';
			tmp = fopen("temp.txt","r");
			fscanf(tmp,"%s",&set);
			fclose(tmp);
			for (i=5,j=0;i<23 && j<18;i++,j++)
			{
				pack_out_HL[i]=set[j];
			}
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			for (i=0;i<25;i++)
			{
				set[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/




		}

		else if (invio == 7)
		{
			printf("entrato caso 7");
			pack_out_HL[3] = 'C';
			pack_out_HL[4] = 'T';
			tmp = fopen("temp.txt","r");
			fscanf(tmp,"%s",&set);
			fclose(tmp);
			for (i=5,j=0;i<23 && j<18;i++,j++)
			{
				pack_out_HL[i]=set[j];
			}
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			for (i=0;i<25;i++)
			{
				set[i] = 0;
			}
			inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 8)
		{
			printf("entrato caso 8");
			pack_out_HL[3] = 'P';
			pack_out_HL[4] = '0';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 9)
		{
			printf("entrato caso 9");
			pack_out_HL[3] = 'P';
			pack_out_HL[4] = '1';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 10)
		{
			printf("entrato caso 10");
			pack_out_HL[3] = 'B';
			pack_out_HL[4] = '0';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 11)
		{
			printf("entrato caso 11");
			pack_out_HL[3] = 'B';
			pack_out_HL[4] = '1';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 12)
		{
			printf("entrato caso 12");
			pack_out_HL[3] = 'H';
			pack_out_HL[4] = '1';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 13)
		{
			printf("entrato caso 13");
			pack_out_HL[3] = 'H';
			pack_out_HL[4] = '0';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/


		}

		else if (invio == 14)
		{
			printf("entrato caso 14");
			pack_out_HL[3] = 'C';
			pack_out_HL[4] = '1';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 15)
		{
			printf("entrato caso 15");
			pack_out_HL[3] = 'C';
			pack_out_HL[4] = '0';
			g = write (serial_number, pack_out_HL,23);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_HL);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/
		}
	}
	else if (port==1)		//comunicazione via TNC
	{
	printf("\ninvio dati TNC abilitato\n");
		if (invio == 1)
		{
			printf("entrato caso 1");
			pack_out_TNC[18] = 'S';
			pack_out_TNC[19] = 'T';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 2)
		{
			printf("entrato caso 2");
			pack_out_TNC[18] = 'R';
			pack_out_TNC[19] = 'S';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 3)
		{
			printf("entrato caso 3");
			pack_out_TNC[18] = 'R';
			pack_out_TNC[19] = 'E';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 4)
		{
			printf("entrato caso 4");
			pack_out_TNC[18] = 'F';
			pack_out_TNC[19] = 'T';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 5)
		{
			printf("entrato caso 5");
			pack_out_TNC[18] = 'N';
			pack_out_TNC[19] = 'L';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 6)
		{
			printf("entrato caso 6");
			pack_out_TNC[18] = 'C';
			pack_out_TNC[19] = 'L';
			tmp = fopen("temp.txt","r");
			fscanf(tmp,"%s",&set);
			fclose(tmp);
			for (i=20,j=0;i<38 && j<18;i++,j++)
			{
				pack_out_TNC[i]=set[j];
			}
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando : %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			for (i=0;i<25;i++)
			{
				set[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/




		}

		else if (invio == 7)
		{
			printf("entrato caso 7");
			pack_out_TNC[18] = 'C';
			pack_out_TNC[19] = 'T';
			tmp = fopen("temp.txt","r");
			fscanf(tmp,"%s",&set);
			fclose(tmp);
			for (i=20,j=0;i<38 && j<18;i++,j++)
			{
				pack_out_HL[i]=set[j];
			}
			g = write (serial_number, pack_out_HL,30);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			for (i=0;i<25;i++)
			{
				set[i] = 0;
			}
			inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 8)
		{
			printf("entrato caso 8");
			pack_out_TNC[18] = 'P';
			pack_out_TNC[19] = '0';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 9)
		{
			printf("entrato caso 9");
			pack_out_TNC[18] = 'P';
			pack_out_TNC[19] = '1';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 10)
		{
			printf("entrato caso 10");
			pack_out_TNC[18] = 'B';
			pack_out_TNC[19] = '0';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 11)
		{
			printf("entrato caso 11");
			pack_out_TNC[18] = 'B';
			pack_out_TNC[19] = '1';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}

		else if (invio == 12)
		{
			printf("entrato caso 12");
			pack_out_TNC[18] = 'H';
			pack_out_TNC[19] = '1';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 13)
		{
			printf("entrato caso 13");
			pack_out_TNC[18] = 'H';
			pack_out_TNC[19] = '0';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}*/
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/


		}

		else if (invio == 14)
		{
			printf("entrato caso 14");
			pack_out_TNC[18] = 'C';
			pack_out_TNC[19] = '1';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/



		}
		else if (invio == 15)
		{
			printf("entrato caso 15");
			pack_out_TNC[18] = 'C';
			pack_out_TNC[19] = '0';
			g = write (serial_number1, pack_out_TNC,38);
			if (g==-1)
			{
				printf("\tErrore invio comando fallito.\n");
			}
			else if (g>0)
			{
				printf("\nInviato comando TNC: %s \n", pack_out_TNC);
				printf("byte scritti su reriale : %d\n", g);
			}
			/*for (i=3;i<30;i++)
			{
				pack_out_HL[i] = 0;
			}
			/*inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);*/
		}




	}

			for (i=3;i<23;i++)
			{
				pack_out_HL[i] = 0;
			}
			for (i=18;i<38;i++)
			{
				pack_out_TNC[i] = 0;
			}
			for (i=0;i<18;i++)
			{
				set[i] = 0;
			}




			inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);
sleep (2);







	}

}



  
  return 0;
}

