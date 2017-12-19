#include <iostream>
#include <windows.h>
#include <c++/fstream>
#include <thread>
#include "mingw.thread.h"
#include "plog/Log.h"
#include "cmdTools.h"
#include "GitReleases.h"

#pragma comment( lib, "wininet" )

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

using namespace std;

BOOL IsCurrentUserLocalAdministrator(void);

bool bConnect(void);
void exportREADME(void);
void exportLICENSE(void);
BOOL IsWow64(void);
bool IsWin7OrLater(void);
bool IsWindows8OrGreater(void);
bool CheckUpdate(string version);
void WindowsDefender(bool offline);

int main() {
    if (pathExists("RTLog.log")) {
        remove("RTLog.log");
    }
    exportREADME();
    exportLICENSE();
    bool Updates = CheckUpdate("0.91");
    plog::init_txt("RTLog.log", plog::debug); //https://www.codeproject.com/Articles/992287/Plog-portable-and-simple-log-for-Cplusplus#step-2-initialization
    if (!IsCurrentUserLocalAdministrator()){
        LOG_FATAL << "No admin privileges\n";
        cout << "Admin rights needed for executing this program . . . \n" << endl;
        system("pause");
        exit(1);
    } else {
        thread bt(RESTOREPOINT);
        LOG_INFO << "Program executed with admin privileges\n";
        cout << "        \\                 \\\n"
                "         \\         ..      \\\n"
                "          \\       /  `-.       __.-.___\n"
                "  `-.      \\     /  #   `-._.-'    \\   `--.__\n"
                "     `-.        /  ####    /   ###  \\        `.\n"
                "  ________     /  #### ############  |       _|           .'\n"
                "              |\\ #### ##############  \\__.--' |    /    .'\n"
                "              | ####################  |       |   /   .'\n"
                "              | #### ###############  |       |  /\n"
                "              | #### ###############  |      /|      ----\n"
                "            . | ## WinRepair Tool ##  |    .'<    ____\n"
                "          .'  | ####################  | _.'-'\\|\n"
                "        .'    |   ##################  |       |\n"
                "               `.   ################  |       |\n"
                "                 `.    ############   |       | ----\n"
                "                ___`.     #####     _..____.-'     .\n"
                "               |`-._ `-._       _.-'    \\\\\\         `.\n"
                "            .'`-._  `-._ `-._.-'`--.___.-' \\          `.\n"
                "          .' .. . `-._  `-._        ___.---'|   \\   \\\n"
                "        .' .. . .. .  `-._  `-.__.-'        |    \\   \\\n"
                "       |`-. . ..  . .. .  `-._|             |     \\   \\\n"
                "       |   `-._ . ..  . ..   .'            _|\n"
                "        `-._   `-._ . ..   .' |      __.--'\n"
                "            `-._   `-._  .' .'|__.--'\n"
                "                `-._   `' .'\n"
                "                    `-._.'" << endl;
        Sleep(2000);
        system("cls");
        cout << "+---------------------------+---------------+\n"
                "| Windows Repair Tool (x86) | Version: 0.91 |\n"
                "+---------------------------+---------------+\n"
                "\n"
                "      Copyright \270 Javinator9889 - 2017\n"
                "\n"
                "   Program licensed under MIT License. See \n"
                "   details in generated file \"LICENSE.rtf\" \n"
                "   (in the execution path) of this program. \n"
                "\n"
                "    More info about this program in file \n"
                "\"README.rtf\", available also in the execution \n"
                "           path of this program.\n"
                "\n"
                "\n"
                "Go to: https://goo.gl/F5PV35 for more" << endl;
        Sleep(5000);
        if (Updates) {
            system("cls");
            cout << "There is an update available. Please, go to    > https://goo.gl/u75kUh <    for getting the latest version\n" << endl;
            system("pause");
        }
        if (IsWindows8OrGreater()) {
            LOG_INFO << "OS greater than WINDOWS 8. All capabilities available\n";
            if (IsWow64()) {
                LOG_FATAL << "64-bit OS. This version is for 32-bit. Exiting . . .";
                cout << "It seems that your Windows is 64-bit version. This is for 32-bit OS\n"
                        "\n"
                        "Please, go to  > https://github.com/Javinator9889/WinRepairTool#downloads <   and get the 64-bit version\n" << endl;
                system("pause");
                exit(1);
            } else if (bConnect()) {
                LOG_INFO << "System has Internet connection";
                system("cls");
                cout << "\n\tPerforming first operation . . . Please, keep your system connected to Internet" << endl;
                cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                LOG_DEBUG << "Initializing execution of DISM.EXE command ...";
                DISM(false);
                LOG_INFO << "DISM.EXE finalized";
                Sleep(1000);
                system("cls");
                LOG_DEBUG << "Initializing execution of SFC.EXE command ...";
                cout << "\n\tDoing second operation . . . (No need of Internet connection)" << endl;
                cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                SFC(false);
                LOG_INFO << "SFC.EXE finalized";
                Sleep(1000);
                system("cls");
                LOG_DEBUG << "Initializing checking drives ...";
                char aChar;
                string dr_letter;
                string run;
                for (int i = 0; i < 26; ++i) {
                    system("cls");
                    aChar = (char) ('A' + i);
                    dr_letter.push_back(aChar);
                    run = "cmd /c chkdsk " + dr_letter + ": /R";
                    cout << "\n\tDoing third operation . . . Please, do not remove your drives from the computer" << endl;
                    cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                    cout << "\t\tAnalyzing and repairing drive - " << dr_letter << ":\\\n" << endl;
                    LOG_DEBUG << "Checking drive: " << dr_letter << ":\\";
                    system(run.c_str());
                    dr_letter.clear();
                    run.clear();
                }
                LOG_INFO << "CHKDSK finished";
                LOG_INFO << "Trying to look for viruses\n";
                cout << "\n\tDoing fourth operation . . . Please, keep your system connected to Internet" << endl;
                WindowsDefender(false);
                LOG_INFO << "Windows Defender finished\n";
                LOG_DEBUG << "Requesting reboot . . .";
                system("cls");
                cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
                char option = 'd';
                while (option != 'S' && option != 's' && option != 'N' && option != 'n') {
                    cin >> option;
                    switch (option) {
                        case 'Y':
                        case 'y':
                        {
                            cout << "\nRebooting . . .";
                            Sleep(500);
                            system("cmd /c shutdown /r /c \"REBOOT BECAUSE OF REPAIRS IN WINDOWS\"");
                            exit(0);
                        }
                        case 'N':
                        case 'n':
                        {
                            cout << "\nSystem will not reboot. You should reboot your system manually later" << endl;
                            system("pause");
                            exit(0);
                        }
                        default:
                        {
                            system("cls");
                            cout << "Type \"Y\" (Yes) or \"N\" (No) to confirm your selection\n" << endl;
                            cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
                            break;
                        }
                    }
                }
            } else {
                LOG_WARNING << "System has no Internet connection ... Working in \"offline\" mode";
                system("cls");
                LOG_DEBUG << "Initializing execution of SFC.EXE command ... #OFFLINE MODE";
                cout << "\n\tDoing first operation . . . #OFFLINE MODE" << endl;
                cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                SFC(false);
                LOG_INFO << "SFC.EXE finalized #OFFLINE MODE";
                Sleep(1000);
                system("cls");
                LOG_DEBUG << "Initializing checking drives ... #OFFLINE MODE";
                char aChar;
                string dr_letter;
                string run;
                for (int i = 0; i < 26; ++i) {
                    system("cls");
                    aChar = (char) ('A' + i);
                    dr_letter.push_back(aChar);
                    run = "cmd /c chkdsk " + dr_letter + ": /R";
                    cout << "\n\tDoing second operation . . . Please, do not remove your drives from the computer #OFFLINE MODE" << endl;
                    cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                    cout << "\t\tAnalyzing and repairing drive - " << dr_letter << ":\\\n" << endl;
                    LOG_DEBUG << "Checking drive: " << dr_letter << ":\\ #OFFLINE MODE";
                    system(run.c_str());
                    dr_letter.clear();
                    run.clear();
                }
                LOG_INFO << "CHKDSK finished #OFFLINE MODE";
                LOG_INFO << "Looking for viruses... #OFFLINE MODE";
                cout << "\n\tDoing fourth operation . . . #OFFLINE MODE\n";
                WindowsDefender(true);
                LOG_INFO << "Windows Defender finished\n";
                LOG_DEBUG << "Requesting reboot . . . #OFFLINE MODE";
                system("cls");
                cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
                char option = 'd';
                while (option != 'S' && option != 's' && option != 'N' && option != 'n') {
                    cin >> option;
                    switch (option) {
                        case 'Y':
                        case 'y':
                        {
                            cout << "\nRebooting . . .";
                            Sleep(500);
                            system("cmd /c shutdown /r /c \"REBOOT BECAUSE OF REPAIRS IN WINDOWS\"");
                            exit(0);
                        }
                        case 'N':
                        case 'n':
                        {
                            cout << "\nSystem will not reboot. You should reboot your system manually later" << endl;
                            system("pause");
                            exit(0);
                        }
                        default:
                        {
                            system("cls");
                            cout << "Type \"Y\" (Yes) or \"N\" (No) to confirm your selection\n" << endl;
                            cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
                            break;
                        }
                    }
                }
            }
        } else {
            LOG_WARNING << "OS not greater than WINDOWS 8. Using compatible capabilities\n";
            system("cls");
            LOG_DEBUG << "Initializing execution of SFC.EXE command ... #COMPATIBLE MODE";
            cout << "\n\tDoing first operation . . . #COMPATIBLE MODE" << endl;
            cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
            SFC(false);
            LOG_INFO << "SFC.EXE finalized #COMPATIBLE MODE";
            Sleep(1000);
            system("cls");
            LOG_DEBUG << "Initializing checking drives ... #COMPATIBLE MODE";
            char aChar;
            string dr_letter;
            string run;
            for (int i = 0; i < 26; ++i) {
                system("cls");
                aChar = (char) ('A' + i);
                dr_letter.push_back(aChar);
                run = "cmd /c chkdsk " + dr_letter + ": /R";
                cout << "\n\tDoing second operation . . . Please, do not remove your drives from the computer #COMPATIBLE MODE" << endl;
                cout << "\tPress \"Ctrl + C\" to cancel at any time\n" << endl;
                cout << "\t\tAnalyzing and repairing drive - " << dr_letter << ":\\\n" << endl;
                LOG_DEBUG << "Checking drive: " << dr_letter << ":\\ #COMPATIBLE MODE";
                system(run.c_str());
                dr_letter.clear();
                run.clear();
            }
            LOG_INFO << "CHKDSK finished #COMPATIBLE MODE";
            cout << "\n\tDoing fourth operation . . . #COMPATIBLE MODE" << endl;
            LOG_INFO << "Looking for viruses... #COMPATIBLE MODE\n";
            WindowsDefender(true);
            LOG_INFO << "Windows Defender finished #COMPATIBLE MODE\n";
            LOG_DEBUG << "Requesting reboot . . . #COMPATIBLE MODE";
            system("cls");
            cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
            char option = 'd';
            while (option != 'S' && option != 's' && option != 'N' && option != 'n') {
                cin >> option;
                switch (option) {
                    case 'Y':
                    case 'y':
                    {
                        cout << "\nRebooting . . .";
                        Sleep(500);
                        system("cmd /c shutdown /r /c \"REBOOT BECAUSE OF REPAIRS IN WINDOWS\"");
                        exit(0);
                    }
                    case 'N':
                    case 'n':
                    {
                        cout << "\nSystem will not reboot. You should reboot your system manually later" << endl;
                        system("pause");
                        exit(0);
                    }
                    default:
                    {
                        system("cls");
                        cout << "Type \"Y\" (Yes) or \"N\" (No) to confirm your selection\n" << endl;
                        cout << "All operations done. A reboot is needed to complete the process. Would you like to reboot now? (Y/N): ";
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

BOOL IsCurrentUserLocalAdministrator(void) {
    BOOL   fReturn         = FALSE;
    DWORD  dwStatus;
    DWORD  dwAccessMask;
    DWORD  dwAccessDesired;
    DWORD  dwACLSize;
    DWORD  dwStructureSize = sizeof(PRIVILEGE_SET);
    PACL   pACL            = NULL;
    PSID   psidAdmin       = NULL;

    HANDLE hToken              = NULL;
    HANDLE hImpersonationToken = NULL;

    PRIVILEGE_SET   ps;
    GENERIC_MAPPING GenericMapping;

    PSECURITY_DESCRIPTOR     psdAdmin           = NULL;
    SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;
    LOG_INFO << "Checking for admin privileges\n";


    /*
       Determine if the current thread is running as a user that is a member

 of
       the local admins group.  To do this, create a security descriptor

 that
       has a DACL which has an ACE that allows only local aministrators

 access.
       Then, call AccessCheck with the current thread's token and the

 security
       descriptor.  It will say whether the user could access an object if

 it
       had that security descriptor.  Note: you do not need to actually

 create
       the object.  Just checking access against the security descriptor

 alone
       will be sufficient.
    */
    const DWORD ACCESS_READ  = 1;
    const DWORD ACCESS_WRITE = 2;


    __try
    {

        /*
           AccessCheck() requires an impersonation token.  We first get a

  primary
           token and then create a duplicate impersonation token.  The
           impersonation token is not actually assigned to the thread, but is
           used in the call to AccessCheck.  Thus, this function itself never
           impersonates, but does use the identity of the thread.  If the

  thread
           was impersonating already, this function uses that impersonation

  context.
        */
        if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE|TOKEN_QUERY,

                             TRUE, &hToken))
        {
            if (GetLastError() != ERROR_NO_TOKEN)
                return false;

            if (!OpenProcessToken(GetCurrentProcess(),

                                  TOKEN_DUPLICATE|TOKEN_QUERY, &hToken))
                return false;
        }

        if (!DuplicateToken (hToken, SecurityImpersonation,

                             &hImpersonationToken))
            return false;


        /*
          Create the binary representation of the well-known SID that
          represents the local administrators group.  Then create the

  security
          descriptor and DACL with an ACE that allows only local admins

  access.
          After that, perform the access check.  This will determine whether
          the current user is a local admin.
        */
        if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
                                      SECURITY_BUILTIN_DOMAIN_RID,
                                      DOMAIN_ALIAS_RID_ADMINS,
                                      0, 0, 0, 0, 0, 0, &psidAdmin))
            return false;

        psdAdmin = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
        if (psdAdmin == NULL)
            return false;

        if (!InitializeSecurityDescriptor(psdAdmin,

                                          SECURITY_DESCRIPTOR_REVISION))
            return false;

        // Compute size needed for the ACL.
        dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
                    GetLengthSid(psidAdmin) - sizeof(DWORD);

        pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
        if (pACL == NULL)
            return false;

        if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))
            return false;

        dwAccessMask= ACCESS_READ | ACCESS_WRITE;

        if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask,

                                 psidAdmin))
            return false;

        if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
            return false;

        /*
           AccessCheck validates a security descriptor somewhat; set the

  group
           and owner so that enough of the security descriptor is filled out

  to
           make AccessCheck happy.
        */
        SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
        SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

        if (!IsValidSecurityDescriptor(psdAdmin))
            return false;

        dwAccessDesired = ACCESS_READ;

        /*
           Initialize GenericMapping structure even though you
           do not use generic rights.
        */
        GenericMapping.GenericRead    = ACCESS_READ;
        GenericMapping.GenericWrite   = ACCESS_WRITE;
        GenericMapping.GenericExecute = 0;
        GenericMapping.GenericAll     = ACCESS_READ | ACCESS_WRITE;

        if (!AccessCheck(psdAdmin, hImpersonationToken, dwAccessDesired,
                         &GenericMapping, &ps, &dwStructureSize, &dwStatus,
                         &fReturn))
        {
            fReturn = FALSE;
            return false;
        }
    }
    catch (exception)
    {
        // Clean up.
        return false;
    }
    LocalFree(pACL);
    LocalFree(psdAdmin);
    if (psidAdmin) FreeSid(psidAdmin);
    if (hImpersonationToken) CloseHandle (hImpersonationToken);
    if (hToken) CloseHandle (hToken);

    return fReturn;
}

bool bConnect(void) {
    LOG_DEBUG << "Checking Internet connection";
    return system("ping www.google.com -n 1 > nul") == 0;
}

void WindowsDefender(bool offline) {
    LOG_DEBUG << "Trying to execute WindowsDefender...\n";
    if (IsWin7OrLater()) {
        LOG_DEBUG << "OS is Windows 7 OR greater\n";
        LOG_DEBUG << "Looking for new updates...\n";
        if (!offline) {
            system("cmd /c \"%ProgramFiles%\\Windows Defender\\MpCmdRun.exe\" -SignatureUpdate -MMPC");
            LOG_DEBUG << "Completed\n";
        } else {
            LOG_WARNING << "No Internet connection\n";
        }
        LOG_DEBUG << "Starting fastest scan...\n";
        int scanResult = system("cmd /c \"%ProgramFiles%\\Windows Defender\\MpCmdRun.exe\" -Scan -1 -BootSectorScan");
        if (scanResult == 0) {
            cout << "All found problems during Windows Defender scan were solved" << endl;
            LOG_DEBUG << "All found problems were solved\n";
        } else {
            cout << "User action required. Please, check Windows Defender history" << endl;
            LOG_WARNING << "User action required.\n";
        }
        LOG_DEBUG << "Programmed full scan for next boot\n";
        return;
    } else {
        LOG_WARNING << "OS is not Windows 7 OR greater. Aborting...\n";
        cout << "Windows Defender is not available on this computer. Please, use your own antivirus for checking" << endl;
        return;
    }
}

bool IsWin7OrLater(void) {
    DWORD version = GetVersion();
    DWORD major = (DWORD) (LOBYTE(LOWORD(version)));
    DWORD minor = (DWORD) (HIBYTE(LOWORD(version)));

    return (major > 6) || ((major == 6) && (minor >= 1));
}

bool IsWindows8OrGreater(void) {
    DWORD version = GetVersion();
    DWORD major = (DWORD) (LOBYTE(LOWORD(version)));
    DWORD minor = (DWORD) (HIBYTE(LOWORD(version)));

    return (major > 6.1) || ((major == 6) && (minor >= 2));
}

void exportREADME(void) {
    LOG_INFO << "Creating README file ...";
    string DATA = "{\\rtf1\\adeflang1025\\ansi\\ansicpg1252\\uc1\\adeff0\\deff0\\stshfdbch31505\\stshfloch31506\\stshfhich31506\\stshfbi0\\deflang3082\\deflangfe3082\\themelang3082\\themelangfe0\\themelangcs0{\\fonttbl{\\f0\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f0\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\f38\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0302020204030204}Calibri Light;}{\\f42\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 00000000000000000000}Verdana;}{\\flomajor\\f31500\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\fdbmajor\\f31501\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\fhimajor\\f31502\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0302020204030204}Calibri Light;}\n"
            "{\\fbimajor\\f31503\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\flominor\\f31504\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\fdbminor\\f31505\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\fhiminor\\f31506\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0502020204030204}Calibri;}\n"
            "{\\fbiminor\\f31507\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f43\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\f44\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\f46\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f47\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\f48\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\f49\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\f50\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f51\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\f43\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\f44\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\f46\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f47\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\f48\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\f49\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\f50\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f51\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\f423\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri Light CE;}{\\f424\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Light Cyr;}\n"
            "{\\f426\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Light Greek;}{\\f427\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Light Tur;}{\\f428\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri Light (Hebrew);}{\\f429\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri Light (Arabic);}\n"
            "{\\f430\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Light Baltic;}{\\f431\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri Light (Vietnamese);}{\\f463\\fbidi \\fswiss\\fcharset238\\fprq2 Verdana CE;}{\\f464\\fbidi \\fswiss\\fcharset204\\fprq2 Verdana Cyr;}\n"
            "{\\f466\\fbidi \\fswiss\\fcharset161\\fprq2 Verdana Greek;}{\\f467\\fbidi \\fswiss\\fcharset162\\fprq2 Verdana Tur;}{\\f470\\fbidi \\fswiss\\fcharset186\\fprq2 Verdana Baltic;}{\\f471\\fbidi \\fswiss\\fcharset163\\fprq2 Verdana (Vietnamese);}\n"
            "{\\flomajor\\f31508\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\flomajor\\f31509\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\flomajor\\f31511\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}\n"
            "{\\flomajor\\f31512\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\flomajor\\f31513\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\flomajor\\f31514\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\flomajor\\f31515\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\flomajor\\f31516\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fdbmajor\\f31518\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\fdbmajor\\f31519\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\fdbmajor\\f31521\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fdbmajor\\f31522\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
            "{\\fdbmajor\\f31523\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\fdbmajor\\f31524\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fdbmajor\\f31525\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}\n"
            "{\\fdbmajor\\f31526\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fhimajor\\f31528\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri Light CE;}{\\fhimajor\\f31529\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Light Cyr;}\n"
            "{\\fhimajor\\f31531\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Light Greek;}{\\fhimajor\\f31532\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Light Tur;}{\\fhimajor\\f31533\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri Light (Hebrew);}\n"
            "{\\fhimajor\\f31534\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri Light (Arabic);}{\\fhimajor\\f31535\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Light Baltic;}{\\fhimajor\\f31536\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri Light (Vietnamese);}\n"
            "{\\fbimajor\\f31538\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fbimajor\\f31539\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\fbimajor\\f31541\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}\n"
            "{\\fbimajor\\f31542\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fbimajor\\f31543\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\fbimajor\\f31544\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\fbimajor\\f31545\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fbimajor\\f31546\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\flominor\\f31548\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\flominor\\f31549\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\flominor\\f31551\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\flominor\\f31552\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
            "{\\flominor\\f31553\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\flominor\\f31554\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\flominor\\f31555\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}\n"
            "{\\flominor\\f31556\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fdbminor\\f31558\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fdbminor\\f31559\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\fdbminor\\f31561\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fdbminor\\f31562\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fdbminor\\f31563\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\fdbminor\\f31564\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fdbminor\\f31565\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fdbminor\\f31566\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}\n"
            "{\\fhiminor\\f31568\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri CE;}{\\fhiminor\\f31569\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Cyr;}{\\fhiminor\\f31571\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Greek;}{\\fhiminor\\f31572\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Tur;}\n"
            "{\\fhiminor\\f31573\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri (Hebrew);}{\\fhiminor\\f31574\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri (Arabic);}{\\fhiminor\\f31575\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Baltic;}\n"
            "{\\fhiminor\\f31576\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri (Vietnamese);}{\\fbiminor\\f31578\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fbiminor\\f31579\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\fbiminor\\f31581\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fbiminor\\f31582\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fbiminor\\f31583\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\fbiminor\\f31584\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fbiminor\\f31585\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fbiminor\\f31586\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}}\n"
            "{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\\red0\\green0\\blue128;\\red0\\green128\\blue128;\\red0\\green128\\blue0;\n"
            "\\red128\\green0\\blue128;\\red128\\green0\\blue0;\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;\\chyperlink\\ctint255\\cshade255\\red5\\green99\\blue193;\\red230\\green230\\blue230;}{\\*\\defchp \\fs22\\loch\\af31506\\hich\\af31506\\dbch\\af31505 }\n"
            "{\\*\\defpap \\ql \\li0\\ri0\\sa160\\sl259\\slmult1\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 }\\noqfpromote {\\stylesheet{\\ql \\li0\\ri0\\sa160\\sl259\\slmult1\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \n"
            "\\rtlch\\fcs1 \\af0\\afs22\\alang1025 \\ltrch\\fcs0 \\fs22\\lang3082\\langfe3082\\loch\\f31506\\hich\\af31506\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 \\snext0 \\sqformat \\spriority0 Normal;}{\\s2\\ql \\li0\\ri0\\sb240\\sa60\\sl259\\slmult1\n"
            "\\keepn\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\outlinelevel1\\adjustright\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\ab\\ai\\af0\\afs28\\alang1025 \\ltrch\\fcs0 \\b\\i\\fs28\\lang3082\\langfe3082\\loch\\f31502\\hich\\af31502\\dbch\\af31501\\cgrid\\langnp3082\\langfenp3082 \n"
            "\\sbasedon0 \\snext0 \\slink15 \\sunhideused \\sqformat \\spriority9 \\styrsid3608401 heading 2;}{\\*\\cs10 \\additive \\ssemihidden \\sunhideused \\spriority1 Default Paragraph Font;}{\\*\n"
            "\\ts11\\tsrowd\\trftsWidthB3\\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddft3\\trpaddfb3\\trpaddfr3\\trcbpat1\\trcfpat1\\tblind0\\tblindtype3\\tsvertalt\\tsbrdrt\\tsbrdrl\\tsbrdrb\\tsbrdrr\\tsbrdrdgl\\tsbrdrdgr\\tsbrdrh\\tsbrdrv \\ql \\li0\\ri0\\sa160\\sl259\\slmult1\n"
            "\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af0\\afs22\\alang1025 \\ltrch\\fcs0 \\fs22\\lang3082\\langfe3082\\loch\\f31506\\hich\\af31506\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 \\snext11 \\ssemihidden \\sunhideused \n"
            "Normal Table;}{\\*\\cs15 \\additive \\rtlch\\fcs1 \\ab\\ai\\af0\\afs28 \\ltrch\\fcs0 \\b\\i\\fs28\\loch\\f31502\\hich\\af31502\\dbch\\af31501 \\sbasedon10 \\slink2 \\slocked \\spriority9 \\styrsid3608401 T\\'edtulo 2 Car;}{\\*\\cs16 \\additive \\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\ul\\cf17 \n"
            "\\sbasedon10 \\sunhideused \\styrsid3608401 Hyperlink;}{\\*\\cs17 \\additive \\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\cf15\\chshdng0\\chcfpat0\\chcbpat18 \\sbasedon10 \\ssemihidden \\sunhideused \\styrsid3608401 Unresolved Mention;}}{\\*\\rsidtbl \\rsid211120\\rsid2118172\n"
            "\\rsid3608401\\rsid4284720\\rsid4863302\\rsid6227560\\rsid6763237\\rsid7761167\\rsid9902896\\rsid14964391\\rsid15816503\\rsid15825740}{\\mmathPr\\mmathFont34\\mbrkBin0\\mbrkBinSub0\\msmallFrac0\\mdispDef1\\mlMargin0\\mrMargin0\\mdefJc1\\mwrapIndent1440\\mintLim0\\mnaryLim1}\n"
            "{\\info{\\operator Javier Alonso Silva}{\\creatim\\yr2017\\mo8\\dy21\\hr11\\min19}{\\revtim\\yr2017\\mo8\\dy21\\hr16\\min22}{\\version9}{\\edmins189}{\\nofpages1}{\\nofwords236}{\\nofchars1302}{\\nofcharsws1535}{\\vern39}{\\*\\saveprevpict}\n"
            "{\\*\\passwordhash 0200000078000000180000000e800000a08601004000000010000000280000006800000000000000b7556c72f4cb5f0084a4368ee02d2921001f5fab08933befc352e17df1e5b950a5fe8b9d085da95328d52ecd3e2c32428fac44a6a1a2f8cdb7e91c4b5cb6b5e364686f6120e92a8cd0a3e89f0d903940\n"
            "}}{\\*\\userprops {\\propname _MarkAsFinal}\\proptype11{\\staticval 1}}{\\*\\xmlnstbl {\\xmlns1 http://schemas.microsoft.com/office/word/2003/wordml}}\\paperw12240\\paperh15840\\margl1701\\margr1701\\margt1417\\margb1417\\gutter0\\ltrsect \n"
            "\\widowctrl\\ftnbj\\aenddoc\\hyphhotz425\\trackmoves0\\trackformatting1\\donotembedsysfont0\\relyonvml0\\donotembedlingdata1\\grfdocevents0\\validatexml0\\showplaceholdtext0\\ignoremixedcontent0\\saveinvalidxml0\\showxmlerrors0\\annotprot\\readprot\\horzdoc\\dghspace120\n"
            "\\dgvspace120\\dghorigin1701\\dgvorigin1984\\dghshow0\\dgvshow3\\jcompress\\viewkind1\\viewscale100\\rsidroot3608401 \\fet0{\\*\\wgrffmtfilter 2450}\\ilfomacatclnup0\\enforceprot1\\protlevel3\\ltrpar \\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\*\\pnseclvl1\n"
            "\\pnucrm\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl2\\pnucltr\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang {\\pntxta )}}{\\*\\pnseclvl5\n"
            "\\pndec\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6\\pnlcltr\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang \n"
            "{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}\\pard\\plain \\ltrpar\\s2\\qc \\li0\\ri0\\sb240\\sa60\\sl259\\slmult1\n"
            "\\keepn\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\outlinelevel1\\adjustright\\rin0\\lin0\\itap0\\pararsid3608401 \\rtlch\\fcs1 \\ab\\ai\\af0\\afs28\\alang1025 \\ltrch\\fcs0 \n"
            "\\b\\i\\fs28\\lang3082\\langfe3082\\loch\\af31502\\hich\\af31502\\dbch\\af31501\\cgrid\\langnp3082\\langfenp3082 {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \\hich\\af31502\\dbch\\af31501\\loch\\f31502 WINDOWS REPAIR TOOL \n"
            "\\hich\\f31502 \\endash \\loch\\f31502  by }{\\field{\\*\\fldinst {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\lang1033\\langfe3082\\langnp1033\\insrsid7761167 \\hich\\af31502\\dbch\\af31501\\loch\\f31502 HYPERLINK \"https://goo.gl/cwDpMi\"}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\lang1033\\langfe3082\\langnp1033\\insrsid7761167\\charrsid6227560 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90b44000000680074007400700073003a002f002f0067006f006f002e0067006c002f0063007700440070004d0069000000795881f43b1d7f48af2c825dc485276300000000a5ab000300}}}{\\fldrslt {\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\cs16\\ul\\cf17\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \\hich\\af31502\\dbch\\af31501\\loch\\f31502 Javinator9889}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\lang1033\\langfe3082\\langnp1033\\insrsid4284720\\charrsid6227560 \n"
            "\\par }\\pard\\plain \\ltrpar\\qj \\li0\\ri0\\sa160\\sl259\\slmult1\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0\\pararsid3608401 \\rtlch\\fcs1 \\af0\\afs22\\alang1025 \\ltrch\\fcs0 \n"
            "\\fs22\\lang3082\\langfe3082\\loch\\af31506\\hich\\af31506\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \n"
            "\\par }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 Windows}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid3608401 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42  Repair}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42  Tool}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401\\charrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42  }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560\\charrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "is a program you can use }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 for solving problems}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42  on your system. It uses basic CMD (}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 Windows Command Prompt)}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42  commands for repairing }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 system files}{\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 , check }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 health status}{\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42  and }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 devices for errors}{\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 .}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid3608401 \n"
            "\\par }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 Those all operations need }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 admin rights}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 : if not, program }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 cannot do this work. }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "It will not steal your data or similar, is just using }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 SFC, DISM }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 and }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \\hich\\af42\\dbch\\af31505\\loch\\f42 CHKDSK}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6763237 \\hich\\af42\\dbch\\af31505\\loch\\f42  commands for checking your PC (you can check }{\\field{\\*\\fldinst {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid7761167 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 HYPERLINK \"https://goo.gl/F5PV35\"}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid7761167 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90b44000000680074007400700073003a002f002f0067006f006f002e0067006c002f004600350050005600330035000000795881f43b1d7f48af2c825dc485276300000000a5ab000300}}}{\\fldrslt {\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\cs16\\f42\\ul\\cf17\\lang1033\\langfe3082\\langnp1033\\insrsid6763237\\charrsid6763237 \\hich\\af42\\dbch\\af31505\\loch\\f42 GitHub}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6763237 \\hich\\af42\\dbch\\af31505\\loch\\f42  to know what is doing your device)}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 .}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6227560 \n"
            "\\par }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302 \\hich\\af42\\dbch\\af31505\\loch\\f42 If there are any errors, you can check }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 log file}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302 \\hich\\af42\\dbch\\af31505\\loch\\f42  called }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 RTLog.log}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302 \\hich\\af42\\dbch\\af31505\\loch\\f42  (it is in the same path as the \\hich\\af42\\dbch\\af31505\\loch\\f42 executabl\n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 e program).}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503 \\hich\\af42\\dbch\\af31505\\loch\\f42  Also, if program asks for }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503 \\hich\\af42\\dbch\\af31505\\loch\\f42 some missing DLLs}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503 \\hich\\af42\\dbch\\af31505\\loch\\f42 , you can fin\n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 d them at }{\\field\\flddirty{\\*\\fldinst {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503\\charrsid15816503 \\hich\\af42\\dbch\\af31505\\loch\\f42  \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "HYPERLINK \"https://goo.gl/F5PV35\"\\hich\\af42\\dbch\\af31505\\loch\\f42  }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503\\charrsid15816503 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90b44000000680074007400700073003a002f002f0067006f006f002e0067006c002f004600350050005600330035000000795881f43b1d7f48af2c825dc485276300000000a5ab0003}}}{\\fldrslt {\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\cs16\\i\\f42\\ul\\cf17\\lang1033\\langfe3082\\langnp1033\\insrsid15816503\\charrsid15816503 \\hich\\af42\\dbch\\af31505\\loch\\f42 the project web-page}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15816503 .}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid4863302\\charrsid15816503 \n"
            "\\par }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 This software has a license (}{\\field\\flddirty{\\*\\fldinst {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\b\\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid7761167 \\hich\\af42\\dbch\\af31505\\loch\\f42 HYPERLINK\\hich\\af42\\dbch\\af31505\\loch\\f42  \"https://goo.gl/duMJWF\"}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\b\\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid7761167\\charrsid15825740 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90b44000000680074007400700073003a002f002f0067006f006f002e0067006c002f00640075004d004a00570046000000795881f43b1d7f48af2c825dc485276300000000a5ab000300}}}{\\fldrslt {\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\cs16\\b\\i\\f42\\ul\\cf17\\lang1033\\langfe3082\\langnp1033\\insrsid15825740\\charrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 MIT License}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 ) so you can do }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 whatever you want}{\\rtlch\\fcs1 \\af0 \n"
            "\\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42  with this software: distribute, modify, copy, etc. The only requirement is to include the }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 license file}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            " in each project, saying it is mine and I allow you to use it.\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 Despite it has a license, there is no guaranty: everything you do with this software is your responsibility. Because of security reasons, when you execute }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 Windows Repair }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\i\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740\\charrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 Tool}{\\rtlch\\fcs1 \n"
            "\\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 , it cr\\hich\\af42\\dbch\\af31505\\loch\\f42 eates a }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \n"
            "\\hich\\af42\\dbch\\af31505\\loch\\f42 System Restore }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\b\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740\\charrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 Point}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 , so }{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740\\charrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42 it}{\\rtlch\\fcs1 \\af0 \n"
            "\\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \\hich\\af42\\dbch\\af31505\\loch\\f42  is highly recommended}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid211120 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            " to enable this feature on your Windows OS.}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740 \n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 Finally, in case of need, here you have my contact mail: }{\\field\\fldedit{\\*\\fldinst {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid211120 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "HYPERLINK \"mailto:javinator9889@outlook.com?subject=QUESTION%20ABOUT%20WindowsRepairTool\"}{\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid211120 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90bb40000006d00610069006c0074006f003a006a006100760069006e00610074006f007200390038003800390040006f00750074006c006f006f006b002e0063006f006d003f007300750062006a006500630074003d00\n"
            "5100550045005300540049004f004e00250032003000410042004f0055005400250032003000570069006e0064006f007700730052006500700061006900720054006f006f006c000000795881f43b1d7f48af2c825dc485276300000000a5ab00030000}}}{\\fldrslt {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\cs16\\f42\\ul\\cf17\\lang1033\\langfe3082\\langnp1033\\insrsid211120 \\hich\\af42\\dbch\\af31505\\loch\\f42 javinator9889@outlook.com}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af0 \\ltrch\\fcs0 \n"
            "\\f42\\lang1033\\langfe3082\\langnp1033\\insrsid15825740\\charrsid211120 \n"
            "\\par }{\\*\\themedata 504b030414000600080000002100e9de0fbfff0000001c020000130000005b436f6e74656e745f54797065735d2e786d6cac91cb4ec3301045f748fc83e52d4a\n"
            "9cb2400825e982c78ec7a27cc0c8992416c9d8b2a755fbf74cd25442a820166c2cd933f79e3be372bd1f07b5c3989ca74aaff2422b24eb1b475da5df374fd9ad\n"
            "5689811a183c61a50f98f4babebc2837878049899a52a57be670674cb23d8e90721f90a4d2fa3802cb35762680fd800ecd7551dc18eb899138e3c943d7e503b6\n"
            "b01d583deee5f99824e290b4ba3f364eac4a430883b3c092d4eca8f946c916422ecab927f52ea42b89a1cd59c254f919b0e85e6535d135a8de20f20b8c12c3b0\n"
            "0c895fcf6720192de6bf3b9e89ecdbd6596cbcdd8eb28e7c365ecc4ec1ff1460f53fe813d3cc7f5b7f020000ffff0300504b030414000600080000002100a5d6\n"
            "a7e7c0000000360100000b0000005f72656c732f2e72656c73848fcf6ac3300c87ef85bd83d17d51d2c31825762fa590432fa37d00e1287f68221bdb1bebdb4f\n"
            "c7060abb0884a4eff7a93dfeae8bf9e194e720169aaa06c3e2433fcb68e1763dbf7f82c985a4a725085b787086a37bdbb55fbc50d1a33ccd311ba548b6309512\n"
            "0f88d94fbc52ae4264d1c910d24a45db3462247fa791715fd71f989e19e0364cd3f51652d73760ae8fa8c9ffb3c330cc9e4fc17faf2ce545046e37944c69e462\n"
            "a1a82fe353bd90a865aad41ed0b5b8f9d6fd010000ffff0300504b0304140006000800000021006b799616830000008a0000001c0000007468656d652f746865\n"
            "6d652f7468656d654d616e616765722e786d6c0ccc4d0ac3201040e17da17790d93763bb284562b2cbaebbf600439c1a41c7a0d29fdbd7e5e38337cedf14d59b\n"
            "4b0d592c9c070d8a65cd2e88b7f07c2ca71ba8da481cc52c6ce1c715e6e97818c9b48d13df49c873517d23d59085adb5dd20d6b52bd521ef2cdd5eb9246a3d8b\n"
            "4757e8d3f729e245eb2b260a0238fd010000ffff0300504b030414000600080000002100a7259ef29c070000cb200000160000007468656d652f7468656d652f\n"
            "7468656d65312e786d6cec59cd8b1bc915bf07f23f347d97f5d5ad8fc1f2a24fcfda33b6b164873dd648a5eef2547789aad28cc56208de532e81c026e49085bd\n"
            "ed21842cecc22eb9e48f31d8249b3f22afaa5bdd5552c99e191c3061463074977eefd5afde7bf5de53d5ddcf5e26d4bbc05c1096f6fcfa9d9aefe174ce16248d\n"
            "7afeb3d9a4d2f13d2151ba4094a5b8e76fb0f03fbbf7eb5fdd454732c609f6403e1547a8e7c752ae8eaa5531876124eeb0154ee1bb25e30992f0caa3ea82a34b\n"
            "d09bd06aa3566b55134452df4b51026a6720e32db0f778b92473ecdfdbaa1f53982395420dcc299f2ae5389731b08bf3ba42888d1852ee5d20daf361a605bb9c\n"
            "e197d2f7281212bee8f935fde757efddada2a35c88ca03b286dc44ffe572b9c0e2bca1e7e4d1593169108441ab5fe8d7002af771e3f6b8356e15fa3400cde7b0\n"
            "d28c8badb3dd180639d600658f0edda3f6a859b7f086fee61ee77ea83e165e8332fdc11e7e321982152dbc0665f8700f1f0eba8391ad5f83327c6b0fdfaef547\n"
            "41dbd2af413125e9f91eba16b69ac3ed6a0bc892d16327bc1b06937623575ea2201a8ae852532c592a0fc55a825e303e018002522449eac9cd0a2fd11ce27888\n"
            "2839e3c43b21510c81b7422913305c6bd426b526fc579f403f698fa2238c0c69c50b9888bd21c5c713734e56b2e73f00adbe0179fbf3cf6f5efff8e6f54f6fbe\n"
            "faeacdebbfe7736b5596dc314a2353ee97effef09f6f7eebfdfb876f7ff9fa8fd9d4bb7861e2dffded77effef1cff7a9871597a678fba7efdffdf8fddb3ffffe\n"
            "5f7ffddaa1bdcfd199099f91040bef11bef49eb20416e8e08fcff8f524663122a6443f8d044a919ac5a17f2c630bfd68832872e006d8b6e3730ea9c605bcbf7e\n"
            "61119ec67c2d8943e3c338b180a78cd101e34e2b3c547319669eadd3c83d395f9bb8a7085db8e61ea2d4f2f278bd821c4b5c2a8731b6683ea1289528c229969e\n"
            "fa8e9d63ec58dd178458763d2573ce045b4aef0be20d10719a6446ceac682a858e49027ed9b80882bf2ddb9c3ef7068cba563dc2173612f606a20ef2334c2d33\n"
            "de476b891297ca194aa869f013246317c9e986cf4ddc5848f0748429f3c60b2c844be63187f51a4e7f0869c6edf653ba496c2497e4dca5f30431662247ec7c18\n"
            "a364e5c24e491a9bd8cfc5398428f29e30e9829f327b87a877f0034a0fbafb39c196bb3f9c0d9e418635299501a2be5973872fef6366c5ef74439708bb524d9f\n"
            "27568aed73e28c8ec13ab242fb04638a2ed10263efd9e70e0603b6b26c5e927e10435639c6aec07a80ec5855ef2916d8d3cdcd7e9e3c21c20ad9298ed8013ea7\n"
            "9b9dc4b3416982f821cd8fc0eba6cdc750ea1257003ca6f37313f888401708f1e234ca63013a8ce03ea8f5498cac02a6de853b5e37dcf2df55f618eccb17168d\n"
            "2bec4b90c1d79681c46ecabcd7363344ad09ca809921e8325ce916442cf79722aab86ab1b5536e696fdad20dd01d594d4f42d20f76403bbd4ff8bfeb7da0c378\n"
            "fb976f1c9bede3f43b6ec556b2ba66a77328991ceff4378770bb5dcd90f105f9f49b9a115aa74f30d491fd8c75dbd3dcf634feff7d4f73683fdf763287fa8ddb\n"
            "4ec6870ee3b693c90f573e4e2753362fd0d7a8038feca0471ffb24074f7d9684d2a9dc507c22f4c18f80df338b090c2a397de6898b53c0550c8faaccc104162e\n"
            "e248cb789cc9df10194f63b482d3a1baaf944422571d096fc5041c1ae961a76e85a7ebe4942db2c3ce7a5d1d6c66955520598ed7c2621c0eaa64866eb5cb03bc\n"
            "42bd661be983d62d01257b1d12c6643689a683447b3ba88ca48f75c1680e127a651f8545d7c1a2a3d46f5db5c702a8155e811fdc1efc4ceff96100222004e771\n"
            "d09c2f949f32576fbdab9df9313d7dc89856044083bd8d80d2d35dc5f5e0f2d4eab250bb82a72d1246b8d924b46574832762f8199c47a71abd0a8debfaba5bba\n"
            "d4a2a74ca1e783d02a69b43bef6371535f83dc6e6ea0a9992968ea5df6fc5633849099a355cf5fc2a1313c262b881da17e73211ac1ddcb5cf26cc3df24b3acb8\n"
            "902324e2cce03ae964d9202112738f92a4e7abe5176ea0a9ce219a5bbd0109e19325d785b4f2a99103a7db4ec6cb259e4bd3edc688b274f60a193ecb15ce6fb5\n"
            "f8cdc14a92adc1ddd37871e99dd1357f8a20c4c2765d19704104dc1dd4336b2e085c861589ac8cbf9dc294a75df3364ac750368ee82a46794531937906d7a9bc\n"
            "a0a3df0a1b186ff99ac1a08649f2427816a9026b1ad5aaa645d5c8381cacba1f1652963392665933adaca2aaa63b8b59336ccbc08e2d6f56e40d565b13434e33\n"
            "2b7c96ba77536e779beb76fa84a24a80c10bfb39aaee150a8241ad9ccca2a618efa76195b3f351bb766c17f8016a57291246d66f6dd5eed8ada811cee960f046\n"
            "951fe476a3168696dbbe525b5adf9b9b17dbecec05248f1174b96b2a8576255c5b73040dd154f72459da802df252e65b039ebc35273dffcb5ad80f868d7058a9\n"
            "75c271256806b54a27ec372bfd306cd6c761bd361a345e41619171520fb33bfb095c60d04d7e73afc7f76eef93ed1dcd9d394baa4cdfca5735717d7b5f6f58b7\n"
            "f7d94dbc375397f3be4720e97cd96a4cbacdeea055e936fb934a301a742add616b5019b586edd164340c3bddc92bdfbbd0e0a0df1c06ad71a7d2aa0f8795a055\n"
            "53f43bdd4a3b6834fa41bbdf1907fd57791b032bcfd2476e0b30afe675efbf000000ffff0300504b0304140006000800000021000dd1909fb60000001b010000\n"
            "270000007468656d652f7468656d652f5f72656c732f7468656d654d616e616765722e786d6c2e72656c73848f4d0ac2301484f78277086f6fd3ba109126dd88\n"
            "d0add40384e4350d363f2451eced0dae2c082e8761be9969bb979dc9136332de3168aa1a083ae995719ac16db8ec8e4052164e89d93b64b060828e6f37ed1567\n"
            "914b284d262452282e3198720e274a939cd08a54f980ae38a38f56e422a3a641c8bbd048f7757da0f19b017cc524bd62107bd5001996509affb3fd381a89672f\n"
            "1f165dfe514173d9850528a2c6cce0239baa4c04ca5bbabac4df000000ffff0300504b01022d0014000600080000002100e9de0fbfff0000001c020000130000\n"
            "0000000000000000000000000000005b436f6e74656e745f54797065735d2e786d6c504b01022d0014000600080000002100a5d6a7e7c0000000360100000b00\n"
            "000000000000000000000000300100005f72656c732f2e72656c73504b01022d00140006000800000021006b799616830000008a0000001c0000000000000000\n"
            "0000000000190200007468656d652f7468656d652f7468656d654d616e616765722e786d6c504b01022d0014000600080000002100a7259ef29c070000cb2000\n"
            "001600000000000000000000000000d60200007468656d652f7468656d652f7468656d65312e786d6c504b01022d00140006000800000021000dd1909fb60000\n"
            "001b0100002700000000000000000000000000a60a00007468656d652f7468656d652f5f72656c732f7468656d654d616e616765722e786d6c2e72656c73504b050600000000050005005d010000a10b00000000}\n"
            "{\\*\\colorschememapping 3c3f786d6c2076657273696f6e3d22312e302220656e636f64696e673d225554462d3822207374616e64616c6f6e653d22796573223f3e0d0a3c613a636c724d\n"
            "617020786d6c6e733a613d22687474703a2f2f736368656d61732e6f70656e786d6c666f726d6174732e6f72672f64726177696e676d6c2f323030362f6d6169\n"
            "6e22206267313d226c743122207478313d22646b3122206267323d226c743222207478323d22646b322220616363656e74313d22616363656e74312220616363\n"
            "656e74323d22616363656e74322220616363656e74333d22616363656e74332220616363656e74343d22616363656e74342220616363656e74353d22616363656e74352220616363656e74363d22616363656e74362220686c696e6b3d22686c696e6b2220666f6c486c696e6b3d22666f6c486c696e6b222f3e}\n"
            "{\\*\\latentstyles\\lsdstimax375\\lsdlockeddef0\\lsdsemihiddendef0\\lsdunhideuseddef0\\lsdqformatdef0\\lsdprioritydef99{\\lsdlockedexcept \\lsdqformat1 \\lsdpriority0 \\lsdlocked0 Normal;\\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 4;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 7;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 9;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 5;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 9;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 6;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 9;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Normal Indent;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footnote text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 header;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footer;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index heading;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority35 \\lsdlocked0 caption;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 table of figures;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 envelope address;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 envelope return;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footnote reference;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation reference;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 line number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 page number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 endnote reference;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 endnote text;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 table of authorities;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 macro;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 toa heading;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 5;\\lsdqformat1 \\lsdpriority10 \\lsdlocked0 Title;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Closing;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Signature;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority1 \\lsdlocked0 Default Paragraph Font;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 4;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Message Header;\\lsdqformat1 \\lsdpriority11 \\lsdlocked0 Subtitle;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Salutation;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Date;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text First Indent;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text First Indent 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Note Heading;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Block Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Hyperlink;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 FollowedHyperlink;\\lsdqformat1 \\lsdpriority22 \\lsdlocked0 Strong;\n"
            "\\lsdqformat1 \\lsdpriority20 \\lsdlocked0 Emphasis;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Document Map;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Plain Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 E-mail Signature;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Top of Form;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Bottom of Form;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Normal (Web);\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Acronym;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Address;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Cite;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Code;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Definition;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Keyboard;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Preformatted;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Sample;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Typewriter;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Variable;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation subject;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 No List;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Balloon Text;\\lsdpriority39 \\lsdlocked0 Table Grid;\n"
            "\\lsdsemihidden1 \\lsdlocked0 Placeholder Text;\\lsdqformat1 \\lsdpriority1 \\lsdlocked0 No Spacing;\\lsdpriority60 \\lsdlocked0 Light Shading;\\lsdpriority61 \\lsdlocked0 Light List;\\lsdpriority62 \\lsdlocked0 Light Grid;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1;\\lsdpriority64 \\lsdlocked0 Medium Shading 2;\\lsdpriority65 \\lsdlocked0 Medium List 1;\\lsdpriority66 \\lsdlocked0 Medium List 2;\\lsdpriority67 \\lsdlocked0 Medium Grid 1;\\lsdpriority68 \\lsdlocked0 Medium Grid 2;\n"
            "\\lsdpriority69 \\lsdlocked0 Medium Grid 3;\\lsdpriority70 \\lsdlocked0 Dark List;\\lsdpriority71 \\lsdlocked0 Colorful Shading;\\lsdpriority72 \\lsdlocked0 Colorful List;\\lsdpriority73 \\lsdlocked0 Colorful Grid;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 1;\n"
            "\\lsdpriority61 \\lsdlocked0 Light List Accent 1;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 1;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 1;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 1;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 1;\n"
            "\\lsdsemihidden1 \\lsdlocked0 Revision;\\lsdqformat1 \\lsdpriority34 \\lsdlocked0 List Paragraph;\\lsdqformat1 \\lsdpriority29 \\lsdlocked0 Quote;\\lsdqformat1 \\lsdpriority30 \\lsdlocked0 Intense Quote;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 1;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 1;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 1;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 1;\\lsdpriority70 \\lsdlocked0 Dark List Accent 1;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 1;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 1;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 1;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 2;\\lsdpriority61 \\lsdlocked0 Light List Accent 2;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 2;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 2;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 2;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 2;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 2;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 2;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 2;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 2;\\lsdpriority70 \\lsdlocked0 Dark List Accent 2;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 2;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 2;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 2;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 3;\\lsdpriority61 \\lsdlocked0 Light List Accent 3;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 3;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 3;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 3;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 3;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 3;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 3;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 3;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 3;\\lsdpriority70 \\lsdlocked0 Dark List Accent 3;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 3;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 3;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 3;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 4;\\lsdpriority61 \\lsdlocked0 Light List Accent 4;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 4;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 4;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 4;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 4;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 4;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 4;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 4;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 4;\\lsdpriority70 \\lsdlocked0 Dark List Accent 4;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 4;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 4;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 4;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 5;\\lsdpriority61 \\lsdlocked0 Light List Accent 5;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 5;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 5;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 5;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 5;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 5;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 5;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 5;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 5;\\lsdpriority70 \\lsdlocked0 Dark List Accent 5;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 5;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 5;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 5;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 6;\\lsdpriority61 \\lsdlocked0 Light List Accent 6;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 6;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 6;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 6;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 6;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 6;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 6;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 6;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 6;\\lsdpriority70 \\lsdlocked0 Dark List Accent 6;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 6;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 6;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 6;\\lsdqformat1 \\lsdpriority19 \\lsdlocked0 Subtle Emphasis;\\lsdqformat1 \\lsdpriority21 \\lsdlocked0 Intense Emphasis;\n"
            "\\lsdqformat1 \\lsdpriority31 \\lsdlocked0 Subtle Reference;\\lsdqformat1 \\lsdpriority32 \\lsdlocked0 Intense Reference;\\lsdqformat1 \\lsdpriority33 \\lsdlocked0 Book Title;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority37 \\lsdlocked0 Bibliography;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority39 \\lsdlocked0 TOC Heading;\\lsdpriority41 \\lsdlocked0 Plain Table 1;\\lsdpriority42 \\lsdlocked0 Plain Table 2;\\lsdpriority43 \\lsdlocked0 Plain Table 3;\\lsdpriority44 \\lsdlocked0 Plain Table 4;\n"
            "\\lsdpriority45 \\lsdlocked0 Plain Table 5;\\lsdpriority40 \\lsdlocked0 Grid Table Light;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light;\\lsdpriority47 \\lsdlocked0 Grid Table 2;\\lsdpriority48 \\lsdlocked0 Grid Table 3;\\lsdpriority49 \\lsdlocked0 Grid Table 4;\n"
            "\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 1;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 1;\n"
            "\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 1;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 1;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 1;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 1;\n"
            "\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 1;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 2;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 2;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 2;\n"
            "\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 2;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 2;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 2;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 2;\n"
            "\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 3;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 3;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 3;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 3;\n"
            "\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 3;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 3;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 3;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 4;\n"
            "\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 4;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 4;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 4;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 4;\n"
            "\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 4;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 4;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 5;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 5;\n"
            "\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 5;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 5;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 5;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 5;\n"
            "\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 5;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 6;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 6;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 6;\n"
            "\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 6;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 6;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 6;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 6;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light;\\lsdpriority47 \\lsdlocked0 List Table 2;\\lsdpriority48 \\lsdlocked0 List Table 3;\\lsdpriority49 \\lsdlocked0 List Table 4;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark;\n"
            "\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 1;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 1;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 1;\n"
            "\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 1;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 1;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 1;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 1;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 2;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 2;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 2;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 2;\n"
            "\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 2;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 2;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 2;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 3;\n"
            "\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 3;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 3;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 3;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 3;\n"
            "\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 3;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 3;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 4;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 4;\n"
            "\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 4;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 4;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 4;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 4;\n"
            "\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 4;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 5;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 5;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 5;\n"
            "\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 5;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 5;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 5;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 5;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 6;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 6;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 6;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 6;\n"
            "\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 6;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 6;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Mention;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Smart Hyperlink;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Hashtag;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Unresolved Mention;}}{\\*\\datastore 010500000200000018000000\n"
            "4d73786d6c322e534158584d4c5265616465722e362e3000000000000000000000060000\n"
            "d0cf11e0a1b11ae1000000000000000000000000000000003e000300feff090006000000000000000000000001000000010000000000000000100000feffffff00000000feffffff0000000000000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "fffffffffffffffffdfffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffff52006f006f007400200045006e00740072007900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000016000500ffffffffffffffffffffffff0c6ad98892f1d411a65f0040963251e50000000000000000000000005065\n"
            "64e6881ad301feffffff00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff00000000000000000000000000000000000000000000000000000000\n"
            "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff0000000000000000000000000000000000000000000000000000\n"
            "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff000000000000000000000000000000000000000000000000\n"
            "0000000000000000000000000000000000000000000000000105000000000000}}";
    if (pathExists("README.rtf")) {
        remove("README.rtf");
        ofstream README;
        README.open("README.rtf");
        README << DATA;
        LOG_DEBUG << "README created correctly";
        README.close();
        LOG_DEBUG << "README saved correctly";
    } else {
        ofstream README;
        README.open("README.rtf");
        README << DATA;
        LOG_DEBUG << "README created correctly";
        README.close();
        LOG_DEBUG << "README saved correctly";
    }
    return;
}

void exportLICENSE(void) {
    LOG_INFO << "Creating LICENSE file ...";
    string DATA = "{\\rtf1\\adeflang1025\\ansi\\ansicpg1252\\uc1\\adeff38\\deff0\\stshfdbch31505\\stshfloch31506\\stshfhich31506\\stshfbi31507\\deflang3082\\deflangfe3082\\themelang3082\\themelangfe0\\themelangcs0{\\fonttbl{\\f0\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f0\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\f37\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0502020204030204}Calibri;}{\\f38\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0302020204030204}Calibri Light;}{\\f42\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020b0602020104020603}Tw Cen MT;}\n"
            "{\\flomajor\\f31500\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\fdbmajor\\f31501\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\fhimajor\\f31502\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0302020204030204}Calibri Light;}{\\fbimajor\\f31503\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\flominor\\f31504\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\fdbminor\\f31505\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}\n"
            "{\\fhiminor\\f31506\\fbidi \\fswiss\\fcharset0\\fprq2{\\*\\panose 020f0502020204030204}Calibri;}{\\fbiminor\\f31507\\fbidi \\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f43\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\f44\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\f46\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f47\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\f48\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\f49\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\f50\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f51\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\f43\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\f44\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\f46\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f47\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\f48\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\f49\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\f50\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f51\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\f413\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri CE;}\n"
            "{\\f414\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Cyr;}{\\f416\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Greek;}{\\f417\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Tur;}{\\f418\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri (Hebrew);}\n"
            "{\\f419\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri (Arabic);}{\\f420\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Baltic;}{\\f421\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri (Vietnamese);}{\\f423\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri Light CE;}\n"
            "{\\f424\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Light Cyr;}{\\f426\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Light Greek;}{\\f427\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Light Tur;}{\\f428\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri Light (Hebrew);}\n"
            "{\\f429\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri Light (Arabic);}{\\f430\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Light Baltic;}{\\f431\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri Light (Vietnamese);}{\\f463\\fbidi \\fswiss\\fcharset238\\fprq2 Tw Cen MT CE;}\n"
            "{\\flomajor\\f31508\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\flomajor\\f31509\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\flomajor\\f31511\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}\n"
            "{\\flomajor\\f31512\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\flomajor\\f31513\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\flomajor\\f31514\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\flomajor\\f31515\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\flomajor\\f31516\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fdbmajor\\f31518\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\fdbmajor\\f31519\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\fdbmajor\\f31521\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fdbmajor\\f31522\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
            "{\\fdbmajor\\f31523\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\fdbmajor\\f31524\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fdbmajor\\f31525\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}\n"
            "{\\fdbmajor\\f31526\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fhimajor\\f31528\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri Light CE;}{\\fhimajor\\f31529\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Light Cyr;}\n"
            "{\\fhimajor\\f31531\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Light Greek;}{\\fhimajor\\f31532\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Light Tur;}{\\fhimajor\\f31533\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri Light (Hebrew);}\n"
            "{\\fhimajor\\f31534\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri Light (Arabic);}{\\fhimajor\\f31535\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Light Baltic;}{\\fhimajor\\f31536\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri Light (Vietnamese);}\n"
            "{\\fbimajor\\f31538\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fbimajor\\f31539\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\fbimajor\\f31541\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}\n"
            "{\\fbimajor\\f31542\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fbimajor\\f31543\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\fbimajor\\f31544\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
            "{\\fbimajor\\f31545\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fbimajor\\f31546\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\flominor\\f31548\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}\n"
            "{\\flominor\\f31549\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\flominor\\f31551\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\flominor\\f31552\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
            "{\\flominor\\f31553\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\flominor\\f31554\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\flominor\\f31555\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}\n"
            "{\\flominor\\f31556\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}{\\fdbminor\\f31558\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fdbminor\\f31559\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\fdbminor\\f31561\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fdbminor\\f31562\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fdbminor\\f31563\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\fdbminor\\f31564\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fdbminor\\f31565\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fdbminor\\f31566\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}\n"
            "{\\fhiminor\\f31568\\fbidi \\fswiss\\fcharset238\\fprq2 Calibri CE;}{\\fhiminor\\f31569\\fbidi \\fswiss\\fcharset204\\fprq2 Calibri Cyr;}{\\fhiminor\\f31571\\fbidi \\fswiss\\fcharset161\\fprq2 Calibri Greek;}{\\fhiminor\\f31572\\fbidi \\fswiss\\fcharset162\\fprq2 Calibri Tur;}\n"
            "{\\fhiminor\\f31573\\fbidi \\fswiss\\fcharset177\\fprq2 Calibri (Hebrew);}{\\fhiminor\\f31574\\fbidi \\fswiss\\fcharset178\\fprq2 Calibri (Arabic);}{\\fhiminor\\f31575\\fbidi \\fswiss\\fcharset186\\fprq2 Calibri Baltic;}\n"
            "{\\fhiminor\\f31576\\fbidi \\fswiss\\fcharset163\\fprq2 Calibri (Vietnamese);}{\\fbiminor\\f31578\\fbidi \\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\fbiminor\\f31579\\fbidi \\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
            "{\\fbiminor\\f31581\\fbidi \\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\fbiminor\\f31582\\fbidi \\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\fbiminor\\f31583\\fbidi \\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}\n"
            "{\\fbiminor\\f31584\\fbidi \\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\fbiminor\\f31585\\fbidi \\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\fbiminor\\f31586\\fbidi \\froman\\fcharset163\\fprq2 Times New Roman (Vietnamese);}}\n"
            "{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\\red0\\green0\\blue128;\\red0\\green128\\blue128;\\red0\\green128\\blue0;\n"
            "\\red128\\green0\\blue128;\\red128\\green0\\blue0;\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;\\caccentone\\ctint255\\cshade191\\red47\\green84\\blue150;\\red5\\green99\\blue193;}{\\*\\defchp \\fs22\\loch\\af31506\\hich\\af31506\\dbch\\af31505 }\n"
            "{\\*\\defpap \\ql \\li0\\ri0\\sa160\\sl259\\slmult1\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 }\\noqfpromote {\\stylesheet{\\ql \\li0\\ri0\\nowidctlpar\\wrapdefault\\faauto\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af38\\afs24\\alang1025 \\ltrch\\fcs0 \n"
            "\\fs24\\lang3082\\langfe3082\\loch\\f38\\hich\\af38\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 \\snext0 \\sqformat \\spriority0 Normal;}{\\s1\\ql \\li0\\ri0\\nowidctlpar\\wrapdefault\\faauto\\outlinelevel0\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af38\\afs24\\alang1025 \\ltrch\\fcs0 \n"
            "\\fs24\\lang3082\\langfe3082\\loch\\f38\\hich\\af38\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 \\sbasedon0 \\snext0 \\slink15 \\sqformat heading 1;}{\\*\\cs10 \\additive \\ssemihidden \\sunhideused \\spriority1 Default Paragraph Font;}{\\*\n"
            "\\ts11\\tsrowd\\trftsWidthB3\\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddft3\\trpaddfb3\\trpaddfr3\\trcbpat1\\trcfpat1\\tblind0\\tblindtype3\\tsvertalt\\tsbrdrt\\tsbrdrl\\tsbrdrb\\tsbrdrr\\tsbrdrdgl\\tsbrdrdgr\\tsbrdrh\\tsbrdrv \\ql \\li0\\ri0\\sa160\\sl259\\slmult1\n"
            "\\widctlpar\\wrapdefault\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af31507\\afs22\\alang1025 \\ltrch\\fcs0 \\fs22\\lang3082\\langfe3082\\loch\\f31506\\hich\\af31506\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 \\snext11 \\ssemihidden \\sunhideused \n"
            "Normal Table;}{\\*\\cs15 \\additive \\rtlch\\fcs1 \\af31503\\afs32 \\ltrch\\fcs0 \\fs32\\cf17\\loch\\f31502\\hich\\af31502\\dbch\\af31501 \\sbasedon10 \\slink1 \\slocked \\spriority9 T\\'edtulo 1 Car;}}{\\*\\rsidtbl \\rsid6308252\\rsid11809163}{\\mmathPr\\mmathFont34\\mbrkBin0\n"
            "\\mbrkBinSub0\\msmallFrac0\\mdispDef1\\mlMargin0\\mrMargin0\\mdefJc1\\mwrapIndent1440\\mintLim0\\mnaryLim0}{\\info{\\operator Javier Alonso Silva}{\\creatim\\yr2017\\mo8\\dy21\\hr16\\min33}{\\revtim\\yr2017\\mo8\\dy21\\hr16\\min33}{\\version2}{\\edmins0}{\\nofpages1}{\\nofwords207}\n"
            "{\\nofchars1140}{\\nofcharsws1345}{\\vern39}{\\*\\saveprevpict}\n"
            "{\\*\\passwordhash 0200000078000000180000000e800000a086010040000000100000002800000068000000000000002d9d7ec2a38ad3f3c80d635815afc24abf960ffa9eb3518dc982455690d407bc844562140c5eb9256441653e23bff2fbad5a2bc314ad08b60c487625420d09bdd6f1ef86e617d4a780faf1a95591c30d\n"
            "}}{\\*\\userprops {\\propname _MarkAsFinal}\\proptype11{\\staticval 1}}{\\*\\xmlnstbl {\\xmlns1 http://schemas.microsoft.com/office/word/2003/wordml}}\\paperw12240\\paperh15840\\margl1701\\margr1701\\margt1417\\margb1417\\gutter0\\ltrsect \n"
            "\\widowctrl\\ftnbj\\aenddoc\\hyphhotz425\\trackmoves0\\trackformatting1\\donotembedsysfont0\\relyonvml0\\donotembedlingdata1\\grfdocevents0\\validatexml0\\showplaceholdtext0\\ignoremixedcontent0\\saveinvalidxml0\\showxmlerrors0\\annotprot\\readprot\\horzdoc\\dghspace120\n"
            "\\dgvspace120\\dghorigin1701\\dgvorigin1984\\dghshow0\\dgvshow3\\jcompress\\viewkind1\\viewscale100\\rsidroot11809163 \\nouicompat \\fet0{\\*\\wgrffmtfilter 2450}\\nofeaturethrottle1\\ilfomacatclnup0\\enforceprot1\\protlevel3\\ltrpar \\sectd \\ltrsect\n"
            "\\linex0\\sectdefaultcl\\sftnbj {\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl2\\pnucltr\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang {\\pntxta .}}{\\*\\pnseclvl4\n"
            "\\pnlcltr\\pnstart1\\pnindent720\\pnhang {\\pntxta )}}{\\*\\pnseclvl5\\pndec\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6\\pnlcltr\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}\n"
            "{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang {\\pntxtb (}{\\pntxta )}}\\pard\\plain \\ltrpar\\s1\\qc \\li0\\ri0\\sb240\\sa60\\sl252\\slmult1\n"
            "\\keepn\\widctlpar\\wrapdefault\\faauto\\outlinelevel0\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af38\\afs24\\alang1025 \\ltrch\\fcs0 \\fs24\\lang3082\\langfe3082\\loch\\af38\\hich\\af38\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 {\\rtlch\\fcs1 \\ab\\af38\\afs32 \\ltrch\\fcs0 \n"
            "\\b\\fs32\\lang1033\\langfe3082\\kerning32\\langnp1033\\insrsid6308252 \\hich\\af38\\dbch\\af31505\\loch\\f38 MIT License\n"
            "\\par }\\pard\\plain \\ltrpar\\qc \\li0\\ri0\\sa160\\sl252\\slmult1\\widctlpar\\wrapdefault\\faauto\\rin0\\lin0\\itap0 \\rtlch\\fcs1 \\af38\\afs24\\alang1025 \\ltrch\\fcs0 \\fs24\\lang3082\\langfe3082\\loch\\af38\\hich\\af38\\dbch\\af31505\\cgrid\\langnp3082\\langfenp3082 {\\rtlch\\fcs1 \n"
            "\\af37\\afs22 \\ltrch\\fcs0 \\f37\\fs22\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \n"
            "\\par }{\\rtlch\\fcs1 \\ab\\af42\\afs28 \\ltrch\\fcs0 \\b\\f42\\fs28\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 \\hich\\f42 Copyright \\'a9\\loch\\f42  2017 - Javinator9889\n"
            "\\par }{\\field\\fldedit{\\*\\fldinst {\\rtlch\\fcs1 \\ai\\af42\\afs28 \\ltrch\\fcs0 \\i\\f42\\fs28\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 HYPERLINK \"https://goo.gl/F5PV35\" }{\\rtlch\\fcs1 \\ai\\af42\\afs28 \\ltrch\\fcs0 \n"
            "\\i\\f42\\fs28\\lang1033\\langfe3082\\langnp1033\\insrsid11809163 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90b44000000680074007400700073003a002f002f0067006f006f002e0067006c002f004600350050005600330035000000795881f43b1d7f48af2c825dc485276300000000a5ab0003}}}{\\fldrslt {\\rtlch\\fcs1 \n"
            "\\ai\\af42\\afs28 \\ltrch\\fcs0 \\i\\f42\\fs28\\ul\\cf18\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 Windows Repai\\hich\\af42\\dbch\\af31505\\loch\\f42 r Tool}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\ai\\af42\\afs28 \n"
            "\\ltrch\\fcs0 \\i\\f42\\fs28\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42  \\hich\\f42 \\endash \\loch\\f42  Simple tool for fixing common Windows problems}{\\rtlch\\fcs1 \\af42\\afs28 \\ltrch\\fcs0 \n"
            "\\f42\\fs28\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \n"
            "\\par }{\\rtlch\\fcs1 \\af42\\afs22 \\ltrch\\fcs0 \\f42\\fs22\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \n"
            "\\par }{\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 Permission is hereby granted, free of charge, to any person obtaining a copy\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 of this software and associated documentation files (the \"Software\"), to deal\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 in the Software without restriction, including without limitation the rights\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 copies of the Software, and\\hich\\af42\\dbch\\af31505\\loch\\f42  to permit persons to whom the Software is\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 furnished to do so, subject to the following conditions:\n"
            "\\par \n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 The above copyright notice and this permission notice shall be included in all\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 copies or substantial portions of the Software.\n"
            "\\par \n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 THE SOFTWARE IS PROVIDED \"A\\hich\\af42\\dbch\\af31505\\loch\\f42 S IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAG\\hich\\af42\\dbch\\af31505\\loch\\f42 ES OR OTHER\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
            "\\par \\hich\\af42\\dbch\\af31505\\loch\\f42 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
            "\\par }{\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6308252\\charrsid11809163 \\hich\\af42\\dbch\\af31505\\loch\\f42 SOFTWARE.\n"
            "\\par \n"
            "\\par }\\pard \\ltrpar\\ql \\li0\\ri0\\sa160\\sl252\\slmult1\\widctlpar\\wrapdefault\\faauto\\rin0\\lin0\\itap0 {\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "In case of need, here you have my contact email: }{\\field{\\*\\fldinst {\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 HYPERLINK \"mailto:javinator9\\hich\\af42\\dbch\\af31505\\loch\\f42 \n"
            "889@outlook.com?subject=QUESTION%20ABOUT%20WindowsRepairTool\" }{\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid11809163 {\\*\\datafield \n"
            "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000e0c9ea79f9bace118c8200aa004ba90bb40000006d00610069006c0074006f003a006a006100760069006e00610074006f007200390038003800390040006f00750074006c006f006f006b002e0063006f006d003f007300750062006a006500630074003d00\n"
            "5100550045005300540049004f004e00250032003000410042004f0055005400250032003000570069006e0064006f007700730052006500700061006900720054006f006f006c000000795881f43b1d7f48af2c825dc485276300000000a5ab0003}}}{\\fldrslt {\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \n"
            "\\f42\\ul\\cf18\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \\hich\\af42\\dbch\\af31505\\loch\\f42 javinator9889@outlook.com}}}\\sectd \\ltrsect\\linex0\\sectdefaultcl\\sftnbj {\\rtlch\\fcs1 \\af42 \\ltrch\\fcs0 \\f42\\lang1033\\langfe3082\\langnp1033\\insrsid6308252 \n"
            "\\par }{\\*\\themedata 504b030414000600080000002100e9de0fbfff0000001c020000130000005b436f6e74656e745f54797065735d2e786d6cac91cb4ec3301045f748fc83e52d4a\n"
            "9cb2400825e982c78ec7a27cc0c8992416c9d8b2a755fbf74cd25442a820166c2cd933f79e3be372bd1f07b5c3989ca74aaff2422b24eb1b475da5df374fd9ad\n"
            "5689811a183c61a50f98f4babebc2837878049899a52a57be670674cb23d8e90721f90a4d2fa3802cb35762680fd800ecd7551dc18eb899138e3c943d7e503b6\n"
            "b01d583deee5f99824e290b4ba3f364eac4a430883b3c092d4eca8f946c916422ecab927f52ea42b89a1cd59c254f919b0e85e6535d135a8de20f20b8c12c3b0\n"
            "0c895fcf6720192de6bf3b9e89ecdbd6596cbcdd8eb28e7c365ecc4ec1ff1460f53fe813d3cc7f5b7f020000ffff0300504b030414000600080000002100a5d6\n"
            "a7e7c0000000360100000b0000005f72656c732f2e72656c73848fcf6ac3300c87ef85bd83d17d51d2c31825762fa590432fa37d00e1287f68221bdb1bebdb4f\n"
            "c7060abb0884a4eff7a93dfeae8bf9e194e720169aaa06c3e2433fcb68e1763dbf7f82c985a4a725085b787086a37bdbb55fbc50d1a33ccd311ba548b6309512\n"
            "0f88d94fbc52ae4264d1c910d24a45db3462247fa791715fd71f989e19e0364cd3f51652d73760ae8fa8c9ffb3c330cc9e4fc17faf2ce545046e37944c69e462\n"
            "a1a82fe353bd90a865aad41ed0b5b8f9d6fd010000ffff0300504b0304140006000800000021006b799616830000008a0000001c0000007468656d652f746865\n"
            "6d652f7468656d654d616e616765722e786d6c0ccc4d0ac3201040e17da17790d93763bb284562b2cbaebbf600439c1a41c7a0d29fdbd7e5e38337cedf14d59b\n"
            "4b0d592c9c070d8a65cd2e88b7f07c2ca71ba8da481cc52c6ce1c715e6e97818c9b48d13df49c873517d23d59085adb5dd20d6b52bd521ef2cdd5eb9246a3d8b\n"
            "4757e8d3f729e245eb2b260a0238fd010000ffff0300504b030414000600080000002100a7259ef29c070000cb200000160000007468656d652f7468656d652f\n"
            "7468656d65312e786d6cec59cd8b1bc915bf07f23f347d97f5d5ad8fc1f2a24fcfda33b6b164873dd648a5eef2547789aad28cc56208de532e81c026e49085bd\n"
            "ed21842cecc22eb9e48f31d8249b3f22afaa5bdd5552c99e191c3061463074977eefd5afde7bf5de53d5ddcf5e26d4bbc05c1096f6fcfa9d9aefe174ce16248d\n"
            "7afeb3d9a4d2f13d2151ba4094a5b8e76fb0f03fbbf7eb5fdd454732c609f6403e1547a8e7c752ae8eaa5531876124eeb0154ee1bb25e30992f0caa3ea82a34b\n"
            "d09bd06aa3566b55134452df4b51026a6720e32db0f778b92473ecdfdbaa1f53982395420dcc299f2ae5389731b08bf3ba42888d1852ee5d20daf361a605bb9c\n"
            "e197d2f7281212bee8f935fde757efddada2a35c88ca03b286dc44ffe572b9c0e2bca1e7e4d1593169108441ab5fe8d7002af771e3f6b8356e15fa3400cde7b0\n"
            "d28c8badb3dd180639d600658f0edda3f6a859b7f086fee61ee77ea83e165e8332fdc11e7e321982152dbc0665f8700f1f0eba8391ad5f83327c6b0fdfaef547\n"
            "41dbd2af413125e9f91eba16b69ac3ed6a0bc892d16327bc1b06937623575ea2201a8ae852532c592a0fc55a825e303e018002522449eac9cd0a2fd11ce27888\n"
            "2839e3c43b21510c81b7422913305c6bd426b526fc579f403f698fa2238c0c69c50b9888bd21c5c713734e56b2e73f00adbe0179fbf3cf6f5efff8e6f54f6fbe\n"
            "faeacdebbfe7736b5596dc314a2353ee97effef09f6f7eebfdfb876f7ff9fa8fd9d4bb7861e2dffded77effef1cff7a9871597a678fba7efdffdf8fddb3ffffe\n"
            "5f7ffddaa1bdcfd199099f91040bef11bef49eb20416e8e08fcff8f524663122a6443f8d044a919ac5a17f2c630bfd68832872e006d8b6e3730ea9c605bcbf7e\n"
            "61119ec67c2d8943e3c338b180a78cd101e34e2b3c547319669eadd3c83d395f9bb8a7085db8e61ea2d4f2f278bd821c4b5c2a8731b6683ea1289528c229969e\n"
            "fa8e9d63ec58dd178458763d2573ce045b4aef0be20d10719a6446ceac682a858e49027ed9b80882bf2ddb9c3ef7068cba563dc2173612f606a20ef2334c2d33\n"
            "de476b891297ca194aa869f013246317c9e986cf4ddc5848f0748429f3c60b2c844be63187f51a4e7f0869c6edf653ba496c2497e4dca5f30431662247ec7c18\n"
            "a364e5c24e491a9bd8cfc5398428f29e30e9829f327b87a877f0034a0fbafb39c196bb3f9c0d9e418635299501a2be5973872fef6366c5ef74439708bb524d9f\n"
            "27568aed73e28c8ec13ab242fb04638a2ed10263efd9e70e0603b6b26c5e927e10435639c6aec07a80ec5855ef2916d8d3cdcd7e9e3c21c20ad9298ed8013ea7\n"
            "9b9dc4b3416982f821cd8fc0eba6cdc750ea1257003ca6f37313f888401708f1e234ca63013a8ce03ea8f5498cac02a6de853b5e37dcf2df55f618eccb17168d\n"
            "2bec4b90c1d79681c46ecabcd7363344ad09ca809921e8325ce916442cf79722aab86ab1b5536e696fdad20dd01d594d4f42d20f76403bbd4ff8bfeb7da0c378\n"
            "fb976f1c9bede3f43b6ec556b2ba66a77328991ceff4378770bb5dcd90f105f9f49b9a115aa74f30d491fd8c75dbd3dcf634feff7d4f73683fdf763287fa8ddb\n"
            "4ec6870ee3b693c90f573e4e2753362fd0d7a8038feca0471ffb24074f7d9684d2a9dc507c22f4c18f80df338b090c2a397de6898b53c0550c8faaccc104162e\n"
            "e248cb789cc9df10194f63b482d3a1baaf944422571d096fc5041c1ae961a76e85a7ebe4942db2c3ce7a5d1d6c66955520598ed7c2621c0eaa64866eb5cb03bc\n"
            "42bd661be983d62d01257b1d12c6643689a683447b3ba88ca48f75c1680e127a651f8545d7c1a2a3d46f5db5c702a8155e811fdc1efc4ceff96100222004e771\n"
            "d09c2f949f32576fbdab9df9313d7dc89856044083bd8d80d2d35dc5f5e0f2d4eab250bb82a72d1246b8d924b46574832762f8199c47a71abd0a8debfaba5bba\n"
            "d4a2a74ca1e783d02a69b43bef6371535f83dc6e6ea0a9992968ea5df6fc5633849099a355cf5fc2a1313c262b881da17e73211ac1ddcb5cf26cc3df24b3acb8\n"
            "902324e2cce03ae964d9202112738f92a4e7abe5176ea0a9ce219a5bbd0109e19325d785b4f2a99103a7db4ec6cb259e4bd3edc688b274f60a193ecb15ce6fb5\n"
            "f8cdc14a92adc1ddd37871e99dd1357f8a20c4c2765d19704104dc1dd4336b2e085c861589ac8cbf9dc294a75df3364ac750368ee82a46794531937906d7a9bc\n"
            "a0a3df0a1b186ff99ac1a08649f2427816a9026b1ad5aaa645d5c8381cacba1f1652963392665933adaca2aaa63b8b59336ccbc08e2d6f56e40d565b13434e33\n"
            "2b7c96ba77536e779beb76fa84a24a80c10bfb39aaee150a8241ad9ccca2a618efa76195b3f351bb766c17f8016a57291246d66f6dd5eed8ada811cee960f046\n"
            "951fe476a3168696dbbe525b5adf9b9b17dbecec05248f1174b96b2a8576255c5b73040dd154f72459da802df252e65b039ebc35273dffcb5ad80f868d7058a9\n"
            "75c271256806b54a27ec372bfd306cd6c761bd361a345e41619171520fb33bfb095c60d04d7e73afc7f76eef93ed1dcd9d394baa4cdfca5735717d7b5f6f58b7\n"
            "f7d94dbc375397f3be4720e97cd96a4cbacdeea055e936fb934a301a742add616b5019b586edd164340c3bddc92bdfbbd0e0a0df1c06ad71a7d2aa0f8795a055\n"
            "53f43bdd4a3b6834fa41bbdf1907fd57791b032bcfd2476e0b30afe675efbf000000ffff0300504b0304140006000800000021000dd1909fb60000001b010000\n"
            "270000007468656d652f7468656d652f5f72656c732f7468656d654d616e616765722e786d6c2e72656c73848f4d0ac2301484f78277086f6fd3ba109126dd88\n"
            "d0add40384e4350d363f2451eced0dae2c082e8761be9969bb979dc9136332de3168aa1a083ae995719ac16db8ec8e4052164e89d93b64b060828e6f37ed1567\n"
            "914b284d262452282e3198720e274a939cd08a54f980ae38a38f56e422a3a641c8bbd048f7757da0f19b017cc524bd62107bd5001996509affb3fd381a89672f\n"
            "1f165dfe514173d9850528a2c6cce0239baa4c04ca5bbabac4df000000ffff0300504b01022d0014000600080000002100e9de0fbfff0000001c020000130000\n"
            "0000000000000000000000000000005b436f6e74656e745f54797065735d2e786d6c504b01022d0014000600080000002100a5d6a7e7c0000000360100000b00\n"
            "000000000000000000000000300100005f72656c732f2e72656c73504b01022d00140006000800000021006b799616830000008a0000001c0000000000000000\n"
            "0000000000190200007468656d652f7468656d652f7468656d654d616e616765722e786d6c504b01022d0014000600080000002100a7259ef29c070000cb2000\n"
            "001600000000000000000000000000d60200007468656d652f7468656d652f7468656d65312e786d6c504b01022d00140006000800000021000dd1909fb60000\n"
            "001b0100002700000000000000000000000000a60a00007468656d652f7468656d652f5f72656c732f7468656d654d616e616765722e786d6c2e72656c73504b050600000000050005005d010000a10b00000000}\n"
            "{\\*\\colorschememapping 3c3f786d6c2076657273696f6e3d22312e302220656e636f64696e673d225554462d3822207374616e64616c6f6e653d22796573223f3e0d0a3c613a636c724d\n"
            "617020786d6c6e733a613d22687474703a2f2f736368656d61732e6f70656e786d6c666f726d6174732e6f72672f64726177696e676d6c2f323030362f6d6169\n"
            "6e22206267313d226c743122207478313d22646b3122206267323d226c743222207478323d22646b322220616363656e74313d22616363656e74312220616363\n"
            "656e74323d22616363656e74322220616363656e74333d22616363656e74332220616363656e74343d22616363656e74342220616363656e74353d22616363656e74352220616363656e74363d22616363656e74362220686c696e6b3d22686c696e6b2220666f6c486c696e6b3d22666f6c486c696e6b222f3e}\n"
            "{\\*\\latentstyles\\lsdstimax375\\lsdlockeddef0\\lsdsemihiddendef0\\lsdunhideuseddef0\\lsdqformatdef0\\lsdprioritydef99{\\lsdlockedexcept \\lsdqformat1 \\lsdpriority0 \\lsdlocked0 Normal;\\lsdqformat1 \\lsdlocked0 heading 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 4;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 7;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority9 \\lsdlocked0 heading 9;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 5;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index 9;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 6;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority39 \\lsdlocked0 toc 9;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Normal Indent;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footnote text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 header;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footer;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 index heading;\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority35 \\lsdlocked0 caption;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 table of figures;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 envelope address;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 envelope return;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 footnote reference;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation reference;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 line number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 page number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 endnote reference;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 endnote text;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 table of authorities;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 macro;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 toa heading;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Bullet 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Number 5;\\lsdqformat1 \\lsdpriority10 \\lsdlocked0 Title;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Closing;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Signature;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority1 \\lsdlocked0 Default Paragraph Font;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 4;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 List Continue 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Message Header;\\lsdqformat1 \\lsdpriority11 \\lsdlocked0 Subtitle;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Salutation;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Date;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text First Indent;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text First Indent 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Note Heading;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Body Text Indent 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Block Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Hyperlink;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 FollowedHyperlink;\\lsdqformat1 \\lsdpriority22 \\lsdlocked0 Strong;\n"
            "\\lsdqformat1 \\lsdpriority20 \\lsdlocked0 Emphasis;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Document Map;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Plain Text;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 E-mail Signature;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Top of Form;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Bottom of Form;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Normal (Web);\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Acronym;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Address;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Cite;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Code;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Definition;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Keyboard;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Preformatted;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Sample;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Typewriter;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 HTML Variable;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Normal Table;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 annotation subject;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 No List;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Outline List 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Simple 1;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Simple 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Simple 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Classic 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Classic 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Classic 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Classic 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Colorful 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Colorful 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Colorful 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Columns 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Columns 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Columns 3;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Columns 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Columns 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 6;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Grid 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 4;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 5;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 6;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 7;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table List 8;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table 3D effects 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table 3D effects 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table 3D effects 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Contemporary;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Elegant;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Professional;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Subtle 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Subtle 2;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Web 1;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Web 2;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Web 3;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Balloon Text;\\lsdpriority39 \\lsdlocked0 Table Grid;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Table Theme;\\lsdsemihidden1 \\lsdlocked0 Placeholder Text;\n"
            "\\lsdqformat1 \\lsdpriority1 \\lsdlocked0 No Spacing;\\lsdpriority60 \\lsdlocked0 Light Shading;\\lsdpriority61 \\lsdlocked0 Light List;\\lsdpriority62 \\lsdlocked0 Light Grid;\\lsdpriority63 \\lsdlocked0 Medium Shading 1;\\lsdpriority64 \\lsdlocked0 Medium Shading 2;\n"
            "\\lsdpriority65 \\lsdlocked0 Medium List 1;\\lsdpriority66 \\lsdlocked0 Medium List 2;\\lsdpriority67 \\lsdlocked0 Medium Grid 1;\\lsdpriority68 \\lsdlocked0 Medium Grid 2;\\lsdpriority69 \\lsdlocked0 Medium Grid 3;\\lsdpriority70 \\lsdlocked0 Dark List;\n"
            "\\lsdpriority71 \\lsdlocked0 Colorful Shading;\\lsdpriority72 \\lsdlocked0 Colorful List;\\lsdpriority73 \\lsdlocked0 Colorful Grid;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 1;\\lsdpriority61 \\lsdlocked0 Light List Accent 1;\n"
            "\\lsdpriority62 \\lsdlocked0 Light Grid Accent 1;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 1;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 1;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 1;\\lsdsemihidden1 \\lsdlocked0 Revision;\n"
            "\\lsdqformat1 \\lsdpriority34 \\lsdlocked0 List Paragraph;\\lsdqformat1 \\lsdpriority29 \\lsdlocked0 Quote;\\lsdqformat1 \\lsdpriority30 \\lsdlocked0 Intense Quote;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 1;\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 1;\n"
            "\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 1;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 1;\\lsdpriority70 \\lsdlocked0 Dark List Accent 1;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 1;\\lsdpriority72 \\lsdlocked0 Colorful List Accent 1;\n"
            "\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 1;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 2;\\lsdpriority61 \\lsdlocked0 Light List Accent 2;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 2;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 2;\n"
            "\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 2;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 2;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 2;\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 2;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 2;\n"
            "\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 2;\\lsdpriority70 \\lsdlocked0 Dark List Accent 2;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 2;\\lsdpriority72 \\lsdlocked0 Colorful List Accent 2;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 2;\n"
            "\\lsdpriority60 \\lsdlocked0 Light Shading Accent 3;\\lsdpriority61 \\lsdlocked0 Light List Accent 3;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 3;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 3;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 3;\n"
            "\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 3;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 3;\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 3;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 3;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 3;\n"
            "\\lsdpriority70 \\lsdlocked0 Dark List Accent 3;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 3;\\lsdpriority72 \\lsdlocked0 Colorful List Accent 3;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 3;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 4;\n"
            "\\lsdpriority61 \\lsdlocked0 Light List Accent 4;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 4;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 4;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 4;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 4;\n"
            "\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 4;\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 4;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 4;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 4;\\lsdpriority70 \\lsdlocked0 Dark List Accent 4;\n"
            "\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 4;\\lsdpriority72 \\lsdlocked0 Colorful List Accent 4;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 4;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 5;\\lsdpriority61 \\lsdlocked0 Light List Accent 5;\n"
            "\\lsdpriority62 \\lsdlocked0 Light Grid Accent 5;\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 5;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 5;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 5;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 5;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 5;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 5;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 5;\\lsdpriority70 \\lsdlocked0 Dark List Accent 5;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 5;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 5;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 5;\\lsdpriority60 \\lsdlocked0 Light Shading Accent 6;\\lsdpriority61 \\lsdlocked0 Light List Accent 6;\\lsdpriority62 \\lsdlocked0 Light Grid Accent 6;\n"
            "\\lsdpriority63 \\lsdlocked0 Medium Shading 1 Accent 6;\\lsdpriority64 \\lsdlocked0 Medium Shading 2 Accent 6;\\lsdpriority65 \\lsdlocked0 Medium List 1 Accent 6;\\lsdpriority66 \\lsdlocked0 Medium List 2 Accent 6;\n"
            "\\lsdpriority67 \\lsdlocked0 Medium Grid 1 Accent 6;\\lsdpriority68 \\lsdlocked0 Medium Grid 2 Accent 6;\\lsdpriority69 \\lsdlocked0 Medium Grid 3 Accent 6;\\lsdpriority70 \\lsdlocked0 Dark List Accent 6;\\lsdpriority71 \\lsdlocked0 Colorful Shading Accent 6;\n"
            "\\lsdpriority72 \\lsdlocked0 Colorful List Accent 6;\\lsdpriority73 \\lsdlocked0 Colorful Grid Accent 6;\\lsdqformat1 \\lsdpriority19 \\lsdlocked0 Subtle Emphasis;\\lsdqformat1 \\lsdpriority21 \\lsdlocked0 Intense Emphasis;\n"
            "\\lsdqformat1 \\lsdpriority31 \\lsdlocked0 Subtle Reference;\\lsdqformat1 \\lsdpriority32 \\lsdlocked0 Intense Reference;\\lsdqformat1 \\lsdpriority33 \\lsdlocked0 Book Title;\\lsdsemihidden1 \\lsdunhideused1 \\lsdpriority37 \\lsdlocked0 Bibliography;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdqformat1 \\lsdpriority39 \\lsdlocked0 TOC Heading;\\lsdpriority41 \\lsdlocked0 Plain Table 1;\\lsdpriority42 \\lsdlocked0 Plain Table 2;\\lsdpriority43 \\lsdlocked0 Plain Table 3;\\lsdpriority44 \\lsdlocked0 Plain Table 4;\n"
            "\\lsdpriority45 \\lsdlocked0 Plain Table 5;\\lsdpriority40 \\lsdlocked0 Grid Table Light;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light;\\lsdpriority47 \\lsdlocked0 Grid Table 2;\\lsdpriority48 \\lsdlocked0 Grid Table 3;\\lsdpriority49 \\lsdlocked0 Grid Table 4;\n"
            "\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 1;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 1;\n"
            "\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 1;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 1;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 1;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 1;\n"
            "\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 1;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 2;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 2;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 2;\n"
            "\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 2;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 2;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 2;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 2;\n"
            "\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 3;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 3;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 3;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 3;\n"
            "\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 3;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 3;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 3;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 4;\n"
            "\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 4;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 4;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 4;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 4;\n"
            "\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 4;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 4;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 5;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 5;\n"
            "\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 5;\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 5;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 5;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 5;\n"
            "\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 5;\\lsdpriority46 \\lsdlocked0 Grid Table 1 Light Accent 6;\\lsdpriority47 \\lsdlocked0 Grid Table 2 Accent 6;\\lsdpriority48 \\lsdlocked0 Grid Table 3 Accent 6;\n"
            "\\lsdpriority49 \\lsdlocked0 Grid Table 4 Accent 6;\\lsdpriority50 \\lsdlocked0 Grid Table 5 Dark Accent 6;\\lsdpriority51 \\lsdlocked0 Grid Table 6 Colorful Accent 6;\\lsdpriority52 \\lsdlocked0 Grid Table 7 Colorful Accent 6;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light;\\lsdpriority47 \\lsdlocked0 List Table 2;\\lsdpriority48 \\lsdlocked0 List Table 3;\\lsdpriority49 \\lsdlocked0 List Table 4;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark;\n"
            "\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 1;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 1;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 1;\n"
            "\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 1;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 1;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 1;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 1;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 2;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 2;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 2;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 2;\n"
            "\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 2;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 2;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 2;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 3;\n"
            "\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 3;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 3;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 3;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 3;\n"
            "\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 3;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 3;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 4;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 4;\n"
            "\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 4;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 4;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 4;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 4;\n"
            "\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 4;\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 5;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 5;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 5;\n"
            "\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 5;\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 5;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 5;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 5;\n"
            "\\lsdpriority46 \\lsdlocked0 List Table 1 Light Accent 6;\\lsdpriority47 \\lsdlocked0 List Table 2 Accent 6;\\lsdpriority48 \\lsdlocked0 List Table 3 Accent 6;\\lsdpriority49 \\lsdlocked0 List Table 4 Accent 6;\n"
            "\\lsdpriority50 \\lsdlocked0 List Table 5 Dark Accent 6;\\lsdpriority51 \\lsdlocked0 List Table 6 Colorful Accent 6;\\lsdpriority52 \\lsdlocked0 List Table 7 Colorful Accent 6;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Mention;\n"
            "\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Smart Hyperlink;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Hashtag;\\lsdsemihidden1 \\lsdunhideused1 \\lsdlocked0 Unresolved Mention;}}{\\*\\datastore 010500000200000018000000\n"
            "4d73786d6c322e534158584d4c5265616465722e362e3000000000000000000000060000\n"
            "d0cf11e0a1b11ae1000000000000000000000000000000003e000300feff090006000000000000000000000001000000010000000000000000100000feffffff00000000feffffff0000000000000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "fffffffffffffffffdfffffffeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n"
            "ffffffffffffffffffffffffffffffff52006f006f007400200045006e00740072007900000000000000000000000000000000000000000000000000000000000000000000000000000000000000000016000500ffffffffffffffffffffffff0c6ad98892f1d411a65f0040963251e50000000000000000000000008090\n"
            "c2808a1ad301feffffff00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff00000000000000000000000000000000000000000000000000000000\n"
            "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff0000000000000000000000000000000000000000000000000000\n"
            "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffffffffffffffffffff000000000000000000000000000000000000000000000000\n"
            "0000000000000000000000000000000000000000000000000105000000000000}}";
    if (pathExists("LICENSE.rtf")) {
        remove("LICENSE.rtf");
        ofstream README;
        README.open("LICENSE.rtf");
        README << DATA;
        LOG_DEBUG << "LICENSE created correctly";
        README.close();
        LOG_DEBUG << "LICENSE saved correctly";
    } else {
        ofstream README;
        README.open("LICENSE.rtf");
        README << DATA;
        LOG_DEBUG << "LICENSE created correctly";
        README.close();
        LOG_DEBUG << "LICENSE saved correctly";
    }
    return;
}

BOOL IsWow64(void) {
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
            GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

bool CheckUpdate(string version) {
    string json;
    bool IsUp = false;
    if (query_release_information(json) != ERROR_SUCCESS) {
        LOG_ERROR << "ERROR_SUCCESS - GETTING UPDATES";
        IsUp = false;
    }
    json::Document doc;
    if (doc.Parse(json.c_str()).HasParseError()) {
        IsUp = false;
        LOG_ERROR << "HasParseError - GETTING UPDATES";
    }

    try {
        const auto& release = get_index(doc, 0);
        const auto& tag_name = get_member(release, "tag_name");
        if (tag_name.GetString() != version)
            IsUp = true;
    } catch (const JSONMemberNotFound&) {
        LOG_FATAL << "Not found - GETTING UPDATES";
        IsUp = false;
    }
    return IsUp;
}