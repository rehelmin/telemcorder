#ifndef __STREAM_CONTROLLER_H
#define __STREAM_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	ST_INIT,
	ST_IDLE,
	ST_STREAM_READ_PRESS,
	ST_STREAM_READ_GYRO,
	ST_STREAM_READ_ACCEL,
	ST_STREAM_OFFLOAD
} Stream_StateTypeDef;

typedef enum {
	EV_ENTRY,
	EV_EXIT,
	EV_START,
	EV_PRESS_IT,
	EV_GYRO_IT,
	EV_ACCEL_IT

} Stream_EventTypeDef;

void stream_controller_run(void);
void stream_controller_add_event(Stream_EventTypeDef in);

#ifdef __cplusplus
}
#endif

#endif /* __STREAM_CONTROLLER_H */