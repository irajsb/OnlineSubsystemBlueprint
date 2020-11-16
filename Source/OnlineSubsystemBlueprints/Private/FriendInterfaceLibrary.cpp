// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendInterfaceLibrary.h"
#include "OSSActor.h"
bool UFriendInterfaceLibrary::GetFriendsList(AOSSActor* OnlineSubsystemActor,int UserIndex,TArray<FBlueprintOnlineFriend>& List,FName ListName)
  {
        IOnlineFriends* OnlineFriends=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetFriendsInterface().Get();
    
      TArray<TSharedRef<FOnlineFriend>> ListHolder;
      bool result= OnlineFriends->GetFriendsList(0,*ListName.ToString(),ListHolder);

    UE_LOG(LogTemp,Error,TEXT("Fwend!!! %d"),ListHolder.Num());
     for (TSharedRef<FOnlineFriend> OnlineFriend  : ListHolder )
     {
     TSharedPtr<FOnlineFriend>SharedPtr(OnlineFriend) ;
         FBlueprintOnlineFriend BlueprintOnlineFriend;
         BlueprintOnlineFriend.Friends=SharedPtr;
         List.Add(BlueprintOnlineFriend);
     }
     
    
return  result;
}

bool UFriendInterfaceLibrary::ReadFriendsList(AOSSActor* OnlineSubsystemActor, int UserIndex, FName ListName)
{

    IOnlineFriends* OnlineFriends=	IOnlineSubsystem::Get(OnlineSubsystemActor->SubsystemName)->GetFriendsInterface().Get();
    OnlineSubsystemActor->OnReadFriendsListComplete.BindUObject(OnlineSubsystemActor,&AOSSActor::OnReadFriendsListCompleteDelegates);
  return   OnlineFriends->ReadFriendsList(UserIndex,ListName.ToString(),OnlineSubsystemActor->OnReadFriendsListComplete);
    
}
