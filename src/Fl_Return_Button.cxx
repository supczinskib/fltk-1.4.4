//
// Return button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//

#include <FL/Fl.H>
#include <FL/Fl_Return_Button.H>
#include <FL/fl_draw.H>

static Fl_Color return_arrow_lighter(Fl_Color c, float weight) {
  return fl_color_average(FL_WHITE, c, weight * 0.40f);
}

static Fl_Color return_arrow_darker(Fl_Color c, float weight) {
  return fl_color_average(FL_BLACK, c, weight * 0.45f);
}

static int fl_return_arrow(int x, int y, int w, int h, Fl_Color c) {
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
  fl_color(return_arrow_lighter(c, 0.5f));
  fl_line(x0, y0, x1, y0+d);
  fl_yxline(x1, y0+d, y0+t, x1+d+2*t, y0-d);
  fl_yxline(x1, y0-t, y0-d);
  fl_color(return_arrow_darker(c, 1.0f));
  fl_line(x0, y0, x1, y0-d);
  fl_color(return_arrow_darker(c, 0.5f));
  fl_xyline(x1+1, y0-t, x1+d, y0-d, x1+d+2*t);
  return 1;
}

int fl_return_arrow(int x, int y, int w, int h) {
  return fl_return_arrow(x, y, w, h, FL_BACKGROUND_COLOR);
}

void Fl_Return_Button::draw() {
  if (type() == FL_HIDDEN_BUTTON) return;
  Fl_Boxtype bt = value() ? (down_box()?down_box():fl_down(box())) : box();
  int dx = Fl::box_dx(bt);
  draw_box(bt, value() ? selection_color() : color());
  int W = h();
  if (w()/3 < W) W = w()/3;
  fl_return_arrow(x()+w()-(W+dx), y(), W, h(), value() ? selection_color() : color());
  draw_label(x()+dx, y(), w()-(dx+W+dx), h());
  if (Fl::focus() == this) draw_focus();
}

int Fl_Return_Button::handle(int event) {
  if (event == FL_SHORTCUT &&
      (Fl::event_key() == FL_Enter || Fl::event_key() == FL_KP_Enter)) {
    simulate_key_action();
    do_callback(FL_REASON_SELECTED);
    return 1;
  } else
    return Fl_Button::handle(event);
}


Fl_Return_Button::Fl_Return_Button(int X, int Y, int W, int H,const char *l)
: Fl_Button(X,Y,W,H,l)
{
}
