// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API ADemoPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
	void Server_SetVariable(float NewValue);
	
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_DisplayName(const FString& NewName);
	
	
	
};
