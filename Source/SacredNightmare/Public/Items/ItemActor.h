#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class SACREDNIGHTMARE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AItemActor();

	virtual void BeginPlay() override;

};
