// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * kake
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;


private:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Move barrel so a shot would hit where crosshair intersects world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OUT HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OUT LookDirection) const;
	bool GetLookHitLocation(FVector LookDirection, FVector& OUT HitLocation) const;


};
