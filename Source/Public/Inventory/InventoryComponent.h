// Copyright 2026 My MMO Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryUpdated, const FInventoryItem&, Item, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_One(FOnInventoryFull, const FInventoryItem&, Item);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYMMOGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(const FInventoryItem& Item, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(const FString& ItemID, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FInventoryItem* FindItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(const FString& ItemID, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool EquipItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipItem(const FString& ItemID);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	float GetTotalWeight() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int32 GetInventorySize() const { return Inventory.Num(); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	int32 GetMaxInventorySlots() const { return MaxInventorySlots; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	bool IsInventoryFull() const;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FOnInventoryFull OnInventoryFull;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventorySlots = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float MaxCarryWeight = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItem> Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<FString, FInventoryItem> EquippedItems;

private:
	void OnItemUsed(const FInventoryItem& Item);
};