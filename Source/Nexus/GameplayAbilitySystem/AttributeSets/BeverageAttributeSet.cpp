// Fill out your copyright notice in the Description page of Project Settings.


#include "BeverageAttributeSet.h"
#include "Net/UnrealNetwork.h"

UBeverageAttributeSet::UBeverageAttributeSet()
{
	// InitCokes(10.0f);
	// InitMaxCokes(20.0f);
	// InitSprites(5.0f);
	// InitMaxSprites(20.0f);
}

void UBeverageAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UBeverageAttributeSet, Cokes);
	DOREPLIFETIME_CONDITION(UBeverageAttributeSet, MaxCokes, COND_InitialOnly);
	DOREPLIFETIME(UBeverageAttributeSet, Sprites);
	DOREPLIFETIME(UBeverageAttributeSet, MaxSprites);
}


