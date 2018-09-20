@"c:\program files (x86)\national instruments\cvi2017\bin\cvilink.exe" -cmd:link_options.txt -flags:0 -expiry:0 > Link.out 2>&1
@if errorlevel 1 goto err
@echo Link success
@echo Link complete
@exit 0
:err
@echo Link complete
@echo Link failed
@exit 1
