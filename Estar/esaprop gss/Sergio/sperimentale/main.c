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






//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++CONVERSIONE FLOAT IN STRINGA++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// reverses a string 'str' of length 'len' 
void reverse(char *str, int len) 
{ 
	int i=0, j=len-1, temp; 
	while (i<j) 
	{ 
		temp = str[i]; 
		str[i] = str[j]; 
		str[j] = temp; 
		i++; j--; 
	} 
} 

// Converts a given integer x to string str[]. d is the number 
// of digits required in output. If d is more than the number 
// of digits in x, then 0s are added at the beginning. 
int intToStr(int x, char str[], int d) 
{ 
	int i = 0; 
	while (x) 
	{ 
		str[i++] = (x%10) + '0'; 
		x = x/10; 
	} 

	// If number of digits required is more, then 
	// add 0s at the beginning 
	while (i < d) 
		str[i++] = '0'; 

	reverse(str, i); 
	str[i] = '\0'; 
	return i; 
} 

// Converts a floating point number to string. 
void ftoa(float n, char *res, int afterpoint) 
{ 
	// Extract integer part 
	int ipart = (int)n; 

	// Extract floating part 
	float fpart = n - (float)ipart; 

	// convert integer part to string 
	int i = intToStr(ipart, res, 0); 

	// check for display option after point 
	if (afterpoint != 0) 
	{ 
		res[i] = '.'; // add dot 

		// Get the value of fraction part upto given no. 
		// of points after dot. The third parameter is needed 
		// to handle cases like 233.007 
		fpart = fpart * pow(10, afterpoint); 

		intToStr((int)fpart, res + i + 1, afterpoint); 
	} 
} 

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
















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

static void cmd_win(int argc, char *argv)
{

//dichiarazione Widget GTK per comandi
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




  gtk_init(&argc, &argv);

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






int main(int argc, char *argv[]) 
{


FILE *inv;
FILE *tmp;
FILE *seriale;

//definizione variabili
  
	int serial_number,serial_number1;
	int pid;
	int r1=0,r2=0,r3=0,r4=0,r5=0;
	int invio=0, port=0;
	int i,j,g=0,nn=0,k,ii,jj,kk,n,l;

//definizione variabili pacchetti

	char pack_out_HL[23]={0,}; //command HL
	char pack_out_TNC[38]={0,}; //command TNC
	
	char set[18]={0,};		//setting option


unsigned char tnc_init_part[6]={0x1B,0x40,0x4B,0xFF,0xC0,0x0D}; //setting for TNC for KISS AX.25 protocol
unsigned char tnc_init_part1[6]={0x1B,0x54,0x32,0x30,0x30,0x0D};
unsigned char tnc_init_part2[4]={0x1B,0x40,0x4B,0x0D};

unsigned char receive_HL_start[3]={'C','2','G'}; //header HL received packets
unsigned char command_HL_start[3]={'G','2','C'}; //header HL commands
unsigned char pre_pack[50];
unsigned char command_ax25_start[18]={0xC0,0x00,'C','T','P','C','T','P',0xE0,'G','S','S','G','S','S',0x26,0x03,0xF0}; //header TNC commands

//Definizione dei buffer e pacchetti in ingresso per TNC e HL
unsigned char buffer_HL[500]={0,};  //buffer in input HL
unsigned char buffer_TNC[500]={0,};  //buffer in input TNC
unsigned char pack_in_HL[150]={0,};  //packet in input HL
unsigned char pack_in_TNC[150]={0,};  //packet in input TNC

//Header
unsigned char receive_ax25_start[18]={0xC0,0x00,'G','S','S','G','S','S',0xE0,'C','T','P','C','T','P',0x26,0x03,0xF0}; //header kiss AX25 received packets


int flag_HL=1;
int flag_TNC=1;
int packet_display;
int HL_validation=0;
int TNC_validation=0;



//Spacchettamento tempo

u_int8_t year;
u_int8_t month;
u_int8_t day;
u_int8_t hour;
u_int8_t min;
u_int8_t sec;

//Spacchettamento e conversione config_status

int x=0;
int y=0;
u_int32_t tel_pack_number;
u_int32_t saved_pack_number;
char tel_pack_number_c[8];
char saved_pack_number_c[8];
char opmode;
char last_comm;
char reboot_num;

int t=0;
int p=0;
int dati_finale[36];

int FSbasso=16384;
int FSalto=32768;
int FSbassoM=16627;
int FSaltoM=33254;



int volt5_curr;	
int volt3_curr;
int avio_bat1_volt; 
int avio_bat2_volt; 
int avio_bat1_curr;
int avio_bat2_curr; 
int avio_bat1_temp; 
int avio_bat2_temp;
int avio_bat1_chcurr;
int avio_bat2_chcurr;
int ps_bat1_volt; 
int ps_bat2_volt; 
int ps_bat1_curr; 
int ps_bat2_curr; 
int ps_bat1_temp; 
int ps_bat2_temp; 
int ps_bat1_chcurr; 
int ps_bat2_chcurr;  
int step_up_curr;
int step_up_volt;
int dac_command;
int extra1_temp;
int extra2_temp;
int extra3_temp;
int extra4_temp;
int extra5_temp;
int extra6_temp;
int extra7_temp;
int magnet_x;
int magnet_y;
int magnet_z;
int accel_x;
int accel_y;
int accel_z;
int force1;
int force2;
int force3;


float volt5_curr_f;	
float volt3_curr_f;
float avio_bat1_volt_f; 
float avio_bat2_volt_f; 
float avio_bat1_curr_f;
float avio_bat2_curr_f; 
float avio_bat1_temp_f; 
float avio_bat2_temp_f;
float avio_bat1_chcurr_f;
float avio_bat2_chcurr_f;
float ps_bat1_volt_f; 
float ps_bat2_volt_f; 
float ps_bat1_curr_f; 
float ps_bat2_curr_f; 
float ps_bat1_temp_f; 
float ps_bat2_temp_f; 
float ps_bat1_chcurr_f; 
float ps_bat2_chcurr_f;  
float step_up_curr_f;
float step_up_volt_f;
float extra1_temp_f;
float extra2_temp_f;
float extra3_temp_f;
float extra4_temp_f;
float extra5_temp_f;
float extra6_temp_f;
float extra7_temp_f;
float magnet_x_f;
float magnet_y_f;
float magnet_z_f;
float accel_x_f;
float accel_y_f;
float accel_z_f;
float force1_f;
float force2_f;
float force3_f;






float yyy=321.472;
char yyy_s[20];
//-------------------------------------------------------------------------//



//definizione oggetti finestra errore
  
	GtkWidget *eWin1;
	GtkWidget *ebut1;
  	GtkWidget *eFrame1;
	GtkWidget *eLabel1;
	GtkWidget *eTab1;

//definizione oggetti interfaccia
  GtkWidget *window;
  GtkWidget *Hbox_Top;
  GtkWidget *frame_time;
  GtkWidget *frame_status;
  GtkWidget *table;
  GtkWidget *button;
  GtkWidget *frame;
  GtkWidget *label;
  GtkWidget *window1;
  GtkWidget *vbox;
  GtkWidget *vbox2;
  GtkWidget *vboxS7_1;
  GtkWidget *vboxS7_2;
  GtkWidget *vboxS7_3;
  GtkWidget *vboxS7_4;
  GtkWidget *frame1;
  GtkWidget *frame2;
  GtkWidget *frame_T1;
  GtkWidget *frame_T2;
  GtkWidget *frame_T3;
  GtkWidget *frame_T4;
  GtkWidget *frame_T5;
  GtkWidget *frame_T6;
  GtkWidget *frame_T7;
  GtkWidget *frame_T8;
  GtkWidget *frame_T9;
  GtkWidget *frame_T10;
  GtkWidget *Hbox;
  GtkWidget *Hbox2;
  GtkWidget *Hbox3;
  GtkWidget *radioB;
  GtkWidget *entry1;
  GtkWidget *label1;
  GtkWidget *Hbox_T1;
  GtkWidget *Hbox_T2;
  GtkWidget *Hbox_T3;
  GtkWidget *Hbox_T4;
  GtkWidget *VboxS1;
  GtkWidget *VboxS2;
  GtkWidget *VboxS3;
  GtkWidget *VboxS4;
  GtkWidget *VboxS5;
  GtkWidget *VboxS6;
  GtkWidget *HboxS7;
  GtkWidget *VboxS8;
  GtkWidget *VboxS9;
  GtkWidget *HboxS10;
  GtkWidget *Hbox4;
  GtkWidget *Hbox5;
  GtkWidget *Hbox6;
  GtkWidget *Hbox7;
  GtkWidget *Hbox8;
  GtkWidget *Hbox9;
  GtkWidget *Hbox10;
  GtkWidget *Hbox11;
  GtkWidget *Hbox12;
  GtkWidget *Hbox13;
  GtkWidget *Hbox14;
  GtkWidget *Hbox15;
  GtkWidget *Hbox16;
  GtkWidget *Hbox17;
  GtkWidget *Hbox18;
  GtkWidget *Hbox19;
  GtkWidget *Hbox20;
  GtkWidget *Hbox21;
  GtkWidget *Hbox22;
  GtkWidget *Hbox23;
  GtkWidget *Hbox24;
  GtkWidget *Hbox25;
  GtkWidget *Hbox26;
  GtkWidget *Hbox27;
  GtkWidget *Hbox28;
  GtkWidget *Hbox29;
  GtkWidget *Hbox30;
  GtkWidget *Hbox31;
  GtkWidget *Hbox32;
  GtkWidget *Hbox33;
  GtkWidget *Hbox34;
  GtkWidget *Hbox35;
  GtkWidget *Hbox36;
  GtkWidget *Hbox37;
  GtkWidget *Hbox38;
  GtkWidget *Hbox39;
  GtkWidget *Hbox40;
  GtkWidget *Hbox41;
  GtkWidget *Hbox42;
  GtkWidget *Hbox43;
  GtkWidget *Hbox44;
  GtkWidget *Hbox45;
  GtkWidget *label4;
  GtkWidget *label5;
  GtkWidget *label6;
  GtkWidget *label7;
  GtkWidget *label8;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkWidget *label11;
  GtkWidget *label12;
  GtkWidget *label13;
  GtkWidget *label14;
  GtkWidget *label15;
  GtkWidget *label16;
  GtkWidget *label17;
  GtkWidget *label18;
  GtkWidget *label19;
  GtkWidget *label20;
  GtkWidget *label21;
  GtkWidget *label22;
  GtkWidget *label23;
  GtkWidget *label24;
  GtkWidget *label25;
  GtkWidget *label26;
  GtkWidget *label27;
  GtkWidget *label28;
  GtkWidget *label29;
  GtkWidget *label30;
  GtkWidget *label31;
  GtkWidget *label32;
  GtkWidget *label33;
  GtkWidget *label34;
  GtkWidget *label35;
  GtkWidget *label36;
  GtkWidget *label37;
  GtkWidget *label38;
  GtkWidget *label39;
  GtkWidget *label40;
  GtkWidget *label41;
  GtkWidget *label42;
  GtkWidget *label43;
  GtkWidget *label44;
  GtkWidget *label45;
  GtkWidget *telemetry4;
  GtkWidget *telemetry5;
  GtkWidget *telemetry6;
  GtkWidget *telemetry7;
  GtkWidget *telemetry8;
  GtkWidget *telemetry9;
  GtkWidget *telemetry10;
  GtkWidget *telemetry11;
  GtkWidget *telemetry12;
  GtkWidget *telemetry13;
  GtkWidget *telemetry14;
  GtkWidget *telemetry15;
  GtkWidget *telemetry16;
  GtkWidget *telemetry17;
  GtkWidget *telemetry18;
  GtkWidget *telemetry19;
  GtkWidget *telemetry20;
  GtkWidget *telemetry21;
  GtkWidget *telemetry22;
  GtkWidget *telemetry23;
  GtkWidget *telemetry24;
  GtkWidget *telemetry25;
  GtkWidget *telemetry26;
  GtkWidget *telemetry27;
  GtkWidget *telemetry28;
  GtkWidget *telemetry29;
  GtkWidget *telemetry30;
  GtkWidget *telemetry31;
  GtkWidget *telemetry32;
  GtkWidget *telemetry33;
  GtkWidget *telemetry34;
  GtkWidget *telemetry35;
  GtkWidget *telemetry36;
  GtkWidget *telemetry37;
  GtkWidget *telemetry38;
  GtkWidget *telemetry39;
  GtkWidget *telemetry40;
  GtkWidget *telemetry41;
  GtkWidget *telemetry42;
  GtkWidget *telemetry43;
  GtkWidget *telemetry44;
  GtkWidget *telemetry45;


  GtkWidget *Vbox_side;
  GtkWidget *vbox_time;
  GtkWidget *vbox_status;


  GtkWidget *cmd_butt;




//Definizione delle strutture dei pacchetti ricevuti

typedef struct packet_TNC {
	char header[18];
        char time[6];
        char config_status[11];
	char dati[72]; 
        char ps_data[2];
	} packet_TNC;

packet_TNC *msg_rec_TNC;

typedef struct packet_HL {
	char header[3];
        char time[6];
        char config_status[11];
        char dati[72];
        char ps_data[2];
	} packet_HL;

packet_HL *msg_rec_HL;




//Definizione delle stringhe da stampare nelle entries


  char year_char[20];

  char month_char[20];

  char day_char[20];

  char hour_char[20];

  char min_char[20];

  char sec_char[20];

  char volt5_curr_c[20];	

  char volt3_curr_c[20];

  char avio_bat1_volt_c[20]; 

  char avio_bat2_volt_c[20];
 
  char avio_bat1_curr_c[20];

  char avio_bat2_curr_c[20];
 
  char avio_bat1_temp_c[20];
 
  char avio_bat2_temp_c[20];

  char avio_bat1_chcurr_c[20];

  char avio_bat2_chcurr_c[20];

  char ps_bat1_volt_c[20];
 
  char ps_bat2_volt_c[20];
 
  char ps_bat1_curr_c[20];
 
  char ps_bat2_curr_c[20];
 
  char ps_bat1_temp_c[20]; 

  char ps_bat2_temp_c[20];
 
  char ps_bat1_chcurr_c[20];
 
  char ps_bat2_chcurr_c[20];
  
  char step_up_curr_c[20];

  char step_up_volt_c[20];

  char dac_command_c[20];

  char extra1_temp_c[20];

  char extra2_temp_c[20];
  
  char extra3_temp_c[20];

  char extra4_temp_c[20];

  char extra5_temp_c[20];

  char extra6_temp_c[20];

  char extra7_temp_c[20];

  char magnet_x_c[20];

  char magnet_y_c[20];

  char magnet_z_c[20];




  GSList *group;




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

for (l=0;l<50;l++)
{
	pre_pack[l]=0xC0;
}



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


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  //gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_widget_set_size_request(window, 1250, 650);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  gtk_window_set_title(GTK_WINDOW(window), "Telemetry");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  
  Hbox_Top=gtk_hbox_new(FALSE,1);
  gtk_container_add(GTK_CONTAINER (window), Hbox_Top);
  Vbox_side=gtk_vbox_new(FALSE,1);
  gtk_container_add(GTK_CONTAINER (Hbox_Top), Vbox_side);

  
//Frame per tempo

  frame_time = gtk_frame_new("Time Tag");
  gtk_container_add(GTK_CONTAINER (Vbox_side), frame_time);
  vbox_time = gtk_vbox_new(FALSE, 1);
  gtk_container_add(GTK_CONTAINER (frame_time), vbox_time);
  
  Hbox35 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox35);
  label35 = gtk_label_new("Year");
  telemetry35= gtk_entry_new ();
  gtk_entry_set_text (telemetry35,year_char);
  gtk_widget_set_sensitive (telemetry35, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox35), label35, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox35), telemetry35, TRUE, TRUE, 0);
  
  Hbox36 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox36);
  label36 = gtk_label_new("Month");
  telemetry36= gtk_entry_new ();
  gtk_entry_set_text (telemetry36,month_char);
  gtk_widget_set_sensitive (telemetry36, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox36), label36, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox36), telemetry36, TRUE, TRUE, 0);
  
  Hbox37 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox37);
  label37 = gtk_label_new("Day");
  telemetry37= gtk_entry_new ();
  gtk_entry_set_text (telemetry37,day_char);
  gtk_widget_set_sensitive (telemetry37, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox37), label37, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox37), telemetry37, TRUE, TRUE, 0);

  Hbox38 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox38);
  label38 = gtk_label_new("Hour");
  telemetry38= gtk_entry_new ();
  gtk_entry_set_text (telemetry38,hour_char);
  gtk_widget_set_sensitive (telemetry38, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox38), label38, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox38), telemetry38, TRUE, TRUE, 0);

  Hbox39 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox39);
  label39 = gtk_label_new("Min.");
  telemetry39= gtk_entry_new ();
  gtk_entry_set_text (telemetry39,min_char);
  gtk_widget_set_sensitive (telemetry39, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox39), label39, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox39), telemetry39, TRUE, TRUE, 0);

  Hbox40 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_time), Hbox40);
  label40 = gtk_label_new("Sec.");
  telemetry40= gtk_entry_new ();
  gtk_entry_set_text (telemetry40,sec_char);
  gtk_widget_set_sensitive (telemetry40, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox40), label40, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox40), telemetry40, TRUE, TRUE, 0);

//Status Frame

  frame_status = gtk_frame_new("Status");
  gtk_container_add(GTK_CONTAINER (Vbox_side), frame_status);
  vbox_status = gtk_vbox_new(FALSE, 1);
  gtk_container_add(GTK_CONTAINER (frame_status), vbox_status);

  Hbox41 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_status), Hbox41);
  label41 = gtk_label_new("Operative Mode");
  telemetry41= gtk_entry_new ();
  gtk_entry_set_text (telemetry41,"2A");
  gtk_widget_set_sensitive (telemetry41, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox41), label41, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox41), telemetry41, TRUE, TRUE, 0);
  
  Hbox42 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_status), Hbox42);
  label42 = gtk_label_new("Last Command");
  telemetry42= gtk_entry_new ();
  gtk_entry_set_text (telemetry42,"2A");
  gtk_widget_set_sensitive (telemetry42, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox42), label42, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox42), telemetry42, TRUE, TRUE, 0);
  
  Hbox44 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_status), Hbox44);
  label44 = gtk_label_new("Reboot Number");
  telemetry44= gtk_entry_new ();
  gtk_entry_set_text (telemetry44,"2A");
  gtk_widget_set_sensitive (telemetry44, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox44), label44, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox44), telemetry44, TRUE, TRUE, 0);

  Hbox45 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_status), Hbox45);
  label45 = gtk_label_new("Tel.Packet Num.");
  telemetry45= gtk_entry_new ();
  gtk_entry_set_text (telemetry45,"2A");
  gtk_widget_set_sensitive (telemetry45, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox45), label45, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox45), telemetry45, TRUE, TRUE, 0);

  Hbox43 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vbox_status), Hbox43);
  label43 = gtk_label_new("Saved Packet Num.");
  telemetry43= gtk_entry_new ();
  gtk_entry_set_text (telemetry43,"2A");
  gtk_widget_set_sensitive (telemetry43, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox43), label43, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox43), telemetry43, TRUE, TRUE, 0);


//Impostazione grafica dati
  
  vbox = gtk_vbox_new(FALSE, 1);
  gtk_container_add(GTK_CONTAINER (Hbox_Top), vbox);
  Hbox_T1=gtk_hbox_new(TRUE,1);
  gtk_container_add(GTK_CONTAINER (vbox), Hbox_T1);
  Hbox_T2=gtk_hbox_new(TRUE,1);
  gtk_container_add(GTK_CONTAINER (vbox), Hbox_T2);
  Hbox_T3=gtk_hbox_new(TRUE,1);
  gtk_container_add(GTK_CONTAINER (vbox), Hbox_T3);
  Hbox_T4=gtk_hbox_new(TRUE,1);
  gtk_container_add(GTK_CONTAINER (vbox), Hbox_T4);

  frame_T1 = gtk_frame_new("AV Battery 1 Telemetry:");
  gtk_container_add(GTK_CONTAINER (Hbox_T1), frame_T1);
  VboxS1 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T1), VboxS1);

  frame_T2 = gtk_frame_new("AV Battery 2 Telemetry:");
  gtk_container_add(GTK_CONTAINER (Hbox_T1), frame_T2);
  VboxS2 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T2), VboxS2);

  frame_T3 = gtk_frame_new("PS Battery 1 Telemetry:");
  gtk_container_add(GTK_CONTAINER (Hbox_T2), frame_T3);
  VboxS3 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T3), VboxS3);

  frame_T4 = gtk_frame_new("PS Battery 2 Telemetry");
  gtk_container_add(GTK_CONTAINER (Hbox_T2), frame_T4);
  VboxS4 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T4), VboxS4);

  frame_T5 = gtk_frame_new("Bus Telemetry");
  gtk_container_add(GTK_CONTAINER (Hbox_T3), frame_T5);
  VboxS5 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T5), VboxS5);

  frame_T6 = gtk_frame_new("Step-Up circuit Telemetry");
  gtk_container_add(GTK_CONTAINER (Hbox_T3), frame_T6);
  VboxS6 = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T6), VboxS6);

  frame_T7 = gtk_frame_new("Extra Temperature");
  gtk_container_add(GTK_CONTAINER (vbox), frame_T7);
  HboxS7 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (frame_T7), HboxS7);



  //frame1 = gtk_frame_new("Command Window");
  //gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
  //gtk_container_add(GTK_CONTAINER(Hbox), frame1);

  //frame2 = gtk_frame_new("Telemetry Data");
  //gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_IN);
  //gtk_container_add(GTK_CONTAINER(Hbox), frame2);

  //vbox = gtk_vbox_new(TRUE, 1);
  //gtk_container_add(GTK_CONTAINER(frame1), vbox);

  //vbox2 = gtk_vbox_new(TRUE, 1);
  //gtk_container_add(GTK_CONTAINER(frame2), vbox2);


  Hbox2 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (vbox), Hbox2);

  Hbox3 = gtk_hbox_new(TRUE, 1);


  //ENTRY PER TELEMETRY


  Hbox4 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (VboxS1), Hbox4);
  label4= gtk_label_new("AV Bat.1 Voltage [V]:");
  telemetry4= gtk_entry_new ();
  gtk_entry_set_text (telemetry4,avio_bat1_volt_c);
  gtk_widget_set_sensitive (telemetry4, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox4), label4, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox4), telemetry4, TRUE, TRUE, 0);

  Hbox5 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (VboxS1), Hbox5);
  label5 = gtk_label_new("AV Bat.1 Current [A]:");
  telemetry5= gtk_entry_new ();
  gtk_entry_set_text (telemetry5,avio_bat1_curr_c);
  gtk_widget_set_sensitive (telemetry5, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox5), label5, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox5), telemetry5, TRUE, TRUE, 0);

  Hbox6 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (VboxS1), Hbox6);
  label6= gtk_label_new("AV Bat.1 Temperature [°C]:");
  telemetry6= gtk_entry_new ();
  gtk_entry_set_text (telemetry6,avio_bat1_temp_c);
  gtk_widget_set_sensitive (telemetry6, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox6), label6, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox6), telemetry6, TRUE, TRUE, 0);

  Hbox7 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (VboxS1), Hbox7);
  label7 = gtk_label_new("AV Bat.1 Channel current [A]:");
  telemetry7= gtk_entry_new ();
  gtk_entry_set_text (telemetry7,avio_bat1_chcurr_c);
  gtk_widget_set_sensitive (telemetry7, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox7), label7, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox7), telemetry7, TRUE, TRUE, 0);

  Hbox8 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER (VboxS2), Hbox8);
  label8 = gtk_label_new("AV Bat.2 Voltage [V]:");
  telemetry8= gtk_entry_new ();
  gtk_entry_set_text (telemetry8,avio_bat2_volt_c);
  gtk_widget_set_sensitive (telemetry8, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox8), label8, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox8), telemetry8, TRUE, TRUE, 0);

  Hbox9 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS2), Hbox9);
  label9= gtk_label_new("AV Bat.2 Current [A]:");
  telemetry9= gtk_entry_new ();
  gtk_entry_set_text (telemetry9,avio_bat2_curr_c);
  gtk_widget_set_sensitive (telemetry9, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox9), label9, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox9), telemetry9, TRUE, TRUE, 0);

  Hbox10= gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS2), Hbox10);
  label10 = gtk_label_new("AV Bat.2 Temperature [°C]:");
  telemetry10= gtk_entry_new ();
  gtk_entry_set_text (telemetry10,avio_bat2_temp_c);
  gtk_widget_set_sensitive (telemetry10, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox10), label10, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox10), telemetry10, TRUE, TRUE, 0);

  Hbox11 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS2), Hbox11);
  label11 = gtk_label_new("AV Bat.2 Channel current [A]:");
  telemetry11= gtk_entry_new ();
  gtk_entry_set_text (telemetry11,avio_bat2_chcurr_c);
  gtk_widget_set_sensitive (telemetry11, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox11), label11, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox11), telemetry11, TRUE, TRUE, 0);

  Hbox12 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS3), Hbox12);
  label12= gtk_label_new("PS Bat.1 Voltage [V]:");
  telemetry12= gtk_entry_new ();
  gtk_entry_set_text (telemetry12,ps_bat1_volt_c);
  gtk_widget_set_sensitive (telemetry12, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox12), label12, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox12), telemetry12, TRUE, TRUE, 0);

  Hbox13 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS3), Hbox13);
  label13 = gtk_label_new("PS Bat.1 Current [A]:");
  telemetry13= gtk_entry_new ();
  gtk_entry_set_text (telemetry13,ps_bat1_curr_c);
  gtk_widget_set_sensitive (telemetry13, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox13), label13, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox13), telemetry13, TRUE, TRUE, 0);

  Hbox14 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS3), Hbox14);
  label14= gtk_label_new("PS Bat.1 Temperature:");
  telemetry14= gtk_entry_new ();
  gtk_entry_set_text (telemetry14,ps_bat1_temp_c);
  gtk_widget_set_sensitive (telemetry14, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox14), label14, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox14), telemetry14, TRUE, TRUE, 0);

  Hbox15 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS3), Hbox15);
  label15= gtk_label_new("PS Bat.1 Channel current:");
  telemetry15= gtk_entry_new ();
  gtk_entry_set_text (telemetry15,ps_bat1_chcurr_c);
  gtk_widget_set_sensitive (telemetry15, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox15), label15, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox15), telemetry15, TRUE, TRUE, 0);

  Hbox16 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS4), Hbox16);
  label16 = gtk_label_new("PS Bat.2 Voltage:");
  telemetry16= gtk_entry_new ();
  gtk_entry_set_text (telemetry16,ps_bat2_volt_c);
  gtk_widget_set_sensitive (telemetry16, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox16), label16, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox16), telemetry16, TRUE, TRUE, 0);

  Hbox17 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS4), Hbox17);
  label17= gtk_label_new("PS Bat.2 Current:");
  telemetry17= gtk_entry_new ();
  gtk_entry_set_text (telemetry17,ps_bat2_curr_c);
  gtk_widget_set_sensitive (telemetry17, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox17), label17, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox17), telemetry17, TRUE, TRUE, 0);

  Hbox18 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS4), Hbox18);
  label18 = gtk_label_new("PS Bat.2 Temperature:");
  telemetry18= gtk_entry_new ();
  gtk_entry_set_text (telemetry18,ps_bat2_temp_c);
  gtk_widget_set_sensitive (telemetry18, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox18), label18, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox18), telemetry18, TRUE, TRUE, 0);

  Hbox19 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS4), Hbox19);
  label19 = gtk_label_new("PS Bat.2 Channel current:");
  telemetry19= gtk_entry_new ();
  gtk_entry_set_text (telemetry19,ps_bat2_chcurr_c);
  gtk_widget_set_sensitive (telemetry19, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox19), label19, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox19), telemetry19, TRUE, TRUE, 0);


  Hbox20 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS5), Hbox20);
  label20= gtk_label_new("5V Bus Current [A]:");
  telemetry20= gtk_entry_new ();
  gtk_entry_set_text (telemetry20,volt5_curr_c);
  gtk_widget_set_sensitive (telemetry20, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox20), label20, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox20), telemetry20, TRUE, TRUE, 0);

  Hbox21 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS5), Hbox21);
  label21 = gtk_label_new("3.3V Bus Current [A]:");
  telemetry21= gtk_entry_new ();
  gtk_entry_set_text (telemetry21,volt3_curr_c);
  gtk_widget_set_sensitive (telemetry21, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox21), label21, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox21), telemetry21, TRUE, TRUE, 0);


  Hbox22 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS6), Hbox22);
  label22= gtk_label_new("Step-Up circuit Voltage [V]:");
  telemetry22= gtk_entry_new ();
  gtk_entry_set_text (telemetry22, step_up_volt_c);
  gtk_widget_set_sensitive (telemetry22, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox22), label22, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox22), telemetry22, TRUE, TRUE, 0);

  Hbox23 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(VboxS6), Hbox23);
  label23 = gtk_label_new("Step-Up circuit Current [A]:");
  telemetry23= gtk_entry_new ();
  gtk_entry_set_text (telemetry23,step_up_curr_c);
  gtk_widget_set_sensitive (telemetry23, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox23), label23, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox23), telemetry23, TRUE, TRUE, 0);


  vboxS7_1=gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(HboxS7), vboxS7_1);

  vboxS7_2=gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(HboxS7), vboxS7_2);
  
  vboxS7_3=gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(HboxS7), vboxS7_3);


  Hbox28 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_1), Hbox28);
  label28 = gtk_label_new("Extra Temperature 1:");
  telemetry28= gtk_entry_new ();
  gtk_entry_set_text (telemetry28,extra1_temp_c);
  gtk_widget_set_sensitive (telemetry28, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox28), label28, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox28), telemetry28, TRUE, TRUE, 0);

  Hbox29 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_1), Hbox29);
  label29= gtk_label_new("Extra Temperature 2:");
  telemetry29= gtk_entry_new ();
  gtk_entry_set_text (telemetry29,extra2_temp_c);
  gtk_widget_set_sensitive (telemetry29, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox29), label29, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox29), telemetry29, TRUE, TRUE, 0);

  Hbox30 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_1), Hbox30);
  label30 = gtk_label_new("Extra Temperature 3:");
  telemetry30= gtk_entry_new ();
  gtk_entry_set_text (telemetry30,extra3_temp_c);
  gtk_widget_set_sensitive (telemetry30, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox30), label30, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox30), telemetry30, TRUE, TRUE, 0);

  Hbox31 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_2), Hbox31);
  label31= gtk_label_new("Extra Temperature 4:");
  telemetry31= gtk_entry_new ();
  gtk_entry_set_text (telemetry31,extra4_temp_c);
  gtk_widget_set_sensitive (telemetry31, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox31), label31, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox31), telemetry31, TRUE, TRUE, 0);

  Hbox32 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_2), Hbox32);
  label32 = gtk_label_new("Extra Temperature 5:");
  telemetry32= gtk_entry_new ();
  gtk_entry_set_text (telemetry32,extra5_temp_c);
  gtk_widget_set_sensitive (telemetry32, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox32), label32, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox32), telemetry32, TRUE, TRUE, 0);

  Hbox33 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_2), Hbox33);
  label33= gtk_label_new("Extra Temperature 6:");
  telemetry33= gtk_entry_new ();
  gtk_entry_set_text (telemetry33,extra6_temp_c);
  gtk_widget_set_sensitive (telemetry33, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox33), label33, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox33), telemetry33, TRUE, TRUE, 0);

  Hbox34 = gtk_hbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(vboxS7_3), Hbox34);
  label34= gtk_label_new("Extra Temperature 7:");
  telemetry34= gtk_entry_new ();
  gtk_entry_set_text (telemetry34,extra7_temp_c);
  gtk_widget_set_sensitive (telemetry34, FALSE);
  gtk_box_pack_start(GTK_BOX(Hbox34), label34, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(Hbox34), telemetry34, TRUE, TRUE, 0);


	cmd_butt = gtk_button_new_with_label("COMMAND");
	g_signal_connect(cmd_butt,"clicked",G_CALLBACK(cmd_win),NULL);
	gtk_container_add(GTK_CONTAINER (vbox_status), cmd_butt);





  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  

  gtk_widget_show_all(window);

  gtk_main();




}
else if (pid >0)
{
	while(1)
	{
		printf("\ninizio ciclo while\n");

		//lettura pacchetti


		//definizione canale da leggere
		if (flag_TNC==1 && flag_HL==1)
		{
			packet_display=0;
		}
		else if (flag_TNC==0 && flag_HL==1)
		{
			packet_display=0;
		}
		else if (flag_TNC==1 && flag_HL==0)
		{
			packet_display=1;
		}
		else if (flag_TNC==0 && flag_HL==0)		
		{
			printf("\nERROR! no receiving channel activated\n");
			
			packet_display=2;

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
			eLabel1 = gtk_label_new ("\n     No comm channel activated, unable to update displayed data    \n");
			gtk_container_add (GTK_CONTAINER (eFrame1), eLabel1);
			gtk_table_attach(GTK_TABLE(eTab1),eFrame1,0,1,0,1,GTK_FILL,GTK_FILL,10,10);
			gtk_widget_show_all (eWin1);
			gtk_main();
			return 0;
			sleep(1);
			}




		for(ii=0;ii<500;ii++)
		{
			buffer_HL[ii]=0;
		}
		HL_validation=0;
		n=read(serial_number,buffer_HL,500);

		for(ii=0;ii<500;ii++)
		{
			buffer_TNC[ii]=0;
		}
		int n;
		n=read(serial_number1,buffer_TNC,500);
		
		usleep(100000);
		
		//verifica header HL
		
		for(ii=0;ii<500;ii++)
		{
		if (buffer_HL[ii]==receive_HL_start[0]&&buffer_HL[ii+1]==receive_HL_start[1]&&buffer_HL[ii+2]==receive_HL_start[2])
			{
			
				HL_validation=1;
			}
			if (HL_validation==1)
			{
			for(jj=0;jj<150;jj++) //Copio l'intera sequenza di 150 byte dal buffer al pack-in
				{
				pack_in_HL[jj]=buffer_HL[ii+jj];
				printf ("pack_in[%d]=%x\t",jj,pack_in_HL[jj]);
				}	
				printf("\n\n");
			}
			HL_validation=0; //Azzero il flag
			ii=500; //Mi porto al termine del flusso del buffer
		}	

		//verifica header TNC
		for(ii=0;ii<500;ii++)
		{
		if (buffer_TNC[ii]==receive_ax25_start[0]&&buffer_TNC[ii+2]==receive_ax25_start[2]) //Faccio un controllo a campione nell'header per 		cercare corrispondenza
			{
				for (kk=3, TNC_validation=0;kk<18;kk++) //Se trovo corrispondenza di almeno 2 elementi dell'header controllo gli altri 15
				{
				     if (buffer_TNC[ii+kk]==receive_ax25_start[kk]);
					{
					TNC_validation++;//Se trovo corrispondenza al passo kk tra header e flusso di byte incremento il flag di 1		
					}
				}
		        printf("%d\n",TNC_validation);
			}
			if (TNC_validation==15)//Al termine del controllo se il flag==15 (ossia tutti gli elementi dell'header corrispondono)
			{
				for(jj=0;jj<150;jj++) //Copio l'intera sequenza di 150 byte dal buffer al pack-in
					{
					pack_in_TNC[jj]=buffer_TNC[ii+jj];
					printf ("pack_in[%d]=%x\t",jj,pack_in_TNC[jj]);
					}	
				printf("\n\n");
			}
			TNC_validation=0; //Azzero il flag
			ii=500; //Mi porto al termine del flusso del buffer
		}	
		



		if (packet_display==0)
		{
			//Spacchettamento tempo

			year=pack_in_HL[3];
			month=pack_in_HL[4];
			day=pack_in_HL[5];
			hour=pack_in_HL[6];
			min=pack_in_HL[7];
			sec=pack_in_HL[8];

			//Spacchettamento e conversione config_status

			opmode=pack_in_HL[17];
			last_comm=pack_in_HL[18];
			reboot_num=pack_in_HL[19];
			//Spacchetto config_status in tel_pack
			 tel_pack_number=(u_int32_t)(pack_in_HL[12]*255*255*255+pack_in_HL[11]*255*255+pack_in_HL[10]*255+pack_in_HL[9]);
			//Spacchetto config_status in saved pack
			 saved_pack_number=(u_int32_t)(pack_in_HL[16]*255*255*255+pack_in_HL[15]*255*255+pack_in_HL[14]*255+pack_in_HL[13]);
			
			for(t=0,p=0;p<36;t=t+2,p++)
			{
				dati_finale[p]=(int)(pack_in_HL[20+t+1]*256+pack_in_HL[20+t]);
        
			}



		}
		else if (packet_display==1)
		{

			//Spacchettamento tempo
		
			year=pack_in_TNC[18];
			month=pack_in_TNC[19];
			day=pack_in_TNC[20];
			hour=pack_in_TNC[21];
			min=pack_in_TNC[22];
			sec=pack_in_TNC[23];
			
			//Spacchettamento e conversione config_status
			
			opmode=pack_in_TNC[32];
			last_comm=pack_in_TNC[33];
			reboot_num=pack_in_TNC[34];
			//Spacchetto config_status in tel_pack
			 tel_pack_number=(unsigned int)(pack_in_TNC[27]*255*255*255+pack_in_TNC[26]*255*255+pack_in_TNC[25]*255+pack_in_TNC[24]);
			//Spacchetto config_status in saved pack
			 saved_pack_number=(unsigned int)(pack_in_TNC[31]*255*255*255+pack_in_TNC[30]*255*255+pack_in_TNC[29]*255+pack_in_TNC[28]);

			for(t=0,p=0;p<36;t=t+2,p++)
			{
				dati_finale[p]=(unsigned short)(pack_in_TNC[35+t+1]*256+pack_in_TNC[35+t]);
        
			}

		}

			//spostamento nelle variabili

			volt5_curr=dati_finale[0];	
			volt3_curr=dati_finale[1];
			avio_bat1_volt=dati_finale[2]; 
			avio_bat2_volt=dati_finale[3]; 
			avio_bat1_curr=dati_finale[4];
			avio_bat2_curr=dati_finale[5]; 
			avio_bat1_temp=dati_finale[6]; 
			avio_bat2_temp=dati_finale[7];
			avio_bat1_chcurr=dati_finale[8];
			avio_bat2_chcurr=dati_finale[9];
			ps_bat1_volt=dati_finale[10]; 
			ps_bat2_volt=dati_finale[11]; 
			ps_bat1_curr=dati_finale[12]; 
			ps_bat2_curr=dati_finale[13]; 
			ps_bat1_temp=dati_finale[14]; 
			ps_bat2_temp=dati_finale[15]; 
			ps_bat1_chcurr=dati_finale[16]; 
			ps_bat2_chcurr=dati_finale[17];  
			step_up_curr=dati_finale[18];
			step_up_volt=dati_finale[19];
			dac_command=dati_finale[20];
			extra1_temp=dati_finale[21];
			extra2_temp=dati_finale[22];
			extra3_temp=dati_finale[23];
			extra4_temp=dati_finale[24];
			extra5_temp=dati_finale[25];
			extra6_temp=dati_finale[26];
			extra7_temp=dati_finale[27];
			magnet_x=dati_finale[28];
			magnet_y=dati_finale[29];
			magnet_z=dati_finale[30];
			accel_x=dati_finale[31];
			accel_y=dati_finale[32];
			accel_z=dati_finale[33];
			force1=dati_finale[34];
			force2=dati_finale[35];
			force3=dati_finale[36];
/*
//temporaneo
			volt5_curr=24563;	
			volt3_curr=18732;
			avio_bat1_volt=40375; 
			avio_bat2_volt=dati_finale[3]; 
			avio_bat1_curr=dati_finale[4];
			avio_bat2_curr=dati_finale[5]; 
			avio_bat1_temp=dati_finale[6]; 
			avio_bat2_temp=dati_finale[7];
			avio_bat1_chcurr=dati_finale[8];
			avio_bat2_chcurr=dati_finale[9];
			ps_bat1_volt=dati_finale[10]; 
			ps_bat2_volt=dati_finale[11]; 
			ps_bat1_curr=dati_finale[12]; 
			ps_bat2_curr=dati_finale[13]; 
			ps_bat1_temp=dati_finale[14]; 
			ps_bat2_temp=dati_finale[15]; 
			ps_bat1_chcurr=dati_finale[16]; 
			ps_bat2_chcurr=dati_finale[17];  
			step_up_curr=dati_finale[18];
			step_up_volt=dati_finale[19];
			dac_command=dati_finale[20];
*/


printf("\nv5 curr: %d", volt5_curr);
printf("\nv3 curr: %d",volt3_curr);
printf("\nav bat 1: %d",avio_bat1_volt);
printf("\nav bat 2: %d",avio_bat2_volt);
printf("\nav bat 1 curr: %d",avio_bat1_curr);
printf("\nav bat 2 curr: %d",avio_bat2_curr);
printf("\nav bat 1 temp: %d",avio_bat1_temp);
printf("\nav bat 2 temp: %d",avio_bat2_temp);
printf("\nav bat 1 ch curr: %d",avio_bat1_chcurr);
printf("\nav bat 1 ch curr: %d",avio_bat2_chcurr);
printf("\nps bat 1 curr: %d",ps_bat1_volt);
printf("\nps bat 1 curr: %d",ps_bat2_volt);
printf("\nps bat 1 curr: %d",ps_bat1_curr);
printf("\nps bat 1 curr: %d",ps_bat2_curr);
printf("\nps bat 1 curr: %d",ps_bat1_temp);
printf("\nps bat 1 curr: %d",ps_bat2_temp);
printf("\nps bat 1 curr: %d",ps_bat1_chcurr);
printf("\nps bat 1 curr: %d",ps_bat2_chcurr);
printf("\nburst curr: %d",step_up_curr);
printf("\nburst volt: %d",step_up_volt);

			

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++TRASFORMAZIONE INTERI IN FLOAT CONVERSIONE VALORE++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Conversione in valori corretti
volt5_curr_f = 5.074*((float)volt5_curr - FSbasso)/FSalto;
volt3_curr_f = 5.074*((float)volt3_curr - FSbasso)/FSalto;
avio_bat1_volt_f = 10.144*((float)avio_bat1_volt - FSbasso)/FSalto; 
avio_bat2_volt_f = 10.144*((float)avio_bat2_volt - FSbasso)/FSalto; 
avio_bat1_curr_f = 5.34*((float)avio_bat1_curr - FSbasso)/FSalto;
avio_bat2_curr_f = 5.34*((float)avio_bat2_curr - FSbasso)/FSalto; 
avio_bat1_temp_f = 5.074*((float)avio_bat1_temp - FSbasso)/FSalto; 
avio_bat2_temp_f = 5.074*((float)avio_bat2_temp - FSbasso)/FSalto; 
avio_bat1_chcurr_f = 6.775*((float)avio_bat1_chcurr - FSbasso)/FSalto; 
avio_bat2_chcurr_f = 6.775*((float)avio_bat2_chcurr - FSbasso)/FSalto; 
ps_bat1_volt_f = 21.5*((float)ps_bat1_volt - FSbassoM)/FSaltoM;  
ps_bat2_volt_f = 21.5*((float)ps_bat2_volt - FSbassoM)/FSaltoM; 
ps_bat1_curr_f = 5.34*((float)ps_bat1_curr - FSbassoM)/FSaltoM;
ps_bat2_curr_f = 5.34*((float)ps_bat2_curr - FSbassoM)/FSaltoM;
ps_bat1_temp_f = 5.074*((float)ps_bat1_temp - FSbassoM)/FSaltoM; 
ps_bat2_temp_f = 5.074*((float)ps_bat2_temp - FSbassoM)/FSaltoM; 
ps_bat1_chcurr_f = 6.775*((float)ps_bat1_chcurr - FSbassoM)/FSaltoM; 
ps_bat2_chcurr_f = 6.775*((float)ps_bat2_chcurr - FSbassoM)/FSaltoM;  
step_up_curr_f = 5.34*((float)step_up_curr - FSbassoM)/FSaltoM;
step_up_volt_f = 33*((float)step_up_volt - FSbassoM)/FSaltoM;

/*extra1_temp_f;
extra2_temp_f;
extra3_temp_f;
extra4_temp_f;
extra5_temp_f;
extra6_temp_f;
extra7_temp_f;
magnet_x_f;
magnet_y_f;
magnet_z_f;
accel_x_f;
accel_y_f;
accel_z_f;
force1_f;
force2_f;
force3_f;
*/


printf("\nv5 curr: %f", volt5_curr_f);
printf("\nv3 curr: %f",volt3_curr_f);
printf("\nav bat 1: %f",avio_bat1_volt_f);
printf("\nav bat 2: %f",avio_bat2_volt_f);
printf("\nav bat 1 curr: %f",avio_bat1_curr_f);
printf("\nav bat 2 curr: %f",avio_bat2_curr_f);
printf("\nav bat 1 temp: %f",avio_bat1_temp_f);
printf("\nav bat 2 temp: %f",avio_bat2_temp_f);
printf("\nav bat 1 ch curr: %f",avio_bat1_chcurr_f);
printf("\nav bat 1 ch curr: %f",avio_bat2_chcurr_f);
printf("\nps bat 1 curr: %f",ps_bat1_volt_f);
printf("\nps bat 1 curr: %f",ps_bat2_volt_f);
printf("\nps bat 1 curr: %f",ps_bat1_curr_f);
printf("\nps bat 1 curr: %f",ps_bat2_curr_f);
printf("\nps bat 1 curr: %f",ps_bat1_temp_f);
printf("\nps bat 1 curr: %f",ps_bat2_temp_f);
printf("\nps bat 1 curr: %f",ps_bat1_chcurr_f);
printf("\nps bat 1 curr: %f",ps_bat2_chcurr_f);
printf("\nburst curr: %f",step_up_curr_f);
printf("\nburst volt: %f",step_up_volt_f);









//Conversione float to string
ftoa(volt5_curr_f, volt5_curr_c,4);
ftoa(volt3_curr_f, volt3_curr_c,4);
ftoa(avio_bat1_volt_f, avio_bat1_volt_c,4);
ftoa(avio_bat2_volt_f, avio_bat2_volt_c,4);
ftoa(avio_bat1_curr_f, avio_bat1_curr_c,4);
ftoa(avio_bat2_curr_f, avio_bat2_curr_c,4);
ftoa(avio_bat1_temp_f, avio_bat1_temp_c,4);
ftoa(avio_bat2_temp_f, avio_bat2_temp_c,4);
ftoa(avio_bat1_chcurr_f, avio_bat1_chcurr_c,4);
ftoa(avio_bat2_chcurr_f, avio_bat2_chcurr_c,4);
ftoa(ps_bat1_volt_f, ps_bat1_volt_c,4);
ftoa(ps_bat2_volt_f, ps_bat2_volt_c,4);
ftoa(ps_bat1_curr_f, ps_bat1_curr_c,4);
ftoa(ps_bat2_curr_f, ps_bat2_curr_c,4);
ftoa(ps_bat1_temp_f, ps_bat1_temp_c,4);
ftoa(ps_bat2_temp_f, ps_bat2_temp_c,4);
ftoa(ps_bat1_chcurr_f, ps_bat1_chcurr_c,4);
ftoa(ps_bat2_chcurr_f, ps_bat2_chcurr_c,4);
ftoa(step_up_curr_f, step_up_curr_c,4);
ftoa(step_up_volt_f, step_up_volt_c,4);


/*ftoa(extra1_temp_f, extra1_temp_c,4);
ftoa(extra2_temp_f, extra2_temp_c,4);
ftoa(extra3_temp_f, extra3_temp_c,4);
ftoa(extra4_temp_f, extra4_temp_c,4);
ftoa(extra5_temp_f, extra5_temp_c,4);
ftoa(extra6_temp_f, extra6_temp_c,4);
ftoa(extra7_temp_f, extra7_temp_c,4);
ftoa(magnet_x_f, magnet_x_c,4);
ftoa(magnet_y_f, magnet_y_c,4);
ftoa(magnet_z_f, magnet_z_c,4);
ftoa(accel_x_f, accel_x_c,4);
ftoa(accel_y_f, accel_y_c,4);
ftoa(accel_z_f, accel_z_c,4);
ftoa(force1_f, force1_c,4);
ftoa(force2_f, force2_c,4);
ftoa(force3_f, force3_c,4);
*/

printf("\nv5 curr: %s", volt5_curr_c);
printf("\nv3 curr: %s",volt3_curr_c);
printf("\nav bat 1: %s",avio_bat1_volt_c);
printf("\nav bat 2: %s",avio_bat2_volt_c);
printf("\nav bat 1 curr: %s",avio_bat1_curr_c);
printf("\nav bat 2 curr: %s",avio_bat2_curr_c);
printf("\nav bat 1 temp: %s",avio_bat1_temp_c);
printf("\nav bat 2 temp: %s",avio_bat2_temp_c);
printf("\nav bat 1 ch curr: %s",avio_bat1_chcurr_c);
printf("\nav bat 1 ch curr: %s",avio_bat2_chcurr_c);
printf("\nps bat 1 curr: %s",ps_bat1_volt_c);
printf("\nps bat 1 curr: %s",ps_bat2_volt_c);
printf("\nps bat 1 curr: %s",ps_bat1_curr_c);
printf("\nps bat 1 curr: %s",ps_bat2_curr_c);
printf("\nps bat 1 curr: %s",ps_bat1_temp_c);
printf("\nps bat 1 curr: %s",ps_bat2_temp_c);
printf("\nps bat 1 curr: %s",ps_bat1_chcurr_c);
printf("\nps bat 1 curr: %s",ps_bat2_chcurr_c);
printf("\nburst curr: %s",step_up_curr_c);
printf("\nburst volt: %s",step_up_volt_c);





ftoa(yyy,yyy_s,4);
printf("\ntest ftoa: %s", yyy_s);






//Definizione delle stringhe da stampare nelle entries

			  
			  sprintf(tel_pack_number_c,"%ld",tel_pack_number); 

			  sprintf(saved_pack_number_c,"%ld",saved_pack_number); 

			  sprintf(year_char,"%d",year); 
  
			  sprintf(month_char,"%d",month); 

			  sprintf(day_char,"%d",day); 

			  sprintf(hour_char,"%d",hour); 

			  sprintf(min_char,"%d",min); 

			  sprintf(sec_char,"%d",sec); 

			  sprintf(dac_command_c,"%d",dac_command);




/*

printf("***************************************************************************************************************************\n");
printf("**************************************************Incoming Packet *********************************************************\n");
printf("***************************************************************************************************************************\n");
//printf("		%f/%f/%f	%f:%f:%f\n	",year,mese_def,giorno_def,ore_def,min_def,sec_def);
printf("	Telemetry packet: %ld 					saved packet: %ld\n",tel_pack_number,saved_pack_number);
printf("Operative mode: %x			Last command: %x		Number of reboots:%d\n",opmode,last_comm,reboot_num);
printf("		5V bus current: %d				3V bus current: %dn", volt5_curr,volt3_curr);
printf("AV voltage 1: %d	 AV voltage 2: %d	AV current 1: %d	AV current 2: %d\n",avio_bat1_volt,avio_bat2_volt, avio_bat1_curr, avio_bat2_curr);
printf("AV temperature 1: %d	 AV temperature 2: %d	AV current_out 1: %d	AV current_out 2: %d\n",avio_bat1_temp,avio_bat2_temp, avio_bat1_chcurr, avio_bat2_chcurr);
printf("PS voltage 1: %d	 PS voltage 2: %d	PS current 1: %d	PS current 2: %d\n",ps_bat1_volt,ps_bat2_volt, ps_bat1_curr, ps_bat2_curr);
printf("PS temperature 1: %d	 PS temperature 2: %d	PS current_out 1: %d	PS current_out 2: %d\n",ps_bat1_temp,ps_bat2_temp, ps_bat1_chcurr, ps_bat2_chcurr);
printf("Temperaure 1: %d	Temperaure 2: %d	Temperaure 3: %d	Temperaure 4: %d\n",extra1_temp, extra2_temp, extra3_temp, extra4_temp);
printf("Magnetic Field: X:%d	Y:%d	Z:%d\n",magnet_x,magnet_y,magnet_z);

printf("\nyear:%d     month:%d    day:%d    hour:%d     minute:%d      second:%d    ",year,month,day,hour,min,sec);

*/






		//invio comandi


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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
			}			

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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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

			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			flag_HL=1;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			flag_HL=0;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			flag_TNC=1;
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
			for (l=5;l<=23;l++)
			{
				pack_out_HL[l]=0x00;
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
			flag_TNC=0;
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			
			g = write (serial_number1, pre_pack,50);
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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

			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			flag_HL=1;
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			flag_HL=0;
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			flag_TNC=1;
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
			for (l=20;l<=38;l++)
			{
				pack_out_TNC[l]=0x00;
			}			

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
			flag_TNC=0;
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
				pack_out_HL[i] = 0x00;
			}
			for (i=18;i<38;i++)
			{
				pack_out_TNC[i] = 0x00;
			}
			for (i=0;i<18;i++)
			{
				set[i] = 0x00;
			}




			inv=fopen("ext.txt","w");
			fprintf(inv, "0");
			fclose(inv);
sleep (2);







	}

}



  
  return 0;
}


/*
void float_2_bytes(float angle,char *out)
{
out[3] = *( (char *) &angle+3);
out[2] = *( (char *) &angle+2);
out[1] = *( (char *) &angle+1);
out[0] = *( (char *) &angle+0);
}

void int_2_bytes(int num,char *out)

{
out[1] = *( (char *) &num+0);
out[0] = *( (char *) &num+1);
}


float bytes_2_float(unsigned char *input)
{
	return *(float *) input;
}
*/
























  
