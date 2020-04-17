#include"../KdLibrary.h"
#include"json11.hpp"
#include"MyJson.h"



bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json, const std::string& Tag, const std::string& Value)
{
	if ((*Json)[Tag].is_string() && (*Json)[Tag].string_value() == Value)return true;
	return false;
}

bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json,const std::string& Tag,const int& Value)
{
	
	if ((*Json)[Tag].is_number() && (*Json)[Tag].int_value() == Value) return true;
	return false;
}

bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json,const std::string& Tag,const bool& Value)
{
	if ((*Json)[Tag].is_bool() && (*Json)[Tag].bool_value() == Value)return true;
	return false;
}


bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json,const std::string& Tag,const double& Value)
{
	if ((*Json)[Tag].is_number() && (*Json)[Tag].number_value() == Value)return true;
	return false;
}
