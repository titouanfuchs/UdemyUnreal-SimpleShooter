// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeapon;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
		bool IsDead() const {return Health <= 0;};
private:

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health;
	
	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);

	void Shoot();

	UPROPERTY(EditAnywhere)
		float RotationRate = 50.f;

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeapon> WeaponClass;

	AWeapon* CurrentWeapon;
};
