// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	//DoActorSpawn3();
	DoActorSpawn4();
}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; ++i) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
			//生成SpanActor
			//参数：生成的actor类，位置，旋转，使用默认值
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; ++i) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
			//生成SpanActor
			//SpawnActorDeferred表示仅调用actor的构造函数，而不调用BeginPlay函数 参数：生成的actor类，位置，旋转，使用默认值
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if (Geometry)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);//手动调用BeginPlay()
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld();
	if (World) {
		for (const FGeometryPayload Payload : GeometryPayloads) {
			//生成ABaseGeometryActor
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

			if (Geometry) {
				Geometry->SetGeometryData(Payload.Data);
				//添加动态委托使用AddDynamic。参数： 指向对象的指针，对该对象功能的引用（即，当委托被触发时，将调用它）
				Geometry->OnColorChanged.AddDynamic(this,&AGeometryHubActor::OnColorChanged);
				//不是动态委托使用AddUObject。参数同上；
				Geometry->OnTimerFinished.AddUObject(this,&AGeometryHubActor::OnTimerFinished);
				Geometry->FinishSpawning(Payload.InitialTransform);//手动调用BeginPlay()

			}
		}
	}
}
void AGeometryHubActor::DoActorSpawn4() {
	if (!GetWorld()) return;
	FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 300.0f, 300.0f));
	NonePropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

	GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(700.0f, 700.0f, 300.0f));
	PropertyActor = GetWorld()->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
}
//颜色变化
void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString());
}
//计时器
void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"),*Actor->GetName());

	//Cast将基类指针转换为只想子类的指针
	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude %f"), Geometry->GetGeometryData().Amplitude);

	//删除
	Geometry->Destroy();
	//计时器，多少秒后执行删除操作
	//Geometry->SetLifeSpan(2.0f);
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogGeometryHub, Warning, TEXT("Property pointer %i, is valid %i"), PropertyActor!=nullptr,IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Error, TEXT("none Property pointer %i, is valid %i"), NonePropertyActor!=nullptr,IsValid(NonePropertyActor));
}