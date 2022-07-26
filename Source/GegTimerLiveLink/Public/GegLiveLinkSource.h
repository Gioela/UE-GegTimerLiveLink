// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ILiveLinkSource.h"
#include "ILiveLinkClient.h"
#include "RenderCore.h"
//#include "Engine/World.h"

/**
 * 
 */
class GEGTIMERLIVELINK_API GegLiveLinkSource : public ILiveLinkSource, public FTickableGameObject
{
public:
	GegLiveLinkSource();

	/*
	* create connection between myself (source) and UE
	* 
	* Param InSourceGuid is GUID of this new connection
	*/
	void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;
	bool IsSourceStillValid() const override;
	bool RequestSourceShutdown() override;

	FText GetSourceType() const override;
	FText GetSourceMachineName() const override;
	FText GetSourceStatus() const override;

	TStatId GetStatId() const override;

	bool IsTickableInEditor() const override;

	void Tick(float DeltaTime) override;

	void CallClockTime();

protected:
	// Connection between my source of data and UE
	ILiveLinkClient* LiveLinkClient;

	// Subject which is defined and associated to GUID by ReceiveClient method
	FLiveLinkSubjectKey SubjectKey001;

	//FTimerManager* TimerManager;
	FDateTime Dtime;
};
