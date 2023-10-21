#include <iostream>
using namespace std;

// Creating a table of constants
char constTable[2][16] = {
	// For the first four bits
	{'9', '6', '3', '2', '8', 'B', '1', '7', 'A', '4', 'E', 'F', 'C', '0', 'D', '5'},
	// For the last four bits
	{'3', '7', 'E', '9', '8', 'A', 'F', '0', '5', '2', '6', 'C', 'B', '4', 'D', '1'}
};

char newTable[2][16];

char S_blok_1(char byte, char table[2][16]) // Encryption
{
	char res;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 16; j++) 
		{
			if (i == 0 && j == byte >> 4)
			{
				if (table[i][j] == 'A' || table[i][j] == 'B' || table[i][j] == 'C' || table[i][j] == 'D' || table[i][j] == 'E' || table[i][j] == 'F')
				{
					res = (table[i][j] - '0' - 7) << 4;
				}
				else
				{
					res = (table[i][j] - '0') << 4;
				}
				break;
			}
			else if (i == 1 && ((byte & 0x0F) == j))
			{
				if (table[i][j] == 'A' || table[i][j] == 'B' || table[i][j] == 'C' || table[i][j] == 'D' || table[i][j] == 'E' || table[i][j] == 'F')
				{
					res = res | (table[i][j] - '0' - 7);
				}
				else
				{
					res = res | (table[i][j] - '0');
				}
				break;
			}
		}
	}
	return res;
}

void S_blok_2(const char table[2][16], char newTable[2][16]) // Create table reverce
{
	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < 16; j++) 
		{
			char value = table[i][j];
			if (value == 'A' || value == 'B' || value == 'C' || value == 'D' || value == 'E' || value == 'F')
			{
				int index = value - '0' - 7;
				if (j > 9)
				{
					newTable[i][index] = j + '0' + 7;
				}
				else
				{
					newTable[i][index] = j + '0';
				}
			}
			else
			{
				int index = value - '0';
				if (j > 9)
				{
					newTable[i][index] = j + '0' + 7;
				}
				else
				{
					newTable[i][index] = j + '0';
				}
			}
		}
	}
}

struct bites
{
	short bit1 : 1;
	short bit2 : 1;
	short bit3 : 1;
	short bit4 : 1;
	short bit5 : 1;
	short bit6 : 1;
	short bit7 : 1;
	short bit8 : 1;
};


union char_bites
{
	char symbol;
	bites bit;
};

char P_block_1(char_bites ch)
{
	char_bites res;
	res.bit.bit1 = ch.bit.bit2;
	res.bit.bit2 = ch.bit.bit8;
	res.bit.bit3 = ch.bit.bit1;
	res.bit.bit4 = ch.bit.bit5;
	res.bit.bit5 = ch.bit.bit7;
	res.bit.bit6 = ch.bit.bit3;
	res.bit.bit7 = ch.bit.bit6;
	res.bit.bit8 = ch.bit.bit4;
	return res.symbol;
}


char P_block_2(char_bites ch)
{
	char_bites res;
	res.bit.bit1 = ch.bit.bit3;
	res.bit.bit2 = ch.bit.bit1;
	res.bit.bit3 = ch.bit.bit6;
	res.bit.bit4 = ch.bit.bit8;
	res.bit.bit5 = ch.bit.bit4;
	res.bit.bit6 = ch.bit.bit7;
	res.bit.bit7 = ch.bit.bit5;
	res.bit.bit8 = ch.bit.bit2;
	return res.symbol;
}

int main()
{
		//------------------------ S-block encryption
		cout << "Enter symbol: ";
		char byte_after;
		cin >> byte_after;
		char byte_before = S_blok_1(byte_after, constTable);
		cout << byte_after << " ---> " << byte_before << endl;

		S_blok_2(constTable, newTable);

		cout << byte_before << " ---> " << S_blok_1(byte_before, newTable) << endl;

		//------------------------ P - block encryption
		char_bites pb, res1, res2;
		cout << "Enter symbol: ";
		cin >> pb.symbol;
		res1.symbol = P_block_1(pb);
		cout << pb.symbol << " ----> " << res1.symbol << endl;
		res2.symbol = P_block_2(res1);
		cout << res1.symbol << " ----> " << res2.symbol << endl;

	return 0;
}