#ifndef CHAT_DATABASE_H
#define CHAT_DATABASE_H

#include <mysql/mysql.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class ChatDataBase
{
private:
	MYSQL *mysql;
public:
	ChatDataBase();
	~ChatDataBase();

	void my_database_connect(const char *name);
	int my_database_get_group_name(string *);
	void my_database_get_group_member(string, string &);
	bool my_database_user_exist(string);
	void my_database_user_password(string, string);
	bool my_database_password_correct(string, string);
	bool my_database_is_friend(string, string);
	void my_database_get_friend_group(string, string &, string &);
	void my_database_add_new_friend(string, string);
	bool my_database_group_exist(string);
	void my_database_add_new_group(string, string);
	void my_database_user_add_group(string, string);
	void my_database_group_add_user(string, string);
	void my_database_disconnect();
};

#endif
