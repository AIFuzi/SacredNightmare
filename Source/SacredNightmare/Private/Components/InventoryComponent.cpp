#include "Components/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, InventoryArray);
}

TArray<FItemStruct> UInventoryComponent::GetInventoryInfo()
{
	return InventoryArray;
}

void UInventoryComponent::AddItemToInventory(FItemStruct ItemAdded)
{
	Server_AddItemToInventory(ItemAdded);
}

void UInventoryComponent::Server_AddItemToInventory_Implementation(FItemStruct ItemAdded)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		if(InventoryArray.Num() > 0)
		{
			int itemIndex = 0;
			bool bIsItemFound = false;
			
			for(int i = 0; i < InventoryArray.Num(); i++)
			{
				if(InventoryArray[i].ItemName == ItemAdded.ItemName)
				{
					itemIndex = i;
					bIsItemFound = true;
					break;
				}
			}

			if(bIsItemFound) InventoryArray[itemIndex].ItemCount = InventoryArray[itemIndex].ItemCount + ItemAdded.ItemCount;
			else InventoryArray.Add(ItemAdded);
		}
		else InventoryArray.Add(ItemAdded);
	}
}

bool UInventoryComponent::Server_AddItemToInventory_Validate(FItemStruct ItemAdded) { return true; }

void UInventoryComponent::FindItemInInventoryByName(FName ItemName, bool& ItemFound, FItemStruct& Item)
{
	ItemFound = false;
	
	for(int i = 0; i < InventoryArray.Num(); i++)
	{
		if(InventoryArray[i].ItemName == ItemName)
		{
			Item = InventoryArray[i];
			ItemFound = true;
			
			break;
		}
	}
}

void UInventoryComponent::TestFuncRetVal(FName Name)
{
	bool bTeB = false;
	FItemStruct testItem;
	
	FindItemInInventoryByName(Name, bTeB, testItem);


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, bTeB? "True" : "False");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::FromInt(testItem.ItemCount));
}
