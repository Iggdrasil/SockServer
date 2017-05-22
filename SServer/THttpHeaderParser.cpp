#include "stdafx.h"
#include "THttpHeaderParser.h"


std::vector<std::string> THttpHeaderParser::split(const std::string & s, const std::string & delim)
{
	std::vector<std::string> splitted;
	if (s.empty())
	{
		return splitted;
	}
	size_t p = 0;
	for (;;) 
	{
		auto pos = s.find(delim, p);
		if (pos == std::string::npos) 
		{ 
			splitted.push_back(s.substr(p)); 
			return splitted;
		}
		splitted.push_back(s.substr(p, pos - p));
		p = pos + delim.size();
	}
	return splitted;
}
/*
std::string THttpHeaderParser::getMethod(const std::string & request)
{

}


std::string THttpHeaderParser::getUrl(const std::string & request)
{

}
*/
THttpHeaderParser::THttpHeaderParser()
{
}


THttpHeaderParser::~THttpHeaderParser()
{
}

bool THttpHeaderParser::parse(const std::string & header)
{
	std::vector<std::string> splitted = split(split(header, "\r\n\r\n")[0], "\r\n");



	return false;
}
