// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}



void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn()->FindComponentByClass<UTankAimingComponent>())) { return; }

	FVector HitLocation;

	//Get World Location through(linetrace) crosshair
	if (GetSightRayHitLocation(OUT HitLocation)) {
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OUT HitLocation) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	//De-project screen pos of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,OUT LookDirection)) {
		// line-trace along that look direction (up to max range)
		return GetLookHitLocation(LookDirection, OUT HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookHitLocation(FVector LookDirection, FVector& OUT HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		OUT LookDirection
	);

}
