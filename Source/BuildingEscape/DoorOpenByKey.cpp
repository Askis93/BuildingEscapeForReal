// Copyright Erik 2020


#include "DoorOpenByKey.h"

// Sets default values
ADoorOpenByKey::ADoorOpenByKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorOpenByKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorOpenByKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

