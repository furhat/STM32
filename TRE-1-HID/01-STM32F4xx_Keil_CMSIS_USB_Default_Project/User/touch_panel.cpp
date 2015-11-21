#include "touch_panel.h"
#include "log.h"
#include "stdio.h"


#define MOUSE_MOVE_AMP 3

touch_panel_t::touch_panel_t()
{
	m_touch_driver = NULL;
	m_last_action = &m_action_factory.act_null;
}

touch_panel_t::touch_panel_t(touch_driver_t* a_driver)
:m_touch_driver(a_driver)
{
	m_last_action = &m_action_factory.act_null;
}

void touch_panel_t::set_touch_driver(touch_driver_t* a_driver)
{
	m_touch_driver = a_driver;
}



action_t* touch_panel_t::check_action(void)
{
	action_t* l_action = &m_action_factory.act_null;

	if(m_points[0].is_moved())
	{
		coord_dist_t l_dis = m_points[0].get_latest_move_distance();
		m_action_factory.act_mouse_move.set_value(MOUSE_MOVE_AMP * l_dis.x, MOUSE_MOVE_AMP * l_dis.y);
		l_action = &m_action_factory.act_mouse_move;		
	}
	else if(m_points[0].is_released())
	{
		// discard the release from a moving press
		if(m_last_action != &m_action_factory.act_mouse_move)
		{
			if(m_points[0].is_double_click())
			{
				l_action = &m_action_factory.act_l1_click_t;
			}
		}
	}

	
	
	
	
	/*
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
	
	
	l_p->m_last_state = l_p->m_state;
	
	*/
	
	if(l_action == &m_action_factory.act_null && m_last_action != &m_action_factory.act_null)	{
		m_points[0].die();
	}

	m_last_action = l_action;
	return l_action;	
}





void touch_panel_t::update_point_data(void)
{
	uint8_t l_update_flag = 0;
	const TouchScreen_Data_t* l_touch_data = m_touch_driver->get_touch_points();
	
	if(l_touch_data->touch_point > 0)
	{
		/*
		char str[LOG_MAX_SIZE] = {0};
		sprintf(str, "points: %d\nid=%d,x1=%d,y1=%d\nid=%d, x2=%d, y2=%d\n...", 
			l_touch_data->touch_point, l_touch_data->touches[0].t_id, l_touch_data->touches[0].x, l_touch_data->touches[0].y, l_touch_data->touches[1].t_id, l_touch_data->touches[1].x, l_touch_data->touches[1].y);			
		log(1, str);
		*/
	}

	
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
		if((l_update_flag & (0x01 << i)) == 0)
		{
			m_points[i].coord_change(touch_coord_t(0, 0));
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
