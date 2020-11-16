// Fill out your copyright notice in the Description page of Project Settings.


#include "OSSActor.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AOSSActor::AOSSActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates=false;
	
}

// Called when the game starts or when spawned
void AOSSActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOSSActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AOSSActor* AOSSActor::GetOnlineSubsystemActor(UObject* WorldContextObject,FName InSubsystemName,TEnumAsByte<EOSSResult>& Result)
{
	Result=EOSSResult::Fail;
	if(!IOnlineSubsystem::Get(InSubsystemName))
	{//if subsystem is not inited 
		UE_LOG(LogOnline,Error,TEXT(" %s is Null"),*InSubsystemName.ToString());
		return NULL;
	}
	TArray<AActor*> OnlineSubsystemActors;
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject,AOSSActor::StaticClass(),OnlineSubsystemActors);
	if(OnlineSubsystemActors.Num()==0)
	{
		UE_LOG(LogOnline,Log,TEXT("No OSA Found,Creating OSA for %s"),*InSubsystemName.ToString());
		
		AOSSActor* OnlineSubsystemActor=World->SpawnActor<AOSSActor>(AOSSActor::StaticClass());
		OnlineSubsystemActor->Init(InSubsystemName);
		Result=EOSSResult::Success;
		return OnlineSubsystemActor	;
	}	else 
	{
		for(AActor* Actor:OnlineSubsystemActors)
		{
		if(	Cast<AOSSActor>(Actor)->SubsystemName==InSubsystemName)
			{
			Result=EOSSResult::Success;
			return Cast<AOSSActor>(Actor);
			}
		}
		//if looped without returning then subsystem with that name doesnot exist

		AOSSActor* OnlineSubsystemActor=World->SpawnActor<AOSSActor>(AOSSActor::StaticClass());
		OnlineSubsystemActor->Init(InSubsystemName);
		Result=EOSSResult::Success;
		return OnlineSubsystemActor	;
	}
	

	
}



void AOSSActor::Init(FName InSubsystemName)
{
	SubsystemName=InSubsystemName;
	IOnlineSubsystem* OnlineSubsystem=	IOnlineSubsystem::Get(SubsystemName);
	
	
	OnlineSessionSearch=TSharedPtr<FOnlineSessionSearch>(new FOnlineSessionSearch);
	

	
}











//Delegates
void AOSSActor::OnLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                             const FString& Error)
{
	OnLoginComplete.Broadcast(LocalUserNum,bWasSuccessful,UserId.ToString(),Error);
}



void AOSSActor::OnFindSessionsCompleteDelegates(bool bWasSuccessful)
{
	TArray<FBlueprintSessionResult> Results;
	
	for(	FOnlineSessionSearchResult OnlineSessionSearchResult:	OnlineSessionSearch->SearchResults)
	{
		FBlueprintSessionResult  Wrapper;
		Wrapper.OnlineResult=OnlineSessionSearchResult;
		Results.Add(Wrapper);	
		
		
	}
	OnFindSessionsCompleteBP.Broadcast(bWasSuccessful,Results);
}

void AOSSActor::OnJoinSessionCompleteDelegates(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	OnJoinSessionCompleteBP.Broadcast(SessionName,EOnJoinSessionCompleteResultToString(Result));
}

void AOSSActor::OnReadFriendsListCompleteDelegates(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
	const FString& ErrorStr)
{
	OnReadFriendsListCompleteBP.Broadcast(LocalUserNum,bWasSuccessful,ListName,ErrorStr);
}



