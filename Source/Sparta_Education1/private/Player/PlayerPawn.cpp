#include "Player/PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerPawn::APlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    RootComponent = CapsuleComp;

    CapsuleComp->SetSimulatePhysics(false);
    CapsuleComp->SetCollisionResponseToChannel(
        ECC_WorldDynamic,
        ECR_Overlap);
    
    
    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetSimulatePhysics(false);

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

        if (Subsystem && InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!MoveInput.IsNearlyZero())
    {
        const FRotator CameraRot = CameraComp->GetComponentRotation();
        const FRotator YawRot(0.0f, CameraRot.Yaw, 0.0f);

        const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
        const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
        
        FVector MoveDirection =
            Forward * MoveInput.Y +
            Right * MoveInput.X;
        
        MoveDirection.Z = 0.0f;
        MoveDirection.Normalize();

        AddActorWorldOffset(MoveDirection * MoveSpeed * DeltaTime, true);
    }

    if (!LookInput.IsNearlyZero())
    {
        const float Yaw = LookInput.X * LookSpeed * DeltaTime;
        const float Pitch = LookInput.Y * LookSpeed * DeltaTime;

        AddActorLocalRotation(FRotator(0.0f, Yaw, 0.0f));

        FRotator SpringRot = SpringArmComp->GetRelativeRotation();
        SpringRot.Pitch = FMath::Clamp(SpringRot.Pitch - Pitch, -60.0f, 60.0f);
        SpringArmComp->SetRelativeRotation(SpringRot);
    }
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComp)
    {
        EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
        EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerPawn::Move);

        EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::Look);
        EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Completed, this, &APlayerPawn::Look);
    }
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
    MoveInput = Value.Get<FVector2D>();
}

void APlayerPawn::Look(const FInputActionValue& Value)
{
    LookInput = Value.Get<FVector2D>();
}