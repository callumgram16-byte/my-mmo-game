// Copyright 2026 My MMO Game. All Rights Reserved.

#include "Character/CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.TickInterval = 0.0f;
	PrimaryActorTick.bTickEvenWhenPaused = false;

	// Don't rotate character with camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

	// Initialize health and mana
	CurrentHealth = MaxHealth;
	CurrentMana = MaxMana;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitudeSq() > 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotm(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotm(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Value.Get<FVector2D>().Y);
		AddMovementInput(RightDirection, Value.Get<FVector2D>().X);
	}
}

void ACharacterBase::Look(const FInputActionValue& Value)
{
	if (Value.GetMagnitudeSq() > 0.0f)
	{
		AddControllerYawInput(Value.Get<FVector2D>().X);
		AddControllerPitchInput(Value.Get<FVector2D>().Y);
	}
}

void ACharacterBase::TakeDamage(float DamageAmount)
{
	if (DamageAmount <= 0.0f)
	{
		return;
	}

	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		Die();
	}
}

void ACharacterBase::Heal(float HealAmount)
{
	if (HealAmount <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Min(CurrentHealth + HealAmount, MaxHealth);
}

void ACharacterBase::ConsumeMana(float ManaAmount)
{
	if (ManaAmount <= 0.0f)
	{
		return;
	}

	CurrentMana = FMath::Max(CurrentMana - ManaAmount, 0.0f);
}

void ACharacterBase::RestoreMana(float ManaAmount)
{
	if (ManaAmount <= 0.0f)
	{
		return;
	}

	CurrentMana = FMath::Min(CurrentMana + ManaAmount, MaxMana);
}

void ACharacterBase::GainExperience(int64 ExperienceAmount)
{
	if (ExperienceAmount <= 0)
	{
		return;
	}

	ExperiencePoints += ExperienceAmount;

	int64 ExperienceThreshold = CharacterLevel * 1000;
	if (ExperiencePoints >= ExperienceThreshold)
	{
		LevelUp();
	}
}

void ACharacterBase::LevelUp()
{
	CharacterLevel++;
	MaxHealth += 10.0f;
	CurrentHealth = MaxHealth;
	MaxMana += 5.0f;
	CurrentMana = MaxMana;

	UE_LOG(LogTemp, Warning, TEXT("Character leveled up to %d"), CharacterLevel);
}

void ACharacterBase::Die()
{
	if (!IsAlive())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Character died"));

	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECC_Pawn);
}