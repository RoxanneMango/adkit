#include "draw.h"

void 
draw_second(Adafruit_SSD1306 & display, int second, int mode, const LookupTable_time<60,24,60> & lookup_table_s)
{
   if(mode)
   {
	   display.drawCircle(lookup_table_s.table[second][0], lookup_table_s.table[second][1], 2, SSD1306_WHITE);
   }
   else
   {
	   display.drawCircle(lookup_table_s.table[second][0], lookup_table_s.table[second][1], 2, SSD1306_BLACK);
   }
}

void 
draw_minute(Adafruit_SSD1306 & display, int minute, int mode, const LookupTable_time<60,24,60> & lookup_table_m)
{
   if(mode)
   {
	   display.drawLine(clock_center_x, clock_center_y, lookup_table_m.table[minute][0], lookup_table_m.table[minute][1], SSD1306_WHITE); 
   }
   else
   {
	   display.drawLine(clock_center_x, clock_center_y, lookup_table_m.table[minute][0], lookup_table_m.table[minute][1], SSD1306_BLACK);
   }
}

void 
draw_hour(Adafruit_SSD1306 & display, int hour, int mode, const LookupTable_time<24,18,12> & lookup_table_h)
{
   if(mode)
   {
    display.drawLine(clock_center_x, clock_center_y, lookup_table_h.table[hour][0], lookup_table_h.table[hour][1], SSD1306_WHITE);
   }
   else
   {
    display.drawLine(clock_center_x, clock_center_y, lookup_table_h.table[hour][0], lookup_table_h.table[hour][1], SSD1306_BLACK);
   }  
}

void 
draw_clock_face(Adafruit_SSD1306 & display, const LookupTable_clock_face<12> & clock_face)
{
	display.drawCircle(clock_center_x, clock_center_y,3, SSD1306_WHITE);
	display.fillCircle(clock_center_x, clock_center_y,3, SSD1306_WHITE);

	for (int i = 0; i < 12; ++i)
	{
		display.drawLine(clock_face.table[i][0], clock_face.table[i][1], clock_face.table[i][2], clock_face.table[i][3], SSD1306_WHITE);
	}
}

void 
redraw_clock_face_elements(Adafruit_SSD1306 & display)
{
	display.drawCircle(clock_center_x, clock_center_y,3, SSD1306_WHITE);
	display.fillCircle(clock_center_x, clock_center_y,3, SSD1306_WHITE);
	display.setCursor(clock_center_x-3,0);
}