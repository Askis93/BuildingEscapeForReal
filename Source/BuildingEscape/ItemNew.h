// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemNew.generated.h"

UCLASS()
class BUILDINGESCAPE_API AItemNew : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemNew();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
