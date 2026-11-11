#ifndef UI_TIMER_WINDOW_H
#define UI_TIMER_WINDOW_H

#include "ui_timer.h"
#include <gtk/gtk.h>

#define ADHD_TIMER_WINDOW_TYPE (adhd_timer_window_get_type())
G_DECLARE_FINAL_TYPE(AdhdTimerWindow, adhd_timer_window, ADHDTIMER, APP_WINDOW,
                     GtkApplicationWindow)

AdhdTimerWindow* adhd_timer_window_new(AdhdTimer* app);
void adhd_timer_window_open(AdhdTimerWindow* win, GFile* file);

#endif // UI_TIMER_WINDOW_H