// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry,All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	//printTransform();
	//printStringTypes();
	//printTypes();

	SetColor(GeometryData.Color);

	//参数：计时器句柄;每次计数器触发时要在其上调用函数的对象指针;每次触发时都会调用的函数的引用;计时器频率;计时器是否循环
	GetWorldTimerManager().SetTimer(TimerHandle,this, &ABaseGeometryActor::OnTimerFired,GeometryData.TimerRate,true);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	HandleMovement();

}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name: %s"), *GetName());

	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons NUM:%d,Kills num:%i "), WeaponsNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health:%.2f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead:%d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon:%d"), static_cast<int>(HasWeapon));
}
void ABaseGeometryActor::PrintStringTypes() {
	FString Name = "John";

	UE_LOG(LogBaseGeometry, Display, TEXT("Name:%s"), *Name);


	FString WeaponsNumStr = "weapons num : " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health : " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "IsDead : " + FString(IsDead ? "true" : "false");

	FString stat = FString::Printf(TEXT("\n == ALL Stat == \n %s  \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *stat);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, stat, true, FVector2D(1.5f, 1.5f));
	}
}
void ABaseGeometryActor::PrintTransform() {

	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale %s"), *Scale.ToString());

	UE_LOG(LogBaseGeometry, Error, TEXT("Human transform %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin: {
		FVector CurrentLocation = GetActorLocation();
		if (GetWorld()) {//确保游戏对象存在
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);

			SetActorLocation(CurrentLocation);
		}
	}
	break;
	
	case EMovementType::Static:
		break;
	default:
		break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	//参数：材质索引
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial) {
		//参数：材质中参数的名称
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount) {
		//局部变量声明为const，表示该变量的值在初始化后不能被修改。
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("Color to set up: %s"), *NewColor.ToString());
		SetColor(NewColor);
		//调用委托invoke
		OnColorChanged.Broadcast(NewColor,GetName());
	}
	else {
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		//调用委托
		OnTimerFinished.Broadcast(this);
	}
}
