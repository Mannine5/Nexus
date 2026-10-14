// Fill out your copyright notice in the Description page of Project Settings.


#include "MannineCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AMannineCharacter::AMannineCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));
	
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	
	
}

// Called when the game starts or when spawned
void AMannineCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	AddDefaultAbilities();
	ApplyStartupEffects();
}

// Called every frame
void AMannineCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMannineCharacter::AddDefaultAbilities()
{
	UE_LOG(LogTemp, Warning, TEXT("DefaultAbilities Num: %d"), DefaultAbilities.Num());
	
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

void AMannineCharacter::ApplyStartupEffects()
{
	UE_LOG(LogTemp, Warning, TEXT("StartupEffects Num: %d"), StartupEffects.Num());
	
	if (IsValid(AbilitySystemComponent) == false || StartupEffectsApplied)
	{
		return;	
	}
	
	for (auto& Effect :StartupEffects)
	{
		if (!IsValid(Effect))
		{
			UE_LOG(LogTemp, Error, TEXT("StartupEffects contains an INVALID GameplayEffect!"));
			continue;
		}
		
		
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		
		if (!SpecHandle.IsValid())
		{
			UE_LOG(LogTemp, Error,
				TEXT("Failed to create GameplayEffectSpec for: %s"),
				*Effect->GetName());

			continue;
		}
		
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		
	}
	StartupEffectsApplied = true;
}

// Called to bind functionality to input
void AMannineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

UAbilitySystemComponent* AMannineCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

