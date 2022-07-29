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
	
	UFUNCTION(BlueprintPure, Category="Inventory")
	TArray<FItemStruct> GetInventoryInfo();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void AddItemToInventory(FItemStruct ItemAdded);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Inventory")
	void Server_AddItemToInventory(FItemStruct ItemAdded);

private:

	UPROPERTY(Replicated)
	TArray<FItemStruct> InventoryArray;
	
};
