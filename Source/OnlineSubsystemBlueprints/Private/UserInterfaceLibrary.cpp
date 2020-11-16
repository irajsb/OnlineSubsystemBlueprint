// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaceLibrary.h"
#include "OSSActor.h"
bool UUserInterfaceLibrary::Login(AOSSActor* OnlineSubsystemActor, int32 LocalUserNum, FString Type, FString Id,
    FString Token)
{

    IOnlineSubsystem* OnlineSubsystem=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName);
    if(!OnlineSubsystem->GetIdentityInterface().Get()->OnLoginCompleteDelegates->IsBound())
    OnlineSubsystem->GetIdentityInterface().Get()->OnLoginCompleteDelegates->AddUObject(OnlineSubsystemActor,&AOSSActor::OnLoginCompleted);
    const FOnlineAccountCredentials OnlineAccountCredentials(Type,Id,Token);
    return  OnlineSubsystem->GetIdentityInterface().Get()->Login(LocalUserNum,OnlineAccountCredentials);
}

uint8 UUserInterfaceLibrary::GetLoginStatus(AOSSActor* OnlineSubsystemActor, int32 LocalUserNum)
{
    IOnlineIdentity* OnlineIdentity=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetIdentityInterface().Get();
    if(!OnlineIdentity)
    {
        UE_LOG(LogOnline,Error,TEXT("No OS Pointer"));
        return 0;
    }
    return OnlineIdentity->GetLoginStatus(LocalUserNum);
    
}

FString UUserInterfaceLibrary::GetPlayerNickname(AOSSActor* OnlineSubsystemActor, int32 LocalUserNum)
{
    IOnlineIdentity* OnlineIdentity=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetIdentityInterface().Get();
    return OnlineIdentity->GetPlayerNickname(LocalUserNum);
}
