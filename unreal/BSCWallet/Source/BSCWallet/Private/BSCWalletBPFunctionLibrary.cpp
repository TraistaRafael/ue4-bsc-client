// Fill out your copyright notice in the Description page of Project Settings.

#include "BSCWalletBPFunctionLibrary.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

FString UBSCWalletBPFunctionLibrary::QueryBalance(FString walletAdress, FString tokenAdress)
{
	UE_LOG(LogTemp, Display, TEXT("QueryBalance: %s  %s"), *walletAdress, *tokenAdress);

	FString pythonScriptPath = FPaths::ProjectContentDir();
	pythonScriptPath += "/../../../scripts/querybalance.py";

	FString command = FString::Printf(TEXT("python %s -wallet %s -token %s"), 
		*pythonScriptPath,
		*walletAdress,
		*tokenAdress
	);

	UE_LOG(LogTemp, Display, TEXT("Commmand: %s"), *command);
	std::string result = exec(TCHAR_TO_ANSI(*command));
	return FString(result.c_str());
}