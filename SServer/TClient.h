#pragma once
class TClient
{
	char* data_;

public:
	TClient();
	~TClient();
	void addData(const char* src, size_t len);
	void printData();
	
};

