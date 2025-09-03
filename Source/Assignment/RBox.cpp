// Fill out your copyright notice in the Description page of Project Settings.


#include "RBox.h"
#include "BoxSpawner.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ARBox::ARBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	RootComponent = Cube;
	Cube->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Cube->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Cube->SetNotifyRigidBodyCollision(true); 

	//setting box static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	Cube->SetStaticMesh(CubeAsset.Object);
}

// Called when the game starts or when spawned
void ARBox::BeginPlay()
{
	Super::BeginPlay();
	
	//Getting widget class
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UUI::StaticClass(), false);

	for (UUserWidget* Widget : Widgets)
	{
		ui = Cast<UUI>(Widget);
	}
	
}

// Called every frame
void ARBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//getting data from box spawner
void ARBox::InitializeCube(const FLinearColor& Color, int32 Ihealth, int32 Iscore, FString Iname)
{
	health = Ihealth;
	score = Iscore;
	name = Iname;

	if (!CubeMaterial)
	{
		CubeMaterial = Cube->CreateDynamicMaterialInstance(0);
	}

	if (CubeMaterial)
	{
		//Setting box color parameter
		CubeMaterial->SetVectorParameterValue(TEXT("Color"), Color);
	}
}

//Taking damage
void ARBox::BoxDamage()
{
	//Taking single health off
	health -= 1;


	//Checking if health is zero
	if (health <= 0)
	{
	    if (ui)
	    {
	    	//Updating score
		    ui->setscore(name, score);
		}

		//Spawning other box
		BS->SpawnBox();

		//Destroying self
		Destroy();

	}
}

