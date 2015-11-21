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
	if((abs((float)(this->x - other.x)) + abs((float)(this->y - other.y))) > MOVE_THREDHOLD)
		return true;
	else
		return false;	
}

bool touch_coord_t::is_null(void)
{
	return (x == 0) && (y == 0);
}


// ===========================================================
touch_point_t::touch_point_t()
{
	die();
}

void touch_point_t::coord_change(touch_coord_t a_coord)
{
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
}


void touch_point_t::ripple_data(touch_coord_t a_coord)
{
	if(m_data_num > 0)
	{
		for(int16_t i = m_data_num; i > 0; i--)
		{
			m_his_coords[i] = m_his_coords[i - 1];
		}
	}
	
	m_his_coords[0] = a_coord;
}

coord_dist_t touch_point_t::get_latest_move_distance(void)
{
	coord_dist_t l_dist;
	l_dist.x = m_his_coords[0].x - m_his_coords[1].x;
	l_dist.y = m_his_coords[0].y - m_his_coords[1].y;	
	return l_dist;
	
}

bool touch_point_t::is_moved()
{
	if(m_data_num < 2) return false;
	return !(m_his_coords[0] == m_his_coords[1]);
	
}

void touch_point_t::die()
{
	m_state = TOUCH_STATE_DEAD;
	m_last_state = TOUCH_STATE_DEAD;
	m_data_num = 0;
	
	memset(m_his_coords, 0x00, (MAX_HIS_COORDS + 1)*sizeof(touch_coord_t));
}
