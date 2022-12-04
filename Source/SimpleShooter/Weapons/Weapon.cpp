// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/ShooterCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	RootComponent = RootComp;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	MeshComp->SetupAttachment(RootComp);
}

void AWeapon::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("PULL TRIGGER"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComp, TEXT("MuzzleFlashSocket"));

	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr) return;

	AController* ownerController = ownerPawn->GetController();
	if (ownerController == nullptr) return;

	FVector viewportLocation;
	FRotator viewportRotation;
	ownerController->GetPlayerViewPoint(viewportLocation, viewportRotation);

	FVector end = viewportLocation + viewportRotation.Vector() * MaxRange;
	
	//DrawDebugCamera(GetWorld(), viewportLocation, viewportRotation, 90, 2, FColor::Red, true);

	FHitResult hit;

	if (bool hasHit = GetWorld()->LineTraceSingleByChannel(hit, viewportLocation, end, ECollisionChannel::ECC_GameTraceChannel1))
	{
		FVector shotDirection = -viewportRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,hit.Location, shotDirection.Rotation());

		FPointDamageEvent DamageEvent(Damage, hit, shotDirection, nullptr);
		AActor* targetActor = hit.GetActor();

		if (targetActor != nullptr)
		{
			targetActor->TakeDamage(Damage, DamageEvent, ownerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

