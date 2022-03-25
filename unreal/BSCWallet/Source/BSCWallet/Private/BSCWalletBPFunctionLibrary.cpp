/*
MIT License

Copyright(c) 2022 Rafael Traista <traista.rafael@yahoo.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "BSCWalletBPFunctionLibrary.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

FString UBSCWalletBPFunctionLibrary::ExecuteSystemCommand(const char* command) {
	//char* charCommand = TCHAR_TO_ANSI(*command); // Convert FString to char*
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command, "r"), _pclose);
	if (!pipe) {
		return FString("UBSCWalletBPFunctionLibrary::ExecuteSystemCommand error: popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return FString(result.c_str()); // Convert std::string to FString
}

FString UBSCWalletBPFunctionLibrary::QueryBalance(FString walletAdress, FString tokenAddress)
{
	UE_LOG(LogTemp, Display, TEXT("QueryBalance: %s  %s"), *walletAdress, *tokenAddress);

	FString pythonScriptPath = FPaths::ProjectContentDir();
	pythonScriptPath += "/../../../scripts/querybalance.py";

	FString command = FString::Printf(TEXT("python %s -wallet %s -token %s"), 
		*pythonScriptPath,
		*walletAdress,
		*tokenAddress
	);

	UE_LOG(LogTemp, Display, TEXT("Commmand: %s"), *command);
	return UBSCWalletBPFunctionLibrary::ExecuteSystemCommand(TCHAR_TO_ANSI(*command));
}