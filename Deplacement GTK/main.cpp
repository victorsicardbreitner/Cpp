#include <gtk/gtk.h>

#include <gtkmm/image.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/alignment.h>
#include <gtkmm/table.h>
#include <gdk/gdkkeysyms.h>

#include <stdlib.h>

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *image1;
GtkWidget *image2;
GtkWidget *nivo;
GtkAdjustment *h,*v;

int Gx=100;
int Gy=100;
int d=5;

int Gxnivo=-500;
int Gynivo=0;

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
GSourceFunc  TempsQuiPasse();

#include <glib.h>
gboolean timeout_callback(gpointer data);



static gboolean is_z_pressed = FALSE;
static gboolean is_q_pressed = FALSE;
static gboolean is_s_pressed = FALSE;
static gboolean is_d_pressed = FALSE;




int main(int argc, char *argv[]) {



    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Le Jeu");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 224);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    h=gtk_adjustment_new (300,300,300,0,0,300);
    v=gtk_adjustment_new (300,300,300,0,0,300);
    fixed = gtk_layout_new(h,v);
    gtk_container_add(GTK_CONTAINER(window), fixed);

    image1 = gtk_image_new_from_file("V4.gif");
    image2 = gtk_image_new_from_file("pika.gif");
    nivo = gtk_image_new_from_file("nivo.gif");

    g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(on_key_press), NULL);
    g_signal_connect(G_OBJECT(window), "key_release_event", G_CALLBACK(on_key_release), NULL);


    gtk_layout_put(GTK_LAYOUT(fixed), nivo, Gxnivo, Gynivo);
    gtk_layout_put(GTK_LAYOUT(fixed), image2, Gx, Gy);



    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    GMainLoop *loop;
    loop = g_main_loop_new ( NULL , FALSE );
    g_timeout_add(10 , timeout_callback , loop);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    gtk_main();

    return 0;
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    if (event->keyval == GDK_KEY_z){
        is_z_pressed = TRUE;
    }
    if (event->keyval == GDK_KEY_q){
        is_q_pressed = TRUE;
    }
    if (event->keyval == GDK_KEY_s){
        is_s_pressed = TRUE;
    }
    if (event->keyval == GDK_KEY_d){
        is_d_pressed = TRUE;
    }
    return FALSE;
}

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer user_data){
    if (event->keyval == GDK_KEY_z){
        is_z_pressed = FALSE;
    }
    if (event->keyval == GDK_KEY_q){
        is_q_pressed = FALSE;
    }
    if (event->keyval == GDK_KEY_s){
        is_s_pressed = FALSE;
    }
    if (event->keyval == GDK_KEY_d){
        is_d_pressed = FALSE;
    }
    return FALSE;
}

gboolean timeout_callback(gpointer data)
{
    if (is_z_pressed) {
        Gy=Gy-d;
        gtk_layout_move(GTK_LAYOUT(fixed), image2, Gx, Gy);
    }
    if (is_q_pressed) {
        Gxnivo=Gxnivo+d;
        gtk_layout_move(GTK_LAYOUT(fixed), nivo, Gxnivo, Gynivo);
    }
    if (is_s_pressed) {
        Gy=Gy+d;
        gtk_layout_move(GTK_LAYOUT(fixed), image2, Gx, Gy);
    }
    if (is_d_pressed) {
        Gxnivo=Gxnivo-d;
        gtk_layout_move(GTK_LAYOUT(fixed), nivo, Gxnivo, Gynivo);
    }

    return TRUE;
}
