// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
# include"AbilitySystemComponent.h" // Tarvitaan EGameplayEffectReplicationMode enumin käyttöön. Forward declaration ei riitä, koska käytetään enumia.
#include "AbilitySystemInterface.h"
#include "Nexus/GameplayAbilitySystem/AttributeSets/HealthAttributeSet.h"
#include "MannineCharacter.generated.h"


// AbilitySystemComponent sisältää nämä:
// class UAbilitySystemComponent;
// class UGameplayAbility;
// class UGameplayEffect;

UCLASS()
class NEXUS_API AMannineCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannineCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;

protected:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	bool DefaultAbilitiesGiven = false;
	
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;
	bool StartupEffectsApplied = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void AddDefaultAbilities();
	virtual void ApplyStartupEffects();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
