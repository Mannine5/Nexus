// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitVendingProcess.generated.h"

class AVendingMachine;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVendingStageEvent);

UCLASS()
class NEXUS_API UWaitVendingProcess : public UAbilityTask
{
	GENERATED_BODY()
	
protected:
	TObjectPtr<AVendingMachine> VendingMachine;
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = true))
	static UWaitVendingProcess* StartVendingAndWait(UGameplayAbility* OwningAbility, AVendingMachine * Target);
	
	virtual void Activate() override;
	
	UFUNCTION()
	void HandleVendingStarted();
	
	UFUNCTION()
	void HandleVendingComplete();
	
	UPROPERTY(BlueprintAssignable)
	FVendingStageEvent OnVendingStarted;
	
	UPROPERTY(BlueprintAssignable)
	FVendingStageEvent OnVendingComplete;
	
	UPROPERTY(BlueprintAssignable)
	FVendingStageEvent OnCanceled;
};
