#include "InternalFunction.h"
#include "Constants.h";
#include "IVR.h"
#include "Queue.h"
#include "ActiveSip.h"

// ������� ������ �������� � ���������� ���
std::string phoneParsing(std::string &phone)
{
	if (phone.length() < 6)
	{
		return "null";	// ��� ������� ������� �� ������� � �� ���������
	}
	else if (phone.length() == 10)
	{
		return "+7" + phone;
	}
	else if (phone.length() == 11)
	{
		return "+" + phone;
	}
	else
	{
		return "null";	// ������ �� ����� ��������� null
	}
};


// ������� + �������� ������� IVR
void getIVR(void)
{   
	if (!CONSTANTS::DEBUG_MODE) {
		system(CONSTANTS::cIVRResponse.c_str());
	};
	  

    // ���������
    IVR::Parsing ivr(CONSTANTS::cIVRName.c_str());
    ivr.show();

    //if (ivr.isExistList()) {
    //    // ��������� � mysql
    //    ivr.show();
    //}   
}

// ������� + �������� ������� �������
void getQueue(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cQueueResponse.c_str());
	}

    QUEUE::Parsing queue(CONSTANTS::cQueueName.c_str());

    queue.show();
}

// ������� + �������� ��� � ��� �������������
void getActiveSip(void)
{
	if (!CONSTANTS::DEBUG_MODE)	{
		system(CONSTANTS::cActiveSipResponse.c_str());
	}

    ACTIVE_SIP::Parsing sip(CONSTANTS::cActiveSipName.c_str());

    sip.show();
}




