#include "stdafx.h"
#include "TClient.h"
#include <iostream>

using std::cout;
using std::endl;


TClient::TClient()
	:data_(NULL), len_(0)
{
}


TClient::~TClient()
{
	delete[] data_;
}

void TClient::addData(const char * src, size_t len)
{
	if (src == NULL || len == 0)
	{
		return;
	}

	data_ = new char[len];
	memcpy(data_, src, len);
	len_ = len;
	return;
}

void TClient::printData()
{
	if (data_)
	{
		cout << "Packet data:" << endl;
		cout << data_ << endl;
	}
	else
	{
		cout << "No data" << endl;
	}
}

void TClient::getdata(char *& dst, size_t & len)
{
	if (data_ == NULL || len_ == 0)
	{
		return;
	}
	dst = data_;
	len = len_;
}
