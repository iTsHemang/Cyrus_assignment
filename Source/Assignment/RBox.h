// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RBox.generated.h"

class ABoxSpawner;
class UUI;

UCLASS()
class ASSIGNMENT_API ARBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cube;
	
	UPROPERTY()
	UMaterialInstanceDynamic* CubeMaterial;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintreadWrite, EditAnywhere)
	int32 health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 score;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString name;

	UPROPERTY()
	ABoxSpawner* BS;
	
	UUI* ui;

	void InitializeCube(const FLinearColor& Color, int32 Ihealth, int32 Iscore, FString Iname);

	void BoxDamage();
};
