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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//TODO FPlatformTime might cause problems
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) 
	{
		FiringState = EFiringState::Reloading;
	}
	else if(isBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}
}



void UTankAimingComponent::Initialise(UTankTurret* Turret, UTankBarrel* Barrel)
{
	if (!ensure(Turret && Barrel)) {
		return;
	}
	this->Turret = Turret;
	this->Barrel = Barrel;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
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
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else {
		//TODO max range in Yaw
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
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

bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.05f);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBP && Barrel)) { return; }
	if (FiringState == EFiringState::Reloading) { return; }
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
