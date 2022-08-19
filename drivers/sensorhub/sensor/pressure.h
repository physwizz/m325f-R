#ifndef __SHUB_PRESSURE_H_
#define __SHUB_PRESSURE_H_

#include <linux/types.h>

struct pressure_event {
	s32 pressure;
	s16 temperature;
	s32 pressure_cal;
	s32 pressure_sealevel;
} __attribute__((__packed__));

struct pressure_chipset_funcs {
	void (*init)(void);
};

struct pressure_data {
	struct pressure_chipset_funcs *chipset_funcs;

	int sw_offset_default;
	int sw_offset;
	int convert_coef;
};

struct pressure_chipset_funcs *get_pressure_lps22hh_function_pointer(char *name);

int save_pressure_sw_offset_file(int offset);

#endif /* __SHUB_PRESSURE_H_ */
