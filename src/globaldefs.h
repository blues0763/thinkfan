/************************************************************************
 * globaldefs.h: Stuff that's needed by all objects
 *
 * this file is part of thinkfan. See thinkfan.c for further information.
 *
 * thinkfan is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * thinkfan is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with thinkfan.  If not, see <http://www.gnu.org/licenses/>.
 *
 ************************************************************************/
#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>

#define VERSION "0.9.1"

#define ERR_T_GET          1
#define ERR_FAN_INIT       1<<1
#define ERR_CONF_NOFILE    1<<2
#define ERR_CONF_LOST      1<<3
#define ERR_CONF_RELOAD    1<<4
#define ERR_PIDFILE        1<<5
#define ERR_FORK           1<<6
#define ERR_MALLOC         1<<7
#define ERR_CONF_LOWHIGH   1<<8
#define ERR_CONF_LVLORDER  1<<9
#define ERR_CONF_ORDERLOW  1<<10
#define ERR_CONF_ORDERHIGH 1<<11
#define ERR_CONF_OVERLAP   1<<12
#define ERR_CONF_LVL0      1<<13
#define ERR_FAN_SET        1<<14
#define ERR_CONF_LIMIT     1<<15
#define WRN_CONF_INTMIN_LVL 1<<16
#define ERR_CONF_LVLFORMAT 1<<17
#define ERR_CONF_LIMITLEN  1<<18

#ifndef DUMMYRUN
#define PID_FILE "/var/run/thinkfan.pid"
#define IBM_TEMP "/proc/acpi/ibm/thermal"
#define IBM_FAN "/proc/acpi/ibm/fan"
#else
#define PID_FILE "/tmp/thinkfan.pid"
#define IBM_TEMP "/tmp/thermal"
#define IBM_FAN "/tmp/fan"
#endif //DUMMYRUN

#ifndef MAXERR
#define MAXERR 2
#endif

// Stolen from the gurus
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

struct limit {
	char *level; // this is written to the fan control file.
	int nlevel;   // A numeric interpretation of the level
	int *low;   // int array specifying the LOWER limit, terminated by INT_MIN
	int *high;  // dito for UPPER limit.
};

struct sensor {
	char *path;
	int bias[16];
	void (*get_temp)();
};

struct tf_config {
	struct sensor *sensors;
	int num_sensors;
	char *fan;
	struct limit *limits;
	int num_limits;
	int limit_len;
	void (*setfan)();
	void (*init_fan)();
	void (*uninit_fan)();
	int (*lvl_up)();
	int (*lvl_down)();
	int (*cmp_lvl)();
	void (*get_temps)();
	int used_temps; // how many temperatures do we expect to find?
};


struct tf_config *config;
unsigned long int errcnt;
int *temps, tmax, last_tmax, lvl_idx, *b_tmax, line_count;
int	tempidx; // global index into global temps[] array
int sensoridx; // separate since one sensor may have multiple temps (ibm)
int found_temps; // how may temperatures we actually found
unsigned int watchdog_timeout, num_temps;
char quiet, nodaemon, resume_is_safe, chk_sanity;
char *config_file, *prefix, *rbuf,
	*cur_lvl,
	*oldpwm; // old contents of pwm*_enable, used for uninit_fan()
float bias_level, depulse_tmp;
useconds_t depulse;

int triggered_tidx;

#ifdef USE_ATASMART
char dnd_disk;
#endif

#define FALSE 0
#define TRUE !FALSE
#define TEMP_UNUSED INT_MAX


#endif


