// Copyright Erik 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTracer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API ULineTracer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULineTracer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public: 
	AActor* LineTraceSingle(FVector Start, FVector End);
	AActor* LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine);
};
