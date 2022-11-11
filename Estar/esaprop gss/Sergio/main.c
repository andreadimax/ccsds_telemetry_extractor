#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <gtk/gtk.h>


#define PI 3.1415

void float_2_bytes(float angle,char *out);
void int_2_bytes(int num,char *out);
float bytes_2_float(unsigned char *input);


main(int   argc, char *argv[])
{
//definizione Widget per Gtk
GtkWidget *window1;
GtkWidget *table;
GtkWidget *button;
GtkWidget *frame;
GtkWidget *label;
GtkWidget *window2;
GtkWidget *table2;
GtkWidget *button2;
GtkWidget *frame2;
GtkWidget *label2;
GtkWidget *window3;


//inizializzazione Gtk
gtk_init (&argc, &argv);





printf("-------------------------------------------------------------------------------\n");
FILE * nome_file;
//FILE * nome_file1;
//FILE * nome_file2;
//FILE * tp;

//stringa di comando per gli alimentatori
unsigned char pack_out_HL[40]={0,}; //command HL
unsigned char pack_out_TNC[40]={0,}; //command TNC
unsigned char buffer_HL[1000]={0,};  //buffer in input HL
unsigned char buffer_TNC[500]={0,};  //buffer in input TNC
unsigned char pack_in_HL[150]={0,};  //packet in input HL
unsigned char pack_in_TNC[150]={0,};  //packet in input TNC


unsigned char tnc_init_part[6]={0x1B,0x40,0x4B,0xFF,0xC0,0x0D}; //setting for TNC for KISS AX.25 protocol
unsigned char tnc_init_part1[6]={0x1B,0x54,0x32,0x30,0x30,0x0D};
unsigned char tnc_init_part2[4]={0x1B,0x40,0x4B,0x0D};

				     
unsigned char receive_ax25_start[18]={0xC0,0x00,'G','S','S','G','S','S',0xE0,'C','T','P','C','T','P',0x26,0x03,0xF0}; //header kiss AX25 received packets
unsigned char command_ax25_start[18]={0xC0,0x00,'C','T','P','C','T','P',0xE0,'G','S','S','G','S','S',0x26,0x03,0xF0}; //header kiss AX25 commands

unsigned char receive_HL_start[3]={'C','2','G'}; //header HL received packets
unsigned char command_HL_start[3]={'G','2','C'}; //header HL commands

//utilizzate per determinare il tempo
double tt,dt,usec,tt1,tt2; 
double anno,anno0,day,hour,mins,sec;
int mese;
float tf[6];
//double daysmo[12] = {-1,30,58,89,119,150,180,211,242,272,303,333};
//int daylim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};


unsigned char contatempo=0; //counter utilizzato per determinare ogni quanti cicli salvare i log file


int i,ii,j,k,jj,kk,nn; //contatori vari
int serial_number,serial_number1;
int TNC_validation=0;

// definition of packets and commands structure
typedef struct packet_TNC {
	unsigned char header[18];
	unsigned char cmd[4];
	unsigned char value_cmd[18];
	} packet_TNC;

packet_TNC *msg_rec_TNC;


typedef struct packet_HL {
	unsigned char header[3];
	unsigned char cmd[4];
	unsigned char value_cmd[18];
	} packet_HL;

packet_HL *msg_rec_HL;
///pacchetten spediten

typedef struct command_TNC {
	char header[18];
	char dati[132]; //dati shall be converted in telemetry data name
	} command_TNC;

command_TNC *msg_snd_TNC;

typedef struct command_HL {
	char header[3];
	
	} command_HL;

command_HL *msg_snd_HL;



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


serial_number1= serial_init2();
if (serial_number1<0){
	printf("Wrong opening TNC\n");
	window2=gtk_window_new (GTK_WINDOW_POPUP);
	gtk_window_set_title (GTK_WINDOW (window2),"Error");
	gtk_container_set_border_width (GTK_CONTAINER (window2),10);
	table2=gtk_table_new(2,1,TRUE);
	gtk_container_add (GTK_CONTAINER (window2), table2);
	button2=gtk_button_new_with_label("Exit");
	g_signal_connect_swapped (button2, "clicked",G_CALLBACK (gtk_widget_destroy),window2);
	gtk_table_attach(GTK_TABLE(table2),button2,0,1,1,2,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show  (button2);
	frame2 = gtk_frame_new (" Error ");
	label2 = gtk_label_new ("\n     Unable to open TNC Serial Port    \n");
	gtk_container_add (GTK_CONTAINER (frame2), label2);
	gtk_table_attach(GTK_TABLE(table2),frame2,0,1,0,1,GTK_FILL,GTK_FILL,10,10);
	gtk_widget_show_all (window2);
	gtk_main();
	return 0;
	sleep(1);
}


nn=write(serial_number1,tnc_init_part,6);
printf("nn= %d",nn);
nn=write(serial_number1,tnc_init_part1,6);
printf("nn= %d",nn);
nn=write(serial_number1,tnc_init_part2,4);
printf("nn= %d",nn);

struct timeval start,end,mio;
gettimeofday(&start, NULL);


printf("\n-----------------------------INIZIO------------------------------\n");

//inizio del ciclo principale
while(1){

//finestra gtk
window3=gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window3),"CTP Ground Station");
gtk_container_set_border_width (GTK_CONTAINER (window3),10);





// ------------------------gestione del tempo-------------------
gettimeofday(&end, NULL);
sec = end.tv_sec - start.tv_sec;
usec = end.tv_usec - start.tv_usec;
//tt2 = sec+usec/1000000 ;+ tstart;
//dt = tt2-tt1;
//tt += dt;
//tt1 = tt2;

//tp = fopen("anno.txt","r");
//fscanf(tp,"%f %f %f %f %f %f",&tf[0],&tf[1],&tf[2],&tf[3],&tf[4],&tf[5]);
//fclose(tp);
//printf("%.0f %.0f %.0f %.0f %.0f %f\n",tf[0],tf[1],tf[2],tf[3],tf[4],tf[5]);
// sec
/*tf[5] += dt;
if(tf[5]>=60){
	tf[5] -= 60;	// sec
	tf[4] += 1;	// min
}
// min
if(tf[4]>=60){
	tf[4] -= 60;	// min
	tf[3] += 1;	// hour
}
// hour
if(tf[3]==24){
	tf[3] = 0;	// hour
	tf[2] += 1;	// day
}
// day
if(tf[2]>daylim[mese]){
	tf[2] = 1;	// day
	tf[1] += 1;	// mese
}
// mese
if(tf[1]>11){
	tf[1] = 0;	// mese
	tf[0] += 1;	// anno
}
anno = 1900+(double)tf[0];
mese = (int)tf[1];
day = (double)tf[2];
hour = (double)tf[3];
mins = (double)tf[4];
sec = (double)tf[5];

anno = anno + (day+daysmo[mese])/365;
anno = anno + hour/8760 + mins/525600 + (sec+usec/1000000)/31536000;
//printf("\nt = %f\ndt = %f\n",tt,dt);
//fine gestione tempo


*/
//printf("Latitudine = %f\n Longitudine = %f\n Quota = %f\n",L[0],L[1],(L[2]-6378137)/1000);
//printf("EMF reale = %f %f %f", B[0],B[1],B[2]);  

/*for(i = 0; i < 150; i++){
	stringa[i]=i;
	printf("%d ",stringa[i]);
}
*/

//gestione tempo fabri
//msg_snd = (timeval *) malloc (sizeof(mio);

gettimeofday(&mio, NULL);

double secondi;
secondi = mio.tv_sec;
//printf ("secondi fabri %f\n",secondi); 
float sec_def, min_def, ore_def, giorno_def;
float minuti,ore,giorno;


sec_def=secondi - (int)(secondi/60)*60;
//printf ("sec_def %f\n",sec_def); 
minuti=(int)(secondi)/60;
min_def=minuti-(int)(minuti/60)*60;
//printf ("min_def %f\n",min_def); 
ore=(int)(minuti)/60;
ore_def=ore-(int)(ore/24)*24;
//printf ("ore_def %f\n",ore_def+2);
giorno=(int)(ore/24); 
//printf ("giorno %f\n",giorno);

float nab=11, month=0;
giorno_def=giorno-(int)((giorno-nab)/365)*365;

if(giorno_def<31)
	{
	month=1;
	} else {
	if (giorno_def<69)
	{		
	month=2;
	giorno_def=giorno_def-31;
	} else {
	if (giorno_def<90)
	{
	month=3;
	giorno_def=giorno_def-69;
	} else {
	if (giorno_def<120)
	{
	month=4;
	giorno_def=giorno_def-90;
	} else {
	if (giorno_def<151)
	{
	month=5;
	giorno_def=giorno_def-121;
	} else {
	if (giorno_def<181)
	{
	month=6;
	giorno_def=giorno_def-151;
	} else {
	if (giorno_def<212)
	{
	month=7;
	giorno_def=giorno_def-181;
	} else {
	if (giorno_def<243)
	{
	month=8;
	giorno_def=giorno_def-212;
	} else {
	if (giorno_def<273)
	{
	month=9;
	giorno_def=giorno_def-243;
	} else {
	if (giorno_def<304)
	{
	month=10;
	giorno_def=giorno_def-273;
	} else {
	if (giorno_def<334)
	{
	month=11;
	giorno_def=giorno_def-304;
	}
	else
	{
	month=12;
	giorno_def=giorno_def-334;
	}
}
}
}
}
}
}
}
}
}
}

//printf("giorno def %d\n", (int)(giorno_def));
//printf("mese %d\n", (int)(month));


float mesi=(giorno-nab)/365;
float mese_def=mesi*12-(mesi/12)*12;
//printf("mesi_def %d\n", (int)(mese_def));
float year=1970+(int)(mese_def/12);
//printf("year %d\n", (int)(year));






/*
//create command packet via TNC

msg_snd_TNC = (command_TNC *) malloc (sizeof(command_TNC));

for (ii=0;ii<18;ii++)
{
msg_snd_TNC->header[ii]= command_ax25_start[ii];
}

// switch according to the selected command



nn=write(serial_number1,msg_snd_TNC,40); // send on serial TNC of the command
//printf("bytes on serial = %d\n",nn);

usleep(100000);


//create command packet for HL

msg_snd_HL = (command_HL *) malloc (sizeof(command_HL));

for (ii=0;ii<3;ii++)
{
msg_snd_HL->header[ii]= command_HL_start[ii];
}

// switch according to the selected command



nn=write(serial_number,msg_snd_HL,25); // send on serial TNC of the command
//printf("bytes on serial = %d\n",nn);

usleep(100000);
*/
printf("\n");




/////////////////////////////////////////////////////////////////////////////////////
///////////////      RECEPTION //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

//reception from TNC
printf ("\n\n\n RECEPTION \n\n\n");

for(ii=0;ii<500;ii++)
	{
	buffer_TNC[ii]=0;
	}


int n;
n=read(serial_number1,buffer_TNC,500);

usleep(100000);
printf("read channel TNC: %d\n",n);
for(ii=0;ii<500;ii++)
{
printf ("%x",buffer_TNC[ii]);
}
printf("\n");


msg_rec_TNC = (packet_TNC *) malloc (sizeof(packet_TNC));

for(ii=0;ii<500;ii++)
{
if (buffer_TNC[ii]==receive_ax25_start[0]&&buffer_TNC[ii+2]==receive_ax25_start[2])
	{
	for (kk=3;kk<18;kk++)
	{
	if (buffer_TNC[ii+kk]==receive_ax25_start[kk]);
		{
		TNC_validation++;		
		}
	}
printf("%d\n",TNC_validation);
	if (TNC_validation==15)
	{
	for(jj=0;jj<150;jj++)
		{
		pack_in_TNC[jj]=buffer_TNC[ii+jj];
		printf ("pack_in[%d]=%x\t",jj,pack_in_TNC[jj]);
		}	
		printf("\n\n");
	}
	TNC_validation=0;
	ii=500;
	
}



}


//associare packet TNC

//msg_rec_TNC.xxxx = pack_in_TNC[18]; 



//reception from HL

msg_rec_HL = (packet_HL *) malloc (sizeof(packet_HL));

nn=read(serial_number,buffer_HL,1000);
printf("read channel HL: %d\n",nn);

for(ii=0;ii<1000;ii++)
{
if ((buffer_HL[ii]==receive_HL_start[0])&&(buffer_HL[ii+1]==receive_HL_start[1])&&(buffer_HL[ii+2]==receive_HL_start[2]))
	{
	for(jj=0;jj<150;jj++)
		{
		pack_in_HL[jj]==buffer_HL[ii+jj];
		printf("\n\n packet...\n\n");
		printf ("%x",pack_in_HL[jj]);
		printf("\n\n packet...\n\n");
		}	
	}

}


//associare packet

//msg_rec_HL.xxxx = pack_in_HL[3]; 


usleep(10000);
sleep(1);
} //chiusura while

}//chiusura main


///fine



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
