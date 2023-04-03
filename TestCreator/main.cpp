#include<iostream>
#include<vector>
#include"Menu.h"
#include"User.h"
#include"Admin.h"
#include"Student.h"

int main()
{

	render::SetColor(Color::LightCyan, Color::Black);

	User current_user;

	while (true)
	{
		
		render::gotoxy(0, 0);
		system("cls");
		render::renderText("Super Tests", 11, 1);
		int reg_or_log = Menu::select_vertical({ "Register", "Login" }, Center);
		switch (reg_or_log)
		{
			case -1:
			{
				exit(0);
			}
			case 0:
			{
				int status = current_user.Registration();
				continue;
			}
			case 1:
			{
				int status = current_user.Login();
				switch (status)
				{
					case -1:
					{
						continue;
					}
					case 0:
					{
						continue;
					}
					case 1:
					{
						break;
					}
				}
				break;
			}
			break;
		}
		break;
	}
	
	if (current_user.is_Admin())
	{
		Admin current_admin = current_user;
		
		while (true)
		{
			render::gotoxy(0, 0);
			system("cls");
			render::SetColor(Color::LightCyan, Color::Black);
			render::renderText("Admin", 22, 1);
			int main = Menu::select_vertical({ "Edit Users", "Statistics", "Edit Tests" }, Center);
			switch (main)
			{
				case -1:
				{
					exit(0);
				}
				case 0:
				{
					while (true)
					{
						render::gotoxy(0, 0);
						system("cls");
						render::SetColor(Color::LightCyan, Color::Black);
						render::renderText("Admin", 22, 1);
						int admin_user = Menu::select_vertical({ "Create User", "Delete User", "Edit User" }, Center);
						switch (admin_user)
						{
							case -1:
							{
								break;
							}
							case 0:
							{
								User created_user;
								int status = created_user.Registration();
								continue;
							}
							case 1:
							{
								current_admin.delete_user();
								continue;
							}
							case 2:
							{
								current_admin.edit_user();
								continue;
							}
						}
						break;
					}
					continue;
				}
				case 1:
				{
					current_admin.statistic();
					continue;
				}
				case 2:
				{
					while (true)
					{
						render::gotoxy(0, 0);
						system("cls");
						render::SetColor(Color::LightCyan, Color::Black);
						render::renderText("Admin", 22, 1);
						int admin_user = Menu::select_vertical({ "Create Test", "Delete Test", "Create Category"}, Center);
						switch (admin_user)
						{
							case -1:
							{
								break;
							}
							case 0:
							{
								current_admin.create_test();
								continue;
							}
							case 1:
							{
								current_admin.delete_test();
								continue;
							}
							case 2:
							{
								current_admin.create_category();
								continue;
							}
						}
						break;
					}
					continue;
				}
			}
		}
	}
	else
	{
		Student current_student = current_user;

		while (true)
		{
			render::gotoxy(0, 0);
			system("cls");
			render::SetColor(Color::LightCyan, Color::Black);
			render::renderText("Student", 22, 1);
			int main = Menu::select_vertical({ "Take A Test", "Completed Tests" }, Center);
			switch (main)
			{
				case -1:
				{
					exit(0);
				}	
				case 0:
				{
					current_student.choose_test();
					continue;
				}
				case 1:
				{
					current_student.completed_test();
					continue;
				}
			}
		}
		


	}

	
	
}