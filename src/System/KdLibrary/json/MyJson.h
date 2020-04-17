#pragma once


class MyJson {

private:
	MyJson() {};
	~MyJson() {};

	std::map<std::string, std::shared_ptr<json11::Json>>jsons;


public:
	static MyJson& GetInstance()
	{
		static MyJson instance;
		return instance;

	}

	inline 	std::shared_ptr <json11::Json> LoadJson(const std::string& filename) {
		
		//ÉäÉXÉgì‡åüçı
		if (jsons.find(filename) != jsons.end()) {
			return jsons[filename];
		}

		auto mfilename = "Resouce/JsonData/" + filename;

		std::ifstream ifs(mfilename);
		if (!ifs) { return nullptr; }

		std::string strJson(
			(std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>())
		);

		//âêÕ
		std::string err;

		auto Json = std::make_shared<json11::Json>();
		//Json->parse(strJson, err);
		(*Json).parse(strJson, err);
		if (err.size() > 0) { return nullptr; }


		
		jsons[filename] = Json;
		return Json;
	}

	bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const int& Value);
	bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const bool Value);
	bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const std::string& Value);
	bool checkValue(const std::shared_ptr < json11::Json>Json, const std::string& Tag, const double& Value);
};
#define JSONS MyJson::GetInstance()