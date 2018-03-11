// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UTankAimingComponent::Initialise(UTankTurret* Turret, UTankBarrel* Barrel)
{
	if (!ensure(Turret && Barrel)) {
		return;
	}
	this->Turret = Turret;
	this->Barrel = Barrel;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!ensure(Barrel) || !ensure(Turret)) { 
		return; 
	}

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	//calculate launch velocity

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else {
		//TODO max range in Yaw
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	UE_LOG(LogTemp, Warning, TEXT("CALLED"));
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	//work out difference between current barrel and required
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator RequiredRotator = Direction.Rotation();
	FRotator DeltaRotator = RequiredRotator - BarrelRotator;

	//move such given max speed given frametime
	Barrel->ElevateBarrel(DeltaRotator.Pitch); 
	///TODO gjør en mindre yalla fix
	float Rotation = DeltaRotator.Yaw;
	if (Rotation < -180) {
		//Rotation other way is best
		Rotation = 1;
	}
	if (Rotation > 180) {
		//same
		Rotation = -1;
	}
	Turret->RotateTurret(Rotation);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (!isReloaded) { return; }
	LastFireTime = FPlatformTime::Seconds();
	//Spawn projectile at socket location from barrel
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("ProjectileStart")),
		Barrel->GetSocketRotation(FName("ProjectileStart"))
		);
	if (!ensure(Projectile)) { return; }
	Projectile->Launch(LaunchSpeed);
}
