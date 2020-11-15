// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SessionInterfaceLibrary.generated.h"


/**
 * 
 */
class AOSSActor;
struct FBlueprintSessionResult;
UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API USessionInterfaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
		UFUNCTION(BlueprintCallable,Category="OnlineSession")
    	static FString GetOnlineSessionSearchState(AOSSActor* OnlineSubsystemActor) ;
	/**
	* Searches for sessions matching the settings specified
	* @return true if successful searching for sessions, false otherwise
	* Has Bindable Delegate
	*/
    	UFUNCTION(BlueprintCallable,Category="OnlineSession")
    	static bool FindSession(AOSSActor* OnlineSubsystemActor,int SearchingUserNum,int TimeOut);
	/**
	* Joins the session specified
	* @return true if the call completed successfully, false otherwise
	* Has Bindable Delegate
	*/
		UFUNCTION(BlueprintCallable,Category="OnlineSession")
		static bool JoinSession(AOSSActor* OnlineSubsystemActor,int LocalUserIndex,FBlueprintSessionResult Session );
	UFUNCTION(BlueprintCallable,Category="OnlineSession")
	static	bool GetResolvedConnectString(AOSSActor* OnlineSubsystemActor,FBlueprintSessionResult Session,FString& ConnectInfo);
	
};



	

