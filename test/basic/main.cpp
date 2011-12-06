//#define JSON_VALUE_USE_INTERNAL_MAP
#pragma warning(disable:4786)
#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>
#include <iostream>
#include <string>
#include <fstream>

void test1()
{
	Json::Value object;
	object["hello"] = 1;
	Json::Value& value = (object["foo"] = Json::Value());
	value.append(1);
	value.append(2);
	value.append(3);
	value.append(4);
	Json::Value& v1 = (object["bar"] = Json::Value());
	v1["hello"] = "world";
	v1["1"] = 2;

	Json::StyledWriter writer;
	std::string s = writer.write(object);
	std::cout << s << std::endl;

	Json::Reader reader;
	Json::Value obj;
	bool b = reader.parse(s, obj);
	assert(b);
	std::cout << obj << std::endl;
}

void test2()
{
	Json::Value obj;
	Json::Reader reader;
	const char* const uncompleted = "{\"a\": 1}";
	bool b = reader.parse(uncompleted, obj);
	assert(b);
}

void test3()
{
	Json::Value object;
	Json::Reader reader;
	std::ifstream ifs("test3.json");
	assert(ifs);
	assert(reader.parse(ifs, object));

	std::cout << "object: " << object << std::endl;

	Json::StyledWriter writer;
	{
		Json::Path path(".data");
		const Json::Value& data = path.resolve(object);
		std::string result = writer.write(data);
		std::cout << "result: " << result << std::endl;
	}
	{
		Json::Path path(".data[1].foo");
		const Json::Value& foo = path.resolve(object);
		std::string result = writer.write(foo);
		std::cout << "result: " << result << std::endl;
	}
}

int main()
{
	test1();
	test2();
	test3();
	return 0;
}

