// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusGameplayAbility.h"

UNexusGameplayAbility::UNexusGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
}

bool UNexusGameplayAbility::HasPC() const
{
	const APawn* PawnObject = Cast<APawn>(GetOwningActorFromActorInfo());
	
	if (!PawnObject)
	{
		return false;
	}
	return PawnObject->GetController()->IsA<APlayerController>();
}
