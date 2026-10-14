// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


// Sets default values
AConnectActor::AConnectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConnectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConnectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConnectActor::ConnectToServer()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->ClientTravel("127.0.0.1", ETravelType::TRAVEL_Absolute);
}

