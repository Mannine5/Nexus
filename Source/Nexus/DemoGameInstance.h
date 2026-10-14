// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	virtual void OnConnectionFailure(
		UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
	
	const FString& GetNextLevelName();
	
public:
	TArray<FString> Levels;
	
	TMap<APlayerController*, FName> PlayerIdentifiers; // Map to store player identifiers
	
protected:
	int LevelIndex;
};
