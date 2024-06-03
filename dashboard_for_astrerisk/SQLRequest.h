//////////////////////////////////////////////////////
//													//	        
//			by Petrov Yuri 03.06.2024				//
//				   SQL запросы	             		//
//													//	
//////////////////////////////////////////////////////
#include <iostream>
#include "Constants.h"
#include <mysql/mysql.h>
#include "IVR.h"
#include "Queue.h"

#ifndef SQLREQUEST_H
#define	SQLREQUEST_H

namespace SQL_REQUEST
{
	class SQL
	{
	public:
		SQL();
		~SQL() = default;

		bool isConnectedBD();	// есть ли коннект с БД

		void query_test();
		void insertData_test();

		//table IVR
		void insertIVR(const char *phone, const char *time, std::string callerid ); // добавление данных в таблицу IVR
		bool isExistIVRPhone(const char *phone);					// существует ли такой уже номер в таблице IVR
		int getLastIDphone(const char *phone);				// получение последнего ID актуального
		void updateIVR(const char *id, const char *phone, const char *time); // обновление данных в таблице IVR
		


		// table QUEUE
		void insertQUEUE(const char *queue, const char *phone, const char *time); // добавление данных в таблицу QUEUE
		bool isExistQUEUE(const char *queue, const char *phone);				  // существует ли такой уже номер в таблице QUEUE
		void updateQUEUE(const char *id, const char *phone, const char *time);					  // обновление данных в таблице QUEUE
		int getLastIDQUEUE(const char *phone);		// получение последнего ID актуального
		void updateQUEUE_SIP(const char *phone, const char *sip, const char *talk_time); // обновление данных таблицы QUEUE о том с кем сейчас разговаривает оператор
		bool isExistQUEUE_SIP(const char *phone);   // существует ли такой номер в таблице QUEUE чтобы добавить sip оператора который с разговор ведет
		void updateQUEUE_fail(const std::vector<QUEUE::Pacients> &pacient_list); // обновление данных когда звонок не дождался своей очереди 
		void updateQUEUE_fail();				// обновление данных когда звонок не дождался своей очереди 
		void updateIVR_to_queue(const std::vector<QUEUE::Pacients> &pacient_list); // обновление данных когда у нас звонок из IVR попал в очередь
		bool isExistQueueAfter20hours(); // проверка есть ли номера которые позвонили после 20:00
		void updateQUEUE_hash(const std::vector<QUEUE::Pacients> &pacient_list); // обновление поля hash когда успешно поговорили


		// Статистика
		int getIVR_totalCalls();			// сколько всего позвонило на линию IVR
		int getIVR_totalCalls(const IVR::CallerID &trunk);			// сколько всего позвонило на линию IVR (поиск по trunk)
		int getQUEUE_Calls(bool answered);  // сколько всего ответило и сколько пропущенных
		int getQUEUE_Calls();				// сколько всего было в очереди

	private:
		MYSQL mysql;
		void createMySQLConnect(MYSQL &mysql); // подключаемся к БД MySQL
	};

};


#endif //SQLREQUEST_H