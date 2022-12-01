#include <Windows.h>
#include <stdio.h>

DWORD WINAPI time(int* t)
{
	int sec = 0, min = 0, hour = 0;
	int cursec = 0, curmin = 0, curhour = 0;
	if (t[3] == 0 || t[3] == NULL)
	{
		sec = t[0];
		min = t[1];
		hour = t[2];
	}
	else
	{
		cursec = t[0];
		curmin = t[1];
		curhour = t[2];
	}
	while (1)
	{
		Sleep(970);
		sec++;
		if (sec >= 60)
		{
			min++;
			sec -= 60;
		}
		if (min >= 60)
		{
			hour++;
			min -= 60;
		}
		if (hour >= 24)
		{
			hour = 0;
		}

		system("cls");
		printf("%d:%d:%d\n", hour, min, sec);
		if (curhour == hour && curmin == min && cursec == sec && (t[3] != 0 || t[3] != NULL))
		{
			ExitThread(0);
		}
	}
	return 0;
}

DWORD WINAPI params(int* t)
{
	int sec = 0, min = 0, hour = 0;
	int cursec = 0, curmin = 0, curhour = 0;
	if (t[3] == 0 || t[3] == NULL)
	{
		if (t[0] >= 60)
		{
			sec = t[0] % 60;
			t[0] = t[0] - sec;
			min = t[0] / 60;
		}
		else sec = t[0];
		if (t[1] >= 60)
		{
			min = min + (t[1] % 60);
			t[1] = t[1] - min;
			hour = t[1] / 60;
		}
		else min = min + t[1];
		if (t[2] >= 24)
		{
			hour = hour + (t[2] % 24);
		}
		else hour = hour + t[2];
	}
	else
	{
		cursec = t[0];
		curmin = t[1];
		curhour = t[2];
	}
	while (1)
	{
		Sleep(970);
		sec++;
		if (sec >= 60)
		{
			min++;
			sec -= 60;
		}
		if (min >= 60)
		{
			hour++;
			min -= 60;
		}
		if (hour >= 24)
		{
			hour = 0;
		}

		system("cls");
		printf("%d:%d:%d\n", hour, min, sec);
	}
	ExitThread(0);
}

int main()
{
	system("chcp 1251>nul");

	int* t = calloc(4, sizeof(int));

	while (1)
	{
		int i = 0;
		char user = 0;
		printf("Для запуска часов нажмите 1\nНажмите 2 для паузы\nНажмите 3 для настройки времени\nНажмите 4 чтобы включить таймер\nНажмите 5 чтобы включить секундомер\nНажмите 6 для выхода из программы\n");
		scanf_s("%d", &i);
		HANDLE hand = NULL;
		switch (i)
		{
		case 1:
			t[0] = 0, t[1] = 0, t[2] = 0, t[3] = 0;
			hand = CreateThread(NULL, 0, time, t, 0, 0);
			WaitForSingleObject(hand, INFINITE);
			break;

		case 2:
			if (hand == NULL)
			{
				printf("Запуск часов");
				t[0] = 0, t[1] = 0, t[2] = 0, t[3] = 0;
				hand = CreateThread(NULL, 0, time, t, 0, 0);
				Sleep(4000);
				while (1)
				{
					printf("Пауза\n");
					scanf_s("%d", &user);
					if (user == 0)
					{
						SuspendThread(hand);
					}
					else
					{
						ResumeThread(hand);
					}
				}

				WaitForSingleObject(hand, 120000);
				break;
			}
			break;
		case 3:
			printf("Введите часы: \n");
			scanf_s("%d", &t[2]);
			printf("Введите минуты: \n");
			scanf_s("%d", &t[1]);
			printf("Введите секунды: \n");
			scanf_s("%d", &t[0]);
			t[3] = 0;
			hand = CreateThread(NULL, 0, params, t, 0, 0);
			WaitForSingleObject(hand, 120000);
			break;
		case 4:
			printf("Введите часы: \n");
			scanf_s("%d", &t[2]);
			printf("Введите минуты: \n");
			scanf_s("%d", &t[1]);
			printf("Введите секунды: \n");
			scanf_s("%d", &t[0]);
			t[3] = 1;
			hand = CreateThread(NULL, 0, time, t, 0, 0);
			WaitForSingleObject(hand, 120000);
			break;
		case 5:
			if (hand == NULL)
			{

				printf("Секундомер\n  Для запуска нажмите - 1");
				scanf_s("%d", &user);
				t[0] = 0, t[1] = 0, t[2] = 0, t[3] = 0;
				hand = CreateThread(NULL, 0, time, t, 0, 0);
				while (1)
				{
					if (user == 1)
					{
						WaitForSingleObject(hand, 120000);
					}
					else
					{
						ExitThread(0);
						break;
					}
				}
				break;
		case 6:
			exit(0);
		default:
			break;
			}
		}
	}
}