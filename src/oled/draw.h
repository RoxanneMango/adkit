#ifndef DRAW_H
#define DRAW_H

#include "ada_fruit.h"
#include "constexpr_lookup_table.h"

void draw_second(Adafruit_SSD1306 & display, int second, int mode, const LookupTable_time<60,24,60> & lookup_table_s);
void draw_minute(Adafruit_SSD1306 & display, int minute, int mode, const LookupTable_time<60,24,60> & lookup_table_m);
void draw_hour(Adafruit_SSD1306 & display, int hour, int mode, const LookupTable_time<24,18,12> & lookup_table_h);
void draw_clock_face(Adafruit_SSD1306 & display, const LookupTable_clock_face<12> & clock_face);
void redraw_clock_face_elements(Adafruit_SSD1306 & display);

#endif // DRAW_H