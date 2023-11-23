// Copyright Weilin


#include "UI/Widget/AuroraUserWidget.h"

void UAuroraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
