#ifndef GTK3_NATIVE
#define GTK3_NATIVE

#include <ruby.h>
#include <gtk/gtk.h>
#include "closure.h"
#include "type.h"
#include "widget.h"
#include "window.h"

extern VALUE gtk3_mGtk3;

extern void Init_gtk3();

#endif
