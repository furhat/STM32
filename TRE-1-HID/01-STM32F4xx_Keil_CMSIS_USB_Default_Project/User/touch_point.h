#ifndef TOUCH_POINT___H
#define TOUCH_POINT___H


#include "stm32f4xx.h"
#include "touch_defines.h"


typedef struct
{
	uint16_t x;
	uint16_t y;
}touch_coord_t;

typedef struct
{
	uint16_t x;
	uint16_t y;	
}coord_dist_t;

class touch_point_t
{
public:
	touch_point_t();
	
	void add_coord(touch_coord_t a_coord);
	coord_dist_t get_latest_move_distance(void);
	void reset();

private:
	touch_coord_t m_coords[MAX_HIS_COORDS];
	uint32_t m_data_num;
	
};

#endif
