#include "touch_point.h"
#include "string.h"

touch_point_t::touch_point_t():
m_data_num(0)
{
	memset(m_coords, 0x00, MAX_HIS_COORDS*sizeof(touch_coord_t));
}

void touch_point_t::add_coord(touch_coord_t a_coord)
{
}

coord_dist_t touch_point_t::get_latest_move_distance(void)
{
	coord_dist_t l_dist;
	return l_dist;
	
}
void touch_point_t::reset()
{
}
