// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"
#include "Net/UnrealNetwork.h"

UHealthAttributeSet::UHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	
	UE_LOG(LogTemp, Warning, TEXT("HealthAttributeSet constructor: Health=%f MaxHealth=%f"),
	GetHealth(),
	GetMaxHealth());
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthAttributeSet, Health);
	DOREPLIFETIME(UHealthAttributeSet, MaxHealth);
}
