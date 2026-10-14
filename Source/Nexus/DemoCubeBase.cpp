// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCubeBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ADemoCubeBase::ADemoCubeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetReplicates(true);
	SetReplicateMovement(true);
	
}

// Called when the game starts or when spawned
void ADemoCubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemoCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoCubeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADemoCubeBase, Variable);
}

void ADemoCubeBase::Multicast_SayHi_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Server asked to say hi!");
	}
}