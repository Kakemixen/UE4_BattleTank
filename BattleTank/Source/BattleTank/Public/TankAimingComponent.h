// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward Decloeration
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//class comment
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(Blueprintcallable, Category = Setup)
		void Initialise(UTankTurret* Turret, UTankBarrel* Barrel);
	
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Locked;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection = FVector(0);

	void MoveBarrelTowards(FVector Direction);
	bool isBarrelMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	double LastFireTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double ReloadTimeSeconds = 2;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;



	
};
