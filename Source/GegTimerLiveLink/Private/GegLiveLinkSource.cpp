// Fill out your copyright notice in the Description page of Project Settings.

#include "GegLiveLinkSource.h"
#include "Roles/LiveLinkAnimationRole.h"

GegLiveLinkSource::GegLiveLinkSource()
{
	LiveLinkClient = nullptr;

	//FWorldContext* WorldContext = GEngine->GetWorldContextFromGameViewport(GEditor->GameViewport);
	//TimerManager = &WorldContext->World()->GetTimerManager();
	//TimerManager->SetTimer(FTimerHandle::FTimerHandle(),this, );	// vedere FSimpleDelegate signature to call Test f(x)
}

bool GegLiveLinkSource::IsSourceStillValid() const
{
	return true;
}

void GegLiveLinkSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
	// client connect
	LiveLinkClient = InClient;

	// create new Subject for this connection and associate it:
	// Name and the GUID given like param
	SubjectKey001.SubjectName = FLiveLinkSubjectName(TEXT("Time"));
	SubjectKey001.Source = InSourceGuid;

	// Describe to LiveLink System HOW my data structure is organized
	// NOTE: FLiveLinkStaticDataStruct is wrapper of a wrapper. It contains the ptr to custom data structure
	FLiveLinkStaticDataStruct StaticData001;
	StaticData001.InitializeWith(FLiveLinkBaseStaticData::StaticStruct(), nullptr);
	
	// Cast able to access to the wrapper's content
	FLiveLinkBaseStaticData* BaseDataPtr = StaticData001.Cast<FLiveLinkBaseStaticData>();

	// Specify the name for each parameter which is content in my custom structure
	BaseDataPtr->PropertyNames.Add("Seconds");
	BaseDataPtr->PropertyNames.Add("Minutes");
	BaseDataPtr->PropertyNames.Add("Hours12");
	BaseDataPtr->PropertyNames.Add("Hours24");

	// this will clear all buffered frames
	// public custom DataStruct in LiveLink System on all UE Thread
	// key - role* - data was created
	InClient->PushSubjectStaticData_AnyThread(SubjectKey001, ULiveLinkBasicRole::StaticClass(), MoveTemp(StaticData001));

	// *Remember: Role specify which type of data are exposed by subject
}

bool GegLiveLinkSource::RequestSourceShutdown()
{
	LiveLinkClient = nullptr;
	return true;
}

FText GegLiveLinkSource::GetSourceType() const
{
	return FText::FromString("TimerSource");
}

FText GegLiveLinkSource::GetSourceMachineName() const
{
	return FText::FromString(FPlatformProcess::UserName());
}

FText GegLiveLinkSource::GetSourceStatus() const
{
	return FText::FromString("Active");
}

TStatId GegLiveLinkSource::GetStatId() const
{
	return TStatId();
}

bool GegLiveLinkSource::IsTickableInEditor() const
{
	return true;
}

void GegLiveLinkSource::Tick(float DeltaTime)
{
	if (LiveLinkClient)
	{
		CallClockTime();
	}
}

void GegLiveLinkSource::CallClockTime()
{
	// OPTIMIZATION: add timer which is called every 1 sec 
	// GEngine->TimecodeProviderClassName
	// GEngine->GetWorldContextFromGameViewport(GEditor->GameViewport);

	FLiveLinkFrameDataStruct FrameDataStruct001 = FLiveLinkFrameDataStruct(FLiveLinkBaseFrameData::StaticStruct());
	FLiveLinkBaseFrameData* FrameDataPtr001 = FrameDataStruct001.Cast<FLiveLinkBaseFrameData>();

	// TO INSERT ALWAYS: it's time in those data was generated. It's always validate
	// NOTE: if this WorldTime is too late or forward in time respect the WorldCounter, the pack will not valid
	FrameDataPtr001->WorldTime = FPlatformTime::Seconds();		// Engine Time

	Dtime = FDateTime::UtcNow();
	
	FrameDataPtr001->PropertyValues.Add(Dtime.GetSecond());
	FrameDataPtr001->PropertyValues.Add(Dtime.GetMinute());
	FrameDataPtr001->PropertyValues.Add(Dtime.GetHour12());
	FrameDataPtr001->PropertyValues.Add(Dtime.GetHour());

	LiveLinkClient->PushSubjectFrameData_AnyThread(SubjectKey001, MoveTemp(FrameDataStruct001));
}