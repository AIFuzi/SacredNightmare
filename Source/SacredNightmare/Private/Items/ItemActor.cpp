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

int AItemActor::GetCurrentCondition() const
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

		if(CurrentMiningCondition >= ItemStruct.MiningCondition)
		{
			IsMiningCooldown = true;
			OnItemMiningCooldownStart.Broadcast();
			
			GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &AItemActor::ClearCooldown, ItemStruct.RegenRate, false);
		}
	}
}

bool AItemActor::Server_UpdateCondition_Validate() { return true; }

void AItemActor::ClearCooldown()
{
	IsMiningCooldown = false;
	CurrentMiningCondition = 0;
	OnItemMiningCooldownFinish.Broadcast();
	
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimer);
}

bool AItemActor::GetIsCooldown() const
{
	return IsMiningCooldown;
}

