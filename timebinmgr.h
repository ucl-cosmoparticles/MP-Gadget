#ifndef TIMEBINMGR_H
#define TIMEBINMGR_H
/* This file manages the integer timeline, 
 * and converts from integers ti to double loga.*/

/*!< The simulated timespan is mapped onto the integer interval [0,TIMEBASE],
 *   where TIMEBASE needs to be a power of 2. Note that (1<<28) corresponds
 *   to 2^29.
 *   We allow some bits at the top of the integer timeline for snapshot outputs.
 *   Note that because each snapshot uses TIMEBASE on the integer timeline, the conversion
 *   factor between loga and ti is not constant across snapshots.
 */
#define TIMEBINS 20
#define TIMEBASE (1u<<TIMEBINS)
#define MAXSNAPSHOTS (1u<<(30-TIMEBINS))

typedef struct SyncPoint SyncPoint;

struct SyncPoint
{
    double loga;
    int write_snapshot;
    int write_fof;
    inttime_t ti;
};


/*Convert an integer to and from loga*/
double loga_from_ti(inttime_t ti);
inttime_t ti_from_loga(double loga);

/*Convert changes in loga to and from ti*/
inttime_t dti_from_dloga(double loga);
double dloga_from_dti(inttime_t ti);

/*Get dloga from a timebin*/
double get_dloga_for_bin(int timebin);

/* Enforce that an integer timestep is a power
 * of two subdivision of TIMEBASE, rounding down
 * to the first power of two less than the ti passed in.
 * Note TIMEBASE is the maximum value returned.*/
inttime_t round_down_power_of_two(inttime_t ti);

/*! this function returns the next output time after ti_curr.*/
inttime_t find_next_outputtime(inttime_t ti_curr);

/*Get whatever is the last output number from ti*/
inttime_t out_from_ti(inttime_t ti);

void setup_sync_points(void);

SyncPoint *
find_next_sync_point(inttime_t ti);

SyncPoint *
find_current_sync_point(inttime_t ti);

SyncPoint *
make_unplanned_sync_point(inttime_t ti);

#endif
