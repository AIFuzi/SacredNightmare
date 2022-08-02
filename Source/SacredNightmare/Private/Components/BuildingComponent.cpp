#include "Components/BuildingComponent.h"
#include "Components/InventoryComponent.h"
#include "Building/BuildingActor.h"
#include "Characters/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

UBuildingComponent::UBuildingComponent()
{

}

void UBuildingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBuildingComponent, bIsItemsFoundForBuild);
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

void UBuildingComponent::SpawnPreviewBuilding(TSubclassOf<class ABuildingActor> BuildingClass, UMaterialInterface* PreviewMaterial, UInventoryComponent* InventoryComponent)
{
	Server_SpawnPreviewBuilding(BuildingClass, PreviewMaterial, InventoryComponent);
}

void UBuildingComponent::Server_SpawnPreviewBuilding_Implementation(TSubclassOf<ABuildingActor> BuildingClass, UMaterialInterface* PreviewMaterial, UInventoryComponent* InventoryComponent)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		if(!PreviewBuildingObject)
		{
			const FVector SpawnLoc (0.f, 0.f, 0.f);
			const FRotator SpawnRot(0.f, 0.f, 0.f);

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			PreviewBuildingObject = GetWorld()->SpawnActor<ABuildingActor>(BuildingClass, SpawnLoc, SpawnRot, SpawnParameters);
			if(GetOwner() && PreviewBuildingObject)
			{
				bool bIsItemsFound = false;
				TArray<FItemStruct> ItemsForBuild;
				
				GetWorld()->GetTimerManager().SetTimer(UpdatePreviewObjectLocationTimer, this, &UBuildingComponent::UpdatePreviewObjectLocation, 0.01, true);
				Multicast_CreatePreviewMaterial(PreviewBuildingObject->BuildingMesh, PreviewMaterial);

				FindItemForBuilding(InventoryComponent, PreviewBuildingObject->NeedItemForBuild, bIsItemsFound, ItemsForBuild);
				ActivateBuildingMode(true);
				bIsItemsFoundForBuild = bIsItemsFound;

				SetIsSpawnBuilding(bIsItemsFound);
			
				if(APlayerCharacter* PlayerOwner = Cast<APlayerCharacter>(GetOwner()))
				{
					PreviewBuildingObject->PlayerOwner = PlayerOwner;
					PreviewBuildingObject->OnRep_PlayerOwner();
				}
			}
		}
		else
		{
			if(bIsAbleToBuild && bIsItemsFoundForBuild)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				
				if(const ABuildingActor* Building = GetWorld()->SpawnActor<ABuildingActor>(BuildingClass ,PreviewBuildingObject->GetActorLocation(), PreviewBuildingObject->GetActorRotation(), SpawnParameters))
				{
					RemoveBuildingItems(InventoryComponent, Building->NeedItemForBuild);
					DestroyPreviewBuilding();
					
					Building->OnSpawnBuildingInWorld.Broadcast();
				}
			}
		}
	}
}

bool UBuildingComponent::Server_SpawnPreviewBuilding_Validate(TSubclassOf<ABuildingActor> BuildingClass, UMaterialInterface* PreviewMaterial, UInventoryComponent* InventoryComponent) { return true; }

void UBuildingComponent::Multicast_CreatePreviewMaterial_Implementation(UStaticMeshComponent* PreviewMeshTarget, UMaterialInterface* PreviewMaterial)
{
	PreviewDynamic = PreviewMeshTarget->CreateDynamicMaterialInstance(0, PreviewMaterial);
}

bool UBuildingComponent::Multicast_CreatePreviewMaterial_Validate(UStaticMeshComponent* PreviewMeshTarget, UMaterialInterface* PreviewMaterial) { return true; }

void UBuildingComponent::DestroyPreviewBuilding()
{
	Server_DestroyPreviewBuilding();
}

void UBuildingComponent::Server_DestroyPreviewBuilding_Implementation()
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		if(PreviewBuildingObject)
		{
			GetWorld()->GetTimerManager().ClearTimer(UpdatePreviewObjectLocationTimer);
    	
			PreviewBuildingObject->Destroy();
			PreviewBuildingObject = nullptr;
			ActivateBuildingMode(false);
			bIsItemsFoundForBuild = false;
		}
	}
}

bool UBuildingComponent::Server_DestroyPreviewBuilding_Validate() { return true; }

void UBuildingComponent::UpdatePreviewObjectLocation() const
{
	const FVector NewLocationXY = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * PreviewDistance;
	const FVector NewLocationZ = GetOwner()->GetActorLocation() + PreviewBuildingObject->BuildingCollision->GetScaledBoxExtent().Z / 2.f;
	PreviewBuildingObject->SetActorLocation(FVector(NewLocationXY.X, NewLocationXY.Y, NewLocationZ.Z));
}

void UBuildingComponent::SetIsSpawnBuilding(bool IsSpawn)
{
	Multicast_SetIsSpawnBuilding(IsSpawn);
}

void UBuildingComponent::Multicast_SetIsSpawnBuilding_Implementation(bool IsSpawn)
{
	if(PreviewDynamic)
	{
		if(IsSpawn && bIsItemsFoundForBuild)
		{
			PreviewDynamic->SetVectorParameterValue("Color", FLinearColor(0.f, 1.f, 0.f, 1.f));
			bIsAbleToBuild = true;
		}
		else
		{
			PreviewDynamic->SetVectorParameterValue("Color", FLinearColor(1.f, 0.f, 0.f, 1.f));
			bIsAbleToBuild = false;
		}
	}
}

bool UBuildingComponent::Multicast_SetIsSpawnBuilding_Validate(bool IsSpawn) { return true; }

void UBuildingComponent::ActivateBuildingMode(bool Activate)
{
	bIsBuildingModeActivate = Activate;
}

bool UBuildingComponent::IsActivateBuildingMode() const
{
	return bIsBuildingModeActivate;
}

void UBuildingComponent::RotateBuilding()
{
	Server_RotateBuilding();
}

void UBuildingComponent::Server_RotateBuilding_Implementation()
{
	if(PreviewBuildingObject)
	{
		PreviewBuildingObject->AddActorWorldRotation(FRotator(0.f, 90.f, 0.f));
	}
}

bool UBuildingComponent::Server_RotateBuilding_Validate() { return true; }

void UBuildingComponent::RemoveBuildingItems(UInventoryComponent* InventoryComponent, TArray<FBuildingStruct> BuildingItems)
{
	for (int i = 0; i < BuildingItems.Num(); i++)
	{
		InventoryComponent->RemoveItemFromInventory(BuildingItems[i].ItemName, false, BuildingItems[i].Count);
	}
}