@call %1.bat > %1.out
@if %errorlevel% neq 0 (
  @echo Build Step failed for %1
  @exit %errorlevel%)
@echo Build Step complete for %1
