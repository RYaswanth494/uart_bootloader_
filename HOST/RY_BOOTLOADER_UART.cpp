#include <windows.h>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
/**********************************************************************
 *                 Bootloader Commands                                *
***********************************************************************/
#define CBL_GET_VER_CMD              0x10
#define CBL_GET_HELP_CMD             0x11
#define CBL_GET_CID_CMD              0x12
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_GO_TO_ADDR_CMD           0x14
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16
#define CBL_ED_W_PROTECT_CMD         0x17
#define CBL_MEM_READ_CMD             0x18
#define CBL_READ_SECTOR_STATUS_CMD   0x19
#define CBL_OTP_READ_CMD             0x20
#define CBL_CHANGE_ROP_Level_CMD     0x21
// Sector Status
#define INVALID_SECTOR_NUMBER        0x00
#define VALID_SECTOR_NUMBER          0x01
#define UNSUCCESSFUL_ERASE           0x02
#define SUCCESSFUL_ERASE             0x03
// Flash Write Status
#define FLASH_PAYLOAD_WRITE_FAILED   0x00
#define FLASH_PAYLOAD_WRITE_PASSED   0x01
// Runtime Flags (not constant, so use regular variables)
int verbose_mode = 1;
int Memory_Write_Active = 0;
/***************************************************************************
*               Function Declarations                                      *
****************************************************************************/
bool is_port_available1(const string& full_port_name);
void Entering_Into_Menu();
void Decode_CBL_Command(int cmd);
/***************************************************************************
*                       main                                               *
****************************************************************************/
int main() {
    string port;

    // Scan COM1 to COM250
    // for (int i = 1; i <= 250; ++i) {
    //     string port_name = "\\\\.\\COM" + to_string(i);

    //     if (is_port_available(port_name)) {
    //         cout << "Port " << port_name << " is available" << endl;
    //     } else {
    //         cout << " Port " << port_name << " is not available" << endl;
    //     }
    // }

    cout << "\nEnter COM port to check (e.g., COM3): ";
    cin >> port;

    if (is_port_available1(port)) {
        cout << port << " is available and  accessible." << endl;
        Entering_Into_Menu();
    } else {
        cout << port << " is not available or accessible." << endl;
    }

    return 0;
}
/***************************************************************************
*                                                                          *
****************************************************************************/
bool is_port_available1(const string& port_name) {
    string full_port_name = "\\\\.\\" + port_name;

    HANDLE hSerial = CreateFileA(full_port_name.c_str(),
                                 GENERIC_READ | GENERIC_WRITE,
                                 0,
                                 NULL,
                                 OPEN_EXISTING,
                                 0,
                                 NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        return false;
    }

    CloseHandle(hSerial);
    return true;
}
/***************************************************************************
*                                                                          *
****************************************************************************/
void Entering_Into_Menu(){
    int CBL_Command;
    while(1){
        cout << "\nSTM32F103 Custom BootLoader\n";
        cout << "==============================\n";
        cout << "Which command you need to send to the bootLoader:\n";
        cout << "   CBL_GET_VER_CMD              --> 1\n";
        cout << "   CBL_GET_HELP_CMD             --> 2\n";
        cout << "   CBL_GET_CID_CMD              --> 3\n";
        cout << "   CBL_GET_RDP_STATUS_CMD       --> 4\n";
        cout << "   CBL_GO_TO_ADDR_CMD           --> 5\n";
        cout << "   CBL_FLASH_ERASE_CMD          --> 6\n";
        cout << "   CBL_MEM_WRITE_CMD            --> 7\n";
        cout << "   CBL_ED_W_PROTECT_CMD         --> 8\n";
        cout << "   CBL_MEM_READ_CMD             --> 9\n";
        cout << "   CBL_READ_SECTOR_STATUS_CMD   --> 10\n";
        cout << "   CBL_OTP_READ_CMD             --> 11\n";
        cout << "   CBL_CHANGE_ROP_Level_CMD     --> 12\n";
        cout << "\nEnter the command code: ";
        cin >> CBL_Command;
                if (cin.fail()) {
            cout << " Error: Please enter a valid number!\n";
            // Clear input stream error and discard invalid input
            cin.clear();
            cin.ignore(10, '\n');
        } else {
            Decode_CBL_Command(CBL_Command);
        }
        cout << "\n Press Enter to continue...";
        cin.ignore();  // flush leftover newline
        cin.get();     // wait for Enter key
    }
}

/***************************************************************************
*                                                                          *
****************************************************************************/
void Decode_CBL_Command(int cmd) {
    cout << " Executing bootloader command code: " << cmd << endl;
    uint8_t BL_Host_Buffer[255];
    memset(BL_Host_Buffer, 0, sizeof(BL_Host_Buffer));// Clear the buffer (set all bytes to 0)
    // You can replace this with switch-case for real actions
    // switch (cmd) {
    //     case 1: cout << "CBL_GET_VER_CMD\n"; break;
    //     case 2: cout << "CBL_GET_HELP_CMD\n"; break;
    //     case 3: cout << "CBL_GET_CID_CMD\n"; break;
    //     case 4: cout << "CBL_GET_RDP_STATUS_CMD\n"; break;
    //     case 5: cout << "CBL_GO_TO_ADDR_CMD\n"; break;
    //     case 6: cout << "CBL_FLASH_ERASE_CMD\n"; break;
    //     case 7: cout << "CBL_MEM_WRITE_CMD\n"; break;
    //     case 8: cout << "CBL_ED_W_PROTECT_CMD\n"; break;
    //     case 9: cout << "CBL_MEM_READ_CMD\n"; break;
    //     case 10: cout << "CBL_READ_SECTOR_STATUS_CMD\n"; break;
    //     case 11: cout << "CBL_OTP_READ_CMD\n"; break;
    //     case 12: cout << "CBL_CHANGE_ROP_Level_CMD\n"; break;
    //     default: cout << " Invalid command code!\n"; break;
    // }
}
/***************************************************************************
*                                                                          *
****************************************************************************/

/***************************************************************************
*                                                                          *
****************************************************************************/

/***************************************************************************
*                                                                          *
****************************************************************************/

/***************************************************************************
*                                                                          *
****************************************************************************/