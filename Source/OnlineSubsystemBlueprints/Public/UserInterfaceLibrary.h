// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserInterfaceLibrary.generated.h"

/**
 * 
 */
class AOSSActor;
UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UUserInterfaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable,Category="OnlineIdentity")
static bool Login(AOSSActor* OnlineSubsystemActor,
	int32 LocalUserNum,/** Type of account. Needed to identity the auth method to use (epic, internal, facebook, etc) */

FString Type,
/** Id of the user logging in (email, display name, facebook id, etc) */
FString Id,
/** Credentials of the user logging in (password or auth token) */
FString Token);

	//
	
	
	
	/* Player has not logged in or chosen a local profile 
	0=NotLoggedIn,
	Player is using a local profile but is not logged in 
	1=UsingLocalProfile,
	Player has been validated by the platform specific authentication service 
	2=LoggedIn*/
	UFUNCTION(BlueprintCallable,Category="OnlineIdentity")
	static uint8 GetLoginStatus(AOSSActor* OnlineSubsystemActor,int32 LocalUserNum);
	UFUNCTION(BlueprintCallable,Category="OnlineIdentity")
    static FString GetPlayerNickname(AOSSActor* OnlineSubsystemActor,int32 LocalUserNum);
	
};
