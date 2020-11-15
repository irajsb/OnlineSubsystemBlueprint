// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IOnlineSubsystemBlueprints.h"


class FOnlineSubsystemBlueprints : public IOnlineSubsystemBlueprints
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FOnlineSubsystemBlueprints, OnlineSubsystemBlueprints )



void FOnlineSubsystemBlueprints::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FOnlineSubsystemBlueprints::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



