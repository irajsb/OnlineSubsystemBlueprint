// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Engine.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "GameFramework/Actor.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineStatsInterface.h"
#include "Interfaces/OnlineUserInterface.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include"OnlineSubsystemUtils/Classes/FindSessionsCallbackProxy.h"
#include "OSSActor.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLoginCompleteBP,int32, LocalUserNum, bool ,bWasSuccessful,  FString ,UserId, const FString&, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFindSessionsCompleteBP, bool,bWasSuccessful, const TArray<FBlueprintSessionResult>&, Results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnJoinSessionCompleteBP,FName,SessionName, FString,Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnReadFriendsListCompleteBP, int32 ,LocalUserNum, bool ,bWasSuccessful, const FString& ,ListName, const FString& ,ErrorStr);

UENUM()
enum EOSSResult
{
	Success,Fail
};


UCLASS()
class ONLINESUBSYSTEMBLUEPRINTS_API AOSSActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AOSSActor();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, meta=( WorldContext="WorldContextObject" ,ExpandEnumAsExecs ="Result" ))
    static AOSSActor* GetOnlineSubsystemActor(UObject* WorldContextObject,FName InSubsystemName,TEnumAsByte<EOSSResult>& Result);
	
	void Init(FName InSubsystemName);

	//Props
	UPROPERTY(BlueprintReadOnly)
	FName SubsystemName;
	TSharedPtr<FOnlineSessionSearch> OnlineSessionSearch;

	
	
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FOnLoginCompleteBP OnLoginComplete;
	void OnLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	UPROPERTY(BlueprintAssignable)
	FOnFindSessionsCompleteBP OnFindSessionsCompleteBP;
	void OnFindSessionsCompleteDelegates(bool bWasSuccessful);
	
	UPROPERTY(BlueprintAssignable)
	FOnJoinSessionCompleteBP OnJoinSessionCompleteBP;
	void OnJoinSessionCompleteDelegates(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	UPROPERTY(BlueprintAssignable)
	FOnReadFriendsListCompleteBP OnReadFriendsListCompleteBP;
	void OnReadFriendsListCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);
	FOnReadFriendsListComplete OnReadFriendsListComplete;
};





inline const TCHAR* EOnJoinSessionCompleteResultToString(EOnJoinSessionCompleteResult::Type EnumVal)
{
	switch (EnumVal)
	{
	case EOnJoinSessionCompleteResult::Success:
		{
			return TEXT("Success");
		}
	case EOnJoinSessionCompleteResult::SessionIsFull:
		{
			return TEXT("SessionIsFull");
		}
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		{
			return TEXT("SessionDoesNotExist");
		}
	case EOnJoinSessionCompleteResult::AlreadyInSession :
		{
			return TEXT("AlreadyInSession");
		}
	case EOnJoinSessionCompleteResult::UnknownError :
		{
			return TEXT("UnknownError");
		}
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress :
		{
			return TEXT("CouldNotRetrieveAddress");
		}
		
		
		
	}
	return TEXT("");
}


