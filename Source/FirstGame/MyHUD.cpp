#include "MyHUD.h"


void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    FString WaveText = FString::Printf(TEXT("Wave: %d"), CurrentWave + 1);
    FString EnemyText = FString::Printf(TEXT("Enemies: %d"), EnemyCount);

    // �����ı�λ��
    FVector2D WavePosition(50, 50);
    FVector2D EnemyPosition(50, 100);

    // �����ı�
    DrawText(WaveText, FColor::White, WavePosition.X, WavePosition.Y, nullptr, 2.0f, false);
    DrawText(EnemyText, FColor::White, EnemyPosition.X, EnemyPosition.Y, nullptr, 2.0f, false);

    if (bIsTakingDamage)
    {
        // ���㵱ǰ��͸����
        if (DamageEffectTime <= 0.25f)
            CurrentOpacity = FMath::Lerp(0.0f, 0.3f, DamageEffectTime / 0.25f);
        else
            CurrentOpacity = FMath::Lerp(0.3f, 0.0f, (DamageEffectTime - 0.25f) / 0.25f);
        // ����ȫ����ɫ����
        FCanvasTileItem TileItem(FVector2D(0, 0), FVector2D(Canvas->SizeX, Canvas->SizeY), FLinearColor(1, 0, 0, CurrentOpacity));
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
        // ����Ч��ʱ��
        DamageEffectTime -= GetWorld()->GetDeltaSeconds();
        if (DamageEffectTime <= 0)
        {
            bIsTakingDamage = false;
            CurrentOpacity = 0.0f;
        }
    }

    // ����Ѫ������
    FVector2D HealthBarPosition(Canvas->SizeX / 2 - 500, Canvas->SizeY - 100);
    FVector2D HealthBarSize(1000, 40);
    FCanvasTileItem HealthBarBackground(HealthBarPosition, HealthBarSize, FLinearColor::Black);
    Canvas->DrawItem(HealthBarBackground);
    // ����Ѫ��
    FVector2D HealthBarFillSize(HealthBarSize.X * HealthPercentage, HealthBarSize.Y);
    FCanvasTileItem HealthBarFill(HealthBarPosition, HealthBarFillSize, FLinearColor::Red);
    Canvas->DrawItem(HealthBarFill);

}

void AMyHUD::SetCurrentWave(int32 Wave)
{
    CurrentWave = Wave;
}

void AMyHUD::SetEnemyCount(int32 Count)
{
    EnemyCount = Count;
}

void AMyHUD::ShowDamageEffect()
{
    bIsTakingDamage = true;
    DamageEffectTime = DamageEffectDuration;
}

void AMyHUD::UpdateHealth(float HealthPercent)
{
    HealthPercentage = HealthPercent;
}
