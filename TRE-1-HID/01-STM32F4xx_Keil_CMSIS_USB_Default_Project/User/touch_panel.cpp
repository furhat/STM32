#include "touch_panel.h"


#define MOUSE_MOVE_AMP 3

touch_panel_t::touch_panel_t()
{
}

touch_panel_t::touch_panel_t(touch_driver_t* a_driver)
:m_touch_driver(a_driver)
{
}

void touch_panel_t::set_touch_driver(touch_driver_t* a_driver)
{
	m_touch_driver = a_driver;
}



action_t* touch_panel_t::check_action(void)
{
	action_t* l_action = &m_action_factory.act_null;
	
	// only consider one point for this phase	
	touch_point_t* l_p = &m_points[0];
	if(l_p->m_last_state == TOUCH_STATE_DEAD && l_p->m_state == TOUCH_STATE_PRESSING)
	{
		l_action = &m_action_factory.act_l1_click_down;			
	}
	else if(l_p->m_last_state == TOUCH_STATE_PRESSING && l_p->m_state == TOUCH_STATE_DEAD)
	{
		l_action = &m_action_factory.act_l1_click_up;
	}
	else if(l_p->m_state == TOUCH_STATE_MOVING)
	{
		coord_dist_t l_dis = l_p->get_latest_move_distance();
		m_action_factory.act_mouse_move.set_value(MOUSE_MOVE_AMP * l_dis.x, MOUSE_MOVE_AMP * l_dis.y);
		l_action = &m_action_factory.act_mouse_move;		
	}
	
	// backup the state
	l_p->m_last_state = l_p->m_state;

	return l_action;	
}





void touch_panel_t::update_point_data(void)
{
	uint8_t l_update_flag = 0;
	const TouchScreen_Data_t* l_touch_data = m_touch_driver->get_touch_points();
	
	for(uint8_t i = 0; i < l_touch_data->touch_point; i++)
	{
		/* ID starts from 0 */
		uint8_t l_id = l_touch_data->touches[i].t_id;
		m_points[l_id].coord_change(touch_coord_t(l_touch_data->touches[i].x, l_touch_data->touches[i].y));
		l_update_flag |= (0x01 << l_id);		
	}
	
	// for those when get no touch detected, set die
	for(uint8_t i = 0; i < MAX_TOUCH_POINT; i++)
	{
		if((l_update_flag & (0x01 << i)) == 0 && m_points[i].m_state != TOUCH_STATE_DEAD)
		{
			m_points[i].die();
		}
	}
}


struct touch_point_status touch_panel_t::get_active_point(void)
{
	struct touch_point_status result = {0};
	for(uint8_t i = 0; i < MAX_TOUCH_POINT; i++)
	{
		if(m_points[i].m_state != TOUCH_STATE_DEAD)
		{
			result.p[result.n] = &m_points[i];
			result.n++;			
		}		
	}
	return result;
}
