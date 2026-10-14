// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DemoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API ADemoGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADemoGameMode();
	
	virtual void Tick(float DeltaSeconds) override;
	
	float LevelChangeInterval = 5.0f;
	float LevelChangeTime = 0.0f;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void HandleSeamlessTravelPlayer(AController*& Controller) override;
	
	UClass* PawnClass; 
	
	virtual void GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList) override;
};
