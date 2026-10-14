// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitVendingProcess.h"
#include "VendingMachine.h"

UWaitVendingProcess* UWaitVendingProcess::StartVendingAndWait(UGameplayAbility* OwningAbility, AVendingMachine* Target)
{
	UWaitVendingProcess* NewTask = NewAbilityTask<UWaitVendingProcess>(OwningAbility);
	NewTask->VendingMachine = Target;
	return NewTask;
}

void UWaitVendingProcess::Activate()
{
	if (IsValid(VendingMachine))
	{
		VendingMachine->OnVendingStarted.AddDynamic(this, &ThisClass::HandleVendingStarted);
		VendingMachine->OnVendingComplete.AddDynamic(this, &ThisClass::HandleVendingComplete);
		VendingMachine->StartVending();
	}
	else
	{
		OnCanceled.Broadcast();
		EndTask();
	}
}

void UWaitVendingProcess::HandleVendingStarted()
{
	OnVendingStarted.Broadcast();
}

void UWaitVendingProcess::HandleVendingComplete()
{
	OnVendingComplete.Broadcast();
}
