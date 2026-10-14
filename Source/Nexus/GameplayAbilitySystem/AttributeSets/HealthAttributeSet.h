// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UHealthAttributeSet();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Health Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Health Attributes")
	FGameplayAttributeData MaxHealth;
	
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, MaxHealth);
};
