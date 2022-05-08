#ifndef SOIL_SENSOR_H_
#define SOIL_SENSOR_H_
#include <Arduino.h>
#ifdef __cplusplus
extern "C" {
#endif

void soil_init(void);
void soil_run( int soil_read);
#ifdef __cplusplus
}
#endif

#endif
