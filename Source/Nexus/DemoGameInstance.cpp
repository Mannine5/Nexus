// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameInstance.h"

void UDemoGameInstance::Init()
{
	Levels.Add("Lvl_ThirdPerson");
	Levels.Add("Lvl_ThirdPerson1");
	Levels.Add("Lvl_ThirdPerson2");
	
	LevelIndex = 0;
	
	if (GEngine)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UDemoGameInstance::OnConnectionFailure);
	}
}

void UDemoGameInstance::OnConnectionFailure(
	UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType,const FString& ErrorString)
{
	UE_LOG(LogTemp, Error, TEXT("Connection failure: %s"), *ErrorString);
	// Handle the network failure here (e.g., show a message to the player, return to main menu, etc.)
	
	if (GEngine)
	{
		switch (FailureType)
		{
		case ENetworkFailure::Type::ConnectionTimeout:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Connection timeout!"));
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Other network failure: ") + ErrorString);
			break;
		}
	}
}

const FString& UDemoGameInstance::GetNextLevelName()
{
	LevelIndex++;
	
	if (LevelIndex >= Levels.Num())
	{
		LevelIndex = 0; // Loop back to the first level
	}
	
	return Levels[LevelIndex];
}
