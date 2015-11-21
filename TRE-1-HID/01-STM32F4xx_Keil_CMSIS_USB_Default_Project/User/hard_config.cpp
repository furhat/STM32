#include "hard_config.h"
#include "touch_driver_stmpe811.h"
#include "touch_driver_ft5x06.h"


static touch_driver_stmpe811 	g_stmpe811;
static touch_driver_ft5x06		g_ft5x06;

touch_driver_t* hard_config_t::get_touch_driver(void)
{
	// return &g_stmpe811;
	return &g_ft5x06;
}
