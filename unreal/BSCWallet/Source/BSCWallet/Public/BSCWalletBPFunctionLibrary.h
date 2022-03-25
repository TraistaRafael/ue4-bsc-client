// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BSCWalletBPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BSCWALLET_API UBSCWalletBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category="BSCWallet")
	FString QueryBalance(FString walletAdress, FString tokenAddress);
};
