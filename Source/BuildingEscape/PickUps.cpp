// Copyright Erik 2020


#include "PickUps.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUps::APickUps()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = MeshComp;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUps::AddToInv(ACharacter_BuildingESC* Player)
{
	if (Player)
	{
		InvenComp = Player->PlayerInventoryComp;
		if (InvenComp)
		{
			InvenComp->AddItemToInventory(this);
		}
	}
}



