/* AVRTime.h
written by: Jake Marlett
10/23/2022

License: MIT (see LICENSE)

Purpose of library: 
    To be able to store time and keep it on an AVR device (Arduino)
    The storage of time is avalible only when 

Please check the "examples" folder in this library to learn how to use it

*/

#ifndef AVRTime_h
#define AVRTime_h
#include "Arduino.h" 
class AVRTime {
    private:
        bool am;
        bool update;
        int currentSec;
        int pastSec;
        int sec;
        int min;
        int hour;
        int hour12;
        int day;
        int month;
        int year1; //The left two digits of the year
        int year2; //The right two digits of the year
        String STRTime;
        String STRDate;
        String monthName[12];
    public:
        void setTime(int h, int m, int s);
  void setStringTime(String h, String m, String s);
  void setDate(int d, int m, int y1, int y2);
  void setStringDate(String d, String m, String y1, String y2);
  void keepTime();
  void printFormattedTime();
  bool validTime(int startH, int startM, int endH, int endM); //24 Hour Format, Tells you if the current time is within the given window (Start --> End)
  bool validGivenTime(int hour, int min, int startH, int startM, int endH, int endM); //Tells you if a given time is within the given window
  bool timeUpdate();
  int getSecond();
  int getMinute();
  int getHour();
  int getDate();
  int getMonth();
  int getYear();
  String parseHour();
  String parseMin();
  String parseSec();
  String parseDay();
  String parseMonth();
  String parseYear1(); //Left two digits of the year
  String parseYear2(); //Right two digits of the year
};
#endif