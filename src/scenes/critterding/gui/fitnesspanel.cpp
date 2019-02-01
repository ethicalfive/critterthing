#include "fitnesspanel.h"

Fitnesspanel::Fitnesspanel()
{
	isMovable = true;

	m_localposition.set(2, 24);

	col2 = 270;
	col3 = 350;
	col4 = 380;
	
	row+=8;
	addSection("Eliminate portion of population", 0, 0);
	addSettingmutator("population_eliminate_portion_percent", 0, 0);
	
	row+=8;
	addSection("fitnessmode", 0, 0);
	addSettingcheckbox("fitness_height", 0, 0);
	addSettingcheckbox("fitness_distance", 0, 0);
	addSettingcheckbox("fitness_jump", 0, 0);
	



	


	m_dimensions.set(col4 + 70, row-rowspacer+10+10);  // 10 = height of 1 line, 10 = horizontal margin

	BeWidgetPtr w = addWidgetButton( "fitnesspanel_close", Vector2i(2, 2), Vector2i(12, 12), "x", BeCommand("gui_togglepanel", "fitnesspanel"), EVENT_NOREPEAT, 0 );
		w->isAlignedRight = true;
	
}

Fitnesspanel::~Fitnesspanel()
{
}
