#include "Building/BuildingActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ABuildingActor::ABuildingActor()
{
	BuildingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingCollision"));
	BuildingCollision->SetupAttachment(RootComponent);

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(BuildingCollision);
}

void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}
