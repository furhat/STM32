#include "touch_point.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

touch_coord_t::touch_coord_t():x(0),y(0)
{}

touch_coord_t::touch_coord_t(uint16_t a_x, uint16_t a_y):x(a_x), y(a_y)
{}
	
bool touch_coord_t::operator ==(const touch_coord_t & other) const
{
	if((abs((float)(this->x - other.x)) + abs((float)(this->y - other.y))) < MOVE_THREDHOLD)
		return true;
	else
		return false;	
}

bool touch_coord_t::operator !=(const touch_coord_t & other) const
{
	if((abs((float)(this->x - other.x)) + abs((float)(this->y - other.y))) >= MOVE_THREDHOLD)
		return true;
	else
		return false;
	
}

bool touch_coord_t::is_null(void)
{
	if((x == 0) && (y == 0))
		return 1;
	else 
		return 0;
}

bool touch_coord_t::is_not_null(void)
{
	if((x != 0) || (y != 0))
		return 1;
	else
		return 0;
}


// ===========================================================
touch_point_t::touch_point_t()
{
	die();
	m_start_flag = 0;
	m_count_from_start = 0;
}

void touch_point_t::coord_change(touch_coord_t a_coord)
{			
	ripple_data(a_coord);	
	if(m_data_num < MAX_HIS_COORDS) m_data_num++;
	
	
// for debug 	
#if 1
	if(a_coord.is_not_null())
	{
		m_start_flag = 1;
	}
	
	if(m_start_flag == 1)
	{
		m_count_from_start++;
		if(m_count_from_start > 60)
		{
			touch_coord_t* p = m_d;	
		}		
	}
#endif	
	
/*	
	if(!a_coord.is_null())	
	{
		ripple_data(a_coord);
		
		if(m_data_num < MAX_HIS_COORDS) m_data_num++;
		
		
		if(m_state == TOUCH_STATE_DEAD)
		{
			m_state = TOUCH_STATE_PRESSING;
		}
		else if(m_state == TOUCH_STATE_PRESSING && is_moved())
		{
			m_state = TOUCH_STATE_MOVING;
		}
	}
*/	
}


void touch_point_t::ripple_data(touch_coord_t a_coord)
{
	if(m_data_num > 0)
	{
		for(int16_t i = m_data_num - 1; i > 0; i--)
		{
			m_d[i] = m_d[i-1];
		}
	}
	
	m_d[0] = a_coord;
}

coord_dist_t touch_point_t::get_latest_move_distance(void)
{
	coord_dist_t l_dist;
	l_dist.x = m_d[0].x - m_d[1].x;
	l_dist.y = m_d[0].y - m_d[1].y;	
	return l_dist;
	
}

bool touch_point_t::is_moved()
{
	if(m_data_num < 2) return false;	
	return (m_d[0].is_not_null() && m_d[1].is_not_null() && m_d[0] != m_d[1]);
	
}


bool touch_point_t::is_pressed()
{
	return is_rise(0);	
}

bool touch_point_t::is_released()
{
	return is_fall(0);
}
	

void touch_point_t::die()
{
	m_state = TOUCH_STATE_DEAD;
	m_last_state = TOUCH_STATE_DEAD;
	m_data_num = 0;
	m_rises.reset();
	m_falls.reset();
	
	memset(m_d, 0x00, (MAX_HIS_COORDS + 1)*sizeof(touch_coord_t));
}

touch_coord_t* touch_point_t::get_p(void)
{
	return m_d;
}

void touch_point_t::stats_edges(void){
	for(uint16_t i = 0; i < MAX_HIS_COORDS; i++){
		if(is_rise(i) && m_rises.num < MAX_TRACK_EDGE){
			m_rises.insert(i);
		}
		if(is_fall(i) && m_falls.num < MAX_TRACK_EDGE){
			m_falls.insert(i);
		}			
	}
}

bool touch_point_t::is_rise(uint16_t i){
	if( i > (MAX_HIS_COORDS-1)) return false;
	return (m_d[i].is_not_null() && m_d[i+1].is_null());
}

bool touch_point_t::is_fall(uint16_t i){
	if( i > (MAX_HIS_COORDS-1)) return false;
	return (m_d[i].is_null() && m_d[i+1].is_not_null());
}

bool touch_point_t::is_double_click()
{
	if(!is_fall(0)){
		return false;
	}
	
	stats_edges();
	
	if(m_rises.num < 2 || m_falls.num < 2){
		return false;
	}
	
	if((m_rises.ids[0] - m_falls.ids[0]) < 5 
		&& (m_rises.ids[1] - m_falls.ids[1]) < 5
		&& (m_falls.ids[1] - m_rises.ids[0]) < 10  ){
			return true;
	}
	
	return false;
	
	
	
	
}

	
