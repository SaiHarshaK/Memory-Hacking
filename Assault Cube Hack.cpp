#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

using namespace std;
string game = "AssaultCube";
LPCSTR LgameWindow = "AssaultCube"; //some games have window names not same as game name
string gameStatus;

bool isGameAvail;
bool updateOnNextRun;

//Ammo variables
bool ammoStatus;//is the infinite hack on
BYTE ammoValue[] = { 0x58, 0x1B, 0x0, 0x0 }; //turning on gives me 7000.
DWORD ammoBaseAddress = { 0x00509B74 };
DWORD AmmoOffsets[] = { 0x384,0x14,0x0 };

//Health variables
bool healthStatus;//is the infinite hack on
BYTE healthValue[] = { 0xDC, 0x5, 0x0, 0x0 }; //turning on gives me 1337.
DWORD healthBaseAddress = { 0x00509B74 };
DWORD healthOffsets[] = { 0xF8 };


DWORD findDmaAdd(int PointerLevel1, HANDLE hProcHandle, DWORD offsets[], DWORD baseAddress);
void WriteToMemory(HANDLE hProcHandle);

int main()
{
	HWND hGameWindow = NULL; //hwnd is handle; null to close handle that have menu and stuff
	int timeSinceLastUpdate = clock();
	int gameAvailTimer = clock();
	int onePressTimer = clock();
	DWORD dwProcID = NULL; //process ID
	HANDLE hProcHandle = NULL; //process handle
	updateOnNextRun = TRUE;
	string s_ammoStatus = "OFF";
	string s_healthStatus = "OFF";

	while (!GetAsyncKeyState(VK_INSERT)) //kind of infinite loop & ppl dont use this key often
	{
		if (clock() - gameAvailTimer > 100)
		{
			gameAvailTimer = clock();
			isGameAvail = FALSE;//every loop we set it to false which can be proved otherwise. So we wont try and write into memory of game that isnt there.

			hGameWindow = FindWindow(NULL, LgameWindow);//this function will find that window for us
			if (hGameWindow) //if that handle is available
			{
				GetWindowThreadProcessId(hGameWindow, &dwProcID); //get the process and put it in dwProcID
				if (dwProcID != 0)
				{
					//so till now we r making sure all IDs ,handles for windows r there
					hProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcID); // open the process to play with it, we r going to handle of the program now

					if (hProcHandle == INVALID_HANDLE_VALUE || hProcHandle == NULL)
					{
						gameStatus = "Failed to open process for valid handle"; //game isnt available
					}
					else
					{
						gameStatus = "Game is ready to be hacked";
						isGameAvail = TRUE;
					}
				}

				else
				{
					gameStatus = "Failed to get process ID";
				}
			}
			else
			{
				gameStatus = "AssaultCube not found";
			}

			if (updateOnNextRun || clock() - timeSinceLastUpdate > 5000) //to update every 5 seconds( like if game was on but suddenly switched off) 
			{
				system("cls");
				cout << "---------------------------------------------------------------------------------------------" << endl;
				cout << "								AssaultCube Hack (SHK)	 										" << endl;
				cout << "---------------------------------------------------------------------------------------------" << '\n' << endl;
				cout << "Game Status : " << gameStatus << '\n' << endl;
				cout << "Press [F1] to toggle Unlimited Ammo -> " << s_ammoStatus << '\n' << endl;
				cout << "Press [F2] to toggle Unlimited Health -> " << s_healthStatus << '\n' << endl;
				cout << "Press [INSERT] to exit" << '\n' << endl;
				updateOnNextRun = FALSE;
				timeSinceLastUpdate = clock();

				if (isGameAvail)
				{
					WriteToMemory(hProcHandle);
				}

			}

			if (clock() - onePressTimer >400) //user might press it for a long time and it would toggle continuosly and we dont want that
			{
				if (isGameAvail)
				{
					//vk is virtual key
					//ammo
					if (GetAsyncKeyState(VK_F1))
					{
						onePressTimer = clock(); //basically key wont be registed for another 4 sec
						ammoStatus = !ammoStatus;
						updateOnNextRun = TRUE;//since a value has been changed
						if (ammoStatus)
							s_ammoStatus = "ON";
						else s_ammoStatus = "OFF";

					}
					//health
					if (GetAsyncKeyState(VK_F2))
					{
						onePressTimer = clock(); //basically key wont be registed for another 4 sec
						healthStatus = !healthStatus;
						updateOnNextRun = TRUE;//since a value has been changed
						if (healthStatus)
							s_healthStatus = "ON";
						else s_healthStatus = "OFF";

					}
				}
			}

		}
	}

	return ERROR_SUCCESS;
}

DWORD findDmaAdd(int PointerLevel, HANDLE hProcHandle, DWORD offsets[], DWORD baseAddress)
{
	//to reach the temporary address, the dynamic address
	DWORD pointer = baseAddress;
	DWORD pTemp;

	DWORD pointerAdd;
	for (int i = 0; i < PointerLevel; i++)
	{
		if (i == 0)//first pointer
		{
			ReadProcessMemory(hProcHandle, (LPCVOID)pointer, &pTemp, sizeof(pTemp), NULL); //we need to read the contents and find out what that pointer points to. To get value inside that.&pTemp to point where the address of memory is.
		}

		pointerAdd = pTemp + offsets[i];
		ReadProcessMemory(hProcHandle, (LPCVOID)pointerAdd, &pTemp, sizeof(pTemp), NULL);

	}
	return pointerAdd;

}


void WriteToMemory(HANDLE hProcHandle)
{
	if (ammoStatus)
	{
		DWORD ammoAddressToWrite = findDmaAdd(3, hProcHandle, AmmoOffsets, ammoBaseAddress);
		WriteProcessMemory(hProcHandle, (BYTE*)ammoAddressToWrite, &ammoValue, sizeof(ammoValue), NULL);//this si the key to overwrite current ammo value
	}

	if (healthStatus)
	{
		DWORD healthAddressToWrite = findDmaAdd(1, hProcHandle, healthOffsets, healthBaseAddress);
		WriteProcessMemory(hProcHandle, (BYTE*)healthAddressToWrite, &healthValue, sizeof(healthValue), NULL);//this si the key to overwrite current ammo value
	}
}