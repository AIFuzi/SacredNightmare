#include "Building/BuildingActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Characters/PlayerCharacter.h"
#include "Components/HealthComponent.h"

ABuildingActor::ABuildingActor()
{
	bReplicates = true;
	
	BuildingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingCollision"));
	BuildingCollision->SetupAttachment(RootComponent);

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(BuildingCollision);

	BuildingHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("BuildingHealth"));
}

void ABuildingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuildingActor, PlayerOwner);
}

void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingActor::OnRep_PlayerOwner()
{
	if(PlayerOwner)
	{
		SetInstigator(PlayerOwner);
		SetOwner(PlayerOwner);
	}
	else
	{
		SetOwner(nullptr);
		SetInstigator(nullptr);
	}
}

APlayerCharacter* ABuildingActor::GetPlayerOwner() const
{
	return PlayerOwner;
}
