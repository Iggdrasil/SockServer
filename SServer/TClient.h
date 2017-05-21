#pragma once
class TClient
{
	char* data_;
	size_t len_;

public:
	TClient();
	~TClient();
	void addData(const char* src, size_t len);
	void printData();
	void getdata(char*& dst, size_t& len);
	
};

