#include "Items/ItemActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

AItemActor::AItemActor()
{
	bReplicates = true;
	
	ItemBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemBoxCollision"));
	ItemBoxCollision->SetupAttachment(RootComponent);

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(ItemBoxCollision);
}

void AItemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemActor, CurrentMiningCondition);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

int AItemActor::GetCurrentCondition()
{
	return CurrentMiningCondition;
}

void AItemActor::UpdateCondition()
{
	Server_UpdateCondition();
}

void AItemActor::Server_UpdateCondition_Implementation()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		CurrentMiningCondition++;
		CurrentMiningCondition = FMath::Min(CurrentMiningCondition, ItemStruct.MiningCondition);
	}
}

bool AItemActor::Server_UpdateCondition_Validate() { return true; }




