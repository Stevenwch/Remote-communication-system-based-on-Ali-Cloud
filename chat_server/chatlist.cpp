#include "chatlist.h"

ChatInfo::ChatInfo()
{
	online_user = new list<User>;

	group_info = new list<Group>;

	//往group_info链表中添加群信息
	mydatabase = new ChatDataBase;
	mydatabase->my_database_connect("chatgroup");

	string group_name[MAXNUM];
	int group_num = mydatabase->my_database_get_group_name(group_name);

	for (int i = 0; i < group_num; i++)
	{
		Group g;
		g.name = group_name[i];
		g.l = new list<GroupUser>;    //保存群中所有用户

		group_info->push_back(g);

		string member;              //保存群里所有用户
		mydatabase->my_database_get_group_member(group_name[i], member);	
		if (member.size() == 0)
		{
			continue;
		}

		int start = 0, end = 0;
		GroupUser u;
		while (1)
		{
			end = member.find('|', start);
			if (-1 == end)
			{
				break;
			}
			u.name = member.substr(start, end - start);
			g.l->push_back(u);
			start = end + 1;
			u.name.clear();
		}
		u.name = member.substr(start, member.size() - start);
		g.l->push_back(u);

	}

	/*for (list<Group>::iterator it = group_info->begin(); it != group_info->end(); it++)
	{
		cout << "群名字 " << it->name << endl;
		for (list<GroupUser>::iterator i = it->l->begin(); i != it->l->end(); i++)
		{
			cout << i->name << endl;
		}
	}*/

	mydatabase->my_database_disconnect();

	cout << "初始化链表成功" << endl;
}

bool ChatInfo::info_group_exist(string group_name)
{
	for (list<Group>::iterator it = group_info->begin(); it != group_info->end(); it++)
	{
		if (it->name == group_name)
		{
			return true;
		}
	}
	return false;
}

bool ChatInfo::info_user_in_group(string group_name, string user_name)
{
	for (list<Group>::iterator it = group_info->begin(); it != group_info->end(); it++)
	{
		if (it->name == group_name)
		{
			for (list<GroupUser>::iterator i = it->l->begin(); i != it->l->end(); i++)
			{
				if (i->name == user_name)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void ChatInfo::info_group_add_user(string group_name, string user_name)
{	
	for (list<Group>::iterator it = group_info->begin(); it != group_info->end(); it++)
	{
		if (it->name == group_name)
		{
			GroupUser u;
			u.name = user_name;
			it->l->push_back(u);
		}
	}
}

struct bufferevent *ChatInfo::info_get_friend_bev(string name)
{
	for (list<User>::iterator it = online_user->begin(); it != online_user->end(); it++)
	{
		if (it->name == name)
		{
			return it->bev;
		}
	}
	return NULL;
}

string ChatInfo::info_get_group_member(string group)
{
	string member;
	for (list<Group>::iterator it = group_info->begin(); it != group_info->end(); it++)
	{
		if (group == it->name)
		{
			for (list<GroupUser>::iterator i = it->l->begin(); i != it->l->end(); i++)
			{
				member += i->name;
				member += "|";
			}
		}
	}
	return member;
}

void ChatInfo::info_add_new_group(string group_name, string user_name)
{
	Group g;
	g.name = group_name;
	g.l = new list<GroupUser>;
	group_info->push_back(g);

	GroupUser u;
	u.name = user_name;
	g.l->push_back(u);
}
