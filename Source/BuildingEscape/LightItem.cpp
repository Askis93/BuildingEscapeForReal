// Copyright Erik 2020


#include "LightItem.h"

ULightItem::ULightItem()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->InitSphereRadius(40.f);
	CollisionComp->SetCollisionProfileName(TEXT("LightColl"));

	SM_Light = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light"));
	//SM_Light->SetupAttachment(RootComponent);
}

void ULightItem::Use(ACharacter_BuildingESC* Character)
{
}

void ULightItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
