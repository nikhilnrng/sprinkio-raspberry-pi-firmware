#include "sprinkio.h"

void get_time(sptime_t* time) {
  struct timeval curTime;
  struct tm *my_date_time;
  gettimeofday(&curTime, NULL);
  my_date_time = localtime(&curTime.tv_sec);

  time->second = my_date_time->tm_sec;
  time->minute = my_date_time->tm_min;
  time->hour = my_date_time->tm_hour;
}
