// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoPlayerController.h"
#include "EngineUtils.h"
#include "DemoCubeBase.h"

void ADemoPlayerController::Server_SetVariable_Implementation(float NewValue)
{
	for (TActorIterator<ADemoCubeBase> It(GetWorld()); It; ++It)
	{
		ADemoCubeBase* DemoCube = *It;
		if (DemoCube)
		{
			DemoCube->Variable = NewValue;
		}
	}
}

bool ADemoPlayerController::Server_SetVariable_Validate(float NewValue)
{
	if (NewValue > 42.0f) return false; 
	
	return true;
}

void ADemoPlayerController::Client_DisplayName_Implementation(const FString& NewName)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Name: %s"), *NewName));
	}
	
	
}


