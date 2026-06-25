// Copyright 2026 My MMO Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"

/**
 * Base character class for all player and NPC characters in the MMO
 * Handles movement, animation, and basic stat systems
 */
UCLASS()
class MYMMOGAME_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Input callback functions
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Enhanced Input System
	class UEnhancedInputComponent* EnhancedInputComponent;
	class UEnhancedInputLocalPlayerSubsystem* InputSubsystem;
	class UInputMappingContext* DefaultMappingContext;

	// Input actions
	class UInputAction* MoveAction;
	class UInputAction* LookAction;
	class UInputAction* JumpAction;

	// Character Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float MaxMana = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	float CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	int32 CharacterLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Stats")
	int64 ExperiencePoints = 0;

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1000.0f;

	// Input callbacks
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	// Health and Mana
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void ConsumeMana(float ManaAmount);

	UFUNCTION(BlueprintCallable, Category = "Mana")
	void RestoreMana(float ManaAmount);

	// Character progression
	UFUNCTION(BlueprintCallable, Category = "Progression")
	void GainExperience(int64 ExperienceAmount);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void LevelUp();

	// Death
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void Die();

public:
	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	float GetHealthPercentage() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Mana")
	float GetManaPercentage() const { return CurrentMana / MaxMana; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Stats")
	int32 GetCharacterLevel() const { return CharacterLevel; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Stats")
	int64 GetExperiencePoints() const { return ExperiencePoints; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool IsAlive() const { return CurrentHealth > 0.0f; }
};