#include "buffer.hpp"

Buffer::Buffer ()
{
	//buffer = new char[capacity];
	packets.push_back(new char[PACKET_SIZE]);
	capacity = PACKET_SIZE;
	packetCount = 1;

	byteCount = 0;
	putPointer = 0;
	getPointer = 0;
}

void Buffer::put (const char& c)
{
	if(byteCount == capacity)
	{
		packets.push_back(new char[PACKET_SIZE]);
		capacity += PACKET_SIZE;
		packetCount += 1;
		//write header to new packet? TODO
	}
	byteCount += 1;
	packets.back()[byteCount - ((packetCount - 1) * PACKET_SIZE)] = c;
	//cout << "add \"" << (int)packets[packetCount - 1][byteCount - ((packetCount - 1) * PACKET_SIZE)] << "\" at [" << packetCount - 1 << "][" << byteCount - ((packetCount - 1) * PACKET_SIZE) << "]" << endl;
	//whew long line ^.^
	//cout << "add \"" << (int)buffer[byteCount] << "\" at [" << byteCount << "]" << endl;
	cout << "add \"" << (int)c << "\" at [" << packetCount - 1 << "][" << byteCount - ((packetCount - 1) * PACKET_SIZE) << "]\n";
	putPointer += 1;
	getPointer = putPointer; //TODO temporary, in the future have functions that increment {put, get}Pointer
}

//helper[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
//
// packetNum starts at 0, byteNum is relative and goes from 0 to PACKET_SIZE-1
char Buffer::get (unsigned int packetNum, unsigned int byteNum)
{
	list<char*>::iterator it = packets.begin(); //why no random_access_iterator std::list? why? :(
	for(int i = 0; i < packetNum; i++)
	{
		it++;
	}
	return (*it)[byteNum];
}
//helper]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


char Buffer::get ()
{
	int listNum = getPointer / 1024;
	int buffNum = getPointer % 1024;
	getPointer--;
	//cout << "listNum = " << listNum << " buffnum = " << buffNum << endl;
	//cout << "getPointer = " << getPointer << endl;
	cout << "get \"" << (int)get(listNum, buffNum) << "\" at [" << listNum << "][" << buffNum << "]" << '\n';
	
	return get(listNum, buffNum);
}

void Buffer::get (char& c)
{
	//getPointer--;
	//c = buffer[getPointer++];
	c = get();
}

void Buffer::put (const int& i)
{
	unsigned int bigE = htonl(i);
	unsigned char c1 = (bigE & 0xff000000) >> 24;//most significant (on big-endian)
	unsigned char c2 = (bigE & 0x00ff0000) >> 16;
	unsigned char c3 = (bigE & 0x0000ff00) >> 8;
	unsigned char c4 = (bigE & 0x000000ff);			//least significant (on big-endian)

	this->put((char)c1);
	this->put((char)c2);
	this->put((char)c3);
	this->put((char)c4);
}

void Buffer::get (int& i)
{
	unsigned char c4 = get();
	unsigned char c3 = get();
	unsigned char c2 = get();
	unsigned char c1 = get();

	i = (c1 << 24) | (c2 << 16) | (c3 << 8) | c4;
	i = ntohl(i);
}

void Buffer::put (const long long& l)
{
	//long long mask1 = 0xffffffffffffffff;
	int i1 = int((l & 0x00000000ffffffff));
	int i2 = int((l & 0xffffffff00000000) >> 32);
	this->put(i2);
	this->put(i1);
}

void Buffer::get (long long& l)
{
	//cout << "segfault incomming" << endl;
	long long l1 = 0;
	long long l2 = 0;
	this->get((int&)l2);
	this->get((int&)l1);
	l = (l2 << 32) | l1;
}

void Buffer::put (const float& f)
{
	//cout << "put " << f << endl;
	int i = *(reinterpret_cast<int*>((float*)&f));
	//cout << "ftoi " << i << endl;
	this->put(i);
}

void Buffer::get (float& f)
{
	int i = 0;
	this->get(i);
	//cout << "itof " << i << endl;
	f = *(reinterpret_cast<float*>(&i));
	//cout << f << endl;
}

void Buffer::put (const double& d)
{
	long long i = *(reinterpret_cast<long long*>((double*)&d));
	this->put(i);
}

void Buffer::get (double& d)
{
	long long o = 0;
	this->get(o);
	double out = *(reinterpret_cast<double*>(&o));
	d = out;
}

void Buffer::add(char* data, int length)
{
	for(int i = 0; i < length; i++)
	{
		this->put(data[i]);
	}
}

char* Buffer::getPacket (int n)
{
	return NULL;
}

list<char*>* Buffer::getPackets ()
{
	return NULL;
}

unsigned int Buffer::getByteCount ()
{
	return byteCount;
}

unsigned int Buffer::getCapacity ()
{
	return capacity;
}

list<char*>* Buffer::end ()
{
	return &packets;
}
