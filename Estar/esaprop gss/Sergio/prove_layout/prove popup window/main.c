#include <gtk/gtk.h>

G_MODULE_EXPORT void
cb_show_prop( GtkButton *button,
              GtkWidget *popup )
{
    gtk_window_present( GTK_WINDOW( popup ) );
}

int
main( int    argc,
      char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GtkWidget  *popup;

    gtk_init( &argc, &argv );

    builder = gtk_builder_new();
    gtk_builder_add_from_file( builder, "popup.builder", NULL );

    window = GTK_WIDGET( gtk_builder_get_object( builder, "main_w" ) );
    popup  = GTK_WIDGET( gtk_builder_get_object( builder, "popup_w" ) );

    gtk_builder_connect_signals( builder, popup );
    g_object_unref( G_OBJECT( builder ) );

    gtk_widget_show_all( window );
    gtk_main();

    return( 0 );
}
