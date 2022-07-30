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
	static void FindItemForBuilding(class UInventoryComponent* InventoryComponent, TArray<FBuildingStruct> NeedItems, bool& IsItemFound, TArray<FItemStruct>& Items);
};
