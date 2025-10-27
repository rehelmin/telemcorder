#ifndef __PARAM_H
#define __PARAM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t param_t;

#define PARAM_INVALID	((uint16_t)0xffff)

/**
 * @brief Initialize the parameter dictionary
 */
void param_init(void);
param_t	param_find(uint16_t param_id);
const char *param_name(param_t param);

/**
 * @brief Retrieve a value of a parameter at a given index
 * 
 * @param param		A parameter handle returned by param_find
 * @param val		A pointer for storing the value of appropriate type
 * @return 			Zero if parameter value was successfully retrieved, nonzero otherwise
 */
int32_t param_get(param_t param, void *val);

/**
 * @brief Write a value of a parameter at a given index
 * 
 * @param param		A parameter handle returned by param_find
 * @param val		A pointer for storing the value of appropriate type
 * @return 			Zero if parameter value was successfully retrieved, nonzero otherwise
 */
int32_t param_set(param_t param, const void *val);

union param_value_u {
	void		*p;
	int32_t		i;
	float		f;
};


#ifdef __cplusplus
}
#endif

#endif /* __PARAM_H */
