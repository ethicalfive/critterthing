#include "settingspanel.h"
#include "text.h"
#include "text_uintp.h"
#include "textinput.h"

Settingspanel::Settingspanel( bool resizable )
 : Panel(resizable)
 , m_margin(5)
 , m_time_interval(120)
 , m_button_margin(13)
{
// 	isTouchable = true;
// 	isTransparant = true;
// 	zaxis = 0;

	col1 = 10;
	col2 = 180;
	col3 = 220;
	col4 = 250;
	row = 10;
	rowspacer = 12;
}

void Settingspanel::addSection( const std::string& name, unsigned int posx, unsigned int posy )
{
	addWidget(name, Vector2i(posx+col1, posy+row+9), BeWidgetTextPtr(new BeWidgetText(name)));
	row += rowspacer;
}

void Settingspanel::addMutator( const std::string& name, const BeCommand& cmd1, const BeCommand& cmd2, unsigned int posx, unsigned int posy )
{

	std::string str(name); std::string strval = str; std::string strdec = str; std::string strinc = str; std::string strtextinput = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc"); strtextinput.append("textinput");
	
	addWidget(str, Vector2i(posx+col1+m_margin, posy+row+9), BeWidgetTextPtr(new BeWidgetText(name)));
// 	addWidgetText( str, posx+col1, posy+row+9, name );
	addWidget(strval, Vector2i(posx+col2+m_margin, posy+row+9), BeWidgetTextCVARuintPtr(new BeWidgetTextCVARuint(settings->getCVarPtr(name))));
// 	addWidgetText( strval, posx+col2, posy+row+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+col3+m_margin, posy+row), Vector2i(11, 10), "-", Vector2i(3, 8), cmd1, EVENT_REPEAT, m_time_interval );
	addWidgetButton( strinc, Vector2i(posx+col3+m_button_margin+m_margin, posy+row), Vector2i(11, 10), "+", Vector2i(1, 8), cmd2, EVENT_REPEAT, m_time_interval );
//	addWidgetTextInput( strtextinput,  Vector2i(posx+220+m_margin, posy+row), Vector2i(50, 10), BeWidgetTextCVARuintPtr(new BeWidgetTextCVARuint(settings->getCVarPtr(name))) , Vector2i(1, 8),BeCommand("settings_setInt", name) , EVENT_REPEAT, m_time_interval, name );//ethical
	addWidgetTextInput( strtextinput,  Vector2i(posx+col4+m_margin, posy+row), Vector2i(50, 11), "" , Vector2i(1, 8),BeCommand("settings_setInt", name) , EVENT_REPEAT, m_time_interval, name );//ethical
	row += rowspacer;	
	
  
	
}

/*
 * Ethicals notes for linking textinput field with value
 * 
 * 
 * This is responsible for updating a variable value
 * settings->setCVar("name", 0);
 * 
 * so we need to pass the new value in the text input to settings->setCVar("name", 0)
 * 
 * maybe we can pass on the name into textinput and send an update from inside there on pressing enter?
 * 
 * 
 */

void Settingspanel::addSettingmutator( const std::string& name, unsigned int posx, unsigned int posy )
{
	std::string str(name); std::string strval = str; std::string strdec = str; std::string strinc = str; std::string strtextinput = str;
	strval.append("val"); strdec.append("dec"); strinc.append("inc");strtextinput.append("textinput");

	addWidget(str, Vector2i(posx+col1+m_margin, posy+row+9), BeWidgetTextPtr(new BeWidgetText(name)));
// 	addWidgetText( str, posx+col1, posy+row+9, name );
	addWidget(strval, Vector2i(posx+col2+m_margin, posy+row+9), BeWidgetTextCVARuintPtr(new BeWidgetTextCVARuint(settings->getCVarPtr(name))));
// 	addWidgetText( strval, posx+col2, posy+row+9, settings->getCVarPtr(name) );
	addWidgetButton( strdec, Vector2i(posx+col3+m_margin, posy+row), Vector2i(11, 10), "-", Vector2i(3, 8), BeCommand("settings_decrease", name), EVENT_REPEAT, m_time_interval );
	addWidgetButton( strinc, Vector2i(posx+col3+m_button_margin+m_margin, posy+row), Vector2i(11, 10), "+", Vector2i(1, 8), BeCommand("settings_increase", name), EVENT_REPEAT, m_time_interval );
//	addWidgetTextInput( strtextinput,  Vector2i(posx+220+m_margin, posy+row), Vector2i(50, 10), BeWidgetTextCVARuintPtr(new BeWidgetTextCVARuint(settings->getCVarPtr(name))) , Vector2i(1, 8), BeCommand("settings_setInt", name), EVENT_REPEAT, m_time_interval, name );//ethical
	addWidgetTextInput( strtextinput,  Vector2i(posx+col4+m_margin, posy+row), Vector2i(50, 11), "" , Vector2i(1, 8), BeCommand("settings_setInt", name), EVENT_REPEAT, m_time_interval, name );//ethical
	row += rowspacer;
}

void Settingspanel::addCheckbox( const std::string& name, const BeCommand& cmd1, unsigned int posx, unsigned int posy )
{
	std::string str(name);
	std::string strinc(str);
	strinc.append("inc");

	addWidget(str, Vector2i(posx+col1+23+m_margin, posy+row+9), BeWidgetTextPtr(new BeWidgetText(name)));
// 	addWidgetText( str, posx+col1+23, posy+row+9, name );
	addWidgetCheckbox( strinc, Vector2i(posx+col1+m_margin, posy+row), Vector2i(11, 10), "x", Vector2i(3, 8), cmd1, name, EVENT_NOREPEAT, 0 );
	row += rowspacer;
}

void Settingspanel::addSettingcheckbox( const std::string& name, unsigned int posx, unsigned int posy )
{
	std::string str(name);
	std::string strinc(str);
	strinc.append("inc");

	addWidget(str, Vector2i(posx+col1+23+m_margin, posy+row+9), BeWidgetTextPtr(new BeWidgetText(name)));
// 	addWidgetText( str, posx+col1+23, posy+row+9, name );
	addWidgetCheckbox( strinc, Vector2i(posx+col1+m_margin, posy+row), Vector2i(11, 10), "x", Vector2i(3, 8), BeCommand("settings_increase", name), EVENT_NOREPEAT, 0 );
	row += rowspacer;
}
