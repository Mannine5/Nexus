// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"

class UInventoryItemFragment;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, Const)
class NEXUS_API UItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	TObjectPtr<UTexture2D> ItemIcon;
	
	// Very important to have this set to Instanced, so that each item definition can have its own unique fragments, 
	// rather than sharing the same fragment instances across all item definitions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Fragments Array")
	TArray<TObjectPtr<UInventoryItemFragment>> Fragments;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "FragmentClass"))
	static const UInventoryItemFragment* FindFragmentByClass(
		const TSubclassOf<UItemDefinition> ItemDefinitionClass, 
		const TSubclassOf<UInventoryItemFragment> FragmentClass);
};
