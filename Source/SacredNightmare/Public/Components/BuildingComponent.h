#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Building/BuildingStructure.h"
#include "Items/ItemStructure.h"
#include "BuildingComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SACREDNIGHTMARE_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBuildingComponent();
	
	UFUNCTION(BlueprintPure, Category="Building")
	void FindItemForBuilding(class UInventoryComponent* InventoryComponent, TArray<FBuildingStruct> NeedItems, bool& IsItemFound, TArray<FItemStruct>& Items);

	UFUNCTION(BlueprintCallable, Category="Building")
	void SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInstanceDynamic* PreviewMaterial);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Building_RPC")
	void Server_SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInstanceDynamic* PreviewMaterial);

	UFUNCTION(BlueprintCallable, Category="Building")
	void DestroyPreviewBuilding();

	UFUNCTION(Unreliable, Server, WithValidation, Category="Building_RPC")
	void Server_DestroyPreviewBuilding();

private:

	FTimerHandle UpdatePreviewObjectLocationTimer;
	
	ABuildingActor* PreviewBuildingObject;
	UMaterialInstanceDynamic* PreviewDynamic;

	void UpdatePreviewObjectLocation() const;
	
};
