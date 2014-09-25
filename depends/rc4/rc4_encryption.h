
/*
* zsummerX License
* -----------
*
* zsummerX is licensed under the terms of the MIT license reproduced below.
* This means that zsummerX is free software and can be used for both academic
* and commercial purposes at absolutely no cost.
*
*
* ===============================================================================
*
* Copyright (C) 2013 YaweiZhang <yawei_zhang@foxmail.com>.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* ===============================================================================
*
* (end of COPYRIGHT)
*/



#ifndef _RC4_ENCRYPTION_H 
#define _RC4_ENCRYPTION_H

class CRC4Encryption
{
public:
	void MakeSBox(std::string obscure)
	{
		m_x = 0;
		m_y = 0;
		for (int i = 0; i < 256; i++)
		{
			m_box[i] = i;
		}
		if (!obscure.empty())
		{
			int j = 0;
			int k = 0;
			const unsigned char * obs = (const unsigned char *)obscure.c_str();
			int lenth = (int)obscure.length();
			for (int i = 0; i < 256; i++)
			{
				int tmp = m_box[i];
				j = (unsigned char)(j + tmp + obs[k]);
				m_box[i] = m_box[j];
				m_box[j] = tmp;
				if (++k >= lenth)
				{
					k = 0;
				}
			}
		}
	}

	void RC4Encryption(unsigned char * data, int length)
	{
		int  x, y;

		x = m_x;
		y = m_y;

		for (int i = 0; i < length; i++)
		{
			x = (unsigned char)(x + 1);
			int a = m_box[x];
			y = (unsigned char)(y + a);
			int b = m_box[x] = m_box[y];
			m_box[y] = a;
			data[i] ^= m_box[(unsigned char)(a + b)];
		}

		m_x = x;
		m_y = y;
	}
private:

	int m_x;
	int m_y;
	int m_box[256];
};






#endif 



