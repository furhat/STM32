#ifndef TOUCH_POINT___H
#define TOUCH_POINT___H


#include "stm32f4xx.h"
#include "touch_defines.h"

typedef enum{
	TOUCH_STATE_DEAD = 0,
	TOUCH_STATE_PRESSING,
	TOUCH_STATE_MOVING,	
} TOUCH_STATE;


class touch_coord_t
{
public:
	uint16_t x;
	uint16_t y;

	touch_coord_t(uint16_t x, uint16_t y);
	touch_coord_t(void);
	
	bool operator ==(const touch_coord_t & other) const;
	bool is_null(void);

};

typedef struct
{
	int16_t x;
	int16_t y;	
}coord_dist_t;

class touch_point_t
{
public:
	touch_point_t();
	
	
	coord_dist_t get_latest_move_distance(void);

	void die();

	void coord_change(touch_coord_t a_coord);
	
	TOUCH_STATE m_state;
	TOUCH_STATE m_last_state;
	

private:

	//int8_t m_tid;
	touch_coord_t m_his_coords[MAX_HIS_COORDS + 1];
	uint32_t m_data_num;

	bool is_moved();
	void ripple_data(touch_coord_t a_coord);
	
	
};

#endif
