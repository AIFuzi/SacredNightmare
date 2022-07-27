#include "Components/HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{

}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::DamageChar(float Damage)
{
	Server_DamageChar(Damage);
}

void UHealthComponent::Server_DamageChar_Implementation(float Damage)
{
	if(GetOwnerRole() == ROLE_Authority) CurrentHealth -= Damage;
}

bool UHealthComponent::Server_DamageChar_Validate(float Damage) { return  true; }
