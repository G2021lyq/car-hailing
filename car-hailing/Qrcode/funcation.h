﻿#define VersionLevel 0						//b版本纠错等级 0：L	1：M	2：Q	3：H	可根据需要更改

struct QRVersion
{
	unsigned char Version;					//版本
	unsigned char Level;					//纠错等级
	unsigned char SideSize;					//边界大小
	short DataCodeWordsNo;					//数据码字数
	unsigned char RemainBit;				//剩余位
	short ECCodeWordsNo;					//每块纠错码字数
	unsigned char Block1No;					//包含块1数量
	unsigned char Block1DataCodeWordsNo;	//块1中数据码字数
	unsigned char Block2No;					//包含块2数量
	unsigned char Block2DataCodeWordsNo;	//块2中数据码字数
};
const QRVersion AllVersion[] = {
	{ 1,'L',21,19,0,7,1,19,0,0 },
	{ 1,'M',21,16,0,10,1,16,0,0 },
	{ 1,'Q',21,13,0,13,1,13,0,0 },
	{ 1,'H',21,9,0,17,1,9,0,0 },
	{ 2,'L',25,34,7,10,1,34,0,0 },
	{ 2,'M',25,28,7,16,1,28,0,0 },
	{ 2,'Q',25,22,7,22,1,22,0,0 },
	{ 2,'H',25,16,7,28,1,16,0,0 },
	{ 3,'L',29,55,7,15,1,55,0,0 },
	{ 3,'M',29,44,7,26,1,44,0,0 },
	{ 3,'Q',29,34,7,18,2,17,0,0 },
	{ 3,'H',29,26,7,22,2,13,0,0 },
	{ 4,'L',33,80,7,20,1,80,0,0 },
	{ 4,'M',33,64,7,18,2,32,0,0 },
	{ 4,'Q',33,48,7,26,2,24,0,0 },
	{ 4,'H',33,36,7,16,4,9,0,0 },
	{ 5,'L',37,108,7,26,1,108,0,0 },
	{ 5,'M',37,86,7,24,2,43,0,0 },
	{ 5,'Q',37,62,7,18,2,15,2,16 },
	{ 5,'H',37,46,7,22,2,11,2,12 },
	{ 6,'L',41,136,7,18,2,68,0,0 },
	{ 6,'M',41,108,7,16,4,27,0,0 },
	{ 6,'Q',41,76,7,24,4,19,0,0 },
	{ 6,'H',41,60,7,28,4,15,0,0 },
	{ 7,'L',45,156,0,20,2,78,0,0 },
	{ 7,'M',45,124,0,18,4,31,0,0 },
	{ 7,'Q',45,88,0,18,2,14,4,15 },
	{ 7,'H',45,66,0,26,4,13,1,14 },
	{ 8,'L',49,194,0,24,2,97,0,0 },
	{ 8,'M',49,154,0,22,2,38,2,39 },
	{ 8,'Q',49,110,0,22,4,18,2,19 },
	{ 8,'H',49,86,0,26,4,14,2,15 },
	{ 9,'L',53,232,0,30,2,116,0,0 },
	{ 9,'M',53,182,0,22,3,36,2,37 },
	{ 9,'Q',53,132,0,20,4,16,4,17 },
	{ 9,'H',53,100,0,24,4,12,4,13 },
	{ 10,'L',57,274,0,18,2,68,2,69 },
	{ 10,'M',57,216,0,26,4,43,1,44 },
	{ 10,'Q',57,154,0,24,6,19,2,20 },
	{ 10,'H',57,122,0,28,6,15,2,16 },
	{ 11,'L',61,324,0,20,4,81,0,0 },
	{ 11,'M',61,254,0,30,1,50,4,51 },
	{ 11,'Q',61,180,0,28,4,22,4,23 },
	{ 11,'H',61,140,0,24,3,12,8,13 },
	{ 12,'L',65,370,0,24,2,92,2,93 },
	{ 12,'M',65,290,0,22,6,36,2,37 },
	{ 12,'Q',65,206,0,26,4,20,6,21 },
	{ 12,'H',65,158,0,28,7,14,4,15 },
	{ 13,'L',69,428,0,26,4,107,0,0 },
	{ 13,'M',69,334,0,22,8,37,1,38 },
	{ 13,'Q',69,244,0,24,8,20,4,21 },
	{ 13,'H',69,180,0,22,12,11,4,12 },
	{ 14,'L',73,461,3,30,3,115,1,116 },
	{ 14,'M',73,365,3,24,4,40,5,41 },
	{ 14,'Q',73,261,3,20,11,16,5,17 },
	{ 14,'H',73,197,3,24,11,12,5,13 },
	{ 15,'L',77,523,3,22,5,87,1,88 },
	{ 15,'M',77,415,3,24,5,41,5,42 },
	{ 15,'Q',77,295,3,30,5,24,7,25 },
	{ 15,'H',77,223,3,24,11,12,7,13 },
	{ 16,'L',81,589,3,24,5,98,1,99 },
	{ 16,'M',81,453,3,28,7,45,3,46 },
	{ 16,'Q',81,325,3,24,15,19,2,20 },
	{ 16,'H',81,253,3,30,3,15,13,16 },
	{ 17,'L',85,647,3,28,1,107,5,108 },
	{ 17,'M',85,507,3,28,10,46,1,47 },
	{ 17,'Q',85,367,3,28,1,22,15,23 },
	{ 17,'H',85,283,3,28,2,14,17,15 },
	{ 18,'L',89,721,3,30,5,120,1,121 },
	{ 18,'M',89,563,3,26,9,43,4,44 },
	{ 18,'Q',89,397,3,28,17,22,1,23 },
	{ 18,'H',89,313,3,28,2,14,19,15 },
	{ 19,'L',93,795,3,28,3,113,4,114 },
	{ 19,'M',93,627,3,26,3,44,11,45 },
	{ 19,'Q',93,445,3,26,17,21,4,22 },
	{ 19,'H',93,341,3,26,9,13,16,14 },
	{ 20,'L',97,861,3,28,3,107,5,108 },
	{ 20,'M',97,669,3,26,3,41,13,42 },
	{ 20,'Q',97,485,3,30,15,24,5,25 },
	{ 20,'H',97,385,3,28,15,15,10,16 },
	{ 21,'L',101,932,4,28,4,116,4,117 },
	{ 21,'M',101,714,4,26,17,42,0,0 },
	{ 21,'Q',101,512,4,28,17,22,6,23 },
	{ 21,'H',101,406,4,30,19,16,6,17 },
	{ 22,'L',105,1006,4,28,2,111,7,112 },
	{ 22,'M',105,782,4,28,17,46,0,0 },
	{ 22,'Q',105,568,4,30,7,24,16,25 },
	{ 22,'H',105,442,4,24,34,13,0,0 },
	{ 23,'L',109,1094,4,30,4,121,5,122 },
	{ 23,'M',109,860,4,28,4,47,14,48 },
	{ 23,'Q',109,614,4,30,11,24,14,25 },
	{ 23,'H',109,464,4,30,16,15,14,16 },
	{ 24,'L',113,1174,4,30,6,117,4,118 },
	{ 24,'M',113,914,4,28,6,45,14,46 },
	{ 24,'Q',113,664,4,30,11,24,16,25 },
	{ 24,'H',113,514,4,30,30,16,2,17 },
	{ 25,'L',117,1276,4,26,8,106,4,107 },
	{ 25,'M',117,1000,4,28,8,47,13,48 },
	{ 25,'Q',117,718,4,30,7,24,22,25 },
	{ 25,'H',117,538,4,30,22,15,13,16 },
	{ 26,'L',121,1370,4,28,10,114,2,115 },
	{ 26,'M',121,1062,4,28,19,46,4,47 },
	{ 26,'Q',121,754,4,28,28,22,6,23 },
	{ 26,'H',121,596,4,30,33,16,4,17 },
	{ 27,'L',125,1468,4,30,8,122,4,123 },
	{ 27,'M',125,1128,4,28,22,45,3,46 },
	{ 27,'Q',125,808,4,30,8,23,26,24 },
	{ 27,'H',125,628,4,30,12,15,28,16 },
	{ 28,'L',129,1531,3,30,3,117,10,118 },
	{ 28,'M',129,1193,3,28,3,45,23,46 },
	{ 28,'Q',129,871,3,30,4,24,31,25 },
	{ 28,'H',129,661,3,30,11,15,31,16 },
	{ 29,'L',133,1631,3,30,7,116,7,117 },
	{ 29,'M',133,1267,3,28,21,45,7,46 },
	{ 29,'Q',133,911,3,30,1,23,37,24 },
	{ 29,'H',133,701,3,30,19,15,26,16 },
	{ 30,'L',137,1735,3,30,5,115,10,116 },
	{ 30,'M',137,1373,3,28,19,47,10,48 },
	{ 30,'Q',137,985,3,30,15,24,25,25 },
	{ 30,'H',137,745,3,30,23,15,25,16 },
	{ 31,'L',141,1843,3,30,13,115,3,116 },
	{ 31,'M',141,1455,3,28,2,46,29,47 },
	{ 31,'Q',141,1033,3,30,42,24,1,25 },
	{ 31,'H',141,793,3,30,23,15,28,16 },
	{ 32,'L',145,1955,3,30,17,115,0,0 },
	{ 32,'M',145,1541,3,28,10,46,23,47 },
	{ 32,'Q',145,1115,3,30,10,24,35,25 },
	{ 32,'H',145,845,3,30,19,15,35,16 },
	{ 33,'L',149,2071,3,30,17,115,1,116 },
	{ 33,'M',149,1631,3,28,14,46,21,47 },
	{ 33,'Q',149,1171,3,30,29,24,19,25 },
	{ 33,'H',149,901,3,30,11,15,46,16 },
	{ 34,'L',153,2191,3,30,13,115,6,116 },
	{ 34,'M',153,1725,3,28,14,46,23,47 },
	{ 34,'Q',153,1231,3,30,44,24,7,25 },
	{ 34,'H',153,961,3,30,59,16,1,17 },
	{ 35,'L',157,2306,0,30,12,121,7,122 },
	{ 35,'M',157,1812,0,28,12,47,26,48 },
	{ 35,'Q',157,1286,0,30,39,24,14,25 },
	{ 35,'H',157,986,0,30,22,15,41,16 },
	{ 36,'L',161,2434,0,30,6,121,14,122 },
	{ 36,'M',161,1914,0,28,6,47,34,48 },
	{ 36,'Q',161,1354,0,30,46,24,10,25 },
	{ 36,'H',161,1054,0,30,2,15,64,16 },
	{ 37,'L',165,2566,0,30,17,122,4,123 },
	{ 37,'M',165,1992,0,28,29,46,14,47 },
	{ 37,'Q',165,1426,0,30,49,24,10,25 },
	{ 37,'H',165,1096,0,30,24,15,46,16 },
	{ 38,'L',169,2702,0,30,4,122,18,123 },
	{ 38,'M',169,2102,0,28,13,46,32,47 },
	{ 38,'Q',169,1502,0,30,48,24,14,25 },
	{ 38,'H',169,1142,0,30,42,15,32,16 },
	{ 39,'L',173,2812,0,30,20,117,4,118 },
	{ 39,'M',173,2216,0,28,40,47,7,48 },
	{ 39,'Q',173,1582,0,30,43,24,22,25 },
	{ 39,'H',173,1222,0,30,10,15,67,16 },
	{ 40,'L',177,2956,0,30,19,118,6,119 },
	{ 40,'M',177,2334,0,28,18,47,31,48 },
	{ 40,'Q',177,1666,0,30,34,24,34,25 },
	{ 40,'H',177,1276,0,30,20,15,61,16 } };

struct AlignLocation
{
	unsigned char Version;				//版本
	unsigned char ncoord;				//校正图形坐标数字的个数
	unsigned char coord[7];				//存储校正图形坐标的数组，最多有七个校正数
};
const AlignLocation AL[40] = {
	{ 1,0,{ 0,0,0,0,0,0,0 } },
	{ 2,2,{ 6,18,0,0,0,0,0 } },
	{ 3,2,{ 6,22,0,0,0,0,0 } },
	{ 4,2,{ 6,26,0,0,0,0,0 } },
	{ 5,2,{ 6,30,0,0,0,0,0 } },
	{ 6,2,{ 6,34,0,0,0,0,0 } },
	{ 7,3,{ 6,22,38,0,0,0,0 } },
	{ 8,3,{ 6,24,42,0,0,0,0 } },
	{ 9,3,{ 6,26,46,0,0,0,0 } },
	{ 10,3,{ 6,28,50,0,0,0,0 } },
	{ 11,3,{ 6,30,54,0,0,0,0 } },
	{ 12,3,{ 6,32,58,0,0,0,0 } },
	{ 13,3,{ 6,34,62,0,0,0,0 } },
	{ 14,4,{ 6,26,46,66,0,0,0 } },
	{ 15,4,{ 6,26,48,70,0,0,0 } },
	{ 16,4,{ 6,26,50,74,0,0,0 } },
	{ 17,4,{ 6,30,54,78,0,0,0 } },
	{ 18,4,{ 6,30,56,82,0,0,0 } },
	{ 19,4,{ 6,30,58,86,0,0,0 } },
	{ 20,4,{ 6,34,62,90,0,0,0 } },
	{ 21,5,{ 6,28,50,72,94,0,0 } },
	{ 22,5,{ 6,26,50,74,98,0,0 } },
	{ 23,5,{ 6,30,54,78,102,0,0 } },
	{ 24,5,{ 6,28,54,80,106,0,0 } },
	{ 25,5,{ 6,32,58,84,110,0,0 } },
	{ 26,5,{ 6,30,58,86,114,0,0 } },
	{ 27,5,{ 6,34,62,90,118,0,0 } },
	{ 28,6,{ 6,26,50,74,98,122,0 } },
	{ 29,6,{ 6,30,54,78,102,126,0 } },
	{ 30,6,{ 6,26,52,78,104,130,0 } },
	{ 31,6,{ 6,30,56,82,108,134,0 } },
	{ 32,6,{ 6,34,60,86,112,138,0 } },
	{ 33,6,{ 6,30,58,86,114,142,0 } },
	{ 34,6,{ 6,34,62,90,118,146,0 } },
	{ 35,7,{ 6,30,54,78,102,126,150 } },
	{ 36,7,{ 6,24,50,76,102,128,154 } },
	{ 37,7,{ 6,28,54,80,106,132,158 } },
	{ 38,7,{ 6,32,58,84,110,136,162 } },
	{ 39,7,{ 6,26,54,82,110,138,166 } },
	{ 40,7,{ 6,30,58,86,114,142,170 } } };
void ToBit(int I, char* bitChar, int NBit);
void DataAnalysis(const char* data, QRVersion& Q);
void DataEnCoding(const QRVersion& Q, char* data, unsigned char* result);
void GenerErrorCorCode(const unsigned char* Mes, int MesNum, unsigned char* result, int ErrCorCodeNum);
void StructMes(const QRVersion& Q, unsigned char* data, char* bitString);
void ModulePlacement(const QRVersion& Q, char(*m)[177], char* bitString);
void Masking(const QRVersion& Q, char(*m)[177], char(*mask)[177], int& pmode);
void SetFormatVersion(const QRVersion& Q, char(*m)[177], int pmode);
void ScreenOutput(const QRVersion& Q, char(*m)[177]);
std::string GetLocalIPv4Address();