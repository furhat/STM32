#ifndef TOUCH_POINT___H
#define TOUCH_POINT___H


#include "stm32f4xx.h"
#include "touch_defines.h"

#define MAX_TRACK_EDGE 3

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
	bool operator !=(const touch_coord_t & other) const;
	bool is_null(void);
	bool is_not_null(void);

};

typedef struct
{
	int16_t x;
	int16_t y;	
}coord_dist_t;

typedef struct
{
	int16_t ids[MAX_TRACK_EDGE];
	int16_t num;
	
	void insert(uint16_t i){
		ids[num] = i;
		num++;
	}
	
	void reset(void){
		num = 0;
	}
	
}edge_record_t;


class touch_point_t
{
public:
	touch_point_t();
	
	
	coord_dist_t get_latest_move_distance(void);

	void die();

	void coord_change(touch_coord_t a_coord);

	touch_coord_t* get_p(void); 

	bool is_moved();
	bool is_pressed();
	bool is_released();

	bool is_double_click();
	
	

	TOUCH_STATE m_state;
	TOUCH_STATE m_last_state;
	

private:

	//int8_t m_tid;
	touch_coord_t m_d[MAX_HIS_COORDS + 1];
	uint32_t m_data_num;

	//save the index of the nth rises/falls
	edge_record_t m_rises;
	edge_record_t	m_falls;

	
	void ripple_data(touch_coord_t a_coord);
	void stats_edges(void);

	bool is_rise(uint16_t i);
	bool is_fall(uint16_t i);

	// for debug
	int16_t m_start_flag;
	int16_t	m_count_from_start;
	
	
};

#endif
