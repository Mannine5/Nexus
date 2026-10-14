// Fill out your copyright notice in the Description page of Project Settings.


#include "VendingMachine.h"
#include "AbilitySystemComponent.h"

// Sets default values
AVendingMachine::AVendingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	BeverageSet = CreateDefaultSubobject<UBeverageAttributeSet>(TEXT("BeverageSet"));
	
	bReplicates = true;
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

// Called when the game starts or when spawned
void AVendingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	AddDefaultAbilities();
	ApplyStartupEffects();
}

void AVendingMachine::AddDefaultAbilities()
{
	if (IsValid(AbilitySystemComponent) == false || DefaultAbilitiesGiven)
	{
		return;	
	}
	
	for (auto& Ability :DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, nullptr));
	}
	DefaultAbilitiesGiven = true;
}

void AVendingMachine::ApplyStartupEffects()
{
	if (IsValid(AbilitySystemComponent) == false || StartupEffectsApplied)
	{
		return;	
	}
	
	for (auto& Effect :StartupEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		
	}
	StartupEffectsApplied = true;
}

// Called every frame
void AVendingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* AVendingMachine::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AVendingMachine::StartVending()
{
	FTimerDelegate VendingStart;
	VendingStart.BindUObject(this, &ThisClass::OnTimerFinished, 1);
	GetWorld()->GetTimerManager().SetTimer(VendingStartTimer, VendingStart, 1.0f, false);
	
	FTimerDelegate VendingComplete;
	VendingComplete.BindUObject(this, &ThisClass::OnTimerFinished, 2);
	GetWorld()->GetTimerManager().SetTimer(VendingCompleteTimer, VendingComplete, 5.0f, false);
}

void AVendingMachine::OnTimerFinished(int Stage)
{
	switch (Stage)
	{
		case 1:
			OnVendingStarted.Broadcast();
			break;
		case 2:
			OnVendingComplete.Broadcast();
			break;
		default:
			break;
	}
	
	
}

