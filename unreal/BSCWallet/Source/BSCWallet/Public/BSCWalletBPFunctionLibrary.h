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

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BSCWalletBPFunctionLibrary.generated.h"

UCLASS()
class BSCWALLET_API UBSCWalletBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	* Query BSC for balance via python script based on web3 module.
	* @param FString walletAdress 
	* @param FString tokenAddress
	* @return FString - balance as fetched from BSC
	*/
	UFUNCTION(BlueprintCallable, Category="BSCWallet")
	FString QueryBalance(FString walletAdress, FString tokenAddress);

private: 
	
	/* Execute command console in backgroundand return output FString
	* @param FString fCommand - command to be executed
	* @return FString - command execution output as string
	*/ 
	static FString ExecuteSystemCommand(const char* command);
};
