// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameMode.h"
#include "EngineUtils.h"
#include "DemoGameInstance.h"

ADemoGameMode::ADemoGameMode()
{
	bUseSeamlessTravel = true;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f; 
	static ConstructorHelpers::FObjectFinder<UClass> Pawn(TEXT("/Script/Engine.Blueprint'/Game/GameplayAbilitySystem/Character/BP_NexusPlayer.BP_NexusPlayer_C'"));
	
	if (Pawn.Object)
	{
		PawnClass = Pawn.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not load character. Pawn class not found or something..."));
	}
}

void ADemoGameMode::Tick(float DeltaSeconds)
{
	LevelChangeTime += DeltaSeconds;
	if (LevelChangeTime >= LevelChangeInterval)
	{
		LevelChangeTime = 0.0f;
		UDemoGameInstance* GameInstance = GetGameInstance<UDemoGameInstance>();
		const FString &NextLevelName = GameInstance->GetNextLevelName();
		GetWorld()->ServerTravel(NextLevelName);
	}
}

void ADemoGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Player %s has joined the game."), *NewPlayer->GetName());
	
	AActor* PlayerStart = ChoosePlayerStart(NewPlayer);
	FActorSpawnParameters SpawnParams;
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(PawnClass, PlayerStart->GetActorTransform(), SpawnParams);
	
	FString PlayerName = FString::Printf(TEXT("Player %d"), GetNumPlayers());
	FName PlayerNameTag = FName(*PlayerName);
	Pawn->Tags.Add(PlayerNameTag);
	UDemoGameInstance* GameInstance = GetGameInstance<UDemoGameInstance>();
	GameInstance->PlayerIdentifiers.Add(NewPlayer, PlayerNameTag);
	
	if (Pawn)
	{
		NewPlayer->Possess(Pawn);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn pawn for player %s."), *NewPlayer->GetName());
	}
}

void ADemoGameMode::HandleSeamlessTravelPlayer(AController*& Controller)
{
	UE_LOG(LogTemp, Warning, TEXT("Handling seamless travel for player %s."), *Controller->GetName());
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	
	if (PlayerController)
	{
		UDemoGameInstance* GameInstance = GetGameInstance<UDemoGameInstance>();
		APawn* PawnToPossess = nullptr;
		
		if (GameInstance->PlayerIdentifiers.Find(PlayerController) != nullptr)
		{
			FName PlayerTag = *GameInstance->PlayerIdentifiers.Find(PlayerController);
			
			for (TActorIterator<APawn> It(GetWorld()); It; ++It)
			{
				if (It->ActorHasTag(PlayerTag))
				{
					PawnToPossess = *It;
					break;
				}
			}
		}
		
		if (PawnToPossess)
		{
			Controller->Possess(PawnToPossess);
			UE_LOG(LogTemp, Warning, TEXT("Player %s possessed pawn %s after seamless travel."), *PlayerController->GetName(), *PawnToPossess->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No pawn found for player %s after seamless travel."), *PlayerController->GetName());
		}
	}
}

void ADemoGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		ActorList.Add(*It);
	}
}
