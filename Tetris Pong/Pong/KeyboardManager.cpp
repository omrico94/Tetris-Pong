#include <conio.h>
#include "KeyboardManager.h"

void KeyboardManager::registerKbListener(KeyboardEventListener * pKbListener)
{
	const char * chars = pKbListener->getKbChars();
	size_t numCharToRegister = strlen(chars);
	for (size_t i = 0; i < numCharToRegister; ++i)
	{
		int index = getIndex(chars[i]);
		if (index != -1)
		{
			kbListeners[index].push_back(pKbListener);
		}
	}
}

int KeyboardManager::handleKeyboard(int& counters, int& counterk)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int i, index;
	char k;
	for (i = 0; i < 3; i++)
	{
		if (_kbhit())
		{
			k = tolower(_getch());
			index = getIndex(k);
			if (index != ESC)
			{
				if (index != -1)
				{
					if (((k != 'k') && (k != 's')) || ((k == 'k') && (counterk == 0)) || ((k == 's') && (counters == 0)))
					{
						for (auto pKbListener : kbListeners[index])
						{
							pKbListener->handleKey(k);

							//draw the line of the bomb.
							if (k == 'k')
							{
								SetConsoleTextAttribute(hConsole, 375);
								gotoxy(73, 1);
								cout << "    ";
								SetConsoleTextAttribute(hConsole, 7);
								counterk++;
							}
							if (k == 's')
							{
								SetConsoleTextAttribute(hConsole, 375);
								gotoxy(2, 1);
								cout << "    ";
								SetConsoleTextAttribute(hConsole, 7);
								counters++;
							}
						}
					
					}
				}
			}
			else
				return 1;
		}
	}
	return 0;
}

