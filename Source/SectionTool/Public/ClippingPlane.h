// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"
#include "ClippingPlaneVolume.h"
#include "ClippingPlane.generated.h"

UCLASS()
class SECTIONTOOL_API AClippingPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClippingPlane();

	UPROPERTY(BlueprintReadOnly)
		USceneComponent* Root;
	UPROPERTY(BlueprintReadOnly)
		USceneComponent* Plane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ThePlaneMesh;
	UPROPERTY(EditAnywhere)
		UMaterialInstanceDynamic* MaterialInstance;

	AClippingPlaneVolume* TheVolume;
	FVector VolumeLocation;
	FVector PlaneOriginalLocation;
	UPROPERTY(BlueprintReadOnly)
		FVector VolumeBoxExtent;
	UPROPERTY(BlueprintReadWrite)
		float VolumeBoundSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetVolumeBoundSize(float Size);
	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetPlaneToOriginal();
	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetPlaneHeight(float Height);
	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetPlaneVertical();
	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetPlaneRotation(float Pitch);
	UFUNCTION(BlueprintCallable, Category = "PlaneTransform")
		void SetPlaneOffSet(float ZValue);

private:
	UFUNCTION()
		void Clip();
};
