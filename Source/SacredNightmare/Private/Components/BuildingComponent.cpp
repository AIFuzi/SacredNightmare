#include "Components/BuildingComponent.h"
#include "Components/InventoryComponent.h"

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


