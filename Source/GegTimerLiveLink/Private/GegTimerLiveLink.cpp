// Copyright Epic Games, Inc. All Rights Reserved.

#include "GegTimerLiveLink.h"
#include "GegLiveLinkSource.h"

#define LOCTEXT_NAMESPACE "FGegTimerLiveLinkModule"

void FGegTimerLiveLinkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
		
	// accedo al modulo LiveLink e vi registro la nuova sorgente LiveLink
	ILiveLinkClient& LiveLinkClient = IModularFeatures::Get().GetModularFeature<ILiveLinkClient>(ILiveLinkClient::ModularFeatureName);
	LiveLinkClient.AddSource(MakeShared<GegLiveLinkSource>());
}

void FGegTimerLiveLinkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGegTimerLiveLinkModule, GegTimerLiveLink)