#ifndef CONNECTION_H
#define CONNECTION_H

class Connection final 
{
public:
	int x, y;
	float weight;
	float lastInput = 0;
	Connection(int x, int y, float weight) : x(x), y(y), weight(weight) {};
};

#endif //CONNECTION_H