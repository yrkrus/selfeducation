#include <iostream>
#include <string>


#define LOG_CLASS_H
#ifdef LOG_CLASS_H

class Logging
{

public:
	
	Logging();
	~Logging();

	void setLog(std::string message, bool isError);

};


#endif // LOG_CLASS_H

