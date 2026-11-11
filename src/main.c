#include "ui_timer.h"

int main(int argc, char** argv) {
    // run_timer_ui (argc, argv);
    return g_application_run(G_APPLICATION(adhd_timer_new()), argc, argv);
}