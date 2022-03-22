/* -----------------------------------------
   File: Packet.h
   Usage: Contains the full packet class for reading / writing to the initial buffer.
   Version: 2007/2008 servers for Sahar042 have fun bitch.
   Author: Phail
   -----------------------------------------*/
class CPacket
{
	public:
		unsigned char *mData;
		unsigned char mKey[32];
		short mSize;
	
		unsigned char *BuildKey(char *pPacket)
		{
			byte Xor[] = { 0x57, 0x02,0x5B,0x04,0x34,0x06,0x01,0x08,0x37,0x0A,0x12,0x69,0x41,0x38,0x0F,0x78 };
			byte mBytes[] = { 0x37,0x04,0x5D,0x2E,0x43,0x38,0x49,0x53,0x50,0x05,0x13,0xC9,0x28,0xA4,0x4D,0x05 }; //GameNao! same shit Exploits
			unsigned int szTmp = 0,szTmp2 = 0,szTmp3 = 0;
			memcpy(mKey,pPacket+12,4);
			memcpy(mKey+4,pPacket,12);
			memcpy(mKey+16,mBytes,16);
			for(int i=0; i<4; ++i)
			{
				memcpy(&szTmp,Xor+(i*4),4);
				memcpy(&szTmp2,mKey+(i*4),4);
				szTmp3 = szTmp ^ szTmp2;
				memcpy(mKey+(i*4),&szTmp3,4);
			}
			return (unsigned char *)mKey;
		}
		void Encrypt(unsigned char *szBuffer, int iStart, int iLength)
		{
			for(int i=0; i < iLength; ++i)
			{
				unsigned short a = szBuffer[iStart+i];
				a ^=mKey[i%32];
				a <<= 3;

				byte b = (byte)(a >> 8);
				b |= (byte)(a & 0xB4);
				b ^= 0xF0; //Packet encryption
				szBuffer[iStart + i] = (byte)b;
			}
		}


		void Decrypt(unsigned char *szBuffer, int iStart, int iLength)
		{           
			for (int i = 0; i < iLength; ++i)
			{
				byte a = szBuffer[iStart + i];
				a ^= 0x0F0; //Packet encryption
				byte b = (byte)(7 & a);
				b <<= 5;
				a >>= 3;
				b = (byte)(a | b);
				szBuffer[iStart+i] = (byte)(b ^ mKey[i % 32]);
			}
		}



		unsigned short Checksum(unsigned char *szBuffer, int iStart, int iLength)
		{
			unsigned int uiSum = (unsigned int)(szBuffer[iStart] + szBuffer[iStart+1] + szBuffer[iStart+2] + szBuffer[iStart+3]),uiSum2=0,uiSum3=0,uiSum4=0;
			for(int i=6; i < iLength; ++i) uiSum2 += szBuffer[i];
			uiSum3 = uiSum2 - uiSum;
			uiSum4 = uiSum3 >> 0x10;
			uiSum3 += uiSum4;
			return (unsigned short)uiSum3;
		}
		void WriteData(void *pData, short pLength)
		{
			char cZero = 0x00;
			if(pData == 0)
			{
				for(int i=0; i < pLength; i++)
				{
					memcpy(mData+mSize,&cZero,1);
					mSize++;
				}
			}
			else
			{
				memcpy(mData+mSize,pData,pLength);
				mSize += pLength;
			}
		}

		void WriteString(char *szBuffer)
		{
			short wSize = strlen(szBuffer)+1;
			WriteData(&wSize,2);
			WriteData(szBuffer,wSize);
		}


		short ReadShort()
		{
			short s = 0;
			memcpy(&s,mData+mSize,2);
			mSize+=2;
			return s;
		}
		char *ReadString()
		{
			short wSize = ReadShort();
			char *szString = (char *)malloc(wSize);
			memset(szString,0,wSize);
			memcpy(szString,mData+mSize,wSize);
			mSize+=wSize;
			return szString;
		}
		byte ReadByte()
		{
			byte out = mData[mSize];
			mSize++;
			return out;
		}
		long ReadLong()
		{
			long out = 0;
			memcpy(&out,mData+mSize,4);
			mSize+=4;
			return out;
		}
		byte *ReadArray(short iSize)
		{
			byte *bArray = new byte[iSize];
			memset(bArray,0,iSize);
			memcpy(bArray,mData+mSize,iSize);
			mSize+=iSize;
			return bArray;
		}
		short GetLen(int iLast)
		{
			short wOut = 0;
			for(int i=mSize; i < iLast; i++,wOut++)
			{
				if(mData[i] == 0){
					wOut++;
					break;
				}							
			}
			return wOut;
		}
		void SkipByte(short wSize)
		{
			mSize+=wSize;
		}
		void SetPos(short pVal)
		{
			mSize = pVal;
		}
		void WriteShort(short pIn)
		{
			memcpy((mData+mSize),&pIn,2);
			mSize+=2;
		}
		void MakeCommand(short wCommand,byte val)
		{
			char cPacketId = val;

			memcpy(mData,&wCommand,2);
			memcpy(mData+2,&cPacketId,1);

			mSize += 3;
		}
		unsigned char *FinalizePacket(unsigned short wVersion)
		{
			unsigned short wLen = mSize + 8;
			unsigned short wLen2 = mSize+2;
			unsigned short wChecksum = 0;
			unsigned char *szPacket = new unsigned char[wLen];
			byte bZero[] = {0x0,0x0};
			
			memset(szPacket,0,wLen);
			memcpy(szPacket,&wVersion,2);
			memcpy(szPacket+2,&wLen,2);

			if(wVersion == 0x65)Encrypt(szPacket,2,2);
			
			memcpy(szPacket+4,&bZero,2);
			memcpy(szPacket+6,&wLen2,2);
			memcpy(szPacket+8,mData,mSize);
		
			if(wVersion == 0x65)Encrypt(szPacket,6,mSize+2);
			wChecksum = Checksum(szPacket,0,wLen);
			memcpy(szPacket+4,&wChecksum,2);

			return szPacket;
		}


		CPacket(int pLen,unsigned char pKey[32])
		{
			mData = (unsigned char *)malloc(pLen);
			memset(mData,0,pLen);
			mSize = 0;
			memcpy(mKey,pKey,32);
		}

		CPacket(unsigned char *pDecrypted, short pStart, short pSize)
		{
			mData = (unsigned char *)malloc(pSize);
			memset(mData,0,pSize);
			memcpy(mData,pDecrypted,pSize);
			mSize = pStart;
		}

		CPacket(unsigned char pKey[32])
		{
			memcpy(mKey,pKey,32);
		}

		CPacket(){}
		~CPacket()
		{
			free((void *)mData);
			mSize = 0;
		}

};
