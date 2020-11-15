// Fill out your copyright notice in the Description page of Project Settings.
#include "SessionInterfaceLibrary.h"
#include  "OSSActor.h"






FString USessionInterfaceLibrary::GetOnlineSessionSearchState(AOSSActor* OnlineSubsystemActor)
{	return EOnlineAsyncTaskState::ToString(OnlineSubsystemActor->OnlineSessionSearch->SearchState);
}

bool USessionInterfaceLibrary::FindSession(AOSSActor* OnlineSubsystemActor, int SearchingUserNum, int TimeOut)
{

    IOnlineSession* OnlineSession=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetSessionInterface().Get();
    OnlineSubsystemActor->OnlineSessionSearch->MaxSearchResults=50;
  OnlineSubsystemActor->  OnlineSessionSearch->TimeoutInSeconds=TimeOut;
    OnlineSession->OnFindSessionsCompleteDelegates.AddUObject(OnlineSubsystemActor,&AOSSActor::OnFindSessionsCompleteDelegates);
    return OnlineSession->FindSessions(SearchingUserNum,OnlineSubsystemActor->OnlineSessionSearch.ToSharedRef());
    
}

bool USessionInterfaceLibrary::JoinSession(AOSSActor* OnlineSubsystemActor, int LocalUserIndex,
    FBlueprintSessionResult Session)
{
    IOnlineSession* OnlineSession=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetSessionInterface().Get();
    OnlineSession->OnJoinSessionCompleteDelegates.AddUObject(OnlineSubsystemActor,&AOSSActor::OnJoinSessionCompleteDelegates);
    return OnlineSession->JoinSession(LocalUserIndex,NAME_GameSession,Session.OnlineResult);
    
}

bool USessionInterfaceLibrary::GetResolvedConnectString(AOSSActor* OnlineSubsystemActor,FBlueprintSessionResult Session,FString& ConnectInfo)
{
  FString ConnectionInfo;
  IOnlineSession* OnlineSession=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetSessionInterface().Get();
  return   OnlineSession->GetResolvedConnectString(Session.OnlineResult,NAME_GamePort,ConnectInfo);
}



