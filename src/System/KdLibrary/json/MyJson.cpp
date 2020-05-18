#include"../KdLibrary.h"
#include"json11.hpp"
#include"MyJson.h"



 bool MyJson::checkValue(const std::shared_ptr<json11::Json>Json, const std::string& Tag,const std::string& Value)
{
	if ((*Json)[Tag].is_string() && (*Json)[Tag].string_value() == Value)return true;
	 else return false;
}

 bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json, const std::string& Tag, const int& Value)
{
	if ((*Json)[Tag].is_number() && (*Json)[Tag].int_value() == Value) return true;

	else return false;
}

 bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json, const std::string& Tag, const double& Value)
{
	if ((*Json)[Tag].is_number() && (*Json)[Tag].number_value() == Value)return true;

	else return false;
}

 bool MyJson::checkValue(const std::shared_ptr<json11::Json> Json, const std::string& Tag, const bool& Value)
{
	if ((*Json)[Tag].is_bool() && (*Json)[Tag].bool_value() == Value)return true;

	else return false;
}

const std::shared_ptr < json11::Json>& MyJson::GetArray(const std::shared_ptr<json11::Json> Json, const std::string& Tag)
 {		std::shared_ptr < json11::Json>mJson;
	if ((*Json)[Tag].is_array()) {

		
		(*mJson)=(*Json)[Tag].array_items();

	}
	return mJson;
	// TODO: return ステートメントをここに挿入します
 }





 void MyJson::AddKeyValue(std::shared_ptr<json11::Json> Json, const std::string& Tag,  const std::string Value)
{
	(*Json)[Tag] = Value;
}
 void MyJson::AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const int Value)
{
	(*Json)[Tag] = Value;
}
 void MyJson::AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const double Value)
{
	(*Json)[Tag] = Value;
}
 void MyJson::AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const bool Value)
{
	(*Json)[Tag] = Value;
}
 void MyJson::AddKeyValue( std::shared_ptr<json11::Json> Json, const std::string& Tag, const json11::Json& Value)
{
	(*Json)[Tag] = Value;
}


//
//void MyJson::AddKeyValue(D& Json, const std::string& Tag, const E& Value)
//{
//	Json[Tag] = Value;
//}





