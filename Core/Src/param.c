#include <stdint.h>
#include <string.h>
#include "param.h"
#include "param_dict.h"

// Static flag to track initialization
static uint8_t param_initialized = 0;

void param_init(void) {
    // Verify dictionary is sorted by param_id (debug check)
    #ifdef DEBUG
    for (size_t i = 1; i < PARAM_COUNT; i++) {
        if (param_dict[i-1].param_id >= param_dict[i].param_id) {
            // Error: Dictionary not properly sorted!
            while(1); // Halt in debug mode
        }
    }
    #endif
    
    param_initialized = 1;
}

param_t param_find(uint16_t param_id) {
    if (!param_initialized) {
        return PARAM_INVALID;
    }
    
    // Binary search implementation
    int32_t left = 0;
    int32_t right = PARAM_COUNT - 1;
    
    while (left <= right) {
        int32_t mid = left + (right - left) / 2;
        
        if (param_dict[mid].param_id == param_id) {
            return (param_t)mid; // Return array index as handle
        }
        
        if (param_dict[mid].param_id < param_id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return PARAM_INVALID; // Parameter not found
}

const char *param_name(param_t param) {
    if (param >= PARAM_COUNT) {
        return NULL;
    }
    
    return param_dict[param].name;
}

int32_t param_get(param_t param, void *val) {
    if (param >= PARAM_COUNT || val == NULL) {
        return -1; // Invalid parameter or null pointer
    }
    
    param_entry_t *entry = &param_dict[param];
    
    switch (entry->type) {
        case 0: // int32_t
            *(int32_t*)val = entry->value.i;
            break;
        case 1: // float
            *(float*)val = entry->value.f;
            break;
        case 2: // pointer
            *(void**)val = entry->value.p;
            break;
        default:
            return -2; // Invalid type
    }
    
    return 0; // Success
}