// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BeverageAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UBeverageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UBeverageAttributeSet();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Beverage Attributes")
	FGameplayAttributeData Cokes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Beverage Attributes")
	FGameplayAttributeData MaxCokes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Beverage Attributes")
	FGameplayAttributeData Sprites;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Beverage Attributes")
	FGameplayAttributeData MaxSprites;
	
	ATTRIBUTE_ACCESSORS_BASIC(UBeverageAttributeSet, Cokes);
	ATTRIBUTE_ACCESSORS_BASIC(UBeverageAttributeSet, MaxCokes);
	ATTRIBUTE_ACCESSORS_BASIC(UBeverageAttributeSet, Sprites);
	ATTRIBUTE_ACCESSORS_BASIC(UBeverageAttributeSet, MaxSprites);
};
