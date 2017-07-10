del *.ncb
del *.ilk
del *.lib
del *.sdf
del *.exp
del *.map
del *.pdb
del Upgradelog.xml
del *.exe
del *.bsc
del applog.txt
del *.suo /AH
del *.user
del debug\*.* /Q
del release\*.* /Q
del x64\debug\*.* /Q
del x64\release\*.* /Q
del debug\template.tlog\*.* /Q
del release\template.tlog\*.* /Q
del x64\debug\template.tlog\*.* /Q
del x64\release\template.tlog\*.* /Q
rd debug\template.tlog
rd release\template.tlog
rd x64\debug\template.tlog
rd x64\release\template.tlog
rd release /Q
rd debug /Q
rd x64\release /Q
rd x64\debug /Q
rd x64

