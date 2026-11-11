#include "ui_timer.h"
#include "ui_timer_window.h"

#include <gtk/gtk.h>

struct _AdhdTimer {
    GtkApplication parent;
};

static void adhd_timer_init(AdhdTimer* app);
static void adhd_timer_activate(GApplication* app);

// the order seems to be: Application class, class function prefix, and GTK
// widget type
G_DEFINE_TYPE(AdhdTimer, adhd_timer, GTK_TYPE_APPLICATION);

AdhdTimer* adhd_timer_new(void) {
    return g_object_new(ADHD_TIMER_TYPE, "application-id",
                        "tech.saphieron.adhdtimer", "flags",
                        G_APPLICATION_HANDLES_OPEN, NULL);
}

static void adhd_timer_init(AdhdTimer* app) {}

static void adhd_timer_activate(GApplication* app) {
    AdhdTimerWindow* win;

    win = adhd_timer_window_new(ADHDTIMER_APP(app));
    gtk_window_present(GTK_WINDOW(win));
}

static void adhd_timer_open(GApplication* app, GFile** files, int n_files,
                            const char* hint) {
    GList* windows;
    AdhdTimerWindow* win;
    int i;

    windows = gtk_application_get_windows(GTK_APPLICATION(app));
    if (windows)
        win = ADHDTIMER_APP_WINDOW(windows->data);
    else
        win = adhd_timer_window_new(ADHDTIMER_APP(app));

    for (i = 0; i < n_files; i++)
        adhd_timer_window_open(win, files[i]);

    gtk_window_present(GTK_WINDOW(win));
}

static void adhd_timer_class_init(AdhdTimerClass* class) {
    G_APPLICATION_CLASS(class)->activate = adhd_timer_activate;
    G_APPLICATION_CLASS(class)->open = adhd_timer_open;
}
