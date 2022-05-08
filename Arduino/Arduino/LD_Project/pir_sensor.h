#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

uint8_t read_pir;

void pir_init(void);
void pir_run(void);

#ifdef __cplusplus
}
#endif

#endif
