//
// Created by Javier Alonso Silva on 19/08/2017.
//
#include <windows.h>
#include <string>
#include <iostream>

#ifndef REPAIR_TOOL_CMDTOOLS_H
#define REPAIR_TOOL_CMDTOOLS_H

void DISM(bool quiet) {
    if (quiet)
        system("cmd /c DISM.exe /Online /Cleanup-Image /RestoreHealth > nul");
    else
        system("cmd /c DISM.exe /Online /Cleanup-Image /RestoreHealth");
    return;
}

void SFC(bool quiet) {
    if (quiet)
        system("cmd /c sfc.exe /scannow > nul");
    else
        system("cmd /c sfc.exe /scannow");
    return;
}

void RESTOREPOINT(void) {
    system("Wmic.exe /Namespace:\\\\root\\default Path SystemRestore Call CreateRestorePoint \"AUTO -- WinRepairTool\", 100, 12 > nul");
    return;
}

inline bool pathExists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

#endif //REPAIR_TOOL_CMDTOOLS_H
