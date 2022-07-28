#include "Items/ItemActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AItemActor::AItemActor()
{
	ItemBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemBoxCollision"));
	ItemBoxCollision->SetupAttachment(RootComponent);

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(ItemBoxCollision);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

int AItemActor::GetCurrentCondition()
{
	return CurrentMiningCondition;
}

