#include "Components/BuildingComponent.h"
#include "Components/InventoryComponent.h"
#include "Building/BuildingActor.h"
#include "Components/BoxComponent.h"

UBuildingComponent::UBuildingComponent()
{

}

void UBuildingComponent::FindItemForBuilding(UInventoryComponent* InventoryComponent,
	TArray<FBuildingStruct> NeedItems, bool& IsItemFound, TArray<FItemStruct>& Items)
{
	if(InventoryComponent)
	{
		bool bItemFound = false;
		FItemStruct FoundItem;
		
		bool bIsItemsForBuildFound = false;
		TArray<FItemStruct> ItemsForBuild;

		for(int i = 0; i < NeedItems.Num(); i++)
		{
			InventoryComponent->FindItemInInventoryByName(NeedItems[i].ItemName, bItemFound, FoundItem);

			if(!bItemFound || FoundItem.ItemCount < NeedItems[i].Count)
			{
				bIsItemsForBuildFound = false;
				break;
			}
			else
			{
				ItemsForBuild.Add(FoundItem);
				bIsItemsForBuildFound = true;
			}
		}

		IsItemFound = bIsItemsForBuildFound;
		Items = ItemsForBuild;
	}
}

void UBuildingComponent::SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInstanceDynamic* PreviewMaterial)
{
	Server_SpawnPreviewBuilding(BuildingClass, PreviewMaterial);
}

void UBuildingComponent::Server_SpawnPreviewBuilding_Implementation(TSubclassOf<ABuildingActor> BuildingClass, UMaterialInstanceDynamic* PreviewMaterial)
{
	const FVector SpawnLoc (0.f, 0.f, 0.f);
	const FRotator SpawnRot(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	PreviewBuildingObject = GetWorld()->SpawnActor<ABuildingActor>(BuildingClass, SpawnLoc, SpawnRot, SpawnParameters);
	if(GetOwner() && PreviewBuildingObject)
	{
		GetWorld()->GetTimerManager().SetTimer(UpdatePreviewObjectLocationTimer, this, &UBuildingComponent::UpdatePreviewObjectLocation, 0.01, true);

		PreviewDynamic = PreviewBuildingObject->BuildingMesh->CreateDynamicMaterialInstance(0, PreviewMaterial);
	}
}

bool UBuildingComponent::Server_SpawnPreviewBuilding_Validate(TSubclassOf<ABuildingActor> BuildingClass, UMaterialInstanceDynamic* PreviewMaterial) { return true; }

void UBuildingComponent::DestroyPreviewBuilding()
{
	Server_DestroyPreviewBuilding();
}

void UBuildingComponent::Server_DestroyPreviewBuilding_Implementation()
{
	if(PreviewBuildingObject)
    	{
    		GetWorld()->GetTimerManager().ClearTimer(UpdatePreviewObjectLocationTimer);
    		
    		PreviewBuildingObject->Destroy();
    		PreviewBuildingObject = nullptr;
    	}
}

bool UBuildingComponent::Server_DestroyPreviewBuilding_Validate() { return true; }

void UBuildingComponent::UpdatePreviewObjectLocation() const
{
	const FVector NewLocationXY = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200.f;
	const FVector NewLocationZ = GetOwner()->GetActorLocation() + PreviewBuildingObject->BuildingCollision->GetScaledBoxExtent().Z / 2.f;
	PreviewBuildingObject->SetActorLocation(FVector(NewLocationXY.X, NewLocationXY.Y, NewLocationZ.Z));
}







