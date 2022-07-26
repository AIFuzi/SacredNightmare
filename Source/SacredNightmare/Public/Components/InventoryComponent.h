#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemStructure.h"
#include "InventoryComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACREDNIGHTMARE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	
	UInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<FItemStruct> BeginItems;
	
	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FItemStruct> GetInventoryInfo();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItemToInventory(FItemStruct ItemAdded);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Inventory")
	void Server_AddItemToInventory(FItemStruct ItemAdded);

	UFUNCTION(BlueprintPure, Category="Inventory")
	void FindItemInInventoryByName(FName ItemName, bool& ItemFound, FItemStruct & Item);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void RemoveItemFromInventory(FName ItemName, bool RemoveAll, int Count);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Inventory")
	void Server_RemoveItemFromInventory(FName ItemName, bool RemoveAll, int Count);

private:

	UPROPERTY(Replicated)
	TArray<FItemStruct> InventoryArray;

	void SpawnBeginItems();
	
};
