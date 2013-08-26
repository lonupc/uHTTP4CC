/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002-2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <uhttp/io/BufferedReader.h>
#include <uhttp/util/TimeUtil.h>

using namespace uHTTP;
using namespace uHTTP;

static const char LF = '\n';
static const char CR = '\r';

const char *BufferedReader::readLine()
{
	char readChar = 0;
	lineStr = "";

	// Read line until CR & LF
	int readLen = reader->read(lineStr, 1);
	if (readLen <= 0)
		return "";

	while (0 < readLen) {
		int lastPos = lineStr.size() - 1;
		readChar = lineStr.at(lastPos);
		if (readChar == CR || readChar == LF) {
			lineStr = lineStr.substr(0, lastPos);
			break;
		}
		readLen = reader->read(lineStr, 1);
	}

	// Skip next LF ?
	if (readChar == CR) {
		std::string skipChar;
		readLen = reader->read(skipChar, 1);
		if (0 < readLen) {
			readChar = skipChar.at(0);
			if (readChar != LF)
				unread(readChar);
		}
	}

	return lineStr.c_str();
}