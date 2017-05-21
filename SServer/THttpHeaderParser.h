#pragma once
#include <string>
#include <vector>

class THttpHeaderParser
{
	static std::vector<std::string> split(const std::string&s, const std::string& stop);
	static std::string getMethod(const std::string& request);
	static std::string ScanParam(const std::string& Before, const std::string& Where, const std::string& After, int& Pos);
	static std::string getUrl(const std::string& request);
public:
	THttpHeaderParser();
	~THttpHeaderParser();

	static bool parse(const std::string& header);
};

