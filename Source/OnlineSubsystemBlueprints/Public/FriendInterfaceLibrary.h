// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystemTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineFriendsInterface.h"


#include "FriendInterfaceLibrary.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FBlueprintOnlineFriend
{
	GENERATED_USTRUCT_BODY()
	
	TSharedPtr<FOnlineFriend> Friends;
};



class AOSSActor;
UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API UFriendInterfaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
	UFUNCTION(BlueprintCallable)
	static bool GetFriendsList(AOSSActor* OnlineSubsystemActor,int UserIndex,TArray<FBlueprintOnlineFriend>& List,FName ListName=TEXT("Default"));
	/*
	* Valid Names:
	* Default,
	OnlinePlayers,
	InGamePlayers,
	InGameAndSessionPlayers,
	*/
	UFUNCTION(BlueprintCallable)
	static bool ReadFriendsList(AOSSActor* OnlineSubsystemActor,int UserIndex,FName ListName=TEXT("Default"));
public:

	
};
