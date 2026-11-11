#ifndef UI_TIMER_H
#define UI_TIMER_H

#include <gtk/gtk.h>

#define ADHD_TIMER_TYPE (adhd_timer_get_type())
G_DECLARE_FINAL_TYPE(AdhdTimer, adhd_timer, ADHDTIMER, APP, GtkApplication);

AdhdTimer* adhd_timer_new(void);

int run_timer_ui(int argc, char** argv);
#endif // UI_TIMER_H