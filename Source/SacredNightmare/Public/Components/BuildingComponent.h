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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Building")
	float PreviewDistance;
	
	UFUNCTION(BlueprintPure, Category="Building")
	void FindItemForBuilding(class UInventoryComponent* InventoryComponent, TArray<FBuildingStruct> NeedItems, bool& IsItemFound, TArray<FItemStruct>& Items);

	UFUNCTION(BlueprintCallable, Category="Building")
	void SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInterface* PreviewMaterial, UInventoryComponent* InventoryComponent);

	UFUNCTION(Unreliable, Server, WithValidation, Category="Building_RPC")
	void Server_SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInterface* PreviewMaterial, UInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable, Category="Building")
	void DestroyPreviewBuilding();

	UFUNCTION(Unreliable, Server, WithValidation, Category="Building_RPC")
	void Server_DestroyPreviewBuilding();

	UFUNCTION(Unreliable, NetMulticast, WithValidation, Category="Building_RPC")
	void Multicast_CreatePreviewMaterial(UStaticMeshComponent* PreviewMeshTarget, UMaterialInterface* PreviewMaterial);

	UFUNCTION(BlueprintCallable, Category="Building")
	void SetIsSpawnBuilding(bool IsSpawn);

	UFUNCTION(Unreliable, NetMulticast, WithValidation, Category="Building_RPC")
	void Multicast_SetIsSpawnBuilding(bool IsSpawn);

	UFUNCTION(BlueprintCallable, Category="Building")
	void ActivateBuildingMode(bool Activate);

	UFUNCTION(BlueprintPure, Category="Building")
	bool IsActivateBuildingMode() const;

	UFUNCTION(BlueprintCallable, Category="Building")
	void RotateBuilding();

	UFUNCTION(Unreliable, Server, WithValidation, Category="Building_RPC")
	void Server_RotateBuilding();

private:

	FTimerHandle UpdatePreviewObjectLocationTimer;

	ABuildingActor* PreviewBuildingObject;
	
	UMaterialInstanceDynamic* PreviewDynamic;

	void UpdatePreviewObjectLocation() const;

	bool bIsAbleToBuild = true;
	bool bIsBuildingModeActivate = false;

	UPROPERTY(Replicated)
	bool bIsItemsFoundForBuild = false;
	
};
