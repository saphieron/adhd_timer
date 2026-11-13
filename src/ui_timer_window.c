#include <gtk/gtk.h>

#include "ui_timer.h"
#include "ui_timer_window.h"

struct _AdhdTimerWindow {
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(AdhdTimerWindow, adhd_timer_window, GTK_TYPE_APPLICATION_WINDOW);

static void adhd_timer_window_init(AdhdTimerWindow* win) {
    gtk_widget_init_template(GTK_WIDGET(win));
}

static void adhd_timer_window_class_init(AdhdTimerWindowClass* class) {
    gtk_widget_class_set_template_from_resource(
        GTK_WIDGET_CLASS(class),
        "tech/saphieron/adhdtimer/timer_ui.xml");
}

AdhdTimerWindow* adhd_timer_window_new(AdhdTimer* app) {
    return g_object_new(ADHD_TIMER_WINDOW_TYPE, "application", app, NULL);
}

void adhd_timer_window_open(AdhdTimerWindow* win, GFile* file) {}
