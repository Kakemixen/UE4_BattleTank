// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("Tank No barrel %s"), *GetOwner()->GetName());
		return;
	}

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

	//calculate launch velocity

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"),
			*AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	//work out difference between current barrel and required
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator RequiredRotator = Direction.Rotation();
	FRotator DeltaRotator = RequiredRotator - BarrelRotator;

	//move such given max speed given frametime
	//TODO Barrel
	//TODO Turret
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* Barrel)
{
	this->Barrel = Barrel;
}

