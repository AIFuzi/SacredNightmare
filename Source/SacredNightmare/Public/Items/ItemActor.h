#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int MiningCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	float RegenRate;
	
};

UCLASS()
class SACREDNIGHTMARE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AItemActor();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UBoxComponent* ItemBoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemActor")
	class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemInfo")
	FItemStruct ItemStruct;
	
};
