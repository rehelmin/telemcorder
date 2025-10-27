#include "stream_controller.h"
#include "queue.h"

#define EV_ENTRY	1U
#define EV_EXIT		2U

typedef struct Stream_Controller_TypeDef Stream_Controller_TypeDef;
typedef void * (*state_function)(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);

struct Stream_Controller_TypeDef {
	state_function state;
	state_function super;

	uint32_t buffer
};

static volatile queue_t event_queue = {.head = 0, .tail = 0};

static void stream_controller_init(Stream_Controller_TypeDef *hsc1, state_function init_state);

/**
 * @brief Dispatches to the actual function that is pointed to within the hsc1 struct.
 * 
 * @param hsc1		A pointer to the state management struct.
 * @param event		Event that caused the dispatch
 * @return 			void
 */
static void stream_controller_dispatch(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void stream_controller_transition(Stream_Controller_TypeDef *hsc1, state_function new_state);

static void * sc_state_init(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void * sc_state_stream(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void * sc_state_stream_pressure(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void * sc_state_stream_gyro(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void * sc_state_stream_accel(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);
static void * sc_state_stream_push_rf(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event);

void stream_controller_run(void)
{
	Stream_Controller_TypeDef hsc1;
	Stream_EventTypeDef event;

	stream_controller_init(&hsc1, sc_state_init);

	while(1)
	{
		dequeue(&)
	}
}

static void * sc_state_init(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event){
    switch(event){
    case EV_ENTRY:
        /* State entry actions */
        return NULL;
    case EV_BAS:
        hsm_transition(hsm, hsm_state_bas);
        return NULL;
    case EV_EXIT:
        /* State exit actions  */ 
        return NULL;
    default:
        return NULL;
    }
}

static void stream_controller_init(Stream_Controller_TypeDef *hsc1, state_function init_state)
{
	hsc1->state = init_state;
	stream_controller_dispatch(hsc1, EV_ENTRY);
}


static void stream_controller_dispatch(Stream_Controller_TypeDef *hsc1, Stream_EventTypeDef event)
{
	hsc1->super = hsc1->state;
	do
	{
		hsc1->super = (state_function)(*(hsc1)->super)(hsc1, event);
	} while (hsc1->super != NULL);
}

static void stream_controller_transition(Stream_Controller_TypeDef *hsc1, state_function new_state)
{
	stream_controller_dispatch(hsc1, EV_EXIT);
	hsc1->state = new_state;
	stream_controller_dispatch(hsc1, EV_ENTRY);
}