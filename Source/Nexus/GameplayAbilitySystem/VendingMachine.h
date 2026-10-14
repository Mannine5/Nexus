// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "AttributeSets/BeverageAttributeSet.h"
#include "VendingMachine.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FVendingEvent);

UCLASS()
class NEXUS_API AVendingMachine : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVendingMachine();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UBeverageAttributeSet> BeverageSet;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;
	
	virtual void AddDefaultAbilities();
	virtual void ApplyStartupEffects();
	
	bool DefaultAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	
	FTimerHandle VendingStartTimer;
	FTimerHandle VendingCompleteTimer;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void StartVending();
	
	FVendingEvent OnVendingStarted;
	FVendingEvent OnVendingComplete;
	
	UFUNCTION()
	virtual void OnTimerFinished(int Stage);
};
